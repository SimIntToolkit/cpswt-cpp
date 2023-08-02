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

#include "RTIForTesting.hpp"
#include "RTIAmbassadorProxy.hpp"

#if __cplusplus >= 201703L
#define throw(x, ...)
#endif

// 4.2
void RTI::RTIambassador::createFederationExecution (
  const char *executionName, // supplied C4
  const char *FED            // supplied C4
) throw (
  FederationExecutionAlreadyExists,
  CouldNotOpenFED,
  ErrorReadingFED,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    rtiAmbassadorProxy->createFederationExecution(executionName, FED);
}

// 4.3
void RTI::RTIambassador::destroyFederationExecution (
  const char *executionName // supplied C4
) throw (
  FederatesCurrentlyJoined,
  FederationExecutionDoesNotExist,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    rtiAmbassadorProxy->destroyFederationExecution(executionName);
}

// 4.4
RTI::FederateHandle RTI::RTIambassador::joinFederationExecution (        // returned C3
  const char              *yourName,                    // supplied C4
  const char              *executionName,               // supplied C4
  FederateAmbassadorPtr   federateAmbassadorReference   // supplied C1
) throw (
  FederateAlreadyExecutionMember,
  FederationExecutionDoesNotExist,
  CouldNotOpenFED,
  ErrorReadingFED,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    return rtiAmbassadorProxy->joinFederationExecution(yourName, executionName, federateAmbassadorReference);
}

// 4.5
void RTI::RTIambassador::resignFederationExecution (
  ResignAction theAction // supplied C1
) throw (
  FederateOwnsAttributes,
  FederateNotExecutionMember,
  InvalidResignAction,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    rtiAmbassadorProxy->resignFederationExecution(theAction);
}

// 4.6
void RTI::RTIambassador::registerFederationSynchronizationPoint (
  const char *label,  // supplied C4
  const char *theTag  // supplied C4
) throw (
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->registerFederationSynchronizationPoint(label, theTag);
}

void RTI::RTIambassador::registerFederationSynchronizationPoint (
  const char                *label,    // supplied C4
  const char                *theTag,   // supplied C4
  const FederateHandleSet&   syncSet   // supplied C4
) throw (
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->registerFederationSynchronizationPoint(label, theTag, syncSet);
}

// 4.9
void RTI::RTIambassador::synchronizationPointAchieved (
  const char *label  // supplied C4
) throw (
  SynchronizationPointLabelWasNotAnnounced,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->synchronizationPointAchieved(label);
}

// 4.11
void RTI::RTIambassador::requestFederationSave (
  const char     *label,   // supplied C4
  const FedTime&  theTime  // supplied C4
) throw (
  FederationTimeAlreadyPassed,
  InvalidFederationTime,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->requestFederationSave(label, theTime);
}

void RTI::RTIambassador::requestFederationSave (
  const char *label     // supplied C4
) throw (
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->requestFederationSave(label);
}

// 4.13
void RTI::RTIambassador::federateSaveBegun () throw (
  SaveNotInitiated,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->federateSaveBegun();
}

// 4.14
void RTI::RTIambassador::federateSaveComplete () throw (
  SaveNotInitiated,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->federateSaveComplete();
}

void RTI::RTIambassador::federateSaveNotComplete () throw (
  SaveNotInitiated,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->federateSaveNotComplete();
}

// 4.16
void RTI::RTIambassador::requestFederationRestore (
  const char *label // supplied C4
) throw (
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->requestFederationRestore(label);
}

// 4.20
void RTI::RTIambassador::federateRestoreComplete () throw (
  RestoreNotRequested,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->federateRestoreComplete();
}

void RTI::RTIambassador::federateRestoreNotComplete () throw (
  RestoreNotRequested,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RTIinternalError
) { }

/////////////////////////////////////
// Declaration Management Services //
/////////////////////////////////////

// 5.2
void RTI::RTIambassador::publishObjectClass (
        ObjectClassHandle   theClass,      // supplied C1
  const AttributeHandleSet& attributeList  // supplied C4
) throw (
  ObjectClassNotDefined,
  AttributeNotDefined,
  OwnershipAcquisitionPending,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->publishObjectClass(theClass, attributeList);
}

// 5.3
void RTI::RTIambassador::unpublishObjectClass (
  ObjectClassHandle theClass  // supplied C1
) throw (
  ObjectClassNotDefined,
  ObjectClassNotPublished,
  OwnershipAcquisitionPending,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->unpublishObjectClass(theClass);
}

