#ifndef RTI_AMBASSADOR_TEST_1_HH
#define RTI_AMBASSADOR_TEST_1_HH

#include "RTIAmbassadorProxy.hh"

#include <map>

class ClassAndPropertyName;

class RTIAmbassadorTest1: public RTIProxy::RTIAmbassadorProxy {

public:
    typedef std::map<std::string, RTI::InteractionClassHandle> ClassNameToHandleMap;
    typedef std::map<ClassAndPropertyName, int> ClassAndPropertyNameHandleMap;

private:
    static const ClassNameToHandleMap &get_class_name_handle_map_aux();
    static int get_new_int_value() {
        static int value = 0;
        return value++;
    }
    static const ClassAndPropertyNameHandleMap &get_class_and_property_name_parameter_handle_map_aux();
    static const ClassAndPropertyNameHandleMap &get_class_and_property_name_attribute_handle_map_aux();

public:
    static const ClassNameToHandleMap &get_class_name_handle_map() {
        static const ClassNameToHandleMap &classNameToHandleMap = get_class_name_handle_map_aux();
        return classNameToHandleMap;
    }

    static const ClassAndPropertyNameHandleMap &get_class_and_property_name_parameter_handle_map() {
        static const ClassAndPropertyNameHandleMap &classAndPropertyNameHandleMap =
          get_class_and_property_name_parameter_handle_map_aux();
        return classAndPropertyNameHandleMap;
    }

    static const ClassAndPropertyNameHandleMap &get_class_and_property_name_attribute_handle_map() {
        static const ClassAndPropertyNameHandleMap &classAndPropertyNameHandleMap =
          get_class_and_property_name_attribute_handle_map_aux();
        return classAndPropertyNameHandleMap;
    }

    RTI::InteractionClassHandle getInteractionClassHandle (const char *theName) throw (
      RTI::NameNotFound, RTI::FederateNotExecutionMember, RTI::ConcurrentAccessAttempted, RTI::RTIinternalError
    ) override;

    RTI::ParameterHandle getParameterHandle (const char *theName, RTI::InteractionClassHandle whichClass) throw (
      RTI::InteractionClassNotDefined,
      RTI::NameNotFound,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    ) override;

    RTI::AttributeHandle getAttributeHandle (const char *theName, RTI::ObjectClassHandle whichClass) throw (
      RTI::ObjectClassNotDefined,
      RTI::NameNotFound,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    ) override;

};

#endif  // RTI_AMBASSADOR_TEST_1_HH
