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

#include "edu/vanderbilt/vuisis/cpswt/hla/helloworldcpp/pingcounter/PingCounter.hpp"


namespace edu {
 namespace vanderbilt {
  namespace vuisis {
   namespace cpswt {
    namespace hla {
     namespace helloworldcpp {
      namespace pingcounter {

PingCounter::PingCounter(FederateConfig *federateConfig): Super(federateConfig) {
}

void PingCounter::handleObjectClass_ObjectRoot_PingCounter(ObjectRoot::SP objectRootSP) {
    ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::PingCounter::SP pingCounterSP =
        boost::dynamic_pointer_cast<::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::PingCounter>( objectRootSP );

    static int counter = 0;
    if (++counter >= 5) {
        exitCondition = true;
    }

    std::cout << "PingCounter: ping count is now " << pingCounterSP->get_pingCount() << std::endl;
}

void PingCounter::checkReceivedSubscriptions() {

    ObjectReflector::SP reflectorSP;
    while (reflectorSP = getNextObjectReflectorSP()) {
        reflectorSP->reflect();
        ObjectRoot::SP objectRootSP = reflectorSP->getObjectRootSP();

        if (objectRootSP->isInstanceHlaClassDerivedFromHlaClass("ObjectRoot.PingCounter")) {
            handleObjectClass_ObjectRoot_PingCounter(objectRootSP);
            continue;
        }

        std::cerr << "unhandled object reflection: " << objectRootSP->getInstanceHlaClassName() << std::endl;
    }

}

void PingCounter::initialize( void ) {
    m_currentTime = 0;
    if ( this->get_IsLateJoiner() ) {
        m_currentTime = getLBTS() - getLookahead();
        disableTimeRegulation();
    }
    PingCounterATRCallback advanceTimeRequest(*this);
    putAdvanceTimeRequest(m_currentTime, advanceTimeRequest);
    if ( !this->get_IsLateJoiner() ) {
        readyToPopulate();
        readyToRun();
    }
}

void PingCounter::execute() {

    checkReceivedSubscriptions();
    // TODO update registered object instances

    if (!exitCondition) {
        m_currentTime += getStepSize();
        PingCounterATRCallback advanceTimeRequest( *this );
        putAdvanceTimeRequest( m_currentTime, advanceTimeRequest );
    }
}
      } // NAMESPACE "pingcounter"
     } // NAMESPACE "helloworldcpp"
    } // NAMESPACE "hla"
   } // NAMESPACE "cpswt"
  } // NAMESPACE "vuisis"
 } // NAMESPACE "vanderbilt"
} // NAMESPACE "edu"


int main( int argc, char *argv[] ) {
    FederateConfigParser *configParser = new FederateConfigParser();
    FederateConfig *config = configParser->parseArgs( argc, argv );
    std::cout << "Creating ::edu::vanderbilt::vuisis::cpswt::hla::helloworldcpp::pingcounter::PingCounter instance" << std::endl;
    ::edu::vanderbilt::vuisis::cpswt::hla::helloworldcpp::pingcounter::PingCounter federateInstance( config );
    federateInstance.initialize();
    std::cout << "Running ::edu::vanderbilt::vuisis::cpswt::hla::helloworldcpp::pingcounter::PingCounter instance" << std::endl;
    federateInstance.run();
    return 0;
}
