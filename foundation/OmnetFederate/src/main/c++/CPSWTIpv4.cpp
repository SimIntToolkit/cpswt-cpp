/*
 * CPSWTIpv4.cc
 *
 *  Created on: Jul 7, 2021
 *      Author: Harmon Nine
 */


#include "../include/CPSWTIpv4.h"

//#include "UDPPacket.h"
//#include "TCPSegment.h"
//#include "UDPPacket_m.h"

#include <inet/networklayer/ipv4/Ipv4InterfaceData.h>

#include "InteractionMsg_m.h"

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
#include "IPFirewallMsg_m.h"

Define_Module(CPSWTIpv4);


void CPSWTIpv4::initialize(int stage) {

    Super::initialize(stage);

    if (stage == inet::INITSTAGE_LOCAL) {
        _notificationBoard = inet::getContainingNode(this);

        _hostFullName = getParentModule()->getParentModule()->getFullPath();
        AttackCoordinator::getSingleton().registerIPModule(_hostFullName, this);

    } else if (stage == inet::INITSTAGE_LAST) {

        // SHOULD BE LAST BECAUSE MODULE WHERE SUBSCRIPTION TAKES PLACE MUST EXIST -- COULD BE ANY NODE
        _notificationBoard->subscribe( inet::interfaceIpv4ConfigChangedSignal, this );
        recordNetworkInformation();

    }

}

void CPSWTIpv4::receiveSignal(omnetpp::cComponent *source, omnetpp::simsignal_t signalID, omnetpp::cObject *obj, omnetpp::cObject *details) {

    Enter_Method_Silent();

    Super::receiveSignal(source, signalID, obj, details);

    if (signalID == inet::interfaceIpv4ConfigChangedSignal) {
        recordNetworkInformation();
    }
}

