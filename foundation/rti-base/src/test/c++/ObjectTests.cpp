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

using ObjectRoot = ::org::cpswt::hla::ObjectRoot;
using FederateObject = ::org::cpswt::hla::ObjectRoot_p::FederateObject;

RTI::RTIambassador *ObjectTests::get_rti_ambassador_1_ptr() {
    static RTI::RTIambassador rtiAmbassador(&get_rti_ambassador_test_1());
    return &rtiAmbassador;
}

void ObjectTests::init_1() {
    if (get_is_initialized()) {
        return;
    }
    get_is_initialized() = true;

    std::cout << "INITIALIZING ... " << std::flush;
    ObjectRoot::init(get_rti_ambassador_1_ptr());
    std::cout << "DONE" << std::endl;
}

void ObjectTests::objectTest1() {

std::cout << 1 << std::endl;
    // MAKE SURE ATTRIBUTES ARE PUBLISHED
    FederateObject::publish_FederateHandle_attribute();
    FederateObject::publish_FederateHost_attribute();
    FederateObject::publish_FederateType_attribute();
    FederateObject::publish_object(get_rti_ambassador_1_ptr());  // NOT REALLY NEEDED FOR TESTING

    // CREATE FederateObject, GIVE ATTRIBUTES VALUES
std::cout << 2 << std::endl;
    FederateObject federateObject1;
    federateObject1.set_FederateHandle(2);
    federateObject1.set_FederateHost("localhost");
    federateObject1.set_FederateType("test");

    // REGISTER THE OBJECT WITH MOCK RTI
    federateObject1.registerObject(get_rti_ambassador_1_ptr());

    // CHECK MOST RTI VALUES
std::cout << 3 << std::endl;
    CPPUNIT_ASSERT_EQUAL(static_cast<RTI::ObjectHandle>(0), get_rti_ambassador_test_1().getCurrentObjectHandle());
    CPPUNIT_ASSERT_EQUAL(
      static_cast<RTI::ObjectClassHandle>(FederateObject::get_class_handle()),
      get_rti_ambassador_test_1().getCurrentClassHandle()
    );

    // DISCOVER OBJECT INSTANCE TO CREATE A SECOND INSTANCE
    ObjectRoot::SP objectRootSP1 = ObjectRoot::discover(
      get_rti_ambassador_test_1().getCurrentClassHandle(), get_rti_ambassador_test_1().getCurrentObjectHandle()
    );
    FederateObject::SP federateObjectSP2 = boost::dynamic_pointer_cast<FederateObject>(objectRootSP1);
    CPPUNIT_ASSERT(federateObjectSP2);

    // INITIALLY, SECOND INSTANCE SHOULD HAVE DEFAULT VALUES
std::cout << 4 << std::endl;
    FederateObject &federateObject2 = *federateObjectSP2;
    CPPUNIT_ASSERT_EQUAL(0, federateObject2.get_FederateHandle());
    CPPUNIT_ASSERT_EQUAL(std::string(""), federateObject2.get_FederateHost());
    CPPUNIT_ASSERT_EQUAL(std::string(""), federateObject2.get_FederateType());

    // SEND OUT ATTRIBUTE VALUES OF FIRST INSTANCE TO MOCK RTI
std::cout << 4.5 << std::endl;
    federateObject1.updateAttributeValues(get_rti_ambassador_1_ptr(), 5.0);

    // CHECK MOCK RTI VALUES
std::cout << 5 << std::endl;
    RTIfedTime *currentRTIFedTimeImplPtr = get_rti_ambassador_test_1().getCurrentRTIFedTimeImplPtr();
    CPPUNIT_ASSERT(currentRTIFedTimeImplPtr);
    RTIfedTime &currentRTIFedTimeImpl1 = *currentRTIFedTimeImplPtr;
    CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0, currentRTIFedTimeImpl1.getTime(), 0.1);

    // ALL VALUES SHOULD BE UPDATED (3)
    RTI::AttributeHandleValuePairSet &currentAttributeHandleValuePairSet1 =
      get_rti_ambassador_test_1().getCurrentAttributeHandleValuePairSet();
    CPPUNIT_ASSERT_EQUAL(static_cast<RTI::ULong>(3), currentAttributeHandleValuePairSet1.size());

    // REFLECT UPDATED ATTRIBUTE VALUES TO SECOND INSTANCE
    FederateObject::reflect(
      get_rti_ambassador_test_1().getCurrentObjectHandle(), currentAttributeHandleValuePairSet1, currentRTIFedTimeImpl1
    );
    CPPUNIT_ASSERT_EQUAL(2, federateObject2.get_FederateHandle());
    CPPUNIT_ASSERT_EQUAL(std::string("localhost"), federateObject2.get_FederateHost());
    CPPUNIT_ASSERT_EQUAL(std::string("test"), federateObject2.get_FederateType());

    // CHANGE ONLY ONE VALUE IN FIRST INSTANCE AND SEND OUT UPDATE TO MOCK RTI
    federateObject1.set_FederateType("foobar");
    federateObject1.updateAttributeValues(get_rti_ambassador_1_ptr(), 6.0);

    // CHECK MOCK RTI VALUES
    currentRTIFedTimeImplPtr = get_rti_ambassador_test_1().getCurrentRTIFedTimeImplPtr();
    CPPUNIT_ASSERT(currentRTIFedTimeImplPtr);
    RTIfedTime &currentRTIFedTimeImpl2 = *currentRTIFedTimeImplPtr;
    CPPUNIT_ASSERT_DOUBLES_EQUAL(6.0, currentRTIFedTimeImpl2.getTime(), 0.1);

    // ONLY ONE VALUE SHOULD BE UPDATED SINCE ONLY ONE WAS CHANGED
    RTI::AttributeHandleValuePairSet &currentAttributeHandleValuePairSet2 =
      get_rti_ambassador_test_1().getCurrentAttributeHandleValuePairSet();
    CPPUNIT_ASSERT_EQUAL(static_cast<RTI::ULong>(1), currentAttributeHandleValuePairSet2.size());

    // REFLECT CHANGED ATTRIBUTE INTO SECOND INSTANCE, CHECK VALUES
    FederateObject::reflect(
      get_rti_ambassador_test_1().getCurrentObjectHandle(), currentAttributeHandleValuePairSet2, currentRTIFedTimeImpl2
    );
    CPPUNIT_ASSERT_EQUAL(2, federateObject2.get_FederateHandle());
    CPPUNIT_ASSERT_EQUAL(std::string("localhost"), federateObject2.get_FederateHost());
    CPPUNIT_ASSERT_EQUAL(std::string("foobar"), federateObject2.get_FederateType());
}

CPPUNIT_TEST_SUITE_REGISTRATION( ObjectTests );