// 5.4
void RTI::RTIambassador::publishInteractionClass (
  InteractionClassHandle theInteraction  // supplied C1
) throw (
  InteractionClassNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->publishInteractionClass(theInteraction);
}

// 5.5
void RTI::RTIambassador::unpublishInteractionClass (
  InteractionClassHandle theInteraction  // supplied C1
) throw (
  InteractionClassNotDefined,
  InteractionClassNotPublished,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->unpublishInteractionClass(theInteraction);
}

// 5.6
void RTI::RTIambassador::subscribeObjectClassAttributes (
  ObjectClassHandle theClass,                           // supplied C1
  const             AttributeHandleSet& attributeList, // supplied C4
  Boolean           active
) throw (
  ObjectClassNotDefined,
  AttributeNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
 ) {
     rtiAmbassadorProxy->subscribeObjectClassAttributes(theClass, attributeList, active);
 }

// 5.7
void RTI::RTIambassador::unsubscribeObjectClass (
  ObjectClassHandle theClass  // supplied C1
) throw (
  ObjectClassNotDefined,
  ObjectClassNotSubscribed,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->unsubscribeObjectClass(theClass);
}

// 5.8
void RTI::RTIambassador::subscribeInteractionClass (
  InteractionClassHandle theClass, // supplied C1
  Boolean                active
) throw (
  InteractionClassNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  FederateLoggingServiceCalls,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->subscribeInteractionClass(theClass, active);
}

// 5.9
void RTI::RTIambassador::unsubscribeInteractionClass (
  InteractionClassHandle theClass  // supplied C1
) throw (
  InteractionClassNotDefined,
  InteractionClassNotSubscribed,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->unsubscribeInteractionClass(theClass);
}

////////////////////////////////
// Object Management Services //
////////////////////////////////

// 6.2
RTI::ObjectHandle RTI::RTIambassador::registerObjectInstance (  // returned C3
  ObjectClassHandle   theClass,        // supplied C1
  const char         *theObject        // supplied C4
) throw (
  ObjectClassNotDefined,
  ObjectClassNotPublished,
  ObjectAlreadyRegistered,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    return rtiAmbassadorProxy->registerObjectInstance(theClass, theObject);
}

RTI::ObjectHandle RTI::RTIambassador::registerObjectInstance (  // returned C3
  ObjectClassHandle theClass           // supplied C1
) throw (
  ObjectClassNotDefined,
  ObjectClassNotPublished,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    return rtiAmbassadorProxy->registerObjectInstance(theClass);
}

// 6.4
RTI::EventRetractionHandle RTI::RTIambassador::updateAttributeValues (       // returned C3
  ObjectHandle                       theObject,     // supplied C1
  const AttributeHandleValuePairSet& theAttributes, // supplied C4
  const FedTime&                     theTime,       // supplied C4
  const char                        *theTag         // supplied C4
) throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  InvalidFederationTime,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    return rtiAmbassadorProxy->updateAttributeValues(theObject, theAttributes, theTime, theTag);
}

void RTI::RTIambassador::updateAttributeValues (
  ObjectHandle                       theObject,     // supplied C1
  const AttributeHandleValuePairSet& theAttributes, // supplied C4
  const char                        *theTag         // supplied C4
) throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->updateAttributeValues(theObject, theAttributes, theTag);
}

// 6.6
RTI::EventRetractionHandle RTI::RTIambassador::sendInteraction (              // returned C3
  InteractionClassHandle             theInteraction, // supplied C1
  const ParameterHandleValuePairSet& theParameters,  // supplied C4
  const FedTime&                     theTime,        // supplied C4
  const char                        *theTag)         // supplied C4
throw (
  InteractionClassNotDefined,
  InteractionClassNotPublished,
  InteractionParameterNotDefined,
  InvalidFederationTime,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    return rtiAmbassadorProxy->sendInteraction(theInteraction, theParameters, theTime, theTag);
}

void RTI::RTIambassador::sendInteraction (
        InteractionClassHandle       theInteraction, // supplied C1
  const ParameterHandleValuePairSet& theParameters,  // supplied C4
  const char                        *theTag          // supplied C4
) throw (
  InteractionClassNotDefined,
  InteractionClassNotPublished,
  InteractionParameterNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->sendInteraction(theInteraction, theParameters, theTag);
}

