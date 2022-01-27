#ifndef RTI_TEST_HH
#define RTI_TEST_HH


#define RTI_EXPORT
#define RTI_EXPORT_FEDTIME


#define CPSWT_TEST

#define RTI_STD std

namespace RTIProxy {
class RTIAmbassadorProxy;
}

class RTI {

public:
#include "baseTypes.hh"
#include "RTItypes.hh"

    class FederateAmbassador;

    class RTIambassador {
    private:
        RTIProxy::RTIAmbassadorProxy *rtiAmbassadorProxy;

    public:
        typedef FederateAmbassador *FederateAmbassadorPtr;

        ////////////////////////////////////
        // Federation Management Services //
        ////////////////////////////////////

        // 4.2
        void createFederationExecution (
          const char *executionName, // supplied C4
          const char *FED            // supplied C4
        ) throw (
          FederationExecutionAlreadyExists,
          CouldNotOpenFED,
          ErrorReadingFED,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 4.3
        void destroyFederationExecution (
          const char *executionName // supplied C4
        ) throw (
          FederatesCurrentlyJoined,
          FederationExecutionDoesNotExist,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 4.4
        FederateHandle joinFederationExecution (        // returned C3
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
        );

        // 4.5
        void resignFederationExecution (
          ResignAction theAction // supplied C1
        ) throw (
          FederateOwnsAttributes,
          FederateNotExecutionMember,
          InvalidResignAction,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 4.6
        void registerFederationSynchronizationPoint (
          const char *label,  // supplied C4
          const char *theTag  // supplied C4
        ) throw (
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        void registerFederationSynchronizationPoint (
          const char                *label,    // supplied C4
          const char                *theTag,   // supplied C4
          const FederateHandleSet&   syncSet   // supplied C4
        ) throw (
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 4.9
        void synchronizationPointAchieved (
          const char *label  // supplied C4
        ) throw (
          SynchronizationPointLabelWasNotAnnounced,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 4.11
        void requestFederationSave (
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
        );

        void requestFederationSave (
          const char *label)     // supplied C4
          throw (
            FederateNotExecutionMember,
            ConcurrentAccessAttempted,
            SaveInProgress,
            RestoreInProgress,
            RTIinternalError
        );

        // 4.13
        void federateSaveBegun () throw (
          SaveNotInitiated,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RestoreInProgress,
          RTIinternalError
        );

        // 4.14
        void federateSaveComplete () throw (
          SaveNotInitiated,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RestoreInProgress,
          RTIinternalError
        );

        void federateSaveNotComplete () throw (
          SaveNotInitiated,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RestoreInProgress,
          RTIinternalError
        );

        // 4.16
        void requestFederationRestore (
          const char *label // supplied C4
        ) throw (
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 4.20
        void federateRestoreComplete () throw (
          RestoreNotRequested,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RTIinternalError
        );

        void federateRestoreNotComplete () throw (
          RestoreNotRequested,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RTIinternalError
        );

        /////////////////////////////////////
        // Declaration Management Services //
        /////////////////////////////////////

        // 5.2
        void publishObjectClass (
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
        );

        // 5.3
        void unpublishObjectClass (
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
        );

        // 5.4
        void publishInteractionClass (
          InteractionClassHandle theInteraction  // supplied C1
        ) throw (
          InteractionClassNotDefined,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 5.5
        void unpublishInteractionClass (
          InteractionClassHandle theInteraction  // supplied C1
        ) throw (
          InteractionClassNotDefined,
          InteractionClassNotPublished,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 5.6
        void subscribeObjectClassAttributes (
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
         );

        // 5.7
        void unsubscribeObjectClass (
          ObjectClassHandle theClass  // supplied C1
        ) throw (
          ObjectClassNotDefined,
          ObjectClassNotSubscribed,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 5.8
        void subscribeInteractionClass (
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
        );

        // 5.9
        void unsubscribeInteractionClass (
          InteractionClassHandle theClass  // supplied C1
        ) throw (
          InteractionClassNotDefined,
          InteractionClassNotSubscribed,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        ////////////////////////////////
        // Object Management Services //
        ////////////////////////////////

        // 6.2
        ObjectHandle registerObjectInstance (  // returned C3
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
        );

        ObjectHandle registerObjectInstance (  // returned C3
          ObjectClassHandle theClass           // supplied C1
        ) throw (
          ObjectClassNotDefined,
          ObjectClassNotPublished,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 6.4
        EventRetractionHandle updateAttributeValues (       // returned C3
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
        );

        void updateAttributeValues (
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
        );

        // 6.6
        EventRetractionHandle sendInteraction (              // returned C3
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
        );

        void sendInteraction (
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
        );

        // 6.8
        EventRetractionHandle deleteObjectInstance ( // returned C3
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
        );

        void deleteObjectInstance (
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
        );

        // 6.10
        void localDeleteObjectInstance (
          ObjectHandle    theObject       // supplied C1
        ) throw (
          ObjectNotKnown,
          FederateOwnsAttributes,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 6.11
        void changeAttributeTransportationType (
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
        );

        // 6.12
        void changeInteractionTransportationType (
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
        );

        // 6.15
        void requestObjectAttributeValueUpdate (
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
        );

        void requestClassAttributeValueUpdate (
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
        );

        ///////////////////////////////////
        // Ownership Management Services //
        ///////////////////////////////////

        // 7.2
        void unconditionalAttributeOwnershipDivestiture (
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
        );

        // 7.3
        void negotiatedAttributeOwnershipDivestiture (
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
        );

        // 7.7
        void attributeOwnershipAcquisition (
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
        );

        // 7.8
        void attributeOwnershipAcquisitionIfAvailable (
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
        );

        // 7.11
        AttributeHandleSet* attributeOwnershipReleaseResponse ( // returned C6
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
        );

        // 7.12
        void cancelNegotiatedAttributeOwnershipDivestiture (
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
        );

        // 7.13
        void cancelAttributeOwnershipAcquisition (
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
        );

        // 7.15
        void queryAttributeOwnership (
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
        );

        // 7.17
        Boolean isAttributeOwnedByFederate ( // returned C3
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
        );

        //////////////////////////////
        // Time Management Services //
        //////////////////////////////

        // 8.2
        void enableTimeRegulation (
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
        );

        // 8.4
        void disableTimeRegulation () throw (
          TimeRegulationWasNotEnabled,
          ConcurrentAccessAttempted,
          FederateNotExecutionMember,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 8.5
        void enableTimeConstrained () throw (
          TimeConstrainedAlreadyEnabled,
          EnableTimeConstrainedPending,
          TimeAdvanceAlreadyInProgress,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 8.7
        void disableTimeConstrained () throw (
          TimeConstrainedWasNotEnabled,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 8.8
        void timeAdvanceRequest (
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
        );

        // 8.9
        void timeAdvanceRequestAvailable (
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
        );

        // 8.10
        void nextEventRequest (
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
        );

        // 8.11
        void nextEventRequestAvailable (
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
        );

        // 8.12
        void flushQueueRequest (
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
        );

        // 8.14
        void enableAsynchronousDelivery() throw (
          AsynchronousDeliveryAlreadyEnabled,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 8.15
        void disableAsynchronousDelivery() throw (
          AsynchronousDeliveryAlreadyDisabled,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 8.16
        void queryLBTS (
          FedTime& theTime  // returned C5
        ) throw (
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 8.17
        void queryFederateTime (
          FedTime& theTime  // returned C5
        ) throw (
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 8.18
        void queryMinNextEventTime (
          FedTime& theTime  // returned C5
        ) throw (
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 8.19
        void modifyLookahead (
          const FedTime& theLookahead  // supplied C4
        ) throw (
          InvalidLookahead,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 8.20
        void queryLookahead (
           FedTime& theTime  // returned C5
        ) throw (
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 8.21
        void retract (
          EventRetractionHandle theHandle  // supplied C1
        ) throw (
          InvalidRetractionHandle,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 8.23
        void changeAttributeOrderType (
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
        );

        // 8.24
        void changeInteractionOrderType (
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
        );

        //////////////////////////////////
        // Data Distribution Management //
        //////////////////////////////////

        // 9.2
        Region *createRegion (    // returned C6
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
        );


        // 9.3
        void notifyAboutRegionModification (
          Region &theRegion   // supplied C4
        ) throw (
          RegionNotKnown,
          InvalidExtents,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 9.4
        void deleteRegion (
          Region *theRegion  // supplied C1
        ) throw (
          RegionNotKnown,
          RegionInUse,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 9.5
        ObjectHandle registerObjectInstanceWithRegion (  // returned C3
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
        );

        ObjectHandle registerObjectInstanceWithRegion (  // returned C3
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
        );

        // 9.6
        void associateRegionForUpdates (
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
        );

        // 9.7
        void unassociateRegionForUpdates (
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
        );

        // 9.8
        void subscribeObjectClassAttributesWithRegion (
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
        );

        // 9.9
        void unsubscribeObjectClassWithRegion (
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
        );

        // 9.10
        void subscribeInteractionClassWithRegion (
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
        );

        // 9.11
        void unsubscribeInteractionClassWithRegion (
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
        );

        // 9.12
        EventRetractionHandle sendInteractionWithRegion (  // returned C3
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
        );

        void sendInteractionWithRegion (
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
        );

        // 9.13
        void requestClassAttributeValueUpdateWithRegion (
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
        );

        //////////////////////////
        // RTI Support Services //
        //////////////////////////

        // 10.2
        ObjectClassHandle getObjectClassHandle (  // returned C3
          const char *theName  // supplied C4
        ) throw (
          NameNotFound,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 10.3
        char *getObjectClassName (     // returned C6
          ObjectClassHandle theHandle  // supplied C1
        ) throw (
          ObjectClassNotDefined,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 10.4
        AttributeHandle getAttributeHandle (  // returned C3
          const char             *theName,    // supplied C4
                ObjectClassHandle whichClass  // supplied C1
        ) throw (
          ObjectClassNotDefined,
          NameNotFound,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 10.5
        char *getAttributeName (  // returned C6
          AttributeHandle   theHandle,  // supplied C1
          ObjectClassHandle whichClass  // supplied C1
        ) throw (
          ObjectClassNotDefined,
          AttributeNotDefined,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 10.6
        InteractionClassHandle getInteractionClassHandle ( // returned C3
          const char *theName      // supplied C4
        ) throw (
          NameNotFound,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 10.7
        char * getInteractionClassName (  // returned C6
          InteractionClassHandle theHandle        // supplied C1
        ) throw (
          InteractionClassNotDefined,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 10.8
        ParameterHandle getParameterHandle (  // returned C3
          const char *theName,                     // supplied C4
                InteractionClassHandle whichClass  // supplied C1
        ) throw (
          InteractionClassNotDefined,
          NameNotFound,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 10.9
        char *getParameterName (     // returned C6
          ParameterHandle        theHandle,  // supplied C1
          InteractionClassHandle whichClass  // supplied C1
        ) throw (
          InteractionClassNotDefined,
          InteractionParameterNotDefined,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 10.10
        ObjectHandle getObjectInstanceHandle (  // returned C3
          const char *theName        // supplied C4
        ) throw (
          ObjectNotKnown,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 10.11
        char *getObjectInstanceName (  // returned C6
          ObjectHandle theHandle   // supplied C1
        ) throw (
          ObjectNotKnown,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 10.12
        SpaceHandle getRoutingSpaceHandle (  // returned C3
          const char *theName      // supplied C4
        ) throw (
          NameNotFound,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 10.13
        char *getRoutingSpaceName (  // returned C6
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
        );

        // 10.14
        DimensionHandle getDimensionHandle (  // returned C3
          const char         *theName,    // supplied C4
                SpaceHandle   whichSpace  // supplied C1
        ) throw (
          SpaceNotDefined,
          NameNotFound,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 10.15
        char *getDimensionName (  // returned C6
          DimensionHandle theHandle,  // supplied C1
          SpaceHandle     whichSpace  // supplied C1
        ) throw (
          SpaceNotDefined,
          DimensionNotDefined,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 10.16
        SpaceHandle getAttributeRoutingSpaceHandle (  // returned C3
          AttributeHandle   theHandle,   // supplied C1
          ObjectClassHandle whichClass   // supplied C1
        ) throw (
          ObjectClassNotDefined,
          AttributeNotDefined,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 10.17
        ObjectClassHandle getObjectClass (  // returned C3
          ObjectHandle theObject     // supplied C1
        ) throw (
          ObjectNotKnown,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 10.18
        SpaceHandle getInteractionRoutingSpaceHandle (  // returned C3
          InteractionClassHandle   theHandle    // supplied C1
        ) throw (
          InteractionClassNotDefined,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 10.19
        TransportationHandle getTransportationHandle (  // returned C3
          const char *theName     // supplied C4
        ) throw (
          NameNotFound,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 10.20
        char *getTransportationName (  // returned C6
          TransportationHandle theHandle  // supplied C1
        ) throw (
          InvalidTransportationHandle,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 10.21
        OrderingHandle getOrderingHandle (  // returned C3
          const char *theName  // supplied C4
        ) throw (
          NameNotFound,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 10.22
        char *getOrderingName (  // returned C6
          OrderingHandle theHandle  // supplied C1
        ) throw (
          InvalidOrderingHandle,
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        // 10.23
        void enableClassRelevanceAdvisorySwitch() throw(
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 10.24
        void disableClassRelevanceAdvisorySwitch() throw(
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 10.25
        void enableAttributeRelevanceAdvisorySwitch() throw(
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 10.26
        void disableAttributeRelevanceAdvisorySwitch() throw(
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 10.27
        void enableAttributeScopeAdvisorySwitch() throw(
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 10.28
        void disableAttributeScopeAdvisorySwitch() throw(
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 10.29
        void enableInteractionRelevanceAdvisorySwitch() throw(
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        // 10.30
        void disableInteractionRelevanceAdvisorySwitch() throw(
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          SaveInProgress,
          RestoreInProgress,
          RTIinternalError
        );

        //
        Boolean tick () throw (  // returned C3
          SpecifiedSaveLabelDoesNotExist,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        Boolean tick (  // returned C3
          TickTime minimum, // supplied C1
          TickTime maximum  // supplied C1
        ) throw (
          SpecifiedSaveLabelDoesNotExist,
          ConcurrentAccessAttempted,
          RTIinternalError
        );

        RTIambassador() throw (
          MemoryExhausted,
          RTIinternalError
        );

        RTIambassador(RTIProxy::RTIAmbassadorProxy &inputRTIAmbassadorProxy);
        RTIambassador(RTIProxy::RTIAmbassadorProxy *inputRTIAmbassadorProxy);

        ~RTIambassador() throw (
          RTIinternalError
        );

        RegionToken getRegionToken(
          Region *returnPtr
        ) throw(
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RegionNotKnown,
          RTIinternalError
        );

        Region *getRegion(
          RegionToken regionToken
        ) throw(
          FederateNotExecutionMember,
          ConcurrentAccessAttempted,
          RegionNotKnown,
          RTIinternalError
        );
    };  // class RTIambassador

}; // class RTI

#include "fedtimeTest.hh"

#endif