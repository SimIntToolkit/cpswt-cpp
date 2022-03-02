#include "InteractionTests.hpp"

#include "InteractionRoot.hpp"
#include "InteractionRoot_p/C2WInteractionRoot.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/SimLog.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/SimLog_p/HighPrio.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/SimulationControl.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/SimulationControl_p/SimEnd.hpp"
#include "ObjectRoot.hpp"
#include "ObjectRoot_p/FederateObject.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/expressions.hpp>
#include <boost/regex.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/algorithm/string.hpp>
#include <list>
#include <sstream>
#include <iostream>


using InteractionRoot = ::org::cpswt::hla::InteractionRoot;
using ObjectRoot = ::org::cpswt::hla::ObjectRoot;
using C2WInteractionRoot = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot;
using SimLog = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::SimLog;
using HighPrio = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::SimLog_p::HighPrio;
using SimulationControl = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::SimulationControl;
using SimEnd = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::SimulationControl_p::SimEnd;
using FederateObject = ::org::cpswt::hla::ObjectRoot_p::FederateObject;

typedef std::set<std::string> StringSet;
typedef std::list<std::string> StringList;

namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;

template<typename COLLECTION>
void printCollection(std::ostream &os, const COLLECTION &collection) {
    os << "[";

    bool first = true;
    for(typename COLLECTION::const_iterator stsCit = collection.begin() ; stsCit != collection.end() ; ++stsCit) {
        if (first) first = false;
        else       os << ", ";
        os << *stsCit;
    }

    os << "]";
}

std::ostream &operator<<(std::ostream &os, const StringSet &stringSet) {
    os << "StringSet";
    printCollection(os, stringSet);
    return os;
}

std::ostream &operator<<(std::ostream &os, const ClassAndPropertyNameList &classAndPropertyNameList) {
    os << "ClassAndPropertyNameList";
    printCollection(os, classAndPropertyNameList);
    return os;
}

RTI::RTIambassador *InteractionTests::get_rti_ambassador_1_ptr() {
    static RTIAmbassadorTest1 rtiAmbassadorTest1;
    static RTI::RTIambassador rtiAmbassador(&rtiAmbassadorTest1);
    return &rtiAmbassador;
}

void InteractionTests::init_1() {
    if (get_is_initialized()) {
        return;
    }
    get_is_initialized() = true;

    std::cout << "INITIALIZING ... " << std::flush;
    InteractionRoot::init(get_rti_ambassador_1_ptr());
    ObjectRoot::init(get_rti_ambassador_1_ptr());
    std::cout << "DONE" << std::endl;
}

void InteractionTests::messagingNamesTest() {

    std::set<std::string> expectedInteractionClassNameSet;
    expectedInteractionClassNameSet.insert("InteractionRoot");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.ActionBase");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.FederateJoinInteraction");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.FederateResignInteraction");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.OutcomeBase");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.SimLog");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.SimLog.HighPrio");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.SimLog.HighPrio");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.SimLog.LowPrio");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.SimLog.MediumPrio");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.SimLog.VeryLowPrio");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.SimulationControl");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.SimulationControl.SimEnd");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.SimulationControl.SimPause");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.SimulationControl.SimResume");

    const std::set<std::string> &actualInteractionClassNameSet = InteractionRoot::get_interaction_hla_class_name_set();
    CPPUNIT_ASSERT_EQUAL(expectedInteractionClassNameSet, actualInteractionClassNameSet);

    std::set<std::string> expectedObjectClassNameSet;
    expectedObjectClassNameSet.insert("ObjectRoot");
    expectedObjectClassNameSet.insert("ObjectRoot.FederateObject");

    const std::set<std::string> &actualObjectClassNameSet = ObjectRoot::get_object_hla_class_name_set();
    CPPUNIT_ASSERT(expectedObjectClassNameSet == actualObjectClassNameSet);
}

