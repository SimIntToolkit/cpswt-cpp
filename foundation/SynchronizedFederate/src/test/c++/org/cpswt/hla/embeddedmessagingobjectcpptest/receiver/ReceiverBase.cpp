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



#include "org/cpswt/hla/embeddedmessagingobjectcpptest/receiver/ReceiverBase.hpp"


namespace org {
 namespace cpswt {
  namespace hla {
   namespace embeddedmessagingobjectcpptest {
    namespace receiver {


// constructor
void ReceiverBase::init() {
    createRTI();
    joinFederation();

    enableTimeConstrained();
    enableTimeRegulation(getLookahead());

    // INTERACTION SUBSCRIPTIONS

    ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::EmbeddedMessaging_p::Receiver::subscribe_interaction(getRTI());

    // OBJECT SUBSCRIPTIONS
    ::org::cpswt::hla::ObjectRoot_p::TestObject::subscribe_CharValue_attribute();
    ::org::cpswt::hla::ObjectRoot_p::TestObject::subscribe_DoubleValue_attribute();
    ::org::cpswt::hla::ObjectRoot_p::TestObject::subscribe_FloatValue_attribute();
    ::org::cpswt::hla::ObjectRoot_p::TestObject::subscribe_IntValue_attribute();
    ::org::cpswt::hla::ObjectRoot_p::TestObject::subscribe_LongValue_attribute();
    ::org::cpswt::hla::ObjectRoot_p::TestObject::subscribe_ShortValue_attribute();
    ::org::cpswt::hla::ObjectRoot_p::TestObject::subscribe_StringValue_attribute();
    ::org::cpswt::hla::ObjectRoot_p::TestObject::subscribe_object(getRTI());
}

ReceiverBase::ReceiverBase(FederateConfig *federateConfig): Super(federateConfig) {
    init();
}

void ReceiverBase::receiveInteraction(
  RTI::InteractionClassHandle interactionClassHandle,
  const RTI::ParameterHandleValuePairSet& parameterHandleValuePairSet,
  const char *userSuppliedTag
) throw (
  RTI::InteractionClassNotKnown,
  RTI::InteractionParameterNotKnown,
  RTI::FederateInternalError
) {
    if (getMoreATRs()) {
        ::org::cpswt::hla::InteractionRoot::SP interactionRootSP =
          ::org::cpswt::hla::InteractionRoot::create_interaction(
            interactionClassHandle, parameterHandleValuePairSet
          );

        C2WInteractionRoot::SP c2wInteractionRootSP =
          boost::dynamic_pointer_cast<C2WInteractionRoot>(interactionRootSP);
        if (c2wInteractionRootSP) {
            // Filter interaction if src/origin fed requirements (if any) are not met
            if ( _subscribedInteractionFilter.filterC2WInteraction( getFederateId(), c2wInteractionRootSP ) ) {
                return;
            }
        }
        Super::receiveInteraction(interactionClassHandle, parameterHandleValuePairSet, userSuppliedTag);
    }
}

void ReceiverBase::receiveInteraction(
  RTI::InteractionClassHandle interactionClassHandle,
  const RTI::ParameterHandleValuePairSet &parameterHandleValuePairSet,
  const RTI::FedTime &fedTime,
  const char *userSuppliedTag,
  RTI::EventRetractionHandle eventRetractionHandle
) throw (
  RTI::InteractionClassNotKnown,
  RTI::InteractionParameterNotKnown,
  RTI::InvalidFederationTime,
  RTI::FederateInternalError
) {
    if (getMoreATRs()) {
        ::org::cpswt::hla::InteractionRoot::SP interactionRootSP =
          ::org::cpswt::hla::InteractionRoot::create_interaction(
            interactionClassHandle, parameterHandleValuePairSet, fedTime
          );

        C2WInteractionRoot::SP c2wInteractionRootSP =
          boost::dynamic_pointer_cast<C2WInteractionRoot>( interactionRootSP );
        if (c2wInteractionRootSP) {
            // Filter interaction if src/origin fed requirements (if any) are not met
            if ( _subscribedInteractionFilter.filterC2WInteraction( getFederateId(), c2wInteractionRootSP ) ) {
                return;
            }
        }
        Super::receiveInteraction(
            interactionClassHandle, parameterHandleValuePairSet, fedTime, userSuppliedTag, eventRetractionHandle
        );
    }
}
    } // NAMESPACE "receiver"
   } // NAMESPACE "embeddedmessagingobjectcpptest"
  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"
