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

#ifndef ORG_CPSWT_HLA_EMBEDDEDMESSAGINGOBJECTCPPTEST_RECEIVER_CLASS_CLASS
#define ORG_CPSWT_HLA_EMBEDDEDMESSAGINGOBJECTCPPTEST_RECEIVER_CLASS_CLASS


#include "edu/vanderbilt/vuisis/cpswt/hla/embeddedmessagingobjectcpptest/receiver/ReceiverBase.hpp"
#include "FederateConfigParser.h"

#include <boost/shared_ptr.hpp>

namespace edu {
 namespace vanderbilt {
  namespace vuisis {
   namespace cpswt {
    namespace hla {
     namespace embeddedmessagingobjectcpptest {
      namespace receiver {

class Receiver: public ReceiverBase {

using InteractionRoot = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot;
using C2WInteractionRoot = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot;

//    private final static Logger log = LogManager.getLogger();
public:
    typedef ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject TestObject;
    typedef boost::shared_ptr<TestObject> TestObjectSP;
private:
    double m_currentTime;

public:
    Receiver(FederateConfig *federateConfig);

    virtual ~Receiver() throw (RTI::FederateInternalError) {}

private:

    TestObjectSP _testObjectSP;

    void handleObjectClass_ObjectRoot_TestObject(ObjectRoot::SP objectRootSP);

    void checkReceivedSubscriptions();

public:
    typedef ReceiverBase Super;

    class ReceiverATRCallback : public ATRCallback {
        private:
            Receiver &m_federateInstance;
        public:
            ReceiverATRCallback(Receiver &federateInstance): m_federateInstance(federateInstance) {}

            virtual void execute( void ) {
                m_federateInstance.execute();
            }

            virtual SP clone() {
                return SP(new ReceiverATRCallback(*this));
            }
    };

    TestObjectSP getTestObjectSP() {
        return _testObjectSP;
    }

    void initialize();
    void execute();
};
      } // NAMESPACE "receiver"
     } // NAMESPACE "embeddedmessagingobjectcpptest"
    } // NAMESPACE "hla"
   } // NAMESPACE "cpswt"
  } // NAMESPACE "vuisis"
 } // NAMESPACE "vanderbilt"
} // NAMESPACE "edu"

#endif // ORG_CPSWT_HLA_EMBEDDEDMESSAGINGOBJECTCPPTEST_RECEIVER_CLASS_CLASS
