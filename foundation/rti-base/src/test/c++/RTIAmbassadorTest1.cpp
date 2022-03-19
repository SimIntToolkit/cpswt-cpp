#include "RTIAmbassadorTest1.hh"

#include "InteractionRoot.hpp"
#include "ObjectRoot.hpp"

#include <limits>
#include <iostream>

using InteractionRoot = ::org::cpswt::hla::InteractionRoot;
using ObjectRoot = ::org::cpswt::hla::ObjectRoot;

const RTIAmbassadorTest1::ClassNameHandleMap &RTIAmbassadorTest1::get_class_name_handle_map_aux() {
    static ClassNameHandleMap classNameHandleMap;

    int handleValue = 0;

    classNameHandleMap["InteractionRoot"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameHandleMap["InteractionRoot.C2WInteractionRoot"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameHandleMap["InteractionRoot.C2WInteractionRoot.ActionBase"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameHandleMap["InteractionRoot.C2WInteractionRoot.FederateJoinInteraction"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameHandleMap["InteractionRoot.C2WInteractionRoot.FederateResignInteraction"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameHandleMap["InteractionRoot.C2WInteractionRoot.OutcomeBase"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameHandleMap["InteractionRoot.C2WInteractionRoot.SimLog"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameHandleMap["InteractionRoot.C2WInteractionRoot.SimLog.HighPrio"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameHandleMap["InteractionRoot.C2WInteractionRoot.SimLog.LowPrio"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameHandleMap["InteractionRoot.C2WInteractionRoot.SimLog.MediumPrio"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameHandleMap["InteractionRoot.C2WInteractionRoot.SimLog.VeryLowPrio"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameHandleMap["InteractionRoot.C2WInteractionRoot.SimulationControl"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameHandleMap["InteractionRoot.C2WInteractionRoot.SimulationControl.SimEnd"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameHandleMap["InteractionRoot.C2WInteractionRoot.SimulationControl.SimPause"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameHandleMap["InteractionRoot.C2WInteractionRoot.SimulationControl.SimResume"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameHandleMap["InteractionRoot.TestBase"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    classNameHandleMap["InteractionRoot.TestBase.DerivedBase"] =
      static_cast<RTI::InteractionClassHandle>(handleValue++);

    return classNameHandleMap;
}

const RTIAmbassadorTest1::ClassHandleNameMap &RTIAmbassadorTest1::get_class_handle_name_map_aux() {
    const ClassNameHandleMap &classNameHandleMap = get_class_name_handle_map();

    static ClassHandleNameMap classHandleNameMap;
    for(
      ClassNameHandleMap::const_iterator chmCit = classNameHandleMap.begin() ;
      chmCit != classNameHandleMap.end() ;
      ++chmCit
    ) {
        classHandleNameMap[chmCit->second] = chmCit->first;
    }

    return classHandleNameMap;
}

const RTIAmbassadorTest1::ClassAndPropertyNameHandleMap
  &RTIAmbassadorTest1::get_interaction_class_and_property_name_handle_map_aux() {

    static ClassAndPropertyNameHandleMap interactionClassAndPropertyNameHandleMap;

    interactionClassAndPropertyNameHandleMap[
            ClassAndPropertyName("InteractionRoot.C2WInteractionRoot", "actualLogicalGenerationTime")
    ] = get_new_int_value();
    interactionClassAndPropertyNameHandleMap[
            ClassAndPropertyName("InteractionRoot.C2WInteractionRoot", "federateFilter")
    ] = get_new_int_value();
    interactionClassAndPropertyNameHandleMap[
            ClassAndPropertyName("InteractionRoot.C2WInteractionRoot", "federateSequence")
    ] = get_new_int_value();
    interactionClassAndPropertyNameHandleMap[
            ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.SimLog", "Comment")
    ] = get_new_int_value();
    interactionClassAndPropertyNameHandleMap[
            ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.SimLog", "FedName")
    ] = get_new_int_value();
    interactionClassAndPropertyNameHandleMap[
            ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.SimLog", "Time")
    ] = get_new_int_value();
    interactionClassAndPropertyNameHandleMap[
            ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.FederateJoinInteraction", "FederateId")
    ] = get_new_int_value();
    interactionClassAndPropertyNameHandleMap[
            ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.FederateJoinInteraction", "FederateType")
    ] = get_new_int_value();
    interactionClassAndPropertyNameHandleMap[
            ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.FederateJoinInteraction", "IsLateJoiner")
    ] = get_new_int_value();
    interactionClassAndPropertyNameHandleMap[
            ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.FederateResignInteraction", "FederateId")
    ] = get_new_int_value();
    interactionClassAndPropertyNameHandleMap[
            ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.FederateResignInteraction", "FederateType")
    ] = get_new_int_value();
    interactionClassAndPropertyNameHandleMap[
            ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.FederateResignInteraction", "IsLateJoiner")
    ] = get_new_int_value();

    interactionClassAndPropertyNameHandleMap[
            ClassAndPropertyName("InteractionRoot.TestBase", "field1")
    ] =get_new_int_value();
    interactionClassAndPropertyNameHandleMap[
            ClassAndPropertyName("InteractionRoot.TestBase", "field2")
    ] = get_new_int_value();
    interactionClassAndPropertyNameHandleMap[
            ClassAndPropertyName("InteractionRoot.TestBase.TestDerived", "field3")
    ] = get_new_int_value();
    interactionClassAndPropertyNameHandleMap[
            ClassAndPropertyName("InteractionRoot.TestBase.TestDerived", "field4")
    ] = get_new_int_value();
    interactionClassAndPropertyNameHandleMap[
            ClassAndPropertyName("InteractionRoot.TestBase.TestDerived", "field5")
    ] = get_new_int_value();

    return interactionClassAndPropertyNameHandleMap;
}

const RTIAmbassadorTest1::ClassAndPropertyNameHandleMap
  &RTIAmbassadorTest1::get_object_class_and_property_name_handle_map_aux() {

    static ClassAndPropertyNameHandleMap objectClassAndPropertyNameHandleMap;

    objectClassAndPropertyNameHandleMap[
            ClassAndPropertyName("ObjectRoot.FederateObject", "FederateHandle")
    ] = get_new_int_value();
    objectClassAndPropertyNameHandleMap[
            ClassAndPropertyName("ObjectRoot.FederateObject", "FederateHost")
    ] = get_new_int_value();
    objectClassAndPropertyNameHandleMap[
            ClassAndPropertyName("ObjectRoot.FederateObject", "FederateType")
    ] = get_new_int_value();

    return objectClassAndPropertyNameHandleMap;
}

// 10.6
RTI::InteractionClassHandle RTIAmbassadorTest1::getInteractionClassHandle(const char *theName) throw (
  RTI::NameNotFound, RTI::FederateNotExecutionMember, RTI::ConcurrentAccessAttempted, RTI::RTIinternalError
) {
    ClassNameHandleMap::const_iterator chmCit = get_class_name_handle_map().find(theName);

    return chmCit == get_class_name_handle_map().end() ?
      std::numeric_limits<RTI::InteractionClassHandle>::max() : chmCit->second;
}

RTI::ParameterHandle RTIAmbassadorTest1::getParameterHandle(
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
    return get_interaction_class_and_property_name_handle_map().find(classAndPropertyName)->second;
}

RTI::AttributeHandle RTIAmbassadorTest1::getAttributeHandle(
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
    return get_object_class_and_property_name_handle_map().find(classAndPropertyName)->second;
}

void RTIAmbassadorTest1::publishInteractionClass(RTI::InteractionClassHandle theInteraction) throw (
  RTI::InteractionClassNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) {
    const std::string &interactionName = get_class_handle_name_map().find(theInteraction)->second;
    get_published_interaction_class_name_set_aux().insert(interactionName);
}

void RTIAmbassadorTest1::subscribeInteractionClass(RTI::InteractionClassHandle theInteraction, RTI::Boolean active)
throw (
  RTI::InteractionClassNotDefined,
  RTI::FederateNotExecutionMember,
  RTI::ConcurrentAccessAttempted,
  RTI::SaveInProgress,
  RTI::RestoreInProgress,
  RTI::RTIinternalError
) {
    const std::string &interactionName = get_class_handle_name_map().find(theInteraction)->second;
    get_subscribed_interaction_class_name_set_aux().insert(interactionName);
}
