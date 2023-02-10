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

#ifndef _edu_vanderbilt_vuisis_cpswt_hla_ObjectRoot_p_TestObject_CLASS
#define _edu_vanderbilt_vuisis_cpswt_hla_ObjectRoot_p_TestObject_CLASS

#include "ObjectRoot.hpp"
#include "C2WException.hpp"

#include <boost/unordered_set.hpp>


namespace edu {
 namespace vanderbilt {
  namespace vuisis {
   namespace cpswt {
    namespace hla {
     namespace ObjectRoot_p {

class TestObject : public ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot {
public:
//    using ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot;
    typedef ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot Super;
    typedef boost::shared_ptr< TestObject > SP;

private:
    static severity_logger &get_logger_aux() {
        static severity_logger logger;
        logger.add_attribute("MessagingClassName", attrs::constant< std::string >(
          "ObjectRoot.TestObject"
        ));

        logging::add_common_attributes();
        return logger;
    }

public:
    static severity_logger &get_logger() {
        static severity_logger &logger = get_logger_aux();
        return logger;
    }

    // ----------------------------------------------------------------------------
    // STATIC PROPERTIES AND CODE THAT DEAL WITH NAMES
    // THIS CODE IS STATIC BECAUSE IT IS CLASS-DEPENDENT AND NOT INSTANCE-DEPENDENT
    // ----------------------------------------------------------------------------

    /**
     * Returns the fully-qualified (dot-delimited) name of the ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject object class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the name of the class pertaining to the reference,
     * rather than the name of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getJavaClassName()}.
     *
     * @return the fully-qualified Java class name for this object class
     */
    static const std::string &get_cpp_class_name() {
        static const std::string cppClassName("::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject");
        return cppClassName;
    }

    /**
     * Returns the fully-qualified (dot-delimited) name of this instance's object class.
     * Polymorphic equivalent of get_java_class_name static method.
     *
     * @return the fully-qualified (dot-delimited) name of this instance's object class
     */
    const std::string &getCppClassName() const override {
        return get_cpp_class_name();
    }

    /**
     * Returns the simple name (the last name in the dot-delimited fully-qualified
     * class name) of the edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.TestObject object class.
     *
     * @return the name of this object class
     */
    static const std::string get_simple_class_name() {
        return ObjectRoot::get_simple_class_name(get_hla_class_name());
    }

    /**
     * Returns the fully-qualified (dot-delimited) hla class name of the
     * ObjectRoot.TestObject object class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the federation name of the class pertaining to the reference,
     * rather than the name of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getHlaClassName()}.
     *
     * @return the fully-qualified federation (HLA) class name for this object class
     */
    static const std::string &get_hla_class_name() {
        static const std::string hlaClassName("ObjectRoot.TestObject");
        return hlaClassName;
    }

    /**
     * Returns the fully-qualified (dot-delimited) hla class name of this instance's object class.
     * Polymorphic equivalent of get_hla_class_name static method.
     *
     * @return the fully-qualified (dot-delimited) name of this instance's object class
     */
    const std::string &getHlaClassName() const override {
        return get_hla_class_name();
    }

    /**
     * Returns a sorted list containing the names of all of the non-hidden attributes in the
     * edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.TestObject object class.
     * The property names are paired with name of the hla class in which they are defined in a
     * ClassAndPropertyName POJO.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return a set of class-and0parameter names pertaining to the reference,
     * rather than the parameter names of the class for the instance referred to by
     * the reference.  For the polymorphic version of this method, use
     * {@link #getAttributeNames()}.
     *
     * @return a sorted list of the non-hidden attribute names for this object class
     * paired with name of the hla class in which they are defined in a ClassAndPropertyName POJO.
     */
    static ClassAndPropertyNameList get_attribute_names() {
        return ObjectRoot::get_attribute_names( get_hla_class_name() );
    }

    /**
     * Returns a sorted list containing the names of all of the attributes in the
     * edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.TestObject object class.
     * The property names are paired with name of the hla class in which they are defined in a
     * ClassAndPropertyName POJO.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return a set of parameter names pertaining to the reference,
     * rather than the parameter names of the class for the instance referred to by
     * the reference.  For the polymorphic version of this method, use
     * {@link #getAttributeNames()}.
     *
     * @return a sorted list of the attribute names for this object class
     * paired with name of the hla class in which they are defined in a ClassAndPropertyName POJO.
     */
    static ClassAndPropertyNameList get_all_attribute_names() {
        return ObjectRoot::get_all_attribute_names( get_hla_class_name() );
    }

    /*
     * INITIALIZE STATIC PROPERTYS THAT DEAL WITH NAMES
     */
    static bool static_init();
    static bool static_init_var;

    // --------------------------------------------------------
    // END OF STATIC PROPERTYS AND CODE THAT DEAL WITH NAMES.
    // --------------------------------------------------------


    // ----------------------------------------------------------------------------
    // STATIC PROPERTYS AND CODE THAT DEAL WITH HANDLES.
    // THIS CODE IS STATIC BECAUSE IT IS CLASS-DEPENDENT AND NOT INSTANCE-DEPENDENT
    // ----------------------------------------------------------------------------
    /**
     * Returns the handle (RTI assigned) of the edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.TestObject object class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the handle of the class pertaining to the reference,
     * rather than the handle of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getClassHandle()}.
     *
     * @return the RTI assigned integer handle that represents this object class
     */
    static int get_class_handle() {
        return get_class_name_handle_map()[get_hla_class_name()];
    }

