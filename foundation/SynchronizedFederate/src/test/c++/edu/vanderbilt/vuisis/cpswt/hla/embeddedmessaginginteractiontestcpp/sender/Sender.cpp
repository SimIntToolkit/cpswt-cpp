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

#include "edu/vanderbilt/vuisis/cpswt/hla/embeddedmessaginginteractiontestcpp/sender/Sender.hpp"


namespace edu {
 namespace vanderbilt {
  namespace vuisis {
   namespace cpswt {
    namespace hla {
     namespace embeddedmessaginginteractiontestcpp {
      namespace sender {

Sender::Sender(FederateConfig *federateConfig, int executeMethodNumber):
  Super(federateConfig), virtualFederateName1("VirtualFederate1"), virtualFederateName2("VirtualFederate2") {

    executeMethodPtr = executeMethodNumber == 0 ? &Sender::executeForProxyFederateInteractions :
      &Sender::executeForInteractionNetworkPropagation;

    TestInteraction_0.set_BoolValue1(false);
    TestInteraction_0.set_BoolValue2(true);
    TestInteraction_0.set_ByteValue(42);
    TestInteraction_0.set_CharValue('X');
    TestInteraction_0.set_DoubleValue(2.7181);
    TestInteraction_0.set_FloatValue(3.14f);
    TestInteraction_0.set_IntValue(1000000);
    TestInteraction_0.set_ShortValue(300);
    TestInteraction_0.set_LongValue(1000000000000000000L);

    Json::Value thingList(Json::arrayValue);
    thingList.append("this");
    thingList.append("that");
    thingList.append("other");
    TestInteraction_0.set_JSONValue(thingList);

    TestInteraction_0.set_StringValue("Hello");
    TestInteraction_0.set_actualLogicalGenerationTime(0.0);
    TestInteraction_0.set_federateFilter("");

    state = 0;
}

void Sender::handleInteractionClass_InteractionRoot_C2WInteractionRoot_TestInteraction(InteractionRoot::SP interactionRootSP) {
    TestInteraction::SP testInteractionSP = boost::dynamic_pointer_cast<TestInteraction>( interactionRootSP );

    _testInteractionSPList.push_back(testInteractionSP);
}

void Sender::checkReceivedSubscriptions() {

    InteractionRoot::SP interactionRootSP;
    while (interactionRootSP = getNextInteraction()) {
        if (interactionRootSP->isInstanceHlaClassDerivedFromHlaClass("InteractionRoot.C2WInteractionRoot.TestInteraction")) {

            handleInteractionClass_InteractionRoot_C2WInteractionRoot_TestInteraction(interactionRootSP);
            continue;
        }

        std::cerr << "unhandled interaction " << interactionRootSP->getInstanceHlaClassName() << std::endl;
    }

}

void Sender::initialize( void ) {
    m_currentTime = 0;
    SenderATRCallback advanceTimeRequest(*this);
    putAdvanceTimeRequest(m_currentTime, advanceTimeRequest);
}

void Sender::executeForProxyFederateInteractions() {
    if (state == 0) {
        addProxiedFederate(virtualFederateName1);
        addProxiedFederate(virtualFederateName2);

        // FIRST SENT-INTERACTION SHOULD BE SENT ON FIRST ADVANCE-TIME-REQUEST (TO 1 SEC)
        TestInteraction testInteraction;
        testInteraction.setProxiedFederateName(virtualFederateName2);

        sendInteraction(testInteraction, 0);

        m_currentTime += getStepSize();
        SenderATRCallback advanceTimeRequest(*this);
        putAdvanceTimeRequest(m_currentTime, advanceTimeRequest);

    } else if (state == 1) {
        // SEND QUEUED TIME-BASED-INTERACTIONS
        SenderATRCallback advanceTimeRequest(*this);
        putAdvanceTimeRequest(m_currentTime, advanceTimeRequest);

    } else if (state == 2) {

        deleteProxiedFederate(virtualFederateName1);
        deleteProxiedFederate(virtualFederateName2);

        checkReceivedSubscriptions();

        m_currentTime += getStepSize();
        SenderATRCallback advanceTimeRequest(*this);
        putAdvanceTimeRequest(m_currentTime, advanceTimeRequest);
    }

    ++state;

}

void Sender::executeForInteractionNetworkPropagation() {

    if (state == 0) {

        sendInteraction(TestInteraction_0, 0.5);

        sendInteraction(TestInteraction_0, 1.5);
        sendInteraction(TestInteraction_0, 1.6);
    }

    // AFTER 3 ITERATIONS, DON'T PUT ANYTHING ON THE ATRQueue TO LEAVE IT EMPTY
    // THE ATRQueue IS A STATIC DATA MEMBER OF THE SynchronizedFederate CLASS
    // AND SO CAN CAUSE TESTS TO STOMP ON ONE ANOTHER
    if (state < 3) {
    // TO GET THE FIRST INTERACTION (AT TIME 0.5) SENT
        m_currentTime += getStepSize();
        SenderATRCallback advanceTimeRequest(*this);
        putAdvanceTimeRequest(m_currentTime, advanceTimeRequest);
    }

    ++state;

    // FINAL EXECUTION, FOR WHICH THERE IS NO STATE
    // GETS LAST 2 INTERACTIONS SENT
}
      } // NAMESPACE "sender"
     } // NAMESPACE "embeddedmessaginginteractiontestcpp"
    } // NAMESPACE "hla"
   } // NAMESPACE "cpswt"
  } // NAMESPACE "vuisis"
 } // NAMESPACE "vanderbilt"
} // NAMESPACE "edu"
