#include "RTIAmbassadorTest1.hh"

#include "InteractionRoot.hpp"
#include "ObjectRoot.hpp"

#include <limits>

using InteractionRoot = ::org::cpswt::hla::InteractionRoot;
using ObjectRoot = ::org::cpswt::hla::ObjectRoot;

const RTIAmbassadorTest1::ClassNameToHandleMap &RTIAmbassadorTest1::get_class_name_handle_map_aux() {
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


const RTIAmbassadorTest1::ClassAndPropertyNameHandleMap
  &RTIAmbassadorTest1::get_class_and_property_name_parameter_handle_map_aux() {

    static ClassAndPropertyNameHandleMap interactionClassAndPropertyNameHandleMap;

    interactionClassAndPropertyNameHandleMap[
            ClassAndPropertyName("InteractionRoot.C2WInteractionRoot", "actualLogicalGenerationTime")
    ] = get_new_int_value();
    interactionClassAndPropertyNameHandleMap[
            ClassAndPropertyName("InteractionRoot.C2WInteractionRoot", "federateFilter")
    ] = get_new_int_value();
    interactionClassAndPropertyNameHandleMap[
            ClassAndPropertyName("InteractionRoot.C2WInteractionRoot", "originFed")
    ] = get_new_int_value();
    interactionClassAndPropertyNameHandleMap[
            ClassAndPropertyName("InteractionRoot.C2WInteractionRoot", "sourceFed")
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

    return interactionClassAndPropertyNameHandleMap;
}

const RTIAmbassadorTest1::ClassAndPropertyNameHandleMap
  &RTIAmbassadorTest1::get_class_and_property_name_attribute_handle_map_aux() {

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
    ClassNameToHandleMap::const_iterator chmCit = get_class_name_handle_map().find(theName);
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
    return get_class_and_property_name_parameter_handle_map().find(classAndPropertyName)->second;
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
    return get_class_and_property_name_attribute_handle_map().find(classAndPropertyName)->second;
}
