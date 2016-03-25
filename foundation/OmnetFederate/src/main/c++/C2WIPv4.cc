//
// Copyright (C) 2004 Andras Varga
// Copyright (C) 2014 OpenSim Ltd.
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

#include <stdlib.h>
#include <string.h>

#include "C2WIPv4.h"

#include "ARPPacket_m.h"
#include "IARPCache.h"
#include "ICMPMessage_m.h"
#include "Ieee802Ctrl_m.h"
#include "IRoutingTable.h"
#include "InterfaceTableAccess.h"
#include "IPSocket.h"
#include "IPv4ControlInfo.h"
#include "IPv4Datagram.h"
#include "IPv4InterfaceData.h"
#include "NodeOperations.h"
#include "NodeStatus.h"
#include "NotificationBoard.h"
#include "UDPPacket.h"
#include "TCPSegment.h"
#include "UDPPacket_m.h"
#include "FilterAttackMsg_m.h"
#include "NodeAttackMsg_m.h"
#include "NetworkAttackMsg_m.h"
#include "OutOfOrderAttackMsg_m.h"
#include "OutOfOrderMsg_m.h"
#include "RecordReplayAttackMsg_m.h"
#include "ReplayAttackMsg_m.h"
#include "ReplayMsg_m.h"
#include "SnifferAttackMsg_m.h"
#include "AddRouteEntryMsg_m.h"
#include "DropRouteEntryMsg_m.h"
#include "DelayNodeAttackMsg_m.h"
#include "DelayedMsg_m.h"
#include "IPFirewallMsg_m.h"

Define_Module(C2WIPv4);

//TODO TRANSLATE
// a multicast cimek eseten hianyoznak bizonyos NetFilter hook-ok
// a local interface-k hasznalata eseten szinten hianyozhatnak bizonyos NetFilter hook-ok

#define NEWFRAGMENT
simsignal_t C2WIPv4::completedARPResolutionSignal = registerSignal("completedARPResolution");
simsignal_t C2WIPv4::failedARPResolutionSignal = registerSignal("failedARPResolution");
simsignal_t C2WIPv4::iPv4PromiscousPacket = registerSignal("iPv4PromiscousPacket");

void C2WIPv4::initialize(int stage)
{
    if (stage == 0)
    {
        _hostFullName = getParentModule()->getParentModule()->getFullPath();
        HLAInterface::get_InstancePtr()->registerIPModule(_hostFullName, this);

        QueueBase::initialize();

        ift = InterfaceTableAccess().get();
        rt = check_and_cast<IRoutingTable *>(getModuleByPath(par("routingTableModule")));
        nb = NotificationBoardAccess().getIfExists(); // needed only for multicast forwarding

        arpInGate = gate("arpIn");
        arpOutGate = gate("arpOut");
        cModule *arpModule = arpOutGate->getPathEndGate()->getOwnerModule();
        arp = check_and_cast<IARPCache *>(arpModule);
        transportInGateBaseId = gateBaseId("transportIn");
        queueOutGateBaseId = gateBaseId("queueOut");

        defaultTimeToLive = par("timeToLive");
        defaultMCTimeToLive = par("multicastTimeToLive");
        fragmentTimeoutTime = par("fragmentTimeout");
        forceBroadcast = par("forceBroadcast");
        useProxyARP = par("useProxyARP");

        curFragmentId = 0;
        lastCheckTime = 0;
        fragbuf.init(icmpAccess.get());

        numMulticast = numLocalDeliver = numDropped = numUnroutable = numForwarded = 0;

        // NetFilter:
        hooks.clear();
        queuedDatagramsForHooks.clear();

        pendingPackets.clear();
        arpModule->subscribe(completedARPResolutionSignal, this);
        arpModule->subscribe(failedARPResolutionSignal, this);

        WATCH (numMulticast);
        WATCH (numLocalDeliver);
        WATCH (numDropped);
        WATCH (numUnroutable);
        WATCH (numForwarded);
        WATCH_MAP(pendingPackets);
        isDsr = false;
    }
    else if (stage == 1)
    {
        isUp = isNodeUp();
    }
    else if (stage == 4)
    {
        nb->subscribe(this, NF_INTERFACE_IPv4CONFIG_CHANGED);
    }
    else if (stage == 5)
    {
        recordNetworkInformation();
    }
}

void C2WIPv4::updateDisplayString()
{
    char buf[80] = "";
    if (numForwarded>0) sprintf(buf+strlen(buf), "fwd:%d ", numForwarded);
    if (numLocalDeliver>0) sprintf(buf+strlen(buf), "up:%d ", numLocalDeliver);
    if (numMulticast>0) sprintf(buf+strlen(buf), "mcast:%d ", numMulticast);
    if (numDropped>0) sprintf(buf+strlen(buf), "DROP:%d ", numDropped);
    if (numUnroutable>0) sprintf(buf+strlen(buf), "UNROUTABLE:%d ", numUnroutable);
    getDisplayString().setTagArg("t", 0, buf);
}

