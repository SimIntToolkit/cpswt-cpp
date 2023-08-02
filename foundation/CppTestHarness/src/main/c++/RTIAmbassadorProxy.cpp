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

#include "RTIAmbassadorProxy.hpp"

#if __cplusplus >= 201703L
#define MultiArgTuple17
#define Tuple17 noexcept
#define throw(...) __VA_OPT__(MultiArg)##Tuple17
#endif

namespace RTIProxy {


void RTIAmbassadorProxy::createFederationExecution (
  const char *executionName, // supplied C4
  const char *FED            // supplied C4
) throw (
  RTI::FederationExecutionAlreadyExists,
  RTI::CouldNotOpenFED,
  RTI::ErrorReadingFED,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) { }

// 4.3
void RTIAmbassadorProxy::destroyFederationExecution (
  const char *executionName // supplied C4
) throw (
  RTI::FederatesCurrentlyJoined,
  RTI::FederationExecutionDoesNotExist,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) { }

// 4.4
RTI::FederateHandle RTIAmbassadorProxy::joinFederationExecution (        // returned C3
  const char              *yourName,                    // supplied C4
  const char              *executionName,               // supplied C4
  RTI::RTIambassador::FederateAmbassadorPtr   federateAmbassadorReference   // supplied C1
) throw (
  RTI::FederateAlreadyExecutionMember,
  RTI::FederationExecutionDoesNotExist,
  RTI::CouldNotOpenFED,
  RTI::ErrorReadingFED,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) {
    return static_cast<RTI::FederateHandle>(0);
}

// 4.5
void RTIAmbassadorProxy::resignFederationExecution (
  RTI::ResignAction theAction // supplied C1
) throw (
  RTI::FederateOwnsAttributes,
  RTI::FederateNotExecutionMember,
  RTI::InvalidResignAction,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) { }

// 4.6
void RTIAmbassadorProxy::registerFederationSynchronizationPoint (
  const char *label,  // supplied C4
  const char *theTag  // supplied C4
) throw (
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

void RTIAmbassadorProxy::registerFederationSynchronizationPoint (
  const char                *label,    // supplied C4
  const char                *theTag,   // supplied C4
  const RTI::FederateHandleSet&   syncSet   // supplied C4
) throw (
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 4.9
void RTIAmbassadorProxy::synchronizationPointAchieved (
  const char *label  // supplied C4
) throw (
  RTI::SynchronizationPointLabelWasNotAnnounced,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 4.11
void RTIAmbassadorProxy::requestFederationSave (
  const char     *label,   // supplied C4
  const RTI::FedTime&  theTime  // supplied C4
) throw (
  RTI::FederationTimeAlreadyPassed,
  RTI::InvalidFederationTime,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

void RTIAmbassadorProxy::requestFederationSave (
  const char *label     // supplied C4
) throw (
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 4.13
void RTIAmbassadorProxy::federateSaveBegun () throw (
  RTI::SaveNotInitiated,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 4.14
void RTIAmbassadorProxy::federateSaveComplete () throw (
  RTI::SaveNotInitiated,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

void RTIAmbassadorProxy::federateSaveNotComplete () throw (
  RTI::SaveNotInitiated,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 4.16
void RTIAmbassadorProxy::requestFederationRestore (
  const char *label // supplied C4
) throw (
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 4.20
void RTIAmbassadorProxy::federateRestoreComplete () throw (
  RTI::RestoreNotRequested,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RTIinternalError
) { }

void RTIAmbassadorProxy::federateRestoreNotComplete () throw (
  RTI::RestoreNotRequested,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RTIinternalError
) { }

/////////////////////////////////////
// Declaration Management Services //
/////////////////////////////////////

// 5.2
void RTIAmbassadorProxy::publishObjectClass (
        RTI::ObjectClassHandle   theClass,      // supplied C1
  const RTI::AttributeHandleSet& attributeList  // supplied C4
) throw (
  RTI::ObjectClassNotDefined,
  RTI::AttributeNotDefined,
  RTI::OwnershipAcquisitionPending,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 5.3
void RTIAmbassadorProxy::unpublishObjectClass (
  RTI::ObjectClassHandle theClass  // supplied C1
) throw (
  RTI::ObjectClassNotDefined,
  RTI::ObjectClassNotPublished,
  RTI::OwnershipAcquisitionPending,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 5.4
void RTIAmbassadorProxy::publishInteractionClass (
  RTI::InteractionClassHandle theInteraction  // supplied C1
) throw (
  RTI::InteractionClassNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 5.5
void RTIAmbassadorProxy::unpublishInteractionClass (
  RTI::InteractionClassHandle theInteraction  // supplied C1
) throw (
  RTI::InteractionClassNotDefined,
  RTI::InteractionClassNotPublished,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 5.6
void RTIAmbassadorProxy::subscribeObjectClassAttributes (
  RTI::ObjectClassHandle theClass,                           // supplied C1
  const             RTI::AttributeHandleSet& attributeList, // supplied C4
  RTI::Boolean           active
) throw (
  RTI::ObjectClassNotDefined,
  RTI::AttributeNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
 ) { }

// 5.7
void RTIAmbassadorProxy::unsubscribeObjectClass (
  RTI::ObjectClassHandle theClass  // supplied C1
) throw (
  RTI::ObjectClassNotDefined,
  RTI::ObjectClassNotSubscribed,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 5.8
void RTIAmbassadorProxy::subscribeInteractionClass (
  RTI::InteractionClassHandle theClass, // supplied C1
  RTI::Boolean                active
) throw (
  RTI::InteractionClassNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::FederateLoggingServiceCalls,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 5.9
void RTIAmbassadorProxy::unsubscribeInteractionClass (
  RTI::InteractionClassHandle theClass  // supplied C1
) throw (
  RTI::InteractionClassNotDefined,
  RTI::InteractionClassNotSubscribed,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

////////////////////////////////
// Object Management Services //
////////////////////////////////

// 6.2
RTI::ObjectHandle RTIAmbassadorProxy::registerObjectInstance (  // returned C3
  RTI::ObjectClassHandle   theClass,        // supplied C1
  const char         *theObject        // supplied C4
) throw (
  RTI::ObjectClassNotDefined,
  RTI::ObjectClassNotPublished,
  RTI::ObjectAlreadyRegistered,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) {
    return static_cast<RTI::ObjectHandle>(0);
}

RTI::ObjectHandle RTIAmbassadorProxy::registerObjectInstance (  // returned C3
  RTI::ObjectClassHandle theClass           // supplied C1
) throw (
  RTI::ObjectClassNotDefined,
  RTI::ObjectClassNotPublished,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) {
    return static_cast<RTI::ObjectHandle>(0);
}

// 6.4
RTI::EventRetractionHandle RTIAmbassadorProxy::updateAttributeValues (       // returned C3
  RTI::ObjectHandle                       theObject,     // supplied C1
  const RTI::AttributeHandleValuePairSet& theAttributes, // supplied C4
  const RTI::FedTime&                     theTime,       // supplied C4
  const char                        *theTag         // supplied C4
) throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotDefined,
  RTI::AttributeNotOwned,
  RTI::InvalidFederationTime,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) {
  RTI::EventRetractionHandle eventRetractionHandle;
  eventRetractionHandle.theSerialNumber = 0;
  eventRetractionHandle.sendingFederate = 0;
  return eventRetractionHandle;
}

void RTIAmbassadorProxy::updateAttributeValues (
  RTI::ObjectHandle                       theObject,     // supplied C1
  const RTI::AttributeHandleValuePairSet& theAttributes, // supplied C4
  const char                        *theTag         // supplied C4
) throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotDefined,
  RTI::AttributeNotOwned,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 6.6
RTI::EventRetractionHandle RTIAmbassadorProxy::sendInteraction (              // returned C3
  RTI::InteractionClassHandle             theInteraction, // supplied C1
  const RTI::ParameterHandleValuePairSet& theParameters,  // supplied C4
  const RTI::FedTime&                     theTime,        // supplied C4
  const char                        *theTag)         // supplied C4
throw (
  RTI::InteractionClassNotDefined,
  RTI::InteractionClassNotPublished,
  RTI::InteractionParameterNotDefined,
  RTI::InvalidFederationTime,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) {
  RTI::EventRetractionHandle eventRetractionHandle;
  eventRetractionHandle.theSerialNumber = 0;
  eventRetractionHandle.sendingFederate = 0;
  return eventRetractionHandle;
}

void RTIAmbassadorProxy::sendInteraction (
        RTI::InteractionClassHandle       theInteraction, // supplied C1
  const RTI::ParameterHandleValuePairSet& theParameters,  // supplied C4
  const char                        *theTag          // supplied C4
) throw (
  RTI::InteractionClassNotDefined,
  RTI::InteractionClassNotPublished,
  RTI::InteractionParameterNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 6.8
RTI::EventRetractionHandle RTIAmbassadorProxy::deleteObjectInstance ( // returned C3
  RTI::ObjectHandle    theObject,                         // supplied C1
  const RTI::FedTime&  theTime,                           // supplied C4
  const char      *theTag                            // supplied C4
) throw (
  RTI::ObjectNotKnown,
  RTI::DeletePrivilegeNotHeld,
  RTI::InvalidFederationTime,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) {
  RTI::EventRetractionHandle eventRetractionHandle;
  eventRetractionHandle.theSerialNumber = 0;
  eventRetractionHandle.sendingFederate = 0;
  return eventRetractionHandle;
}

void RTIAmbassadorProxy::deleteObjectInstance (
        RTI::ObjectHandle    theObject,    // supplied C1
  const char           *theTag        // supplied C4
) throw (
  RTI::ObjectNotKnown,
  RTI::DeletePrivilegeNotHeld,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 6.10
void RTIAmbassadorProxy::localDeleteObjectInstance (
  RTI::ObjectHandle    theObject       // supplied C1
) throw (
  RTI::ObjectNotKnown,
  RTI::FederateOwnsAttributes,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 6.11
void RTIAmbassadorProxy::changeAttributeTransportationType (
        RTI::ObjectHandle             theObject,     // supplied C1
  const RTI::AttributeHandleSet&      theAttributes, // supplied C4
        RTI::TransportationHandle     theType        // supplied C1
) throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotDefined,
  RTI::AttributeNotOwned,
  RTI::InvalidTransportationHandle,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 6.12
void RTIAmbassadorProxy::changeInteractionTransportationType (
  RTI::InteractionClassHandle theClass, // supplied C1
  RTI::TransportationHandle   theType   // supplied C1
) throw (
  RTI::InteractionClassNotDefined,
  RTI::InteractionClassNotPublished,
  RTI::InvalidTransportationHandle,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 6.15
void RTIAmbassadorProxy::requestObjectAttributeValueUpdate (
        RTI::ObjectHandle        theObject,     // supplied C1
  const RTI::AttributeHandleSet& theAttributes  // supplied C4
) throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

void RTIAmbassadorProxy::requestClassAttributeValueUpdate (
        RTI::ObjectClassHandle   theClass,      // supplied C1
  const RTI::AttributeHandleSet& theAttributes  // supplied C4
) throw (
  RTI::ObjectClassNotDefined,
  RTI::AttributeNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

///////////////////////////////////
// Ownership Management Services //
///////////////////////////////////

// 7.2
void RTIAmbassadorProxy::unconditionalAttributeOwnershipDivestiture (
        RTI::ObjectHandle                  theObject,     // supplied C1
  const RTI::AttributeHandleSet&           theAttributes  // supplied C4
) throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotDefined,
  RTI::AttributeNotOwned,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 7.3
void RTIAmbassadorProxy::negotiatedAttributeOwnershipDivestiture (
        RTI::ObjectHandle                  theObject,     // supplied C1
  const RTI::AttributeHandleSet&           theAttributes, // supplied C4
  const char                         *theTag         // supplied C4
) throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotDefined,
  RTI::AttributeNotOwned,
  RTI::AttributeAlreadyBeingDivested,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 7.7
void RTIAmbassadorProxy::attributeOwnershipAcquisition (
        RTI::ObjectHandle        theObject,         // supplied C1
  const RTI::AttributeHandleSet& desiredAttributes, // supplied C4
  const char               *theTag             // supplied C4
) throw (
  RTI::ObjectNotKnown,
  RTI::ObjectClassNotPublished,
  RTI::AttributeNotDefined,
  RTI::AttributeNotPublished,
  RTI::FederateOwnsAttributes,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 7.8
void RTIAmbassadorProxy::attributeOwnershipAcquisitionIfAvailable (
        RTI::ObjectHandle        theObject,         // supplied C1
  const RTI::AttributeHandleSet& desiredAttributes  // supplied C4
) throw (
  RTI::ObjectNotKnown,
  RTI::ObjectClassNotPublished,
  RTI::AttributeNotDefined,
  RTI::AttributeNotPublished,
  RTI::FederateOwnsAttributes,
  RTI::AttributeAlreadyBeingAcquired,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 7.11
RTI::AttributeHandleSet* RTIAmbassadorProxy::attributeOwnershipReleaseResponse ( // returned C6
        RTI::ObjectHandle        theObject,                          // supplied C1
  const RTI::AttributeHandleSet& theAttributes                       // supplied C4
) throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotDefined,
  RTI::AttributeNotOwned,
  RTI::FederateWasNotAskedToReleaseAttribute,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) {
    return nullptr;
}

// 7.12
void RTIAmbassadorProxy::cancelNegotiatedAttributeOwnershipDivestiture (
        RTI::ObjectHandle        theObject,     // supplied C1
  const RTI::AttributeHandleSet& theAttributes  // supplied C4
) throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotDefined,
  RTI::AttributeNotOwned,
  RTI::AttributeDivestitureWasNotRequested,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 7.13
void RTIAmbassadorProxy::cancelAttributeOwnershipAcquisition (
        RTI::ObjectHandle        theObject,     // supplied C1
  const RTI::AttributeHandleSet& theAttributes  // supplied C4
) throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotDefined,
  RTI::AttributeAlreadyOwned,
  RTI::AttributeAcquisitionWasNotRequested,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 7.15
void RTIAmbassadorProxy::queryAttributeOwnership (
  RTI::ObjectHandle    theObject,    // supplied C1
  RTI::AttributeHandle theAttribute  // supplied C1
) throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 7.17
RTI::Boolean RTIAmbassadorProxy::isAttributeOwnedByFederate ( // returned C3
  RTI::ObjectHandle    theObject,                 // supplied C1
  RTI::AttributeHandle theAttribute               // supplied C1
) throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) {
    return RTI::RTI_FALSE;
}

//////////////////////////////
// Time Management Services //
//////////////////////////////

// 8.2
void RTIAmbassadorProxy::enableTimeRegulation (
  const RTI::FedTime& theFederateTime,  // supplied C4
  const RTI::FedTime& theLookahead      // supplied C4
) throw (
  RTI::TimeRegulationAlreadyEnabled,
  RTI::EnableTimeRegulationPending,
  RTI::TimeAdvanceAlreadyInProgress,
  RTI::InvalidFederationTime,
  RTI::InvalidLookahead,
  RTI::ConcurrentAccessAttempted,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 8.4
void RTIAmbassadorProxy::disableTimeRegulation () throw (
  RTI::TimeRegulationWasNotEnabled,
  RTI::ConcurrentAccessAttempted,
  RTI::FederateNotExecutionMember,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 8.5
void RTIAmbassadorProxy::enableTimeConstrained () throw (
  RTI::TimeConstrainedAlreadyEnabled,
  RTI::EnableTimeConstrainedPending,
  RTI::TimeAdvanceAlreadyInProgress,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 8.7
void RTIAmbassadorProxy::disableTimeConstrained () throw (
  RTI::TimeConstrainedWasNotEnabled,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 8.8
void RTIAmbassadorProxy::timeAdvanceRequest (
 const  RTI::FedTime& theTime  // supplied C4
) throw (
  RTI::InvalidFederationTime,
  RTI::FederationTimeAlreadyPassed,
  RTI::TimeAdvanceAlreadyInProgress,
  RTI::EnableTimeRegulationPending,
  RTI::EnableTimeConstrainedPending,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 8.9
void RTIAmbassadorProxy::timeAdvanceRequestAvailable (
  const RTI::FedTime& theTime  // supplied C4
) throw (
  RTI::InvalidFederationTime,
  RTI::FederationTimeAlreadyPassed,
  RTI::TimeAdvanceAlreadyInProgress,
  RTI::EnableTimeRegulationPending,
  RTI::EnableTimeConstrainedPending,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 8.10
void RTIAmbassadorProxy::nextEventRequest (
  const RTI::FedTime& theTime  // supplied C4
) throw (
  RTI::InvalidFederationTime,
  RTI::FederationTimeAlreadyPassed,
  RTI::TimeAdvanceAlreadyInProgress,
  RTI::EnableTimeRegulationPending,
  RTI::EnableTimeConstrainedPending,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 8.11
void RTIAmbassadorProxy::nextEventRequestAvailable (
  const RTI::FedTime& theTime  // supplied C4
) throw (
  RTI::InvalidFederationTime,
  RTI::FederationTimeAlreadyPassed,
  RTI::TimeAdvanceAlreadyInProgress,
  RTI::EnableTimeRegulationPending,
  RTI::EnableTimeConstrainedPending,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 8.12
void RTIAmbassadorProxy::flushQueueRequest (
  const RTI::FedTime& theTime  // supplied C4
) throw (
  RTI::InvalidFederationTime,
  RTI::FederationTimeAlreadyPassed,
  RTI::TimeAdvanceAlreadyInProgress,
  RTI::EnableTimeRegulationPending,
  RTI::EnableTimeConstrainedPending,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 8.14
void RTIAmbassadorProxy::enableAsynchronousDelivery() throw (
  RTI::AsynchronousDeliveryAlreadyEnabled,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 8.15
void RTIAmbassadorProxy::disableAsynchronousDelivery() throw (
  RTI::AsynchronousDeliveryAlreadyDisabled,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 8.16
void RTIAmbassadorProxy::queryLBTS (
  RTI::FedTime& theTime  // returned C5
) throw (
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 8.17
void RTIAmbassadorProxy::queryFederateTime (
  RTI::FedTime& theTime  // returned C5
) throw (
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 8.18
void RTIAmbassadorProxy::queryMinNextEventTime (
  RTI::FedTime& theTime  // returned C5
) throw (
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 8.19
void RTIAmbassadorProxy::modifyLookahead (
  const RTI::FedTime& theLookahead  // supplied C4
) throw (
  RTI::InvalidLookahead,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 8.20
void RTIAmbassadorProxy::queryLookahead (
   RTI::FedTime& theTime  // returned C5
) throw (
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 8.21
void RTIAmbassadorProxy::retract (
  RTI::EventRetractionHandle theHandle  // supplied C1
) throw (
  RTI::InvalidRetractionHandle,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 8.23
void RTIAmbassadorProxy::changeAttributeOrderType (
        RTI::ObjectHandle        theObject,     // supplied C1
  const RTI::AttributeHandleSet& theAttributes, // supplied C4
        RTI::OrderingHandle      theType        // supplied C1
) throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotDefined,
  RTI::AttributeNotOwned,
  RTI::InvalidOrderingHandle,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 8.24
void RTIAmbassadorProxy::changeInteractionOrderType (
  RTI::InteractionClassHandle theClass, // supplied C1
  RTI::OrderingHandle         theType   // supplied C1
) throw (
  RTI::InteractionClassNotDefined,
  RTI::InteractionClassNotPublished,
  RTI::InvalidOrderingHandle,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

//////////////////////////////////
// Data Distribution Management //
//////////////////////////////////

// 9.2
RTI::Region *RTIAmbassadorProxy::createRegion (    // returned C6
  RTI::SpaceHandle theSpace,           // supplied C1
  RTI::ULong       numberOfExtents     // supplied C1
) throw (
  RTI::SpaceNotDefined,
  RTI::InvalidExtents,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) {
    return nullptr;
}


// 9.3
void RTIAmbassadorProxy::notifyAboutRegionModification (
  RTI::Region &theRegion   // supplied C4
) throw (
  RTI::RegionNotKnown,
  RTI::InvalidExtents,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 9.4
void RTIAmbassadorProxy::deleteRegion (
  RTI::Region *theRegion  // supplied C1
) throw (
  RTI::RegionNotKnown,
  RTI::RegionInUse,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 9.5
RTI::ObjectHandle RTIAmbassadorProxy::registerObjectInstanceWithRegion (  // returned C3
        RTI::ObjectClassHandle theClass,           // supplied C1
  const char             *theObject,          // supplied C4
        RTI::AttributeHandle   theAttributes[],    // supplied C4
        RTI::Region           *theRegions[],       // supplied C4
        RTI::ULong             theNumberOfHandles  // supplied C1
) throw (
  RTI::ObjectClassNotDefined,
  RTI::ObjectClassNotPublished,
  RTI::AttributeNotDefined,
  RTI::AttributeNotPublished,
  RTI::RegionNotKnown,
  RTI::InvalidRegionContext,
  RTI::ObjectAlreadyRegistered,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) {
    return static_cast<RTI::ObjectHandle>(0);
}

RTI::ObjectHandle RTIAmbassadorProxy::registerObjectInstanceWithRegion (  // returned C3
  RTI::ObjectClassHandle theClass,             // supplied C1
  RTI::AttributeHandle   theAttributes[],      // supplied C4
  RTI::Region           *theRegions[],         // supplied C4
  RTI::ULong             theNumberOfHandles    // supplied C1
) throw (
  RTI::ObjectClassNotDefined,
  RTI::ObjectClassNotPublished,
  RTI::AttributeNotDefined,
  RTI::AttributeNotPublished,
  RTI::RegionNotKnown,
  RTI::InvalidRegionContext,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) {
    return static_cast<RTI::ObjectHandle>(0);
}

// 9.6
void RTIAmbassadorProxy::associateRegionForUpdates (
        RTI::Region             &theRegion,     // supplied C4
        RTI::ObjectHandle        theObject,     // supplied C1
  const RTI::AttributeHandleSet &theAttributes  // supplied C4
) throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotDefined,
  RTI::InvalidRegionContext,
  RTI::RegionNotKnown,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 9.7
void RTIAmbassadorProxy::unassociateRegionForUpdates (
  RTI::Region       &theRegion,     // supplied C4
  RTI::ObjectHandle  theObject      // supplied C1
) throw (
  RTI::ObjectNotKnown,
  RTI::InvalidRegionContext,
  RTI::RegionNotKnown,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 9.8
void RTIAmbassadorProxy::subscribeObjectClassAttributesWithRegion (
        RTI::ObjectClassHandle   theClass,      // supplied C1
        RTI::Region             &theRegion,     // supplied C4
  const RTI::AttributeHandleSet &attributeList, // supplied C4
        RTI::Boolean        active
) throw (
  RTI::ObjectClassNotDefined,
  RTI::AttributeNotDefined,
  RTI::RegionNotKnown,
  RTI::InvalidRegionContext,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 9.9
void RTIAmbassadorProxy::unsubscribeObjectClassWithRegion (
  RTI::ObjectClassHandle theClass,          // supplied C1
  RTI::Region           &theRegion          // supplied C4
) throw (
  RTI::ObjectClassNotDefined,
  RTI::RegionNotKnown,
  RTI::ObjectClassNotSubscribed,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 9.10
void RTIAmbassadorProxy::subscribeInteractionClassWithRegion (
  RTI::InteractionClassHandle theClass,        // supplied C1
  RTI::Region                &theRegion,       // supplied C4
  RTI::Boolean           active
) throw (
  RTI::InteractionClassNotDefined,
  RTI::RegionNotKnown,
  RTI::InvalidRegionContext,
  RTI::FederateLoggingServiceCalls,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 9.11
void RTIAmbassadorProxy::unsubscribeInteractionClassWithRegion (
  RTI::InteractionClassHandle theClass,  // supplied C1
  RTI::Region                &theRegion  // supplied C4
) throw (
  RTI::InteractionClassNotDefined,
  RTI::InteractionClassNotSubscribed,
  RTI::RegionNotKnown,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 9.12
RTI::EventRetractionHandle RTIAmbassadorProxy::sendInteractionWithRegion (  // returned C3
        RTI::InteractionClassHandle       theInteraction, // supplied C1
  const RTI::ParameterHandleValuePairSet &theParameters,  // supplied C4
  const RTI::FedTime&                     theTime,        // supplied C4
  const char                        *theTag,         // supplied C4
  const RTI::Region                      &theRegion       // supplied C4
) throw (
  RTI::InteractionClassNotDefined,
  RTI::InteractionClassNotPublished,
  RTI::InteractionParameterNotDefined,
  RTI::InvalidFederationTime,
  RTI::RegionNotKnown,
  RTI::InvalidRegionContext,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) {
      RTI::EventRetractionHandle eventRetractionHandle;
      eventRetractionHandle.theSerialNumber = 0;
      eventRetractionHandle.sendingFederate = 0;
      return eventRetractionHandle;
}

void RTIAmbassadorProxy::sendInteractionWithRegion (
  RTI::InteractionClassHandle       theInteraction, // supplied C1
  const RTI::ParameterHandleValuePairSet &theParameters,  // supplied C4
  const char                        *theTag,         // supplied C4
  const RTI::Region                      &theRegion       // supplied C4
) throw (
  RTI::InteractionClassNotDefined,
  RTI::InteractionClassNotPublished,
  RTI::InteractionParameterNotDefined,
  RTI::RegionNotKnown,
  RTI::InvalidRegionContext,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 9.13
void RTIAmbassadorProxy::requestClassAttributeValueUpdateWithRegion (
        RTI::ObjectClassHandle   theClass,      // supplied C1
  const RTI::AttributeHandleSet &theAttributes, // supplied C4
  const RTI::Region             &theRegion      // supplied C4
) throw (
  RTI::ObjectClassNotDefined,
  RTI::AttributeNotDefined,
  RTI::RegionNotKnown,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

//////////////////////////
// RTI Support Services //
//////////////////////////

// 10.2
RTI::ObjectClassHandle RTIAmbassadorProxy::getObjectClassHandle (  // returned C3
  const char *theName  // supplied C4
) throw (
  RTI::NameNotFound,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return static_cast<RTI::ObjectClassHandle>(0);
}

// 10.3
char *RTIAmbassadorProxy::getObjectClassName (     // returned C6
  RTI::ObjectClassHandle theHandle  // supplied C1
) throw (
  RTI::ObjectClassNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return nullptr;
}

// 10.4
RTI::AttributeHandle RTIAmbassadorProxy::getAttributeHandle (  // returned C3
  const char             *theName,    // supplied C4
        RTI::ObjectClassHandle whichClass  // supplied C1
) throw (
  RTI::ObjectClassNotDefined,
  RTI::NameNotFound,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return static_cast<RTI::AttributeHandle>(0);
}

// 10.5
char *RTIAmbassadorProxy::getAttributeName (  // returned C6
  RTI::AttributeHandle   theHandle,  // supplied C1
  RTI::ObjectClassHandle whichClass  // supplied C1
) throw (
  RTI::ObjectClassNotDefined,
  RTI::AttributeNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return nullptr;
}

// 10.6
RTI::InteractionClassHandle RTIAmbassadorProxy::getInteractionClassHandle ( // returned C3
  const char *theName      // supplied C4
) throw (
  RTI::NameNotFound,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return static_cast<RTI::InteractionClassHandle>(5);
}

// 10.7
char * RTIAmbassadorProxy::getInteractionClassName (  // returned C6
  RTI::InteractionClassHandle theHandle        // supplied C1
) throw (
  RTI::InteractionClassNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return nullptr;
}

// 10.8
RTI::ParameterHandle RTIAmbassadorProxy::getParameterHandle (  // returned C3
  const char *theName,                     // supplied C4
        RTI::InteractionClassHandle whichClass  // supplied C1
) throw (
  RTI::InteractionClassNotDefined,
  RTI::NameNotFound,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return static_cast<RTI::ParameterHandle>(0);
}

// 10.9
char *RTIAmbassadorProxy::getParameterName (     // returned C6
  RTI::ParameterHandle        theHandle,  // supplied C1
  RTI::InteractionClassHandle whichClass  // supplied C1
) throw (
  RTI::InteractionClassNotDefined,
  RTI::InteractionParameterNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return nullptr;
}

// 10.10
RTI::ObjectHandle RTIAmbassadorProxy::getObjectInstanceHandle (  // returned C3
  const char *theName        // supplied C4
) throw (
  RTI::ObjectNotKnown,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return static_cast<RTI::ObjectHandle>(0);
}

// 10.11
char *RTIAmbassadorProxy::getObjectInstanceName (  // returned C6
  RTI::ObjectHandle theHandle   // supplied C1
) throw (
  RTI::ObjectNotKnown,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return nullptr;
}

// 10.12
RTI::SpaceHandle RTIAmbassadorProxy::getRoutingSpaceHandle (  // returned C3
  const char *theName      // supplied C4
) throw (
  RTI::NameNotFound,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return static_cast<RTI::SpaceHandle>(0);
}

// 10.13
char *RTIAmbassadorProxy::getRoutingSpaceName (  // returned C6
   //
   // This const was removed for the RTI 1.3 NG to work around a limitation of
   // the Sun 4.2 C++ compiler regarding template instantiation.  The const
   // is unnecessary.
   //
   /* const */ RTI::SpaceHandle theHandle  // supplied C4
) throw (
  RTI::SpaceNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return nullptr;
}

// 10.14
RTI::DimensionHandle RTIAmbassadorProxy::getDimensionHandle (  // returned C3
  const char         *theName,    // supplied C4
        RTI::SpaceHandle   whichSpace  // supplied C1
) throw (
  RTI::SpaceNotDefined,
  RTI::NameNotFound,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return static_cast<RTI::DimensionHandle>(0);
}

// 10.15
char *RTIAmbassadorProxy::getDimensionName (  // returned C6
  RTI::DimensionHandle theHandle,  // supplied C1
  RTI::SpaceHandle     whichSpace  // supplied C1
) throw (
  RTI::SpaceNotDefined,
  RTI::DimensionNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return nullptr;
}

// 10.16
RTI::SpaceHandle RTIAmbassadorProxy::getAttributeRoutingSpaceHandle (  // returned C3
  RTI::AttributeHandle   theHandle,   // supplied C1
  RTI::ObjectClassHandle whichClass   // supplied C1
) throw (
  RTI::ObjectClassNotDefined,
  RTI::AttributeNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return static_cast<RTI::SpaceHandle>(0);
}

// 10.17
RTI::ObjectClassHandle RTIAmbassadorProxy::getObjectClass (  // returned C3
  RTI::ObjectHandle theObject     // supplied C1
) throw (
  RTI::ObjectNotKnown,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return static_cast<RTI::ObjectClassHandle>(0);
}

// 10.18
RTI::SpaceHandle RTIAmbassadorProxy::getInteractionRoutingSpaceHandle (  // returned C3
  RTI::InteractionClassHandle   theHandle    // supplied C1
) throw (
  RTI::InteractionClassNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return static_cast<RTI::SpaceHandle>(0);
}

// 10.19
RTI::TransportationHandle RTIAmbassadorProxy::getTransportationHandle (  // returned C3
  const char *theName     // supplied C4
) throw (
  RTI::NameNotFound,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return static_cast<RTI::TransportationHandle>(0);
}

// 10.20
char *RTIAmbassadorProxy::getTransportationName (  // returned C6
  RTI::TransportationHandle theHandle  // supplied C1
) throw (
  RTI::InvalidTransportationHandle,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return nullptr;
}

// 10.21
RTI::OrderingHandle RTIAmbassadorProxy::getOrderingHandle (  // returned C3
  const char *theName  // supplied C4
) throw (
  RTI::NameNotFound,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return static_cast<RTI::OrderingHandle>(0);
}

// 10.22
char *RTIAmbassadorProxy::getOrderingName (  // returned C6
  RTI::OrderingHandle theHandle  // supplied C1
) throw (
  RTI::InvalidOrderingHandle,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return nullptr;
}

// 10.23
void RTIAmbassadorProxy::enableClassRelevanceAdvisorySwitch() throw(
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 10.24
void RTIAmbassadorProxy::disableClassRelevanceAdvisorySwitch() throw(
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 10.25
void RTIAmbassadorProxy::enableAttributeRelevanceAdvisorySwitch() throw(
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 10.26
void RTIAmbassadorProxy::disableAttributeRelevanceAdvisorySwitch() throw(
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 10.27
void RTIAmbassadorProxy::enableAttributeScopeAdvisorySwitch() throw(
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 10.28
void RTIAmbassadorProxy::disableAttributeScopeAdvisorySwitch() throw(
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 10.29
void RTIAmbassadorProxy::enableInteractionRelevanceAdvisorySwitch() throw(
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

// 10.30
void RTIAmbassadorProxy::disableInteractionRelevanceAdvisorySwitch() throw(
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) { }

//
RTI::Boolean RTIAmbassadorProxy::tick () throw (  // returned C3
  RTI::SpecifiedSaveLabelDoesNotExist,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return RTI::RTI_FALSE;
}

RTI::Boolean RTIAmbassadorProxy::tick (  // returned C3
  RTI::TickTime minimum, // supplied C1
  RTI::TickTime maximum  // supplied C1
) throw (
  RTI::SpecifiedSaveLabelDoesNotExist,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return RTI::RTI_FALSE;
}

RTIAmbassadorProxy::RTIAmbassadorProxy() throw (
  RTI::MemoryExhausted,
  RTI::RTIinternalError
) { }

RTIAmbassadorProxy::~RTIAmbassadorProxy() throw (
  RTI::RTIinternalError
) { }

RTI::RegionToken RTIAmbassadorProxy::getRegionToken(
  RTI::Region *returnPtr
) throw(
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RegionNotKnown,
  RTI::RTIinternalError
) {
    return static_cast<RTI::RegionToken>(0);
}

RTI::Region *RTIAmbassadorProxy::getRegion(
  RTI::RegionToken regionToken
) throw(
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RegionNotKnown,
  RTI::RTIinternalError
) {
    return nullptr;
}


} // namespace RTIProxy

#if __cplusplus >= 201703L
#undef MultiArgTuple17
#undef Tuple17
#undef throw
#endif
