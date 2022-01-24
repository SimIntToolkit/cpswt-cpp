#ifndef _INTERACTION_TESTS
#define _INTERACTION_TESTS

#include <cppunit/extensions/HelperMacros.h>

class InteractionTests: public CppUnit::TestCase {

    CPPUNIT_TEST_SUITE( InteractionTests );
    CPPUNIT_TEST(messagingNamesTest);
    CPPUNIT_TEST(classHandleTest);
    CPPUNIT_TEST(parameterNamesTest);
    CPPUNIT_TEST_SUITE_END();

public:
    InteractionTests() : CppUnit::TestCase() {}

    void messagingNamesTest();
    void classHandleTest();
    void parameterNamesTest();
};

#endif // _INTERACTION_TESTS
