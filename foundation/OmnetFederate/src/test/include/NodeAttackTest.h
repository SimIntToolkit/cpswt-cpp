#include <omnetpp.h>
#include <inet/common/packet/Packet.h>
#include <inet/common/INETDefs.h>
#include <AttackCoordinator.h>

#include <NetworkPacket.hpp>
#include <messages/InteractionMsg_m.h>

class NodeAttackTest: public omnetpp::cSimpleModule {

public:
    static const std::string &getAppName(void) {
        static const std::string appName("BasicUdpAppWrapper");
        return appName;
    }
    static const std::string &getInteractionMessageLabel(void) {
        static const std::string interactionMessageLabel("BasicUdpAppWrapper");
        return interactionMessageLabel;
    }

    static NetworkPacketSP createNetworkPacketSP(const std::string &senderHostName, const std::string &receiverHostName);
    static InteractionMsg *createInteractionMsgPtr(NetworkPacketSP &networkPacketSP, int uniqueNumber);
    static inet::Packet *createPacket(InteractionMsg *interactionMsgPtr);

    static int getMessageNumber(inet::Packet *packetPtr);

private:
    int _stateCounter;
    omnetpp::cMessage *_keepAliveMsg;
    omnetpp::cMessage *_timingMsg;

    bool _nodeAttackInProgress;
    const std::string _interactionMessageLabel;
    const std::string _appName;
    const std::string _host1Name;
    const std::string _host2Name;
    const std::string _host3Name;
    const std::string _router1Name;

    const int _waitSeconds;

public:
    NodeAttackTest(void) :
        _stateCounter(0),
        _keepAliveMsg(  new omnetpp::cMessage( "keepAlive" )  ),
        _timingMsg(  new omnetpp::cMessage( "timing" )  ),
        _nodeAttackInProgress(false),
        _interactionMessageLabel(getInteractionMessageLabel()),
        _appName(getAppName()),
        _host1Name("NodeAttackTestNetwork.host1"),
        _host2Name("NodeAttackTestNetwork.host2"),
        _host3Name("NodeAttackTestNetwork.host3"),
        _router1Name("NodeAttackTestNetwork.router1"),
        _waitSeconds(2) { }

    virtual ~NodeAttackTest() {
        if (_keepAliveMsg != nullptr) {
            cancelAndDelete(_keepAliveMsg);
            _keepAliveMsg = nullptr;
        }
        if (_timingMsg != nullptr) {
            cancelAndDelete(_timingMsg);
            _timingMsg = nullptr;
        }
    }
    int sendPacket(const std::string &senderHostName, const std::string &receiverHostName);
    void checkPacket(omnetpp::cMessage *msg, const std::string &senderHostName, const std::string &receiverHostName, int messageNumber);
    void setNodeAttack(bool attackInProgress);

protected:
    virtual int numInitStages() const override { return inet::NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessage(omnetpp::cMessage *msg) override;

private:
    void sendKeepAliveMsg() {
        scheduleAt(omnetpp::simTime() + 2, _keepAliveMsg);
    }

};