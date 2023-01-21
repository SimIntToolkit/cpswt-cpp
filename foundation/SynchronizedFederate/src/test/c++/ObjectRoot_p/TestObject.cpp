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

#include "ObjectRoot_p/TestObject.hpp"
namespace edu {
 namespace vanderbilt {
  namespace vuisis {
   namespace cpswt {
    namespace hla {
     namespace ObjectRoot_p {

bool TestObject::static_init_var = TestObject::static_init();

bool TestObject::static_init() {
    BOOST_LOG_SEV(get_logger(), info) << "Class \"::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject\" loaded.";

    // ADD THIS CLASS TO THE _classNameSet DEFINED IN ObjectRoot
    get_hla_class_name_set().insert(get_hla_class_name());

    ObjectRoot::NoInstanceInit noInstanceInit;
    SP instanceSP = SP( new TestObject(noInstanceInit) );
    get_hla_class_name_instance_sp_map()[get_hla_class_name()] = instanceSP;

    ClassAndPropertyNameSetSP classAndPropertyNameSetSP( new ClassAndPropertyNameSet() );
    classAndPropertyNameSetSP->emplace(
        "ObjectRoot.TestObject", "BooleanValue1"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "ObjectRoot.TestObject", "BooleanValue1" )] =
      ValueSP( new Value( false ));
    classAndPropertyNameSetSP->emplace(
        "ObjectRoot.TestObject", "BooleanValue2"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "ObjectRoot.TestObject", "BooleanValue2" )] =
      ValueSP( new Value( false ));
    classAndPropertyNameSetSP->emplace(
        "ObjectRoot.TestObject", "ByteValue"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "ObjectRoot.TestObject", "ByteValue" )] =
      ValueSP( new Value( static_cast<char>(0) ));
    classAndPropertyNameSetSP->emplace(
        "ObjectRoot.TestObject", "CharValue"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "ObjectRoot.TestObject", "CharValue" )] =
      ValueSP( new Value( static_cast<char>(0) ));
    classAndPropertyNameSetSP->emplace(
        "ObjectRoot.TestObject", "DoubleValue"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "ObjectRoot.TestObject", "DoubleValue" )] =
      ValueSP( new Value( static_cast<double>(0) ));
    classAndPropertyNameSetSP->emplace(
        "ObjectRoot.TestObject", "FloatValue"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "ObjectRoot.TestObject", "FloatValue" )] =
      ValueSP( new Value( static_cast<bool>(0) ));
    classAndPropertyNameSetSP->emplace(
        "ObjectRoot.TestObject", "IntValue"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "ObjectRoot.TestObject", "IntValue" )] =
      ValueSP( new Value( static_cast<int>(0) ));
    classAndPropertyNameSetSP->emplace(
        "ObjectRoot.TestObject", "LongValue"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "ObjectRoot.TestObject", "LongValue" )] =
      ValueSP( new Value( static_cast<long>(0) ));
    classAndPropertyNameSetSP->emplace(
        "ObjectRoot.TestObject", "ShortValue"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "ObjectRoot.TestObject", "ShortValue" )] =
      ValueSP( new Value( static_cast<short>(0) ));
    classAndPropertyNameSetSP->emplace(
        "ObjectRoot.TestObject", "StringValue"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "ObjectRoot.TestObject", "StringValue" )] =
      ValueSP( new Value( std::string("") ));

    // ADD THIS CLASS'S _classAndPropertyNameSet TO _classNamePropertyNameSetMap DEFINED
    // IN ObjectRoot
    get_class_name_class_and_property_name_set_sp_map()[get_hla_class_name()] = classAndPropertyNameSetSP;

    ClassAndPropertyNameSetSP allClassAndPropertyNameSetSP( new ClassAndPropertyNameSet() );

    allClassAndPropertyNameSetSP->emplace(
        "ObjectRoot.TestObject", "BooleanValue1"
    );

    allClassAndPropertyNameSetSP->emplace(
        "ObjectRoot.TestObject", "BooleanValue2"
    );

    allClassAndPropertyNameSetSP->emplace(
        "ObjectRoot.TestObject", "ByteValue"
    );

    allClassAndPropertyNameSetSP->emplace(
        "ObjectRoot.TestObject", "CharValue"
    );

    allClassAndPropertyNameSetSP->emplace(
        "ObjectRoot.TestObject", "DoubleValue"
    );

    allClassAndPropertyNameSetSP->emplace(
        "ObjectRoot.TestObject", "FloatValue"
    );

    allClassAndPropertyNameSetSP->emplace(
        "ObjectRoot.TestObject", "IntValue"
    );

    allClassAndPropertyNameSetSP->emplace(
        "ObjectRoot.TestObject", "LongValue"
    );

    allClassAndPropertyNameSetSP->emplace(
        "ObjectRoot.TestObject", "ShortValue"
    );

    allClassAndPropertyNameSetSP->emplace(
        "ObjectRoot.TestObject", "StringValue"
    );// ADD THIS CLASS'S _allClassAndPropertyNameSet TO _classNameAllPropertyNameSetMap DEFINED
    // IN ObjectRoot
    get_class_name_all_class_and_property_name_set_sp_map()[get_hla_class_name()] = allClassAndPropertyNameSetSP;

    return true;
}

     } // NAMESPACE "ObjectRoot_p"
    } // NAMESPACE "hla"
   } // NAMESPACE "cpswt"
  } // NAMESPACE "vuisis"
 } // NAMESPACE "vanderbilt"
} // NAMESPACE "edu"