    /**
     * Returns the handle of an attribute (RTI assigned) of
     * this object class (i.e. "edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.TestObject") given the attribute's name.
     *
     * @param propertyName name of attribute
     * @return the handle (RTI assigned) of the attribute "propertyName" of object class "hlaClassName"
     */
    static int get_attribute_handle(const std::string &propertyName) {
        return ObjectRoot::get_attribute_handle(get_hla_class_name(), propertyName);
    }

    static AttributeHandleSetSP get_published_attribute_handle_set_sp() {
        return ObjectRoot::get_published_attribute_handle_set_sp( get_hla_class_name() );
    }

    /**
     * Returns a data structure containing the handles of all attributes for this object
     * class that are currently marked for subscription.  To actually subscribe to these
     * attributes, a federate must call &lt;objectclassname&gt;.subscribe( RTIambassador rti ).
     *
     * @return data structure containing the handles of all attributes for this object
     * class that are currently marked for subscription
     */
    static AttributeHandleSetSP get_subscribed_attribute_handle_set_sp() {
        return ObjectRoot::get_subscribed_attribute_handle_set_sp( get_hla_class_name() );
    }

    // ----------------------------------------------------------
    // END OF STATIC PROPERTYS AND CODE THAT DEAL WITH HANDLES.
    // ----------------------------------------------------------


    //-------------------------------------------------
    // METHODS FOR PUBLISHING/SUBSCRIBING-TO THIS CLASS
    //-------------------------------------------------

    /**
     * Publishes the edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.TestObject object class for a federate.
     *
     * @param rti handle to the Local RTI Component
     */
    static void publish_object(RTI::RTIambassador *rti) {
        ObjectRoot::publish_object( get_hla_class_name(), rti );
    }

    static bool get_is_published() {
        return ObjectRoot::get_is_published(get_hla_class_name());
    }

    /**
     * Unpublishes the edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.TestObject object class for a federate.
     *
     * @param rti handle to the Local RTI Component, usu. obtained through the
     *            {@link SynchronizedFederate#getRTI()} call
     */
    static void unpublish_object(RTI::RTIambassador *rti) {
        ObjectRoot::unpublish_object( get_hla_class_name(), rti);
    }

/**
 * Subscribes a federate to the edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.TestObject object class.
 *
 * @param rti handle to the Local RTI Component
 */
    static void subscribe_object(RTI::RTIambassador *rti) {
        ObjectRoot::subscribe_object( get_hla_class_name(), rti );
    }

    static bool get_is_subscribed() {
        return ObjectRoot::get_is_subscribed(get_hla_class_name());
    }

    static void soft_subscribe_object(RTI::RTIambassador *rti) {
        ObjectRoot::soft_subscribe_object(get_hla_class_name(), rti);
    }

    static bool get_is_soft_subscribed() {
        return ObjectRoot::get_is_soft_subscribed(get_hla_class_name());
    }

    /**
     * Unsubscribes a federate from the edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.TestObject object class.
     *
     * @param rti handle to the Local RTI Component
     */
    static void unsubscribe_object(RTI::RTIambassador *rti) {
        ObjectRoot::unsubscribe_object( get_hla_class_name(), rti );
    }

    static void soft_unsubscribe_object(RTI::RTIambassador *rti) {
        ObjectRoot::soft_unsubscribe_object(get_hla_class_name(), rti);
    }

    static ClassAndPropertyNameSetSP get_published_attribute_name_set_sp() {
        return ObjectRoot::get_class_name_published_class_and_property_name_set_sp_map()[get_hla_class_name()];
    }

    static ClassAndPropertyNameSetSP get_subscribed_attribute_name_set_sp() {
        return ObjectRoot::get_class_name_subscribed_class_and_property_name_set_sp_map()[get_hla_class_name()];
    }

    static void add_object_update_embedded_only_id(int id) {
        ObjectRoot::add_object_update_embedded_only_id(get_hla_class_name(), id);
    }

    static void remove_object_update_embedded_only_id(int id) {
        ObjectRoot::remove_object_update_embedded_only_id(get_hla_class_name(), id);
    }

    static const IntegerSetSP &get_object_update_embedded_only_id_set_sp() {
        return ObjectRoot::get_object_update_embedded_only_id_set_sp(get_hla_class_name());
    }

    static bool get_is_object_update_embedded_only_id(int id) {
        return ObjectRoot::get_is_object_update_embedded_only_id(get_hla_class_name(), id);
    }

    static void add_federate_name_soft_publish_direct(const std::string &federateName) {
        ObjectRoot::add_federate_name_soft_publish_direct(get_hla_class_name(), federateName);
    }

    static void remove_federate_name_soft_publish_direct(const std::string &federateName) {
        ObjectRoot::remove_federate_name_soft_publish_direct(get_hla_class_name(), federateName);
    }

    static const StringSetSP &get_federate_name_soft_publish_direct_set() {
        return ObjectRoot::get_federate_name_soft_publish_direct_set_sp(get_hla_class_name());
    }

    static void add_federate_name_soft_publish(const std::string &networkFederateName) {
        ObjectRoot::add_federate_name_soft_publish(get_hla_class_name(), networkFederateName);
    }

