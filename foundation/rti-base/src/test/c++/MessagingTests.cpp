/*
 * Certain portions of this software are Copyright (C) 2006-present
 * Vanderbilt University, Institute for Software Integrated Systems.
 *
 * Certain portions of this software are contributed as a public service by
 * The National Institute of Standards and Technology (NIST) and are not
 * subject to U.S. Copyright.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above Vanderbilt University copyright notice, NIST contribution
 * notice and this permission and disclaimer notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE. THE AUTHORS OR COPYRIGHT HOLDERS SHALL NOT HAVE
 * ANY OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS,
 * OR MODIFICATIONS.
 */

#include "MessagingTests.hpp"

#include "Initialization.hpp"

#include "InteractionRoot.hpp"
#include "InteractionRoot_p/C2WInteractionRoot.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/SimLog.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/SimLog_p/HighPrio.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/SimulationControl.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/SimulationControl_p/SimEnd.hpp"
#include "ObjectRoot.hpp"
#include "ObjectRoot_p/FederateObject.hpp"
#include "ObjectRoot_p/BaseObjectClass.hpp"
#include "ObjectRoot_p/BaseObjectClass_p/DerivedObjectClass.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/expressions.hpp>
#include <boost/regex.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/algorithm/string.hpp>
#include <list>
#include <sstream>
#include <iostream>

#include <jsoncpp/json/json.h>

using InteractionRoot = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot;
using ObjectRoot = ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot;
using C2WInteractionRoot = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot;
using SimLog = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::SimLog;
using HighPrio = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::SimLog_p::HighPrio;
using SimulationControl = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::SimulationControl;
using SimEnd = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::SimulationControl_p::SimEnd;
using FederateObject = ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::FederateObject;
using DerivedObjectClass = ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::BaseObjectClass_p::DerivedObjectClass;

typedef std::set<std::string> StringSet;
typedef std::list<std::string> StringList;

namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;

MessagingTests::MessagingTests() : CppUnit::TestCase() {
    Initialization::init_1();
    nullSink = boost::make_shared< text_sink >();
    nullSink->set_filter(&null_filter);
    logging::core::get()->add_sink(nullSink);
}

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

void MessagingTests::setUp() {
    RTIAmbassadorTest1::clearPubSub();
}

void MessagingTests::interactionClassNamesTest() {

    std::set<std::string> expectedInteractionClassNameSet;
    expectedInteractionClassNameSet.insert("InteractionRoot");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.ActionBase");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.EmbeddedMessaging");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.FederateJoinInteraction");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.FederateResignInteraction");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.OutcomeBase");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.SimLog");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.SimLog.HighPrio");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.SimLog.LowPrio");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.SimLog.MediumPrio");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.SimLog.VeryLowPrio");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.SimulationControl");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.SimulationControl.SimEnd");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.SimulationControl.SimPause");
    expectedInteractionClassNameSet.insert("InteractionRoot.C2WInteractionRoot.SimulationControl.SimResume");
    expectedInteractionClassNameSet.insert("InteractionRoot.TestBase");
    expectedInteractionClassNameSet.insert("InteractionRoot.TestBase.TestDerived");

    const std::set<std::string> &actualInteractionClassNameSet = InteractionRoot::get_interaction_hla_class_name_set();
    CPPUNIT_ASSERT_EQUAL(expectedInteractionClassNameSet, actualInteractionClassNameSet);
}

void MessagingTests::objectClassNamesTest() {
    std::set<std::string> expectedObjectClassNameSet;
    expectedObjectClassNameSet.insert("ObjectRoot");
    expectedObjectClassNameSet.insert("ObjectRoot.FederateObject");
    expectedObjectClassNameSet.insert("ObjectRoot.BaseObjectClass");
    expectedObjectClassNameSet.insert("ObjectRoot.BaseObjectClass.DerivedObjectClass");

    const std::set<std::string> &actualObjectClassNameSet = ObjectRoot::get_object_hla_class_name_set();
    CPPUNIT_ASSERT(expectedObjectClassNameSet == actualObjectClassNameSet);
}

