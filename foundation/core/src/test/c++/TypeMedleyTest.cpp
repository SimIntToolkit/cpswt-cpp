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

#include "TypeMedleyTest.hpp"
#include <iostream>

void TypeMedleyTest::compareStringLists(const std::list<std::string> &list1, const std::list<std::string> &list2) {

    CPPUNIT_ASSERT_EQUAL(list1.size(), list2.size());
    std::list<std::string>::const_iterator stlCit1 = list1.begin();
    std::list<std::string>::const_iterator stlCit2 = list2.begin();
    while(stlCit1 != list1.end()) {
        CPPUNIT_ASSERT_EQUAL(*stlCit1, *stlCit2);
        ++stlCit1;
        ++stlCit2;
    }
}
void TypeMedleyTest::compareStringListRegex(
  const std::list<std::string> &stringList, const std::list<std::regex> &regexList
) {

    CPPUNIT_ASSERT_EQUAL(stringList.size(), regexList.size());
    std::list<std::string>::const_iterator stlCit = stringList.begin();
    std::list<std::regex>::const_iterator rglCit = regexList.begin();
    while(stlCit != stringList.end()) {
        CPPUNIT_ASSERT(std::regex_match(*stlCit, *rglCit));
        ++stlCit;
        ++rglCit;
    }
}


void TypeMedleyTest::boolTrueTest() {
    TypeMedley typeMedley(true);
    CPPUNIT_ASSERT(typeMedley.getDataType() == TypeMedley::BOOLEAN);

    const auto boolValue = static_cast<bool>(typeMedley);
    CPPUNIT_ASSERT(boolValue);

    const auto charValue = static_cast<char>(typeMedley);
    CPPUNIT_ASSERT_EQUAL('\1', charValue);

    const auto shortValue = static_cast<short>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<short>(1), shortValue);

    const auto intValue = static_cast<int>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<int>(1), intValue);

    const auto longValue = static_cast<long>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<long>(1), longValue);

    const auto floatValue = static_cast<float>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<float>(1), floatValue, 0.001);

    const auto doubleValue = static_cast<double>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<double>(1), doubleValue, 0.001);

    const auto stringValue = static_cast<std::string>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(std::string("true"), stringValue);

    const auto stringListValue = typeMedley.asStringList();
    compareStringLists(std::list<std::string> { std::string("true") }, stringListValue);
}

void TypeMedleyTest::boolFalseTest() {
    TypeMedley typeMedley(false);
    CPPUNIT_ASSERT(typeMedley.getDataType() == TypeMedley::BOOLEAN);

    const auto boolValue = static_cast<bool>(typeMedley);
    CPPUNIT_ASSERT(!boolValue);

    const auto charValue = static_cast<char>(typeMedley);
    CPPUNIT_ASSERT_EQUAL('\0', charValue);

    const auto shortValue = static_cast<short>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<short>(0), shortValue);

    const auto intValue = static_cast<int>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<int>(0), intValue);

    const auto longValue = static_cast<long>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<long>(0), longValue);

    const auto floatValue = static_cast<float>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<float>(0), floatValue, 0.001);

    const auto doubleValue = static_cast<double>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<double>(0), doubleValue, 0.001);

    const auto stringValue = static_cast<std::string>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(std::string("false"), stringValue);

    const auto stringListValue = typeMedley.asStringList();
    compareStringLists(std::list<std::string> { std::string("false") }, stringListValue);
}

void TypeMedleyTest::charTest() {
    TypeMedley typeMedley('3');
    CPPUNIT_ASSERT(typeMedley.getDataType() == TypeMedley::CHARACTER);

    const auto boolValue = static_cast<bool>(typeMedley);
    CPPUNIT_ASSERT(boolValue);

    const auto charValue = static_cast<char>(typeMedley);
    CPPUNIT_ASSERT_EQUAL('3', charValue);

    const auto shortValue = static_cast<short>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<short>('3'), shortValue);

    const auto intValue = static_cast<int>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<int>('3'), intValue);

    const auto longValue = static_cast<long>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<long>('3'), longValue);

    const auto floatValue = static_cast<float>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<float>('3'), floatValue, 0.001);

    const auto doubleValue = static_cast<double>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<double>('3'), doubleValue, 0.001);

    const auto stringValue = static_cast<std::string>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(std::string("3"), stringValue);

    const auto stringListValue = typeMedley.asStringList();
    compareStringLists(std::list<std::string> { std::string("3") }, stringListValue);
}