    static void remove_federate_name_soft_publish(const std::string &networkFederateName) {
        ObjectRoot::remove_federate_name_soft_publish(get_hla_class_name(), networkFederateName);
    }

    //-----------------------------------------------------
    // END METHODS FOR PUBLISHING/SUBSCRIBING-TO THIS CLASS
    //-----------------------------------------------------

    /**
     * Return true if "handle" is equal to the handle (RTI assigned) of this class
     * (that is, the edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.TestObject object class).
     *
     * @param handle handle to compare to the value of the handle (RTI assigned) of
     * this class (the edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.TestObject object class).
     * @return "true" if "handle" matches the value of the handle of this class
     * (that is, the edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.TestObject object class).
     */
    static bool match(int handle) {
        return handle == get_class_handle();
    }

    static int get_num_attributes() {
        return get_class_name_all_class_and_property_name_set_sp_map()[get_hla_class_name()]->size();
    }

    //------------------------------
    // PROPERTY MANIPULATION METHODS
    //------------------------------


    /**
     * Set the value of the "BooleanValue1" parameter to "value" for this parameter.
     *
     * @param value the new value for the "BooleanValue1" parameter
     */
    void set_BooleanValue1(bool newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "BooleanValue1");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
        value.setTime(getTime());
    }

    /**
     * Returns the value of the "BooleanValue1" parameter of this interaction.
     *
     * @return the value of the "BooleanValue1" parameter
     */
    bool get_BooleanValue1() {
        ClassAndPropertyName key(get_hla_class_name(), "BooleanValue1");
        return static_cast<bool>(*_classAndPropertyNameValueSPMap[key]);
    }

    /**
     * Returns the current timestamp of the "BooleanValue1" attribute of this object.
     *
     * @return the current timestamp of the "BooleanValue1" attribute
     */
    double get_BooleanValue1_time() {
        ClassAndPropertyName key(get_hla_class_name(), "BooleanValue1");
        return _classAndPropertyNameValueSPMap[key]->getTime();
    }


    /**
     * Set the value of the "BooleanValue2" parameter to "value" for this parameter.
     *
     * @param value the new value for the "BooleanValue2" parameter
     */
    void set_BooleanValue2(bool newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "BooleanValue2");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
        value.setTime(getTime());
    }

    /**
     * Returns the value of the "BooleanValue2" parameter of this interaction.
     *
     * @return the value of the "BooleanValue2" parameter
     */
    bool get_BooleanValue2() {
        ClassAndPropertyName key(get_hla_class_name(), "BooleanValue2");
        return static_cast<bool>(*_classAndPropertyNameValueSPMap[key]);
    }

    /**
     * Returns the current timestamp of the "BooleanValue2" attribute of this object.
     *
     * @return the current timestamp of the "BooleanValue2" attribute
     */
    double get_BooleanValue2_time() {
        ClassAndPropertyName key(get_hla_class_name(), "BooleanValue2");
        return _classAndPropertyNameValueSPMap[key]->getTime();
    }


    /**
     * Set the value of the "ByteValue" parameter to "value" for this parameter.
     *
     * @param value the new value for the "ByteValue" parameter
     */
    void set_ByteValue(char newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "ByteValue");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
        value.setTime(getTime());
    }

    /**
     * Returns the value of the "ByteValue" parameter of this interaction.
     *
     * @return the value of the "ByteValue" parameter
     */
    char get_ByteValue() {
        ClassAndPropertyName key(get_hla_class_name(), "ByteValue");
        return static_cast<char>(*_classAndPropertyNameValueSPMap[key]);
    }

    /**
     * Returns the current timestamp of the "ByteValue" attribute of this object.
     *
     * @return the current timestamp of the "ByteValue" attribute
     */
    double get_ByteValue_time() {
        ClassAndPropertyName key(get_hla_class_name(), "ByteValue");
        return _classAndPropertyNameValueSPMap[key]->getTime();
    }


    /**
     * Set the value of the "CharValue" parameter to "value" for this parameter.
     *
     * @param value the new value for the "CharValue" parameter
     */
    void set_CharValue(char newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "CharValue");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
        value.setTime(getTime());
    }

    /**
     * Returns the value of the "CharValue" parameter of this interaction.
     *
     * @return the value of the "CharValue" parameter
     */
    char get_CharValue() {
        ClassAndPropertyName key(get_hla_class_name(), "CharValue");
        return static_cast<char>(*_classAndPropertyNameValueSPMap[key]);
    }

    /**
     * Returns the current timestamp of the "CharValue" attribute of this object.
     *
     * @return the current timestamp of the "CharValue" attribute
     */
    double get_CharValue_time() {
        ClassAndPropertyName key(get_hla_class_name(), "CharValue");
        return _classAndPropertyNameValueSPMap[key]->getTime();
    }


    /**
     * Set the value of the "DoubleValue" parameter to "value" for this parameter.
     *
     * @param value the new value for the "DoubleValue" parameter
     */
    void set_DoubleValue(double newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "DoubleValue");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
        value.setTime(getTime());
    }

    /**
     * Returns the value of the "DoubleValue" parameter of this interaction.
     *
     * @return the value of the "DoubleValue" parameter
     */
    double get_DoubleValue() {
        ClassAndPropertyName key(get_hla_class_name(), "DoubleValue");
        return static_cast<double>(*_classAndPropertyNameValueSPMap[key]);
    }