void MessagingTests::interactionClassHandleTest() {

    InteractionRoot::SP interactionRootSP;

    // InteractionRoot
    RTI::InteractionClassHandle interactionRootClassHandle =
      RTIAmbassadorTest1::get_class_name_handle_map().find("InteractionRoot")->second;
    CPPUNIT_ASSERT_EQUAL(
            interactionRootClassHandle, static_cast<RTI::InteractionClassHandle>(InteractionRoot::get_class_handle())
    );
    interactionRootSP = InteractionRoot::create_interaction();
    CPPUNIT_ASSERT_EQUAL(
            interactionRootClassHandle, static_cast<RTI::InteractionClassHandle>(interactionRootSP->getClassHandle())
    );
    CPPUNIT_ASSERT_EQUAL(
            interactionRootClassHandle,
            static_cast<RTI::InteractionClassHandle>(InteractionRoot::get_class_handle("InteractionRoot"))
    );

    // C2WInteractionRoot
    RTI::InteractionClassHandle c2wInteractionRootClassHandle =
            RTIAmbassadorTest1::get_class_name_handle_map().find("InteractionRoot.C2WInteractionRoot")->second;
    CPPUNIT_ASSERT_EQUAL(
            c2wInteractionRootClassHandle,
            static_cast<RTI::InteractionClassHandle>(C2WInteractionRoot::get_class_handle())
    );
    interactionRootSP = C2WInteractionRoot::create_interaction();
    CPPUNIT_ASSERT_EQUAL(
            c2wInteractionRootClassHandle, static_cast<RTI::InteractionClassHandle>(interactionRootSP->getClassHandle())
    );
    CPPUNIT_ASSERT_EQUAL(
            c2wInteractionRootClassHandle,
            static_cast<RTI::InteractionClassHandle>(
              InteractionRoot::get_class_handle("InteractionRoot.C2WInteractionRoot")
            )
    );

    // SimLog
    RTI::InteractionClassHandle simLogClassHandle =
            RTIAmbassadorTest1::get_class_name_handle_map().find("InteractionRoot.C2WInteractionRoot.SimLog")->second;
    CPPUNIT_ASSERT_EQUAL(
            simLogClassHandle,
            static_cast<RTI::InteractionClassHandle>(SimLog::get_class_handle())
    );
    interactionRootSP = SimLog::create_interaction();
    CPPUNIT_ASSERT_EQUAL(
            simLogClassHandle, static_cast<RTI::InteractionClassHandle>(interactionRootSP->getClassHandle())
    );
    CPPUNIT_ASSERT_EQUAL(
            simLogClassHandle,
            static_cast<RTI::InteractionClassHandle>(
              InteractionRoot::get_class_handle("InteractionRoot.C2WInteractionRoot.SimLog")
            )
    );

    // HighPrio
    RTI::InteractionClassHandle highPrioClassHandle =
            RTIAmbassadorTest1::get_class_name_handle_map().find(
              "InteractionRoot.C2WInteractionRoot.SimLog.HighPrio"
            )->second;
    CPPUNIT_ASSERT_EQUAL(
            highPrioClassHandle, static_cast<RTI::InteractionClassHandle>(HighPrio::get_class_handle())
    );
    interactionRootSP = HighPrio::create_interaction();
    CPPUNIT_ASSERT_EQUAL(
            highPrioClassHandle, static_cast<RTI::InteractionClassHandle>(interactionRootSP->getClassHandle())
    );
    CPPUNIT_ASSERT_EQUAL(
            highPrioClassHandle, 
            static_cast<RTI::InteractionClassHandle>(
              InteractionRoot::get_class_handle("InteractionRoot.C2WInteractionRoot.SimLog.HighPrio")
            )
    );

    // SimulationControl
    RTI::InteractionClassHandle simulationControlClassHandle =
            RTIAmbassadorTest1::get_class_name_handle_map().find(
              "InteractionRoot.C2WInteractionRoot.SimulationControl"
            )->second;
    CPPUNIT_ASSERT_EQUAL(
            simulationControlClassHandle,
            static_cast<RTI::InteractionClassHandle>(SimulationControl::get_class_handle())
    );
    interactionRootSP = SimulationControl::create_interaction();
    CPPUNIT_ASSERT_EQUAL(
            simulationControlClassHandle, static_cast<RTI::InteractionClassHandle>(interactionRootSP->getClassHandle())
    );
    CPPUNIT_ASSERT_EQUAL(
            simulationControlClassHandle,
            static_cast<RTI::InteractionClassHandle>(
              InteractionRoot::get_class_handle("InteractionRoot.C2WInteractionRoot.SimulationControl")
            )
    );

    // SimEnd
    RTI::InteractionClassHandle simEndClassHandle = RTIAmbassadorTest1::get_class_name_handle_map().find(
      "InteractionRoot.C2WInteractionRoot.SimulationControl.SimEnd"
    )->second;
    CPPUNIT_ASSERT_EQUAL(
            simEndClassHandle, static_cast<RTI::InteractionClassHandle>(SimEnd::get_class_handle())
    );
    interactionRootSP = SimEnd::create_interaction();
    CPPUNIT_ASSERT_EQUAL(
            simEndClassHandle, static_cast<RTI::InteractionClassHandle>(interactionRootSP->getClassHandle())
    );
    CPPUNIT_ASSERT_EQUAL(
            simEndClassHandle,
            static_cast<RTI::InteractionClassHandle>(
              InteractionRoot::get_class_handle("InteractionRoot.C2WInteractionRoot.SimulationControl.SimEnd")
            )
    );
}
void MessagingTests::objectClassHandleTest() {

    ObjectRoot::SP objectRootSP;

    // ObjectRoot
    RTI::ObjectClassHandle objectRootClassHandle =
      RTIAmbassadorTest1::get_class_name_handle_map().find("ObjectRoot")->second;
    CPPUNIT_ASSERT_EQUAL(
            objectRootClassHandle, static_cast<RTI::ObjectClassHandle>(ObjectRoot::get_class_handle())
    );
    objectRootSP = ObjectRoot::create_object();
    CPPUNIT_ASSERT_EQUAL(
            objectRootClassHandle, static_cast<RTI::ObjectClassHandle>(objectRootSP->getClassHandle())
    );
    CPPUNIT_ASSERT_EQUAL(
            objectRootClassHandle,
            static_cast<RTI::ObjectClassHandle>(ObjectRoot::get_class_handle("ObjectRoot"))
    );

    // FederateObject
    RTI::ObjectClassHandle federateObjectClassHandle =
            RTIAmbassadorTest1::get_class_name_handle_map().find("ObjectRoot.FederateObject")->second;
    CPPUNIT_ASSERT_EQUAL(
            federateObjectClassHandle,
            static_cast<RTI::ObjectClassHandle>(FederateObject::get_class_handle())
    );
    objectRootSP = FederateObject::create_object();
    CPPUNIT_ASSERT_EQUAL(
            federateObjectClassHandle, static_cast<RTI::ObjectClassHandle>(objectRootSP->getClassHandle())
    );
    CPPUNIT_ASSERT_EQUAL(
            federateObjectClassHandle,
            static_cast<RTI::ObjectClassHandle>(
              ObjectRoot::get_class_handle("ObjectRoot.FederateObject")
            )
    );
}