void C2WIPv4::handleMessage(cMessage *msg)
{
    if (msg->getKind() == IP_C_REGISTER_PROTOCOL) {
        IPRegisterProtocolCommand * command = check_and_cast<IPRegisterProtocolCommand *>(msg->getControlInfo());
        mapping.addProtocolMapping(command->getProtocol(), msg->getArrivalGate()->getIndex());

        if (command->getProtocol() == IP_PROT_MANET)
        {
            int gateindex = mapping.getOutputGateForProtocol(IP_PROT_MANET);
            cGate *manetgate = gate("transportOut", gateindex)->getPathEndGate();
            cModule *destmod = manetgate->getOwnerModule();
            cProperties *props = destmod->getProperties();
            isDsr = props && props->getAsBool("isDsr");
        }
        delete msg;
    }
    else if (!msg->isSelfMessage() && msg->getArrivalGate()->isName("arpIn"))
        endService(PK(msg));
    else
    {
        NodeAttackMsg *nodeAttackMsg = dynamic_cast<NodeAttackMsg *>(msg);
        if (nodeAttackMsg != 0) {
            _nodeAttack = nodeAttackMsg->getAttackInProgress();
            cancelAndDelete(msg);
            return;
        }

        DelayNodeAttackMsg *delayNodeAttackMsg =
                dynamic_cast<DelayNodeAttackMsg *>(msg);
        if (delayNodeAttackMsg != 0) {
            _nodeDelayed = delayNodeAttackMsg->getAttackInProgress();
            _nodeDelayMean = delayNodeAttackMsg->getDelayMean();
            _nodeDelayStdDev = delayNodeAttackMsg->getDelayStdDev();
            cancelAndDelete(msg);
            return;
        }

        DelayedMsg *delayedMsg = dynamic_cast<DelayedMsg *>(msg);
        if (delayedMsg != 0) {
            DatagramData &datagramData = *delayedMsg->getDatagramDataSP();
            continueRouteUnicastPacket(datagramData.getIPDatagram(),
                    datagramData.getFromInterfaceEntry(),
                    datagramData.getDestInterfaceEntry(),
                    datagramData.getNextHopAddr());
            return;
        }

        SnifferAttackMsg *snifferAttackMsg = dynamic_cast<SnifferAttackMsg *>(msg);
        if (snifferAttackMsg != 0) {
            std::string hostName = snifferAttackMsg->getListenerNodeFullPath();
            std::string interface = snifferAttackMsg->getListenerInterface();
            if (snifferAttackMsg->getListen()) {
                addListener(
                        HLAInterface::get_InstancePtr()->getIPAddress(hostName,
                                interface));
            } else {
                deleteListener(
                        HLAInterface::get_InstancePtr()->getIPAddress(hostName,
                                interface));
            }
            cancelAndDelete(msg);
            return;
        }

        FilterAttackMsg *filterAttackMsg = dynamic_cast<FilterAttackMsg *>(msg);
        if (filterAttackMsg != 0) {
            if (filterAttackMsg->getEnable()) {
                addFilter(filterAttackMsg->getSourceNetworkAddress(),
                        filterAttackMsg->getDestinationNetworkAddress());
            } else {
                deleteFilter(filterAttackMsg->getSourceNetworkAddress(),
                        filterAttackMsg->getDestinationNetworkAddress());
            }
            cancelAndDelete(msg);
            return;
        }

        IPFirewallMsg *ipFirewallMsg = dynamic_cast<IPFirewallMsg *>(msg);
        if (ipFirewallMsg != 0) {
            if (ipFirewallMsg->getEnable()) {
                addFilter(ipFirewallMsg->getSourceNetworkAddress(),
                        ipFirewallMsg->getDestinationNetworkAddress());
            } else {
                deleteFilter(ipFirewallMsg->getSourceNetworkAddress(),
                        ipFirewallMsg->getDestinationNetworkAddress());
            }
            cancelAndDelete(msg);
            return;
        }

        NetworkAttackMsg *networkAttackMsg = dynamic_cast<NetworkAttackMsg *>(msg);
        if (networkAttackMsg != 0) {
            NetworkAddress networkAddress(networkAttackMsg->getNetworkAddress());
            NetworkAddressInterfaceNameMap::iterator nimItr =
                    _networkAddressInterfaceNameMap.find(networkAddress);
            if (nimItr != _networkAddressInterfaceNameMap.end()) {
                if (networkAttackMsg->getEnable()) {
                    _attackedInterfaceSet.insert(nimItr->second);
                    _hasNetworkAttack = true;
                } else {
                    _attackedInterfaceSet.erase(nimItr->second);
                    if (_attackedInterfaceSet.empty()) {
                        _hasNetworkAttack = false;
                    }
                }
            }
            cancelAndDelete(msg);
            return;
        }

        RecordReplayAttackMsg *recordReplayAttackMsg =
                dynamic_cast<RecordReplayAttackMsg *>(msg);
        if (recordReplayAttackMsg != 0) {

            ReplayBufferSP replayBufferSP = getSerialReplayBufferSP(
                    recordReplayAttackMsg->getSourceNetworkAddress(),
                    recordReplayAttackMsg->getDestinationNetworkAddress());

            if (recordReplayAttackMsg->getEnable()) {
                replayBufferSP->reset(recordReplayAttackMsg->getRecordDuration());
            } else {
                replayBufferSP->setPlaying(false);
                removeSerialReplayBufferSP(
                        recordReplayAttackMsg->getSourceNetworkAddress(),
                        recordReplayAttackMsg->getDestinationNetworkAddress());
            }
            cancelAndDelete(msg);
            return;
        }

        ReplayAttackMsg *replayAttackMsg = dynamic_cast<ReplayAttackMsg *>(msg);
        if (replayAttackMsg != 0) {

            ReplayBufferSP replayBufferSP = getSerialReplayBufferSP(
                    replayAttackMsg->getSourceNetworkAddress(),
                    replayAttackMsg->getDestinationNetworkAddress());

            if (replayAttackMsg->getPlay()) {
                replayBufferSP->setPlaying(true);

                ReplayMsg *replayMsg = new ReplayMsg;
                replayMsg->setReplayBufferSP(replayBufferSP);

                scheduleAt(simTime() + replayBufferSP->getNextTimeOffset().dbl(),
                        replayMsg);
            } else {
                replayBufferSP->setPlaying(false);
            }

            cancelAndDelete(msg);
            return;
        }

        ReplayMsg *replayMsg = dynamic_cast<ReplayMsg *>(msg);
        if (replayMsg != 0) {
            ReplayBufferSP replayBufferSP = replayMsg->getReplayBufferSP();
            if (!replayBufferSP->getPlaying()) {
                cancelAndDelete(msg);
                return;
            }

            DatagramData &datagramData = *replayBufferSP->getSerial();

            IPv4Datagram *ipDatagram = datagramData.getIPDatagram()->dup();
            cPacket *transportPacket = ipDatagram->decapsulate();
            cPacket *applicationPacket = transportPacket->decapsulate();
            InteractionMsg *interactionMsg =
                    dynamic_cast<InteractionMsg *>(applicationPacket);
            if (interactionMsg != 0) {
                interactionMsg->setMessageNo(HLAInterface::getUniqueNo());
            }
            transportPacket->encapsulate(applicationPacket);
            ipDatagram->encapsulate(transportPacket);
            continueRouteUnicastPacket(ipDatagram, datagramData.getFromInterfaceEntry(),
                    datagramData.getDestInterfaceEntry(), datagramData.getNextHopAddr());

            double nextTimeOffset = replayBufferSP->getNextTimeOffset().dbl();
            if (nextTimeOffset < 0) {
                std::cerr << "ERROR:  IPv4:  ReplayAttack:  Host \""
                        << _hostFullName
                        << "\":  Attempt to get time offset from empty ReplayBuffer"
                        << std::endl;
                cancelAndDelete(msg);
                return;
            }

            scheduleAt(simTime() + nextTimeOffset, msg);
            return;
        }

        OutOfOrderAttackMsg *outOfOrderAttackMsg =
                dynamic_cast<OutOfOrderAttackMsg *>(msg);
        if (outOfOrderAttackMsg != 0) {

            ReplayBufferSP replayBufferSP = getRandomReplayBufferSP(
                    outOfOrderAttackMsg->getSourceNetworkAddress(),
                    outOfOrderAttackMsg->getDestinationNetworkAddress());

            if (outOfOrderAttackMsg->getPlay()) {
                replayBufferSP->reset(outOfOrderAttackMsg->getRecordDuration());
                replayBufferSP->setPlayingRandom(true);
                OutOfOrderMsg *outOfOrderMsg = new OutOfOrderMsg;
                outOfOrderMsg->setReplayBufferSP(replayBufferSP);

                scheduleAt(simTime() + replayBufferSP->getRecordDuration(),
                        outOfOrderMsg);
            } else {
                replayBufferSP->setPlayingRandom(false);
                removeRandomReplayBufferSP(
                        outOfOrderAttackMsg->getSourceNetworkAddress(),
                        outOfOrderAttackMsg->getDestinationNetworkAddress());
            }

            cancelAndDelete(msg);
            return;
        }

        OutOfOrderMsg *outOfOrderMsg = dynamic_cast<OutOfOrderMsg *>(msg);
        if (outOfOrderMsg != 0) {
            ReplayBufferSP replayBufferSP = outOfOrderMsg->getReplayBufferSP();
            if (!replayBufferSP->getPlayingRandom()) {
                cancelAndDelete(msg);
                return;
            }

            DatagramDataSP datagramDataSP = replayBufferSP->getRandom();

            if (datagramDataSP == 0) {
                cancelAndDelete(msg);
                return;
            }
            continueRouteUnicastPacket(datagramDataSP->getIPDatagram(),
                    datagramDataSP->getFromInterfaceEntry(),
                    datagramDataSP->getDestInterfaceEntry(),
                    datagramDataSP->getNextHopAddr());

            double nextTimeOffset = replayBufferSP->getNextTimeOffset().dbl();
            if (nextTimeOffset < 0) {
                scheduleAt(simTime() + replayBufferSP->getRecordDuration(), msg);
            } else {
                scheduleAt(simTime() + nextTimeOffset, msg);
            }

            return;
        }

        AddRouteEntryMsg *addRouteEntryMsg = dynamic_cast<AddRouteEntryMsg *>(msg);
        if (addRouteEntryMsg != 0) {
            HLAInterface::RouteEntrySP routeEntrySP =
                    addRouteEntryMsg->getRouteEntrySP();
            IPv4Route *ipRoute = new IPv4Route;
            ipRoute->setDestination(
                    IPv4Address(
                            routeEntrySP->get_networkAddress().getNetworkIPAddress()));
            ipRoute->setNetmask(
                    IPv4Address(routeEntrySP->get_networkAddress().getNetMask()));
            int gatewayAddress =
                    routeEntrySP->get_gatewayAddress().getNetworkIPAddress();
            ipRoute->setGateway(IPv4Address(gatewayAddress));
            ipRoute->setInterface(
                    ift->getInterfaceByName(
                            routeEntrySP->get_interfaceEntry().c_str()));
            ipRoute->setAdminDist(
                    gatewayAddress != 0 ? IPv4Route::dStatic : IPv4Route::dDirectlyConnected);
            rt->addRoute(ipRoute);
            return;
        }

        DropRouteEntryMsg *dropRouteEntryMsg =
                dynamic_cast<DropRouteEntryMsg *>(msg);
        if (dropRouteEntryMsg != 0) {
            HLAInterface::RouteEntrySP routeEntrySP =
                    dropRouteEntryMsg->getRouteEntrySP();
            IPv4Route *ipRoute = new IPv4Route;
            ipRoute->setDestination(
                    IPv4Address(
                            routeEntrySP->get_networkAddress().getNetworkIPAddress()));
            ipRoute->setNetmask(
                    IPv4Address(routeEntrySP->get_networkAddress().getNetMask()));
            int gatewayAddress =
                    routeEntrySP->get_gatewayAddress().getNetworkIPAddress();
            ipRoute->setGateway(IPv4Address(gatewayAddress));
            ipRoute->setInterface(
                    ift->getInterfaceByName(
                            routeEntrySP->get_interfaceEntry().c_str()));
            ipRoute->setAdminDist(
                    gatewayAddress != 0 ? IPv4Route::dStatic : IPv4Route::dDirectlyConnected);
            rt->deleteRoute(ipRoute);
            return;
        }

        QueueBase::handleMessage(msg);
    }
}

void C2WIPv4::endService(cPacket *packet)
{
    if (!isUp) {
        EV << "IPv4 is down -- discarding message\n";
        delete packet;
        return;
    }
    if (mayHaveListeners(iPv4PromiscousPacket))
        emit(iPv4PromiscousPacket, packet);
    if (packet->getArrivalGate()->isName("transportIn")) //TODO packet->getArrivalGate()->getBaseId() == transportInGateBaseId
    {
        handlePacketFromHL(packet);
    }
    else if (packet->getArrivalGate() == arpInGate)
    {
        handlePacketFromARP(packet);
    }
    else // from network
    {
        const InterfaceEntry *fromIE = getSourceInterfaceFrom(packet);
        if (dynamic_cast<ARPPacket *>(packet))
            handleIncomingARPPacket((ARPPacket *)packet, fromIE);
        else if (dynamic_cast<IPv4Datagram *>(packet))
            handleIncomingDatagram((IPv4Datagram *)packet, fromIE);
        else
            throw cRuntimeError(packet, "Unexpected packet type");
    }

    if (ev.isGUI())
        updateDisplayString();
}

const InterfaceEntry *C2WIPv4::getSourceInterfaceFrom(cPacket *packet)
{
    cGate *g = packet->getArrivalGate();
    return g ? ift->getInterfaceByNetworkLayerGateIndex(g->getIndex()) : NULL;
}

void C2WIPv4::handleIncomingDatagram(IPv4Datagram *datagram, const InterfaceEntry *fromIE)
{
    ASSERT(datagram);
    ASSERT(fromIE);

    //
    // "Prerouting"
    //

    // check for header biterror
    if (datagram->hasBitError())
    {
        // probability of bit error in header = size of header / size of total message
        // (ignore bit error if in payload)
        double relativeHeaderLength = datagram->getHeaderLength() / (double)datagram->getByteLength();
        if (dblrand() <= relativeHeaderLength)
        {
            EV << "bit error found, sending ICMP_PARAMETER_PROBLEM\n";
            icmpAccess.get()->sendErrorMessage(datagram, fromIE->getInterfaceId(), ICMP_PARAMETER_PROBLEM, 0);
            return;
        }
    }
// check input drop rules
    const IPv4RouteRule *rule=checkInputRule(datagram);
    if (rule && rule->getRule()==IPv4RouteRule::DROP)
    {
        EV << "\n Drop datagram with source "<< datagram->getSrcAddress() <<
                " and  destination "<< datagram->getDestAddress() << " by rule "<<rule->info() << "\n";
        numDropped++;
        delete datagram;
        return;
    }
    else if (rule && rule->getRule()==IPv4RouteRule::ACCEPT)
    {
        InterfaceEntry *destIE = rule->getInterface();
        EV << "Received datagram `" << datagram->getName() << "' with dest=" << datagram->getDestAddress()  << " processing by rule accept \n";
        // hop counter decrement; FIXME but not if it will be locally delivered
        datagram->setTimeToLive(datagram->getTimeToLive()-1);
        if (!datagram->getDestAddress().isMulticast())
            preroutingFinish(datagram, fromIE, destIE, IPv4Address::UNSPECIFIED_ADDRESS);
        else
            forwardMulticastPacket(datagram, fromIE);
        return;
    }
// end check

    EV << "Received datagram `" << datagram->getName() << "' with dest=" << datagram->getDestAddress() << "\n";

    const InterfaceEntry *destIE = NULL;
    IPv4Address nextHop(IPv4Address::UNSPECIFIED_ADDRESS);
    if (datagramPreRoutingHook(datagram, fromIE, destIE, nextHop) == INetfilter::IHook::ACCEPT)
        preroutingFinish(datagram, fromIE, destIE, nextHop);
}