    /**
     * Returns the current timestamp of the "DoubleValue" attribute of this object.
     *
     * @return the current timestamp of the "DoubleValue" attribute
     */
    double get_DoubleValue_time() {
        ClassAndPropertyName key(get_hla_class_name(), "DoubleValue");
        return _classAndPropertyNameValueSPMap[key]->getTime();
    }


    /**
     * Set the value of the "FloatValue" parameter to "value" for this parameter.
     *
     * @param value the new value for the "FloatValue" parameter
     */
    void set_FloatValue(float newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "FloatValue");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
        value.setTime(getTime());
    }

    /**
     * Returns the value of the "FloatValue" parameter of this interaction.
     *
     * @return the value of the "FloatValue" parameter
     */
    float get_FloatValue() {
        ClassAndPropertyName key(get_hla_class_name(), "FloatValue");
        return static_cast<float>(*_classAndPropertyNameValueSPMap[key]);
    }

    /**
     * Returns the current timestamp of the "FloatValue" attribute of this object.
     *
     * @return the current timestamp of the "FloatValue" attribute
     */
    double get_FloatValue_time() {
        ClassAndPropertyName key(get_hla_class_name(), "FloatValue");
        return _classAndPropertyNameValueSPMap[key]->getTime();
    }


    /**
     * Set the value of the "IntValue" parameter to "value" for this parameter.
     *
     * @param value the new value for the "IntValue" parameter
     */
    void set_IntValue(int newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "IntValue");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
        value.setTime(getTime());
    }

    /**
     * Returns the value of the "IntValue" parameter of this interaction.
     *
     * @return the value of the "IntValue" parameter
     */
    int get_IntValue() {
        ClassAndPropertyName key(get_hla_class_name(), "IntValue");
        return static_cast<int>(*_classAndPropertyNameValueSPMap[key]);
    }

    /**
     * Returns the current timestamp of the "IntValue" attribute of this object.
     *
     * @return the current timestamp of the "IntValue" attribute
     */
    double get_IntValue_time() {
        ClassAndPropertyName key(get_hla_class_name(), "IntValue");
        return _classAndPropertyNameValueSPMap[key]->getTime();
    }


    /**
     * Set the value of the "LongValue" parameter to "value" for this parameter.
     *
     * @param value the new value for the "LongValue" parameter
     */
    void set_LongValue(long newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "LongValue");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
        value.setTime(getTime());
    }

    /**
     * Returns the value of the "LongValue" parameter of this interaction.
     *
     * @return the value of the "LongValue" parameter
     */
    long get_LongValue() {
        ClassAndPropertyName key(get_hla_class_name(), "LongValue");
        return static_cast<long>(*_classAndPropertyNameValueSPMap[key]);
    }

    /**
     * Returns the current timestamp of the "LongValue" attribute of this object.
     *
     * @return the current timestamp of the "LongValue" attribute
     */
    double get_LongValue_time() {
        ClassAndPropertyName key(get_hla_class_name(), "LongValue");
        return _classAndPropertyNameValueSPMap[key]->getTime();
    }


    /**
     * Set the value of the "ShortValue" parameter to "value" for this parameter.
     *
     * @param value the new value for the "ShortValue" parameter
     */
    void set_ShortValue(short newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "ShortValue");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
        value.setTime(getTime());
    }

    /**
     * Returns the value of the "ShortValue" parameter of this interaction.
     *
     * @return the value of the "ShortValue" parameter
     */
    short get_ShortValue() {
        ClassAndPropertyName key(get_hla_class_name(), "ShortValue");
        return static_cast<short>(*_classAndPropertyNameValueSPMap[key]);
    }

    /**
     * Returns the current timestamp of the "ShortValue" attribute of this object.
     *
     * @return the current timestamp of the "ShortValue" attribute
     */
    double get_ShortValue_time() {
        ClassAndPropertyName key(get_hla_class_name(), "ShortValue");
        return _classAndPropertyNameValueSPMap[key]->getTime();
    }


    /**
     * Set the value of the "StringValue" parameter to "value" for this parameter.
     *
     * @param value the new value for the "StringValue" parameter
     */
    void set_StringValue(const std::string & newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "StringValue");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
        value.setTime(getTime());
    }

    /**
     * Returns the value of the "StringValue" parameter of this interaction.
     *
     * @return the value of the "StringValue" parameter
     */
    std::string get_StringValue() {
        ClassAndPropertyName key(get_hla_class_name(), "StringValue");
        return static_cast<std::string>(*_classAndPropertyNameValueSPMap[key]);
    }

    /**
     * Returns the current timestamp of the "StringValue" attribute of this object.
     *
     * @return the current timestamp of the "StringValue" attribute
     */
    double get_StringValue_time() {
        ClassAndPropertyName key(get_hla_class_name(), "StringValue");
        return _classAndPropertyNameValueSPMap[key]->getTime();
    }

    //------------------------------------
    // END PROPERTY MANIPULATION METHODS
    //------------------------------------

    //--------------------------
    // INSTANCE CREATION METHODS
    //--------------------------