void MessagingTests::interactionParameterNamesTest() {

    InteractionRoot::SP interactionRootSP;

    // TEST InteractionRoot get_parameter_names()
    ClassAndPropertyNameList expectedInteractionRootParameterList;

    interactionRootSP = InteractionRoot::create();

    CPPUNIT_ASSERT_EQUAL(expectedInteractionRootParameterList, InteractionRoot::get_parameter_names());
    CPPUNIT_ASSERT_EQUAL(expectedInteractionRootParameterList, interactionRootSP->getParameterNames());
    CPPUNIT_ASSERT_EQUAL(
            expectedInteractionRootParameterList,
            InteractionRoot::get_parameter_names("InteractionRoot")
    );

    // TEST InteractionRoot get_all_parameter_names()
    ClassAndPropertyNameList expectedInteractionRootAllParameterList(expectedInteractionRootParameterList);

    CPPUNIT_ASSERT_EQUAL(expectedInteractionRootAllParameterList, InteractionRoot::get_all_parameter_names());
    CPPUNIT_ASSERT_EQUAL(expectedInteractionRootAllParameterList, interactionRootSP->getAllParameterNames());
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
            C2WInteractionRoot::get_hla_class_name(), "federateSequence"
    );
    expectedC2WInteractionRootParameterList.sort();

    interactionRootSP = C2WInteractionRoot::create();
    
    CPPUNIT_ASSERT_EQUAL(expectedC2WInteractionRootParameterList, C2WInteractionRoot::get_parameter_names());
    CPPUNIT_ASSERT_EQUAL(expectedC2WInteractionRootParameterList, interactionRootSP->getParameterNames());
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
    CPPUNIT_ASSERT_EQUAL(expectedC2WInteractionRootAllParameterList, interactionRootSP->getAllParameterNames());
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

    interactionRootSP = SimLog::create();

    CPPUNIT_ASSERT_EQUAL(expectedSimLogParameterList, SimLog::get_parameter_names());
    CPPUNIT_ASSERT_EQUAL(expectedSimLogParameterList, interactionRootSP->getParameterNames());
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
    CPPUNIT_ASSERT_EQUAL(expectedSimLogAllParameterList, interactionRootSP->getAllParameterNames());
    CPPUNIT_ASSERT_EQUAL(
            expectedSimLogAllParameterList,
            InteractionRoot::get_all_parameter_names("InteractionRoot.C2WInteractionRoot.SimLog")
    );


    // TEST InteractionRoot.C2WInteractionRoot.SimLog get_parameter_names()
    ClassAndPropertyNameList expectedHighPrioParameterList;

    interactionRootSP = HighPrio::create();

    CPPUNIT_ASSERT_EQUAL(expectedHighPrioParameterList, HighPrio::get_parameter_names());
    CPPUNIT_ASSERT_EQUAL(expectedHighPrioParameterList, interactionRootSP->getParameterNames());
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
    CPPUNIT_ASSERT_EQUAL(expectedHighPrioAllParameterList, interactionRootSP->getAllParameterNames());
    CPPUNIT_ASSERT_EQUAL(
            expectedHighPrioAllParameterList,
            InteractionRoot::get_all_parameter_names("InteractionRoot.C2WInteractionRoot.SimLog.HighPrio")
    );

    CPPUNIT_ASSERT_EQUAL(6, HighPrio::get_num_parameters());
    CPPUNIT_ASSERT_EQUAL(6, interactionRootSP->getNumParameters());
    CPPUNIT_ASSERT_EQUAL(6, InteractionRoot::get_num_parameters(
            "InteractionRoot.C2WInteractionRoot.SimLog.HighPrio"
    ));
}

