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

#ifndef RTI_TEST_PROXY_HH
#define RTI_TEST_PROXY_HH

#include "RTIForTesting.hpp"

#if __cplusplus >= 201703L
#define MultiArgTuple17
#define Tuple17 noexcept
#define throw(...) __VA_OPT__(MultiArg)##Tuple17
#endif

namespace RTIProxy {

class RTIAmbassadorProxy {
public:

    ////////////////////////////////////
    // Federation Management Services //
    ////////////////////////////////////

    // 4.2
    virtual void createFederationExecution (
      const char *executionName, // supplied C4
      const char *FED            // supplied C4
    ) throw (
      RTI::FederationExecutionAlreadyExists,
      RTI::CouldNotOpenFED,
      RTI::ErrorReadingFED,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 4.3
    virtual void destroyFederationExecution (
      const char *executionName // supplied C4
    ) throw (
      RTI::FederatesCurrentlyJoined,
      RTI::FederationExecutionDoesNotExist,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 4.4
    virtual RTI::FederateHandle joinFederationExecution (        // returned C3
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
    );

    // 4.5
    virtual void resignFederationExecution (
      RTI::ResignAction theAction // supplied C1
    ) throw (
      RTI::FederateOwnsAttributes,
      RTI::FederateNotExecutionMember,
      RTI::InvalidResignAction,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 4.6
    virtual void registerFederationSynchronizationPoint (
      const char *label,  // supplied C4
      const char *theTag  // supplied C4
    ) throw (
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    virtual void registerFederationSynchronizationPoint (
      const char                *label,    // supplied C4
      const char                *theTag,   // supplied C4
      const RTI::FederateHandleSet&   syncSet   // supplied C4
    ) throw (
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 4.9
    virtual void synchronizationPointAchieved (
      const char *label  // supplied C4
    ) throw (
      RTI::SynchronizationPointLabelWasNotAnnounced,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 4.11
    virtual void requestFederationSave (
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
    );

    virtual void requestFederationSave (
      const char *label)     // supplied C4
      throw (
        RTI::FederateNotExecutionMember,
        RTI::ConcurrentAccessAttempted,
        RTI::SaveInProgress,
        RTI::RestoreInProgress,
        RTI::RTIinternalError
    );

    // 4.13
    virtual void federateSaveBegun () throw (
      RTI::SaveNotInitiated,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 4.14
    virtual void federateSaveComplete () throw (
      RTI::SaveNotInitiated,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    virtual void federateSaveNotComplete () throw (
      RTI::SaveNotInitiated,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 4.16
    virtual void requestFederationRestore (
      const char *label // supplied C4
    ) throw (
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 4.20
    virtual void federateRestoreComplete () throw (
      RTI::RestoreNotRequested,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RTIinternalError
    );

    virtual void federateRestoreNotComplete () throw (
      RTI::RestoreNotRequested,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RTIinternalError
    );

    /////////////////////////////////////
    // Declaration Management Services //
    /////////////////////////////////////

    // 5.2
    virtual void publishObjectClass (
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
    );

    // 5.3
    virtual void unpublishObjectClass (
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
    );

    // 5.4
    virtual void publishInteractionClass (
      RTI::InteractionClassHandle theInteraction  // supplied C1
    ) throw (
      RTI::InteractionClassNotDefined,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 5.5
    virtual void unpublishInteractionClass (
      RTI::InteractionClassHandle theInteraction  // supplied C1
    ) throw (
      RTI::InteractionClassNotDefined,
      RTI::InteractionClassNotPublished,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 5.6
    virtual void subscribeObjectClassAttributes (
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
     );

    // 5.7
    virtual void unsubscribeObjectClass (
      RTI::ObjectClassHandle theClass  // supplied C1
    ) throw (
      RTI::ObjectClassNotDefined,
      RTI::ObjectClassNotSubscribed,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 5.8
    virtual void subscribeInteractionClass (
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
    );

    // 5.9
    virtual void unsubscribeInteractionClass (
      RTI::InteractionClassHandle theClass  // supplied C1
    ) throw (
      RTI::InteractionClassNotDefined,
      RTI::InteractionClassNotSubscribed,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    ////////////////////////////////
    // Object Management Services //
    ////////////////////////////////

    // 6.2
    virtual RTI::ObjectHandle registerObjectInstance (  // returned C3
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
    );

    virtual RTI::ObjectHandle registerObjectInstance (  // returned C3
      RTI::ObjectClassHandle theClass           // supplied C1
    ) throw (
      RTI::ObjectClassNotDefined,
      RTI::ObjectClassNotPublished,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 6.4
    virtual RTI::EventRetractionHandle updateAttributeValues (       // returned C3
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
    );

    virtual void updateAttributeValues (
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
    );

    // 6.6
    virtual RTI::EventRetractionHandle sendInteraction (              // returned C3
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
    );

    virtual void sendInteraction (
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
    );

    // 6.8
    virtual RTI::EventRetractionHandle deleteObjectInstance ( // returned C3
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
    );

    virtual void deleteObjectInstance (
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
    );

    // 6.10
    virtual void localDeleteObjectInstance (
      RTI::ObjectHandle    theObject       // supplied C1
    ) throw (
      RTI::ObjectNotKnown,
      RTI::FederateOwnsAttributes,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 6.11
    virtual void changeAttributeTransportationType (
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
    );

    // 6.12
    virtual void changeInteractionTransportationType (
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
    );

    // 6.15
    virtual void requestObjectAttributeValueUpdate (
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
    );

    virtual void requestClassAttributeValueUpdate (
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
    );

    ///////////////////////////////////
    // Ownership Management Services //
    ///////////////////////////////////

    // 7.2
    virtual void unconditionalAttributeOwnershipDivestiture (
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
    );

    // 7.3
    virtual void negotiatedAttributeOwnershipDivestiture (
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
    );

    // 7.7
    virtual void attributeOwnershipAcquisition (
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
    );

    // 7.8
    virtual void attributeOwnershipAcquisitionIfAvailable (
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
    );

    // 7.11
    virtual RTI::AttributeHandleSet* attributeOwnershipReleaseResponse ( // returned C6
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
    );

    // 7.12
    virtual void cancelNegotiatedAttributeOwnershipDivestiture (
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
    );

    // 7.13
    virtual void cancelAttributeOwnershipAcquisition (
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
    );

    // 7.15
    virtual void queryAttributeOwnership (
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
    );

    // 7.17
    virtual RTI::Boolean isAttributeOwnedByFederate ( // returned C3
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
    );

    //////////////////////////////
    // Time Management Services //
    //////////////////////////////

    // 8.2
    virtual void enableTimeRegulation (
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
    );

    // 8.4
    virtual void disableTimeRegulation () throw (
      RTI::TimeRegulationWasNotEnabled,
      RTI::ConcurrentAccessAttempted,
      RTI::FederateNotExecutionMember,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 8.5
    virtual void enableTimeConstrained () throw (
      RTI::TimeConstrainedAlreadyEnabled,
      RTI::EnableTimeConstrainedPending,
      RTI::TimeAdvanceAlreadyInProgress,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 8.7
    virtual void disableTimeConstrained () throw (
      RTI::TimeConstrainedWasNotEnabled,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 8.8
    virtual void timeAdvanceRequest (
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
    );

    // 8.9
    virtual void timeAdvanceRequestAvailable (
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
    );

    // 8.10
    virtual void nextEventRequest (
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
    );

    // 8.11
    virtual void nextEventRequestAvailable (
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
    );

    // 8.12
    virtual void flushQueueRequest (
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
    );

    // 8.14
    virtual void enableAsynchronousDelivery() throw (
      RTI::AsynchronousDeliveryAlreadyEnabled,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 8.15
    virtual void disableAsynchronousDelivery() throw (
      RTI::AsynchronousDeliveryAlreadyDisabled,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 8.16
    virtual void queryLBTS (
      RTI::FedTime& theTime  // returned C5
    ) throw (
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 8.17
    virtual void queryFederateTime (
      RTI::FedTime& theTime  // returned C5
    ) throw (
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 8.18
    virtual void queryMinNextEventTime (
      RTI::FedTime& theTime  // returned C5
    ) throw (
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 8.19
    virtual void modifyLookahead (
      const RTI::FedTime& theLookahead  // supplied C4
    ) throw (
      RTI::InvalidLookahead,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 8.20
    virtual void queryLookahead (
       RTI::FedTime& theTime  // returned C5
    ) throw (
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 8.21
    virtual void retract (
      RTI::EventRetractionHandle theHandle  // supplied C1
    ) throw (
      RTI::InvalidRetractionHandle,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 8.23
    virtual void changeAttributeOrderType (
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
    );

    // 8.24
    virtual void changeInteractionOrderType (
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
    );

    //////////////////////////////////
    // Data Distribution Management //
    //////////////////////////////////

    // 9.2
    virtual RTI::Region *createRegion (    // returned C6
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
    );


    // 9.3
    virtual void notifyAboutRegionModification (
      RTI::Region &theRegion   // supplied C4
    ) throw (
      RTI::RegionNotKnown,
      RTI::InvalidExtents,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 9.4
    virtual void deleteRegion (
      RTI::Region *theRegion  // supplied C1
    ) throw (
      RTI::RegionNotKnown,
      RTI::RegionInUse,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 9.5
    virtual RTI::ObjectHandle registerObjectInstanceWithRegion (  // returned C3
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
    );

    virtual RTI::ObjectHandle registerObjectInstanceWithRegion (  // returned C3
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
    );

    // 9.6
    virtual void associateRegionForUpdates (
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
    );

    // 9.7
    virtual void unassociateRegionForUpdates (
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
    );

    // 9.8
    virtual void subscribeObjectClassAttributesWithRegion (
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
    );

    // 9.9
    virtual void unsubscribeObjectClassWithRegion (
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
    );

    // 9.10
    virtual void subscribeInteractionClassWithRegion (
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
    );

    // 9.11
    virtual void unsubscribeInteractionClassWithRegion (
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
    );

    // 9.12
    virtual RTI::EventRetractionHandle sendInteractionWithRegion (  // returned C3
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
    );

    virtual void sendInteractionWithRegion (
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
    );

    // 9.13
    virtual void requestClassAttributeValueUpdateWithRegion (
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
    );

    //////////////////////////
    // RTI Support Services //
    //////////////////////////

    // 10.2
    virtual RTI::ObjectClassHandle getObjectClassHandle (  // returned C3
      const char *theName  // supplied C4
    ) throw (
      RTI::NameNotFound,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 10.3
    virtual char *getObjectClassName (     // returned C6
      RTI::ObjectClassHandle theHandle  // supplied C1
    ) throw (
      RTI::ObjectClassNotDefined,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 10.4
    virtual RTI::AttributeHandle getAttributeHandle (  // returned C3
      const char             *theName,    // supplied C4
            RTI::ObjectClassHandle whichClass  // supplied C1
    ) throw (
      RTI::ObjectClassNotDefined,
      RTI::NameNotFound,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 10.5
    virtual char *getAttributeName (  // returned C6
      RTI::AttributeHandle   theHandle,  // supplied C1
      RTI::ObjectClassHandle whichClass  // supplied C1
    ) throw (
      RTI::ObjectClassNotDefined,
      RTI::AttributeNotDefined,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 10.6
    virtual RTI::InteractionClassHandle getInteractionClassHandle ( // returned C3
      const char *theName      // supplied C4
    ) throw (
      RTI::NameNotFound,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 10.7
    virtual char * getInteractionClassName (  // returned C6
      RTI::InteractionClassHandle theHandle        // supplied C1
    ) throw (
      RTI::InteractionClassNotDefined,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 10.8
    virtual RTI::ParameterHandle getParameterHandle (  // returned C3
      const char *theName,                     // supplied C4
            RTI::InteractionClassHandle whichClass  // supplied C1
    ) throw (
      RTI::InteractionClassNotDefined,
      RTI::NameNotFound,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 10.9
    virtual char *getParameterName (     // returned C6
      RTI::ParameterHandle        theHandle,  // supplied C1
      RTI::InteractionClassHandle whichClass  // supplied C1
    ) throw (
      RTI::InteractionClassNotDefined,
      RTI::InteractionParameterNotDefined,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 10.10
    virtual RTI::ObjectHandle getObjectInstanceHandle (  // returned C3
      const char *theName        // supplied C4
    ) throw (
      RTI::ObjectNotKnown,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 10.11
    virtual char *getObjectInstanceName (  // returned C6
      RTI::ObjectHandle theHandle   // supplied C1
    ) throw (
      RTI::ObjectNotKnown,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 10.12
    virtual RTI::SpaceHandle getRoutingSpaceHandle (  // returned C3
      const char *theName      // supplied C4
    ) throw (
      RTI::NameNotFound,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 10.13
    virtual char *getRoutingSpaceName (  // returned C6
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
    );

    // 10.14
    virtual RTI::DimensionHandle getDimensionHandle (  // returned C3
      const char         *theName,    // supplied C4
            RTI::SpaceHandle   whichSpace  // supplied C1
    ) throw (
      RTI::SpaceNotDefined,
      RTI::NameNotFound,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 10.15
    virtual char *getDimensionName (  // returned C6
      RTI::DimensionHandle theHandle,  // supplied C1
      RTI::SpaceHandle     whichSpace  // supplied C1
    ) throw (
      RTI::SpaceNotDefined,
      RTI::DimensionNotDefined,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 10.16
    virtual RTI::SpaceHandle getAttributeRoutingSpaceHandle (  // returned C3
      RTI::AttributeHandle   theHandle,   // supplied C1
      RTI::ObjectClassHandle whichClass   // supplied C1
    ) throw (
      RTI::ObjectClassNotDefined,
      RTI::AttributeNotDefined,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 10.17
    virtual RTI::ObjectClassHandle getObjectClass (  // returned C3
      RTI::ObjectHandle theObject     // supplied C1
    ) throw (
      RTI::ObjectNotKnown,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 10.18
    virtual RTI::SpaceHandle getInteractionRoutingSpaceHandle (  // returned C3
      RTI::InteractionClassHandle   theHandle    // supplied C1
    ) throw (
      RTI::InteractionClassNotDefined,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 10.19
    virtual RTI::TransportationHandle getTransportationHandle (  // returned C3
      const char *theName     // supplied C4
    ) throw (
      RTI::NameNotFound,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 10.20
    virtual char *getTransportationName (  // returned C6
      RTI::TransportationHandle theHandle  // supplied C1
    ) throw (
      RTI::InvalidTransportationHandle,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 10.21
    virtual RTI::OrderingHandle getOrderingHandle (  // returned C3
      const char *theName  // supplied C4
    ) throw (
      RTI::NameNotFound,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 10.22
    virtual char *getOrderingName (  // returned C6
      RTI::OrderingHandle theHandle  // supplied C1
    ) throw (
      RTI::InvalidOrderingHandle,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    // 10.23
    virtual void enableClassRelevanceAdvisorySwitch() throw(
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 10.24
    virtual void disableClassRelevanceAdvisorySwitch() throw(
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 10.25
    virtual void enableAttributeRelevanceAdvisorySwitch() throw(
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 10.26
    virtual void disableAttributeRelevanceAdvisorySwitch() throw(
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 10.27
    virtual void enableAttributeScopeAdvisorySwitch() throw(
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 10.28
    virtual void disableAttributeScopeAdvisorySwitch() throw(
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 10.29
    virtual void enableInteractionRelevanceAdvisorySwitch() throw(
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    // 10.30
    virtual void disableInteractionRelevanceAdvisorySwitch() throw(
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    );

    //
    virtual RTI::Boolean tick () throw (  // returned C3
      RTI::SpecifiedSaveLabelDoesNotExist,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    virtual RTI::Boolean tick (  // returned C3
      RTI::TickTime minimum, // supplied C1
      RTI::TickTime maximum  // supplied C1
    ) throw (
      RTI::SpecifiedSaveLabelDoesNotExist,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    );

    RTIAmbassadorProxy() throw (
      RTI::MemoryExhausted,
      RTI::RTIinternalError
    );

    virtual ~RTIAmbassadorProxy() throw (
      RTI::RTIinternalError
    );

    virtual RTI::RegionToken getRegionToken(
      RTI::Region *returnPtr
    ) throw(
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RegionNotKnown,
      RTI::RTIinternalError
    );

    virtual RTI::Region *getRegion(
      RTI::RegionToken regionToken
    ) throw(
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RegionNotKnown,
      RTI::RTIinternalError
    );
};  // class RTIambassador

} // namespace RTIProxy

#if __cplusplus >= 201703L
#undef MultiArgTuple17
#undef Tuple17
#undef throw
#endif

#endif