void InteractionTests::classHandleTest() {
    CPPUNIT_ASSERT_EQUAL(
            RTIAmbassadorTest1::get_class_name_handle_map().find("InteractionRoot")->second,
            static_cast<RTI::InteractionClassHandle>(InteractionRoot::get_class_handle())
    );
    CPPUNIT_ASSERT_EQUAL(
            RTIAmbassadorTest1::get_class_name_handle_map().find("InteractionRoot.C2WInteractionRoot")->second,
            static_cast<RTI::InteractionClassHandle>(C2WInteractionRoot::get_class_handle())
    );
    CPPUNIT_ASSERT_EQUAL(
            RTIAmbassadorTest1::get_class_name_handle_map().find("InteractionRoot.C2WInteractionRoot.SimLog")->second,
            static_cast<RTI::InteractionClassHandle>(SimLog::get_class_handle())
    );
    CPPUNIT_ASSERT_EQUAL(
            RTIAmbassadorTest1::get_class_name_handle_map().find(
              "InteractionRoot.C2WInteractionRoot.SimLog.HighPrio"
            )->second,
            static_cast<RTI::InteractionClassHandle>(HighPrio::get_class_handle())
    );
    CPPUNIT_ASSERT_EQUAL(
            RTIAmbassadorTest1::get_class_name_handle_map().find(
              "InteractionRoot.C2WInteractionRoot.SimulationControl"
            )->second,
            static_cast<RTI::InteractionClassHandle>(SimulationControl::get_class_handle())
    );
    CPPUNIT_ASSERT_EQUAL(
            RTIAmbassadorTest1::get_class_name_handle_map().find(
              "InteractionRoot.C2WInteractionRoot.SimulationControl.SimEnd"
            )->second,
            static_cast<RTI::InteractionClassHandle>(SimEnd::get_class_handle())
    );

    CPPUNIT_ASSERT_EQUAL(
            RTIAmbassadorTest1::get_class_name_handle_map().find("InteractionRoot")->second,
            static_cast<RTI::InteractionClassHandle>(
              InteractionRoot::get_class_handle("InteractionRoot")
            )
    );
    CPPUNIT_ASSERT_EQUAL(
            RTIAmbassadorTest1::get_class_name_handle_map().find("InteractionRoot.C2WInteractionRoot")->second,
            static_cast<RTI::InteractionClassHandle>(
              InteractionRoot::get_class_handle("InteractionRoot.C2WInteractionRoot")
            )
    );
    CPPUNIT_ASSERT_EQUAL(
            RTIAmbassadorTest1::get_class_name_handle_map().find("InteractionRoot.C2WInteractionRoot.SimLog")->second,
            static_cast<RTI::InteractionClassHandle>(
              InteractionRoot::get_class_handle("InteractionRoot.C2WInteractionRoot.SimLog")
            )
    );
    CPPUNIT_ASSERT_EQUAL(
            RTIAmbassadorTest1::get_class_name_handle_map().find(
              "InteractionRoot.C2WInteractionRoot.SimLog.HighPrio"
            )->second,
            static_cast<RTI::InteractionClassHandle>(
              InteractionRoot::get_class_handle("InteractionRoot.C2WInteractionRoot.SimLog.HighPrio")
            )
    );
    CPPUNIT_ASSERT_EQUAL(
            RTIAmbassadorTest1::get_class_name_handle_map().find(
              "InteractionRoot.C2WInteractionRoot.SimulationControl"
            )->second,
            static_cast<RTI::InteractionClassHandle>(
              InteractionRoot::get_class_handle("InteractionRoot.C2WInteractionRoot.SimulationControl")
            )
    );
    CPPUNIT_ASSERT_EQUAL(
            RTIAmbassadorTest1::get_class_name_handle_map().find(
              "InteractionRoot.C2WInteractionRoot.SimulationControl.SimEnd"
            )->second,
            static_cast<RTI::InteractionClassHandle>(
              InteractionRoot::get_class_handle("InteractionRoot.C2WInteractionRoot.SimulationControl.SimEnd")
            )
    );
}

