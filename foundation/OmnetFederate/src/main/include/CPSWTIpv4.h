/*
 * CPSWTIPv4.h
 *
 *  Created on: Jul 7, 2021
 *      Author: Harmon Nine
 */

#ifndef CPSWTIPv4_H
#define CPSWTIPv4_H

#include <algorithm>
#include <inet/networklayer/ipv4/Ipv4.h>
#include <inet/common/INETDefs.h>


//#ifdef WITH_MANET
//#include "ControlManetRouting_m.h"
//#endif

//#include "INotifiable.h"
//#include "IPv4Datagram.h"
//#include "NotificationBoard.h"

//class IPv4Datagram;


#include "AttackCoordinator.h"


class CPSWTIpv4: public inet::Ipv4 {

public:
    typedef inet::Ipv4 Super;

protected:
    bool isDsr;

    inet::cModule *_notificationBoard;

    std::string _hostFullName;

    //
    // CODE FOR NODE ATTACK
    //
    bool _nodeAttack;

    virtual int numInitStages() const override { return inet::NUM_INIT_STAGES; }

public:
    const std::string &getHostFullName( void ) {
        return _hostFullName;
    }

    //
    // CODE FOR SNIFFER ATTACK
    //
    typedef std::set< inet::Ipv4Address > IPAddressSet;

private:
    IPAddressSet _listenerIPAddressSet;
    bool _hasListeners;

    void addListener( const inet::Ipv4Address &ipAddress ) {
        _listenerIPAddressSet.insert( ipAddress );
        _hasListeners = true;
    }

    void deleteListener( const inet::Ipv4Address &ipAddress ) {
        _listenerIPAddressSet.erase( ipAddress );
        if ( _listenerIPAddressSet.empty() ) {
            _hasListeners = false;
        }
    }


    //
    // CODE FOR NETWORK FILTER ATTACK
    //
    bool _hasFilters;

public:
    typedef AttackCoordinator::NetworkAddress NetworkAddress;
    typedef AttackCoordinator::NetworkAddressComparator NetworkAddressComparator;
    typedef AttackCoordinator::NetworkAddressSet NetworkAddressSet;

    typedef std::pair< NetworkAddress, NetworkAddress > NetworkAddressSDPair;

    struct NetworkAddressSDPairComparator {
        bool operator()( const NetworkAddressSDPair &networkAddressSDPair1, const NetworkAddressSDPair &networkAddressSDPair2 ) {
            NetworkAddressComparator networkAddressComparator;

            {
                const NetworkAddress &sourceNetworkAddress1 = networkAddressSDPair1.first;
                const NetworkAddress &sourceNetworkAddress2 = networkAddressSDPair2.first;
                if (  networkAddressComparator( sourceNetworkAddress1, sourceNetworkAddress2 )  ) {
                    return true;
                }
                if (  networkAddressComparator( sourceNetworkAddress2, sourceNetworkAddress1 )  ) {
                    return false;
                }
            }

            if (  networkAddressComparator( networkAddressSDPair1.second, networkAddressSDPair2.second )  ) {
                return true;
            }
            return false;
        }
    };

    typedef std::set< NetworkAddressSDPair, NetworkAddressSDPairComparator > NetworkAddressSDPairSet;

private:
    NetworkAddressSet _networkAddressSet;
    NetworkAddressSDPairSet _filterAttackSet;

    void addFilter( const NetworkAddress &srcNetworkAddress, const NetworkAddress &dstNetworkAddress ) {
        std::cerr << "Host \"" << _hostFullName << "\":  adding filter (" << srcNetworkAddress << "," << dstNetworkAddress << ")" << std::endl;
        _hasFilters = true;
        _filterAttackSet.insert(  NetworkAddressSDPair( srcNetworkAddress, dstNetworkAddress )  );
    }

    void deleteFilter( const NetworkAddress &srcNetworkAddress, const NetworkAddress &dstNetworkAddress ) {
        NetworkAddressSDPair networkAddressSDPair( srcNetworkAddress, dstNetworkAddress );

        if ( _filterAttackSet.find( networkAddressSDPair ) == _filterAttackSet.end() ) {
            std::cerr << "Host \"" << _hostFullName << "\":  not deleting filter (" << srcNetworkAddress << "," << dstNetworkAddress
             << "):  filter not present" << std::endl;
        } else {
            std::cerr << "Host \"" << _hostFullName << "\":  deleting filter (" << srcNetworkAddress << "," << dstNetworkAddress << ")" << std::endl;
            _filterAttackSet.erase( networkAddressSDPair );
            if ( _filterAttackSet.empty() ) {
                _hasFilters = false;
            }
        }
    }

    bool isFiltered( const inet::Ipv4Address &sourceIPv4Address, const inet::Ipv4Address &destinationIPv4Address );

