#ifndef RTI_AMBASSADOR_TEST_1_HH
#define RTI_AMBASSADOR_TEST_1_HH

#include "RTIAmbassadorProxy.hh"

#include <map>
#include <set>

class ClassAndPropertyName;

class RTIAmbassadorTest1: public RTIProxy::RTIAmbassadorProxy {

public:
    typedef std::map<std::string, RTI::InteractionClassHandle> ClassNameHandleMap;
    typedef std::map<RTI::InteractionClassHandle, std::string> ClassHandleNameMap;
    typedef std::map<ClassAndPropertyName, int> ClassAndPropertyNameHandleMap;
    typedef std::set<std::string> StringSet;

private:
    static const ClassNameHandleMap &get_class_name_handle_map_aux();
    static const ClassHandleNameMap &get_class_handle_name_map_aux();

    static int get_new_int_value() {
        static int value = 0;
        return value++;
    }
    static const ClassAndPropertyNameHandleMap &get_interaction_class_and_property_name_handle_map_aux();
    static const ClassAndPropertyNameHandleMap &get_object_class_and_property_name_handle_map_aux();

    static StringSet &get_published_interaction_class_name_set_aux() {
        static StringSet publishedInteractionClassNameSet;
        return publishedInteractionClassNameSet;
    }

    static StringSet &get_subscribed_interaction_class_name_set_aux() {
        static StringSet subscribedInteractionClassNameSet;
        return subscribedInteractionClassNameSet;
    }

public:
    static const ClassNameHandleMap &get_class_name_handle_map() {
        static const ClassNameHandleMap &classNameHandleMap = get_class_name_handle_map_aux();
        return classNameHandleMap;
    }

    static const ClassHandleNameMap &get_class_handle_name_map() {
        static const ClassHandleNameMap &classHandleNameMap = get_class_handle_name_map_aux();
        return classHandleNameMap;
    }

    static const ClassAndPropertyNameHandleMap &get_interaction_class_and_property_name_handle_map() {
        static const ClassAndPropertyNameHandleMap &classAndPropertyNameHandleMap =
          get_interaction_class_and_property_name_handle_map_aux();
        return classAndPropertyNameHandleMap;
    }

    static const ClassAndPropertyNameHandleMap &get_object_class_and_property_name_handle_map() {
        static const ClassAndPropertyNameHandleMap &classAndPropertyNameHandleMap =
          get_object_class_and_property_name_handle_map_aux();
        return classAndPropertyNameHandleMap;
    }

    static const StringSet &get_published_interaction_class_name_set() {
        return get_published_interaction_class_name_set_aux();
    }

    static const StringSet &get_subscribed_interaction_class_name_set() {
        return get_subscribed_interaction_class_name_set_aux();
    }

    static void clearPubSub() {
        get_published_interaction_class_name_set_aux().clear();
        get_subscribed_interaction_class_name_set_aux().clear();
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

    void publishInteractionClass(RTI::InteractionClassHandle theInteraction) throw (
      RTI::InteractionClassNotDefined,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    ) override;

    void subscribeInteractionClass(RTI::InteractionClassHandle theInteraction, RTI::Boolean active = RTI::RTI_TRUE)
    throw (
      RTI::InteractionClassNotDefined,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    ) override;
};

#endif  // RTI_AMBASSADOR_TEST_1_HH