void InteractionTests::parameterNamesTest() {

    // TEST InteractionRoot get_parameter_names()
    ClassAndPropertyNameList expectedInteractionRootParameterList;

    CPPUNIT_ASSERT_EQUAL(expectedInteractionRootParameterList, InteractionRoot::get_parameter_names());
    CPPUNIT_ASSERT_EQUAL(
            expectedInteractionRootParameterList,
            InteractionRoot::get_parameter_names("InteractionRoot")
    );

    // TEST InteractionRoot get_all_parameter_names()
    ClassAndPropertyNameList expectedInteractionRootAllParameterList(expectedInteractionRootParameterList);

    CPPUNIT_ASSERT_EQUAL(expectedInteractionRootAllParameterList, InteractionRoot::get_all_parameter_names());
    CPPUNIT_ASSERT_EQUAL(
            expectedInteractionRootAllParameterList,
            InteractionRoot::get_all_parameter_names("InteractionRoot")
    );


    // TEST InteractionRoot.C2WInteractionRoot get_parameter_names()
    ClassAndPropertyNameList expectedC2WInteractionRootParameterList;
    expectedC2WInteractionRootParameterList.emplace_back(
            C2WInteractionRoot::get_hla_class_name(), "actualLogicalGenerationTime"
    );
    expectedC2WInteractionRootParameterList.emplace_back(
            C2WInteractionRoot::get_hla_class_name(), "federateFilter"
    );
    expectedC2WInteractionRootParameterList.emplace_back(
            C2WInteractionRoot::get_hla_class_name(), "originFed"
    );
    expectedC2WInteractionRootParameterList.emplace_back(
            C2WInteractionRoot::get_hla_class_name(), "sourceFed"
    );
    expectedC2WInteractionRootParameterList.sort();

    CPPUNIT_ASSERT_EQUAL(expectedC2WInteractionRootParameterList, C2WInteractionRoot::get_parameter_names());
    CPPUNIT_ASSERT_EQUAL(
            expectedC2WInteractionRootParameterList,
            InteractionRoot::get_parameter_names("InteractionRoot.C2WInteractionRoot")
    );


    // TEST InteractionRoot.C2WInteractionRoot get_all_parameter_names()
    ClassAndPropertyNameList expectedC2WInteractionRootAllParameterList(expectedInteractionRootAllParameterList);
    expectedC2WInteractionRootAllParameterList.insert(
            expectedC2WInteractionRootAllParameterList.end(),
            expectedC2WInteractionRootParameterList.begin(),
            expectedC2WInteractionRootParameterList.end()
    );
    expectedC2WInteractionRootAllParameterList.sort();

    CPPUNIT_ASSERT_EQUAL(expectedC2WInteractionRootAllParameterList, C2WInteractionRoot::get_all_parameter_names());
    CPPUNIT_ASSERT_EQUAL(
            expectedC2WInteractionRootAllParameterList,
            InteractionRoot::get_all_parameter_names("InteractionRoot.C2WInteractionRoot")
    );


    // TEST InteractionRoot.C2WInteractionRoot.SimLog get_parameter_names()
    ClassAndPropertyNameList expectedSimLogParameterList;
    expectedSimLogParameterList.emplace_back(
            SimLog::get_hla_class_name(), "Comment"
    );
    expectedSimLogParameterList.emplace_back(
            SimLog::get_hla_class_name(), "FedName"
    );
    expectedSimLogParameterList.emplace_back(
            SimLog::get_hla_class_name(), "Time"
    );
    expectedSimLogParameterList.sort();

    CPPUNIT_ASSERT_EQUAL(expectedSimLogParameterList, SimLog::get_parameter_names());
    CPPUNIT_ASSERT_EQUAL(
            expectedSimLogParameterList,
            InteractionRoot::get_parameter_names("InteractionRoot.C2WInteractionRoot.SimLog")
    );


    // TEST InteractionRoot.C2WInteractionRoot.SimLog get_all_parameter_names()
    ClassAndPropertyNameList expectedSimLogAllParameterList(expectedC2WInteractionRootAllParameterList);
    expectedSimLogAllParameterList.insert(
            expectedSimLogAllParameterList.end(),
            expectedSimLogParameterList.begin(),
            expectedSimLogParameterList.end()
    );
    expectedSimLogAllParameterList.sort();

    CPPUNIT_ASSERT_EQUAL(expectedSimLogAllParameterList, SimLog::get_all_parameter_names());
    CPPUNIT_ASSERT_EQUAL(
            expectedSimLogAllParameterList,
            InteractionRoot::get_all_parameter_names("InteractionRoot.C2WInteractionRoot.SimLog")
    );


    // TEST InteractionRoot.C2WInteractionRoot.SimLog get_parameter_names()
    ClassAndPropertyNameList expectedHighPrioParameterList;

    CPPUNIT_ASSERT_EQUAL(expectedHighPrioParameterList, HighPrio::get_parameter_names());
    CPPUNIT_ASSERT_EQUAL(
            expectedHighPrioParameterList,
            InteractionRoot::get_parameter_names("InteractionRoot.C2WInteractionRoot.SimLog.HighPrio")
    );


    // TEST InteractionRoot.C2WInteractionRoot.SimLog get_all_parameter_names()
    ClassAndPropertyNameList expectedHighPrioAllParameterList(expectedSimLogAllParameterList);
    expectedHighPrioAllParameterList.insert(
            expectedHighPrioAllParameterList.end(),
            expectedHighPrioParameterList.begin(),
            expectedHighPrioParameterList.end()
    );
    expectedHighPrioAllParameterList.sort();

    CPPUNIT_ASSERT_EQUAL(expectedHighPrioAllParameterList, HighPrio::get_all_parameter_names());
    CPPUNIT_ASSERT_EQUAL(
            expectedHighPrioAllParameterList,
            InteractionRoot::get_all_parameter_names("InteractionRoot.C2WInteractionRoot.SimLog.HighPrio")
    );
}