// 6.8
RTI::EventRetractionHandle RTI::RTIambassador::deleteObjectInstance ( // returned C3
  ObjectHandle    theObject,                         // supplied C1
  const FedTime&  theTime,                           // supplied C4
  const char      *theTag                            // supplied C4
) throw (
  ObjectNotKnown,
  DeletePrivilegeNotHeld,
  InvalidFederationTime,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    return rtiAmbassadorProxy->deleteObjectInstance(theObject, theTime, theTag);
}

void RTI::RTIambassador::deleteObjectInstance (
        ObjectHandle    theObject,    // supplied C1
  const char           *theTag        // supplied C4
) throw (
  ObjectNotKnown,
  DeletePrivilegeNotHeld,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->deleteObjectInstance(theObject, theTag);
}

// 6.10
void RTI::RTIambassador::localDeleteObjectInstance (
  ObjectHandle    theObject       // supplied C1
) throw (
  ObjectNotKnown,
  FederateOwnsAttributes,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->localDeleteObjectInstance(theObject);
}

// 6.11
void RTI::RTIambassador::changeAttributeTransportationType (
        ObjectHandle             theObject,     // supplied C1
  const AttributeHandleSet&      theAttributes, // supplied C4
        TransportationHandle     theType        // supplied C1
) throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  InvalidTransportationHandle,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->changeAttributeTransportationType(theObject, theAttributes, theType);
}

// 6.12
void RTI::RTIambassador::changeInteractionTransportationType (
  InteractionClassHandle theClass, // supplied C1
  TransportationHandle   theType   // supplied C1
) throw (
  InteractionClassNotDefined,
  InteractionClassNotPublished,
  InvalidTransportationHandle,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->changeInteractionTransportationType(theClass, theType);
}

// 6.15
void RTI::RTIambassador::requestObjectAttributeValueUpdate (
        ObjectHandle        theObject,     // supplied C1
  const AttributeHandleSet& theAttributes  // supplied C4
) throw (
  ObjectNotKnown,
  AttributeNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->requestObjectAttributeValueUpdate(theObject, theAttributes);
}

void RTI::RTIambassador::requestClassAttributeValueUpdate (
        ObjectClassHandle   theClass,      // supplied C1
  const AttributeHandleSet& theAttributes  // supplied C4
) throw (
  ObjectClassNotDefined,
  AttributeNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->requestClassAttributeValueUpdate(theClass, theAttributes);
}

///////////////////////////////////
// Ownership Management Services //
///////////////////////////////////

// 7.2
void RTI::RTIambassador::unconditionalAttributeOwnershipDivestiture (
        ObjectHandle                  theObject,     // supplied C1
  const AttributeHandleSet&           theAttributes  // supplied C4
) throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->unconditionalAttributeOwnershipDivestiture(theObject, theAttributes);
}

// 7.3
void RTI::RTIambassador::negotiatedAttributeOwnershipDivestiture (
        ObjectHandle                  theObject,     // supplied C1
  const AttributeHandleSet&           theAttributes, // supplied C4
  const char                         *theTag         // supplied C4
) throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  AttributeAlreadyBeingDivested,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->negotiatedAttributeOwnershipDivestiture(theObject, theAttributes, theTag);
}

// 7.7
void RTI::RTIambassador::attributeOwnershipAcquisition (
        ObjectHandle        theObject,         // supplied C1
  const AttributeHandleSet& desiredAttributes, // supplied C4
  const char               *theTag             // supplied C4
) throw (
  ObjectNotKnown,
  ObjectClassNotPublished,
  AttributeNotDefined,
  AttributeNotPublished,
  FederateOwnsAttributes,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->attributeOwnershipAcquisition(theObject, desiredAttributes, theTag);
}

// 7.8
void RTI::RTIambassador::attributeOwnershipAcquisitionIfAvailable (
        ObjectHandle        theObject,         // supplied C1
  const AttributeHandleSet& desiredAttributes  // supplied C4
) throw (
  ObjectNotKnown,
  ObjectClassNotPublished,
  AttributeNotDefined,
  AttributeNotPublished,
  FederateOwnsAttributes,
  AttributeAlreadyBeingAcquired,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->attributeOwnershipAcquisitionIfAvailable(theObject, desiredAttributes);
}

// 7.11
RTI::AttributeHandleSet* RTI::RTIambassador::attributeOwnershipReleaseResponse ( // returned C6
        ObjectHandle        theObject,                          // supplied C1
  const AttributeHandleSet& theAttributes                       // supplied C4
) throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  FederateWasNotAskedToReleaseAttribute,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    return rtiAmbassadorProxy->attributeOwnershipReleaseResponse(theObject, theAttributes);
}