    //
    // CODE FOR NETWORK ATTACK
    //
    typedef std::map< NetworkAddress, std::string, NetworkAddressComparator > NetworkAddressInterfaceNameMap;
    typedef std::set< std::string > AttackedInterfaceSet;

private:
    bool _hasNetworkAttack;
    NetworkAddressInterfaceNameMap _networkAddressInterfaceNameMap;
    AttackedInterfaceSet _attackedInterfaceSet;

    //
    // CODE FOR REPLAY/OUT-OF-ORDER-PACKETS ATTACK
    //
public:
//    class DatagramData {
//        friend std::ostream &operator<<(std::ostream &os, const DatagramData &datagramData);
//    private:
//        inet::Packet *_delayedPacket;
//        const inet::InterfaceEntry *_fromIE;
//        const inet::InterfaceEntry *_destIE;
//        const inet::Ipv4Address _nextHopAddr;
//
//    public:
//        DatagramData( inet::DelayedPacket *delayedPacket, const inet::InterfaceEntry *fromIE, const inet::InterfaceEntry *destIE, const inet::Ipv4Address &nextHopAddr ) :
//         _delayedPacket( delayedPacket ), _fromIE( fromIE ), _destIE( destIE ), _nextHopAddr( nextHopAddr ) { }
//
//        inet::Packet *getDelayedPacket( void ) {
//            return _delayedPacket;
//        }
//        const inet::InterfaceEntry *getFromInterfaceEntry( void ) const {
//            return _fromIE;
//        }
//        const inet::InterfaceEntry *getDestInterfaceEntry( void ) const {
//            return _destIE;
//        }
//        const inet::Ipv4Address getNextHopAddr( void ) const {
//            return _nextHopAddr;
//        }
//    };

    class DelayedPacket: public inet::Packet {
    public:
        explicit DelayedPacket(const char *name = nullptr, short kind = 0): inet::Packet(name, kind) { }
        DelayedPacket(const char *name, const inet::Ptr<const inet::Chunk>& content): inet::Packet(name, content) { }
        DelayedPacket(const inet::Packet& other): inet::Packet(other) { }
        DelayedPacket(const inet::Packet *other): inet::Packet(*other) { }

        virtual DelayedPacket *dup() const override { return new DelayedPacket(*this); }
    };

    typedef boost::shared_ptr< inet::Packet > PacketSP;
    typedef std::deque< PacketSP > PacketSPDeque;

    class ReplayBuffer {
        friend std::ostream &operator<<( std::ostream &os, const ReplayBuffer &replayBuffer );

    private:
        PacketSPDeque _packetSPDeque;

        omnetpp::SimTime _recordStartTime;
        omnetpp::SimTime _lastRecordTime;
        double _recordDuration;
        omnetpp::SimTime _recordEndTime;

        unsigned int _serialNo;
        bool _playing;

    public:
        ReplayBuffer( void ) : _serialNo( 0 ), _playing( false ) {}

        void setRecordDuration( double recordDuration ) {
            _recordStartTime = omnetpp::simTime();
            _lastRecordTime = _recordStartTime;
            _recordDuration = recordDuration;
            _recordEndTime = _recordStartTime + _recordDuration;
        }

    private:
        void addPacket(inet::Packet *packet) {

            omnetpp::SimTime currentSimTime = omnetpp::simTime();
            packet->setTimestamp( currentSimTime - _lastRecordTime );
            _lastRecordTime = currentSimTime;

            _packetSPDeque.push_back( PacketSP(packet->dup()) );
        }

    public:
        void addPacketSerial(inet::Packet *packet) {

            if ( omnetpp::simTime() > _recordEndTime || _playing  ) {
                return;
            }

            addPacket(packet);
        }

        void addPacketRandom(inet::Packet *packet) {

            addPacket(packet);
        }

        bool empty( void ) const {
            return _packetSPDeque.empty();
        }

        void setPlaying( bool playing ) {
            _playing = _packetSPDeque.empty() ? false : playing;
        }

        void setPlayingRandom( bool playing ) {
            _playing = playing;
        }

        bool getPlaying( void ) {
            if ( _packetSPDeque.empty() ) _playing = false;
            return _playing;
        }

        bool getPlayingRandom( void ) {
            return _playing;
        }

        double getRecordDuration( void ) const {
            return _recordDuration;
        }

        omnetpp::SimTime getRecordEndTime( void ) const {
            return _recordEndTime;
        }

        omnetpp::SimTime getNextTimeOffset( void ) const {
            return _packetSPDeque.empty() ? -1 : _packetSPDeque[ _serialNo ]->getTimestamp();
        }

        PacketSP getSerial( void ) {
            if ( _packetSPDeque.empty() ) {
                return PacketSP();
            }
            PacketSP packetSP = _packetSPDeque[ _serialNo ];
            if ( ++_serialNo >= _packetSPDeque.size() ) {
                _serialNo = 0;
            }
            return packetSP;
        }

        PacketSP getRandom( void );

        void reset( double recordDuration ) {
            _recordStartTime = omnetpp::simTime();
            _recordDuration = recordDuration;
            _recordEndTime = _recordStartTime + _recordDuration;
            _packetSPDeque.clear();
            _serialNo = 0;
            _playing = false;
        }
    };