void MessagingTests::objectAttributeNamesTest() {

    ObjectRoot::SP objectRootSP;

    // TEST ObjectRoot get_attribute_names()
    ClassAndPropertyNameList expectedObjectRootAttributeList;

    objectRootSP = ObjectRoot::create();

    CPPUNIT_ASSERT_EQUAL(expectedObjectRootAttributeList, ObjectRoot::get_attribute_names());
    CPPUNIT_ASSERT_EQUAL(expectedObjectRootAttributeList, objectRootSP->getAttributeNames());
    CPPUNIT_ASSERT_EQUAL(
            expectedObjectRootAttributeList,
            ObjectRoot::get_attribute_names("ObjectRoot")
    );

    // TEST ObjectRoot get_all_attribute_names()
    ClassAndPropertyNameList expectedObjectRootAllAttributeList(expectedObjectRootAttributeList);

    CPPUNIT_ASSERT_EQUAL(expectedObjectRootAllAttributeList, ObjectRoot::get_all_attribute_names());
    CPPUNIT_ASSERT_EQUAL(expectedObjectRootAllAttributeList, objectRootSP->getAllAttributeNames());
    CPPUNIT_ASSERT_EQUAL(
            expectedObjectRootAllAttributeList,
            ObjectRoot::get_all_attribute_names("ObjectRoot")
    );


    // TEST ObjectRoot.FederateObject get_attribute_names()
    ClassAndPropertyNameList expectedFederateObjectAttributeList;
    expectedFederateObjectAttributeList.emplace_back(
            FederateObject::get_hla_class_name(), "FederateHandle"
    );
    expectedFederateObjectAttributeList.emplace_back(
            FederateObject::get_hla_class_name(), "FederateHost"
    );
    expectedFederateObjectAttributeList.emplace_back(
            FederateObject::get_hla_class_name(), "FederateType"
    );
    expectedFederateObjectAttributeList.sort();

    objectRootSP = FederateObject::create();

    CPPUNIT_ASSERT_EQUAL(expectedFederateObjectAttributeList, FederateObject::get_attribute_names());
    CPPUNIT_ASSERT_EQUAL(expectedFederateObjectAttributeList, objectRootSP->getAttributeNames());
    CPPUNIT_ASSERT_EQUAL(
            expectedFederateObjectAttributeList,
            ObjectRoot::get_attribute_names("ObjectRoot.FederateObject")
    );

    // TEST ObjectRoot.FederateObject get_all_attribute_names()
    ClassAndPropertyNameList expectedFederateObjectAllAttributeList(expectedObjectRootAllAttributeList);
    expectedFederateObjectAllAttributeList.insert(
            expectedFederateObjectAllAttributeList.end(),
            expectedFederateObjectAttributeList.begin(),
            expectedFederateObjectAttributeList.end()
    );
    expectedFederateObjectAllAttributeList.sort();

    CPPUNIT_ASSERT_EQUAL(expectedFederateObjectAllAttributeList, FederateObject::get_all_attribute_names());
    CPPUNIT_ASSERT_EQUAL(expectedFederateObjectAllAttributeList, objectRootSP->getAllAttributeNames());
    CPPUNIT_ASSERT_EQUAL(
            expectedFederateObjectAllAttributeList,
            ObjectRoot::get_all_attribute_names("ObjectRoot.FederateObject")
    );

    CPPUNIT_ASSERT_EQUAL(3, FederateObject::get_num_attributes());
    CPPUNIT_ASSERT_EQUAL(3, objectRootSP->getNumAttributes());
    CPPUNIT_ASSERT_EQUAL(3, ObjectRoot::get_num_attributes("ObjectRoot.FederateObject"));
}

void MessagingTests::interactionParameterHandleTest() {

    InteractionRoot::SP interactionRootSP;

    int expectedValue = RTIAmbassadorTest1::get_interaction_class_and_property_name_handle_map().find(
            ClassAndPropertyName("InteractionRoot.C2WInteractionRoot", "federateSequence")
    )->second;

    CPPUNIT_ASSERT_EQUAL(expectedValue, C2WInteractionRoot::get_parameter_handle("federateSequence"));
    interactionRootSP = C2WInteractionRoot::create_interaction();
    CPPUNIT_ASSERT_EQUAL(expectedValue, interactionRootSP->getParameterHandle("federateSequence"));
    CPPUNIT_ASSERT_EQUAL(expectedValue, InteractionRoot::get_parameter_handle(
            "InteractionRoot.C2WInteractionRoot", "federateSequence"
    ));

    CPPUNIT_ASSERT_EQUAL(expectedValue, SimLog::get_parameter_handle("federateSequence"));
    interactionRootSP = SimLog::create_interaction();
    CPPUNIT_ASSERT_EQUAL(expectedValue, interactionRootSP->getParameterHandle("federateSequence"));
    CPPUNIT_ASSERT_EQUAL(expectedValue, InteractionRoot::get_parameter_handle(
            "InteractionRoot.C2WInteractionRoot.SimLog", "federateSequence"
    ));

    CPPUNIT_ASSERT_EQUAL(expectedValue, HighPrio::get_parameter_handle("federateSequence"));
    interactionRootSP = HighPrio::create_interaction();
    CPPUNIT_ASSERT_EQUAL(expectedValue, interactionRootSP->getParameterHandle("federateSequence"));
    CPPUNIT_ASSERT_EQUAL(expectedValue, InteractionRoot::get_parameter_handle(
            "InteractionRoot.C2WInteractionRoot.SimLog.HighPrio", "federateSequence"
    ));

    expectedValue = RTIAmbassadorTest1::get_interaction_class_and_property_name_handle_map().find(
            ClassAndPropertyName("InteractionRoot.C2WInteractionRoot.SimLog", "FedName")
    )->second;

    CPPUNIT_ASSERT_EQUAL(expectedValue, SimLog::get_parameter_handle("FedName"));
    interactionRootSP = SimLog::create_interaction();
    CPPUNIT_ASSERT_EQUAL(expectedValue, interactionRootSP->getParameterHandle("FedName"));
    CPPUNIT_ASSERT_EQUAL(expectedValue, InteractionRoot::get_parameter_handle(
            "InteractionRoot.C2WInteractionRoot.SimLog", "FedName"
    ));

    CPPUNIT_ASSERT_EQUAL(expectedValue, HighPrio::get_parameter_handle("FedName"));
    interactionRootSP = HighPrio::create_interaction();
    CPPUNIT_ASSERT_EQUAL(expectedValue, interactionRootSP->getParameterHandle("FedName"));
    CPPUNIT_ASSERT_EQUAL(expectedValue, InteractionRoot::get_parameter_handle(
            "InteractionRoot.C2WInteractionRoot.SimLog.HighPrio", "FedName"
    ));
}

void MessagingTests::objectAttributeHandleTest() {

    ObjectRoot::SP objectRootSP;

    int expectedValue = RTIAmbassadorTest1::get_object_class_and_property_name_handle_map().find(
            ClassAndPropertyName("ObjectRoot.FederateObject", "FederateHost")
    )->second;

    CPPUNIT_ASSERT_EQUAL(expectedValue, FederateObject::get_attribute_handle("FederateHost"));
    objectRootSP = FederateObject::create_object();
    CPPUNIT_ASSERT_EQUAL(expectedValue, objectRootSP->getAttributeHandle("FederateHost"));
    CPPUNIT_ASSERT_EQUAL(expectedValue, ObjectRoot::get_attribute_handle(
            "ObjectRoot.FederateObject", "FederateHost"
    ));
}