// 7.12
void RTI::RTIambassador::cancelNegotiatedAttributeOwnershipDivestiture (
        ObjectHandle        theObject,     // supplied C1
  const AttributeHandleSet& theAttributes  // supplied C4
) throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  AttributeDivestitureWasNotRequested,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->cancelNegotiatedAttributeOwnershipDivestiture(theObject, theAttributes);
}

// 7.13
void RTI::RTIambassador::cancelAttributeOwnershipAcquisition (
        ObjectHandle        theObject,     // supplied C1
  const AttributeHandleSet& theAttributes  // supplied C4
) throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeAlreadyOwned,
  AttributeAcquisitionWasNotRequested,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->cancelAttributeOwnershipAcquisition(theObject, theAttributes);
}

// 7.15
void RTI::RTIambassador::queryAttributeOwnership (
  ObjectHandle    theObject,    // supplied C1
  AttributeHandle theAttribute  // supplied C1
) throw (
  ObjectNotKnown,
  AttributeNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->queryAttributeOwnership(theObject, theAttribute);
}

// 7.17
RTI::Boolean RTI::RTIambassador::isAttributeOwnedByFederate ( // returned C3
  ObjectHandle    theObject,                 // supplied C1
  AttributeHandle theAttribute               // supplied C1
) throw (
  ObjectNotKnown,
  AttributeNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    return rtiAmbassadorProxy->isAttributeOwnedByFederate(theObject, theAttribute);
}

//////////////////////////////
// Time Management Services //
//////////////////////////////

// 8.2
void RTI::RTIambassador::enableTimeRegulation (
  const FedTime& theFederateTime,  // supplied C4
  const FedTime& theLookahead      // supplied C4
) throw (
  TimeRegulationAlreadyEnabled,
  EnableTimeRegulationPending,
  TimeAdvanceAlreadyInProgress,
  InvalidFederationTime,
  InvalidLookahead,
  ConcurrentAccessAttempted,
  FederateNotExecutionMember,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->enableTimeRegulation(theFederateTime, theLookahead);
}

// 8.4
void RTI::RTIambassador::disableTimeRegulation () throw (
  TimeRegulationWasNotEnabled,
  ConcurrentAccessAttempted,
  FederateNotExecutionMember,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->disableTimeRegulation();
}

// 8.5
void RTI::RTIambassador::enableTimeConstrained () throw (
  TimeConstrainedAlreadyEnabled,
  EnableTimeConstrainedPending,
  TimeAdvanceAlreadyInProgress,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->enableTimeConstrained();
}

// 8.7
void RTI::RTIambassador::disableTimeConstrained () throw (
  TimeConstrainedWasNotEnabled,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->disableTimeConstrained();
}

// 8.8
void RTI::RTIambassador::timeAdvanceRequest (
 const  FedTime& theTime  // supplied C4
) throw (
  InvalidFederationTime,
  FederationTimeAlreadyPassed,
  TimeAdvanceAlreadyInProgress,
  EnableTimeRegulationPending,
  EnableTimeConstrainedPending,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->timeAdvanceRequest(theTime);
}

// 8.9
void RTI::RTIambassador::timeAdvanceRequestAvailable (
  const FedTime& theTime  // supplied C4
) throw (
  InvalidFederationTime,
  FederationTimeAlreadyPassed,
  TimeAdvanceAlreadyInProgress,
  EnableTimeRegulationPending,
  EnableTimeConstrainedPending,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->timeAdvanceRequestAvailable(theTime);
}

// 8.10
void RTI::RTIambassador::nextEventRequest (
  const FedTime& theTime  // supplied C4
) throw (
  InvalidFederationTime,
  FederationTimeAlreadyPassed,
  TimeAdvanceAlreadyInProgress,
  EnableTimeRegulationPending,
  EnableTimeConstrainedPending,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->nextEventRequest(theTime);
}

// 8.11
void RTI::RTIambassador::nextEventRequestAvailable (
  const FedTime& theTime  // supplied C4
) throw (
  InvalidFederationTime,
  FederationTimeAlreadyPassed,
  TimeAdvanceAlreadyInProgress,
  EnableTimeRegulationPending,
  EnableTimeConstrainedPending,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->nextEventRequestAvailable(theTime);
}

