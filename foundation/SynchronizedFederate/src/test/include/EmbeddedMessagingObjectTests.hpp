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

#ifndef _EMBEDDEDMESSAGINGOBJECT_TESTS
#define _EMBEDDEDMESSAGINGOBJECT_TESTS

#define BOOST_LOG_DYN_LINK

#include "RTIAmbassadorTest2.hpp"

#include <cppunit/extensions/HelperMacros.h>

#include <boost/log/core.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/shared_ptr.hpp>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;

class EmbeddedMessagingObjectTests: public CppUnit::TestCase {
private:
    void compareStringLists(const std::list<std::string> &list1, const std::list<std::string> &list2);
    bool stringListsNotEqual(const std::list<std::string> &list1, const std::list<std::string> &list2);

public:
    typedef sinks::synchronous_sink< sinks::text_ostream_backend > text_sink;

    static bool null_filter(const logging::attribute_value_set &attrs) {
        return false;
    }

    // nullSink IS MEANT TO DISPOSE OF DEFAULT SINK, SO DEFAULT LOGGING BEHAVIOR IS ESSENTIALLY NO SINK.
    boost::shared_ptr< text_sink > nullSink;

    typedef boost::shared_ptr<FederateConfig> FederateConfigSP;
    FederateConfigSP getNewFederateConfigSP(const std::string &federateName) {

        FederateConfigSP federateConfigSP(new FederateConfig());

        FederateConfig &federateConfig = *federateConfigSP;
        federateConfig.federateType = federateName;
        federateConfig.federationId = "testOjbectNetworkPropagation";
        federateConfig.isLateJoiner = false;
        federateConfig.lookahead = 0.1;
        federateConfig.stepSize = 1.0;

        return federateConfigSP;
    }

private:
    CPPUNIT_TEST_SUITE( EmbeddedMessagingObjectTests );
    CPPUNIT_TEST(testObjectNetworkPropagation);
    CPPUNIT_TEST_SUITE_END();

public:
    void testObjectNetworkPropagation();
};

#endif // _EMBEDDEDMESSAGINGOBJECT_TESTS