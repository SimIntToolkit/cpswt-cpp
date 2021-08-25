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

#include <algorithm>

#include "C2WDHCPServer.h"

#include <inet/transportlayer/contract/udp/UdpControlInfo_m.h>
#include <inet/networklayer/common/L3AddressResolver.h>
#include <inet/networklayer/common/InterfaceTable.h>
#include <inet/networklayer/ipv4/Ipv4InterfaceData.h>
#include <inet/common/lifecycle/NodeStatus.h>
//#include "NodeOperations.h"
//#include "NotificationBoard.h"
//#include "NotifierConsts.h"

Define_Module(C2WDHCPServer);

C2WDHCPServer::C2WDHCPServer()
{
    ie = NULL;
    nb = NULL;
    startTimer = NULL;
}

C2WDHCPServer::~C2WDHCPServer()
{
    cancelAndDelete(startTimer);
}

void C2WDHCPServer::initialize(int stage)
{
    if (stage == 0)
    {
        startTimer = new omnetpp::cMessage("Start DHCP server",START_DHCP);
        startTime = par("startTime");
    }
    else if (stage == 3)
    {
        numSent = 0;
        numReceived = 0;
        WATCH(numSent);
        WATCH(numReceived);
        WATCH_MAP(leased);

        subnetMask = inet::Ipv4Address(par("subnetMask").stringValue());
        gateway = inet::Ipv4Address(par("gateway").stringValue());
        ipAddressStart = inet::Ipv4Address(par("ipAddressStart").stringValue());
        maxNumOfClients = par("maxNumClients");
        leaseTime = par("leaseTime");

        // DHCP UDP ports
        clientPort = 68; // client
        serverPort = 67; // server

        cModule *host = getContainingNode(this);
        nb = omnetpp::check_and_cast<omnetpp::cModule*>(getModuleByPath(par("notificationBoardPath")));
        nb->subscribe(inet::interfaceDeletedSignal, this);

        inet::NodeStatus *nodeStatus = dynamic_cast<inet::NodeStatus *>(host->getSubmodule("status"));
        isOperational = (!nodeStatus) || nodeStatus->getState() == inet::NodeStatus::UP;

        if (isOperational)
            startApp();


        // IPAddress to bind to the server port
        this->ipv4Address = this->ie->getIpv4Address();
    }
}

void C2WDHCPServer::openSocket()
{
    if (!ie)
        throw inet::cRuntimeError("Interface to listen on does not exist");  // may have been deleted

    socket.setOutputGate(gate("udpOut"));
    // socket.bind(serverPort);
    socket.bind(this->ipv4Address, serverPort);
    socket.setBroadcast(true);
    EV_INFO << "DHCP server bound to port " << serverPort << std::endl;
}

void C2WDHCPServer::receiveChangeNotification(int category, const omnetpp::cObject *details)
{
    Enter_Method_Silent();

    if (category == inet::interfaceDeletedSignal)
    {
        if (isOperational)
        {
            const inet::InterfaceEntry *nie = omnetpp::check_and_cast<const inet::InterfaceEntry*>(details);
            if (ie == nie)
                throw inet::cRuntimeError("Reacting to interface deletions is not implemented in this module");
        }
    }
    else
        throw inet::cRuntimeError("Unaccepted notification category: %d", category);
}

inet::InterfaceEntry *C2WDHCPServer::chooseInterface()
{
    inet::IInterfaceTable* ift = omnetpp::check_and_cast<inet::IInterfaceTable*>(getModuleByPath(par("interfaceTablePath")));
    const char *interfaceName = par("interface");
    inet::InterfaceEntry *ie = NULL;

    if (strlen(interfaceName) > 0)
    {
        ie = ift->findInterfaceByName(interfaceName);
        if (ie == NULL)
            throw inet::cRuntimeError("Interface \"%s\" does not exist", interfaceName);
    }
    else
    {
        // there should be exactly one non-loopback interface that we want to serve DHCP requests on
        for (int i = 0; i < ift->getNumInterfaces(); i++) {
            inet::InterfaceEntry *current = ift->getInterface(i);
            if (!current->isLoopback()) {
                if (ie)
                    throw inet::cRuntimeError("Multiple non-loopback interfaces found, please select explicitly which one you want to serve DHCP requests on");
                ie = current;
            }
        }
        if (!ie)
            throw inet::cRuntimeError("No non-loopback interface found to be configured via DHCP");
    }

    return ie;
}

