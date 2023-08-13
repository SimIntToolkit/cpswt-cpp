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

Sender::Sender(FederateConfig *federateConfig): Super(federateConfig) {
}

void Sender::initialize( void ) {
    m_currentTime = 0;
    if ( this->get_IsLateJoiner() ) {
        m_currentTime = getLBTS() - getLookahead();
        disableTimeRegulation();
    }
    SenderATRCallback advanceTimeRequest(*this);
    putAdvanceTimeRequest(m_currentTime, advanceTimeRequest);
    if ( !this->get_IsLateJoiner() ) {
        readyToPopulate();
        readyToRun();
    }
}

void Sender::execute() {

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

    sendInteraction(TestInteraction_0, 0.0);
}
      } // NAMESPACE "sender"
     } // NAMESPACE "embeddedmessaginginteractiontestcpp"
    } // NAMESPACE "hla"
   } // NAMESPACE "cpswt"
  } // NAMESPACE "vuisis"
 } // NAMESPACE "vanderbilt"
} // NAMESPACE "edu"
