#ifndef RTI_AMBASSADOR_TEST_1_HH
#define RTI_AMBASSADOR_TEST_1_HH

#include "RTIAmbassadorProxy.hh"

#include <map>



class RTIAmbassadorTest1: public RTIProxy::RTIAmbassadorProxy {

public:
    typedef std::map<std::string, RTI::InteractionClassHandle> ClassNameToHandleMap;

private:
    static const ClassNameToHandleMap &get_class_name_handle_map_aux();

public:
    static const ClassNameToHandleMap &get_class_name_handle_map() {
        static const ClassNameToHandleMap &classNameToHandleMap = get_class_name_handle_map_aux();
        return classNameToHandleMap;
    }

    RTI::InteractionClassHandle getInteractionClassHandle (const char *theName) throw (
      RTI::NameNotFound, RTI::FederateNotExecutionMember, RTI::ConcurrentAccessAttempted, RTI::RTIinternalError
    ) override;

};

#endif  // RTI_AMBASSADOR_TEST_1_HH