void C2WIPv4::preroutingFinish(IPv4Datagram *datagram, const InterfaceEntry *fromIE, const InterfaceEntry *destIE, IPv4Address nextHopAddr)
{
    IPv4Address &destAddr = datagram->getDestAddress();

    // remove control info
    delete datagram->removeControlInfo();

    // route packet

    if (fromIE->isLoopback())
    {
        reassembleAndDeliver(datagram);
    }
    else if (destAddr.isMulticast())
    {
        // check for local delivery
        // Note: multicast routers will receive IGMP datagrams even if their interface is not joined to the group
        if (fromIE->ipv4Data()->isMemberOfMulticastGroup(destAddr) ||
                (rt->isMulticastForwardingEnabled() && datagram->getTransportProtocol() == IP_PROT_IGMP))
            reassembleAndDeliver(datagram->dup());
        else
            EV << "Skip local delivery of multicast datagram (input interface not in multicast group)\n";

        // don't forward if IP forwarding is off, or if dest address is link-scope
        if (!rt->isIPForwardingEnabled() || destAddr.isLinkLocalMulticast())
        {
            EV << "Skip forwarding of multicast datagram (packet is link-local or forwarding disabled)\n";
            delete datagram;
        }
        else if (datagram->getTimeToLive() == 0)
        {
            EV << "Skip forwarding of multicast datagram (TTL reached 0)\n";
            delete datagram;
        }
        else
            forwardMulticastPacket(datagram, fromIE);
    }
    else
    {
        const InterfaceEntry *broadcastIE = NULL;

        // check for local delivery; we must accept also packets coming from the interfaces that
        // do not yet have an IP address assigned. This happens during DHCP requests.
        if (rt->isLocalAddress(destAddr) || fromIE->ipv4Data()->getIPAddress().isUnspecified())
        {
            reassembleAndDeliver(datagram);
        }
        else if (destAddr.isLimitedBroadcastAddress() || (broadcastIE=rt->findInterfaceByLocalBroadcastAddress(destAddr)))
        {
            // broadcast datagram on the target subnet if we are a router
            if (broadcastIE && fromIE != broadcastIE && rt->isIPForwardingEnabled())
                fragmentPostRouting(datagram->dup(), broadcastIE, IPv4Address::ALLONES_ADDRESS);

            EV << "Broadcast received\n";
            reassembleAndDeliver(datagram);
        }
        else if (!rt->isIPForwardingEnabled())
        {
            EV << "forwarding off, dropping packet\n";
            numDropped++;
            delete datagram;
        }
        else
            routeUnicastPacket(datagram, fromIE, destIE, nextHopAddr);
    }
}

void C2WIPv4::handleIncomingARPPacket(ARPPacket *packet, const InterfaceEntry *fromIE)
{
    // give it to the ARP module
    Ieee802Ctrl *ctrl = check_and_cast<Ieee802Ctrl*>(packet->getControlInfo());
    ctrl->setInterfaceId(fromIE->getInterfaceId());
    send(packet, arpOutGate);
}

void C2WIPv4::handleIncomingICMP(ICMPMessage *packet)
{
    switch (packet->getType())
    {
        case ICMP_REDIRECT: // TODO implement redirect handling
        case ICMP_DESTINATION_UNREACHABLE:
        case ICMP_TIME_EXCEEDED:
        case ICMP_PARAMETER_PROBLEM: {
            // ICMP errors are delivered to the appropriate higher layer protocol
            IPv4Datagram *bogusPacket = check_and_cast<IPv4Datagram *>(packet->getEncapsulatedPacket());
            int protocol = bogusPacket->getTransportProtocol();
            int gateindex = mapping.getOutputGateForProtocol(protocol);
            send(packet, "transportOut", gateindex);
            break;
        }
        default: {
            // all others are delivered to ICMP: ICMP_ECHO_REQUEST, ICMP_ECHO_REPLY,
            // ICMP_TIMESTAMP_REQUEST, ICMP_TIMESTAMP_REPLY, etc.
            int gateindex = mapping.getOutputGateForProtocol(IP_PROT_ICMP);
            send(packet, "transportOut", gateindex);
            break;
        }
    }
}

void C2WIPv4::handlePacketFromHL(cPacket *packet)
{
    // if no interface exists, do not send datagram
    if (ift->getNumInterfaces() == 0)
    {
        EV << "No interfaces exist, dropping packet\n";
        numDropped++;
        delete packet;
        return;
    }

    // encapsulate and send
    IPv4Datagram *datagram = dynamic_cast<IPv4Datagram *>(packet);
    IPv4ControlInfo *controlInfo = NULL;
    //FIXME dubious code, remove? how can the HL tell IP whether it wants tunneling or forwarding?? --Andras
    if (!datagram) // if HL sends an IPv4Datagram, route the packet
    {
        // encapsulate
        controlInfo = check_and_cast<IPv4ControlInfo*>(packet->removeControlInfo());
        datagram = encapsulate(packet, controlInfo);
    }

    // extract requested interface and next hop
    const InterfaceEntry *destIE = controlInfo ? const_cast<const InterfaceEntry *>(ift->getInterfaceById(controlInfo->getInterfaceId())) : NULL;

    if (controlInfo)
        datagram->setControlInfo(controlInfo);    //FIXME ne rakjuk bele a cntrInfot!!!!! de kell :( kulonben a hook queue-ban elveszik a multicastloop flag

    // TODO:
    IPv4Address nextHopAddr(IPv4Address::UNSPECIFIED_ADDRESS);
    if (datagramLocalOutHook(datagram, destIE, nextHopAddr) == INetfilter::IHook::ACCEPT)
        datagramLocalOut(datagram, destIE, nextHopAddr);
}

void C2WIPv4::handlePacketFromARP(cPacket *packet)
{
    // send out packet on the appropriate interface
    Ieee802Ctrl *ctrl = check_and_cast<Ieee802Ctrl*>(packet->getControlInfo());
    InterfaceEntry *destIE = ift->getInterfaceById(ctrl->getInterfaceId());
    sendPacketToNIC(packet, destIE);
}

void C2WIPv4::datagramLocalOut(IPv4Datagram* datagram, const InterfaceEntry* destIE, IPv4Address requestedNextHopAddress)
{
    IPv4ControlInfo *controlInfo = dynamic_cast<IPv4ControlInfo*>(datagram->removeControlInfo());
    bool multicastLoop = true;
    if (controlInfo != NULL)
    {
        multicastLoop = controlInfo->getMulticastLoop();
        delete controlInfo;
    }

    // send
    IPv4Address &destAddr = datagram->getDestAddress();

    EV << "Sending datagram `" << datagram->getName() << "' with dest=" << destAddr << "\n";

    if (datagram->getDestAddress().isMulticast())
    {
        destIE = determineOutgoingInterfaceForMulticastDatagram(datagram, destIE);

        // loop back a copy
        if (multicastLoop && (!destIE || !destIE->isLoopback()))
        {
            const InterfaceEntry *loopbackIF = ift->getFirstLoopbackInterface();
            if (loopbackIF)
                fragmentPostRouting(datagram->dup(), loopbackIF, destAddr);
        }

        if (destIE)
        {
            numMulticast++;
            fragmentPostRouting(datagram, destIE, destAddr);
        }
        else
        {
            EV << "No multicast interface, packet dropped\n";
            numUnroutable++;
            delete datagram;
        }
    }
    else // unicast and broadcast
    {
        // check for local delivery
        if (rt->isLocalAddress(destAddr))
        {
            EV << "local delivery\n";
            if (destIE && !destIE->isLoopback())
            {
                EV << "datagram destination address is local, ignoring destination interface specified in the control info\n";
                destIE = NULL;
            }
            if (!destIE)
                destIE = ift->getFirstLoopbackInterface();
            ASSERT(destIE);
            routeUnicastPacket(datagram, NULL, destIE, destAddr);
        }
        else if (destAddr.isLimitedBroadcastAddress() || rt->isLocalBroadcastAddress(destAddr))
            routeLocalBroadcastPacket(datagram, destIE);
        else
            routeUnicastPacket(datagram, NULL, destIE, requestedNextHopAddress);
    }
}

/* Choose the outgoing interface for the muticast datagram:
 *   1. use the interface specified by MULTICAST_IF socket option (received in the control info)
 *   2. lookup the destination address in the routing table
 *   3. if no route, choose the interface according to the source address
 *   4. or if the source address is unspecified, choose the first MULTICAST interface
 */
const InterfaceEntry *C2WIPv4::determineOutgoingInterfaceForMulticastDatagram(IPv4Datagram *datagram, const InterfaceEntry *multicastIFOption)
{
    const InterfaceEntry *ie = NULL;
    if (multicastIFOption)
    {
        ie = multicastIFOption;
        EV << "multicast packet routed by socket option via output interface " << ie->getName() << "\n";
    }
    if (!ie)
    {
        IPv4Route *route = rt->findBestMatchingRoute(datagram->getDestAddress());
        if (route)
            ie = route->getInterface();
        if (ie)
            EV << "multicast packet routed by routing table via output interface " << ie->getName() << "\n";
    }
    if (!ie)
    {
        ie = rt->getInterfaceByAddress(datagram->getSrcAddress());
        if (ie)
            EV << "multicast packet routed by source address via output interface " << ie->getName() << "\n";
    }
    if (!ie)
    {
        ie = ift->getFirstMulticastInterface();
        if (ie)
            EV << "multicast packet routed via the first multicast interface " << ie->getName() << "\n";
    }
    return ie;
}