// 8.12
void RTI::RTIambassador::flushQueueRequest (
  const FedTime& theTime  // supplied C4
) throw (
  InvalidFederationTime,
  FederationTimeAlreadyPassed,
  TimeAdvanceAlreadyInProgress,
  EnableTimeRegulationPending,
  EnableTimeConstrainedPending,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->flushQueueRequest(theTime);
}

// 8.14
void RTI::RTIambassador::enableAsynchronousDelivery() throw (
  AsynchronousDeliveryAlreadyEnabled,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->enableAsynchronousDelivery();
}

// 8.15
void RTI::RTIambassador::disableAsynchronousDelivery() throw (
  AsynchronousDeliveryAlreadyDisabled,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->disableAsynchronousDelivery();
}

// 8.16
void RTI::RTIambassador::queryLBTS (
  FedTime& theTime  // returned C5
) throw (
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->queryLBTS(theTime);
}

// 8.17
void RTI::RTIambassador::queryFederateTime (
  FedTime& theTime  // returned C5
) throw (
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->queryFederateTime(theTime);
}

// 8.18
void RTI::RTIambassador::queryMinNextEventTime (
  FedTime& theTime  // returned C5
) throw (
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->queryMinNextEventTime(theTime);
}

// 8.19
void RTI::RTIambassador::modifyLookahead (
  const FedTime& theLookahead  // supplied C4
) throw (
  InvalidLookahead,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->modifyLookahead(theLookahead);
}

// 8.20
void RTI::RTIambassador::queryLookahead (
   FedTime& theTime  // returned C5
) throw (
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->queryLookahead(theTime);
}

// 8.21
void RTI::RTIambassador::retract (
  EventRetractionHandle theHandle  // supplied C1
) throw (
  InvalidRetractionHandle,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->retract(theHandle);
}

// 8.23
void RTI::RTIambassador::changeAttributeOrderType (
        ObjectHandle        theObject,     // supplied C1
  const AttributeHandleSet& theAttributes, // supplied C4
        OrderingHandle      theType        // supplied C1
) throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  InvalidOrderingHandle,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->changeAttributeOrderType(theObject, theAttributes, theType);
}

// 8.24
void RTI::RTIambassador::changeInteractionOrderType (
  InteractionClassHandle theClass, // supplied C1
  OrderingHandle         theType   // supplied C1
) throw (
  InteractionClassNotDefined,
  InteractionClassNotPublished,
  InvalidOrderingHandle,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->changeInteractionOrderType(theClass, theType);
}

//////////////////////////////////
// Data Distribution Management //
//////////////////////////////////

// 9.2
RTI::Region *RTI::RTIambassador::createRegion (    // returned C6
  SpaceHandle theSpace,           // supplied C1
  ULong       numberOfExtents     // supplied C1
) throw (
  SpaceNotDefined,
  InvalidExtents,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    return rtiAmbassadorProxy->createRegion(theSpace, numberOfExtents);
}


// 9.3
void RTI::RTIambassador::notifyAboutRegionModification (
  Region &theRegion   // supplied C4
) throw (
  RegionNotKnown,
  InvalidExtents,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->notifyAboutRegionModification(theRegion);
}

// 9.4
void RTI::RTIambassador::deleteRegion (
  Region *theRegion  // supplied C1
) throw (
  RegionNotKnown,
  RegionInUse,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->deleteRegion(theRegion);
}

// 9.5
RTI::ObjectHandle RTI::RTIambassador::registerObjectInstanceWithRegion (  // returned C3
        ObjectClassHandle theClass,           // supplied C1
  const char             *theObject,          // supplied C4
        AttributeHandle   theAttributes[],    // supplied C4
        Region           *theRegions[],       // supplied C4
        ULong             theNumberOfHandles  // supplied C1
) throw (
  ObjectClassNotDefined,
  ObjectClassNotPublished,
  AttributeNotDefined,
  AttributeNotPublished,
  RegionNotKnown,
  InvalidRegionContext,
  ObjectAlreadyRegistered,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    return rtiAmbassadorProxy->registerObjectInstanceWithRegion(
      theClass, theObject, theAttributes, theRegions, theNumberOfHandles
    );
}