void TypeMedleyTest::charZeroTest() {
    TypeMedley typeMedley('\0');
    CPPUNIT_ASSERT(typeMedley.getDataType() == TypeMedley::CHARACTER);

    const auto boolValue = static_cast<bool>(typeMedley);
    CPPUNIT_ASSERT(!boolValue);

    const auto charValue = static_cast<char>(typeMedley);
    CPPUNIT_ASSERT_EQUAL('\0', charValue);

    const auto shortValue = static_cast<short>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<short>(0), shortValue);

    const auto intValue = static_cast<int>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<int>(0), intValue);

    const auto longValue = static_cast<long>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<long>(0), longValue);

    const auto floatValue = static_cast<float>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<float>(0), floatValue, 0.001);

    const auto doubleValue = static_cast<double>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<double>(0), doubleValue, 0.001);

    const auto stringValue = static_cast<std::string>(typeMedley);
    char localValue = '\0';
    CPPUNIT_ASSERT_EQUAL(std::string(&localValue, 1), stringValue);

    const auto stringListValue = typeMedley.asStringList();
    compareStringLists(std::list<std::string> { std::string(&localValue, 1) }, stringListValue);
}

void TypeMedleyTest::zeroCharTest() {
    TypeMedley typeMedley('0');
    CPPUNIT_ASSERT(typeMedley.getDataType() == TypeMedley::CHARACTER);

    const auto boolValue = static_cast<bool>(typeMedley);
    CPPUNIT_ASSERT(boolValue);

    const auto charValue = static_cast<char>(typeMedley);
    CPPUNIT_ASSERT_EQUAL('0', charValue);

    const auto shortValue = static_cast<short>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<short>('0'), shortValue);

    const auto intValue = static_cast<int>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<int>('0'), intValue);

    const auto longValue = static_cast<long>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<long>('0'), longValue);

    const auto floatValue = static_cast<float>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<float>('0'), floatValue, 0.001);

    const auto doubleValue = static_cast<double>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<double>('0'), doubleValue, 0.001);

    const auto stringValue = static_cast<std::string>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(std::string("0"), stringValue);

    const auto stringListValue = typeMedley.asStringList();
    compareStringLists(std::list<std::string> { std::string("0") }, stringListValue);
}

void TypeMedleyTest::intZeroTest() {
    TypeMedley typeMedley(0);
    CPPUNIT_ASSERT(typeMedley.getDataType() == TypeMedley::INTEGER);

    const auto boolValue = static_cast<bool>(typeMedley);
    CPPUNIT_ASSERT(!boolValue);

    const auto charValue = static_cast<char>(typeMedley);
    CPPUNIT_ASSERT_EQUAL('\0', charValue);

    const auto shortValue = static_cast<short>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<short>(0), shortValue);

    const auto intValue = static_cast<int>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<int>(0), intValue);

    const auto longValue = static_cast<long>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<long>(0), longValue);

    const auto floatValue = static_cast<float>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<float>(0), floatValue, 0.001);

    const auto doubleValue = static_cast<double>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<double>(0), doubleValue, 0.001);

    const auto stringValue = static_cast<std::string>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(std::string("0"), stringValue);

    const auto stringListValue = typeMedley.asStringList();
    compareStringLists(std::list<std::string> { std::string("0") }, stringListValue);
}

void TypeMedleyTest::floatTest() {
    TypeMedley typeMedley(static_cast<float>(-53.231));
    CPPUNIT_ASSERT(typeMedley.getDataType() == TypeMedley::FLOAT);

    const auto boolValue = static_cast<bool>(typeMedley);
    CPPUNIT_ASSERT(boolValue);

    const auto charValue = static_cast<char>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<char>(-53), charValue);

    const auto shortValue = static_cast<short>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<short>(-53), shortValue);

    const auto intValue = static_cast<int>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<int>(-53), intValue);

    const auto longValue = static_cast<long>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<long>(-53), longValue);

    const auto floatValue = static_cast<float>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<float>(-53.231), floatValue, 0.001);

    const auto doubleValue = static_cast<double>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<double>(-53.231), doubleValue, 0.001);

    std::regex regex1("-53\\.23[0-9]*");
    const auto stringValue = static_cast<std::string>(typeMedley);

    CPPUNIT_ASSERT(std::regex_match(stringValue, regex1));

    const auto stringListValue = typeMedley.asStringList();
    compareStringListRegex(std::list<std::string> { stringValue }, std::list<std::regex> { regex1 });
}

void TypeMedleyTest::floatWithExponentTest() {
    TypeMedley typeMedley(static_cast<float>(53.231e-01));
    CPPUNIT_ASSERT(typeMedley.getDataType() == TypeMedley::FLOAT);

    const auto boolValue = static_cast<bool>(typeMedley);
    CPPUNIT_ASSERT(boolValue);

    const auto charValue = static_cast<char>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<char>(5), charValue);

    const auto shortValue = static_cast<short>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<short>(5), shortValue);

    const auto intValue = static_cast<int>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<int>(5), intValue);

    const auto longValue = static_cast<long>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<long>(5), longValue);

    const auto floatValue = static_cast<float>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<float>(5.3231), floatValue, 0.001);

    const auto doubleValue = static_cast<double>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<double>(5.3231), doubleValue, 0.001);

    std::regex regex1("5\\.323[0-9]*");
    const auto stringValue = static_cast<std::string>(typeMedley);

    CPPUNIT_ASSERT(std::regex_match(stringValue, regex1));

    const auto stringListValue = typeMedley.asStringList();
    compareStringListRegex(std::list<std::string> { stringValue }, std::list<std::regex> { regex1 });
}