void C2WDHCPServer::handleMessage(omnetpp::cMessage *msg)
{
    inet::Packet *dhcpPacket = dynamic_cast<inet::Packet *>(msg);
    if (msg->isSelfMessage())
    {
        handleSelfMessages(msg);
    }
    else if (dhcpPacket)
        processDHCPMessage(dhcpPacket);
    else
    {
        // note: unknown packets are likely ICMP errors in response to DHCP messages we sent out; just ignore them
        EV_WARN << "Unknown packet '" << msg->getName() << "', discarding it." << std::endl;
        delete msg;
    }
}

void C2WDHCPServer::handleSelfMessages(omnetpp::cMessage * msg)
{
    if (msg->getKind() == START_DHCP)
    {
        openSocket();
    }
    else
        throw inet::cRuntimeError("Unknown selfmessage type!");
}

void C2WDHCPServer::processDHCPMessage(inet::Packet *packet)
{
    ASSERT(isOperational && ie != NULL);

    inet::Ptr<const inet::Chunk> chunkPtr = packet->peekAll();
    const inet::Chunk *chunk = chunkPtr.get();
    const inet::DhcpMessage *dhcpMessage = dynamic_cast<const inet::DhcpMessage *>(chunk);

    // check that the packet arrived on the interface we are supposed to serve
    inet::InterfaceEntry *ctrl = omnetpp::check_and_cast<inet::InterfaceEntry *>(packet->removeControlInfo());
    int inputInterfaceId = ctrl->getInterfaceId();
    delete ctrl;
    if (inputInterfaceId != ie->getInterfaceId())
    {
        EV_WARN << "DHCP message arrived on a different interface, dropping\n";
        delete packet;
        return;
    }

    // check the OP code
    if (dhcpMessage->getOp() == inet::BOOTREQUEST)
    {
        int messageType = dhcpMessage->getOptions().getMessageType();

        if (messageType == inet::DHCPDISCOVER) // RFC 2131, 4.3.1
        {
            EV_INFO << "inet::DHCPDISCOVER arrived. Handling it." << std::endl;

            inet::DhcpLease* lease = getLeaseByMac(dhcpMessage->getChaddr());
            if (!lease)
            {
                // MAC not registered, create offering a new lease to the client
                lease = getAvailableLease(dhcpMessage->getOptions().getRequestedIp(), dhcpMessage->getChaddr());
                if (lease != NULL)
                {
                    // std::cout << "MAC: " << packet->getChaddr() << " ----> IP: " << lease->ip << std::endl;
                    lease->mac = dhcpMessage->getChaddr();
                    lease->xid = dhcpMessage->getXid();
                    //lease->parameterRequestList = dhcpMessage->getOptions().get(PARAM_LIST); TODO: !!
                    lease->leased = true; // TODO
                    sendOffer(lease);
                }
                else
                    EV_ERROR << "No lease available. Ignoring discover." << std::endl;
            }
            else
            {
                // MAC already exist, offering the same lease
                lease->xid = dhcpMessage->getXid();
                //lease->parameterRequestList = dhcpMessage->getOptions().get(PARAM_LIST); // TODO: !!
                sendOffer(lease);
            }

        }
        else if (messageType == inet::DHCPREQUEST) // RFC 2131, 4.3.2
        {
            EV_INFO << "inet::DHCPREQUEST arrived. Handling it." << std::endl;

            // check if the request was in response of an offering
            if (dhcpMessage->getOptions().getServerIdentifier() == ie->getIpv4Address())
            {
                // the REQUEST is in response to an offering (because SERVER_ID is filled)
                // otherwise the msg is a request to extend an existing lease (e. g. INIT-REBOOT)

                inet::DhcpLease* lease = getLeaseByMac(dhcpMessage->getChaddr());
                if (lease != NULL)
                {
                    if (lease->ip != dhcpMessage->getOptions().getRequestedIp())
                    {
                        EV_ERROR << "The 'requested IP address' must be filled in with the 'yiaddr' value from the chosen DHCPOFFER." << std::endl;
                        sendNAK(dhcpMessage);
                    }
                    else
                    {
                        EV_INFO << "From now " << lease->ip << " is leased to " << lease->mac << "." << std::endl;
                        lease->xid = dhcpMessage->getXid();
                        lease->leaseTime = leaseTime;
                        lease->leased = true;

                        // TODO: final check before ACK (it is not necessary but recommended)
                        sendACK(lease, dhcpMessage);

                        // TODO: update the display string to inform how many clients are assigned
                    }
                }
                else
                {
                    EV_ERROR << "There is no available lease for " << dhcpMessage->getChaddr() << ". Probably, the client missed to send inet::DHCPDISCOVER before inet::DHCPREQUEST." << std::endl;
                    sendNAK(dhcpMessage);
                }
            }
            else
            {
                if (dhcpMessage->getCiaddr().isUnspecified())  // init-reboot
                {
                    // std::cout << "init-reboot" << std::endl;
                    inet::Ipv4Address requestedAddress = dhcpMessage->getOptions().getRequestedIp();
                    DHCPLeased::iterator it = leased.find(requestedAddress);
                    if (it == leased.end())
                    {
                        // if DHCP server has no record of the requested IP, then it must remain silent
                        // and may output a warning to the network admin
                        EV_WARN << "DHCP server has no record of IP " << requestedAddress << "." << std::endl;
                    }
                    else if (inet::Ipv4Address::maskedAddrAreEqual(requestedAddress,it->second.ip,subnetMask)) // on the same network
                    {
                        inet::DhcpLease * lease = &it->second;
                        EV_INFO << "Initialization with known IP address (INIT-REBOOT) " << lease->ip <<  " on " << lease->mac <<  " was successful." << std::endl;
                        lease->xid = dhcpMessage->getXid();
                        lease->leaseTime = leaseTime;
                        lease->leased = true;

                        // TODO: final check before ACK (it is not necessary but recommended)
                        sendACK(lease, dhcpMessage);
                    }
                    else
                    {
                        EV_ERROR << "The requested IP address is incorrect, or is on the wrong network." << std::endl;
                        sendNAK(dhcpMessage);
                    }
                }
                else // renewing or rebinding: in this case ciaddr must be filled in with client's IP address
                {
                    DHCPLeased::iterator it = leased.find(dhcpMessage->getCiaddr());
                    inet::DhcpLease * lease = &it->second;
                    if (it != leased.end())
                    {
                        EV_INFO << "Request for renewal/rebinding IP " << lease->ip << " to " << lease->mac << "." << std::endl;
                        lease->xid = dhcpMessage->getXid();
                        lease->leaseTime = leaseTime;
                        lease->leased = true;

                        // unicast ACK to ciaddr
                        sendACK(lease, dhcpMessage);
                    }
                    else
                    {
                        EV_ERROR << "Renewal/rebinding process failed: requested IP address " << dhcpMessage->getCiaddr() << " not found in the server's database!" << std::endl;
                        sendNAK(dhcpMessage);
                    }
                }
            }
        }
        else
            EV_WARN << "inet::BOOTREQUEST arrived, but DHCP message type is unknown. Dropping it." << std::endl;
    }
    else
    {
        EV_WARN << "Message opcode is unknown. This DHCP server only handles inet::BOOTREQUEST messages. Dropping it." << std::endl;
    }

    EV_DEBUG << "Deleting " << packet << "." << std::endl;
    delete packet;

    numReceived++;
}

