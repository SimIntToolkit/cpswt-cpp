/*
 * Certain portions of this software are Copyright (C) 2006-present
 * Vanderbilt University, Institute for Software Integrated Systems.
 *
 * Certain portions of this software are contributed as a public service by
 * The National Institute of Standards and Technology (NIST) and are not
 * subject to U.S. Copyright.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above Vanderbilt University copyright notice, NIST contribution
 * notice and this permission and disclaimer notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE. THE AUTHORS OR COPYRIGHT HOLDERS SHALL NOT HAVE
 * ANY OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS,
 * OR MODIFICATIONS.
 */

#include <NodeAttackTest.h>
#include <messages/NodeAttackMsg_m.h>

#include <inet/common/packet/chunk/cPacketChunk.h>

Define_Module(NodeAttackTest);


NetworkPacketSP NodeAttackTest::createNetworkPacketSP(const std::string &senderHostName, const std::string &receiverHostName) {
    NetworkPacketSP networkPacketSP(new NetworkPacket());

    networkPacketSP->set_packetType("NetworkPacket");
    networkPacketSP->set_data("data");
    networkPacketSP->set_numBytes(1024);

    networkPacketSP->set_senderHost(senderHostName);
    networkPacketSP->set_senderHostApp(getAppName());
    networkPacketSP->set_senderAppIndex(0);

    networkPacketSP->set_receiverHost(receiverHostName);
    networkPacketSP->set_receiverHostApp(getAppName());
    networkPacketSP->set_receiverAppIndex(0);
    networkPacketSP->set_receiverAppInterface("eth");

    return networkPacketSP;
}

InteractionMsg *NodeAttackTest::createInteractionMsgPtr(NetworkPacketSP &networkPacketSP, int uniqueNumber) {
    InteractionMsg *interactionMsgPtr = new InteractionMsg( getInteractionMessageLabel().c_str() );

    interactionMsgPtr->setToHLA( true );
    interactionMsgPtr->setMessageNo( uniqueNumber );
    interactionMsgPtr->setInteractionRootSP( networkPacketSP );
    interactionMsgPtr->setTimestamp( omnetpp::simTime().dbl() );
    interactionMsgPtr->setByteLength(networkPacketSP->get_numBytes());

    return interactionMsgPtr;
}

inet::Packet *NodeAttackTest::createPacket(InteractionMsg *interactionMsgPtr) {
    auto c_packetChunk = inet::makeShared<inet::cPacketChunk>(interactionMsgPtr);
    inet::Packet *packet = new inet::Packet(getInteractionMessageLabel().c_str(), c_packetChunk);

    return packet;
}

int NodeAttackTest::getMessageNumber(inet::Packet *packetPtr) {
    auto c_packetChunkPtr = packetPtr->peekAtFront<inet::cPacketChunk>();
    inet::cPacket *c_packetPtr = c_packetChunkPtr->getPacket();

    InteractionMsg *interactionMsg = dynamic_cast< InteractionMsg * >( c_packetPtr );

    return interactionMsg == nullptr ? -1 : interactionMsg->getMessageNo();
}

int NodeAttackTest::sendPacket(const std::string &senderHostName, const std::string &receiverHostName) {

    int uniqueNumber = AttackCoordinator::getUniqueNo();

    NetworkPacketSP networkPacketSP = createNetworkPacketSP(senderHostName, receiverHostName);

    InteractionMsg *interactionMsgPtr = createInteractionMsgPtr(networkPacketSP, uniqueNumber);

    inet::Packet *packet = createPacket(interactionMsgPtr);

    std::string hostName = networkPacketSP->get_senderHost();
    std::string appName = networkPacketSP->get_senderHostApp();
    int appIndex = networkPacketSP->get_senderAppIndex();

    cModule *udpAppWrapperModule = AttackCoordinator::getSingleton().getAppSpecModule( hostName, appName, appIndex );
    if ( udpAppWrapperModule != 0 ) {
        if (_nodeAttackInProgress && senderHostName == _host1Name) {
            std::cout << "Sending packet to \"" << senderHostName << "\", which will try to send it to \"" << receiverHostName << "\"" << std::endl;
            std::cout << "However, this should fail due to a node attack." << std::endl;
        } else {
            std::cout << "Sending packet to \"" << senderHostName << "\", which should send it to \"" << receiverHostName << "\"" << std::endl;
            std::cout << "\"" << receiverHostName << "\" should send the packet back to this test" << std::endl;
        }
        sendDirect( packet, udpAppWrapperModule, "hlaIn" );
    } else {
        std::cerr << "WARNING: AttackCoordinator:  could not find module corresponding to (hostname,appName) = (" <<
         hostName << "," << appName << ")" << std::endl;
        std::cerr << "Current modules are: " << std::endl;
        std::cerr << AttackCoordinator::getSingleton().listAppSpecProperties();
        std::cerr << std::endl;
    }

    return uniqueNumber;
}