void C2WIPv4::routeUnicastPacket(IPv4Datagram *datagram, const InterfaceEntry *fromIE, const InterfaceEntry *destIE, IPv4Address requestedNextHopAddress)
{
    IPv4Address destAddr = datagram->getDestAddress();
    IPv4Address srcAddr = datagram->getSrcAddress();
    if (srcAddr.isUnspecified())
        srcAddr = destAddr;

    // TBD add option handling code here

    //
    // IF HOST BEING ATTACKED, DROP DATAGRAM
    //
    if (_nodeAttack) {
        std::cout << "Host \"" << _hostFullName
                << "\":  under host attack -- dropping datagram." << std::endl;
        delete datagram;
        return;
    }

    //
    // IF HOST IS UNDER DELAY ATTACK, DELAY DATAGRAM
    //
    if (_nodeDelayed) {
        DelayedMsg *delayedMsg = new DelayedMsg;
        DatagramDataSP datagramDataSP(
                new DatagramData(datagram->dup(), fromIE, destIE,
                        requestedNextHopAddress));
        delayedMsg->setDatagramDataSP(datagramDataSP);
        double delay = truncnormal(_nodeDelayMean, _nodeDelayStdDev);
        scheduleAt(simTime() + delay, delayedMsg);
        std::cout << "Host \"" << _hostFullName << "\":  delaying datagram."
                << std::endl;
        delete datagram;
        return;
    }

    //
    // SNIFFER ATTACK
    //
    if (_hasListeners) {
        for (IPAddressSet::iterator iasItr = _listenerIPAddressSet.begin();
                iasItr != _listenerIPAddressSet.end(); ++iasItr) {
            IPv4Datagram *datagramCopy = datagram->dup();
            const IPv4Address &snifferIPAddress(*iasItr);
            std::cout << "Host \"" << _hostFullName
                    << "\":  sending sniffed datagram to " << snifferIPAddress
                    << std::endl;
            datagramCopy->setDestAddress(snifferIPAddress);
            continueRouteUnicastPacket(datagramCopy, (const InterfaceEntry*) 0,
                    (const InterfaceEntry *) 0, IPv4Address());
        }
    }

    //
    // FILTER ATTACK
    //
    if (_hasFilters && isFiltered(srcAddr, destAddr)) {
        std::cout << "Host \"" << _hostFullName
                << "\":  filtering datagram with (srcAddr,destAddr) = ("
                << srcAddr << "," << destAddr << ")." << std::endl;
        delete datagram;
        return;
    }

    //
    // REPLAY ATTACK
    //
    if (_hasSerialReplayBufferSPMap) {
        ReplayBufferSPList replayBufferSPList = getSerialReplayBufferSPList(
                srcAddr.getInt(), destAddr.getInt());

        bool _replayPlaying = false;
        for (ReplayBufferSPList::iterator rblItr = replayBufferSPList.begin();
                rblItr != replayBufferSPList.end(); ++rblItr) {

            ReplayBuffer &replayBuffer = **rblItr;
            if (replayBuffer.getPlaying()) {
                _replayPlaying = true;
            } else {
                std::cout << "Host \"" << _hostFullName
                        << "\":  recording datagram (" << srcAddr << ","
                        << destAddr << ") for replay attack." << std::endl;
                replayBuffer.addIPDatagramSerial(datagram->dup(), fromIE,
                        destIE, requestedNextHopAddress);
            }
        }
        if (_replayPlaying) {
            std::cout << "Host \"" << _hostFullName
                    << "\":  replay in progress, dropping datagram (" << srcAddr
                    << "," << destAddr << ")" << std::endl;
            delete datagram;
            return;
        }
    }

    //
    // OUT-OF-ORDER-PACKETS ATTACK
    //
    if (_hasRandomReplayBufferSPMap) {
        ReplayBufferSPList replayBufferSPList = getRandomReplayBufferSPList(
                srcAddr.getInt(), destAddr.getInt());

        if (!replayBufferSPList.empty()) {

            for (ReplayBufferSPList::iterator rblItr =
                    replayBufferSPList.begin();
                    rblItr != replayBufferSPList.end(); ++rblItr) {
                std::cout << "Host \"" << _hostFullName
                        << "\":  delaying datagram (" << srcAddr << ","
                        << destAddr << ") for out-of-order packet attack."
                        << std::endl;
                ReplayBuffer &replayBuffer = **rblItr;
                replayBuffer.addIPDatagramRandom(datagram->dup(), fromIE,
                        destIE, requestedNextHopAddress);
            }

            delete datagram;
            return;
        }
    }

    continueRouteUnicastPacket(datagram, fromIE, destIE, requestedNextHopAddress);
}

void C2WIPv4::continueRouteUnicastPacket(IPv4Datagram *datagram, const InterfaceEntry *fromIE, const InterfaceEntry *destIE, IPv4Address requestedNextHopAddress)
{
    IPv4Address destAddr = datagram->getDestAddress();

    EV << "Routing datagram `" << datagram->getName() << "' with dest=" << destAddr << ": ";
    const IPv4RouteRule *rule = checkOutputRule(datagram,destIE);
    if (rule && rule->getRule() == IPv4RouteRule::DROP)
    {
        EV << "\n Drop datagram with source "<< datagram->getSrcAddress() <<
                " and destination "<< datagram->getDestAddress() << " by rule "<<rule->info() << "\n";
        numDropped++;
        delete datagram;
        return;
    }
    IPv4Address nextHopAddr;
    // if output port was explicitly requested, use that, otherwise use IPv4 routing
    if (destIE)
    {
        EV << "using manually specified output interface " << destIE->getName() << "\n";
        // and nextHopAddr remains unspecified
        if (!requestedNextHopAddress.isUnspecified())
            nextHopAddr = requestedNextHopAddress;
         // special case ICMP reply
        else if (destIE->isBroadcast())
        {
            // if the interface is broadcast we must search the next hop
            const IPv4Route *re = rt->findBestMatchingRoute(destAddr);
            if (re && re->getInterface() == destIE)
                nextHopAddr = re->getGateway();
        }
    }
    else
    {
        // use IPv4 routing (lookup in routing table)
        const IPv4Route *re = rt->findBestMatchingRoute(destAddr);

        //
        // NETWORK ATTACK
        //
        if (_hasNetworkAttack && re != NULL) {
            // CHECK IF PACKET IS BEING ROUTED INTO OR THROUGH AN INTERFACE TO AN ATTACKED NETWORK
            std::string interfaceName(re->getInterfaceName());
            if (_attackedInterfaceSet.find(interfaceName)
                    != _attackedInterfaceSet.end()) {
                std::cout << "Host \"" << _hostFullName
                        << "\":  datagram being sent to attacked interface \""
                        << interfaceName << "\".  Dropping datagram."
                        << std::endl;
                delete datagram;
                return;
            }
        }

        if (re)
        {
            destIE = re->getInterface();
            nextHopAddr = re->getGateway();
        }
    }

    if (!destIE) // no route found
    {
        EV << "unroutable, sending ICMP_DESTINATION_UNREACHABLE\n";
        numUnroutable++;
        icmpAccess.get()->sendErrorMessage(datagram, fromIE ? fromIE->getInterfaceId() : -1, ICMP_DESTINATION_UNREACHABLE, 0);
    }
    else // fragment and send
    {
        if (fromIE != NULL)
        {
            if (datagramForwardHook(datagram, fromIE, destIE, nextHopAddr) != INetfilter::IHook::ACCEPT)
                return;
        }

        routeUnicastPacketFinish(datagram, fromIE, destIE, nextHopAddr);
    }
}

void C2WIPv4::routeUnicastPacketFinish(IPv4Datagram *datagram, const InterfaceEntry *fromIE, const InterfaceEntry *destIE, IPv4Address nextHopAddr)
{
    EV << "output interface is " << destIE->getName() << ", next-hop address: " << nextHopAddr << "\n";
    numForwarded++;
    fragmentPostRouting(datagram, destIE, nextHopAddr);
}

void C2WIPv4::routeLocalBroadcastPacket(IPv4Datagram *datagram, const InterfaceEntry *destIE)
{
    // The destination address is 255.255.255.255 or local subnet broadcast address.
    // We always use 255.255.255.255 as nextHopAddress, because it is recognized by ARP,
    // and mapped to the broadcast MAC address.
    if (destIE!=NULL)
    {
        fragmentPostRouting(datagram, destIE, IPv4Address::ALLONES_ADDRESS);
    }
    else if (forceBroadcast)
    {
        // forward to each interface including loopback
        for (int i = 0; i<ift->getNumInterfaces(); i++)
        {
            const InterfaceEntry *ie = ift->getInterface(i);
            fragmentPostRouting(datagram->dup(), ie, IPv4Address::ALLONES_ADDRESS);
        }
        delete datagram;
    }
    else
    {
        numDropped++;
        delete datagram;
    }
}

const InterfaceEntry *C2WIPv4::getShortestPathInterfaceToSource(IPv4Datagram *datagram)
{
    return rt->getInterfaceForDestAddr(datagram->getSrcAddress());
}

void C2WIPv4::forwardMulticastPacket(IPv4Datagram *datagram, const InterfaceEntry *fromIE)
{
    ASSERT(fromIE);
    const IPv4Address &srcAddr = datagram->getSrcAddress();
    const IPv4Address &destAddr = datagram->getDestAddress();
    ASSERT(destAddr.isMulticast());
    ASSERT(!destAddr.isLinkLocalMulticast());

    EV << "Forwarding multicast datagram `" << datagram->getName() << "' with dest=" << destAddr << "\n";

    numMulticast++;

    const IPv4MulticastRoute *route = rt->findBestMatchingMulticastRoute(srcAddr, destAddr);
    if (!route)
    {
        EV << "Multicast route does not exist, try to add.\n";
        nb->fireChangeNotification(NF_IPv4_NEW_MULTICAST, datagram);

        // read new record
        route = rt->findBestMatchingMulticastRoute(srcAddr, destAddr);

        if (!route)
        {
            EV << "No route, packet dropped.\n";
            numUnroutable++;
            delete datagram;
            return;
        }
    }

    if (route->getInInterface() && fromIE != route->getInInterface()->getInterface())
    {
        EV << "Did not arrive on input interface, packet dropped.\n";
        nb->fireChangeNotification(NF_IPv4_DATA_ON_NONRPF, datagram);
        numDropped++;
        delete datagram;
    }
    // backward compatible: no parent means shortest path interface to source (RPB routing)
    else if (!route->getInInterface() && fromIE != getShortestPathInterfaceToSource(datagram))
    {
        EV << "Did not arrive on shortest path, packet dropped.\n";
        numDropped++;
        delete datagram;
    }
    else
    {
        nb->fireChangeNotification(NF_IPv4_DATA_ON_RPF, datagram); // forwarding hook

        numForwarded++;
        // copy original datagram for multiple destinations
        for (unsigned int i=0; i<route->getNumOutInterfaces(); i++)
        {
            IPv4MulticastRoute::OutInterface *outInterface = route->getOutInterface(i);
            const InterfaceEntry *destIE = outInterface->getInterface();
            if (destIE != fromIE && outInterface->isEnabled())
            {
                int ttlThreshold = destIE->ipv4Data()->getMulticastTtlThreshold();
                if (datagram->getTimeToLive() <= ttlThreshold)
                    EV << "Not forwarding to " << destIE->getName() << " (ttl treshold reached)\n";
                else if (outInterface->isLeaf() && !destIE->ipv4Data()->hasMulticastListener(destAddr))
                    EV << "Not forwarding to " << destIE->getName() << " (no listeners)\n";
                else
                {
                    EV << "Forwarding to " << destIE->getName() << "\n";
                    fragmentPostRouting(datagram->dup(), destIE, destAddr);
                }
            }
        }

        nb->fireChangeNotification(NF_IPv4_MDATA_REGISTER, datagram); // postRouting hook

        // only copies sent, delete original datagram
        delete datagram;
    }
}

