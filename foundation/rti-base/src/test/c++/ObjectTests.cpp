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

#include "ObjectTests.hpp"

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

#include <jsoncpp/json/json.h>

using ObjectRoot = ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot;
using FederateObject = ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::FederateObject;

ObjectTests::ObjectTests() : CppUnit::TestCase() {
    Initialization::init_1();
}

void ObjectTests::objectTest1() {

    std::cout << "START objectTest1" << std::endl;

    // MAKE SURE ATTRIBUTES ARE PUBLISHED
    FederateObject::publish_FederateHandle_attribute();
    FederateObject::publish_FederateHost_attribute();
    FederateObject::publish_FederateType_attribute();
    FederateObject::publish_object(RTIAmbassadorTest1::get_rti_ambassador_1_ptr());  // NOT REALLY NEEDED FOR TESTING

    // CREATE FederateObject, GIVE ATTRIBUTES VALUES
    FederateObject federateObject1;
    federateObject1.set_FederateHandle(2);
    federateObject1.set_FederateHost("localhost");
    federateObject1.set_FederateType("test");

    // REGISTER THE OBJECT WITH MOCK RTI
    federateObject1.registerObject(RTIAmbassadorTest1::get_rti_ambassador_1_ptr());

    // CHECK MOST RTI VALUES
//    CPPUNIT_ASSERT_EQUAL(
//      static_cast<RTI::ObjectHandle>(0), RTIAmbassadorTest1::get_rti_ambassador_test_1().getCurrentObjectHandle()
//    );
    CPPUNIT_ASSERT_EQUAL(
      static_cast<RTI::ObjectClassHandle>(FederateObject::get_class_handle()),
      RTIAmbassadorTest1::get_rti_ambassador_test_1().getCurrentClassHandle()
    );

    // DISCOVER OBJECT INSTANCE TO CREATE A SECOND INSTANCE
    ObjectRoot::SP objectRootSP1 = ObjectRoot::discover(
      RTIAmbassadorTest1::get_rti_ambassador_test_1().getCurrentClassHandle(),
      RTIAmbassadorTest1::get_rti_ambassador_test_1().getCurrentObjectHandle()
    );
    FederateObject::SP federateObjectSP2 = boost::dynamic_pointer_cast<FederateObject>(objectRootSP1);
    CPPUNIT_ASSERT(federateObjectSP2);

    // INITIALLY, SECOND INSTANCE SHOULD HAVE DEFAULT VALUES
    FederateObject &federateObject2 = *federateObjectSP2;
    CPPUNIT_ASSERT_EQUAL(0, federateObject2.get_FederateHandle());
    CPPUNIT_ASSERT_EQUAL(std::string(""), federateObject2.get_FederateHost());
    CPPUNIT_ASSERT_EQUAL(std::string(""), federateObject2.get_FederateType());

    // SEND OUT ATTRIBUTE VALUES OF FIRST INSTANCE TO MOCK RTI
    federateObject1.updateAttributeValues(RTIAmbassadorTest1::get_rti_ambassador_1_ptr(), 5.0);

    // CHECK MOCK RTI VALUES
    RTIfedTime *currentRTIFedTimeImplPtr =
      RTIAmbassadorTest1::get_rti_ambassador_test_1().getCurrentRTIFedTimeImplPtr();
    CPPUNIT_ASSERT(currentRTIFedTimeImplPtr);
    RTIfedTime &currentRTIFedTimeImpl1 = *currentRTIFedTimeImplPtr;
    CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0, currentRTIFedTimeImpl1.getTime(), 0.1);

    // ALL VALUES SHOULD BE UPDATED (3)
    RTI::AttributeHandleValuePairSet &currentAttributeHandleValuePairSet1 =
      RTIAmbassadorTest1::get_rti_ambassador_test_1().getCurrentAttributeHandleValuePairSet();
    CPPUNIT_ASSERT_EQUAL(static_cast<RTI::ULong>(3), currentAttributeHandleValuePairSet1.size());

    // REFLECT UPDATED ATTRIBUTE VALUES TO SECOND INSTANCE
    FederateObject::reflect(
      RTIAmbassadorTest1::get_rti_ambassador_test_1().getCurrentObjectHandle(),
      currentAttributeHandleValuePairSet1, currentRTIFedTimeImpl1
    );
    CPPUNIT_ASSERT_EQUAL(2, federateObject2.get_FederateHandle());
    CPPUNIT_ASSERT_EQUAL(std::string("localhost"), federateObject2.get_FederateHost());
    CPPUNIT_ASSERT_EQUAL(std::string("test"), federateObject2.get_FederateType());

    // CHANGE ONLY ONE VALUE IN FIRST INSTANCE AND SEND OUT UPDATE TO MOCK RTI
    federateObject1.set_FederateType("foobar");
    federateObject1.updateAttributeValues(RTIAmbassadorTest1::get_rti_ambassador_1_ptr(), 6.0);

    // CHECK MOCK RTI VALUES
    currentRTIFedTimeImplPtr = RTIAmbassadorTest1::get_rti_ambassador_test_1().getCurrentRTIFedTimeImplPtr();
    CPPUNIT_ASSERT(currentRTIFedTimeImplPtr);
    RTIfedTime &currentRTIFedTimeImpl2 = *currentRTIFedTimeImplPtr;
    CPPUNIT_ASSERT_DOUBLES_EQUAL(6.0, currentRTIFedTimeImpl2.getTime(), 0.1);

    // ONLY ONE VALUE SHOULD BE UPDATED SINCE ONLY ONE WAS CHANGED
    RTI::AttributeHandleValuePairSet &currentAttributeHandleValuePairSet2 =
      RTIAmbassadorTest1::get_rti_ambassador_test_1().getCurrentAttributeHandleValuePairSet();
    CPPUNIT_ASSERT_EQUAL(static_cast<RTI::ULong>(1), currentAttributeHandleValuePairSet2.size());

    // REFLECT CHANGED ATTRIBUTE INTO SECOND INSTANCE, CHECK VALUES
    FederateObject::reflect(
      RTIAmbassadorTest1::get_rti_ambassador_test_1().getCurrentObjectHandle(),
      currentAttributeHandleValuePairSet2,
      currentRTIFedTimeImpl2
    );
    CPPUNIT_ASSERT_EQUAL(2, federateObject2.get_FederateHandle());
    CPPUNIT_ASSERT_EQUAL(std::string("localhost"), federateObject2.get_FederateHost());
    CPPUNIT_ASSERT_EQUAL(std::string("foobar"), federateObject2.get_FederateType());

    std::cout << "END objectTest1" << std::endl;
}