void CPSWTIpv4::handleMessageWhenUp(omnetpp::cMessage *msg) {

    //
    // THIS ATTACK PREVENTS THE HOST FROM PROCESSING THE PACKET -- IMPLEMENTED IN routeUnicastPacket METHOD.
    //
    NodeAttackMsg *nodeAttackMsg = dynamic_cast<NodeAttackMsg *>(msg);
    if (nodeAttackMsg != 0) {

        _nodeAttack = nodeAttackMsg->getAttackInProgress();

        cancelAndDelete(msg);
        return;
    }


    //
    // THIS ATTACK SETS UP A PROCESSING DELAY FOR INCOMING PACKETS
    //
    DelayNodeAttackMsg *delayNodeAttackMsg = dynamic_cast<DelayNodeAttackMsg *>(msg);
    if (delayNodeAttackMsg != 0) {

        _nodeDelayed = delayNodeAttackMsg->getAttackInProgress();
        _nodeDelayMean = delayNodeAttackMsg->getDelayMean();
        _nodeDelayStdDev = delayNodeAttackMsg->getDelayStdDev();

        cancelAndDelete(msg);
        return;
    }


    //
    // THIS ATTACK EAVESDROPS ON NETWORK PACKETS AND SENDS COPIES OF THEM TO UNINTENDED HOSTS
    //
    SnifferAttackMsg *snifferAttackMsg = dynamic_cast<SnifferAttackMsg *>(msg);
    if (snifferAttackMsg != 0) {

        std::string hostName = snifferAttackMsg->getListenerNodeFullPath();
        std::string interface = snifferAttackMsg->getListenerInterface();

        if (snifferAttackMsg->getListen()) {

            addListener(AttackCoordinator::getSingleton().getIPAddress(hostName, interface));

        } else {

            deleteListener(AttackCoordinator::getSingleton().getIPAddress(hostName, interface));

        }

        cancelAndDelete(msg);
        return;
    }


    //
    // THIS ATTACK FILTERS OUT (DELETES) PACKETS SENt FROM ONE SPECIFIED NETWORK (LAN) TO ANOTHER
    //
    FilterAttackMsg *filterAttackMsg = dynamic_cast<FilterAttackMsg *>(msg);
    if (filterAttackMsg != 0) {

        if (filterAttackMsg->getEnable()) {

            addFilter(filterAttackMsg->getSourceNetworkAddress(), filterAttackMsg->getDestinationNetworkAddress());

        } else {

            deleteFilter(filterAttackMsg->getSourceNetworkAddress(), filterAttackMsg->getDestinationNetworkAddress());

        }

        cancelAndDelete(msg);
        return;
    }


    //
    // THIS IS LIKE THE FILTER ATTACK, BUT IS INTENDED AS PART OF THE NORMAL FUNCTIONING OF THE NETWORK
    //
    IPFirewallMsg *ipFirewallMsg = dynamic_cast<IPFirewallMsg *>(msg);
    if (ipFirewallMsg != 0) {

        if (ipFirewallMsg->getEnable()) {

            addFilter(ipFirewallMsg->getSourceNetworkAddress(), ipFirewallMsg->getDestinationNetworkAddress());

        } else {

            deleteFilter(ipFirewallMsg->getSourceNetworkAddress(), ipFirewallMsg->getDestinationNetworkAddress());

        }

        cancelAndDelete(msg);
        return;
    }


    //
    // ATTACK PARTICULAR NETWORK INTERFACES ON A HOST
    //
    NetworkAttackMsg *networkAttackMsg = dynamic_cast<NetworkAttackMsg *>(msg);
    if (networkAttackMsg != 0) {

        NetworkAddress networkAddress(networkAttackMsg->getNetworkAddress());

        NetworkAddressInterfaceNameMap::iterator nimItr =_networkAddressInterfaceNameMap.find(networkAddress);
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


    //
    // REPLAY ATTACK -- START RECORDING
    //
    RecordReplayAttackMsg *recordReplayAttackMsg = dynamic_cast<RecordReplayAttackMsg *>(msg);
    if (recordReplayAttackMsg != 0) {

        ReplayBufferSP replayBufferSP = getSerialReplayBufferSP(
          recordReplayAttackMsg->getSourceNetworkAddress(),
          recordReplayAttackMsg->getDestinationNetworkAddress()
        );

        if (recordReplayAttackMsg->getEnable()) {

            replayBufferSP->reset(recordReplayAttackMsg->getRecordDuration());

        } else {

            replayBufferSP->setPlaying(false);
            removeSerialReplayBufferSP(
              recordReplayAttackMsg->getSourceNetworkAddress(),
              recordReplayAttackMsg->getDestinationNetworkAddress()
            );
        }

        cancelAndDelete(msg);
        return;
    }

    //
    // REPLAY ATTACK:  START/STOP REPLAYING RECORDED Packet'S
    //
    ReplayAttackMsg *replayAttackMsg = dynamic_cast<ReplayAttackMsg *>(msg);
    if (replayAttackMsg != 0) {

        ReplayBufferSP replayBufferSP = getSerialReplayBufferSP(
                replayAttackMsg->getSourceNetworkAddress(),
                replayAttackMsg->getDestinationNetworkAddress()
        );

        if (replayAttackMsg->getPlay()) {

            if (!replayBufferSP->getPlaying()) {
                replayBufferSP->setPlaying(true);

                ReplayMsg *replayMsg = new ReplayMsg;
                replayMsg->setReplayBufferSP(replayBufferSP);

                scheduleAt(omnetpp::simTime() + replayBufferSP->getNextTimeOffset().dbl(), replayMsg);
            }

        } else {

            replayBufferSP->setPlaying(false);

        }

        cancelAndDelete(msg);
        return;
    }

    //
    // PROCESS REPLAYED Packet
    //
    ReplayMsg *replayMsg = dynamic_cast<ReplayMsg *>(msg);
    if (replayMsg != 0) {
        ReplayBufferSP replayBufferSP = replayMsg->getReplayBufferSP();
        if (!replayBufferSP->getPlaying()) {
            cancelAndDelete(msg);
            return;
        }

        inet::Packet *packet = replayBufferSP->getSerial()->dup();
        auto c_packetChunkPtr = packet->peekAtFront<inet::cPacketChunk>();
        inet::cPacket *c_packetPtr = c_packetChunkPtr->getPacket();

        InteractionMsg *interactionMsg = dynamic_cast< InteractionMsg * >( c_packetPtr );

        if (interactionMsg != 0) {
            interactionMsg->setMessageNo(AttackCoordinator::getUniqueNo());
        }
        Super::routeUnicastPacket(packet);

        double nextTimeOffset = replayBufferSP->getNextTimeOffset().dbl();
        if (nextTimeOffset < 0) {

            std::cerr << "ERROR:  IPv4:  ReplayAttack:  Host \"" << _hostFullName
                    << "\":  Attempt to get time offset from empty ReplayBuffer" << std::endl;

            cancelAndDelete(msg);
            return;
        }

        scheduleAt(omnetpp::simTime() + nextTimeOffset, msg);
        return;
    }

    Super::handleMessageWhenUp(msg);
}

void CPSWTIpv4::routeUnicastPacket(inet::Packet *packet) {

    //
    // IF HOST BEING ATTACKED, DROP Packet
    //
    if (_nodeAttack) {

        std::cout << "Host \"" << _hostFullName << "\":  under host attack -- dropping packet." << std::endl;

        delete packet;
        return;
    }


    //
    // IF HOST IS UNDER DELAY ATTACK, DELAY Packet
    // DELAYED PACKET IS RECAST AS "DelayedPacket" SO IT WON'T BE DELAYED MULTIPLE TIMES
    //
    if (_nodeDelayed && dynamic_cast<DelayedPacket *>(packet) == nullptr) {

        DelayedPacket *delayedPacket = new DelayedPacket(packet);

        double delay = truncnormal(_nodeDelayMean, _nodeDelayStdDev);

        scheduleAt(omnetpp::simTime() + delay, delayedPacket);

        std::cout << "Host \"" << _hostFullName << "\":  delaying packet " << delay << " seconds."<< std::endl;

        delete packet;
        return;
    }


    //
    // SNIFFER ATTACK
    //
    if (_hasListeners) {

        for (IPAddressSet::iterator iasItr = _listenerIPAddressSet.begin(); iasItr != _listenerIPAddressSet.end(); ++iasItr) {

            const inet::Ipv4Address &snifferIPAddress(*iasItr);

            auto copiedPacket = new inet::Packet(packet->getName());

            inet::b offset = inet::b(0);
            while(auto chunk = packet->peekAt(offset)->dupShared()) {

                if (chunk->getChunkType() == inet::Chunk::CT_CPACKET) {
                    auto ipv4Header = inet::staticPtrCast<inet::Ipv4Header>(chunk);
                    ipv4Header->setDestAddress(snifferIPAddress);
                }

                copiedPacket->insertAtBack(chunk);

                offset += chunk->getChunkLength();
            }

            std::cout << "Host \"" << _hostFullName << "\":  sending sniffed datagram to " << snifferIPAddress << std::endl;

            Super::routeUnicastPacket(copiedPacket);
        }
    }


    auto ipv4Header = packet->peekAtFront<inet::Ipv4Header>();
    inet::Ipv4Address destAddr = ipv4Header->getDestAddress();
    inet::Ipv4Address srcAddr = ipv4Header->getSrcAddress();
    if (srcAddr.isUnspecified()) {
        srcAddr = destAddr;
    }

    //
    // FILTER ATTACK
    //
    if (_hasFilters && isFiltered(srcAddr, destAddr)) {

        std::cout << "Host \"" << _hostFullName << "\":  filtering datagram with (srcAddr,destAddr) = ("
                << srcAddr << "," << destAddr << ")." << std::endl;

        delete packet;
        return;
    }


    //
    // NETWORK ATTACK
    //
    // THE LOGIC HERE FOLLOWS THE LOGIC IN THE OLDER CPSWTIpv4.cc SOURCE FILE, AS WELL AS THE LOGIC IN THE BASE (Super) CLASS
    //
    const inet::InterfaceEntry *destIE = getDestInterface(packet);
    if (!destIE) {

        // use IPv4 routing (lookup in routing table)
        const inet::Ipv4Route *re = rt->findBestMatchingRoute(destAddr);

        if (_hasNetworkAttack && re != NULL) {

            // CHECK IF PACKET IS BEING ROUTED INTO OR THROUGH AN INTERFACE TO AN ATTACKED NETWORK
            std::string interfaceName(re->getInterfaceName());
            if (_attackedInterfaceSet.find(interfaceName)!= _attackedInterfaceSet.end()) {

                std::cout << "Host \"" << _hostFullName << "\":  packet being sent to attacked interface \""
                        << interfaceName << "\".  Dropping datagram." << std::endl;

                delete packet;
                return;
            }
        }

    }


    //
    // REPLAY ATTACK -- RECORD/PLAY
    //
    if (_hasSerialReplayBufferSPMap) {

        ReplayBufferSPList replayBufferSPList = getSerialReplayBufferSPList(srcAddr.getInt(), destAddr.getInt());

        bool _replayPlaying = false;
        for(ReplayBufferSPList::iterator rblItr = replayBufferSPList.begin(); rblItr != replayBufferSPList.end(); ++rblItr) {

            ReplayBuffer &replayBuffer = **rblItr;
            if (replayBuffer.getPlaying()) {

                _replayPlaying = true;

            } else {

                std::cout << "Host \"" << _hostFullName << "\":  recording datagram ("
                        << srcAddr << "," << destAddr << ") for replay attack." << std::endl;

                replayBuffer.addPacketSerial(packet);
            }
        }

        if (_replayPlaying) {

            std::cout << "Host \"" << _hostFullName << "\":  replay in progress, dropping datagram ("
                    << srcAddr << "," << destAddr << ")" << std::endl;

            delete packet;
            return;
        }
    }

    Super::routeUnicastPacket(packet);
}


bool CPSWTIpv4::isFiltered(const inet::Ipv4Address &sourceIPAddress, const inet::Ipv4Address &destinationIPAddress) {

    for(NetworkAddressSDPairSet::iterator nssItr = _filterAttackSet.begin(); nssItr != _filterAttackSet.end(); ++nssItr) {

        const NetworkAddressSDPair &networkAddressSDPair = *nssItr;

        if (networkAddressSDPair.first.matches(sourceIPAddress) && networkAddressSDPair.second.matches(destinationIPAddress)) {

            std::cerr << "Host \"" << _hostFullName << "\": (" << sourceIPAddress << "," << destinationIPAddress
                    << ") matches filter (" << networkAddressSDPair.first << "," << networkAddressSDPair.second << ")" << std::endl;

            return true;
        }
    }

    return false;
}


CPSWTIpv4::ReplayBufferSPList CPSWTIpv4::getSerialReplayBufferSPList(unsigned int sourceIPAddress, unsigned int destinationIPAddress) {

    ReplayBufferSPList replayBufferSPList;

    for (
            NetworkAddressReplayBufferSPMap::iterator nrmItr = _serialReplayBufferSPMap.begin();
            nrmItr != _serialReplayBufferSPMap.end();
            ++nrmItr
    ) {

        const NetworkAddressSDPair &networkAddressSDPair = nrmItr->first;

        if (networkAddressSDPair.first.matches(sourceIPAddress) && networkAddressSDPair.second.matches(destinationIPAddress)) {
            replayBufferSPList.push_back(nrmItr->second);
        }

    }

    return replayBufferSPList;
}


void CPSWTIpv4::removeSerialReplayBufferSP(const NetworkAddress &sourceNetworkAddress, const NetworkAddress &destinationNetworkAddress) {

    NetworkAddressReplayBufferSPMap::iterator nrmItr = _serialReplayBufferSPMap.find(
            NetworkAddressSDPair(sourceNetworkAddress, destinationNetworkAddress)
    );

    if (nrmItr == _serialReplayBufferSPMap.end()) {
        return;
    }

    _serialReplayBufferSPMap.erase(nrmItr);

    if (_serialReplayBufferSPMap.empty()) {
        _hasSerialReplayBufferSPMap = false;
    }
}


void CPSWTIpv4::recordNetworkInformation(void) {

    AttackCoordinator::InterfaceIPAddressMap &interfaceIPAddressMap = AttackCoordinator::getSingleton().getIPModuleInterfaceIPAddressMap(_hostFullName);

    interfaceIPAddressMap.clear();

    int noEntries = ift->getNumInterfaces();
    for (int ix = 0; ix < noEntries; ++ix) {

        inet::InterfaceEntry *interfaceEntry = ift->getInterface(ix);
        inet::Ipv4Address ipAddress = interfaceEntry->getNetworkAddress().toIpv4();
        if (ipAddress.isUnspecified()) {
            continue;
        }

        interfaceIPAddressMap.insert(std::make_pair(static_cast<omnetpp::cModule *>(interfaceEntry)->getName(), ipAddress));
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

    AttackCoordinator::getSingleton().unregisterIPModuleNetworks(this, _networkAddressSet);
    _networkAddressSet.clear();
    _networkAddressInterfaceNameMap.clear();

    int numRoutes = rt->getNumRoutes();
    for (int ix = 0; ix < numRoutes; ++ix) {
        const inet::Ipv4Route *ipRoute = rt->getRoute(ix);
        if (ipRoute->getAdminDist() != inet::Ipv4Route::dDirectlyConnected) {
            continue;
        }
        NetworkAddress networkAddress(ipRoute);
        _networkAddressSet.insert(networkAddress);
        _networkAddressInterfaceNameMap.insert(std::make_pair(networkAddress, ipRoute->getInterfaceName()));
//      std::cerr << "Host \"" << _hostFullName << "\" adding (" << networkAddress << "," << ipRoute->getInterfaceName() << ") to _networkAddressInterfaceNameMap " << std::endl;
    }

    AttackCoordinator::getSingleton().registerIPModuleNetworks(this, _networkAddressSet);
}


std::ostream &operator<<(std::ostream &os, const CPSWTIpv4::ReplayBuffer &replayBuffer) {
    os << "ReplayBuffer( DatagramDataSPDeque_size:" << replayBuffer._packetSPDeque.size()
            << ", recordStartTime:" << replayBuffer._recordStartTime.dbl()
            << ", recordDuration:" << replayBuffer._recordDuration
            << ", recordEndTime:" << replayBuffer._recordEndTime.dbl()
            << ", serialNo:" << replayBuffer._serialNo
            << ", playing:" << replayBuffer._playing
            << " )";

    return os;
}

std::ostream &operator<<(std::ostream &os, const CPSWTIpv4::ReplayBufferSP &replayBufferSP) {
    return os << *replayBufferSP;
}