void NodeAttackTest::checkPacket(omnetpp::cMessage *msg, const std::string &senderHostName, const std::string &receiverHostName, int messageNumber) {

    inet::Packet *packet = dynamic_cast<inet::Packet *>(msg);
    if (packet == nullptr) {
        delete packet;
        std::cerr << "Test failed.  Did not receive packet from \"" << senderHostName << "\"" << std::endl;
        exit(1);
    }

    omnetpp::cModule *receiverModule = packet->getSenderModule()->getParentModule();
    std::string receiverModuleName(receiverModule->getFullPath());
    if (receiverModuleName != receiverHostName) {
        delete packet;
        std::cerr << "Test failed.  Received packet from host \"" << receiverModuleName << "\", should have been \"" << receiverHostName << "\"" << std::endl;
        exit(1);
    }

    std::cout << "Received packet from \"" << receiverHostName << "\"!" << std::endl;

    int receivedMessageNumber = getMessageNumber(packet);

    if (receivedMessageNumber != messageNumber) {
        std::cerr << "Test failed.  Received packet had incorrect message number (" << receivedMessageNumber << ") -- should be (" << messageNumber << ")" << std::endl;
        delete packet;
        exit(1);
    } else {
        std::cout << "Received packet had correct message number {" << messageNumber << ")" << std::endl;
        delete packet;
    }

}

void NodeAttackTest::setNodeAttack(bool attackInProgress) {

    _nodeAttackInProgress = attackInProgress;

    const std::string attackAction = attackInProgress ? "Starting" : "Stopping";

    std::cout << attackAction << " node attack on \"" << _router1Name << "\" ..." << std::endl;

    NodeAttackMsg *nodeAttackMsg = new NodeAttackMsg();
    nodeAttackMsg->setAttackInProgress(attackInProgress);

    omnetpp::cModule *router1Module = AttackCoordinator::getSingleton().getIPModule(_router1Name);
    sendDirect(nodeAttackMsg, router1Module, "hlaIn");
}

void NodeAttackTest::initialize(int stage) {

    if (stage == inet::INITSTAGE_LAST) {
        scheduleAt(omnetpp::simTime(), _keepAliveMsg);
    }

}

void NodeAttackTest::handleMessage(omnetpp::cMessage *msg) {

    if (msg == _keepAliveMsg) {
        sendKeepAliveMsg();
        if (_stateCounter != 0) {
            return;
        }
    }

    static int uniqueNumber = 0; // GLOBAL OVER IFS BELOW
    if (_stateCounter == 0) {
        uniqueNumber = sendPacket(_host1Name, _host3Name);

        scheduleAt(omnetpp::simTime() + _waitSeconds, _timingMsg);
        ++_stateCounter;
        return;
    }

    if (_stateCounter == 1) {

        if (msg == _timingMsg) {
            std::cerr << "Test failed.  Packet from \"" << _host1Name << "\" to \"" << _host3Name << "\" not received in allotted time (" << _waitSeconds << "s)" << std::endl;
            exit(1);
        }
        cancelEvent(_timingMsg);

        checkPacket(msg, _host1Name, _host3Name, uniqueNumber);

        setNodeAttack(true);

        uniqueNumber = sendPacket(_host1Name, _host3Name);

        scheduleAt(omnetpp::simTime() + _waitSeconds, _timingMsg);
        ++_stateCounter;
        return;
    }

    if (_stateCounter == 2) {
        if (msg != _timingMsg) {
            std::cerr << "Test failed.  Packet from \"" << _host1Name << "\" to \"" << _host3Name << "\" was apparently received and should not have been" << std::endl;
            exit(1);
        }
        std::cout << "Packet sent from \"" << _host1Name << "\" to \"" << _host3Name << "\" dropped as expected." << std::endl;

        uniqueNumber = sendPacket(_host2Name, _host3Name);

        scheduleAt(omnetpp::simTime() + _waitSeconds, _timingMsg);
        ++_stateCounter;
        return;
    }

    if (_stateCounter == 3) {

        if (msg == _timingMsg) {
            std::cerr << "Test failed.  Packet from \"" << _host2Name << "\" to \"" << _host3Name << "\" not received in allotted time (" << _waitSeconds << "s)" << std::endl;
            exit(1);
        }
        cancelEvent(_timingMsg);

        checkPacket(msg, _host2Name, _host3Name, uniqueNumber);

        setNodeAttack(false);

        uniqueNumber = sendPacket(_host1Name, _host3Name);

        scheduleAt(omnetpp::simTime() + _waitSeconds, _timingMsg);
        ++_stateCounter;
        return;
    }

    if (_stateCounter == 4) {

        if (msg == _timingMsg) {
            std::cerr << "Test failed.  Packet from \"" << _host1Name << "\" to \"" << _host3Name << "\" not received in allotted time (" << _waitSeconds << "s)" << std::endl;
            exit(1);
        }
        cancelEvent(_timingMsg);

        checkPacket(msg, _host1Name, _host3Name, uniqueNumber);

        std::cout << "TEST PASSED" << std::endl;
        cancelEvent(_keepAliveMsg);
        return;
    }

}