void ObjectTests::publishObjectTest() {

    std::cout << "START publishObjectTest" << std::endl;

    typedef boost::shared_ptr<ClassAndPropertyNameSet> ClassAndPropertyNameSetSP;

    const std::string testBaseFullHlaClassName = "ObjectRoot.TestBase";
    const std::string testDerivedFullHlaClassName = "ObjectRoot.TestBase.TestDerived";

    std::map<std::string, ClassAndPropertyNameSetSP> localHlaClassNameAttributeHandleSetSPMap;


    ClassAndPropertyNameSetSP classAndPropertyNameTestBaseSetSP( new ClassAndPropertyNameSet() );
    localHlaClassNameAttributeHandleSetSPMap.emplace(testBaseFullHlaClassName, classAndPropertyNameTestBaseSetSP);

    ClassAndPropertyNameSet &classAndPropertyNameTestBaseSet =
      *localHlaClassNameAttributeHandleSetSPMap[testBaseFullHlaClassName];

    ClassAndPropertyName classAndPropertyNameTestBaseField1(testBaseFullHlaClassName, "field1");
    classAndPropertyNameTestBaseSet.emplace(classAndPropertyNameTestBaseField1);

    ClassAndPropertyName classAndPropertyNameTestBaseField2(testBaseFullHlaClassName, "field2");
    classAndPropertyNameTestBaseSet.emplace(classAndPropertyNameTestBaseField2);


    ClassAndPropertyNameSetSP classAndPropertyNameTestDerivedSetSP(new ClassAndPropertyNameSet());
    localHlaClassNameAttributeHandleSetSPMap.emplace(testDerivedFullHlaClassName, classAndPropertyNameTestDerivedSetSP);

    ClassAndPropertyNameSet &classAndPropertyNameTestDerivedSet =
      *localHlaClassNameAttributeHandleSetSPMap[testDerivedFullHlaClassName];

    classAndPropertyNameTestDerivedSet.emplace(classAndPropertyNameTestBaseField1);

    ClassAndPropertyName classAndPropertyNameTestDerivedField3(testDerivedFullHlaClassName, "field3");
    classAndPropertyNameTestDerivedSet.emplace(classAndPropertyNameTestDerivedField3);

    ClassAndPropertyName classAndPropertyNameTestDerivedField4(testDerivedFullHlaClassName, "field4");
    // DO NOT ADD classAndPropertyNameTestDerivedField4 TO classAndPropertyNameTestDerivedSet

    ClassAndPropertyName classAndPropertyNameTestDerivedField5(testDerivedFullHlaClassName, "field5");
    classAndPropertyNameTestDerivedSet.emplace(classAndPropertyNameTestDerivedField5);

    ObjectRoot::publish_attribute(
            testBaseFullHlaClassName,
            classAndPropertyNameTestBaseField1.getClassName(),
            classAndPropertyNameTestBaseField1.getPropertyName()
    );
    ObjectRoot::publish_attribute(
            testBaseFullHlaClassName,
            classAndPropertyNameTestBaseField2.getClassName(),
            classAndPropertyNameTestBaseField2.getPropertyName()
    );

    ClassAndPropertyNameSetSP testBasePublishedClassAndPropertyNameSetSP =
            ObjectRoot::get_published_class_and_property_name_set_sp(testBaseFullHlaClassName);
    CPPUNIT_ASSERT(testBasePublishedClassAndPropertyNameSetSP->empty());

    ObjectRoot::publish_object(testBaseFullHlaClassName, RTIAmbassadorTest1::get_rti_ambassador_1_ptr());
    testBasePublishedClassAndPropertyNameSetSP =
            ObjectRoot::get_published_class_and_property_name_set_sp(testBaseFullHlaClassName);

    CPPUNIT_ASSERT_EQUAL(
      testBasePublishedClassAndPropertyNameSetSP->size(), classAndPropertyNameTestBaseSet.size()
    );
    for(const ClassAndPropertyName &classAndPropertyName : *testBasePublishedClassAndPropertyNameSetSP) {
        CPPUNIT_ASSERT(
          classAndPropertyNameTestBaseSet.find(classAndPropertyName) != classAndPropertyNameTestBaseSet.end()
        );
    }

    ObjectRoot::publish_attribute(
            testDerivedFullHlaClassName,
            classAndPropertyNameTestBaseField1.getClassName(),
            classAndPropertyNameTestBaseField1.getPropertyName()
    );
    ObjectRoot::publish_attribute(
            testDerivedFullHlaClassName,
            classAndPropertyNameTestDerivedField3.getClassName(),
            classAndPropertyNameTestDerivedField3.getPropertyName()
    );
    ObjectRoot::publish_attribute(
            testDerivedFullHlaClassName,
            classAndPropertyNameTestDerivedField4.getClassName(),
            classAndPropertyNameTestDerivedField4.getPropertyName()
    );
    ObjectRoot::unpublish_attribute(
            testDerivedFullHlaClassName,
            classAndPropertyNameTestDerivedField4.getClassName(),
            classAndPropertyNameTestDerivedField4.getPropertyName()
    );
    ObjectRoot::publish_attribute(
            testDerivedFullHlaClassName,
            classAndPropertyNameTestDerivedField5.getClassName(),
            classAndPropertyNameTestDerivedField5.getPropertyName()
    );

    ClassAndPropertyNameSetSP testDerivedPublishedClassAndPropertyNameSetSP =
            ObjectRoot::get_published_class_and_property_name_set_sp(testDerivedFullHlaClassName);
    CPPUNIT_ASSERT(testDerivedPublishedClassAndPropertyNameSetSP->empty());

    ObjectRoot::publish_object(testDerivedFullHlaClassName, RTIAmbassadorTest1::get_rti_ambassador_1_ptr());
    testDerivedPublishedClassAndPropertyNameSetSP =
            ObjectRoot::get_published_class_and_property_name_set_sp(testDerivedFullHlaClassName);

    CPPUNIT_ASSERT_EQUAL(
      testDerivedPublishedClassAndPropertyNameSetSP->size(), classAndPropertyNameTestDerivedSet.size()
    );
    for(const ClassAndPropertyName &classAndPropertyName : *testDerivedPublishedClassAndPropertyNameSetSP) {
        CPPUNIT_ASSERT(
          classAndPropertyNameTestDerivedSet.find(classAndPropertyName) != classAndPropertyNameTestDerivedSet.end()
        );
    }

    std::cout << "END publishObjectTest" << std::endl;
}

CPPUNIT_TEST_SUITE_REGISTRATION( ObjectTests );