BOOST_LOG_ATTRIBUTE_KEYWORD(messagingClassName, "MessagingClassName", std::string);
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", logging::trivial::severity_level);
BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime);

void MessagingTests::basicLogTest() {

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

std::string jsonToString(const Json::Value jsonArray) {
    Json::StreamWriterBuilder streamWriterBuilder;
    streamWriterBuilder["commentStyle"] = "None";
    std::unique_ptr<Json::StreamWriter> streamWriterUPtr(streamWriterBuilder.newStreamWriter());
    std::ostringstream stringOutputStream;
    streamWriterUPtr->write(jsonArray, &stringOutputStream);

    return stringOutputStream.str();
}

std::string createJsonArrayString(const std::string &value) {
    Json::Value jsonArray(Json::arrayValue);
    jsonArray.append( value );

    return jsonToString(jsonArray);
}

void MessagingTests::dynamicMessagingTest() {
    InteractionRoot dynamicSimLogInteraction(SimLog::get_hla_class_name());
    InteractionRoot *dynamicSimLogInteractionPtr = &dynamicSimLogInteraction;

    CPPUNIT_ASSERT(dynamicSimLogInteraction.isDynamicInstance());

    SimLog *simLogPtr1 = dynamic_cast<SimLog *>(dynamicSimLogInteractionPtr);
    CPPUNIT_ASSERT(simLogPtr1 == nullptr);

    CPPUNIT_ASSERT_EQUAL(SimLog::get_hla_class_name(), dynamicSimLogInteraction.getInstanceHlaClassName());

    std::string string1("string1");
    double doubleValue1(1.2);

    std::string jsonArrayString1 = createJsonArrayString(string1);
    dynamicSimLogInteraction.setParameter("InteractionRoot.C2WInteractionRoot", "federateSequence", jsonArrayString1);
    dynamicSimLogInteraction.setParameter("Time", doubleValue1);

    CPPUNIT_ASSERT_EQUAL(string1, C2WInteractionRoot::get_origin_federate_id(dynamicSimLogInteraction));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(
      doubleValue1, static_cast<double>(dynamicSimLogInteraction.getParameter("Time")), 0.01
    );

    std::string string2("string2");
    double doubleValue2(3.4);

    C2WInteractionRoot::update_federate_sequence(dynamicSimLogInteraction, string2);
    dynamicSimLogInteraction.setParameter("Time", doubleValue2);

    C2WInteractionRoot::StringList federateSequenceList1 =
      C2WInteractionRoot::get_federate_sequence_list(dynamicSimLogInteraction);

    CPPUNIT_ASSERT_EQUAL(string1, federateSequenceList1.front());
    CPPUNIT_ASSERT_EQUAL(string2, federateSequenceList1.back());
    CPPUNIT_ASSERT_DOUBLES_EQUAL(
      doubleValue2, static_cast<double>(dynamicSimLogInteraction.getParameter("Time")), 0.01
    );

    InteractionRoot::SP staticSimLogInteractionSP1 = InteractionRoot::create_interaction(SimLog::get_hla_class_name());
    CPPUNIT_ASSERT(!staticSimLogInteractionSP1->isDynamicInstance());

    InteractionRoot *staticSimLogInteraction1Ptr = staticSimLogInteractionSP1.get();

    SimLog *simLogPtr2 = dynamic_cast<SimLog *>(staticSimLogInteraction1Ptr);
    CPPUNIT_ASSERT(simLogPtr2 != nullptr);

    CPPUNIT_ASSERT_EQUAL(SimLog::get_hla_class_name(), staticSimLogInteractionSP1->getInstanceHlaClassName());

    std::string string3("string3");
    double doubleValue3(5.6);

    SimLog &simLogInteraction = *simLogPtr2;
    C2WInteractionRoot::update_federate_sequence(simLogInteraction, string3);
    simLogInteraction.setParameter("Time", doubleValue3);

    CPPUNIT_ASSERT_EQUAL(string3, C2WInteractionRoot::get_source_federate_id(simLogInteraction));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(doubleValue3, static_cast<double>(simLogInteraction.getParameter("Time")), 0.01);

    CPPUNIT_ASSERT_EQUAL(string3, simLogInteraction.getSourceFederateId());
    CPPUNIT_ASSERT_DOUBLES_EQUAL(doubleValue3, simLogInteraction.get_Time(), 0.01);

    std::string string4("string4");
    double doubleValue4(17.3);

    // federateSequence SHOULD NOT BE UPDATED (CAN ONLY UPDATE ONCE PER INTERACTION)
    simLogInteraction.updateFederateSequence(string4);
    simLogInteraction.set_Time(doubleValue4);

    CPPUNIT_ASSERT_EQUAL(string3, C2WInteractionRoot::get_source_federate_id(simLogInteraction));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(doubleValue4, simLogInteraction.getParameter("Time").asDouble(), 0.01);

    CPPUNIT_ASSERT_EQUAL(string3, simLogInteraction.getSourceFederateId());
    CPPUNIT_ASSERT_DOUBLES_EQUAL(doubleValue4, simLogInteraction.get_Time(), 0.01);
}

void MessagingTests::valueTest() {

    InteractionRoot testBase("InteractionRoot.TestBase");
    testBase.setParameter("field1", "value1");
    testBase.setParameter("field2", 5);

    InteractionRoot testDerived("InteractionRoot.TestBase.TestDerived");
    testDerived.setParameter("field1", "value2");
    testDerived.setParameter("field2", -6);
    testDerived.setParameter("field3", true);
    testDerived.setParameter("field4", 10L);
    testDerived.setParameter("field5", 3.14);

    CPPUNIT_ASSERT_EQUAL(std::string("value1"), testBase.getParameter("field1").asString());
    CPPUNIT_ASSERT_EQUAL(5, testBase.getParameter("field2").asInt());

    CPPUNIT_ASSERT_EQUAL(std::string("value2"), testDerived.getParameter("field1").asString());
    CPPUNIT_ASSERT_EQUAL(-6, testDerived.getParameter("field2").asInt());
    CPPUNIT_ASSERT(testDerived.getParameter("field3").asBool());
    CPPUNIT_ASSERT_EQUAL(10L, testDerived.getParameter("field4").asLong());
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3.14, testDerived.getParameter("field5").asDouble(), 0.01);
}

