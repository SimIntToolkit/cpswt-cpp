//
// Copyright (C) 2008 Juan-Carlos Maureira
// Copyright (C) INRIA
// Copyright (C) 2013 OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include "C2WDHCPClient.h"

#include <inet/common/ModuleAccess.h>
#include <inet/networklayer/ipv4/Ipv4InterfaceData.h>
#include <inet/common/lifecycle/NodeStatus.h>
#include <inet/networklayer/ipv4/IIpv4RoutingTable.h>
#include <inet/common/Simsignals.h>


Define_Module(C2WDHCPClient);

C2WDHCPClient::C2WDHCPClient()
{
    timerT1 = NULL;
    timerT2 = NULL;
    timerTo = NULL;
    leaseTimer = NULL;
    startTimer = NULL;
    nb = NULL;
    ie = NULL;
    irt = NULL;
    lease = NULL;
}

C2WDHCPClient::~C2WDHCPClient()
{
    cancelAndDelete(timerT1);
    cancelAndDelete(timerTo);
    cancelAndDelete(timerT2);
    cancelAndDelete(leaseTimer);
    cancelAndDelete(startTimer);
}

void C2WDHCPClient::initialize(int stage)
{
    if (stage == 0)
    {
        timerT1 = new omnetpp::cMessage("T1 Timer",T1);
        timerT2 = new omnetpp::cMessage("T2 Timer",T2);
        timerTo = new omnetpp::cMessage("DHCP Timeout");
        leaseTimer = new omnetpp::cMessage("Lease Timeout",LEASE_TIMEOUT);
        startTimer = new omnetpp::cMessage("Starting DHCP",START_DHCP);
        startTime = par("startTime");
    }
    else if (stage == 3)
    {
        inet::NodeStatus *nodeStatus = dynamic_cast<inet::NodeStatus *>(findContainingNode(this)->getSubmodule("status"));
        isOperational = (!nodeStatus) || nodeStatus->getState() == inet::NodeStatus::UP;

        numSent = 0;
        numReceived = 0;
        xid = 0;
        responseTimeout = 60; // response timeout in seconds RFC 2131, 4.4.3

        WATCH(numSent);
        WATCH(numReceived);
        WATCH(clientState);
        WATCH(xid);

        // DHCP UDP ports
        clientPort = 68; // client
        serverPort = 67; // server

        // get the hostname
        omnetpp::cModule *host = findContainingNode(this);
        hostName = host->getFullName();
        nb = omnetpp::check_and_cast<omnetpp::cModule *>(getModuleByPath(par("notificationBoardPath")));

        // for a wireless interface subscribe the association event to start the DHCP protocol
        nb->subscribe(inet::l2AssociatedSignal, this);
        nb->subscribe(inet::interfaceDeletedSignal, this);

        // get the routing table to update and subscribe it to the blackboard
        irt = omnetpp::check_and_cast<inet::IIpv4RoutingTable*>(getModuleByPath(par("routingTablePath")));
        // set client to idle state
        clientState = IDLE;
        // get the interface to configure

        if (isOperational)
        {
            ie = chooseInterface();
            // grab the interface MAC address
            macAddress = ie->getMacAddress();
            startApp();
        }

        // Use IP address to bind to the client port
        this->ipv4Address = ie->getIpv4Address();
    }
}

inet::InterfaceEntry *C2WDHCPClient::chooseInterface()
{
    inet::IInterfaceTable* ift = omnetpp::check_and_cast<inet::IInterfaceTable*>(getModuleByPath(par("interfaceTablePath")));
    const char *interfaceName = par("interface");
    inet::InterfaceEntry *ie = NULL;

    if (strlen(interfaceName) > 0)
    {
        ie = ift->findInterfaceByName(interfaceName);
        if (ie == NULL)
            throw omnetpp::cRuntimeError("Interface \"%s\" does not exist", interfaceName);
    }
    else
    {
        // there should be exactly one non-loopback interface that we want to configure
        for (int i = 0; i < ift->getNumInterfaces(); i++) {
            inet::InterfaceEntry *current = ift->getInterface(i);
            if (!current->isLoopback()) {
                if (ie)
                    throw omnetpp::cRuntimeError("Multiple non-loopback interfaces found, please select explicitly which one you want to configure via DHCP");
                ie = current;
            }
        }
        if (!ie)
            throw omnetpp::cRuntimeError("No non-loopback interface found to be configured via DHCP");
    }

    if (!ie->getIpv4Address().isUnspecified())
        throw omnetpp::cRuntimeError("Refusing to start DHCP on interface \"%s\" that already has an IP address", dynamic_cast<omnetpp::cModule *>(ie)->getName());
    return ie;
}

