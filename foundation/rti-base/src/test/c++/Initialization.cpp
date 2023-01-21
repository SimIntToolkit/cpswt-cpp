#include "Initialization.hpp"
#include "InteractionRoot.hpp"
#include "ObjectRoot.hpp"


using InteractionRoot = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot;
using ObjectRoot = ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot;


void Initialization::interaction_root_dynamic_init() {
    const std::string federationJson =
            std::string("{\n") +
            "    \"interactions\": {\n" +
            "        \"InteractionRoot\": {},\n" +
            "        \"InteractionRoot.TestBase\": {\n" +
            "             \"field1\": {\n" +
            "                 \"Hidden\": false,\n" +
            "                 \"ParameterType\": \"String\"\n" +
            "             },\n" +
            "             \"field2\": {\n" +
            "                 \"Hidden\": false,\n" +
            "                 \"ParameterType\": \"int\"\n" +
            "             }\n" +
            "        },\n" +
            "        \"InteractionRoot.TestBase.TestDerived\": {\n" +
            "             \"field3\": {\n" +
            "                 \"Hidden\": false,\n" +
            "                 \"ParameterType\": \"boolean\"\n" +
            "             },\n" +
            "             \"field4\": {\n" +
            "                 \"Hidden\": false,\n" +
            "                 \"ParameterType\": \"long\"\n" +
            "             },\n" +
            "             \"field5\": {\n" +
            "                 \"Hidden\": false,\n" +
            "                 \"ParameterType\": \"double\"\n" +
            "             }\n" +
            "        },\n" +
            "        \"InteractionRoot.OtherClass\": {\n" +
            "             \"field1\": {\n" +
            "                 \"Hidden\": false,\n" +
            "                 \"ParameterType\": \"boolean\"\n" +
            "             },\n" +
            "             \"field2\": {\n" +
            "                 \"Hidden\": false,\n" +
            "                 \"ParameterType\": \"long\"\n" +
            "             },\n" +
            "             \"field3\": {\n" +
            "                 \"Hidden\": false,\n" +
            "                 \"ParameterType\": \"double\"\n" +
            "             }\n" +
            "        }\n" +
            "    }\n" +
            "}\n";

    const std::string dynamicMessageTypes =
            std::string("{\n") +
            "    \"interactions\": [\n" +
            "        \"InteractionRoot.TestBase\",\n" +
            "        \"InteractionRoot.TestBase.TestDerived\"\n" +
            "    ]\n" +
            "}\n";

    std::istringstream federationJsonInputStream(federationJson);
    std::istringstream dynamicMessagingTypesInputStream(dynamicMessageTypes);
    InteractionRoot::loadDynamicClassFederationData(federationJsonInputStream, dynamicMessagingTypesInputStream);
}

void Initialization::init_1() {
    if (get_is_initialized()) {
        return;
    }
    get_is_initialized() = true;

    std::cout << "INITIALIZING ... " << std::flush;
    interaction_root_dynamic_init();
    InteractionRoot::init(RTIAmbassadorTest1::get_rti_ambassador_1_ptr());
    ObjectRoot::init(RTIAmbassadorTest1::get_rti_ambassador_1_ptr());
    std::cout << "DONE" << std::endl;
}
