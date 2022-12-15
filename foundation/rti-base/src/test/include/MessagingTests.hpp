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

#ifndef _MESSAGING_TESTS
#define _MESSAGING_TESTS

#define BOOST_LOG_DYN_LINK

#include "RTIAmbassadorTest1.hpp"

#include <cppunit/extensions/HelperMacros.h>

#include <boost/log/core.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;

class MessagingTests: public CppUnit::TestCase {

public:
    typedef sinks::synchronous_sink< sinks::text_ostream_backend > text_sink;

private:
    static bool null_filter(const logging::attribute_value_set &attrs) {
        return false;
    }

    // nullSink IS MEANT TO DISPOSE OF DEFAULT SINK, SO DEFAULT LOGGING BEHAVIOR IS ESSENTIALLY NO SINK.
    boost::shared_ptr< text_sink > nullSink;

    CPPUNIT_TEST_SUITE( MessagingTests );
    CPPUNIT_TEST(interactionClassNamesTest);
    CPPUNIT_TEST(objectClassNamesTest);
    CPPUNIT_TEST(interactionClassHandleTest);
    CPPUNIT_TEST(objectClassHandleTest);
    CPPUNIT_TEST(interactionParameterNamesTest);
    CPPUNIT_TEST(objectAttributeNamesTest);
    CPPUNIT_TEST(interactionParameterHandleTest);
    CPPUNIT_TEST(objectAttributeHandleTest);
    CPPUNIT_TEST(basicLogTest);
    CPPUNIT_TEST(dynamicMessagingTest);
    CPPUNIT_TEST(valueTest);
    CPPUNIT_TEST(messagingInstanceHlaClassTest);
    CPPUNIT_TEST(federateSequenceTest);
    CPPUNIT_TEST(attributePubSubTest);
    CPPUNIT_TEST(printInteractionTest);
    CPPUNIT_TEST(rejectSourceFederateIdTest);
    CPPUNIT_TEST_SUITE_END();

public:
    MessagingTests();

    void setUp() override;

    void interactionClassNamesTest();
    void objectClassNamesTest();
    void interactionClassHandleTest();
    void objectClassHandleTest();
    void interactionParameterNamesTest();
    void objectAttributeNamesTest();
    void interactionParameterHandleTest();
    void objectAttributeHandleTest();
    void basicLogTest();
    void dynamicMessagingTest();
    void valueTest();
    void messagingInstanceHlaClassTest();
    void federateSequenceTest();
    void attributePubSubTest();
    void printInteractionTest();
    void rejectSourceFederateIdTest();
};

#endif // _MESSAGING_TESTS