    typedef boost::shared_ptr< ReplayBuffer > ReplayBufferSP;

    typedef std::map< NetworkAddressSDPair, ReplayBufferSP, NetworkAddressSDPairComparator > NetworkAddressReplayBufferSPMap;
    typedef std::list< ReplayBufferSP > ReplayBufferSPList;

private:
    bool _hasSerialReplayBufferSPMap;
    NetworkAddressReplayBufferSPMap _serialReplayBufferSPMap;

    bool _hasRandomReplayBufferSPMap;
    NetworkAddressReplayBufferSPMap _randomReplayBufferSPMap;

public:
    //
    // CODE FOR REPLAY ATTACK
    //
    ReplayBufferSPList getSerialReplayBufferSPList( unsigned int sourceIPv4Address, unsigned int destinationIPv4Address );

    ReplayBufferSP &getSerialReplayBufferSP( const NetworkAddress &sourceNetworkAddress, const NetworkAddress &destinationNetworkAddress ) {

        _hasSerialReplayBufferSPMap = true;

        ReplayBufferSP &replayBufferSP = _serialReplayBufferSPMap[ NetworkAddressSDPair( sourceNetworkAddress, destinationNetworkAddress ) ];
        if ( replayBufferSP == 0 ) {

            // replayBufferSP IS A REFERENCE, SO SETTING IT PLACES IT IN THE _serialReplayBufferMap
            replayBufferSP = ReplayBufferSP( new ReplayBuffer() );

        }

        return replayBufferSP;
    }

    void removeSerialReplayBufferSP( const NetworkAddress &sourceNetworkAddress, const NetworkAddress &destinationNetworkAddress );


    //
    // CODE FOR OUT-OF-ORDER-PACKETS ATTACK
    //
    ReplayBufferSPList getRandomReplayBufferSPList( unsigned int sourceIPv4Address, unsigned int destinationIPv4Address );

    ReplayBufferSP &getRandomReplayBufferSP( const NetworkAddress &sourceNetworkAddress, const NetworkAddress &destinationNetworkAddress ) {
        _hasRandomReplayBufferSPMap = true;
        ReplayBufferSP &replayBufferSP = _randomReplayBufferSPMap[ NetworkAddressSDPair( sourceNetworkAddress, destinationNetworkAddress ) ];
        if ( replayBufferSP == 0 ) {
            replayBufferSP = ReplayBufferSP( new ReplayBuffer() );
        }
        return replayBufferSP;
    }

    void removeRandomReplayBufferSP( const NetworkAddress &sourceNetworkAddress, const NetworkAddress &destinationNetworkAddress );

    //
    // CODE FOR NODE DELAY ATTACK
    //
    bool _nodeDelayed;
    double _nodeDelayMean;
    double _nodeDelayStdDev;

    static omnetpp::simsignal_t iPv4PromiscousPacket;

    CPSWTIpv4():
        inet::Ipv4(),
        _nodeAttack( false ),
        _hasListeners( false ),
        _hasFilters( false ),
        _hasNetworkAttack( false ),
        _hasSerialReplayBufferSPMap( false ),
        _hasRandomReplayBufferSPMap( false ),
        _nodeDelayed( false ),
        _nodeDelayMean( 0.0 ),
        _nodeDelayStdDev( 0.0 ) { }

    virtual ~CPSWTIpv4() {}

protected:
    void recordNetworkInformation( void );


    virtual void receiveSignal(omnetpp::cComponent *source, omnetpp::simsignal_t signalID, omnetpp::cObject *obj, omnetpp::cObject *details) override;
    virtual void initialize( int stage ) override;
    // MORE SPECIFIC METHODS ARE USED NOW:
    // handleMessage IS DEFINED IN inet::OperationalBase CLASS
    //     inet::OperationalBase::handleMessage ROUTES MESSAGES TO THE handleMessageWhenUp METHOD
    // handleMessageWhenUp IS DEFINED IN THE inet::Ipv4 CLASS
    //     inet::Ipv4::handleMessageWhenUp ROUTES MESSAGE TO THE:
    //     * handleRequest FOR Request MESSAGES (RECEIVED THROUGH THE "transportIn"
    //     * handlePacketFromHL FOR Packet'S COMING FROM HIGHER LEVELS IN THE IP PROTOCOL STACK (I.E. FROM "transportIn" GATE).
    //     * handleIncomingDatagram FOR Packet'S COMING FROM LOWER LEVELS IN THE IP PROTOCOL STACK (I.E. FROM queueIn GATE).
//    virtual void handleMessage( omnetpp::cMessage *msg ) override;
    virtual void handleMessageWhenUp(omnetpp::cMessage *msg) override;
    virtual void routeUnicastPacket(inet::Packet *packet) override;
};

std::ostream &operator<<( std::ostream &os, const CPSWTIpv4::ReplayBufferSP &replayBufferSP );

#endif