#ifndef NEWFRAGMENT
void C2WIPv4::reassembleAndDeliver(IPv4Datagram *datagram)
{
    EV << "Local delivery\n";

    if (datagram->getSrcAddress().isUnspecified())
        EV << "Received datagram '" << datagram->getName() << "' without source address filled in\n";

    // reassemble the packet (if fragmented)
    if (datagram->getFragmentOffset()!=0 || datagram->getMoreFragments())
    {
        EV << "Datagram fragment: offset=" << datagram->getFragmentOffset()
           << ", MORE=" << (datagram->getMoreFragments() ? "true" : "false") << ".\n";

        // erase timed out fragments in fragmentation buffer; check every 10 seconds max
        if (simTime() >= lastCheckTime + 10)
        {
            lastCheckTime = simTime();
            fragbuf.purgeStaleFragments(simTime()-fragmentTimeoutTime);
        }

        datagram = fragbuf.addFragment(datagram, simTime());
        if (!datagram)
        {
            EV << "No complete datagram yet.\n";
            return;
        }
        EV << "This fragment completes the datagram.\n";
    }

    if (datagramLocalInHook(datagram, getSourceInterfaceFrom(datagram)) != INetfilter::IHook::ACCEPT)
    {
        return;
    }

    reassembleAndDeliverFinish(datagram);
}
#endif

void C2WIPv4::reassembleAndDeliverFinish(IPv4Datagram *datagram)
{
    // decapsulate and send on appropriate output gate
    int protocol = datagram->getTransportProtocol();

    if (protocol==IP_PROT_ICMP)
    {
        // incoming ICMP packets are handled specially
        handleIncomingICMP(check_and_cast<ICMPMessage *>(decapsulate(datagram)));
        numLocalDeliver++;
    }
    else if (protocol==IP_PROT_IP)
    {
        // tunnelled IP packets are handled separately
        send(decapsulate(datagram), "preRoutingOut");  //FIXME There is no "preRoutingOut" gate in the IPv4 module.
    }
    else
    {
        int gateindex = mapping.findOutputGateForProtocol(protocol);
        // check if the transportOut port are connected, otherwise discard the packet
        if (gateindex >= 0)
        {
            cGate* outGate = gate("transportOut", gateindex);
            if (outGate->isPathOK())
            {
                send(decapsulate(datagram), outGate);
                numLocalDeliver++;
                return;
            }
        }

        EV << "Transport protocol ID=" << protocol << " not connected, discarding packet\n";
        int inputInterfaceId = getSourceInterfaceFrom(datagram)->getInterfaceId();
        icmpAccess.get()->sendErrorMessage(datagram, inputInterfaceId, ICMP_DESTINATION_UNREACHABLE, ICMP_DU_PROTOCOL_UNREACHABLE);
    }
}

cPacket *C2WIPv4::decapsulate(IPv4Datagram *datagram)
{
    // decapsulate transport packet
    const InterfaceEntry *fromIE = getSourceInterfaceFrom(datagram);
    cPacket *packet = datagram->decapsulate();

    // create and fill in control info
    IPv4ControlInfo *controlInfo = new IPv4ControlInfo();
    controlInfo->setProtocol(datagram->getTransportProtocol());
    controlInfo->setSrcAddr(datagram->getSrcAddress());
    controlInfo->setDestAddr(datagram->getDestAddress());
    controlInfo->setTypeOfService(datagram->getTypeOfService());
    controlInfo->setInterfaceId(fromIE ? fromIE->getInterfaceId() : -1);
    controlInfo->setTimeToLive(datagram->getTimeToLive());

    // original IPv4 datagram might be needed in upper layers to send back ICMP error message
    controlInfo->setOrigDatagram(datagram);

    // attach control info
    packet->setControlInfo(controlInfo);

    return packet;
}

void C2WIPv4::fragmentPostRouting(IPv4Datagram *datagram, const InterfaceEntry *ie, IPv4Address nextHopAddr)
{
    if (datagramPostRoutingHook(datagram, getSourceInterfaceFrom(datagram), ie, nextHopAddr) == INetfilter::IHook::ACCEPT)
        fragmentAndSend(datagram, ie, nextHopAddr);
}

#ifndef NEWFRAGMENT
void C2WIPv4::fragmentAndSend(IPv4Datagram *datagram, const InterfaceEntry *ie, IPv4Address nextHopAddr)
{
    // fill in source address
    if (datagram->getSrcAddress().isUnspecified())
        datagram->setSrcAddress(ie->ipv4Data()->getIPAddress());

    // hop counter decrement; but not if it will be locally delivered
    if (!ie->isLoopback())
        datagram->setTimeToLive(datagram->getTimeToLive()-1);

    // hop counter check
    if (datagram->getTimeToLive() < 0)
    {
        // drop datagram, destruction responsibility in ICMP
        EV << "datagram TTL reached zero, sending ICMP_TIME_EXCEEDED\n";
        icmpAccess.get()->sendErrorMessage(datagram, -1 /*TODO*/, ICMP_TIME_EXCEEDED, 0);
        numDropped++;
        return;
    }

    int mtu = ie->getMTU();

    if (isDsr) // to avoid problems with the DSR header that could force future fragmentations
        mtu -= 30;

    // send datagram straight out if it doesn't require fragmentation (note: mtu==0 means infinite mtu)
    if (mtu == 0 || datagram->getByteLength() <= mtu)
    {
        sendDatagramToOutput(datagram, ie, nextHopAddr);
        return;
    }

    // if "don't fragment" bit is set, throw datagram away and send ICMP error message
    if (datagram->getDontFragment())
    {
        EV << "datagram larger than MTU and don't fragment bit set, sending ICMP_DESTINATION_UNREACHABLE\n";
        icmpAccess.get()->sendErrorMessage(datagram, -1 /*TODO*/, ICMP_DESTINATION_UNREACHABLE,
                ICMP_DU_FRAGMENTATION_NEEDED);
        numDropped++;
        return;
    }

    // FIXME some IP options should not be copied into each fragment, check their COPY bit
    int headerLength = datagram->getHeaderLength();
    int payloadLength = datagram->getByteLength() - headerLength;
    int fragmentLength = ((mtu - headerLength) / 8) * 8; // payload only (without header)
    int offsetBase = datagram->getFragmentOffset();
    if (fragmentLength <= 0)
        throw cRuntimeError("Cannot fragment datagram: MTU=%d too small for header size (%d bytes)", mtu, headerLength); // exception and not ICMP because this is likely a simulation configuration error, not something one wants to simulate

    int noOfFragments = (payloadLength + fragmentLength - 1) / fragmentLength;
    EV << "Breaking datagram into " << noOfFragments << " fragments\n";

    // create and send fragments
    std::string fragMsgName = datagram->getName();
    fragMsgName += "-frag";

    for (int offset=0; offset < payloadLength; offset+=fragmentLength)
    {
        bool lastFragment = (offset+fragmentLength >= payloadLength);
        // length equal to fragmentLength, except for last fragment;
        int thisFragmentLength = lastFragment ? payloadLength - offset : fragmentLength;

        // FIXME is it ok that full encapsulated packet travels in every datagram fragment?
        // should better travel in the last fragment only. Cf. with reassembly code!
        IPv4Datagram *fragment = (IPv4Datagram *) datagram->dup();
        fragment->setName(fragMsgName.c_str());

        // "more fragments" bit is unchanged in the last fragment, otherwise true
        if (!lastFragment)
            fragment->setMoreFragments(true);

        fragment->setByteLength(headerLength + thisFragmentLength);
        fragment->setFragmentOffset(offsetBase + offset);

        sendDatagramToOutput(fragment, ie, nextHopAddr);
    }

    delete datagram;
}
#endif

IPv4Datagram *C2WIPv4::encapsulate(cPacket *transportPacket, IPv4ControlInfo *controlInfo)
{
    IPv4Datagram *datagram = createIPv4Datagram(transportPacket->getName());
    datagram->setByteLength(IP_HEADER_BYTES);
    datagram->encapsulate(transportPacket);

    // set source and destination address
    IPv4Address dest = controlInfo->getDestAddr();
    datagram->setDestAddress(dest);

    IPv4Address src = controlInfo->getSrcAddr();

    // when source address was given, use it; otherwise it'll get the address
    // of the outgoing interface after routing
    if (!src.isUnspecified())
    {
        // if interface parameter does not match existing interface, do not send datagram
        if (rt->getInterfaceByAddress(src)==NULL)
            throw cRuntimeError("Wrong source address %s in (%s)%s: no interface with such address",
                      src.str().c_str(), transportPacket->getClassName(), transportPacket->getFullName());

        datagram->setSrcAddress(src);
    }

    // set other fields
    datagram->setTypeOfService(controlInfo->getTypeOfService());

    datagram->setIdentification(curFragmentId++);
    datagram->setMoreFragments(false);
    datagram->setDontFragment(controlInfo->getDontFragment());
    datagram->setFragmentOffset(0);

    short ttl;
    if (controlInfo->getTimeToLive() > 0)
        ttl = controlInfo->getTimeToLive();
    else if (datagram->getDestAddress().isLinkLocalMulticast())
        ttl = 1;
    else if (datagram->getDestAddress().isMulticast())
        ttl = defaultMCTimeToLive;
    else
        ttl = defaultTimeToLive;
    datagram->setTimeToLive(ttl);
    datagram->setTransportProtocol(controlInfo->getProtocol());

    // setting IPv4 options is currently not supported

    return datagram;
}

IPv4Datagram *C2WIPv4::createIPv4Datagram(const char *name)
{
    return new IPv4Datagram(name);
}

