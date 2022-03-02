#ifndef _INTERACTION_TESTS
#define _INTERACTION_TESTS

#define BOOST_LOG_DYN_LINK

#include "RTIAmbassadorTest1.hh"

#include <cppunit/extensions/HelperMacros.h>

#include <boost/log/core.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;

class InteractionTests: public CppUnit::TestCase {

public:
    typedef sinks::synchronous_sink< sinks::text_ostream_backend > text_sink;

private:
    static RTI::RTIambassador *get_rti_ambassador_1_ptr();

    static bool &get_is_initialized() {
        static bool isInitialized = false;
        return isInitialized;
    }

    static void init_1();

    static bool null_filter(const logging::attribute_value_set &attrs) {
        return false;
    }

    // nullSink IS MEANT TO DISPOSE OF DEFAULT SINK, SO DEFAULT LOGGING BEHAVIOR IS ESSENTIALLY NO SINK.
    boost::shared_ptr< text_sink > nullSink;

    CPPUNIT_TEST_SUITE( InteractionTests );
    CPPUNIT_TEST(messagingNamesTest);
    CPPUNIT_TEST(classHandleTest);
    CPPUNIT_TEST(parameterNamesTest);
    CPPUNIT_TEST(propertyHandleTest);
    CPPUNIT_TEST(basicLogTest);
    CPPUNIT_TEST(dynamicMessagingTest);
    CPPUNIT_TEST_SUITE_END();

public:

    InteractionTests() : CppUnit::TestCase() {
        init_1();
        nullSink = boost::make_shared< text_sink >();
        nullSink->set_filter(&null_filter);
        logging::core::get()->add_sink(nullSink);
    }

    void messagingNamesTest();
    void classHandleTest();
    void parameterNamesTest();
    void propertyHandleTest();
    void basicLogTest();
    void dynamicMessagingTest();
};

#endif // _INTERACTION_TESTS