void C2WDHCPClient::finish()
{
    cancelEvent(timerT1);
    cancelEvent(timerTo);
    cancelEvent(timerT2);
    cancelEvent(leaseTimer);
    cancelEvent(startTimer);
}

static bool routeMatches(const inet::Ipv4Route *entry, const inet::Ipv4Address& target, const inet::Ipv4Address& nmask,
        const inet::Ipv4Address& gw, int metric, const char *dev)
{
    if (!target.isUnspecified() && !target.equals(entry->getDestination()))
        return false;
    if (!nmask.isUnspecified() && !nmask.equals(entry->getNetmask()))
        return false;
    if (!gw.isUnspecified() && !gw.equals(entry->getGateway()))
        return false;
    if (metric && metric != entry->getMetric())
        return false;
    if (dev && strcmp(dev, entry->getInterfaceName()))
        return false;

    return true;
}

const char *C2WDHCPClient::getStateName(ClientState state)
{
    switch (state)
    {
#define CASE(X)  case X: return #X;
    CASE(INIT);
    CASE(INIT_REBOOT);
    CASE(REBOOTING);
    CASE(SELECTING);
    CASE(REQUESTING);
    CASE(BOUND);
    CASE(RENEWING);
    CASE(REBINDING);
    default: return "???";
#undef CASE
    }
}

const char *C2WDHCPClient::getAndCheckMessageTypeName(inet::DhcpMessageType type)
{
    switch (type)
    {
#define CASE(X)  case X: return #X;
    CASE(inet::DHCPDISCOVER);
    CASE(inet::DHCPOFFER);
    CASE(inet::DHCPREQUEST);
    CASE(inet::DHCPDECLINE);
    CASE(inet::DHCPACK);
    CASE(inet::DHCPNAK);
    CASE(inet::DHCPRELEASE);
    CASE(inet::DHCPINFORM);
    default: throw omnetpp::cRuntimeError("Unknown or invalid DHCP message type %d",type);
#undef CASE
    }
}
void C2WDHCPClient::updateDisplayString()
{
    getDisplayString().setTagArg("t", 0, getStateName(clientState));
}

void C2WDHCPClient::handleMessage(omnetpp::cMessage *msg)
{
    if (!isOperational)
    {
        EV_ERROR << "Message '" << msg << "' arrived when module status is down, dropping." << std::endl;
        delete msg;
        return;
    }
    if (msg->isSelfMessage())
    {
        handleTimer(msg);
    }
    else if (msg->arrivedOn("udpIn"))
    {
        inet::DhcpMessage *dhcpPacket = dynamic_cast<inet::DhcpMessage*>(msg);
        if (!dhcpPacket)
            throw omnetpp::cRuntimeError(dhcpPacket, "Unexpected packet received (not a inet::DhcpMessage)");

        handleDHCPMessage(dhcpPacket);
        delete msg;
    }

    if (inet::getEnvir()->isGUI())
        updateDisplayString();
}

void C2WDHCPClient::handleTimer(omnetpp::cMessage * msg)
{
    int category = msg->getKind();

    if (category == START_DHCP)
    {
        openSocket();
        if (lease)
        {
            clientState = INIT_REBOOT;
            initRebootedClient();
        }
        else // we have no lease from the previous DHCP process
        {
            clientState = INIT;
            initClient();
        }
    }
    else if (category == WAIT_OFFER)
    {
        EV_DETAIL << "No DHCP offer received within timeout. Restarting. " << std::endl;
        initClient();
    }
    else if (category == WAIT_ACK)
    {
        EV_DETAIL << "No DHCP ACK received within timeout. Restarting." << std::endl;
        initClient();
    }
    else if (category == T1)
    {
        EV_DETAIL << "T1 expired. Starting RENEWING state." << std::endl;
        clientState = RENEWING;
        scheduleTimerTO(WAIT_ACK);
        sendRequest();
    }
    else if (category == T2 && clientState == RENEWING)
    {
        EV_DETAIL << "T2 expired. Starting REBINDING state." << std::endl;
        clientState = REBINDING;
        cancelEvent(timerT1);
        cancelEvent(timerT2);
        cancelEvent(timerTo);
        cancelEvent(leaseTimer);

        sendRequest();
        scheduleTimerTO(WAIT_ACK);
    }
    else if (category == T2)
    {
        // T1 < T2 always holds by definition and when T1 expires client will move to RENEWING
        throw omnetpp::cRuntimeError("T2 occurred in wrong state. (T1 must be earlier than T2.)");
    }
    else if (category == LEASE_TIMEOUT)
    {
        EV_INFO << "Lease has expired. Starting DHCP process in INIT state." << std::endl;
        unboundLease();
        clientState = INIT;
        initClient();
    }
    else
        throw omnetpp::cRuntimeError("Unknown self message '%s'", dynamic_cast<omnetpp::cModule *>(msg)->getName());
}