void C2WDHCPServer::sendNAK(const inet::DhcpMessage *msg)
{
    // EV_INFO << "Sending NAK to " << lease->mac << "." << std::endl;
    inet::DhcpMessage * nak = new inet::DhcpMessage();
    nak->setOp(inet::BOOTREPLY);
    nak->setHtype(1); // ethernet
    nak->setHlen(6); // hardware address length (6 octets)
    nak->setHops(0);
    nak->setXid(msg->getXid()); // transaction id from client
    nak->setSecs(0); // 0 seconds from transaction started.
    nak->setBroadcast(msg->getBroadcast());
    nak->setGiaddr(msg->getGiaddr()); // next server IP
    nak->setChaddr(msg->getChaddr());
    nak->getOptionsForUpdate().setServerIdentifier(ie->getIpv4Address());
    nak->getOptionsForUpdate().setMessageType(inet::DHCPNAK);

    inet::Ptr<inet::DhcpMessage> nakPtr(nak);
    inet::Packet *dhcpPacket = new inet::Packet("DHCPNAK", nakPtr);
    dhcpPacket->setByteLength(280); // DHCP request packet size

    sendToUDP(dhcpPacket, serverPort, inet::Ipv4Address::ALLONES_ADDRESS, clientPort);
}

void C2WDHCPServer::sendACK(inet::DhcpLease* lease, const inet::DhcpMessage * dhcpMessage)
{
    EV_INFO << "Sending the ACK to " << lease->mac << "." << std::endl;

    inet::DhcpMessage* ack = new inet::DhcpMessage();
    ack->setOp(inet::BOOTREPLY);
    ack->setHtype(1); // ethernet
    ack->setHlen(6); // hardware address length (6 octets)
    ack->setHops(0);
    ack->setXid(lease->xid); // transaction id;
    ack->setSecs(0); // 0 seconds from transaction started
    ack->setBroadcast(false);
    ack->setCiaddr(lease->ip); // client IP addr.
    ack->setYiaddr(lease->ip); // client IP addr.

    ack->setChaddr(lease->mac); // client MAC address
    ack->setSname(""); // no server name given
    ack->setFile(""); // no file given
    ack->getOptionsForUpdate().setMessageType(inet::DHCPACK);

    // add the lease options
    ack->getOptionsForUpdate().setSubnetMask(lease->subnetMask);
    ack->getOptionsForUpdate().setRenewalTime(leaseTime * 0.5); // RFC 4.4.5
    ack->getOptionsForUpdate().setRebindingTime(leaseTime * 0.875);
    ack->getOptionsForUpdate().setLeaseTime(leaseTime);
    ack->getOptionsForUpdate().setRouterArraySize(1);
    ack->getOptionsForUpdate().setRouter(0,lease->gateway);
    ack->getOptionsForUpdate().setDnsArraySize(1);
    ack->getOptionsForUpdate().setDns(0,lease->dns);

    // add the server ID as the RFC says
    ack->getOptionsForUpdate().setServerIdentifier(ie->getIpv4Address());

    // register the lease time
    lease->leaseTime = omnetpp::simTime();

    inet::Ptr<inet::DhcpMessage> ackPtr(ack);
    inet::Packet *dhcpPacket = new inet::Packet("DHCPACK", ackPtr);
    dhcpPacket->setByteLength(308); // DHCP request packet size

    if (dhcpMessage->getGiaddr().isUnspecified() && !dhcpMessage->getCiaddr().isUnspecified())
        sendToUDP(dhcpPacket, serverPort, dhcpMessage->getCiaddr(), clientPort);
    else
        sendToUDP(dhcpPacket, serverPort, lease->ip.makeBroadcastAddress(lease->ip.getNetworkMask()), clientPort);
}

