#include "RTITest.hh"
#include "AttributeHandleSetTest.hh"

#include <limits>

//File RTIambServices.hh
//Included in RTI.hh


//                RTI Parameter Passing Memory Conventions
//
// C1  In parameter by value.
// C2  Out parameter by pointer value.
// C3  Function return by value.
// C4  In parameter by const pointer value.  Caller provides memory.
//     Caller may free memory or overwrite it upon completion of
//     the call.  Callee must copy during the call anything it
//     wishes to save beyond completion of the call.  Parameter
//     type must define const accessor methods.
// C5  Out parameter by pointer value.  Caller provides reference to object.
//     Callee constructs an instance on the heap (new) and returns.
//     The caller destroys the instance (delete) at its leisure.
// C6  Function return by pointer value.  Callee constructs an instance on
//     the heap (new) and returns a reference.  The caller destroys the
//     instance (delete) at its leisure.
//

class FederateAmbassador;
typedef FederateAmbassador *FederateAmbassadorPtr;

////////////////////////////////////
// Federation Management Services //
////////////////////////////////////

// 4.2
void RTI::RTIambassador::createFederationExecution (
  const char *executionName, // supplied C4
  const char *FED)           // supplied C4
throw (
  FederationExecutionAlreadyExists,
  CouldNotOpenFED,
  ErrorReadingFED,
  ConcurrentAccessAttempted,
  RTIinternalError) { }

// 4.3
void RTI::RTIambassador::destroyFederationExecution (
  const char *executionName) // supplied C4
throw (
  FederatesCurrentlyJoined,
  FederationExecutionDoesNotExist,
  ConcurrentAccessAttempted,
  RTIinternalError) { }

// 4.4
RTI::FederateHandle                                               // returned C3
RTI::RTIambassador::joinFederationExecution (
  const char                   *yourName,                    // supplied C4
  const char                   *executionName,               // supplied C4
        FederateAmbassadorPtr   federateAmbassadorReference) // supplied C1
throw (
  FederateAlreadyExecutionMember,
  FederationExecutionDoesNotExist,
  CouldNotOpenFED,
  ErrorReadingFED,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) {
    return static_cast<FederateHandle>(0);
}

// 4.5
void RTI::RTIambassador::resignFederationExecution (
  ResignAction theAction) // supplied C1
throw (
  FederateOwnsAttributes,
  FederateNotExecutionMember,
  InvalidResignAction,
  ConcurrentAccessAttempted,
  RTIinternalError) { }

// 4.6
void RTI::RTIambassador::registerFederationSynchronizationPoint (
  const char *label,  // supplied C4
  const char *theTag) // supplied C4
