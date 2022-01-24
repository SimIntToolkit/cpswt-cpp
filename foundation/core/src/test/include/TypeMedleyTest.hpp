//
// Created by vagrant on 12/22/21.
//

#ifndef _TYPEMEDLEY_TEST
#define _TYPEMEDLEY_TEST

#include <cppunit/extensions/HelperMacros.h>
#include "TypeMedley.hpp"

class TypeMedleyTest: public CppUnit::TestCase {

    CPPUNIT_TEST_SUITE( TypeMedleyTest );
    CPPUNIT_TEST(boolTrueTest);
    CPPUNIT_TEST(boolFalseTest);
    CPPUNIT_TEST(charTest);
    CPPUNIT_TEST(charZeroTest);
    CPPUNIT_TEST(zeroCharTest);
    CPPUNIT_TEST(floatWithExponentTest);
    CPPUNIT_TEST(intZeroTest);
    CPPUNIT_TEST(floatTest);
    CPPUNIT_TEST(zeroStringTest);
    CPPUNIT_TEST(stringFloatWithExponentTest);
    CPPUNIT_TEST(stringTest);
    CPPUNIT_TEST_SUITE_END();

public:
    TypeMedleyTest() : CppUnit::TestCase() {}

    void boolTrueTest();
    void boolFalseTest();
    void charTest();
    void charZeroTest();
    void zeroCharTest();
    void intZeroTest();
    void floatTest();
    void floatWithExponentTest();
    void zeroStringTest();
    void stringFloatWithExponentTest();
    void stringTest();
};

#endif // _TYPEMEDLEY_TEST