void C2WDHCPClient::recordOffer(inet::DhcpMessage * dhcpOffer)
{
    if (!dhcpOffer->getYiaddr().isUnspecified())
     {
         inet::Ipv4Address ip = dhcpOffer->getYiaddr();

         //Byte serverIdB = dhcpOffer->getOptions().get(SERVER_ID);
         inet::Ipv4Address serverId = dhcpOffer->getOptions().getServerIdentifier();

         // minimal information to configure the interface
         // create the lease to request
         lease = new inet::DhcpLease();
         lease->ip = ip;
         lease->mac = macAddress;
         lease->serverId = serverId;
     }
     else
         EV_WARN << "inet::DHCPOFFER arrived, but no IP address has been offered. Discarding it and remaining in SELECTING." << std::endl;
}

void C2WDHCPClient::recordLease(inet::DhcpMessage * dhcpACK)
{
    if (!dhcpACK->getYiaddr().isUnspecified())
    {
        inet::Ipv4Address ip = dhcpACK->getYiaddr();
        EV_DETAIL << "inet::DHCPACK arrived with " << "IP: " << ip << std::endl;

        lease->subnetMask = dhcpACK->getOptions().getSubnetMask();

        if (dhcpACK->getOptions().getRouterArraySize() > 0)
            lease->gateway = dhcpACK->getOptions().getRouter(0);
        if (dhcpACK->getOptions().getDnsArraySize() > 0)
            lease->dns = dhcpACK->getOptions().getDns(0);
        if (dhcpACK->getOptions().getNtpArraySize() > 0)
            lease->ntp = dhcpACK->getOptions().getNtp(0);

        lease->leaseTime = dhcpACK->getOptions().getLeaseTime();
        lease->renewalTime = dhcpACK->getOptions().getRenewalTime();
        lease->rebindTime = dhcpACK->getOptions().getRebindingTime();

        // std::cout << lease->leaseTime << " " << lease->renewalTime << " " << lease->rebindTime << std::endl;

    }
    else
        EV_ERROR << "inet::DHCPACK arrived, but no IP address confirmed." << std::endl;
}

void C2WDHCPClient::bindLease()
{
    ie->getIpv4Address().set(lease->ip.getInt());
    ie->getIpv4Netmask().set(lease->ip.getNetworkMask().getInt());

    std::string banner = "Got IP " + lease->ip.str();
    this->getParentModule()->bubble(banner.c_str());

    /*
        The client SHOULD perform a final check on the parameters (ping, ARP).
        If the client detects that the address is already in use:
        EV_INFO << "The offered IP " << lease->ip << " is not available." << std::endl;
        sendDecline(lease->ip);
        initClient();
    */

    EV_INFO << "The requested IP " << lease->ip << "/" << lease->subnetMask << " is available. Assigning it to "
            << this->getParentModule()->getFullName() << "." << std::endl;

    inet::Ipv4Route * iroute = NULL;
    for (int i = 0; i < irt->getNumRoutes(); i++)
    {
        inet::Ipv4Route * e = irt->getRoute(i);
        if (routeMatches(e, inet::Ipv4Address(), inet::Ipv4Address(), lease->gateway, 0, dynamic_cast<omnetpp::cModule *>(ie)->getName()))
        {
            iroute = e;
            break;
        }
    }
    if (iroute == NULL)
    {
        // create gateway route
        route = new inet::Ipv4Route();
        route->setDestination(inet::Ipv4Address());
        route->setNetmask(inet::Ipv4Address());
        route->setGateway(lease->gateway);
        route->setInterface(ie);
        route->setSourceType(inet::Ipv4Route::MANUAL);
        irt->addRoute(route);
    }

    // update the routing table
    cancelEvent(leaseTimer);
    scheduleAt(omnetpp::simTime() + lease->leaseTime, leaseTimer);
}