void C2WDHCPServer::sendOffer(inet::DhcpLease* lease)
{

    EV_INFO << "Offering " << *lease << std::endl;

    inet::DhcpMessage * offer = new inet::DhcpMessage();
    offer->setOp(inet::BOOTREPLY);
    offer->setHtype(1); // ethernet
    offer->setHlen(6); // hardware address lenght (6 octets)
    offer->setHops(0);
    offer->setXid(lease->xid); // transaction id
    offer->setSecs(0); // 0 seconds from transaction started
    offer->setBroadcast(false); // unicast

    offer->setYiaddr(lease->ip); // ip offered.
    offer->setGiaddr(lease->gateway); // next server ip

    offer->setChaddr(lease->mac); // client mac address
    offer->setSname(""); // no server name given
    offer->setFile(""); // no file given
    offer->getOptionsForUpdate().setMessageType(inet::DHCPOFFER);

    // add the offer options
    offer->getOptionsForUpdate().setSubnetMask(lease->subnetMask);
    offer->getOptionsForUpdate().setRenewalTime(leaseTime * 0.5); // RFC 4.4.5
    offer->getOptionsForUpdate().setRebindingTime(leaseTime * 0.875);
    offer->getOptionsForUpdate().setLeaseTime(leaseTime);
    offer->getOptionsForUpdate().setRouterArraySize(1);
    offer->getOptionsForUpdate().setRouter(0,lease->gateway);
    offer->getOptionsForUpdate().setDnsArraySize(1);
    offer->getOptionsForUpdate().setDns(0,lease->dns);

    // add the server_id as the RFC says
    offer->getOptionsForUpdate().setServerIdentifier(ie->getIpv4Address());

    // register the offering time // todo: ?
    lease->leaseTime = omnetpp::simTime();

    inet::Ptr<inet::DhcpMessage> offerPtr(offer);
    inet::Packet *dhcpPacket = new inet::Packet("DHCPOFFER", offerPtr);
    dhcpPacket->setByteLength(308); // DHCP request packet size

    sendToUDP(dhcpPacket, serverPort, lease->ip.makeBroadcastAddress(lease->ip.getNetworkMask()), clientPort);
}