void C2WIPv4::sendDatagramToOutput(IPv4Datagram *datagram, const InterfaceEntry *ie, IPv4Address nextHopAddr)
{
    {
        bool isIeee802Lan = ie->isBroadcast() && !ie->getMacAddress().isUnspecified(); // we only need/can do ARP on IEEE 802 LANs
        if (!isIeee802Lan) {
            sendPacketToNIC(datagram, ie);
        }
        else {
            if (nextHopAddr.isUnspecified()) {
                if (useProxyARP) {
                    nextHopAddr = datagram->getDestAddress();
                    EV << "no next-hop address, using destination address " << nextHopAddr << " (proxy ARP)\n";
                }
                else {
                    throw cRuntimeError(datagram, "Cannot send datagram on broadcast interface: no next-hop address and Proxy ARP is disabled");
                }
            }

            MACAddress nextHopMacAddr;  // unspecified
            nextHopMacAddr = resolveNextHopMacAddress(datagram, nextHopAddr, ie);

            if (nextHopMacAddr.isUnspecified())
            {
                if (arp->deletePacket(nextHopAddr))
                    delete datagram;
                else
                {
                    pendingPackets[nextHopAddr].insert(datagram);
                    arp->startAddressResolution(nextHopAddr, ie);
                }
            }
            else
            {
                ASSERT2(pendingPackets.find(nextHopAddr) == pendingPackets.end(), "IPv4-ARP error: nextHopAddr found in ARP table, but IPv4 queue for nextHopAddr not empty");
                sendPacketToIeee802NIC(datagram, ie, nextHopMacAddr, ETHERTYPE_IPv4);
            }
        }
    }
}

void C2WIPv4::arpResolutionCompleted(IARPCache::Notification *entry)
{
    PendingPackets::iterator it = pendingPackets.find(entry->ipv4Address);
    if (it != pendingPackets.end())
    {
        cPacketQueue& packetQueue = it->second;
        EV << "ARP resolution completed for " << entry->ipv4Address << ". Sending " << packetQueue.getLength()
                << " waiting packets from the queue\n";

        while (!packetQueue.empty())
        {
            cPacket *msg = packetQueue.pop();
            EV << "Sending out queued packet " << msg << "\n";
            sendPacketToIeee802NIC(msg, entry->ie, entry->macAddress, ETHERTYPE_IPv4);
        }
        pendingPackets.erase(it);
    }
}

void C2WIPv4::arpResolutionTimedOut(IARPCache::Notification *entry)
{
    PendingPackets::iterator it = pendingPackets.find(entry->ipv4Address);
    if (it != pendingPackets.end())
    {
        cPacketQueue& packetQueue = it->second;
        EV << "ARP resolution failed for " << entry->ipv4Address << ",  dropping " << packetQueue.getLength() << " packets\n";
        packetQueue.clear();
        pendingPackets.erase(it);
    }
}

MACAddress C2WIPv4::resolveNextHopMacAddress(cPacket *packet, IPv4Address nextHopAddr, const InterfaceEntry *destIE)
{
    if (nextHopAddr.isLimitedBroadcastAddress() || nextHopAddr == destIE->ipv4Data()->getNetworkBroadcastAddress())
    {
        EV << "destination address is broadcast, sending packet to broadcast MAC address\n";
        return MACAddress::BROADCAST_ADDRESS;
    }

    if (nextHopAddr.isMulticast())
    {
        MACAddress macAddr = MACAddress::makeMulticastAddress(nextHopAddr);
        EV << "destination address is multicast, sending packet to MAC address " << macAddr << "\n";
        return macAddr;
    }

    return arp->getMACAddressFor(nextHopAddr);
}

void C2WIPv4::sendPacketToIeee802NIC(cPacket *packet, const InterfaceEntry *ie, const MACAddress& macAddress, int etherType)
{
    // remove old control info
    delete packet->removeControlInfo();

    // add control info with MAC address
    Ieee802Ctrl *controlInfo = new Ieee802Ctrl();
    controlInfo->setDest(macAddress);
    controlInfo->setEtherType(etherType);
    packet->setControlInfo(controlInfo);

    sendPacketToNIC(packet, ie);
}

void C2WIPv4::sendPacketToNIC(cPacket *packet, const InterfaceEntry *ie)
{
    EV << "Sending out packet to interface " << ie->getName() << endl;
    send(packet, queueOutGateBaseId + ie->getNetworkLayerGateIndex());
}

// NetFilter:

void C2WIPv4::registerHook(int priority, INetfilter::IHook* hook)
{
    Enter_Method("registerHook()");
    hooks.insert(std::pair<int, INetfilter::IHook*>(priority, hook));
}

void C2WIPv4::unregisterHook(int priority, INetfilter::IHook* hook)
{
    Enter_Method("unregisterHook()");
    for (HookList::iterator iter = hooks.begin(); iter != hooks.end(); iter++) {
        if ((iter->first == priority) && (iter->second == hook)) {
            hooks.erase(iter);
            return;
        }
    }
}

void C2WIPv4::dropQueuedDatagram(const IPv4Datagram* datagram)
{
    Enter_Method("dropQueuedDatagram()");
    for (DatagramQueueForHooks::iterator iter = queuedDatagramsForHooks.begin(); iter != queuedDatagramsForHooks.end(); iter++) {
        if (iter->datagram == datagram) {
            delete datagram;
            queuedDatagramsForHooks.erase(iter);
            return;
        }
    }
}

void C2WIPv4::reinjectQueuedDatagram(const IPv4Datagram* datagram)
{
    Enter_Method("reinjectDatagram()");
    for (DatagramQueueForHooks::iterator iter = queuedDatagramsForHooks.begin(); iter != queuedDatagramsForHooks.end(); iter++) {
        if (iter->datagram == datagram) {
            IPv4Datagram* datagram = iter->datagram;
            take(datagram);
            switch (iter->hookType) {
                case INetfilter::IHook::LOCALOUT:
                    datagramLocalOut(datagram, iter->outIE, iter->nextHopAddr);
                    break;
                case INetfilter::IHook::PREROUTING:
                    preroutingFinish(datagram, iter->inIE, iter->outIE, iter->nextHopAddr);
                    break;
                case INetfilter::IHook::POSTROUTING:
                    fragmentAndSend(datagram, iter->outIE, iter->nextHopAddr);
                    break;
                case INetfilter::IHook::LOCALIN:
                    reassembleAndDeliverFinish(datagram);
                    break;
                case INetfilter::IHook::FORWARD:
                    routeUnicastPacketFinish(datagram, iter->inIE, iter->outIE, iter->nextHopAddr);
                    break;
                default:
                    throw cRuntimeError("Unknown hook ID: %d", (int)(iter->hookType));
                    break;
            }
            queuedDatagramsForHooks.erase(iter);
            return;
        }
    }
}

INetfilter::IHook::Result C2WIPv4::datagramPreRoutingHook(IPv4Datagram* datagram, const InterfaceEntry* inIE, const InterfaceEntry*& outIE, IPv4Address& nextHopAddr)
{
    for (HookList::iterator iter = hooks.begin(); iter != hooks.end(); iter++) {
        IHook::Result r = iter->second->datagramPreRoutingHook(datagram, inIE, outIE, nextHopAddr);
        switch(r)
        {
            case INetfilter::IHook::ACCEPT: break;   // continue iteration
            case INetfilter::IHook::DROP:   delete datagram; return r;
            case INetfilter::IHook::QUEUE:  queuedDatagramsForHooks.push_back(QueuedDatagramForHook(datagram, inIE, outIE, nextHopAddr, INetfilter::IHook::PREROUTING)); return r;
            case INetfilter::IHook::STOLEN: return r;
            default: throw cRuntimeError("Unknown Hook::Result value: %d", (int)r);
        }
    }
    return INetfilter::IHook::ACCEPT;
}

INetfilter::IHook::Result C2WIPv4::datagramForwardHook(IPv4Datagram* datagram, const InterfaceEntry* inIE, const InterfaceEntry*& outIE, IPv4Address& nextHopAddr)
{
    for (HookList::iterator iter = hooks.begin(); iter != hooks.end(); iter++) {
        IHook::Result r = iter->second->datagramForwardHook(datagram, inIE, outIE, nextHopAddr);
        switch(r)
        {
            case INetfilter::IHook::ACCEPT: break;   // continue iteration
            case INetfilter::IHook::DROP:   delete datagram; return r;
            case INetfilter::IHook::QUEUE:  queuedDatagramsForHooks.push_back(QueuedDatagramForHook(datagram, inIE, outIE, nextHopAddr, INetfilter::IHook::FORWARD)); return r;
            case INetfilter::IHook::STOLEN: return r;
            default: throw cRuntimeError("Unknown Hook::Result value: %d", (int)r);
        }
    }
    return INetfilter::IHook::ACCEPT;
}

INetfilter::IHook::Result C2WIPv4::datagramPostRoutingHook(IPv4Datagram* datagram, const InterfaceEntry* inIE, const InterfaceEntry*& outIE, IPv4Address& nextHopAddr)
{
    for (HookList::iterator iter = hooks.begin(); iter != hooks.end(); iter++) {
        IHook::Result r = iter->second->datagramPostRoutingHook(datagram, inIE, outIE, nextHopAddr);
        switch(r)
        {
            case INetfilter::IHook::ACCEPT: break;   // continue iteration
            case INetfilter::IHook::DROP:   delete datagram; return r;
            case INetfilter::IHook::QUEUE:  queuedDatagramsForHooks.push_back(QueuedDatagramForHook(datagram, inIE, outIE, nextHopAddr, INetfilter::IHook::POSTROUTING)); return r;
            case INetfilter::IHook::STOLEN: return r;
            default: throw cRuntimeError("Unknown Hook::Result value: %d", (int)r);
        }
    }
    return INetfilter::IHook::ACCEPT;
}

bool C2WIPv4::handleOperationStage(LifecycleOperation *operation, int stage, IDoneCallback *doneCallback)
{
    Enter_Method_Silent();
    if (dynamic_cast<NodeStartOperation *>(operation)) {
        if (stage == NodeStartOperation::STAGE_NETWORK_LAYER)
            start();
    }
    else if (dynamic_cast<NodeShutdownOperation *>(operation)) {
        if (stage == NodeShutdownOperation::STAGE_NETWORK_LAYER)
            stop();
    }
    else if (dynamic_cast<NodeCrashOperation *>(operation)) {
        if (stage == NodeCrashOperation::STAGE_CRASH)
            stop();
    }
    return true;
}

void C2WIPv4::start()
{
    ASSERT(queue.isEmpty());
    isUp = true;
}

void C2WIPv4::stop()
{
    isUp = false;
    flush();
}

void C2WIPv4::flush()
{
    delete cancelService();
    queue.clear();
    pendingPackets.clear();
}