void TypeMedleyTest::zeroStringTest() {
    TypeMedley typeMedley(std::string("0"));
    CPPUNIT_ASSERT(typeMedley.getDataType() == TypeMedley::STRING);

    const auto boolValue = static_cast<bool>(typeMedley);
    CPPUNIT_ASSERT(!boolValue);

    const auto charValue = static_cast<char>(typeMedley);
    CPPUNIT_ASSERT_EQUAL('\0', charValue);

    const auto shortValue = static_cast<short>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<short>(0), shortValue);

    const auto intValue = static_cast<int>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<int>(0), intValue);

    const auto longValue = static_cast<long>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<long>(0), longValue);

    const auto floatValue = static_cast<float>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<float>(0), floatValue, 0.001);

    const auto doubleValue = static_cast<double>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<double>(0), doubleValue, 0.001);

    const auto stringValue = static_cast<std::string>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(std::string("0"), stringValue);

    const auto stringListValue = typeMedley.asStringList();
    compareStringLists(std::list<std::string> { std::string("0") }, stringListValue);
}

void TypeMedleyTest::stringFloatWithExponentTest() {
    TypeMedley typeMedley(std::string("53.231e-01"));
    CPPUNIT_ASSERT(typeMedley.getDataType() == TypeMedley::STRING);

    const auto boolValue = static_cast<bool>(typeMedley);
    CPPUNIT_ASSERT(boolValue);

    const auto charValue = static_cast<char>(typeMedley);
    CPPUNIT_ASSERT_EQUAL('\5', charValue);

    const auto shortValue = static_cast<short>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<short>(5), shortValue);

    const auto intValue = static_cast<int>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<int>(5), intValue);

    const auto longValue = static_cast<long>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<long>(5), longValue);

    const auto floatValue = static_cast<float>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<float>(5.3231), floatValue, 0.001);

    const auto doubleValue = static_cast<double>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<double>(5.3231), doubleValue, 0.001);

    const auto stringValue = static_cast<std::string>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(std::string("53.231e-01"), stringValue);

    const auto stringListValue = typeMedley.asStringList();
    compareStringLists(std::list<std::string> { std::string("53.231e-01") }, stringListValue);
}

void TypeMedleyTest::stringTest() {
    TypeMedley typeMedley(std::string("00ABCD"));
    CPPUNIT_ASSERT(typeMedley.getDataType() == TypeMedley::STRING);

    const auto boolValue = static_cast<bool>(typeMedley);
    CPPUNIT_ASSERT(!boolValue);

    const auto charValue = static_cast<char>(typeMedley);
    CPPUNIT_ASSERT_EQUAL('0', charValue);

    const auto shortValue = static_cast<short>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<short>('0'), shortValue);

    const auto intValue = static_cast<int>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<int>('0'), intValue);

    const auto longValue = static_cast<long>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<long>('0'), longValue);

    const auto floatValue = static_cast<float>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<float>('0'), floatValue, 0.001);

    const auto doubleValue = static_cast<double>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<double>('0'), doubleValue, 0.001);

    const auto stringValue = static_cast<std::string>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(std::string("00ABCD"), stringValue);

    const auto stringListValue = typeMedley.asStringList();
    compareStringLists(std::list<std::string> { std::string("00ABCD") }, stringListValue);
}

void TypeMedleyTest::stringListTest() {
    std::list<std::string> stringList { "this", "that", "other" };

    TypeMedley typeMedley(stringList);
    CPPUNIT_ASSERT(typeMedley.getDataType() == TypeMedley::STRINGLIST);

    const auto boolValue1 = static_cast<bool>(typeMedley);
    CPPUNIT_ASSERT(boolValue1);

    const auto boolValue2 = static_cast<bool>(TypeMedley(std::list<std::string>()));
    CPPUNIT_ASSERT(!boolValue2);

    const auto charValue = static_cast<char>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<char>(3), charValue);

    const auto shortValue = static_cast<short>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<short>(3), shortValue);

    const auto intValue = static_cast<int>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<int>(3), intValue);

    const auto longValue = static_cast<long>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(static_cast<long>(3), longValue);

    const auto floatValue = static_cast<float>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<float>(3), floatValue, 0.001);

    const auto doubleValue = static_cast<double>(typeMedley);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(static_cast<double>(3), doubleValue, 0.001);

    const auto stringValue = static_cast<std::string>(typeMedley);
    CPPUNIT_ASSERT_EQUAL(std::string("[ \"this\", \"that\", \"other\" ]"), stringValue);

    const auto stringListValue = typeMedley.asStringList();
    compareStringLists(stringList, stringListValue);
}

CPPUNIT_TEST_SUITE_REGISTRATION( TypeMedleyTest );