public:
    static SP create() {
        return SP(new TestObject());
    }

    static ObjectRoot::SP create_object() {
        return SP(new TestObject());
    }

    virtual ObjectRoot::SP createObject() {
        return create_object();
    }

    static SP create(const RTIfedTime &rtiFedTime) {
        return SP(new TestObject(rtiFedTime));
    }

    static ObjectRoot::SP create_object(const RTIfedTime &rtiFedTime) {
        return SP(new TestObject(rtiFedTime));
    }

    virtual ObjectRoot::SP createObject(const RTIfedTime &rtiFedTime) {
        return create_object(rtiFedTime);
    }

    static SP create(
      const RTI::AttributeHandleValuePairSet &propertyMap
    ) {
        return SP(new TestObject(propertyMap));
    }

    static ObjectRoot::SP create_object(
      const RTI::AttributeHandleValuePairSet &propertyMap
    ) {
        return SP(new TestObject(propertyMap));
    }

    virtual ObjectRoot::SP createObject(
      const RTI::AttributeHandleValuePairSet &propertyMap
    ) {
        return create_object(propertyMap);
    }

    static SP create(
      const RTI::AttributeHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) {
        return SP(new TestObject(propertyMap, rtiFedTime));
    }

    static ObjectRoot::SP create_object(
      const RTI::AttributeHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) {
        return SP(new TestObject(propertyMap, rtiFedTime));
    }

    virtual ObjectRoot::SP createObject(
      const RTI::AttributeHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime) {
        return create_object(propertyMap, rtiFedTime);
    }

    virtual ObjectRoot::SP cloneObject() {
        return ObjectRoot::SP( new TestObject( *this )  );
    }

    //------------------------------
    // END INSTANCE CREATION METHODS
    //------------------------------

    static void publish_attribute(const std::string &attributeClass, const std::string &attributeName) {
        ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot::publish_attribute(
          get_hla_class_name(), attributeClass, attributeName
        );
    }

    static void publish_attribute(const std::string &attributeName) {
        publish_attribute(get_hla_class_name(), attributeName);
    }

    static void unpublish_attribute(const std::string &attributeClass, const std::string &attributeName) {
        ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot::unpublish_attribute(
          get_hla_class_name(), attributeClass, attributeName
        );
    }

    static void unpublish_attribute(const std::string &attributeName) {
        unpublish_attribute(get_hla_class_name(), attributeName);
    }

    static void subscribe_attribute(const std::string &attributeClass, const std::string &attributeName) {
        ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot::subscribe_attribute(
          get_hla_class_name(), attributeClass, attributeName
        );
    }

    static void subscribe_attribute(const std::string &attributeName) {
        subscribe_attribute(get_hla_class_name(), attributeName);
    }

    static void unsubscribe_attribute(const std::string &attributeClass, const std::string &attributeName) {
        ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot::unsubscribe_attribute(
          get_hla_class_name(), attributeClass, attributeName
        );
    }

    static void unsubscribe_attribute(const std::string &attributeName) {
        unsubscribe_attribute(get_hla_class_name(), attributeName);
    }

    static void soft_subscribe_attribute(const std::string &attributeClass, const std::string &attributeName) {
        ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot::soft_subscribe_attribute(
          get_hla_class_name(), attributeClass, attributeName
        );
    }

    static void soft_subscribe_attribute(const std::string &attributeName) {
        soft_subscribe_attribute(get_hla_class_name(), attributeName);
    }

    static void soft_unsubscribe_attribute(const std::string &attributeClass, const std::string &attributeName) {
        ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot::soft_unsubscribe_attribute(
          get_hla_class_name(), attributeClass, attributeName
        );
    }

    static void soft_unsubscribe_attribute(const std::string &attributeName) {
        soft_unsubscribe_attribute(get_hla_class_name(), attributeName);
    }

    /**
    * Publishes the "BooleanValue1" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "BooleanValue1" attribute for publication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void publish_BooleanValue1_attribute() {
        publish_attribute( get_hla_class_name(), "BooleanValue1" );
    }

    /**
    * Unpublishes the "BooleanValue1" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "BooleanValue1" attribute for unpublication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void unpublish_BooleanValue1_attribute() {
        unpublish_attribute( get_hla_class_name(), "BooleanValue1" );
    }

    /**
    * Subscribes a federate to the "BooleanValue1" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "BooleanValue1" attribute for subscription.
    * To actually subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void subscribe_BooleanValue1_attribute() {
        subscribe_attribute( get_hla_class_name(), "BooleanValue1" );
    }

    /**
    * Unsubscribes a federate from the "BooleanValue1" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "BooleanValue1" attribute for unsubscription.
    * To actually unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void unsubscribe_BooleanValue1_attribute() {
        unsubscribe_attribute( get_hla_class_name(), "BooleanValue1" );
    }

    /**
    * Soft subscribes a federate to the "BooleanValue1" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "BooleanValue1" attribute for soft subscription.
    * To actually soft subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.soft_subscribe_object( RTIambassador rti ) ).
    */
    static void soft_subscribe_BooleanValue1_attribute() {
        soft_subscribe_attribute(get_hla_class_name(), "BooleanValue1");
    }

    /**
    * Soft unsubscribes a federate from the "BooleanValue1" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "BooleanValue1" attribute for soft unsubscription.
    * To actually soft unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.unsubscribe_object( RTIambassador rti ) ).
    */
    static void soft_unsubscribe_BooleanValue1_attribute() {
        soft_unsubscribe_attribute(get_hla_class_name(), "BooleanValue1");
    }

    /**
    * Publishes the "BooleanValue2" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "BooleanValue2" attribute for publication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void publish_BooleanValue2_attribute() {
        publish_attribute( get_hla_class_name(), "BooleanValue2" );
    }

    /**
    * Unpublishes the "BooleanValue2" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "BooleanValue2" attribute for unpublication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void unpublish_BooleanValue2_attribute() {
        unpublish_attribute( get_hla_class_name(), "BooleanValue2" );
    }

    /**
    * Subscribes a federate to the "BooleanValue2" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "BooleanValue2" attribute for subscription.
    * To actually subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void subscribe_BooleanValue2_attribute() {
        subscribe_attribute( get_hla_class_name(), "BooleanValue2" );
    }

    /**
    * Unsubscribes a federate from the "BooleanValue2" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "BooleanValue2" attribute for unsubscription.
    * To actually unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void unsubscribe_BooleanValue2_attribute() {
        unsubscribe_attribute( get_hla_class_name(), "BooleanValue2" );
    }

    /**
    * Soft subscribes a federate to the "BooleanValue2" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "BooleanValue2" attribute for soft subscription.
    * To actually soft subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.soft_subscribe_object( RTIambassador rti ) ).
    */
    static void soft_subscribe_BooleanValue2_attribute() {
        soft_subscribe_attribute(get_hla_class_name(), "BooleanValue2");
    }

    /**
    * Soft unsubscribes a federate from the "BooleanValue2" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "BooleanValue2" attribute for soft unsubscription.
    * To actually soft unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.unsubscribe_object( RTIambassador rti ) ).
    */
    static void soft_unsubscribe_BooleanValue2_attribute() {
        soft_unsubscribe_attribute(get_hla_class_name(), "BooleanValue2");
    }

    /**
    * Publishes the "ByteValue" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "ByteValue" attribute for publication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void publish_ByteValue_attribute() {
        publish_attribute( get_hla_class_name(), "ByteValue" );
    }

    /**
    * Unpublishes the "ByteValue" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "ByteValue" attribute for unpublication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void unpublish_ByteValue_attribute() {
        unpublish_attribute( get_hla_class_name(), "ByteValue" );
    }

    /**
    * Subscribes a federate to the "ByteValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "ByteValue" attribute for subscription.
    * To actually subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void subscribe_ByteValue_attribute() {
        subscribe_attribute( get_hla_class_name(), "ByteValue" );
    }

    /**
    * Unsubscribes a federate from the "ByteValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "ByteValue" attribute for unsubscription.
    * To actually unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void unsubscribe_ByteValue_attribute() {
        unsubscribe_attribute( get_hla_class_name(), "ByteValue" );
    }

    /**
    * Soft subscribes a federate to the "ByteValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "ByteValue" attribute for soft subscription.
    * To actually soft subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.soft_subscribe_object( RTIambassador rti ) ).
    */
    static void soft_subscribe_ByteValue_attribute() {
        soft_subscribe_attribute(get_hla_class_name(), "ByteValue");
    }

    /**
    * Soft unsubscribes a federate from the "ByteValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "ByteValue" attribute for soft unsubscription.
    * To actually soft unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.unsubscribe_object( RTIambassador rti ) ).
    */
    static void soft_unsubscribe_ByteValue_attribute() {
        soft_unsubscribe_attribute(get_hla_class_name(), "ByteValue");
    }

    /**
    * Publishes the "CharValue" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "CharValue" attribute for publication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void publish_CharValue_attribute() {
        publish_attribute( get_hla_class_name(), "CharValue" );
    }

    /**
    * Unpublishes the "CharValue" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "CharValue" attribute for unpublication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void unpublish_CharValue_attribute() {
        unpublish_attribute( get_hla_class_name(), "CharValue" );
    }

    /**
    * Subscribes a federate to the "CharValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "CharValue" attribute for subscription.
    * To actually subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void subscribe_CharValue_attribute() {
        subscribe_attribute( get_hla_class_name(), "CharValue" );
    }

    /**
    * Unsubscribes a federate from the "CharValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "CharValue" attribute for unsubscription.
    * To actually unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void unsubscribe_CharValue_attribute() {
        unsubscribe_attribute( get_hla_class_name(), "CharValue" );
    }

    /**
    * Soft subscribes a federate to the "CharValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "CharValue" attribute for soft subscription.
    * To actually soft subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.soft_subscribe_object( RTIambassador rti ) ).
    */
    static void soft_subscribe_CharValue_attribute() {
        soft_subscribe_attribute(get_hla_class_name(), "CharValue");
    }

    /**
    * Soft unsubscribes a federate from the "CharValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "CharValue" attribute for soft unsubscription.
    * To actually soft unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.unsubscribe_object( RTIambassador rti ) ).
    */
    static void soft_unsubscribe_CharValue_attribute() {
        soft_unsubscribe_attribute(get_hla_class_name(), "CharValue");
    }

    /**
    * Publishes the "DoubleValue" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "DoubleValue" attribute for publication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void publish_DoubleValue_attribute() {
        publish_attribute( get_hla_class_name(), "DoubleValue" );
    }

    /**
    * Unpublishes the "DoubleValue" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "DoubleValue" attribute for unpublication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void unpublish_DoubleValue_attribute() {
        unpublish_attribute( get_hla_class_name(), "DoubleValue" );
    }

    /**
    * Subscribes a federate to the "DoubleValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "DoubleValue" attribute for subscription.
    * To actually subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void subscribe_DoubleValue_attribute() {
        subscribe_attribute( get_hla_class_name(), "DoubleValue" );
    }

    /**
    * Unsubscribes a federate from the "DoubleValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "DoubleValue" attribute for unsubscription.
    * To actually unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void unsubscribe_DoubleValue_attribute() {
        unsubscribe_attribute( get_hla_class_name(), "DoubleValue" );
    }

    /**
    * Soft subscribes a federate to the "DoubleValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "DoubleValue" attribute for soft subscription.
    * To actually soft subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.soft_subscribe_object( RTIambassador rti ) ).
    */
    static void soft_subscribe_DoubleValue_attribute() {
        soft_subscribe_attribute(get_hla_class_name(), "DoubleValue");
    }

    /**
    * Soft unsubscribes a federate from the "DoubleValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "DoubleValue" attribute for soft unsubscription.
    * To actually soft unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.unsubscribe_object( RTIambassador rti ) ).
    */
    static void soft_unsubscribe_DoubleValue_attribute() {
        soft_unsubscribe_attribute(get_hla_class_name(), "DoubleValue");
    }

    /**
    * Publishes the "FloatValue" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "FloatValue" attribute for publication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void publish_FloatValue_attribute() {
        publish_attribute( get_hla_class_name(), "FloatValue" );
    }

    /**
    * Unpublishes the "FloatValue" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "FloatValue" attribute for unpublication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void unpublish_FloatValue_attribute() {
        unpublish_attribute( get_hla_class_name(), "FloatValue" );
    }

    /**
    * Subscribes a federate to the "FloatValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "FloatValue" attribute for subscription.
    * To actually subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void subscribe_FloatValue_attribute() {
        subscribe_attribute( get_hla_class_name(), "FloatValue" );
    }

    /**
    * Unsubscribes a federate from the "FloatValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "FloatValue" attribute for unsubscription.
    * To actually unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void unsubscribe_FloatValue_attribute() {
        unsubscribe_attribute( get_hla_class_name(), "FloatValue" );
    }

    /**
    * Soft subscribes a federate to the "FloatValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "FloatValue" attribute for soft subscription.
    * To actually soft subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.soft_subscribe_object( RTIambassador rti ) ).
    */
    static void soft_subscribe_FloatValue_attribute() {
        soft_subscribe_attribute(get_hla_class_name(), "FloatValue");
    }

    /**
    * Soft unsubscribes a federate from the "FloatValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "FloatValue" attribute for soft unsubscription.
    * To actually soft unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.unsubscribe_object( RTIambassador rti ) ).
    */
    static void soft_unsubscribe_FloatValue_attribute() {
        soft_unsubscribe_attribute(get_hla_class_name(), "FloatValue");
    }

    /**
    * Publishes the "IntValue" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "IntValue" attribute for publication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void publish_IntValue_attribute() {
        publish_attribute( get_hla_class_name(), "IntValue" );
    }

    /**
    * Unpublishes the "IntValue" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "IntValue" attribute for unpublication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void unpublish_IntValue_attribute() {
        unpublish_attribute( get_hla_class_name(), "IntValue" );
    }

    /**
    * Subscribes a federate to the "IntValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "IntValue" attribute for subscription.
    * To actually subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void subscribe_IntValue_attribute() {
        subscribe_attribute( get_hla_class_name(), "IntValue" );
    }

    /**
    * Unsubscribes a federate from the "IntValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "IntValue" attribute for unsubscription.
    * To actually unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void unsubscribe_IntValue_attribute() {
        unsubscribe_attribute( get_hla_class_name(), "IntValue" );
    }

    /**
    * Soft subscribes a federate to the "IntValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "IntValue" attribute for soft subscription.
    * To actually soft subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.soft_subscribe_object( RTIambassador rti ) ).
    */
    static void soft_subscribe_IntValue_attribute() {
        soft_subscribe_attribute(get_hla_class_name(), "IntValue");
    }

    /**
    * Soft unsubscribes a federate from the "IntValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "IntValue" attribute for soft unsubscription.
    * To actually soft unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.unsubscribe_object( RTIambassador rti ) ).
    */
    static void soft_unsubscribe_IntValue_attribute() {
        soft_unsubscribe_attribute(get_hla_class_name(), "IntValue");
    }

    /**
    * Publishes the "LongValue" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "LongValue" attribute for publication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void publish_LongValue_attribute() {
        publish_attribute( get_hla_class_name(), "LongValue" );
    }

    /**
    * Unpublishes the "LongValue" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "LongValue" attribute for unpublication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void unpublish_LongValue_attribute() {
        unpublish_attribute( get_hla_class_name(), "LongValue" );
    }

    /**
    * Subscribes a federate to the "LongValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "LongValue" attribute for subscription.
    * To actually subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void subscribe_LongValue_attribute() {
        subscribe_attribute( get_hla_class_name(), "LongValue" );
    }

    /**
    * Unsubscribes a federate from the "LongValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "LongValue" attribute for unsubscription.
    * To actually unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void unsubscribe_LongValue_attribute() {
        unsubscribe_attribute( get_hla_class_name(), "LongValue" );
    }

    /**
    * Soft subscribes a federate to the "LongValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "LongValue" attribute for soft subscription.
    * To actually soft subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.soft_subscribe_object( RTIambassador rti ) ).
    */
    static void soft_subscribe_LongValue_attribute() {
        soft_subscribe_attribute(get_hla_class_name(), "LongValue");
    }

    /**
    * Soft unsubscribes a federate from the "LongValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "LongValue" attribute for soft unsubscription.
    * To actually soft unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.unsubscribe_object( RTIambassador rti ) ).
    */
    static void soft_unsubscribe_LongValue_attribute() {
        soft_unsubscribe_attribute(get_hla_class_name(), "LongValue");
    }

    /**
    * Publishes the "ShortValue" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "ShortValue" attribute for publication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void publish_ShortValue_attribute() {
        publish_attribute( get_hla_class_name(), "ShortValue" );
    }

    /**
    * Unpublishes the "ShortValue" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "ShortValue" attribute for unpublication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void unpublish_ShortValue_attribute() {
        unpublish_attribute( get_hla_class_name(), "ShortValue" );
    }

    /**
    * Subscribes a federate to the "ShortValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "ShortValue" attribute for subscription.
    * To actually subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void subscribe_ShortValue_attribute() {
        subscribe_attribute( get_hla_class_name(), "ShortValue" );
    }

    /**
    * Unsubscribes a federate from the "ShortValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "ShortValue" attribute for unsubscription.
    * To actually unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void unsubscribe_ShortValue_attribute() {
        unsubscribe_attribute( get_hla_class_name(), "ShortValue" );
    }

    /**
    * Soft subscribes a federate to the "ShortValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "ShortValue" attribute for soft subscription.
    * To actually soft subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.soft_subscribe_object( RTIambassador rti ) ).
    */
    static void soft_subscribe_ShortValue_attribute() {
        soft_subscribe_attribute(get_hla_class_name(), "ShortValue");
    }

    /**
    * Soft unsubscribes a federate from the "ShortValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "ShortValue" attribute for soft unsubscription.
    * To actually soft unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.unsubscribe_object( RTIambassador rti ) ).
    */
    static void soft_unsubscribe_ShortValue_attribute() {
        soft_unsubscribe_attribute(get_hla_class_name(), "ShortValue");
    }

    /**
    * Publishes the "StringValue" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "StringValue" attribute for publication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void publish_StringValue_attribute() {
        publish_attribute( get_hla_class_name(), "StringValue" );
    }

    /**
    * Unpublishes the "StringValue" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "StringValue" attribute for unpublication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void unpublish_StringValue_attribute() {
        unpublish_attribute( get_hla_class_name(), "StringValue" );
    }

    /**
    * Subscribes a federate to the "StringValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "StringValue" attribute for subscription.
    * To actually subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void subscribe_StringValue_attribute() {
        subscribe_attribute( get_hla_class_name(), "StringValue" );
    }

    /**
    * Unsubscribes a federate from the "StringValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "StringValue" attribute for unsubscription.
    * To actually unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void unsubscribe_StringValue_attribute() {
        unsubscribe_attribute( get_hla_class_name(), "StringValue" );
    }

    /**
    * Soft subscribes a federate to the "StringValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "StringValue" attribute for soft subscription.
    * To actually soft subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.soft_subscribe_object( RTIambassador rti ) ).
    */
    static void soft_subscribe_StringValue_attribute() {
        soft_subscribe_attribute(get_hla_class_name(), "StringValue");
    }

    /**
    * Soft unsubscribes a federate from the "StringValue" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "StringValue" attribute for soft unsubscription.
    * To actually soft unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.unsubscribe_object( RTIambassador rti ) ).
    */
    static void soft_unsubscribe_StringValue_attribute() {
        soft_unsubscribe_attribute(get_hla_class_name(), "StringValue");
    }

    //-------------
    // CONSTRUCTORS
    //-------------
