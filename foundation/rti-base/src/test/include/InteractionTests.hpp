#ifndef _INTERACTION_TESTS
#define _INTERACTION_TESTS

#define BOOST_LOG_DYN_LINK

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
    CPPUNIT_TEST_SUITE_END();

public:

    InteractionTests() : CppUnit::TestCase() {
        nullSink = boost::make_shared< text_sink >();
        nullSink->set_filter(&null_filter);
        logging::core::get()->add_sink(nullSink);
    }

    void messagingNamesTest();
    void classHandleTest();
    void parameterNamesTest();
    void propertyHandleTest();
    void basicLogTest();
};

#endif // _INTERACTION_TESTS