void C2WDHCPClient::unboundLease()
{
    EV_INFO << "Unbound lease on " << dynamic_cast<omnetpp::cModule *>(ie)->getName() << "." << std::endl;

    cancelEvent(timerT1);
    cancelEvent(timerT2);
    cancelEvent(timerTo);
    cancelEvent(leaseTimer);

    irt->deleteRoute(route);
    ie->getIpv4Address().set(inet::Ipv4Address().getInt());
    ie->getIpv4Netmask().set(inet::Ipv4Address::ALLONES_ADDRESS.getInt());
}

void C2WDHCPClient::initClient()
{
    EV_INFO << "Starting DHCP configuration process." << std::endl;

    cancelEvent(timerT1);
    cancelEvent(timerT2);
    cancelEvent(timerTo);
    cancelEvent(leaseTimer);

    sendDiscover();
    scheduleTimerTO(WAIT_OFFER);
    clientState = SELECTING;
}

void C2WDHCPClient::initRebootedClient()
{
     sendRequest();
     scheduleTimerTO(WAIT_ACK);
     clientState = REBOOTING;
}

void C2WDHCPClient::handleDHCPMessage(inet::DhcpMessage * msg)
{
    ASSERT(isOperational && ie != NULL);

    if (msg->getOp() != inet::BOOTREPLY)
    {
        EV_WARN << "Client received a non-inet::BOOTREPLY message, dropping." << std::endl;
        return;
    }

    if (msg->getXid() != xid)
    {
        EV_WARN << "Message transaction ID is not valid, dropping." << std::endl;
        return;
    }

    inet::DhcpMessageType messageType = static_cast<inet::DhcpMessageType>(msg->getOptions().getMessageType());
    switch (clientState)
    {
        case INIT:
            EV_WARN << getAndCheckMessageTypeName(messageType) << " message arrived in INIT state. In this state, client does not wait for any message at all, dropping." << std::endl;
            break;
        case SELECTING:
            if (messageType == inet::DHCPOFFER)
            {
                EV_INFO << "inet::DHCPOFFER message arrived in SELECTING state with IP address: " << msg->getYiaddr() << "." << std::endl;
                scheduleTimerTO(WAIT_ACK);
                clientState = REQUESTING;
                recordOffer(msg);
                sendRequest(); // we accept the first offer
            }
            else
                EV_WARN << "Client is in SELECTING and the arriving packet is not a inet::DHCPOFFER, dropping." << std::endl;
            break;
        case REQUESTING:
            if (messageType == inet::DHCPOFFER)
            {
                EV_WARN << "We don't accept DHCPOFFERs in REQUESTING state, dropping." << std::endl; // remains in REQUESTING
            }
            else if (messageType == inet::DHCPACK)
            {
                EV_INFO << "inet::DHCPACK message arrived in REQUESTING state. The requested IP address is available in the server's pool of addresses." << std::endl;
                handleDHCPACK(msg);
                clientState = BOUND;
            }
            else if (messageType == inet::DHCPNAK)
            {
                EV_INFO << "inet::DHCPNAK message arrived in REQUESTING state. Restarting the configuration process." << std::endl;
                initClient();
            }
            else
            {
                EV_WARN << getAndCheckMessageTypeName(messageType) << " message arrived in REQUESTING state. In this state, client does not expect messages of this type, dropping." << std::endl;
            }
            break;
        case BOUND:
            EV_DETAIL << "We are in BOUND, discard all DHCP messages." << std::endl; // remain in BOUND
            break;
        case RENEWING:
            if (messageType == inet::DHCPACK)
            {
                handleDHCPACK(msg);
                EV_INFO << "inet::DHCPACK message arrived in RENEWING state. The renewing process was successful." << std::endl;
                clientState = BOUND;
            }
            else if (messageType == inet::DHCPNAK)
            {
                EV_INFO << "inet::DHCPNAK message arrived in RENEWING state. The renewing process was unsuccessful. Restarting the DHCP configuration process." << std::endl;
                unboundLease(); // halt network (remove address)
                initClient();
            }
            else
            {
                EV_WARN << getAndCheckMessageTypeName(messageType) << " message arrived in RENEWING state. In this state, client does not expect messages of this type, dropping." << std::endl;
            }
            break;
        case REBINDING:
            if (messageType == inet::DHCPNAK)
            {
                EV_INFO << "DHPCNAK message arrived in REBINDING state. The rebinding process was unsuccessful. Restarting the DHCP configuration process." << std::endl;
                unboundLease(); // halt network (remove address)
                initClient();
            }
            else if (messageType == inet::DHCPACK)
            {
                handleDHCPACK(msg);
                EV_INFO << "inet::DHCPACK message arrived in REBINDING state. The rebinding process was successful." << std::endl;
                clientState = BOUND;
            }
            else
            {
                EV_WARN << getAndCheckMessageTypeName(messageType) << " message arrived in REBINDING state. In this state, client does not expect messages of this type, dropping." << std::endl;
            }
            break;
        case REBOOTING:
            if (messageType == inet::DHCPACK)
            {
                handleDHCPACK(msg);
                EV_INFO << "inet::DHCPACK message arrived in REBOOTING state. Initialization with known IP address was successful." << std::endl;
                clientState = BOUND;
            }
            else if (messageType == inet::DHCPNAK)
            {
                EV_INFO << "inet::DHCPNAK message arrived in REBOOTING. Initialization with known IP address was unsuccessful." << std::endl;
                initClient();
            }
            else
            {
                EV_WARN << getAndCheckMessageTypeName(messageType) << " message arrived in REBOOTING state. In this state, client does not expect messages of this type, dropping." << std::endl;
            }
            break;
        default:
            throw omnetpp::cRuntimeError("Unknown or invalid client state %d",clientState);
    }
}