RTI::ObjectHandle RTI::RTIambassador::registerObjectInstanceWithRegion (  // returned C3
  ObjectClassHandle theClass,             // supplied C1
  AttributeHandle   theAttributes[],      // supplied C4
  Region           *theRegions[],         // supplied C4
  ULong             theNumberOfHandles    // supplied C1
) throw (
  ObjectClassNotDefined,
  ObjectClassNotPublished,
  AttributeNotDefined,
  AttributeNotPublished,
  RegionNotKnown,
  InvalidRegionContext,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    return rtiAmbassadorProxy->registerObjectInstanceWithRegion(theClass, theAttributes, theRegions, theNumberOfHandles);
}

// 9.6
void RTI::RTIambassador::associateRegionForUpdates (
        Region             &theRegion,     // supplied C4
        ObjectHandle        theObject,     // supplied C1
  const AttributeHandleSet &theAttributes  // supplied C4
) throw (
  ObjectNotKnown,
  AttributeNotDefined,
  InvalidRegionContext,
  RegionNotKnown,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->associateRegionForUpdates(theRegion, theObject, theAttributes);
}

// 9.7
void RTI::RTIambassador::unassociateRegionForUpdates (
  Region       &theRegion,     // supplied C4
  ObjectHandle  theObject      // supplied C1
) throw (
  ObjectNotKnown,
  InvalidRegionContext,
  RegionNotKnown,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->unassociateRegionForUpdates(theRegion, theObject);
}

// 9.8
void RTI::RTIambassador::subscribeObjectClassAttributesWithRegion (
        ObjectClassHandle   theClass,      // supplied C1
        Region             &theRegion,     // supplied C4
  const AttributeHandleSet &attributeList, // supplied C4
        Boolean        active
) throw (
  ObjectClassNotDefined,
  AttributeNotDefined,
  RegionNotKnown,
  InvalidRegionContext,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->subscribeObjectClassAttributesWithRegion(theClass, theRegion, attributeList, active);
}

// 9.9
void RTI::RTIambassador::unsubscribeObjectClassWithRegion (
  ObjectClassHandle theClass,          // supplied C1
  Region           &theRegion          // supplied C4
) throw (
  ObjectClassNotDefined,
  RegionNotKnown,
  ObjectClassNotSubscribed,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->unsubscribeObjectClassWithRegion(theClass, theRegion);
}

// 9.10
void RTI::RTIambassador::subscribeInteractionClassWithRegion (
  InteractionClassHandle theClass,        // supplied C1
  Region                &theRegion,       // supplied C4
  Boolean           active
) throw (
  InteractionClassNotDefined,
  RegionNotKnown,
  InvalidRegionContext,
  FederateLoggingServiceCalls,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->subscribeInteractionClassWithRegion(theClass, theRegion, active);
}

// 9.11
void RTI::RTIambassador::unsubscribeInteractionClassWithRegion (
  InteractionClassHandle theClass,  // supplied C1
  Region                &theRegion  // supplied C4
) throw (
  InteractionClassNotDefined,
  InteractionClassNotSubscribed,
  RegionNotKnown,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->unsubscribeInteractionClassWithRegion(theClass, theRegion);
}

// 9.12
RTI::EventRetractionHandle RTI::RTIambassador::sendInteractionWithRegion (  // returned C3
        InteractionClassHandle       theInteraction, // supplied C1
  const ParameterHandleValuePairSet &theParameters,  // supplied C4
  const FedTime&                     theTime,        // supplied C4
  const char                        *theTag,         // supplied C4
  const Region                      &theRegion       // supplied C4
) throw (
  InteractionClassNotDefined,
  InteractionClassNotPublished,
  InteractionParameterNotDefined,
  InvalidFederationTime,
  RegionNotKnown,
  InvalidRegionContext,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    return rtiAmbassadorProxy->sendInteractionWithRegion(theInteraction, theParameters, theTime, theTag, theRegion);
}

void RTI::RTIambassador::sendInteractionWithRegion (
  InteractionClassHandle       theInteraction, // supplied C1
  const ParameterHandleValuePairSet &theParameters,  // supplied C4
  const char                        *theTag,         // supplied C4
  const Region                      &theRegion       // supplied C4
) throw (
  InteractionClassNotDefined,
  InteractionClassNotPublished,
  InteractionParameterNotDefined,
  RegionNotKnown,
  InvalidRegionContext,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->sendInteractionWithRegion(theInteraction, theParameters, theTag, theRegion);
}

// 9.13
void RTI::RTIambassador::requestClassAttributeValueUpdateWithRegion (
        ObjectClassHandle   theClass,      // supplied C1
  const AttributeHandleSet &theAttributes, // supplied C4
  const Region             &theRegion      // supplied C4
) throw (
  ObjectClassNotDefined,
  AttributeNotDefined,
  RegionNotKnown,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->requestClassAttributeValueUpdateWithRegion(theClass, theAttributes, theRegion);
}

