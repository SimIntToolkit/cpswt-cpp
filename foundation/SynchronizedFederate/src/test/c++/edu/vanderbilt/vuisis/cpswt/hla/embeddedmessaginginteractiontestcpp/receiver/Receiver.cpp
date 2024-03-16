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

#include "edu/vanderbilt/vuisis/cpswt/hla/embeddedmessaginginteractiontestcpp/receiver/Receiver.hpp"


namespace edu {
 namespace vanderbilt {
  namespace vuisis {
   namespace cpswt {
    namespace hla {
     namespace embeddedmessaginginteractiontestcpp {
      namespace receiver {

Receiver::Receiver(FederateConfig *federateConfig, int executeMethodNumber): Super(federateConfig), state(0) {
    executeMethodPtr = executeMethodNumber == 0 ? &Receiver::executeForProxyFederateInteractions :
      &Receiver::executeForInteractionNetworkPropagation;
}

void Receiver::handleInteractionClass_InteractionRoot_C2WInteractionRoot_TestInteraction(InteractionRoot::SP interactionRootSP) {
    TestInteraction::SP testInteraction0SP = boost::dynamic_pointer_cast<TestInteraction>( interactionRootSP );

    _testInteractionSPList.push_back(testInteraction0SP);
}

void Receiver::checkReceivedSubscriptions() {

    InteractionRoot::SP interactionRootSP;
    while (interactionRootSP = getNextInteraction()) {
        if (interactionRootSP->isInstanceHlaClassDerivedFromHlaClass("InteractionRoot.C2WInteractionRoot.TestInteraction")) {

            handleInteractionClass_InteractionRoot_C2WInteractionRoot_TestInteraction(interactionRootSP);
            continue;
        }

        std::cerr << "unhandled interaction " << interactionRootSP->getInstanceHlaClassName() << std::endl;
    }

}

void Receiver::initialize( void ) {
    m_currentTime = 0;
    ReceiverATRCallback advanceTimeRequest(*this);
    putAdvanceTimeRequest(m_currentTime, advanceTimeRequest);
}

void Receiver::executeForProxyFederateInteractions() {
    checkReceivedSubscriptions();

    m_currentTime += getStepSize();
    ReceiverATRCallback advanceTimeRequest(*this);
    putAdvanceTimeRequest(m_currentTime, advanceTimeRequest);
}

void Receiver::executeForInteractionNetworkPropagation() {

    checkReceivedSubscriptions();

    if (state < 3) {
        m_currentTime += getStepSize();
        ReceiverATRCallback advanceTimeRequest(*this);
        putAdvanceTimeRequest(m_currentTime, advanceTimeRequest);
    }

    ++state;
}

      } // NAMESPACE "receiver"
     } // NAMESPACE "embeddedmessaginginteractiontestcpp"
    } // NAMESPACE "hla"
   } // NAMESPACE "cpswt"
  } // NAMESPACE "vuisis"
 } // NAMESPACE "vanderbilt"
} // NAMESPACE "edu"
