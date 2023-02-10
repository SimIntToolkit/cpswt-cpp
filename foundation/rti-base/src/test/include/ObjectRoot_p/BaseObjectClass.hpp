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

#ifndef _edu_vanderbilt_vuisis_cpswt_hla_ObjectRoot_p_BaseObjectClass_CLASS
#define _edu_vanderbilt_vuisis_cpswt_hla_ObjectRoot_p_BaseObjectClass_CLASS

#include "ObjectRoot.hpp"
#include "C2WException.hpp"

#include <boost/unordered_set.hpp>


namespace edu {
 namespace vanderbilt {
  namespace vuisis {
   namespace cpswt {
    namespace hla {
     namespace ObjectRoot_p {

class BaseObjectClass : public ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot {
public:
//    using ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot;
    typedef ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot Super;
    typedef boost::shared_ptr< BaseObjectClass > SP;

private:
    static severity_logger &get_logger_aux() {
        static severity_logger logger;
        logger.add_attribute("MessagingClassName", attrs::constant< std::string >(
          "ObjectRoot.BaseObjectClass"
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
     * Returns the fully-qualified (dot-delimited) name of the ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::BaseObjectClass object class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the name of the class pertaining to the reference,
     * rather than the name of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getJavaClassName()}.
     *
     * @return the fully-qualified Java class name for this object class
     */
    static const std::string &get_cpp_class_name() {
        static const std::string cppClassName("::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::BaseObjectClass");
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
     * class name) of the edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.BaseObjectClass object class.
     *
     * @return the name of this object class
     */
    static const std::string get_simple_class_name() {
        return ObjectRoot::get_simple_class_name(get_hla_class_name());
    }

    /**
     * Returns the fully-qualified (dot-delimited) hla class name of the
     * ObjectRoot.BaseObjectClass object class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the federation name of the class pertaining to the reference,
     * rather than the name of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getHlaClassName()}.
     *
     * @return the fully-qualified federation (HLA) class name for this object class
     */
    static const std::string &get_hla_class_name() {
        static const std::string hlaClassName("ObjectRoot.BaseObjectClass");
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
     * edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.BaseObjectClass object class.
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
     * edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.BaseObjectClass object class.
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
     * Returns the handle (RTI assigned) of the edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.BaseObjectClass object class.
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
     * this object class (i.e. "edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.BaseObjectClass") given the attribute's name.
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
     * Publishes the edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.BaseObjectClass object class for a federate.
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
     * Unpublishes the edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.BaseObjectClass object class for a federate.
     *
     * @param rti handle to the Local RTI Component, usu. obtained through the
     *            {@link SynchronizedFederate#getRTI()} call
     */
    static void unpublish_object(RTI::RTIambassador *rti) {
        ObjectRoot::unpublish_object( get_hla_class_name(), rti);
    }

/**
 * Subscribes a federate to the edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.BaseObjectClass object class.
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
     * Unsubscribes a federate from the edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.BaseObjectClass object class.
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

    static ClassAndPropertyNameSetSP get_soft_subscribed_attribute_name_set_sp() {
        return ObjectRoot::get_class_name_soft_subscribed_class_and_property_name_set_sp_map()[get_hla_class_name()];
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
     * (that is, the edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.BaseObjectClass object class).
     *
     * @param handle handle to compare to the value of the handle (RTI assigned) of
     * this class (the edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.BaseObjectClass object class).
     * @return "true" if "handle" matches the value of the handle of this class
     * (that is, the edu.vanderbilt.vuisis.cpswt.hla.ObjectRoot_p.BaseObjectClass object class).
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
     * Set the value of the "int_attribute1" parameter to "value" for this parameter.
     *
     * @param value the new value for the "int_attribute1" parameter
     */
    void set_int_attribute1(int newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "int_attribute1");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
        value.setTime(getTime());
    }

    /**
     * Returns the value of the "int_attribute1" parameter of this interaction.
     *
     * @return the value of the "int_attribute1" parameter
     */
    int get_int_attribute1() {
        ClassAndPropertyName key(get_hla_class_name(), "int_attribute1");
        return static_cast<int>(*_classAndPropertyNameValueSPMap[key]);
    }

    /**
     * Returns the current timestamp of the "int_attribute1" attribute of this object.
     *
     * @return the current timestamp of the "int_attribute1" attribute
     */
    double get_int_attribute1_time() {
        ClassAndPropertyName key(get_hla_class_name(), "int_attribute1");
        return _classAndPropertyNameValueSPMap[key]->getTime();
    }


    /**
     * Set the value of the "string_attribute1" parameter to "value" for this parameter.
     *
     * @param value the new value for the "string_attribute1" parameter
     */
    void set_string_attribute1(const std::string & newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "string_attribute1");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
        value.setTime(getTime());
    }

    /**
     * Returns the value of the "string_attribute1" parameter of this interaction.
     *
     * @return the value of the "string_attribute1" parameter
     */
    std::string get_string_attribute1() {
        ClassAndPropertyName key(get_hla_class_name(), "string_attribute1");
        return static_cast<std::string>(*_classAndPropertyNameValueSPMap[key]);
    }

    /**
     * Returns the current timestamp of the "string_attribute1" attribute of this object.
     *
     * @return the current timestamp of the "string_attribute1" attribute
     */
    double get_string_attribute1_time() {
        ClassAndPropertyName key(get_hla_class_name(), "string_attribute1");
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
        return SP(new BaseObjectClass());
    }

    static ObjectRoot::SP create_object() {
        return SP(new BaseObjectClass());
    }

    virtual ObjectRoot::SP createObject() {
        return create_object();
    }

    static SP create(const RTIfedTime &rtiFedTime) {
        return SP(new BaseObjectClass(rtiFedTime));
    }

    static ObjectRoot::SP create_object(const RTIfedTime &rtiFedTime) {
        return SP(new BaseObjectClass(rtiFedTime));
    }

    virtual ObjectRoot::SP createObject(const RTIfedTime &rtiFedTime) {
        return create_object(rtiFedTime);
    }

    static SP create(
      const RTI::AttributeHandleValuePairSet &propertyMap
    ) {
        return SP(new BaseObjectClass(propertyMap));
    }

    static ObjectRoot::SP create_object(
      const RTI::AttributeHandleValuePairSet &propertyMap
    ) {
        return SP(new BaseObjectClass(propertyMap));
    }

    virtual ObjectRoot::SP createObject(
      const RTI::AttributeHandleValuePairSet &propertyMap
    ) {
        return create_object(propertyMap);
    }

    static SP create(
      const RTI::AttributeHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) {
        return SP(new BaseObjectClass(propertyMap, rtiFedTime));
    }

    static ObjectRoot::SP create_object(
      const RTI::AttributeHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) {
        return SP(new BaseObjectClass(propertyMap, rtiFedTime));
    }

    virtual ObjectRoot::SP createObject(
      const RTI::AttributeHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime) {
        return create_object(propertyMap, rtiFedTime);
    }

    virtual ObjectRoot::SP cloneObject() {
        return ObjectRoot::SP( new BaseObjectClass( *this )  );
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
    * Publishes the "int_attribute1" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "int_attribute1" attribute for publication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void publish_int_attribute1_attribute() {
        publish_attribute( get_hla_class_name(), "int_attribute1" );
    }

    /**
    * Unpublishes the "int_attribute1" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "int_attribute1" attribute for unpublication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void unpublish_int_attribute1_attribute() {
        unpublish_attribute( get_hla_class_name(), "int_attribute1" );
    }

    /**
    * Subscribes a federate to the "int_attribute1" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "int_attribute1" attribute for subscription.
    * To actually subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void subscribe_int_attribute1_attribute() {
        subscribe_attribute( get_hla_class_name(), "int_attribute1" );
    }

    /**
    * Unsubscribes a federate from the "int_attribute1" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "int_attribute1" attribute for unsubscription.
    * To actually unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void unsubscribe_int_attribute1_attribute() {
        unsubscribe_attribute( get_hla_class_name(), "int_attribute1" );
    }

    /**
    * Soft subscribes a federate to the "int_attribute1" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "int_attribute1" attribute for soft subscription.
    * To actually soft subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.soft_subscribe_object( RTIambassador rti ) ).
    */
    static void soft_subscribe_int_attribute1_attribute() {
        soft_subscribe_attribute(get_hla_class_name(), "int_attribute1");
    }

    /**
    * Soft unsubscribes a federate from the "int_attribute1" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "int_attribute1" attribute for soft unsubscription.
    * To actually soft unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.unsubscribe_object( RTIambassador rti ) ).
    */
    static void soft_unsubscribe_int_attribute1_attribute() {
        soft_unsubscribe_attribute(get_hla_class_name(), "int_attribute1");
    }

    /**
    * Publishes the "string_attribute1" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "string_attribute1" attribute for publication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void publish_string_attribute1_attribute() {
        publish_attribute( get_hla_class_name(), "string_attribute1" );
    }

    /**
    * Unpublishes the "string_attribute1" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "string_attribute1" attribute for unpublication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador *rti ) ).
    */
    static void unpublish_string_attribute1_attribute() {
        unpublish_attribute( get_hla_class_name(), "string_attribute1" );
    }

    /**
    * Subscribes a federate to the "string_attribute1" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "string_attribute1" attribute for subscription.
    * To actually subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void subscribe_string_attribute1_attribute() {
        subscribe_attribute( get_hla_class_name(), "string_attribute1" );
    }

    /**
    * Unsubscribes a federate from the "string_attribute1" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "string_attribute1" attribute for unsubscription.
    * To actually unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador *rti ) ).
    */
    static void unsubscribe_string_attribute1_attribute() {
        unsubscribe_attribute( get_hla_class_name(), "string_attribute1" );
    }

    /**
    * Soft subscribes a federate to the "string_attribute1" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "string_attribute1" attribute for soft subscription.
    * To actually soft subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.soft_subscribe_object( RTIambassador rti ) ).
    */
    static void soft_subscribe_string_attribute1_attribute() {
        soft_subscribe_attribute(get_hla_class_name(), "string_attribute1");
    }

    /**
    * Soft unsubscribes a federate from the "string_attribute1" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "string_attribute1" attribute for soft unsubscription.
    * To actually soft unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.unsubscribe_object( RTIambassador rti ) ).
    */
    static void soft_unsubscribe_string_attribute1_attribute() {
        soft_unsubscribe_attribute(get_hla_class_name(), "string_attribute1");
    }

    //-------------
    // CONSTRUCTORS
    //-------------
public:
    BaseObjectClass() : Super( get_hla_class_name() ) { }

    BaseObjectClass( const PropertyHandleValuePairSet &propertyMap ) : Super( get_hla_class_name(), propertyMap ) { }

    BaseObjectClass( const RTIfedTime &rtiFedTime ) : Super( get_hla_class_name(), rtiFedTime ) { }

    BaseObjectClass(const PropertyHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime) :
       Super( get_hla_class_name(), propertyMap, rtiFedTime ) { }

protected:
    BaseObjectClass(ObjectRoot::NoInstanceInit &noInstanceInit) : Super(noInstanceInit) { }

    BaseObjectClass( const std::string &hlaClassName ) : Super( hlaClassName ) { }

    BaseObjectClass( const std::string &hlaClassName, const PropertyHandleValuePairSet &propertyMap ) :
      Super( hlaClassName, propertyMap ) { }

    BaseObjectClass( const std::string &hlaClassName, const RTIfedTime &rtiFedTime ) :
      Super( hlaClassName, rtiFedTime ) { }

    BaseObjectClass(
      const std::string &hlaClassName, const PropertyHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) : Super( hlaClassName, propertyMap, rtiFedTime ) { }

};
     } // NAMESPACE "ObjectRoot_p"
    } // NAMESPACE "hla"
   } // NAMESPACE "cpswt"
  } // NAMESPACE "vuisis"
 } // NAMESPACE "vanderbilt"
} // NAMESPACE "edu"

inline std::ostream &operator<<( std::ostream &os, ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::BaseObjectClass::SP messagingSP ) {
    return os << *messagingSP;
}

#endif // _edu_vanderbilt_vuisis_cpswt_hla_ObjectRoot_p_BaseObjectClass_CLASS
