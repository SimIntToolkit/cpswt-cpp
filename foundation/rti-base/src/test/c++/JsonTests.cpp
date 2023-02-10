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

#include "JsonTests.hpp"

#include "Initialization.hpp"

#include <jsoncpp/json/json.h>

#include "InteractionRoot_p/C2WInteractionRoot_p/SimulationControl_p/SimEnd.hpp"
#include "ObjectRoot_p/FederateObject.hpp"

using InteractionRoot = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot;
using ObjectRoot = ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot;

using SimEnd = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::SimulationControl_p::SimEnd;
using FederateObject = ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::FederateObject;

JsonTests::JsonTests() : CppUnit::TestCase() {
    Initialization::init_1();
}

void JsonTests::interactionJsonTest() {

    std::cout << "START interactionJsonTest" << std::endl;

    SimEnd simEnd1;
    Json::Value jsonArray(Json::arrayValue);
    jsonArray.append("Federate1");
    jsonArray.append("Federate2");

    Json::StreamWriterBuilder streamWriterBuilder;
    streamWriterBuilder["commandStyle"] = "None";
    streamWriterBuilder["indentation"] = "    ";
    std::unique_ptr<Json::StreamWriter> streamWriterUPtr(streamWriterBuilder.newStreamWriter());
    std::ostringstream stringOutputStream;
    streamWriterUPtr->write(jsonArray, &stringOutputStream);
    std::string jsonArrayString(stringOutputStream.str());

    simEnd1.set_federateSequence(jsonArrayString);
    simEnd1.set_actualLogicalGenerationTime(5.0);
    simEnd1.set_federateFilter("Filter1");

    std::string jsonString = simEnd1.toJson();

    SimEnd::SP simEndSP = boost::static_pointer_cast<SimEnd>(InteractionRoot::fromJson(jsonString));
    SimEnd &simEnd2 = *simEndSP;

    CPPUNIT_ASSERT_EQUAL(simEnd1.get_federateSequence(), simEnd2.get_federateSequence());
    CPPUNIT_ASSERT_DOUBLES_EQUAL(
      simEnd1.get_actualLogicalGenerationTime(), simEnd2.get_actualLogicalGenerationTime(), 0.01
    );
    CPPUNIT_ASSERT_EQUAL(simEnd1.get_federateFilter(), simEnd2.get_federateFilter());

    std::cout << "END interactionJsonTest" << std::endl;
}

void JsonTests::objectJsonTest() {

    std::cout << "START objectJsonTest" << std::endl;

    FederateObject::publish_object(RTIAmbassadorTest1::get_rti_ambassador_1_ptr());

    FederateObject::publish_FederateType_attribute();
    FederateObject::publish_FederateHost_attribute();
    FederateObject::publish_FederateHandle_attribute();

    FederateObject::soft_subscribe_FederateType_attribute();
    FederateObject::soft_subscribe_FederateHost_attribute();
    FederateObject::soft_subscribe_FederateHandle_attribute();

    FederateObject federateObject1;

    federateObject1.set_FederateType("FederateType1");
    federateObject1.set_FederateHost("FederateHost1");
    federateObject1.set_FederateHandle(20);

    federateObject1.registerObject(RTIAmbassadorTest1::get_rti_ambassador_1_ptr(), "MyObject1");
    int federateObjectHandle = federateObject1.getObjectHandle();

    std::string jsonString = federateObject1.toJson();
    federateObject1.unregisterObject(RTIAmbassadorTest1::get_rti_ambassador_1_ptr());

    FederateObject::SP federateObjectSP = boost::static_pointer_cast<FederateObject>(
      ObjectRoot::discover(FederateObject::get_class_handle(), federateObjectHandle)
    );
    FederateObject &federateObject2 = *federateObjectSP;

    ObjectRoot::ObjectReflector::SP objectReflectorSP = ObjectRoot::fromJson(jsonString);
    objectReflectorSP->reflect();

    CPPUNIT_ASSERT_EQUAL(federateObject1.get_FederateType(), federateObject2.get_FederateType());
    CPPUNIT_ASSERT_EQUAL(federateObject1.get_FederateHost(), federateObject2.get_FederateHost());
    CPPUNIT_ASSERT_EQUAL(federateObject1.get_FederateHandle(), federateObject2.get_FederateHandle());

    std::cout << "END objectJsonTest" << std::endl;
}

CPPUNIT_TEST_SUITE_REGISTRATION( JsonTests );
