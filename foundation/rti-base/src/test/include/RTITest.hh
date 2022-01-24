#ifndef RTI_TEST_HH
#define RTI_TEST_HH

#include <map>

#define RTI_EXPORT
#define RTI_EXPORT_FEDTIME


#define CPSWT_TEST

#define RTI_STD std

class RTI {
public:
#include "baseTypes.hh"
#include "RTItypes.hh"

    class RTIambassador {
    public:
#include "RTIambServices.hh"
    };

};
#include "fedtimeTest.hh"

typedef std::map<std::string, RTI::InteractionClassHandle> ClassNameToHandleMap;
const ClassNameToHandleMap &get_class_name_handle_map();

#endif