inet::DhcpLease* C2WDHCPServer::getLeaseByMac(inet::MacAddress mac)
{
    for (DHCPLeased::iterator it = leased.begin(); it != leased.end(); it++)
    {
        // lease exist
        if (it->second.mac == mac)
        {
            EV_DETAIL << "Found lease for MAC " << mac << "." << std::endl;
            return (&(it->second));
        }
    }
    EV_DETAIL << "Lease not found for MAC " << mac << "." << std::endl;

    // lease does not exist
    return NULL;
}

inet::DhcpLease* C2WDHCPServer::getAvailableLease(inet::Ipv4Address requestedAddress, const inet::MacAddress& clientMAC)
{
    int beginAddr = ipAddressStart.getInt(); // the first address that we might use

    // try to allocate the requested address if that address is valid and not already allocated
    if (!requestedAddress.isUnspecified()) // valid
    {
        if (leased.find(requestedAddress) != leased.end() && !leased[requestedAddress].leased) // not already leased (allocated)
            return &leased[requestedAddress];

        // lease does not exist, create it
        leased[requestedAddress] = inet::DhcpLease();
        leased[requestedAddress].ip = requestedAddress;
        leased[requestedAddress].gateway = gateway;
        leased[requestedAddress].subnetMask = subnetMask;

        return &leased[requestedAddress];
    }

    // allocate new address from server's pool of available addresses
    for (unsigned int i = 0; i < maxNumOfClients; i++)
    {
        inet::Ipv4Address ip(beginAddr + i);
        if (leased.find(ip) != leased.end())
        {
            // lease exists but not allocated (e.g. expired or released)
            if (!leased[ip].leased)
                return (&(leased[ip]));
        }
        else
        {
            // there is no expired lease so we create a new one
            leased[ip] = inet::DhcpLease();
            leased[ip].ip = ip;
            leased[ip].gateway = gateway;
            leased[ip].subnetMask = subnetMask;
            return (&(leased[ip]));
        }
    }
    // no lease available
    return NULL;
}

void C2WDHCPServer::sendToUDP(inet::Packet *msg, int srcPort, const inet::L3Address& destAddr, int destPort)
{
    EV_INFO << "Sending packet: " << msg << "." << std::endl;
    numSent++;
    socket.sendTo(msg, destAddr, destPort);
}

void C2WDHCPServer::startApp()
{
    omnetpp::simtime_t start = std::max(startTime, omnetpp::simTime());
    ie = chooseInterface();
    scheduleAt(start, startTimer);
}

void C2WDHCPServer::stopApp()
{
    leased.clear();
    ie = NULL;
    cancelEvent(startTimer);
    // socket.close(); TODO:
}

bool C2WDHCPServer::handleOperationStage(inet::LifecycleOperation *operation, inet::IDoneCallback *doneCallback)
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
        }
    }
    else if (dynamic_cast<inet::ModuleCrashOperation *>(operation))
    {
        if (operation->getCurrentStage() == inet::ModuleCrashOperation::STAGE_CRASH) {
            stopApp();
            isOperational = false;
        }
    }
    else
        throw inet::cRuntimeError("Unsupported lifecycle operation '%s'", operation->getClassName());
    return true;
}