public:
    TestObject() : Super( get_hla_class_name() ) { }

    TestObject( const PropertyHandleValuePairSet &propertyMap ) : Super( get_hla_class_name(), propertyMap ) { }

    TestObject( const RTIfedTime &rtiFedTime ) : Super( get_hla_class_name(), rtiFedTime ) { }

    TestObject(const PropertyHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime) :
       Super( get_hla_class_name(), propertyMap, rtiFedTime ) { }

protected:
    TestObject(ObjectRoot::NoInstanceInit &noInstanceInit) : Super(noInstanceInit) { }

    TestObject( const std::string &hlaClassName ) : Super( hlaClassName ) { }

    TestObject( const std::string &hlaClassName, const PropertyHandleValuePairSet &propertyMap ) :
      Super( hlaClassName, propertyMap ) { }

    TestObject( const std::string &hlaClassName, const RTIfedTime &rtiFedTime ) :
      Super( hlaClassName, rtiFedTime ) { }

    TestObject(
      const std::string &hlaClassName, const PropertyHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) : Super( hlaClassName, propertyMap, rtiFedTime ) { }

};
     } // NAMESPACE "ObjectRoot_p"
    } // NAMESPACE "hla"
   } // NAMESPACE "cpswt"
  } // NAMESPACE "vuisis"
 } // NAMESPACE "vanderbilt"
} // NAMESPACE "edu"

inline std::ostream &operator<<( std::ostream &os, ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject::SP messagingSP ) {
    return os << *messagingSP;
}

#endif // _edu_vanderbilt_vuisis_cpswt_hla_ObjectRoot_p_TestObject_CLASS
