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

#include "edu/vanderbilt/vuisis/cpswt/hla/embeddedmessagingobjecttestcpp/receiver/Receiver.hpp"


namespace edu {
 namespace vanderbilt {
  namespace vuisis {
   namespace cpswt {
    namespace hla {
     namespace embeddedmessagingobjecttestcpp {
      namespace receiver {

Receiver::Receiver(FederateConfig *federateConfig): Super(federateConfig), state(0) {
}

void Receiver::handleObjectClass_ObjectRoot_TestObject(ObjectRoot::SP objectRootSP) {
    ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject::SP testObject0SP =
        boost::dynamic_pointer_cast<::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject>( objectRootSP );

    _testObjectSP = testObject0SP;
}

void Receiver::checkReceivedSubscriptions() {

    InteractionRoot::SP interactionRootSP;
    while (interactionRootSP = getNextInteraction()) {

        std::cerr << "unhandled interaction " << interactionRootSP->getInstanceHlaClassName() << std::endl;
    }

    ObjectReflector::SP reflectorSP;
    while (reflectorSP = getNextObjectReflectorSP()) {
        reflectorSP->reflect();
        ObjectRoot::SP objectRootSP = reflectorSP->getObjectRootSP();

        if (objectRootSP->isInstanceHlaClassDerivedFromHlaClass("ObjectRoot.TestObject")) {
            handleObjectClass_ObjectRoot_TestObject(objectRootSP);
            continue;
        }

        std::cerr << "unhandled object reflection: " << objectRootSP->getInstanceHlaClassName() << std::endl;
    }

}

void Receiver::initialize( void ) {
    m_currentTime = 0;
    ReceiverATRCallback advanceTimeRequest(*this);
    putAdvanceTimeRequest(m_currentTime, advanceTimeRequest);
}

void Receiver::execute() {

    checkReceivedSubscriptions();

    // state == 0 PUT IN REQUEST FOR TIME = 1
    if (state == 0) {
        m_currentTime = getStepSize();
    }

    // state == 1 MAKE DIRECT UPDATE OCCUR -- NO NEED TO UPDATE TIME AS TIME == 1 AND DIRECT UPDATE WAS AT 0.5
    // state == 2 MAKE INDIRECT UPDATE OCCUR -- NO NEED TO UPDATE TIME AS TIME == 1 AND DIRECT UPDATE WAS AT 0.5

    if (state < 3) {
        ReceiverATRCallback advanceTimeRequest(*this);
        putAdvanceTimeRequest(m_currentTime, advanceTimeRequest);
    }

    ++state;
}
      } // NAMESPACE "receiver"
     } // NAMESPACE "embeddedmessagingobjecttestcpp"
    } // NAMESPACE "hla"
   } // NAMESPACE "cpswt"
  } // NAMESPACE "vuisis"
 } // NAMESPACE "vanderbilt"
} // NAMESPACE "edu"