bool C2WIPv4::isNodeUp()
{
    NodeStatus *nodeStatus = dynamic_cast<NodeStatus *>(findContainingNode(this)->getSubmodule("status"));
    return !nodeStatus || nodeStatus->getState() == NodeStatus::UP;
}

INetfilter::IHook::Result C2WIPv4::datagramLocalInHook(IPv4Datagram* datagram, const InterfaceEntry* inIE)
{
    for (HookList::iterator iter = hooks.begin(); iter != hooks.end(); iter++) {
        IHook::Result r = iter->second->datagramLocalInHook(datagram, inIE);
        switch(r)
        {
            case INetfilter::IHook::ACCEPT: break;   // continue iteration
            case INetfilter::IHook::DROP:   delete datagram; return r;
            case INetfilter::IHook::QUEUE:  queuedDatagramsForHooks.push_back(QueuedDatagramForHook(dynamic_cast<IPv4Datagram *>(datagram), inIE, NULL, IPv4Address::UNSPECIFIED_ADDRESS, INetfilter::IHook::LOCALIN)); return r;
            case INetfilter::IHook::STOLEN: return r;
            default: throw cRuntimeError("Unknown Hook::Result value: %d", (int)r);
        }
    }
    return INetfilter::IHook::ACCEPT;
}

INetfilter::IHook::Result C2WIPv4::datagramLocalOutHook(IPv4Datagram* datagram, const InterfaceEntry*& outIE, IPv4Address& nextHopAddr)
{
    for (HookList::iterator iter = hooks.begin(); iter != hooks.end(); iter++) {
        IHook::Result r = iter->second->datagramLocalOutHook(datagram, outIE, nextHopAddr);
        switch(r)
        {
            case INetfilter::IHook::ACCEPT: break;   // continue iteration
            case INetfilter::IHook::DROP:   delete datagram; return r;
            case INetfilter::IHook::QUEUE:  queuedDatagramsForHooks.push_back(QueuedDatagramForHook(datagram, NULL, outIE, nextHopAddr, INetfilter::IHook::LOCALOUT)); return r;
            case INetfilter::IHook::STOLEN: return r;
            default: throw cRuntimeError("Unknown Hook::Result value: %d", (int)r);
        }
    }
    return INetfilter::IHook::ACCEPT;
}

void C2WIPv4::sendOnTransPortOutGateByProtocolId(cPacket *packet, int protocolId)
{
    int gateindex = mapping.getOutputGateForProtocol(protocolId);
    cGate* outGate = gate("transportOut", gateindex);
    send(packet, outGate);
}

void C2WIPv4::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj)
{
    Enter_Method_Silent();

    if (signalID == completedARPResolutionSignal)
    {
        IARPCache::Notification *entry = check_and_cast<IARPCache::Notification *>(obj);
        arpResolutionCompleted(entry);
    }
    if (signalID == failedARPResolutionSignal)
    {
        IARPCache::Notification *entry = check_and_cast<IARPCache::Notification *>(obj);
        arpResolutionTimedOut(entry);
    }
}

#ifdef NEWFRAGMENT
void C2WIPv4::fragmentAndSend(IPv4Datagram *datagram, const InterfaceEntry *ie, IPv4Address nextHopAddr)
{
    // fill in source address
    if (datagram->getSrcAddress().isUnspecified())
        datagram->setSrcAddress(ie->ipv4Data()->getIPAddress());

    // hop counter decrement; but not if it will be locally delivered
    if (!ie->isLoopback())
        datagram->setTimeToLive(datagram->getTimeToLive()-1);

    // hop counter check
    if (datagram->getTimeToLive() < 0)
    {
        // drop datagram, destruction responsibility in ICMP
        EV << "datagram TTL reached zero, sending ICMP_TIME_EXCEEDED\n";
        icmpAccess.get()->sendErrorMessage(datagram, -1 /*TODO*/, ICMP_TIME_EXCEEDED, 0);
        numDropped++;
        return;
    }

    int mtu = ie->getMTU();

    // check if datagram does not require fragmentation
    if (mtu == 0 || datagram->getByteLength() <= mtu)
    {
        sendDatagramToOutput(datagram, ie, nextHopAddr);
        return;
    }

    if (datagram->getEncapsulatedPacket())
        datagram->setTotalPayloadLength(datagram->getEncapsulatedPacket()->getByteLength());

    // if "don't fragment" bit is set, throw datagram away and send ICMP error message
    if (datagram->getDontFragment())
    {
        EV << "datagram larger than MTU and don't fragment bit set, sending ICMP_DESTINATION_UNREACHABLE\n";
        icmpAccess.get()->sendErrorMessage(datagram, -1 /*TODO*/, ICMP_DESTINATION_UNREACHABLE,
                ICMP_DU_FRAGMENTATION_NEEDED);
        numDropped++;
        return;
    }

    cPacket * payload = datagram->decapsulate();
    int headerLength = datagram->getByteLength();
    int payloadLength = payload->getByteLength();

    if (isDsr) // to avoid problems with the DSR header that could force future fragmentations
        mtu -= 30;

    // FIXME some IP options should not be copied into each fragment, check their COPY bit


    int fragmentLength = ((mtu - headerLength) / 8) * 8; // payload only (without header)
    int offsetBase = datagram->getFragmentOffset();
    if (fragmentLength <= 0)
        throw cRuntimeError("Cannot fragment datagram: MTU=%d too small for header size (%d bytes)", mtu, headerLength); // exception and not ICMP because this is likely a simulation configuration error, not something one wants to simulate

    int noOfFragments = (payloadLength + fragmentLength - 1)/ fragmentLength;
    EV << "Breaking datagram into " << noOfFragments << " fragments\n";

    // create and send fragments
    EV << "Breaking datagram into " << noOfFragments << " fragments\n";
    std::string fragMsgName = datagram->getName();
    fragMsgName += "-frag";

    for (int offset=0; offset < payloadLength; offset+=fragmentLength)
    {
        bool lastFragment = (offset+fragmentLength >= payloadLength);
        // length equal to fragmentLength, except for last fragment;
        int thisFragmentLength = lastFragment ? payloadLength - offset : fragmentLength;
        cPacket *payloadFrag = payload->dup();
        payloadFrag->setByteLength(thisFragmentLength);

        // FIXME is it ok that full encapsulated packet travels in every datagram fragment?
        // should better travel in the last fragment only. Cf. with reassembly code!
        IPv4Datagram *fragment = (IPv4Datagram *) datagram->dup();
        fragment->setName(fragMsgName.c_str());

        // "more fragments" bit is unchanged in the last fragment, otherwise true
        if (!lastFragment)
            fragment->setMoreFragments(true);

        fragment->setByteLength(headerLength);
        fragment->encapsulate(payloadFrag);

        fragment->setFragmentOffset(offsetBase + offset);

        sendDatagramToOutput(fragment, ie, nextHopAddr);
    }

    delete payload;
    delete datagram;
}


void C2WIPv4::reassembleAndDeliver(IPv4Datagram *datagram)
{
    EV << "Local delivery\n";

    if (datagram->getSrcAddress().isUnspecified())
        EV << "Received datagram '%s' without source address filled in" << datagram->getName() << "\n";


    // reassemble the packet (if fragmented)
    if (datagram->getFragmentOffset()!=0 || datagram->getMoreFragments())
    {
        EV << "Datagram fragment: offset=" << datagram->getFragmentOffset()
           << ", MORE=" << (datagram->getMoreFragments() ? "true" : "false") << ".\n";

        // erase timed out fragments in fragmentation buffer; check every 10 seconds max
        if (simTime() >= lastCheckTime + 10)
        {
            lastCheckTime = simTime();
            fragbuf.purgeStaleFragments(simTime()-fragmentTimeoutTime);
        }

        if ((datagram->getTotalPayloadLength()>0) && (datagram->getTotalPayloadLength() != datagram->getEncapsulatedPacket()->getByteLength()))
        {
            int totalLength = datagram->getByteLength();
            cPacket * payload = datagram->decapsulate();
            datagram->setHeaderLength(datagram->getByteLength());
            payload->setByteLength(datagram->getTotalPayloadLength());
            datagram->encapsulate(payload);
            datagram->setByteLength(totalLength);
        }

        datagram = fragbuf.addFragment(datagram, simTime());
        if (!datagram)
        {
            EV << "No complete datagram yet.\n";
            return;
        }
        EV << "This fragment completes the datagram.\n";
    }

    if (datagramLocalInHook(datagram, getSourceInterfaceFrom(datagram)) != INetfilter::IHook::ACCEPT)
    {
        return;
    }

    reassembleAndDeliverFinish(datagram);
}
#endif

const IPv4RouteRule * C2WIPv4::checkInputRule(const IPv4Datagram* datagram)
{
    if (rt->getNumRules(false)>0)
    {
    	int protocol = datagram->getTransportProtocol();
    	int sport=-1;
    	int dport=-1;
    	if (protocol==IP_PROT_UDP)
    	{
    		sport = dynamic_cast<UDPPacket*> (datagram->getEncapsulatedPacket())->getSourcePort();
    		dport = dynamic_cast<UDPPacket*> (datagram->getEncapsulatedPacket())->getDestinationPort();
    	}
    	else if (protocol==IP_PROT_TCP)
    	{
    		TCPSegment *aux = dynamic_cast<TCPSegment*> (datagram->getEncapsulatedPacket());
    		sport = aux->getSrcPort();
    		dport = aux->getDestPort();
    	}
    	IPv4Datagram *pkt = const_cast<IPv4Datagram*>(datagram);
    	const InterfaceEntry *iface=getSourceInterfaceFrom(pkt);
    	const IPv4RouteRule *rule = rt->findRule(false,protocol,sport,datagram->getSrcAddress(),dport,datagram->getDestAddress(),iface);
    	return rule;
    }
    return NULL;
}

const IPv4RouteRule * C2WIPv4::checkOutputRule(const IPv4Datagram* datagram,const InterfaceEntry *destIE)
{
    if (rt->getNumRules(true)>0)
    {
    	int protocol = datagram->getTransportProtocol();
    	int sport=-1;
    	int dport=-1;
    	if (protocol==IP_PROT_UDP)
    	{
    		sport = dynamic_cast<UDPPacket*> (datagram->getEncapsulatedPacket())->getSourcePort();
    		dport = dynamic_cast<UDPPacket*> (datagram->getEncapsulatedPacket())->getDestinationPort();
        }
        else if (protocol==IP_PROT_TCP)
        {
            TCPSegment *aux = dynamic_cast<TCPSegment*> (datagram->getEncapsulatedPacket());
    		sport = aux->getSrcPort();
    		dport = aux->getDestPort();
    	}
    	InterfaceEntry *iface =NULL;
    	if (destIE)
            iface=const_cast<InterfaceEntry*>(destIE);
    	else
    	{
            const IPv4Route *re = rt->findBestMatchingRoute(datagram->getDestAddress());
            if (re)
              iface=re->getInterface();
    	}
    	const IPv4RouteRule *rule = rt->findRule(true,protocol,sport,datagram->getSrcAddress(),dport,datagram->getDestAddress(),iface);
    	return rule;
    }
    return NULL;
}