void MessagingTests::messagingInstanceHlaClassTest() {
    InteractionRoot interactionRoot( "InteractionRoot.C2WInteractionRoot.Simlog.HighPrio" );

    CPPUNIT_ASSERT( interactionRoot.isInstanceOfHlaClass(
            "InteractionRoot.C2WInteractionRoot.Simlog.HighPrio"
    ));
    CPPUNIT_ASSERT( interactionRoot.isInstanceHlaClassDerivedFromHlaClass(
            "InteractionRoot.C2WInteractionRoot.Simlog.HighPrio"
    ));
    CPPUNIT_ASSERT( interactionRoot.isInstanceHlaClassDerivedFromHlaClass(
            "InteractionRoot.C2WInteractionRoot.Simlog"
    ));

    CPPUNIT_ASSERT( !interactionRoot.isInstanceOfHlaClass(
            "InteractionRoot.C2WInteractionRoot.Simlog"
    ));
    CPPUNIT_ASSERT( !interactionRoot.isInstanceHlaClassDerivedFromHlaClass(
            "InteractionRoot.C2WInteractionRoot.SimulationControl"
    ));

    ObjectRoot objectRoot;

    CPPUNIT_ASSERT( objectRoot.isInstanceOfHlaClass("ObjectRoot"));
    CPPUNIT_ASSERT( objectRoot.isInstanceHlaClassDerivedFromHlaClass("ObjectRoot"));
    CPPUNIT_ASSERT( !objectRoot.isInstanceHlaClassDerivedFromHlaClass("ObjectRoot.FederateObject"));
    CPPUNIT_ASSERT( !objectRoot.isInstanceOfHlaClass("ObjectRoot.FederateObject"));

    ObjectRoot federateObject("ObjectRoot.FederateObject");
    CPPUNIT_ASSERT( !federateObject.isInstanceOfHlaClass("ObjectRoot"));
    CPPUNIT_ASSERT( federateObject.isInstanceHlaClassDerivedFromHlaClass("ObjectRoot"));
    CPPUNIT_ASSERT( federateObject.isInstanceHlaClassDerivedFromHlaClass("ObjectRoot.FederateObject"));
    CPPUNIT_ASSERT( federateObject.isInstanceOfHlaClass("ObjectRoot.FederateObject"));
}

void MessagingTests::federateSequenceTest() {

    // CHECK federateSequence THAT STARTS OUT EMPTY
    InteractionRoot interactionRoot1("InteractionRoot.C2WInteractionRoot.SimLog");

    std::string federateName1("federateName1");

    // ADD federateName1 TO federateSequence
    C2WInteractionRoot::update_federate_sequence(interactionRoot1, federateName1);

    // MAKE SURE IT'S THERE
    C2WInteractionRoot::StringList federateSequenceList1 =
      C2WInteractionRoot::get_federate_sequence_list(interactionRoot1);

    CPPUNIT_ASSERT_EQUAL(1, static_cast<int>(federateSequenceList1.size()));
    CPPUNIT_ASSERT_EQUAL(federateName1, federateSequenceList1.front());

    // ADD IT AGAIN
    C2WInteractionRoot::update_federate_sequence(interactionRoot1, federateName1);

    // MAKE SURE federateSequence IS UNCHANGED
    C2WInteractionRoot::StringList federateSequenceList2 =
      C2WInteractionRoot::get_federate_sequence_list(interactionRoot1);

    CPPUNIT_ASSERT_EQUAL(1, static_cast<int>(federateSequenceList2.size()));
    CPPUNIT_ASSERT_EQUAL(federateName1, federateSequenceList2.front());


    // CHECK federateSequence THAT STARTS OUT NON-EMPTY
    InteractionRoot interactionRoot2("InteractionRoot.C2WInteractionRoot.SimLog");

    C2WInteractionRoot::StringList federateNameList;
    federateNameList.push_back("federateName2");
    federateNameList.push_back("federateName3");

    Json::Value jsonArray(Json::arrayValue);
    for(
      C2WInteractionRoot::StringList::const_iterator stlCit = federateNameList.begin() ;
      stlCit != federateNameList.end() ;
      ++stlCit
    ) {
        jsonArray.append( *stlCit );
    }

    interactionRoot2.setParameter("federateSequence", jsonToString(jsonArray));

    // ADD federateName1 TO federateSequence
    C2WInteractionRoot::update_federate_sequence(interactionRoot2, federateName1);

    // MAKE SURE IT'S THERE
    C2WInteractionRoot::StringList federateSequenceList3 =
      C2WInteractionRoot::get_federate_sequence_list(interactionRoot2);
    federateNameList.push_back(federateName1);

    CPPUNIT_ASSERT_EQUAL(federateNameList.size(), federateSequenceList3.size());
    C2WInteractionRoot::StringList::const_iterator fnlCit = federateNameList.begin();
    C2WInteractionRoot::StringList::const_iterator fl3Cit = federateSequenceList3.begin();
    while( fnlCit != federateNameList.end() ) {
        CPPUNIT_ASSERT_EQUAL(*fnlCit, *fl3Cit);
        ++fnlCit;
        ++fl3Cit;
    }

    // ADD IT AGAIN
    C2WInteractionRoot::update_federate_sequence(interactionRoot2, federateName1);

    // MAKE SURE federateSequence IS UNCHANGED
    C2WInteractionRoot::StringList federateSequenceList4 =
      C2WInteractionRoot::get_federate_sequence_list(interactionRoot2);

    CPPUNIT_ASSERT_EQUAL(federateNameList.size(), federateSequenceList3.size());
    fnlCit = federateNameList.begin();
    fl3Cit = federateSequenceList3.begin();
    while( fnlCit != federateNameList.end() ) {
        CPPUNIT_ASSERT_EQUAL(*fnlCit, *fl3Cit);
        ++fnlCit;
        ++fl3Cit;
    }
}

