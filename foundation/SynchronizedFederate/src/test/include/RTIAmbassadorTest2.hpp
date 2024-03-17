#ifndef RTI_AMBASSADOR_TEST_2_HH
#define RTI_AMBASSADOR_TEST_2_HH

#include "RTIAmbassadorProxy.hpp"
#include "PropertyHandleValuePairSetForTesting.hpp"
#include "ClassAndPropertyName.hpp"
#include "FederateConfig.h"
#include "SynchronizedFederate.hpp"

#include <list>
#include <map>
#include <set>
#include <iostream>
#include <boost/shared_ptr.hpp>

#if __cplusplus >= 201703L
#define MultiArgThrow17
#define Throw17 noexcept
#define throw(...) __VA_OPT__(MultiArg)##Throw17
#endif

class RTIAmbassadorTest2: public RTIProxy::RTIAmbassadorProxy {

public:
    typedef RTIProxy::RTIAmbassadorProxy Super;
    typedef RTI::ParameterHandleValuePairSet ParameterHandleValuePairSet;
    typedef RTI::AttributeHandleValuePairSet AttributeHandleValuePairSet;
    typedef std::map<std::string, RTI::InteractionClassHandle> ClassNameHandleMap;

private:
    static int get_unique_no() {
        static int unique_no = 0;
        return unique_no++;
    };

    static const ClassNameHandleMap &get_interaction_class_name_handle_map_aux();

    static const std::map<ClassAndPropertyName, int> &get_interaction_class_and_property_name_handle_map_aux();

    static const ClassNameHandleMap &get_object_class_name_handle_map_aux();

    static const std::map<ClassAndPropertyName, int> &get_object_class_and_property_name_handle_map_aux();

    bool _timeConstrainedRequestOutstanding;
    bool _timeRegulationRequestOutstanding;

public:
    RTIAmbassadorTest2(NullFederateAmbassador &nullFederateAmbassador) :
      Super(nullFederateAmbassador),
      _timeConstrainedRequestOutstanding(false),
      _timeRegulationRequestOutstanding(false),
      _currentTime(0) {}

    // STATIC BECAUSE IT IS USED GLOBALLY AND NEVER CHANGES
    static const ClassNameHandleMap &get_interaction_class_name_handle_map() {
        static const ClassNameHandleMap &interactionClassNameHandleMap =
          get_interaction_class_name_handle_map_aux();
        return interactionClassNameHandleMap;
    }

    // STATIC BECAUSE IT IS USED GLOBALLY AND NEVER CHANGES
    static const std::map<ClassAndPropertyName, int> &get_interaction_class_and_property_name_handle_map() {
        static const std::map<ClassAndPropertyName, int> &interactionClassAndPropertyNameHandleMap =
          get_interaction_class_and_property_name_handle_map_aux();
        return interactionClassAndPropertyNameHandleMap;
    }

    class SentInteractionData {
    private:
        const int _interactionClassHandle;
        const PropertyHandleValuePairSetForTesting _propertyHandleValuePairSetForTesting;
        const RTIfedTime _rtiFedTime;

    public:
        SentInteractionData(
          int interactionClassHandle,
          const RTI::ParameterHandleValuePairSet &parameterHandleValuePairSet,
          const RTIfedTime &rtiFedTime
        ) :
          _interactionClassHandle(interactionClassHandle),
          _propertyHandleValuePairSetForTesting(parameterHandleValuePairSet),
          _rtiFedTime(rtiFedTime) {}

        SentInteractionData(
          int interactionClassHandle,
          const RTI::ParameterHandleValuePairSet &parameterHandleValuePairSet
        ) :
          _interactionClassHandle(interactionClassHandle),
          _propertyHandleValuePairSetForTesting(parameterHandleValuePairSet) {}

        int getInteractionClassHandle() {
            return _interactionClassHandle;
        }

        const RTI::ParameterHandleValuePairSet &getParameterHandleValuePairSet() {
            return _propertyHandleValuePairSetForTesting;
        }

        const RTIfedTime &getRTIfedTime() {
            return _rtiFedTime;
        }
    };

    typedef boost::shared_ptr<SentInteractionData> SentInteractionDataSP;
    typedef std::list<SentInteractionDataSP> SentInteractionDataSPList;

private:
    SentInteractionDataSPList _sentInteractionDataSPList;

public:
    SentInteractionDataSPList &getSentInteractionDataSPList() {
        return _sentInteractionDataSPList;
    }

    // STATIC BECAUSE IT IS USED GLOBALLY AND NEVER CHANGES
    static const ClassNameHandleMap &get_object_class_name_handle_map() {
        static const ClassNameHandleMap &objectClassNameHandleMap =
          get_object_class_name_handle_map_aux();
        return objectClassNameHandleMap;
    }

    // STATIC BECAUSE IT IS USED GLOBALLY AND NEVER CHANGES
    static const std::map<ClassAndPropertyName, int> &get_object_class_and_property_name_handle_map() {
        static const std::map<ClassAndPropertyName, int> &objectClassAndPropertyNameHandleMap =
          get_object_class_and_property_name_handle_map_aux();
        return objectClassAndPropertyNameHandleMap;
    }

    class RegisteredObjectData {
    private:
        const int _objectClassHandle;
        const int _objectHandle;

    public:
        RegisteredObjectData(int objectClassHandle, int objectHandle) :
          _objectClassHandle(objectClassHandle),
          _objectHandle(objectHandle) {}

        int getObjectClassHandle() {
            return _objectClassHandle;
        }