throw (
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

void RTI::RTIambassador::registerFederationSynchronizationPoint (
  const char                *label,    // supplied C4
  const char                *theTag,   // supplied C4
  const FederateHandleSet&   syncSet)  // supplied C4
throw (
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 4.9
void RTI::RTIambassador::synchronizationPointAchieved (
  const char *label) // supplied C4
throw (
  SynchronizationPointLabelWasNotAnnounced,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 4.11
void RTI::RTIambassador::requestFederationSave (
  const char     *label,   // supplied C4
  const FedTime&  theTime) // supplied C4
throw (
  FederationTimeAlreadyPassed,
  InvalidFederationTime,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

void RTI::RTIambassador::requestFederationSave (
  const char *label)     // supplied C4
  throw (
    FederateNotExecutionMember,
    ConcurrentAccessAttempted,
    SaveInProgress,
    RestoreInProgress,
    RTIinternalError) { }

// 4.13
void RTI::RTIambassador::federateSaveBegun ()
throw (
  SaveNotInitiated,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RestoreInProgress,
  RTIinternalError) { }

// 4.14
void RTI::RTIambassador::federateSaveComplete ()
throw (
  SaveNotInitiated,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RestoreInProgress,
  RTIinternalError) { }

void RTI::RTIambassador::federateSaveNotComplete ()
throw (
  SaveNotInitiated,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RestoreInProgress,
  RTIinternalError) { }

// 4.16
void RTI::RTIambassador::requestFederationRestore (
  const char *label) // supplied C4
throw (
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 4.20
void RTI::RTIambassador::federateRestoreComplete ()
  throw (
    RestoreNotRequested,
    FederateNotExecutionMember,
    ConcurrentAccessAttempted,
    SaveInProgress,
    RTIinternalError) { }

void RTI::RTIambassador::federateRestoreNotComplete ()
throw (
  RestoreNotRequested,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RTIinternalError) { }

/////////////////////////////////////
// Declaration Management Services //
/////////////////////////////////////

// 5.2
void RTI::RTIambassador::publishObjectClass (
        ObjectClassHandle   theClass,      // supplied C1
  const AttributeHandleSet& attributeList) // supplied C4
throw (
  ObjectClassNotDefined,
  AttributeNotDefined,
  OwnershipAcquisitionPending,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 5.3
void RTI::RTIambassador::unpublishObjectClass (
  ObjectClassHandle theClass) // supplied C1
throw (
  ObjectClassNotDefined,
  ObjectClassNotPublished,
  OwnershipAcquisitionPending,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 5.4
void RTI::RTIambassador::publishInteractionClass (
  InteractionClassHandle theInteraction) // supplied C1
throw (
  InteractionClassNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 5.5
void RTI::RTIambassador::unpublishInteractionClass (
  InteractionClassHandle theInteraction) // supplied C1
throw (
  InteractionClassNotDefined,
  InteractionClassNotPublished,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 5.6
void RTI::RTIambassador::subscribeObjectClassAttributes (
        ObjectClassHandle   theClass,      // supplied C1
  const AttributeHandleSet& attributeList, // supplied C4
        Boolean        active)
throw (
  ObjectClassNotDefined,
  AttributeNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 5.7
void RTI::RTIambassador::unsubscribeObjectClass (
  ObjectClassHandle theClass) // supplied C1
throw (
  ObjectClassNotDefined,
  ObjectClassNotSubscribed,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 5.8
void RTI::RTIambassador::subscribeInteractionClass (
  InteractionClassHandle theClass, // supplied C1
  Boolean           active)
throw (
  InteractionClassNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  FederateLoggingServiceCalls,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 5.9
void RTI::RTIambassador::unsubscribeInteractionClass (
  InteractionClassHandle theClass) // supplied C1
throw (
  InteractionClassNotDefined,
  InteractionClassNotSubscribed,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

////////////////////////////////
// Object Management Services //
////////////////////////////////

// 6.2
RTI::ObjectHandle                          // returned C3
RTI::RTIambassador::registerObjectInstance (
        ObjectClassHandle  theClass,  // supplied C1
  const char              *theObject) // supplied C4
throw (
  ObjectClassNotDefined,
  ObjectClassNotPublished,
  ObjectAlreadyRegistered,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) {
    return static_cast<ObjectHandle>(0);
}

RTI::ObjectHandle                         // returned C3
RTI::RTIambassador::registerObjectInstance (
        ObjectClassHandle theClass)  // supplied C1
throw (
  ObjectClassNotDefined,
  ObjectClassNotPublished,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) {
    return static_cast<ObjectHandle>(0);
}

// 6.4
RTI::EventRetractionHandle                               // returned C3
RTI::RTIambassador::updateAttributeValues (
        ObjectHandle                 theObject,     // supplied C1
  const AttributeHandleValuePairSet& theAttributes, // supplied C4
  const FedTime&                     theTime,       // supplied C4
  const char                        *theTag)        // supplied C4
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  InvalidFederationTime,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) {

    EventRetractionHandle eventRetractionHandle;
    eventRetractionHandle.theSerialNumber = 0;
    eventRetractionHandle.sendingFederate = 0;
    return eventRetractionHandle;
}

void RTI::RTIambassador::updateAttributeValues (
        ObjectHandle                 theObject,     // supplied C1
  const AttributeHandleValuePairSet& theAttributes, // supplied C4
  const char                        *theTag)        // supplied C4
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 6.6
RTI::EventRetractionHandle                                // returned C3
RTI::RTIambassador::sendInteraction (
        InteractionClassHandle       theInteraction, // supplied C1
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
  RTIinternalError) {

    EventRetractionHandle eventRetractionHandle;
    eventRetractionHandle.theSerialNumber = 0;
    eventRetractionHandle.sendingFederate = 0;
    return eventRetractionHandle;
}

void RTI::RTIambassador::sendInteraction (
        InteractionClassHandle       theInteraction, // supplied C1
  const ParameterHandleValuePairSet& theParameters,  // supplied C4
  const char                        *theTag)         // supplied C4
throw (
  InteractionClassNotDefined,
  InteractionClassNotPublished,
  InteractionParameterNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 6.8
RTI::EventRetractionHandle                 // returned C3
RTI::RTIambassador::deleteObjectInstance (
        ObjectHandle    theObject,    // supplied C1
  const FedTime&        theTime,      // supplied C4
  const char           *theTag)       // supplied C4
throw (
  ObjectNotKnown,
  DeletePrivilegeNotHeld,
  InvalidFederationTime,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) {

    EventRetractionHandle eventRetractionHandle;
    eventRetractionHandle.theSerialNumber = 0;
    eventRetractionHandle.sendingFederate = 0;
    return eventRetractionHandle;
}

void RTI::RTIambassador::deleteObjectInstance (
        ObjectHandle    theObject,    // supplied C1
  const char           *theTag)       // supplied C4
throw (
  ObjectNotKnown,
  DeletePrivilegeNotHeld,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 6.10
void RTI::RTIambassador::localDeleteObjectInstance (
  ObjectHandle    theObject)       // supplied C1
throw (
  ObjectNotKnown,
  FederateOwnsAttributes,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 6.11
void RTI::RTIambassador::changeAttributeTransportationType (
        ObjectHandle             theObject,     // supplied C1
  const AttributeHandleSet&      theAttributes, // supplied C4
        TransportationHandle     theType)       // supplied C1
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  InvalidTransportationHandle,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 6.12
void RTI::RTIambassador::changeInteractionTransportationType (
  InteractionClassHandle theClass, // supplied C1
  TransportationHandle   theType)  // supplied C1
throw (
  InteractionClassNotDefined,
  InteractionClassNotPublished,
  InvalidTransportationHandle,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 6.15
void RTI::RTIambassador::requestObjectAttributeValueUpdate (
        ObjectHandle        theObject,     // supplied C1
  const AttributeHandleSet& theAttributes) // supplied C4
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

void RTI::RTIambassador::requestClassAttributeValueUpdate (
        ObjectClassHandle   theClass,      // supplied C1
  const AttributeHandleSet& theAttributes) // supplied C4
throw (
  ObjectClassNotDefined,
  AttributeNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

///////////////////////////////////
// Ownership Management Services //
///////////////////////////////////

// 7.2
void RTI::RTIambassador::unconditionalAttributeOwnershipDivestiture (
        ObjectHandle                  theObject,     // supplied C1
  const AttributeHandleSet&           theAttributes) // supplied C4
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 7.3
void RTI::RTIambassador::negotiatedAttributeOwnershipDivestiture (
        ObjectHandle                  theObject,     // supplied C1
  const AttributeHandleSet&           theAttributes, // supplied C4
  const char                         *theTag)        // supplied C4
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  AttributeAlreadyBeingDivested,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 7.7
void RTI::RTIambassador::attributeOwnershipAcquisition (
        ObjectHandle        theObject,         // supplied C1
  const AttributeHandleSet& desiredAttributes, // supplied C4
  const char               *theTag)            // supplied C4
throw (
  ObjectNotKnown,
  ObjectClassNotPublished,
  AttributeNotDefined,
  AttributeNotPublished,
  FederateOwnsAttributes,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 7.8
void RTI::RTIambassador::attributeOwnershipAcquisitionIfAvailable (
        ObjectHandle        theObject,         // supplied C1
  const AttributeHandleSet& desiredAttributes) // supplied C4
throw (
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
  RTIinternalError) { }

// 7.11
RTI::AttributeHandleSet*                        // returned C6
RTI::RTIambassador::attributeOwnershipReleaseResponse (
        ObjectHandle        theObject,     // supplied C1
  const AttributeHandleSet& theAttributes) // supplied C4
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  FederateWasNotAskedToReleaseAttribute,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) {

    return new AttributeHandleSetTest();
}

// 7.12
void RTI::RTIambassador::cancelNegotiatedAttributeOwnershipDivestiture (
        ObjectHandle        theObject,     // supplied C1
  const AttributeHandleSet& theAttributes) // supplied C4
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  AttributeDivestitureWasNotRequested,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 7.13
void RTI::RTIambassador::cancelAttributeOwnershipAcquisition (
        ObjectHandle        theObject,     // supplied C1
  const AttributeHandleSet& theAttributes) // supplied C4
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeAlreadyOwned,
  AttributeAcquisitionWasNotRequested,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 7.15
void RTI::RTIambassador::queryAttributeOwnership (
  ObjectHandle    theObject,    // supplied C1
  AttributeHandle theAttribute) // supplied C1
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 7.17
RTI::Boolean                          // returned C3
RTI::RTIambassador::isAttributeOwnedByFederate (
  ObjectHandle    theObject,     // supplied C1
  AttributeHandle theAttribute)  // supplied C1
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) {

    return RTI_FALSE;
}

//////////////////////////////
// Time Management Services //
//////////////////////////////

// 8.2
void RTI::RTIambassador::enableTimeRegulation (
  const FedTime& theFederateTime,  // supplied C4
  const FedTime& theLookahead)     // supplied C4
throw (
  TimeRegulationAlreadyEnabled,
  EnableTimeRegulationPending,
  TimeAdvanceAlreadyInProgress,
  InvalidFederationTime,
  InvalidLookahead,
  ConcurrentAccessAttempted,
  FederateNotExecutionMember,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 8.4
void RTI::RTIambassador::disableTimeRegulation ()
throw (
  TimeRegulationWasNotEnabled,
  ConcurrentAccessAttempted,
  FederateNotExecutionMember,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 8.5
void RTI::RTIambassador::enableTimeConstrained ()
throw (
  TimeConstrainedAlreadyEnabled,
  EnableTimeConstrainedPending,
  TimeAdvanceAlreadyInProgress,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 8.7
void RTI::RTIambassador::disableTimeConstrained ()
throw (
  TimeConstrainedWasNotEnabled,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 8.8
void RTI::RTIambassador::timeAdvanceRequest (
 const  FedTime& theTime) // supplied C4
throw (
  InvalidFederationTime,
  FederationTimeAlreadyPassed,
  TimeAdvanceAlreadyInProgress,
  EnableTimeRegulationPending,
  EnableTimeConstrainedPending,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 8.9
void RTI::RTIambassador::timeAdvanceRequestAvailable (
const FedTime& theTime) // supplied C4
  throw (
    InvalidFederationTime,
    FederationTimeAlreadyPassed,
    TimeAdvanceAlreadyInProgress,
    EnableTimeRegulationPending,
    EnableTimeConstrainedPending,
    FederateNotExecutionMember,
    ConcurrentAccessAttempted,
    SaveInProgress,
    RestoreInProgress,
    RTIinternalError) { }

// 8.10
void RTI::RTIambassador::nextEventRequest (
  const FedTime& theTime) // supplied C4
throw (
  InvalidFederationTime,
  FederationTimeAlreadyPassed,
  TimeAdvanceAlreadyInProgress,
  EnableTimeRegulationPending,
  EnableTimeConstrainedPending,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 8.11
void RTI::RTIambassador::nextEventRequestAvailable (
  const FedTime& theTime) // supplied C4
throw (
  InvalidFederationTime,
  FederationTimeAlreadyPassed,
  TimeAdvanceAlreadyInProgress,
  EnableTimeRegulationPending,
  EnableTimeConstrainedPending,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 8.12
void RTI::RTIambassador::flushQueueRequest (
  const FedTime& theTime) // supplied C4
throw (
  InvalidFederationTime,
  FederationTimeAlreadyPassed,
  TimeAdvanceAlreadyInProgress,
  EnableTimeRegulationPending,
  EnableTimeConstrainedPending,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 8.14
void RTI::RTIambassador::enableAsynchronousDelivery()
  throw (
    AsynchronousDeliveryAlreadyEnabled,
    FederateNotExecutionMember,
    ConcurrentAccessAttempted,
    SaveInProgress,
    RestoreInProgress,
    RTIinternalError) { }

// 8.15
void RTI::RTIambassador::disableAsynchronousDelivery()
  throw (
    AsynchronousDeliveryAlreadyDisabled,
    FederateNotExecutionMember,
    ConcurrentAccessAttempted,
    SaveInProgress,
    RestoreInProgress,
    RTIinternalError) { }

// 8.16
void RTI::RTIambassador::queryLBTS (
  FedTime& theTime) // returned C5
throw (
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 8.17
void RTI::RTIambassador::queryFederateTime (
  FedTime& theTime) // returned C5
throw (
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 8.18
void RTI::RTIambassador::queryMinNextEventTime (
  FedTime& theTime) // returned C5
throw (
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 8.19
void RTI::RTIambassador::modifyLookahead (
  const FedTime& theLookahead) // supplied C4
throw (
  InvalidLookahead,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 8.20
void RTI::RTIambassador::queryLookahead (
   FedTime& theTime) // returned C5
throw (
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 8.21
void RTI::RTIambassador::retract (
  EventRetractionHandle theHandle) // supplied C1
throw (
  InvalidRetractionHandle,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 8.23
void RTI::RTIambassador::changeAttributeOrderType (
        ObjectHandle        theObject,     // supplied C1
  const AttributeHandleSet& theAttributes, // supplied C4
        OrderingHandle      theType)       // supplied C1
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  AttributeNotOwned,
  InvalidOrderingHandle,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 8.24
void RTI::RTIambassador::changeInteractionOrderType (
  InteractionClassHandle theClass, // supplied C1
  OrderingHandle         theType)  // supplied C1
throw (
  InteractionClassNotDefined,
  InteractionClassNotPublished,
  InvalidOrderingHandle,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

//////////////////////////////////
// Data Distribution Management //
//////////////////////////////////

// 9.2
RTI::Region*                           // returned C6
RTI::RTIambassador::createRegion (
  SpaceHandle theSpace,           // supplied C1
  ULong       numberOfExtents)    // supplied C1
throw (
  SpaceNotDefined,
  InvalidExtents,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) {

    return nullptr;
}


// 9.3
void RTI::RTIambassador::notifyAboutRegionModification (
  Region &theRegion)  // supplied C4
throw (
  RegionNotKnown,
  InvalidExtents,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 9.4
void RTI::RTIambassador::deleteRegion (
  Region *theRegion) // supplied C1
throw (
  RegionNotKnown,
  RegionInUse,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 9.5
RTI::ObjectHandle                                  // returned C3
RTI::RTIambassador::registerObjectInstanceWithRegion (
        ObjectClassHandle theClass,           // supplied C1
  const char             *theObject,          // supplied C4
        AttributeHandle   theAttributes[],    // supplied C4
        Region           *theRegions[],       // supplied C4
        ULong             theNumberOfHandles) // supplied C1
throw (
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
  RTIinternalError) {
    return static_cast<ObjectHandle>(0);
}

RTI::ObjectHandle                              // returned C3
RTI::RTIambassador::registerObjectInstanceWithRegion (
  ObjectClassHandle theClass,             // supplied C1
  AttributeHandle   theAttributes[],      // supplied C4
  Region           *theRegions[],         // supplied C4
  ULong             theNumberOfHandles)   // supplied C1
throw (
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
  RTIinternalError) {
    return static_cast<ObjectHandle>(0);
}

// 9.6
void RTI::RTIambassador::associateRegionForUpdates (
        Region             &theRegion,     // supplied C4
        ObjectHandle        theObject,     // supplied C1
  const AttributeHandleSet &theAttributes) // supplied C4
throw (
  ObjectNotKnown,
  AttributeNotDefined,
  InvalidRegionContext,
  RegionNotKnown,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 9.7
void RTI::RTIambassador::unassociateRegionForUpdates (
  Region       &theRegion,     // supplied C4
  ObjectHandle  theObject)     // supplied C1
throw (
  ObjectNotKnown,
  InvalidRegionContext,
  RegionNotKnown,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 9.8
void RTI::RTIambassador::subscribeObjectClassAttributesWithRegion (
        ObjectClassHandle   theClass,      // supplied C1
        Region             &theRegion,     // supplied C4
  const AttributeHandleSet &attributeList, // supplied C4
        Boolean        active)
throw (
  ObjectClassNotDefined,
  AttributeNotDefined,
  RegionNotKnown,
  InvalidRegionContext,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 9.9
void RTI::RTIambassador::unsubscribeObjectClassWithRegion (
  ObjectClassHandle theClass,          // supplied C1
  Region           &theRegion)         // supplied C4
throw (
  ObjectClassNotDefined,
  RegionNotKnown,
  ObjectClassNotSubscribed,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 9.10
void RTI::RTIambassador::subscribeInteractionClassWithRegion (
  InteractionClassHandle theClass,        // supplied C1
  Region                &theRegion,       // supplied C4
  Boolean           active)
throw (
  InteractionClassNotDefined,
  RegionNotKnown,
  InvalidRegionContext,
  FederateLoggingServiceCalls,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 9.11
void RTI::RTIambassador::unsubscribeInteractionClassWithRegion (
  InteractionClassHandle theClass,  // supplied C1
  Region                &theRegion) // supplied C4
throw (
  InteractionClassNotDefined,
  InteractionClassNotSubscribed,
  RegionNotKnown,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 9.12
RTI::EventRetractionHandle                                // returned C3
RTI::RTIambassador::sendInteractionWithRegion (
        InteractionClassHandle       theInteraction, // supplied C1
  const ParameterHandleValuePairSet &theParameters,  // supplied C4
  const FedTime&                     theTime,        // supplied C4
  const char                        *theTag,         // supplied C4
  const Region                      &theRegion)      // supplied C4
throw (
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
  RTIinternalError) {

      EventRetractionHandle eventRetractionHandle;
      eventRetractionHandle.theSerialNumber = 0;
      eventRetractionHandle.sendingFederate = 0;
      return eventRetractionHandle;
}

void RTI::RTIambassador::sendInteractionWithRegion (
  InteractionClassHandle       theInteraction, // supplied C1
  const ParameterHandleValuePairSet &theParameters,  // supplied C4
  const char                        *theTag,         // supplied C4
  const Region                      &theRegion)      // supplied C4
throw (
  InteractionClassNotDefined,
  InteractionClassNotPublished,
  InteractionParameterNotDefined,
  RegionNotKnown,
  InvalidRegionContext,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 9.13
void RTI::RTIambassador::requestClassAttributeValueUpdateWithRegion (
        ObjectClassHandle   theClass,      // supplied C1
  const AttributeHandleSet &theAttributes, // supplied C4
  const Region             &theRegion)     // supplied C4
throw (
  ObjectClassNotDefined,
  AttributeNotDefined,
  RegionNotKnown,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

//////////////////////////
// RTI Support Services //
//////////////////////////

// 10.2
RTI::ObjectClassHandle      // returned C3
RTI::RTIambassador::getObjectClassHandle (
  const char *theName) // supplied C4
throw (
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError) {

    return static_cast<ObjectClassHandle>(0);
}

// 10.3
char *                         // returned C6
RTI::RTIambassador::getObjectClassName (
  ObjectClassHandle theHandle) // supplied C1
throw (
  ObjectClassNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError) {

    return nullptr;
}

// 10.4
RTI::AttributeHandle                       // returned C3
RTI::RTIambassador::getAttributeHandle (
  const char             *theName,    // supplied C4
        ObjectClassHandle whichClass) // supplied C1
throw (
  ObjectClassNotDefined,
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError) {

    return static_cast<AttributeHandle>(0);
}

// 10.5
char *                          // returned C6
RTI::RTIambassador::getAttributeName (
  AttributeHandle   theHandle,  // supplied C1
  ObjectClassHandle whichClass) // supplied C1
throw (
  ObjectClassNotDefined,
  AttributeNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError) {

    return nullptr;
}

const ClassNameToHandleMap &get_class_name_handle_map_aux() {
    static ClassNameToHandleMap classNameToHandleMap;

    int handleValue = 0;

    classNameToHandleMap["InteractionRoot"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameToHandleMap["InteractionRoot.C2WInteractionRoot"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameToHandleMap["InteractionRoot.C2WInteractionRoot.ActionBase"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameToHandleMap["InteractionRoot.C2WInteractionRoot.FederateJoinInteraction"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameToHandleMap["InteractionRoot.C2WInteractionRoot.FederateResignInteraction"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameToHandleMap["InteractionRoot.C2WInteractionRoot.OutcomeBase"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameToHandleMap["InteractionRoot.C2WInteractionRoot.SimLog"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameToHandleMap["InteractionRoot.C2WInteractionRoot.SimLog.HighPrio"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameToHandleMap["InteractionRoot.C2WInteractionRoot.SimLog.HighPrio"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameToHandleMap["InteractionRoot.C2WInteractionRoot.SimLog.LowPrio"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameToHandleMap["InteractionRoot.C2WInteractionRoot.SimLog.MediumPrio"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameToHandleMap["InteractionRoot.C2WInteractionRoot.SimLog.VeryLowPrio"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameToHandleMap["InteractionRoot.C2WInteractionRoot.SimulationControl"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameToHandleMap["InteractionRoot.C2WInteractionRoot.SimulationControl.SimEnd"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameToHandleMap["InteractionRoot.C2WInteractionRoot.SimulationControl.SimPause"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameToHandleMap["InteractionRoot.C2WInteractionRoot.SimulationControl.SimResume"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    return classNameToHandleMap;
}

const ClassNameToHandleMap &get_class_name_handle_map() {
    static const ClassNameToHandleMap &classNameToHandleMap = get_class_name_handle_map_aux();
    return classNameToHandleMap;
}


// 10.6
RTI::InteractionClassHandle      // returned C3
RTI::RTIambassador::getInteractionClassHandle (const char *theName)
  throw (NameNotFound, FederateNotExecutionMember, ConcurrentAccessAttempted, RTIinternalError) {

    ClassNameToHandleMap::const_iterator chmCit = get_class_name_handle_map().find(theName);
    return chmCit == get_class_name_handle_map().end() ?
      std::numeric_limits<RTI::InteractionClassHandle>::max() : chmCit->second;
}

// 10.7
char *                              // returned C6
RTI::RTIambassador::getInteractionClassName (
  InteractionClassHandle theHandle) // supplied C1
throw (
  InteractionClassNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError) {

    return nullptr;
}

// 10.8
RTI::ParameterHandle                            // returned C3
RTI::RTIambassador::getParameterHandle (
  const char *theName,                     // supplied C4
        InteractionClassHandle whichClass) // supplied C1
throw (
  InteractionClassNotDefined,
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError) {

    return static_cast<ParameterHandle>(0);
}

// 10.9
char *                               // returned C6
RTI::RTIambassador::getParameterName (
  ParameterHandle        theHandle,  // supplied C1
  InteractionClassHandle whichClass) // supplied C1
throw (
  InteractionClassNotDefined,
  InteractionParameterNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError) {

    return nullptr;
}

// 10.10
RTI::ObjectHandle                 // returned C3
RTI::RTIambassador::getObjectInstanceHandle (
  const char *theName)       // supplied C4
throw (
  ObjectNotKnown,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError) {

    return static_cast<ObjectHandle>(0);
}

// 10.11
char *                     // returned C6
RTI::RTIambassador::getObjectInstanceName (
  ObjectHandle theHandle)  // supplied C1
throw (
  ObjectNotKnown,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError) {

    return nullptr;
}

// 10.12
RTI::SpaceHandle                // returned C3
RTI::RTIambassador::getRoutingSpaceHandle (
  const char *theName)     // supplied C4
throw (
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError) {

    return static_cast<SpaceHandle>(0);
}

// 10.13
char *                         // returned C6
RTI::RTIambassador::getRoutingSpaceName (
   //
   // This const was removed for the RTI 1.3 NG to work around a limitation of
   // the Sun 4.2 C++ compiler regarding template instantiation.  The const
   // is unnecessary.
   //
   /* const */ SpaceHandle theHandle) // supplied C4
throw (
  SpaceNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError) {

    return nullptr;
}

// 10.14
RTI::DimensionHandle                   // returned C3
RTI::RTIambassador::getDimensionHandle (
  const char         *theName,    // supplied C4
        SpaceHandle   whichSpace) // supplied C1
throw (
  SpaceNotDefined,
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError) {

    return static_cast<DimensionHandle>(0);
}

// 10.15
char *                        // returned C6
RTI::RTIambassador::getDimensionName (
  DimensionHandle theHandle,  // supplied C1
  SpaceHandle     whichSpace) // supplied C1
throw (
  SpaceNotDefined,
  DimensionNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError) {

    return nullptr;
}

// 10.16
RTI::SpaceHandle                      // returned C3
RTI::RTIambassador::getAttributeRoutingSpaceHandle (
  AttributeHandle   theHandle,   // supplied C1
  ObjectClassHandle whichClass)  // supplied C1
throw (
  ObjectClassNotDefined,
  AttributeNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError) {

    return static_cast<SpaceHandle>(0);
}

// 10.17
RTI::ObjectClassHandle            // returned C3
RTI::RTIambassador::getObjectClass (
  ObjectHandle theObject)    // supplied C1
throw (
  ObjectNotKnown,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError) {

    return static_cast<ObjectClassHandle>(0);
}

// 10.18
RTI::SpaceHandle                             // returned C3
RTI::RTIambassador::getInteractionRoutingSpaceHandle (
  InteractionClassHandle   theHandle)   // supplied C1
throw (
  InteractionClassNotDefined,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError) {

    return static_cast<SpaceHandle>(0);
}

// 10.19
RTI::TransportationHandle      // returned C3
RTI::RTIambassador::getTransportationHandle (
  const char *theName)    // supplied C4
throw (
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError) {

    return static_cast<TransportationHandle>(0);

}

// 10.20
char *                            // returned C6
RTI::RTIambassador::getTransportationName (
  TransportationHandle theHandle) // supplied C1
throw (
  InvalidTransportationHandle,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError) {

    return nullptr;
}

// 10.21
RTI::OrderingHandle         // returned C3
RTI::RTIambassador::getOrderingHandle (
  const char *theName) // supplied C4
throw (
  NameNotFound,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError) {

    return static_cast<OrderingHandle>(0);
}

// 10.22
char *                      // returned C6
RTI::RTIambassador::getOrderingName (
  OrderingHandle theHandle) // supplied C1
throw (
  InvalidOrderingHandle,
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RTIinternalError) {

    return nullptr;
}

// 10.23
void RTI::RTIambassador::enableClassRelevanceAdvisorySwitch()
throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 10.24
void RTI::RTIambassador::disableClassRelevanceAdvisorySwitch()
throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 10.25
void RTI::RTIambassador::enableAttributeRelevanceAdvisorySwitch()
throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 10.26
void RTI::RTIambassador::disableAttributeRelevanceAdvisorySwitch()
throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 10.27
void RTI::RTIambassador::enableAttributeScopeAdvisorySwitch()
throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 10.28
void RTI::RTIambassador::disableAttributeScopeAdvisorySwitch()
throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 10.29
void RTI::RTIambassador::enableInteractionRelevanceAdvisorySwitch()
throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

// 10.30
void RTI::RTIambassador::disableInteractionRelevanceAdvisorySwitch()
throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  SaveInProgress,
  RestoreInProgress,
  RTIinternalError) { }

//
RTI::Boolean // returned C3
RTI::RTIambassador::tick ()
throw (
  SpecifiedSaveLabelDoesNotExist,
  ConcurrentAccessAttempted,
  RTIinternalError) {

    return RTI_FALSE;
}

RTI::Boolean             // returned C3
RTI::RTIambassador::tick (
  TickTime minimum, // supplied C1
  TickTime maximum) // supplied C1
throw (
  SpecifiedSaveLabelDoesNotExist,
  ConcurrentAccessAttempted,
  RTIinternalError) {

    return RTI_FALSE;
}

RTI::RTIambassador::RTIambassador()
throw (
  MemoryExhausted,
  RTIinternalError) { }

RTI::RTIambassador::~RTIambassador()
throw (RTIinternalError) { }

RTI::RegionToken
RTI::RTIambassador::getRegionToken(
  Region *)
throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RegionNotKnown,
  RTIinternalError) {

    return static_cast<RegionToken>(0);
}

RTI::Region *
RTI::RTIambassador::getRegion(
  RegionToken)
throw(
  FederateNotExecutionMember,
  ConcurrentAccessAttempted,
  RegionNotKnown,
  RTIinternalError) {

    return nullptr;
}