void compareClassAndPropertyNameSets(
  const ClassAndPropertyNameSet &expectedClassAndPropertyNameSet,
  const ClassAndPropertyNameSet &actualClassAndPropertyNameSet
) {
    ClassAndPropertyNameList expectedClassAndPropertyNameList(
        expectedClassAndPropertyNameSet.begin(), expectedClassAndPropertyNameSet.end()
    );
    expectedClassAndPropertyNameList.sort();

    ClassAndPropertyNameList actualClassAndPropertyNameList(
        actualClassAndPropertyNameSet.begin(), actualClassAndPropertyNameSet.end()
    );
    actualClassAndPropertyNameList.sort();

    CPPUNIT_ASSERT_EQUAL(expectedClassAndPropertyNameList.size(), actualClassAndPropertyNameList.size());

    ClassAndPropertyNameList::const_iterator eclCit = expectedClassAndPropertyNameList.begin();
    ClassAndPropertyNameList::const_iterator aclCit = actualClassAndPropertyNameList.begin();

    while(eclCit != expectedClassAndPropertyNameList.end()) {
        CPPUNIT_ASSERT_EQUAL(*eclCit, *aclCit);
        ++eclCit;
        ++aclCit;
    }
}

void MessagingTests::attributePubSubTest() {

    // PUBLISH
    ClassAndPropertyNameSet expectedPublishedClassAndPropertyNameSet;

    expectedPublishedClassAndPropertyNameSet.emplace(
            "ObjectRoot.BaseObjectClass.DerivedObjectClass", "int_attribute1"
    );
    expectedPublishedClassAndPropertyNameSet.emplace(
            "ObjectRoot.BaseObjectClass.DerivedObjectClass", "int_attribute2"
    );
    expectedPublishedClassAndPropertyNameSet.emplace(
            "ObjectRoot.BaseObjectClass.DerivedObjectClass", "string_attribute2"
    );
    expectedPublishedClassAndPropertyNameSet.emplace(
            "ObjectRoot.BaseObjectClass", "int_attribute1"
    );
    expectedPublishedClassAndPropertyNameSet.emplace(
            "ObjectRoot.BaseObjectClass", "string_attribute1"
    );

    DerivedObjectClass::publish_int_attribute1_attribute();
    DerivedObjectClass::publish_int_attribute2_attribute();
    DerivedObjectClass::publish_attribute("ObjectRoot.BaseObjectClass", "int_attribute1");
    DerivedObjectClass::publish_string_attribute1_attribute();
    DerivedObjectClass::publish_string_attribute2_attribute();

    ObjectRoot::ClassAndPropertyNameSetSP actualPublishedClassAndPropertyNameSetSP =
            DerivedObjectClass::get_published_attribute_name_set_sp();

    compareClassAndPropertyNameSets(
      expectedPublishedClassAndPropertyNameSet, *actualPublishedClassAndPropertyNameSetSP
    );

    // UNPUBLISH
    DerivedObjectClass::unpublish_int_attribute1_attribute();
    DerivedObjectClass::unpublish_attribute("ObjectRoot.BaseObjectClass", "int_attribute1");

    expectedPublishedClassAndPropertyNameSet.erase( ClassAndPropertyName(
            "ObjectRoot.BaseObjectClass.DerivedObjectClass", "int_attribute1"
    ));
    expectedPublishedClassAndPropertyNameSet.erase( ClassAndPropertyName(
            "ObjectRoot.BaseObjectClass", "int_attribute1"
    ));

    compareClassAndPropertyNameSets(
      expectedPublishedClassAndPropertyNameSet, *actualPublishedClassAndPropertyNameSetSP
    );

    // SUBSCRIBE
    ClassAndPropertyNameSet expectedSubscribedClassAndPropertyNameSet;

    expectedSubscribedClassAndPropertyNameSet.emplace(
            "ObjectRoot.BaseObjectClass.DerivedObjectClass", "int_attribute1"
    );
    expectedSubscribedClassAndPropertyNameSet.emplace(
            "ObjectRoot.BaseObjectClass.DerivedObjectClass", "int_attribute2"
    );
    expectedSubscribedClassAndPropertyNameSet.emplace(
            "ObjectRoot.BaseObjectClass.DerivedObjectClass", "string_attribute2"
    );
    expectedSubscribedClassAndPropertyNameSet.emplace(
            "ObjectRoot.BaseObjectClass", "int_attribute1"
    );
    expectedSubscribedClassAndPropertyNameSet.emplace(
            "ObjectRoot.BaseObjectClass", "string_attribute1"
    );

    DerivedObjectClass::subscribe_int_attribute1_attribute();
    DerivedObjectClass::subscribe_int_attribute2_attribute();
    DerivedObjectClass::subscribe_attribute("ObjectRoot.BaseObjectClass", "int_attribute1");
    DerivedObjectClass::subscribe_string_attribute1_attribute();
    DerivedObjectClass::subscribe_string_attribute2_attribute();

    ObjectRoot::ClassAndPropertyNameSetSP actualSubscribedClassAndPropertyNameSetSP =
            DerivedObjectClass::get_subscribed_attribute_name_set_sp();

    compareClassAndPropertyNameSets(
      expectedSubscribedClassAndPropertyNameSet, *actualSubscribedClassAndPropertyNameSetSP
    );

    // UNSUBSCRIBE
    DerivedObjectClass::unsubscribe_int_attribute1_attribute();
    DerivedObjectClass::unsubscribe_attribute("ObjectRoot.BaseObjectClass", "int_attribute1");

    expectedSubscribedClassAndPropertyNameSet.erase( ClassAndPropertyName(
            "ObjectRoot.BaseObjectClass.DerivedObjectClass", "int_attribute1"
    ));
    expectedSubscribedClassAndPropertyNameSet.erase( ClassAndPropertyName(
            "ObjectRoot.BaseObjectClass", "int_attribute1"
    ));

    compareClassAndPropertyNameSets(
      expectedSubscribedClassAndPropertyNameSet, *actualSubscribedClassAndPropertyNameSetSP
    );
}