        int getObjectHandle() {
            return _objectHandle;
        }
    };

    typedef boost::shared_ptr<RegisteredObjectData> RegisteredObjectDataSP;
    typedef std::list<RegisteredObjectDataSP> RegisteredObjectDataSPList;

private:
    RegisteredObjectDataSPList _registeredObjectDataSPList;

public:
    RegisteredObjectDataSPList &getRegisteredObjectDataSPList() {
        return _registeredObjectDataSPList;
    }

    class UpdatedObjectData {

    private:
        const int _objectHandle;
        const PropertyHandleValuePairSetForTesting _propertyHandleValuePairSetForTesting;
        const RTIfedTime _rtiFedTime;

    public:
        UpdatedObjectData(
          int objectHandle,
          const RTI::AttributeHandleValuePairSet &attributeHandleValuePairSet,
          const RTIfedTime &rtiFedTime
        ) :
          _objectHandle(objectHandle),
          _propertyHandleValuePairSetForTesting(attributeHandleValuePairSet),
          _rtiFedTime(rtiFedTime) {}

        int getObjectHandle() {
            return _objectHandle;
        }

        const AttributeHandleValuePairSet &getAttributeHandleValuePairSet() {
            return _propertyHandleValuePairSetForTesting;
        }

        const RTIfedTime &getRTIfedTime() {
            return _rtiFedTime;
        }
    };

    typedef boost::shared_ptr<UpdatedObjectData> UpdatedObjectDataSP;
    typedef std::list<UpdatedObjectDataSP> UpdatedObjectDataSPList;

private:
    UpdatedObjectDataSPList _updatedObjectDataSPList;

public:

    UpdatedObjectDataSPList &getUpdatedObjectDataSPList() {
        return _updatedObjectDataSPList;
    }

    void clear() {
        getSentInteractionDataSPList().clear();
        getRegisteredObjectDataSPList().clear();
        getUpdatedObjectDataSPList().clear();
    }

private:
    RTIfedTime defaultRTIfedTime;

    double _currentTime;

public:
    void resetCurrentTime() {
        _currentTime = 0;
    }

    void enableTimeConstrained() throw (
      RTI::TimeConstrainedAlreadyEnabled,
      RTI::EnableTimeConstrainedPending,
      RTI::TimeAdvanceAlreadyInProgress,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    ) override {
        _timeConstrainedRequestOutstanding = true;
    }

    void enableTimeRegulation(const RTI::FedTime &theFederateTime, const RTI::FedTime &theLookahead) throw (
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
    ) override {
        _timeRegulationRequestOutstanding = true;
    }

    RTI::InteractionClassHandle getInteractionClassHandle(const char *theName) throw (
      RTI::NameNotFound,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    ) override;

    RTI::ObjectClassHandle getObjectClassHandle(const char *theName) throw (
      RTI::NameNotFound,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    ) override;

    RTI::ParameterHandle getParameterHandle(
      const char *theName, RTI::InteractionClassHandle whichClass
    ) throw (
      RTI::InteractionClassNotDefined,
      RTI::NameNotFound,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    ) override;

    RTI::AttributeHandle getAttributeHandle(
      const char *theName, RTI::ObjectClassHandle whichClass
    ) throw (
      RTI::ObjectClassNotDefined,
      RTI::NameNotFound,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    ) override;

    RTI::FederateHandle joinFederationExecution (
      const char *yourName, const char *executionName, RTI::FederateAmbassadorPtr federateAmbassadorReference
    ) throw (
      RTI::FederateAlreadyExecutionMember,
      RTI::FederationExecutionDoesNotExist,
      RTI::CouldNotOpenFED,
      RTI::ErrorReadingFED,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    ) override;

    void queryFederateTime (
      RTI::FedTime& theTime  // returned C5
    ) throw (
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    ) override;

    RTI::ObjectHandle registerObjectInstance (RTI::ObjectClassHandle theClass) throw (
      RTI::ObjectClassNotDefined,
      RTI::ObjectClassNotPublished,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    ) override;

    void sendInteraction(
      RTI::InteractionClassHandle theInteraction,
      const RTI::ParameterHandleValuePairSet& theParameters,
      const char *theTag
    ) throw (
      RTI::InteractionClassNotDefined,
      RTI::InteractionClassNotPublished,
      RTI::InteractionParameterNotDefined,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    ) override;

    RTI::EventRetractionHandle sendInteraction(
      RTI::InteractionClassHandle theInteraction,
      const RTI::ParameterHandleValuePairSet& theParameters,
      const RTI::FedTime& theTime,
      const char *theTag
    ) throw (
      RTI::InteractionClassNotDefined,
      RTI::InteractionClassNotPublished,
      RTI::InteractionParameterNotDefined,
      RTI::InvalidFederationTime,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    ) override;

    RTI::Boolean tick() throw (
      RTI::SpecifiedSaveLabelDoesNotExist,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    ) override;

    RTI::Boolean tick(RTI::TickTime minimum, RTI::TickTime maximum) throw (
      RTI::SpecifiedSaveLabelDoesNotExist,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    ) override;

    void timeAdvanceRequest (
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
    ) override;

    RTI::EventRetractionHandle updateAttributeValues (
      RTI::ObjectHandle theObject,
      const RTI::AttributeHandleValuePairSet& theAttributes,
      const RTI::FedTime& theTime,
      const char *theTag
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
    ) override;
};

#if __cplusplus >= 201703L
#undef MultiArgThrow17
#undef Throw17
#undef throw
#endif

#endif  // RTI_AMBASSADOR_TEST_2_HH
