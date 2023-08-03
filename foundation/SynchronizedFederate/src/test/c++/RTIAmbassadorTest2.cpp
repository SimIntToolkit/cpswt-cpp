#include "RTIAmbassadorTest2.hpp"
#include "InteractionRoot.hpp"
#include "ObjectRoot.hpp"

typedef ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot InteractionRoot;
typedef ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot ObjectRoot;

#if __cplusplus >= 201703L
#define MultiArgThrow17
#define Throw17 noexcept
#define throw(...) __VA_OPT__(MultiArg)##Throw17
#endif

const RTIAmbassadorTest2::ClassNameHandleMap &RTIAmbassadorTest2::get_interaction_class_name_handle_map_aux() {
    static ClassNameHandleMap interactionClassNameHandleMap;

    interactionClassNameHandleMap["InteractionRoot"] = get_unique_no();
    interactionClassNameHandleMap["InteractionRoot.C2WInteractionRoot"] = get_unique_no();
    interactionClassNameHandleMap["InteractionRoot.C2WInteractionRoot.ActionBase"] = get_unique_no();
    interactionClassNameHandleMap["InteractionRoot.C2WInteractionRoot.EmbeddedMessaging"] = get_unique_no();
    interactionClassNameHandleMap["InteractionRoot.C2WInteractionRoot.EmbeddedMessaging.OmnetFederate"] =
      get_unique_no();
    interactionClassNameHandleMap["InteractionRoot.C2WInteractionRoot.EmbeddedMessaging.Receiver"] = get_unique_no();
    interactionClassNameHandleMap["InteractionRoot.C2WInteractionRoot.FederateJoinInteraction"] = get_unique_no();
    interactionClassNameHandleMap["InteractionRoot.C2WInteractionRoot.FederateResignInteraction"] = get_unique_no();
    interactionClassNameHandleMap["InteractionRoot.C2WInteractionRoot.OutcomeBase"] = get_unique_no();
    interactionClassNameHandleMap["InteractionRoot.C2WInteractionRoot.SimLog"] = get_unique_no();
    interactionClassNameHandleMap["InteractionRoot.C2WInteractionRoot.SimLog.HighPrio"] = get_unique_no();
    interactionClassNameHandleMap["InteractionRoot.C2WInteractionRoot.SimLog.LowPrio"] = get_unique_no();
    interactionClassNameHandleMap["InteractionRoot.C2WInteractionRoot.SimLog.MediumPrio"] = get_unique_no();
    interactionClassNameHandleMap["InteractionRoot.C2WInteractionRoot.SimLog.VeryLowPrio"] = get_unique_no();
    interactionClassNameHandleMap["InteractionRoot.C2WInteractionRoot.SimulationControl"] = get_unique_no();
    interactionClassNameHandleMap["InteractionRoot.C2WInteractionRoot.SimulationControl.SimEnd"] = get_unique_no();
    interactionClassNameHandleMap["InteractionRoot.C2WInteractionRoot.SimulationControl.SimPause"] = get_unique_no();
    interactionClassNameHandleMap["InteractionRoot.C2WInteractionRoot.SimulationControl.SimResume"] = get_unique_no();

    return interactionClassNameHandleMap;    
}

const std::map<ClassAndPropertyName, int>
  &RTIAmbassadorTest2::get_interaction_class_and_property_name_handle_map_aux() {
    static std::map<ClassAndPropertyName, int> interactionClassAndPropertyNameHandleMap;

    interactionClassAndPropertyNameHandleMap[
      ClassAndPropertyName("InteractionRoot.C2WInteractionRoot", "actualLogicalGenerationTime")
    ] = get_unique_no();
    
    interactionClassAndPropertyNameHandleMap[
      ClassAndPropertyName("InteractionRoot.C2WInteractionRoot", "federateFilter")
    ] = get_unique_no();
    
    interactionClassAndPropertyNameHandleMap[
      ClassAndPropertyName("InteractionRoot.C2WInteractionRoot", "federateSequence")
    ] = get_unique_no();
    
    interactionClassAndPropertyNameHandleMap[
      ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.SimLog", "Comment")
    ] = get_unique_no();
    
    interactionClassAndPropertyNameHandleMap[
      ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.SimLog", "FedName")
    ] = get_unique_no();
    
    interactionClassAndPropertyNameHandleMap[
      ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.SimLog", "Time")
    ] = get_unique_no();
    
    interactionClassAndPropertyNameHandleMap[
      ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.EmbeddedMessaging", "command")
    ] = get_unique_no();
    
    interactionClassAndPropertyNameHandleMap[
      ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.EmbeddedMessaging", "hlaClassName")
    ] = get_unique_no();
    
    interactionClassAndPropertyNameHandleMap[
      ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.EmbeddedMessaging", "messagingJson")
    ] = get_unique_no();
    
    interactionClassAndPropertyNameHandleMap[
      ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.FederateJoinInteraction", "FederateId")
    ] = get_unique_no();
    
    interactionClassAndPropertyNameHandleMap[
      ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.FederateJoinInteraction", "FederateType")
    ] = get_unique_no();
    
    interactionClassAndPropertyNameHandleMap[
      ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.FederateJoinInteraction", "isLateJoiner")
    ] = get_unique_no();

    interactionClassAndPropertyNameHandleMap[
      ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.SimLog", "Comment")
    ] = get_unique_no();

    interactionClassAndPropertyNameHandleMap[
      ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.SimLog", "FedName")
    ] = get_unique_no();

    interactionClassAndPropertyNameHandleMap[
      ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.SimLog", "Time")
    ] = get_unique_no();

    interactionClassAndPropertyNameHandleMap[
      ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.FederateJoinInteraction", "FederateId")
    ] = get_unique_no();

    interactionClassAndPropertyNameHandleMap[
      ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.FederateJoinInteraction", "FederateType")
    ] = get_unique_no();

    interactionClassAndPropertyNameHandleMap[
      ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.FederateJoinInteraction", "IsLateJoiner")
    ] = get_unique_no();

    interactionClassAndPropertyNameHandleMap[
      ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.FederateResignInteraction", "FederateId")
    ] = get_unique_no();

    interactionClassAndPropertyNameHandleMap[
      ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.FederateResignInteraction", "FederateType")
    ] = get_unique_no();

    interactionClassAndPropertyNameHandleMap[
      ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.FederateResignInteraction", "IsLateJoiner")
    ] = get_unique_no();

    return interactionClassAndPropertyNameHandleMap;
}