//////////////////////////
// RTI Support Services //
//////////////////////////

// 10.2
RTI::ObjectClassHandle RTI::RTIambassador::getObjectClassHandle (  // returned C3
  const char *theName  // supplied C4
) throw (
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getObjectClassHandle(theName);
}

// 10.3
char *RTI::RTIambassador::getObjectClassName (     // returned C6
  ObjectClassHandle theHandle  // supplied C1
) throw (
  ObjectClassNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getObjectClassName(theHandle);
}

// 10.4
RTI::AttributeHandle RTI::RTIambassador::getAttributeHandle (  // returned C3
  const char             *theName,    // supplied C4
        ObjectClassHandle whichClass  // supplied C1
) throw (
  ObjectClassNotDefined,
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getAttributeHandle(theName, whichClass);
}

// 10.5
char *RTI::RTIambassador::getAttributeName (  // returned C6
  AttributeHandle   theHandle,  // supplied C1
  ObjectClassHandle whichClass  // supplied C1
) throw (
  ObjectClassNotDefined,
  AttributeNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getAttributeName(theHandle, whichClass);
}

// 10.6
RTI::InteractionClassHandle RTI::RTIambassador::getInteractionClassHandle ( // returned C3
  const char *theName      // supplied C4
) throw (
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getInteractionClassHandle(theName);
}

// 10.7
char * RTI::RTIambassador::getInteractionClassName (  // returned C6
  InteractionClassHandle theHandle        // supplied C1
) throw (
  InteractionClassNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getInteractionClassName(theHandle);
}

// 10.8
RTI::ParameterHandle RTI::RTIambassador::getParameterHandle (  // returned C3
  const char *theName,                     // supplied C4
        InteractionClassHandle whichClass  // supplied C1
) throw (
  InteractionClassNotDefined,
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getParameterHandle(theName, whichClass);
}

// 10.9
char *RTI::RTIambassador::getParameterName (     // returned C6
  ParameterHandle        theHandle,  // supplied C1
  InteractionClassHandle whichClass  // supplied C1
) throw (
  InteractionClassNotDefined,
  InteractionParameterNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getParameterName(theHandle, whichClass);
}

// 10.10
RTI::ObjectHandle RTI::RTIambassador::getObjectInstanceHandle (  // returned C3
  const char *theName        // supplied C4
) throw (
  ObjectNotKnown,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getObjectInstanceHandle(theName);
}

// 10.11
char *RTI::RTIambassador::getObjectInstanceName (  // returned C6
  ObjectHandle theHandle   // supplied C1
) throw (
  ObjectNotKnown,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getObjectInstanceName(theHandle);
}

// 10.12
RTI::SpaceHandle RTI::RTIambassador::getRoutingSpaceHandle (  // returned C3
  const char *theName      // supplied C4
) throw (
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getRoutingSpaceHandle(theName);
}

// 10.13
char *RTI::RTIambassador::getRoutingSpaceName (  // returned C6
   //
   // This const was removed for the RTI 1.3 NG to work around a limitation of
   // the Sun 4.2 C++ compiler regarding template instantiation.  The const
   // is unnecessary.
   //
   /* const */ SpaceHandle theHandle  // supplied C4
) throw (
  SpaceNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getRoutingSpaceName(theHandle);
}

// 10.14
RTI::DimensionHandle RTI::RTIambassador::getDimensionHandle (  // returned C3
  const char         *theName,    // supplied C4
        SpaceHandle   whichSpace  // supplied C1
) throw (
  SpaceNotDefined,
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getDimensionHandle(theName, whichSpace);
}

// 10.15
char *RTI::RTIambassador::getDimensionName (  // returned C6
  DimensionHandle theHandle,  // supplied C1
  SpaceHandle     whichSpace  // supplied C1
) throw (
  SpaceNotDefined,
  DimensionNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getDimensionName(theHandle, whichSpace);
}

// 10.16
RTI::SpaceHandle RTI::RTIambassador::getAttributeRoutingSpaceHandle (  // returned C3
  AttributeHandle   theHandle,   // supplied C1
  ObjectClassHandle whichClass   // supplied C1
) throw (
  ObjectClassNotDefined,
  AttributeNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getAttributeRoutingSpaceHandle(theHandle, whichClass);
}

