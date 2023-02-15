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

#ifndef ORG_CPSWT_HLA_EMBEDDEDMESSAGINGOBJECTTESTCPP_SENDER_CLASS_CLASS
#define ORG_CPSWT_HLA_EMBEDDEDMESSAGINGOBJECTTESTCPP_SENDER_CLASS_CLASS


#include "edu/vanderbilt/vuisis/cpswt/hla/embeddedmessagingobjecttestcpp/sender/SenderBase.hpp"
#include "FederateConfigParser.h"


namespace edu {
 namespace vanderbilt {
  namespace vuisis {
   namespace cpswt {
    namespace hla {
     namespace embeddedmessagingobjecttestcpp {
      namespace sender {

class Sender: public SenderBase {

using InteractionRoot = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot;
using C2WInteractionRoot = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot;

public:
    typedef ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject TestObject;
//    private final static Logger log = LogManager.getLogger();

private:
    double m_currentTime;

    TestObject TestObject_0;

public:
    Sender(FederateConfig *federateConfig);

    virtual ~Sender() throw (RTI::FederateInternalError) {}

private:

public:
    typedef SenderBase Super;

    class SenderATRCallback : public ATRCallback {
        private:
            Sender &m_federateInstance;
        public:
            SenderATRCallback(Sender &federateInstance): m_federateInstance(federateInstance) {}

            virtual void execute( void ) {
                m_federateInstance.execute();
            }

            virtual SP clone() {
                return SP(new SenderATRCallback(*this));
            }
    };

    TestObject &getTestObject() {
        return TestObject_0;
    }

    void initialize();
    void execute();
};
      } // NAMESPACE "sender"
     } // NAMESPACE "embeddedmessagingobjecttestcpp"
    } // NAMESPACE "hla"
   } // NAMESPACE "cpswt"
  } // NAMESPACE "vuisis"
 } // NAMESPACE "vanderbilt"
} // NAMESPACE "edu"

#endif // ORG_CPSWT_HLA_EMBEDDEDMESSAGINGOBJECTTESTCPP_SENDER_CLASS_CLASS