const RTIAmbassadorTest2::ClassNameHandleMap &RTIAmbassadorTest2::get_object_class_name_handle_map_aux() {
    static ClassNameHandleMap objectClassNameHandleMap;
 
    objectClassNameHandleMap["ObjectRoot"] = get_unique_no();
    objectClassNameHandleMap["ObjectRoot.FederateObject"] = get_unique_no();
    objectClassNameHandleMap["ObjectRoot.TestObject"] = get_unique_no();
    
    return objectClassNameHandleMap;
}

const ObjectRoot::ClassAndPropertyNameIntegerMap &RTIAmbassadorTest2::get_object_class_and_property_name_handle_map_aux() {
    static ObjectRoot::ClassAndPropertyNameIntegerMap objectClassAndPropertyNameHandleMap;

    objectClassAndPropertyNameHandleMap[ClassAndPropertyName("ObjectRoot.FederateObject", "FederateHandle")] =
      get_unique_no();
    objectClassAndPropertyNameHandleMap[ClassAndPropertyName("ObjectRoot.FederateObject", "FederateHost")] =
      get_unique_no();
    objectClassAndPropertyNameHandleMap[ClassAndPropertyName("ObjectRoot.FederateObject", "FederateType")] =
      get_unique_no();
    objectClassAndPropertyNameHandleMap[ClassAndPropertyName("ObjectRoot.TestObject", "BooleanValue1")] = 
      get_unique_no();
    objectClassAndPropertyNameHandleMap[ClassAndPropertyName("ObjectRoot.TestObject", "BooleanValue2")] =
      get_unique_no();
    objectClassAndPropertyNameHandleMap[ClassAndPropertyName("ObjectRoot.TestObject", "ByteValue")] = get_unique_no();
    objectClassAndPropertyNameHandleMap[ClassAndPropertyName("ObjectRoot.TestObject", "CharValue")] = get_unique_no();
    objectClassAndPropertyNameHandleMap[ClassAndPropertyName("ObjectRoot.TestObject", "DoubleValue")] = get_unique_no();
    objectClassAndPropertyNameHandleMap[ClassAndPropertyName("ObjectRoot.TestObject", "FloatValue")] = get_unique_no();
    objectClassAndPropertyNameHandleMap[ClassAndPropertyName("ObjectRoot.TestObject", "IntValue")] = get_unique_no();
    objectClassAndPropertyNameHandleMap[ClassAndPropertyName("ObjectRoot.TestObject", "LongValue")] = get_unique_no();
    objectClassAndPropertyNameHandleMap[ClassAndPropertyName("ObjectRoot.TestObject", "ShortValue")] = get_unique_no();
    objectClassAndPropertyNameHandleMap[ClassAndPropertyName("ObjectRoot.TestObject", "StringValue")] = get_unique_no();

    return objectClassAndPropertyNameHandleMap;
}

RTI::InteractionClassHandle RTIAmbassadorTest2::getInteractionClassHandle(const char *theName) throw (
  RTI::NameNotFound, RTI::FederateNotExecutionMember, RTI::ConcurrentAccessAttempted, RTI::RTIinternalError
) {
    ClassNameHandleMap::const_iterator chmCit = get_interaction_class_name_handle_map().find(theName);

    return chmCit == get_interaction_class_name_handle_map().end() ?
      std::numeric_limits<RTI::InteractionClassHandle>::max() : chmCit->second;
}

