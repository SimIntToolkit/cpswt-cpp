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
            "    },\n" +
            "    \"objects\": {\n" +
            "        \"ObjectRoot\": {},\n" +
            "        \"ObjectRoot.TestBase\": {\n" +
            "             \"field1\": {\n" +
            "                 \"Delivery\": \"reliable\",\n" +
            "                 \"Hidden\": false,\n" +
            "                 \"Order\": \"timestamp\",\n" +
            "                 \"ParameterType\": \"String\"\n" +
            "             },\n" +
            "             \"field2\": {\n" +
            "                 \"Delivery\": \"reliable\",\n" +
            "                 \"Hidden\": false,\n" +
            "                 \"Order\": \"timestamp\",\n" +
            "                 \"ParameterType\": \"int\"\n" +
            "             }\n" +
            "        },\n" +
            "        \"ObjectRoot.TestBase.TestDerived\": {\n" +
            "             \"field3\": {\n" +
            "                 \"Delivery\": \"reliable\",\n" +
            "                 \"Hidden\": false,\n" +
            "                 \"Order\": \"timestamp\",\n" +
            "                 \"ParameterType\": \"boolean\"\n" +
            "             },\n" +
            "             \"field4\": {\n" +
            "                 \"Delivery\": \"reliable\",\n" +
            "                 \"Hidden\": false,\n" +
            "                 \"Order\": \"timestamp\",\n" +
            "                 \"ParameterType\": \"long\"\n" +
            "             },\n" +
            "             \"field5\": {\n" +
            "                 \"Delivery\": \"reliable\",\n" +
            "                 \"Hidden\": false,\n" +
            "                 \"Order\": \"timestamp\",\n" +
            "                 \"ParameterType\": \"double\"\n" +
            "             },\n" +
            "             \"field6\": {\n" +
            "                 \"Delivery\": \"reliable\",\n" +
            "                 \"Hidden\": false,\n" +
            "                 \"Order\": \"timestamp\",\n" +
            "                 \"ParameterType\": \"byte\"\n" +
            "             },\n" +
            "             \"field7\": {\n" +
            "                 \"Delivery\": \"reliable\",\n" +
            "                 \"Hidden\": false,\n" +
            "                 \"Order\": \"timestamp\",\n" +
            "                 \"ParameterType\": \"char\"\n" +
            "             }\n" +
            "        },\n" +
            "        \"ObjectRoot.OtherClass\": {\n" +
            "             \"field1\": {\n" +
            "                 \"Delivery\": \"reliable\",\n" +
            "                 \"Hidden\": false,\n" +
            "                 \"Order\": \"timestamp\",\n" +
            "                 \"ParameterType\": \"boolean\"\n" +
            "             },\n" +
            "             \"field2\": {\n" +
            "                 \"Delivery\": \"reliable\",\n" +
            "                 \"Hidden\": false,\n" +
            "                 \"Order\": \"timestamp\",\n" +
            "                 \"ParameterType\": \"long\"\n" +
            "             },\n" +
            "             \"field3\": {\n" +
            "                 \"Delivery\": \"reliable\",\n" +
            "                 \"Hidden\": false,\n" +
            "                 \"Order\": \"timestamp\",\n" +
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
            "    ],\n" +
            "    \"objects\": [\n" +
            "    ]\n" +
            "}\n";

    std::istringstream federationJsonInputStream(federationJson);
    std::istringstream dynamicMessagingTypesInputStream(dynamicMessageTypes);
    InteractionRoot::loadDynamicClassFederationData(federationJsonInputStream, dynamicMessagingTypesInputStream);

    federationJsonInputStream.seekg(0);
    dynamicMessagingTypesInputStream.seekg(0);
    ObjectRoot::loadDynamicClassFederationData(federationJsonInputStream, dynamicMessagingTypesInputStream);
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