void InteractionTests::propertyHandleTest() {
    int expectedValue = RTIAmbassadorTest1::get_class_and_property_name_parameter_handle_map().find(
            ClassAndPropertyName("InteractionRoot.C2WInteractionRoot", "originFed")
    )->second;

    CPPUNIT_ASSERT_EQUAL(expectedValue, HighPrio::get_parameter_handle("originFed"));
    CPPUNIT_ASSERT_EQUAL(expectedValue, SimLog::get_parameter_handle("originFed"));
    CPPUNIT_ASSERT_EQUAL(expectedValue, C2WInteractionRoot::get_parameter_handle("originFed"));

    expectedValue = RTIAmbassadorTest1::get_class_and_property_name_parameter_handle_map().find(
            ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.SimLog", "FedName")
    )->second;

    CPPUNIT_ASSERT_EQUAL(expectedValue, HighPrio::get_parameter_handle("FedName"));
    CPPUNIT_ASSERT_EQUAL(expectedValue, SimLog::get_parameter_handle("FedName"));

    expectedValue = RTIAmbassadorTest1::get_class_and_property_name_parameter_handle_map().find(
            ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.SimLog", "FedName")
    )->second;

    CPPUNIT_ASSERT_EQUAL(expectedValue, HighPrio::get_parameter_handle("FedName"));
    CPPUNIT_ASSERT_EQUAL(expectedValue, SimLog::get_parameter_handle("FedName"));

    expectedValue = RTIAmbassadorTest1::get_class_and_property_name_attribute_handle_map().find(
            ClassAndPropertyName("ObjectRoot.FederateObject", "FederateHost")
    )->second;

    CPPUNIT_ASSERT_EQUAL(expectedValue, FederateObject::get_attribute_handle("FederateHost"));
}

BOOST_LOG_ATTRIBUTE_KEYWORD(messagingClassName, "MessagingClassName", std::string);
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", logging::trivial::severity_level);
BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime);

void InteractionTests::basicLogTest() {

    boost::shared_ptr< text_sink > stringSink = boost::make_shared< text_sink >();
    boost::shared_ptr< std::ostringstream > ostringstreamSP = boost::make_shared< std::ostringstream >();

    stringSink->locked_backend()->add_stream( ostringstreamSP );

    stringSink->set_formatter(
        expr::stream << messagingClassName << " <" << timestamp << "> [" << severity << "]: " << expr::smessage
    );
    logging::core::get()->add_sink(stringSink);

    RTIAmbassadorTest1 rtiAmbassadorTest1;
    RTI::RTIambassador rtiAmbassador(&rtiAmbassadorTest1);
    HighPrio::publish_interaction(&rtiAmbassador);
    HighPrio::unpublish_interaction(&rtiAmbassador);

    std::string timeRegexString = R"(\d{4}-\w{3}-\d{2} \d{2}:\d{2}:\d{2}.\d*)";
    std::string highPrioHlaClassNameRegexString = std::string("\\Q") + HighPrio::get_hla_class_name() + "\\E";
    std::string publishingRegexString = std::string("(?:un)?publish_interaction: \"") +
      highPrioHlaClassNameRegexString + "\" interaction (?:un)?published";

    std::string logLineRegexString = InteractionRoot::get_hla_class_name() + " <" + timeRegexString + R"(> \[debug\]: )"
      + publishingRegexString;

    boost::regex logLineRegex{ logLineRegexString };

    std::string loggerOutput = ostringstreamSP->str();

    StringList logLineList;
    boost::algorithm::split(logLineList, loggerOutput, boost::is_any_of("\n"));
    if (logLineList.size() > 0 && logLineList.back() == "") {
        logLineList.pop_back();
    }

    for(StringList::const_iterator stlCit = logLineList.begin() ; stlCit != logLineList.end() ; ++stlCit) {
        CPPUNIT_ASSERT(boost::regex_match(*stlCit, logLineRegex));
    }
}