void C2WDHCPClient::receiveChangeNotification(int category, const omnetpp::cObject *details)
{
    Enter_Method_Silent();
    inet::printSignalBanner(category, details, details);

    // host associated. link is up. change the state to init.
    if (category == inet::l2AssociatedSignal)
    {
        inet::InterfaceEntry *associatedIE = NULL;
        if (details)
        {
            omnetpp::cObject *detailsAux = const_cast<omnetpp::cObject*>(details);
            associatedIE = dynamic_cast<inet::InterfaceEntry*>(detailsAux);
        }
        if (associatedIE && ie == associatedIE)
        {
            EV_INFO << "Interface associated, starting DHCP." << std::endl;
            initClient();
        }
    }
    else if (category == inet::interfaceDeletedSignal)
    {
        if (isOperational)
            throw omnetpp::cRuntimeError("Reacting to interface deletions is not implemented in this module");
    }
}

void C2WDHCPClient::sendRequest()
{
    // setting the xid
    xid = intuniform(0, RAND_MAX); // generating a new xid for each transmission

    inet::DhcpMessage * request = new inet::DhcpMessage();
    request->setOp(inet::BOOTREQUEST);
    request->setHtype(1); // ethernet
    request->setHlen(6); // hardware Address length (6 octets)
    request->setHops(0);
    request->setXid(xid); // transaction id
    request->setSecs(0); // 0 seconds from transaction started
    request->setBroadcast(false); // unicast
    request->setYiaddr(inet::Ipv4Address()); // no 'your IP' addr
    request->setGiaddr(inet::Ipv4Address()); // no DHCP Gateway Agents
    request->setChaddr(macAddress); // my mac address;
    request->setSname(""); // no server name given
    request->setFile(""); // no file given
    request->getOptionsForUpdate().setMessageType(inet::DHCPREQUEST);
    request->getOptionsForUpdate().setClientIdentifier(macAddress);

    // set the parameters to request
    request->getOptionsForUpdate().setParameterRequestListArraySize(4);
    request->getOptionsForUpdate().setParameterRequestList(0,inet::SUBNET_MASK);
    request->getOptionsForUpdate().setParameterRequestList(1,inet::ROUTER);
    request->getOptionsForUpdate().setParameterRequestList(2,inet::DNS);
    request->getOptionsForUpdate().setParameterRequestList(3,inet::NTP_SRV);

    inet::Ptr<inet::DhcpMessage> requestPtr(request);
    inet::Packet *dhcpPacket = new inet::Packet("DHCPREQUEST", requestPtr);
    dhcpPacket->setByteLength(280); // DHCP request packet size

    // RFC 4.3.6 Table 4
    if (clientState == INIT_REBOOT)
    {
        request->getOptionsForUpdate().setRequestedIp(lease->ip);
        request->setCiaddr(inet::Ipv4Address()); // zero
        EV_INFO << "Sending inet::DHCPREQUEST asking for IP " << lease->ip << " via broadcast." << std::endl;
        sendToUDP(dhcpPacket, clientPort, inet::Ipv4Address::ALLONES_ADDRESS, serverPort);
    }
    else if (clientState == REQUESTING)
    {
        request->getOptionsForUpdate().setServerIdentifier(lease->serverId);
        request->getOptionsForUpdate().setRequestedIp(lease->ip);
        request->setCiaddr(inet::Ipv4Address()); // zero
        EV_INFO << "Sending inet::DHCPREQUEST asking for IP " << lease->ip << " via broadcast." << std::endl;
        sendToUDP(dhcpPacket, clientPort, inet::Ipv4Address::ALLONES_ADDRESS, serverPort);
    }
    else if (clientState == RENEWING)
    {
        request->setCiaddr(lease->ip); // the client IP
        EV_INFO << "Sending inet::DHCPREQUEST extending lease for IP " << lease->ip << " via unicast to " << lease->serverId << "." << std::endl;
        sendToUDP(dhcpPacket, clientPort, lease->serverId, serverPort);
    }
    else if (clientState == REBINDING)
    {
        request->setCiaddr(lease->ip); // the client IP
        EV_INFO << "Sending inet::DHCPREQUEST renewing the IP " << lease->ip << " via broadcast." << std::endl;
        sendToUDP(dhcpPacket, clientPort, inet::Ipv4Address::ALLONES_ADDRESS, serverPort);
    }
    else
        delete dhcpPacket;
        throw omnetpp::cRuntimeError("Invalid state");
}