// 10.17
RTI::ObjectClassHandle RTI::RTIambassador::getObjectClass (  // returned C3
  ObjectHandle theObject     // supplied C1
) throw (
  ObjectNotKnown,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getObjectClass(theObject);
}

// 10.18
RTI::SpaceHandle RTI::RTIambassador::getInteractionRoutingSpaceHandle (  // returned C3
  InteractionClassHandle   theHandle    // supplied C1
) throw (
  InteractionClassNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getInteractionRoutingSpaceHandle(theHandle);
}

// 10.19
RTI::TransportationHandle RTI::RTIambassador::getTransportationHandle (  // returned C3
  const char *theName     // supplied C4
) throw (
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getTransportationHandle(theName);
}

// 10.20
char *RTI::RTIambassador::getTransportationName (  // returned C6
  TransportationHandle theHandle  // supplied C1
) throw (
  InvalidTransportationHandle,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getTransportationName(theHandle);
}

// 10.21
RTI::OrderingHandle RTI::RTIambassador::getOrderingHandle (  // returned C3
  const char *theName  // supplied C4
) throw (
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getOrderingHandle(theName);
}

// 10.22
char *RTI::RTIambassador::getOrderingName (  // returned C6
  OrderingHandle theHandle  // supplied C1
) throw (
  InvalidOrderingHandle,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getOrderingName(theHandle);
}

// 10.23
void RTI::RTIambassador::enableClassRelevanceAdvisorySwitch() throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->enableClassRelevanceAdvisorySwitch();
}

// 10.24
void RTI::RTIambassador::disableClassRelevanceAdvisorySwitch() throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->disableClassRelevanceAdvisorySwitch();
}

// 10.25
void RTI::RTIambassador::enableAttributeRelevanceAdvisorySwitch() throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->enableAttributeRelevanceAdvisorySwitch();
}

// 10.26
void RTI::RTIambassador::disableAttributeRelevanceAdvisorySwitch() throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->disableAttributeRelevanceAdvisorySwitch();
}

// 10.27
void RTI::RTIambassador::enableAttributeScopeAdvisorySwitch() throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->enableAttributeScopeAdvisorySwitch();
}

// 10.28
void RTI::RTIambassador::disableAttributeScopeAdvisorySwitch() throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->disableAttributeScopeAdvisorySwitch();
}

// 10.29
void RTI::RTIambassador::enableInteractionRelevanceAdvisorySwitch() throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->enableInteractionRelevanceAdvisorySwitch();
}

// 10.30
void RTI::RTIambassador::disableInteractionRelevanceAdvisorySwitch() throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError
) {
    rtiAmbassadorProxy->disableInteractionRelevanceAdvisorySwitch();
}

//
RTI::Boolean RTI::RTIambassador::tick () throw (  // returned C3
  SpecifiedSaveLabelDoesNotExist,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->tick();
}

RTI::Boolean RTI::RTIambassador::tick (  // returned C3
  TickTime minimum, // supplied C1
  TickTime maximum  // supplied C1
) throw (
  SpecifiedSaveLabelDoesNotExist,
  ConcurrentAccessAttempted,
  RTIinternalError
) {
    return rtiAmbassadorProxy->tick(minimum, maximum);
}

RTI::RTIambassador::RTIambassador() throw (
  MemoryExhausted,
  RTIinternalError
) : rtiAmbassadorProxy(nullptr) { }

RTI::RTIambassador::RTIambassador(RTIProxy::RTIAmbassadorProxy &inputRTIAmbassadorProxy) :
  rtiAmbassadorProxy(&inputRTIAmbassadorProxy) { }

RTI::RTIambassador::RTIambassador(RTIProxy::RTIAmbassadorProxy *inputRTIAmbassadorProxy) :
  rtiAmbassadorProxy(inputRTIAmbassadorProxy) { }

RTI::RTIambassador::~RTIambassador() throw (
  RTIinternalError
) { }

RTI::RegionToken RTI::RTIambassador::getRegionToken(
  Region *returnPtr
) throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RegionNotKnown,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getRegionToken(returnPtr);
}

RTI::Region *RTI::RTIambassador::getRegion(
  RegionToken regionToken
) throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RegionNotKnown,
  RTIinternalError
) {
    return rtiAmbassadorProxy->getRegion(regionToken);
}

#if __cplusplus >= 201703L
#undef throw
#endif