const IPv4RouteRule * C2WIPv4::checkOutputRuleMulticast(const IPv4Datagram* datagram)
{
    if (rt->getNumRules(true)>0)
    {
    	int protocol = datagram->getTransportProtocol();
    	int sport=-1;
    	int dport=-1;
    	if (protocol==IP_PROT_UDP)
    	{
    		sport = dynamic_cast<UDPPacket*> (datagram->getEncapsulatedPacket())->getSourcePort();
    		dport = dynamic_cast<UDPPacket*> (datagram->getEncapsulatedPacket())->getDestinationPort();
    	}
    	else if (protocol==IP_PROT_TCP)
    	{
    		TCPSegment *aux = dynamic_cast<TCPSegment*> (datagram->getEncapsulatedPacket());
    		sport = aux->getSrcPort();
    		dport = aux->getDestPort();
    	}
    	InterfaceEntry *iface =NULL;
    	const IPv4RouteRule *rule = rt->findRule(true,protocol,sport,datagram->getSrcAddress(),dport,datagram->getDestAddress(),iface);
    	return rule;
    }
    return NULL;
}

bool C2WIPv4::isFiltered(const IPv4Address &sourceIPAddress,
        const IPv4Address &destinationIPAddress) {

    for (NetworkAddressSDPairSet::iterator nssItr = _filterAttackSet.begin();
            nssItr != _filterAttackSet.end(); ++nssItr) {
        const NetworkAddressSDPair &networkAddressSDPair = *nssItr;
        if (networkAddressSDPair.first.matches(sourceIPAddress)
                && networkAddressSDPair.second.matches(destinationIPAddress)) {
            std::cerr << "Host \"" << _hostFullName << "\": ("
                    << sourceIPAddress << "," << destinationIPAddress
                    << ") matches filter (" << networkAddressSDPair.first << ","
                    << networkAddressSDPair.second << ")" << std::endl;
            return true;
        }
    }

    return false;
}

C2WIPv4::DatagramDataSP C2WIPv4::ReplayBuffer::getRandom(void) {
    if (_datagramDataSPDeque.empty()) {
        return DatagramDataSP();
    }
    if (_serialNo >= _datagramDataSPDeque.size()) {
        _serialNo = 0;
    }

    int number = rand() % _datagramDataSPDeque.size();
    DatagramDataSP datagramDataSP = _datagramDataSPDeque[number];

    IPv4Datagram *datagram = datagramDataSP->getIPDatagram();
    IPv4Datagram *firstDatagram = _datagramDataSPDeque.front()->getIPDatagram();

    SimTime tempSimTime = datagram->getTimestamp();
    datagram->setTimestamp(firstDatagram->getTimestamp());
    firstDatagram->setTimestamp(tempSimTime);

    std::swap(_datagramDataSPDeque[number], _datagramDataSPDeque.front());
    _datagramDataSPDeque.pop_front();

    return datagramDataSP;
}

C2WIPv4::ReplayBufferSPList C2WIPv4::getSerialReplayBufferSPList(
        unsigned int sourceIPAddress, unsigned int destinationIPAddress) {

    ReplayBufferSPList replayBufferSPList;

    for (NetworkAddressReplayBufferSPMap::iterator nrmItr =
            _serialReplayBufferSPMap.begin();
            nrmItr != _serialReplayBufferSPMap.end(); ++nrmItr) {
        const NetworkAddressSDPair &networkAddressSDPair = nrmItr->first;
        if (networkAddressSDPair.first.matches(sourceIPAddress)
                && networkAddressSDPair.second.matches(destinationIPAddress)) {
            replayBufferSPList.push_back(nrmItr->second);
        }
    }

    return replayBufferSPList;
}

void C2WIPv4::removeSerialReplayBufferSP(
        const NetworkAddress &sourceNetworkAddress,
        const NetworkAddress &destinationNetworkAddress) {

    NetworkAddressReplayBufferSPMap::iterator nrmItr =
            _serialReplayBufferSPMap.find(
                    NetworkAddressSDPair(sourceNetworkAddress,
                            destinationNetworkAddress));
    if (nrmItr == _serialReplayBufferSPMap.end()) {
        return;
    }

    _serialReplayBufferSPMap.erase(nrmItr);

    if (_serialReplayBufferSPMap.empty()) {
        _hasSerialReplayBufferSPMap = false;
    }
}

C2WIPv4::ReplayBufferSPList C2WIPv4::getRandomReplayBufferSPList(
        unsigned int sourceIPAddress, unsigned int destinationIPAddress) {

    ReplayBufferSPList replayBufferSPList;

    for (NetworkAddressReplayBufferSPMap::iterator nrmItr =
            _randomReplayBufferSPMap.begin();
            nrmItr != _randomReplayBufferSPMap.end(); ++nrmItr) {
        const NetworkAddressSDPair &networkAddressSDPair = nrmItr->first;
        if (networkAddressSDPair.first.matches(sourceIPAddress)
                && networkAddressSDPair.second.matches(destinationIPAddress)) {
            replayBufferSPList.push_back(nrmItr->second);
        }
    }

    return replayBufferSPList;
}

void C2WIPv4::removeRandomReplayBufferSP(
        const NetworkAddress &sourceNetworkAddress,
        const NetworkAddress &destinationNetworkAddress) {
    NetworkAddressReplayBufferSPMap::iterator nrmItr =
            _randomReplayBufferSPMap.find(
                    NetworkAddressSDPair(sourceNetworkAddress,
                            destinationNetworkAddress));
    if (nrmItr == _randomReplayBufferSPMap.end()) {
        return;
    }

    _randomReplayBufferSPMap.erase(nrmItr);

    if (_randomReplayBufferSPMap.empty()) {
        _hasRandomReplayBufferSPMap = false;
    }
}

void C2WIPv4::recordNetworkInformation(void) {

    HLAInterface::InterfaceIPAddressMap &interfaceIPAddressMap =
            HLAInterface::get_InstancePtr()->getIPModuleInterfaceIPAddressMap(
                    _hostFullName);

    interfaceIPAddressMap.clear();

    int noEntries = ift->getNumInterfaces();
    for (int ix = 0; ix < noEntries; ++ix) {

        InterfaceEntry *interfaceEntry = ift->getInterface(ix);
        IPv4InterfaceData *ipv4InterfaceData = interfaceEntry->ipv4Data();
        IPv4Address ipAddress = ipv4InterfaceData->getIPAddress();
        if (ipAddress.isUnspecified()) {
            continue;
        }

        interfaceIPAddressMap.insert(
                std::make_pair(interfaceEntry->getName(), ipAddress));
    }

//    std::cerr << "Routes:" << std::endl;
//    noEntries = rt->getNumRoutes();
//    for( int ix = 0 ; ix < noEntries ; ++ix ) {
//        const IPv4Route *ipRoute = rt->getRoute( ix );
//        std::cerr << "\tAddress  : " << ipRoute->getHost() << std::endl;
//        std::cerr << "\tNetmask  : " << ipRoute->getNetmask() << std::endl;
//        std::cerr << "\tInterface: " << ipRoute->getInterfaceName() << std::endl;
//        std::cerr << "\tGateway  : " << ipRoute->getGateway() << std::endl;
//        std::cerr << std::endl;
//    }
//    std::cerr << std::endl;

    HLAInterface::get_InstancePtr()->unregisterIPModuleNetworks(this,
            _networkAddressSet);
    _networkAddressSet.clear();
    _networkAddressInterfaceNameMap.clear();

    int numRoutes = rt->getNumRoutes();
    for (int ix = 0; ix < numRoutes; ++ix) {
        const IPv4Route *ipRoute = rt->getRoute(ix);
        if (ipRoute->getAdminDist() != IPv4Route::dDirectlyConnected) {
            continue;
        }
        NetworkAddress networkAddress(ipRoute);
        _networkAddressSet.insert(networkAddress);
        _networkAddressInterfaceNameMap.insert(
                std::make_pair(networkAddress, ipRoute->getInterfaceName()));
//            std::cerr << "Host \"" << _hostFullName << "\" adding (" << networkAddress << "," << ipRoute->getInterfaceName() <<
//             ") to _networkAddressInterfaceNameMap " << std::endl;
    }
    HLAInterface::get_InstancePtr()->registerIPModuleNetworks(this,
            _networkAddressSet);

}

void C2WIPv4::receiveChangeNotification(int category,
        const cPolymorphic *details) {

    if (category == NF_INTERFACE_IPv4CONFIG_CHANGED) {

        recordNetworkInformation();

    } else {

        std::cerr << "WARNING:  unexpected notification \""
                << notificationCategoryName(category)
                << "\" from NotificationBoard:  unsubscribing.";
// THE FOLLOWING LINE WILL CAUSE A SEGFAULT DUE TO THE USE OF VECTORS IN NotificationBoard MODULE FOR LISTENERS.
//        _notificationBoard->unsubscribe( this, category );

    }
}

std::ostream &operator<<(std::ostream &os,
        const C2WIPv4::ReplayBuffer &replayBuffer) {
    os << "ReplayBuffer( DatagramDataSPDeque_size:"
            << replayBuffer._datagramDataSPDeque.size() << ", recordStartTime:"
            << replayBuffer._recordStartTime.dbl() << ", recordDuration:"
            << replayBuffer._recordDuration << ", recordEndTime:"
            << replayBuffer._recordEndTime.dbl() << ", serialNo:"
            << replayBuffer._serialNo << ", playing:" << replayBuffer._playing
            << ")";

    return os;
}

std::ostream &operator<<(std::ostream &os,
        const C2WIPv4::ReplayBufferSP &replayBufferSP) {
    return os << *replayBufferSP;
}

std::ostream &operator<<(std::ostream &os,
        const C2WIPv4::DatagramData &datagramData) {
    os << "DatagramData()";
    return os;
}

std::ostream &operator<<(std::ostream &os,
        const C2WIPv4::DatagramDataSP &datagramDataSP) {
    return os << *datagramDataSP;
}