void C2WDHCPClient::sendDiscover()
{
    // setting the xid
    xid = intuniform(0, RAND_MAX);
    //std::cout << xid << std::endl;
    inet::DhcpMessage* discover = new inet::DhcpMessage();
    discover->setOp(inet::BOOTREQUEST);
    discover->setChunkLength(inet::units::values::b(280 * 8)); // DHCP Discover packet size;
    discover->setHtype(1); // ethernet
    discover->setHlen(6); // hardware Address lenght (6 octets)
    discover->setHops(0);
    discover->setXid(xid); // transaction id
    discover->setSecs(0); // 0 seconds from transaction started
    discover->setBroadcast(false); // unicast
    discover->setChaddr(macAddress); // my mac address
    discover->setSname(""); // no server name given
    discover->setFile(""); // no file given
    discover->getOptionsForUpdate().setMessageType(inet::DHCPDISCOVER);
    discover->getOptionsForUpdate().setClientIdentifier(macAddress);
    discover->getOptionsForUpdate().setRequestedIp(inet::Ipv4Address());

    // set the parameters to request
    discover->getOptionsForUpdate().setParameterRequestListArraySize(4);
    discover->getOptionsForUpdate().setParameterRequestList(0,inet::SUBNET_MASK);
    discover->getOptionsForUpdate().setParameterRequestList(1,inet::ROUTER);
    discover->getOptionsForUpdate().setParameterRequestList(2,inet::DNS);
    discover->getOptionsForUpdate().setParameterRequestList(3,inet::NTP_SRV);

    inet::Ptr<inet::DhcpMessage> discoverPtr(discover);
    inet::Packet *dhcpPacket = new inet::Packet("DHCPDISCOVER", discoverPtr);

    EV_INFO << "Sending DHCPDISCOVER." << std::endl;
    sendToUDP(dhcpPacket, clientPort, inet::Ipv4Address::ALLONES_ADDRESS, serverPort);
}