void MessagingTests::printInteractionTest() {
    C2WInteractionRoot c2wInteractionRoot;
    c2wInteractionRoot.updateFederateSequence( "Hello" );
    c2wInteractionRoot.set_actualLogicalGenerationTime( 2.1 );
    c2wInteractionRoot.set_federateFilter( "GoodBye" );

    std::ostringstream testStream;

    testStream << c2wInteractionRoot;

    std::string expectedOutput =
      std::string("InteractionRoot.C2WInteractionRoot(") +
      "InteractionRoot.C2WInteractionRoot>actualLogicalGenerationTime: 2.1, " +
      "InteractionRoot.C2WInteractionRoot>federateFilter: \"GoodBye\", " +
      "InteractionRoot.C2WInteractionRoot>federateSequence: \"[ \"Hello\" ]\"" +
      ")";

    CPPUNIT_ASSERT_EQUAL(expectedOutput, testStream.str());
}

void MessagingTests::rejectSourceFederateIdTest() {

    const std::string interactionRootHlaClassName( InteractionRoot::get_hla_class_name() );
    C2WInteractionRoot::add_reject_source_federate_id(interactionRootHlaClassName, "foobar");
    CPPUNIT_ASSERT(!C2WInteractionRoot::is_reject_source_federate_id(interactionRootHlaClassName, "foobar"));

    HighPrio highPrio1;
    HighPrio::add_reject_source_federate_id("foo");
    highPrio1.addRejectSourceFederateId("bar");


    Json::Value jsonArray(Json::arrayValue);

    jsonArray.append("foo");
    highPrio1.set_federateSequence(jsonToString(jsonArray));
    CPPUNIT_ASSERT(highPrio1.isRejectSourceFederateId());
    CPPUNIT_ASSERT(HighPrio::is_reject_source_federate_id(highPrio1));

    jsonArray.append("boz");
    highPrio1.set_federateSequence(jsonToString(jsonArray));
    CPPUNIT_ASSERT(!highPrio1.isRejectSourceFederateId());
    CPPUNIT_ASSERT(!HighPrio::is_reject_source_federate_id(highPrio1));

    jsonArray.append("bar");
    highPrio1.set_federateSequence(jsonToString(jsonArray));
    CPPUNIT_ASSERT(highPrio1.isRejectSourceFederateId());
    CPPUNIT_ASSERT(HighPrio::is_reject_source_federate_id(highPrio1));

    highPrio1.removeRejectSourceFederateId("bar");
    CPPUNIT_ASSERT(!highPrio1.isRejectSourceFederateId());
    CPPUNIT_ASSERT(!HighPrio::is_reject_source_federate_id(highPrio1));


    const std::string highPrioHlaClassName = HighPrio::get_hla_class_name();
    InteractionRoot highPrio2(highPrioHlaClassName);
    C2WInteractionRoot::add_reject_source_federate_id(highPrioHlaClassName, "foo");
    C2WInteractionRoot::add_reject_source_federate_id(highPrioHlaClassName, "bar");

    jsonArray.clear();

    jsonArray.append("foo");
    highPrio2.setParameter("federateSequence", jsonToString(jsonArray));
    CPPUNIT_ASSERT(C2WInteractionRoot::is_reject_source_federate_id(highPrio2));

    jsonArray.append("boz");
    highPrio2.setParameter("federateSequence", jsonToString(jsonArray));
    CPPUNIT_ASSERT(!C2WInteractionRoot::is_reject_source_federate_id(highPrio2));

    jsonArray.append("bar");
    highPrio2.setParameter("federateSequence", jsonToString(jsonArray));
    CPPUNIT_ASSERT(C2WInteractionRoot::is_reject_source_federate_id(highPrio2));

    C2WInteractionRoot::remove_reject_source_federate_id(highPrioHlaClassName, "bar");
    CPPUNIT_ASSERT(!C2WInteractionRoot::is_reject_source_federate_id(highPrio2));
}

CPPUNIT_TEST_SUITE_REGISTRATION( MessagingTests );
