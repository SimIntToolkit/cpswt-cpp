#include "RTIAmbassadorTest1.hh"

#include <limits>

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

// 10.6
RTI::InteractionClassHandle RTIAmbassadorTest1::getInteractionClassHandle (const char *theName) throw (
  RTI::NameNotFound, RTI::FederateNotExecutionMember, RTI::ConcurrentAccessAttempted, RTI::RTIinternalError
) {
    std::cout << "Name: " << theName << std::endl;
    ClassNameToHandleMap::const_iterator chmCit = get_class_name_handle_map().find(theName);
    return chmCit == get_class_name_handle_map().end() ?
      std::numeric_limits<RTI::InteractionClassHandle>::max() : chmCit->second;
}