RTI::ObjectClassHandle RTIAmbassadorTest2::getObjectClassHandle(const char *theName) throw (
  RTI::NameNotFound, RTI::FederateNotExecutionMember, RTI::ConcurrentAccessAttempted, RTI::RTIinternalError
) {
    ClassNameHandleMap::const_iterator chmCit = get_object_class_name_handle_map().find(theName);

    return chmCit == get_object_class_name_handle_map().end() ?
      std::numeric_limits<RTI::ObjectClassHandle>::max() : chmCit->second;
}

RTI::ParameterHandle RTIAmbassadorTest2::getParameterHandle(
  const char *theName, RTI::InteractionClassHandle whichClass
) throw (
  RTI::InteractionClassNotDefined,
  RTI::NameNotFound,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    std::string hlaClassName = InteractionRoot::get_hla_class_name(whichClass);
    ClassAndPropertyName classAndPropertyName(hlaClassName, std::string(theName));

    InteractionRoot::ClassAndPropertyNameIntegerMap::const_iterator cimCit =
      get_interaction_class_and_property_name_handle_map().find(classAndPropertyName);

    return cimCit == get_interaction_class_and_property_name_handle_map().end() ?
      std::numeric_limits<RTI::ParameterHandle>::max() : cimCit->second;
}

RTI::AttributeHandle RTIAmbassadorTest2::getAttributeHandle(
  const char *theName, RTI::ObjectClassHandle whichClass
) throw (
  RTI::ObjectClassNotDefined,
  RTI::NameNotFound,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    std::string hlaClassName = ObjectRoot::get_hla_class_name(whichClass);
    ClassAndPropertyName classAndPropertyName(hlaClassName, std::string(theName));

    ObjectRoot::ClassAndPropertyNameIntegerMap::const_iterator cimCit =
      get_object_class_and_property_name_handle_map().find(classAndPropertyName);

    return cimCit == get_object_class_and_property_name_handle_map().end() ?
      std::numeric_limits<RTI::AttributeHandle>::max() : cimCit->second;;
}

RTI::FederateHandle RTIAmbassadorTest2::joinFederationExecution (
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
) {
    _federateAmbassadorPtrList.push_back(federateAmbassadorReference);
    return 0;
}

RTI::ObjectHandle RTIAmbassadorTest2::registerObjectInstance(RTI::ObjectClassHandle theClass) throw (
  RTI::ObjectClassNotDefined,
  RTI::ObjectClassNotPublished,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) {
    RegisteredObjectDataSP registeredObjectDataSP(new RegisteredObjectData(theClass, get_unique_no()));
    get_registered_object_data_sp_list().push_back(registeredObjectDataSP);
    return registeredObjectDataSP->getObjectHandle();
}

void RTIAmbassadorTest2::sendInteraction(
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
) {
    SentInteractionDataSP sentInteractionDataSP( new SentInteractionData(theInteraction, theParameters, RTIfedTime()));
    get_sent_interaction_data_sp_list().push_back(sentInteractionDataSP);
}

RTI::EventRetractionHandle RTIAmbassadorTest2::sendInteraction (
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
) {
    SentInteractionDataSP sentInteractionDataSP(new SentInteractionData(theInteraction, theParameters, theTime));
    get_sent_interaction_data_sp_list().push_back(sentInteractionDataSP);

    return RTI::EventRetractionHandle();
}

RTI::Boolean RTIAmbassadorTest2::tick() throw (
  RTI::SpecifiedSaveLabelDoesNotExist,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    if (_timeConstrainedRequestOutstanding) {
        _timeConstrainedRequestOutstanding = false;
        for (RTI::FederateAmbassadorPtr federateAmbassadorPtr : _federateAmbassadorPtrList) {
            federateAmbassadorPtr->timeConstrainedEnabled(defaultRTIfedTime);
        }
    }
    if (_timeRegulationRequestOutstanding) {
        _timeRegulationRequestOutstanding = false;
        for (RTI::FederateAmbassadorPtr federateAmbassadorPtr : _federateAmbassadorPtrList) {
            federateAmbassadorPtr->timeRegulationEnabled(defaultRTIfedTime);
        }
    }
    return RTI::RTI_TRUE;
}

RTI::Boolean RTIAmbassadorTest2::tick(RTI::TickTime minimum, RTI::TickTime maximum) throw (
  RTI::SpecifiedSaveLabelDoesNotExist,
  RTI::ConcurrentAccessAttempted,
  RTI::RTIinternalError
) {
    return tick();
}

RTI::EventRetractionHandle RTIAmbassadorTest2::updateAttributeValues (
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
) {
    UpdatedObjectDataSP updatedObjectDataSP(new UpdatedObjectData(theObject, theAttributes, theTime));
    get_updated_object_data_sp_list().push_back(updatedObjectDataSP);

    return RTI::EventRetractionHandle(); // DUMMY EventRetractionHandle
}

#if __cplusplus >= 201703L
#undef MultiArgThrow17
#undef Throw17
#undef throw
#endif