void InteractionTests::dynamicMessagingTest() {
    InteractionRoot dynamicSimLogInteraction(SimLog::get_hla_class_name());
    InteractionRoot *dynamicSimLogInteractionPtr = &dynamicSimLogInteraction;

    SimLog *simLogPtr1 = dynamic_cast<SimLog *>(dynamicSimLogInteractionPtr);
    CPPUNIT_ASSERT(simLogPtr1 == nullptr);
    CPPUNIT_ASSERT_EQUAL(SimLog::get_hla_class_name(), dynamicSimLogInteraction.getInstanceHlaClassName());

    std::string string1("string1");
    double doubleValue1(1.2);

    dynamicSimLogInteraction.setParameter("InteractionRoot.C2WInteractionRoot", "originFed", string1);
    dynamicSimLogInteraction.setParameter("Time", doubleValue1);

    CPPUNIT_ASSERT_EQUAL(string1, static_cast<std::string>(dynamicSimLogInteraction.getParameter("originFed")));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(
      doubleValue1, static_cast<double>(dynamicSimLogInteraction.getParameter("Time")), 0.01
    );

    std::string string2("string2");
    double doubleValue2(3.4);

    dynamicSimLogInteraction.setParameter("originFed", string2);
    dynamicSimLogInteraction.setParameter("Time", doubleValue2);

    CPPUNIT_ASSERT_EQUAL(string2, static_cast<std::string>(dynamicSimLogInteraction.getParameter("originFed")));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(
      doubleValue2, static_cast<double>(dynamicSimLogInteraction.getParameter("Time")), 0.01
    );

    InteractionRoot::SP staticSimLogInteractionSP1 = InteractionRoot::create_interaction(SimLog::get_hla_class_name());
    InteractionRoot *staticSimLogInteraction1Ptr = staticSimLogInteractionSP1.get();

    SimLog *simLogPtr2 = dynamic_cast<SimLog *>(staticSimLogInteraction1Ptr);

    CPPUNIT_ASSERT(simLogPtr2 != nullptr);
    CPPUNIT_ASSERT_EQUAL(SimLog::get_hla_class_name(), staticSimLogInteractionSP1->getInstanceHlaClassName());

    std::string string3("string3");
    double doubleValue3(5.6);

    SimLog &simLogInteraction = *simLogPtr2;
    simLogInteraction.setParameter("originFed", string3);
    simLogInteraction.setParameter("Time", doubleValue3);

    CPPUNIT_ASSERT_EQUAL(string3, static_cast<std::string>(simLogInteraction.getParameter("originFed")));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(doubleValue3, static_cast<double>(simLogInteraction.getParameter("Time")), 0.01);

    CPPUNIT_ASSERT_EQUAL(string3, simLogInteraction.get_originFed());
    CPPUNIT_ASSERT_DOUBLES_EQUAL(doubleValue3, simLogInteraction.get_Time(), 0.01);

    std::string string4("string4");
    double doubleValue4(17.3);

    simLogInteraction.set_originFed(string4);
    simLogInteraction.set_Time(doubleValue4);

    CPPUNIT_ASSERT_EQUAL(string4, simLogInteraction.getParameter("originFed").asString());
    CPPUNIT_ASSERT_DOUBLES_EQUAL(doubleValue4, simLogInteraction.getParameter("Time").asDouble(), 0.01);

    CPPUNIT_ASSERT_EQUAL(string4, simLogInteraction.get_originFed());
    CPPUNIT_ASSERT_DOUBLES_EQUAL(doubleValue4, simLogInteraction.get_Time(), 0.01);
}

CPPUNIT_TEST_SUITE_REGISTRATION( InteractionTests );