void C2WDHCPClient::sendDecline(inet::Ipv4Address declinedIp)
{
    xid = intuniform(0, RAND_MAX);
    inet::DhcpMessage * decline = new inet::DhcpMessage();
    decline->setOp(inet::BOOTREQUEST);
    decline->setChunkLength(inet::units::values::b(280 * 8)); // DHCPDECLINE packet size
    decline->setHtype(1); // ethernet
    decline->setHlen(6); // hardware Address length (6 octets)
    decline->setHops(0);
    decline->setXid(xid); // transaction id
    decline->setSecs(0); // 0 seconds from transaction started
    decline->setBroadcast(false); // unicast
    decline->setChaddr(macAddress); // my MAC address
    decline->setSname(""); // no server name given
    decline->setFile(""); // no file given
    decline->getOptionsForUpdate().setMessageType(inet::DHCPDECLINE);
    decline->getOptionsForUpdate().setRequestedIp(declinedIp);
    EV_INFO << "Sending DHCPDECLINE." << std::endl;

    inet::Ptr<inet::DhcpMessage> declinePtr(decline);
    inet::Packet *dhcpPacket = new inet::Packet("DHCPDECLINE", declinePtr);

    sendToUDP(dhcpPacket, clientPort, inet::Ipv4Address::ALLONES_ADDRESS, serverPort);
}

void C2WDHCPClient::handleDHCPACK(inet::DhcpMessage * msg)
{
    recordLease(msg);
    cancelEvent(timerTo);
    scheduleTimerT1();
    scheduleTimerT2();
    bindLease();
}

void C2WDHCPClient::scheduleTimerTO(TimerType type)
{
    // cancel the previous timeout
    cancelEvent(timerTo);
    timerTo->setKind(type);
    scheduleAt(omnetpp::simTime() + responseTimeout, timerTo);
}

void C2WDHCPClient::scheduleTimerT1()
{
    // cancel the previous T1
    cancelEvent(timerT1);
    scheduleAt(omnetpp::simTime() + (lease->renewalTime), timerT1); // RFC 2131 4.4.5
}

void C2WDHCPClient::scheduleTimerT2()
{
    // cancel the previous T2
    cancelEvent(timerT2);
    scheduleAt(omnetpp::simTime() + (lease->rebindTime), timerT2); // RFC 2131 4.4.5
}

void C2WDHCPClient::sendToUDP(inet::Packet *msg, int srcPort, const inet::L3Address& destAddr, int destPort)
{
    EV_INFO << "Sending packet " << msg << std::endl;
    socket.sendTo(msg, destAddr, destPort);
}

void C2WDHCPClient::openSocket()
{
    socket.setOutputGate(gate("udpOut"));
    // socket.bind(clientPort);
    socket.bind(ipv4Address, clientPort);

    socket.setBroadcast(true);
    EV_INFO << "DHCP server bound to port " << serverPort << "." << std::endl;
}

void C2WDHCPClient::startApp()
{
    omnetpp::simtime_t start = std::max(startTime, omnetpp::simTime());
    ie = chooseInterface();
    scheduleAt(start, startTimer);
}

void C2WDHCPClient::stopApp()
{
    cancelEvent(timerT1);
    cancelEvent(timerT2);
    cancelEvent(timerTo);
    cancelEvent(leaseTimer);
    cancelEvent(startTimer);

    // TODO: Client should send DHCPRELEASE to the server. However, the correct operation
    // of DHCP does not depend on the transmission of DHCPRELEASE messages.
    // TODO: socket.close();
}

bool C2WDHCPClient::handleOperationStage(inet::LifecycleOperation *operation, inet::IDoneCallback *doneCallback)
{
    Enter_Method_Silent();
    if (dynamic_cast<inet::ModuleStartOperation *>(operation))
    {
        if (operation->getCurrentStage() == inet::ModuleStartOperation::STAGE_APPLICATION_LAYER) {
            startApp();
            isOperational = true;
        }
    }
    else if (dynamic_cast<inet::ModuleStopOperation *>(operation))
    {
        if (operation->getCurrentStage() == inet::ModuleStopOperation::STAGE_APPLICATION_LAYER) {
            stopApp();
            isOperational = false;
            ie = NULL;
        }
    }
    else if (dynamic_cast<inet::ModuleCrashOperation *>(operation))
    {
        if (operation->getCurrentStage() == inet::ModuleCrashOperation::STAGE_CRASH) {
            stopApp();
            isOperational = false;
            ie = NULL;
        }
    }
    else
        throw omnetpp::cRuntimeError("Unsupported lifecycle operation '%s'", operation->getClassName());
    return true;
}
