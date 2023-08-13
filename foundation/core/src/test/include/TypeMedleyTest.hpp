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
    CPPUNIT_TEST(jsonTest);
    CPPUNIT_TEST_SUITE_END();

    static void compareStringLists(const std::list<std::string> &list1, const std::list<std::string> &list2);
    static void compareStringListRegex(
      const std::list<std::string> &stringList, const std::list<std::regex> &regexList
    );

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
    void jsonTest();
};

#endif // _TYPEMEDLEY_TEST
