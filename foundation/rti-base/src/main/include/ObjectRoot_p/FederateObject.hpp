
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
 *
 * @author Himanshu Neema
 * @author Harmon Nine
 */



#ifndef _org_cpswt_hla_ObjectRoot_p_FederateObject_CLASS
#define _org_cpswt_hla_ObjectRoot_p_FederateObject_CLASS

#include "ObjectRoot.hpp"
#include "C2WException.hpp"

#include <boost/unordered_set.hpp>

using ::org::cpswt::hla::ObjectRoot;


namespace org {
 namespace cpswt {
  namespace hla {
   namespace ObjectRoot_p {

class FederateObject : public ::org::cpswt::hla::ObjectRoot {
public:
    typedef ::org::cpswt::hla::ObjectRoot Super;
    typedef boost::shared_ptr< FederateObject > SP;

    // ----------------------------------------------------------------------------
    // STATIC DATAMEMBERS AND CODE THAT DEAL WITH NAMES
    // THIS CODE IS STATIC BECAUSE IT IS CLASS-DEPENDENT AND NOT INSTANCE-DEPENDENT
    // ----------------------------------------------------------------------------

public:
    /**
     * Returns the fully-qualified (dot-delimited) name of the org.cpswt.hla.ObjectRoot_p.FederateObject object class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the name of the class pertaining to the reference,
     * rather than the name of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getJavaClassName()}.
     *
     * @return the fully-qualified Java class name for this object class
     */
    static const std::string &get_cpp_class_name() {
        static const std::string cppClassName("::org::cpswt::hla::ObjectRoot_p::FederateObject");
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
     * class name) of the org.cpswt.hla.ObjectRoot_p.FederateObject object class.
     *
     * @return the name of this object class
     */
    static const std::string &get_simple_class_name() {
        static const std::string simpleClassName("FederateObject");
        return simpleClassName;
    }

    /**
     * Returns the simple name (last name in its fully-qualified dot-delimited name)
     * of this instance's object class.
     * Polymorphic equivalent of the get_simple_class_name static method.
     *
     * @return the simple name of this instance's object class
     */
    const std::string &getSimpleClassName() const override {
        return get_simple_class_name();
    }

    /**
     * Returns the fully-qualified (dot-delimited) hla class name of the
     * ObjectRoot.FederateObject object class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the federation name of the class pertaining to the reference,
     * rather than the name of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getHlaClassName()}.
     *
     * @return the fully-qualified federation (HLA) class name for this object class
     */
    static const std::string &get_hla_class_name() {
        static const std::string hlaClassName("ObjectRoot.FederateObject");
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

private:
    static ClassAndPropertyNameSetSP &get_class_and_property_name_set_sp() {
        static ClassAndPropertyNameSetSP classAndPropertyNameSetSP(new ClassAndPropertyNameSet());
        return classAndPropertyNameSetSP;
    }

public:
    /**
     * Returns a sorted list containing the names of all of the non-hidden attributes in the
     * org.cpswt.hla.ObjectRoot_p.FederateObject object class.
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
        const ClassAndPropertyNameSet &classAndPropertyNameSet(*get_class_and_property_name_set_sp());
        std::list<ClassAndPropertyName> classAndPropertyNameList(
          classAndPropertyNameSet.begin(), classAndPropertyNameSet.end()
        );
        classAndPropertyNameList.sort();
        return classAndPropertyNameList;
    }

    /**
     * Returns a sorted list containing the names of all of the non-hiddenattributes of an
     * object class instance.
     * The property names are paired with name of the hla class in which they are defined in a
     * ClassAndPropertyName POJO.
     * Polymorphic equivalent to get_attribute_names static method.
     *
     * @return sorted list containing the names of all of the attributes of an
     * object class instance paired with name of the hla class in which they are defined in a
     * ClassAndPropertyName POJO.
     */
    const ClassAndPropertyNameList getAttributeNames() const override {
        return get_attribute_names();
    }

private:
    static ClassAndPropertyNameSetSP &get_all_class_and_property_name_set_sp() {
        static ClassAndPropertyNameSetSP allClassAndPropertyNameSetSP(new ClassAndPropertyNameSet());
        return allClassAndPropertyNameSetSP;
    }

public:
    /**
     * Returns a sorted list containing the names of all of the attributes in the
     * org.cpswt.hla.ObjectRoot_p.FederateObject object class.
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
        const ClassAndPropertyNameSet &allClassAndPropertyNameSet(*get_all_class_and_property_name_set_sp());
        ClassAndPropertyNameList allClassAndPropertyNameList(
          allClassAndPropertyNameSet.begin(), allClassAndPropertyNameSet.end()
        );
        allClassAndPropertyNameList.sort();
        return allClassAndPropertyNameList;
    }

    /**
     * Returns a sorted list containing the names of all of the attributes of an
     * object class instance.
     * The property names are paired with name of the hla class in which they are defined in a
     * ClassAndPropertyName POJO.
     * Polymorphic equivalent of get_all_attribute_names() static method.
     *
     * @return sorted list containing the names of all of the attributes of an
     * object class instance paired with name of the hla class in which they are defined in a
     * ClassAndPropertyName POJO.
     */
    const ClassAndPropertyNameList getAllAttributeNames() const override {
        return get_all_attribute_names();
    }

protected:
    static ClassAndPropertyNameSetSP &get_published_class_and_property_name_set_sp() {
        static ClassAndPropertyNameSetSP publishedAttributeNameSetSP(new ClassAndPropertyNameSet());
        return publishedAttributeNameSetSP;
    }

    virtual const ClassAndPropertyNameSetSP &getPublishedClassAndPropertyNameSetSP() {
        return get_published_class_and_property_name_set_sp();
    }

    static ClassAndPropertyNameSetSP &get_subscribed_class_and_property_name_set_sp() {
        static ClassAndPropertyNameSetSP subscribedAttributeNameSetSP(new ClassAndPropertyNameSet());
        return subscribedAttributeNameSetSP;
    }

    virtual const ClassAndPropertyNameSetSP &getSubscribedClassAndPropertyNameSetSP() {
        return get_subscribed_class_and_property_name_set_sp();
    }


public:
    /*
     * INITIALIZE STATIC DATAMEMBERS THAT DEAL WITH NAMES
     */
    static bool static_init();
    static bool static_init_var;

    // --------------------------------------------------------
    // END OF STATIC DATAMEMBERS AND CODE THAT DEAL WITH NAMES.
    // --------------------------------------------------------


public:
    // ----------------------------------------------------------------------------
    // STATIC DATAMEMBERS AND CODE THAT DEAL WITH HANDLES.
    // THIS CODE IS STATIC BECAUSE IT IS CLASS-DEPENDENT AND NOT INSTANCE-DEPENDENT
    // ----------------------------------------------------------------------------
    /**
     * Returns the handle (RTI assigned) of the org.cpswt.hla.ObjectRoot_p.FederateObject object class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the handle of the class pertaining to the reference,
     * rather than the handle of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getClassHandle()}.
     *
     * @return the RTI assigned integer handle that represents this object class
     */
    static int &get_class_handle() {
        static int _handle;
        return _handle;
    }

    /**
     * Returns the handle (RTI assigned) of this instance's object class.
     * Polymorphic equivalent for get_class_handle static method.
     *
     * @return the handle (RTI assigned) if this instance's object class
     */
    int getClassHandle() const override {
        return get_class_handle();
    }


protected:
    /*
     * THIS IS A PROTECTED METHOD THAT WILL (TRY TO) RETURN THE HANDLE OF A GIVEN DATAMEMBER, GIVEN THE DATAMEMBER'S NAME.
     * FOR A GIVEN CLASS, IT WILL ATTEMPT TO FIND THE ENTRY IN THE _classAndPropertyNameHandleMap USING AS A KEY
     * A ClassAndPropertyName POJO, ClassAndPropertyName(A, B), WHERE "A" IS THE FULL CLASS NAME OF THIS CLASS,
     * AND "B" IS THE NAME OF THE DATAMEMBER. IF THERE IS NO SUCH ENTRY, THIS METHOD CALLS THE SAME METHOD IN ITS
     * SUPER CLASS.  THIS METHOD CHAIN BOTTOMS OUT IN THE "InteractionRoot" CLASS, WHERE AN ERROR IS RAISED INDICATING
     * THERE IS NO SUCH DATAMEMBER.
     *
     * THE "className" ARGUMENT IS THE FULL NAME OF THE CLASS FOR WHICH THIS METHOD WAS ORIGINALLY CALLED, I.E. THE NAME
     * OF THE CLASS AT THE TOP OF THE CALL-CHAIN.  IT IS INCLUDED FOR ERROR REPORTING IN THE "InteractionRoot" CLASS.
     *
     * THIS METHOD IS INDIRECTLY CALLED VIA THE "get_attribute_handle(String)" METHOD BELOW, WHICH PROVIDES THE
     * VALUE FOR THE "className" ARGUMENT.
     */
    static int get_attribute_handle_aux(const std::string &className, const std::string &propertyName);

public:
    /**
     * Returns the handle of an attribute (RTI assigned) of
     * this object class (i.e. "org.cpswt.hla.ObjectRoot_p.FederateObject") given the attribute's name.
     *
     * @param propertyName name of attribute
     * @return the handle (RTI assigned) of the attribute "propertyName" of object class "className"
     */
    static int get_attribute_handle(const std::string &propertyName) {
        return get_attribute_handle_aux(get_hla_class_name(), propertyName);
    }

    /**
     * Returns the handle associated with the given attribute name for an object class instance
     * Polymorphic equivalent of get_attribute_handle static method.
     *
     * @param propertyName the name of a attribute that belongs to this object class
     * @return the RTI handle associated with the attribute name, or -1 if not found
     */
    virtual int getAttributeHandle(const std::string &propertyName) {
        return get_attribute_handle(propertyName);
    }

private:
    static AttributeHandleSetSP get_published_attribute_handle_set_sp() {
        static AttributeHandleSetSP publishedAttributeHandleSetSP(
          RTI::AttributeHandleSetFactory::create( 3 )
        );
        return publishedAttributeHandleSetSP;
    }

    static AttributeHandleSetSP get_subscribed_attribute_handle_set_sp() {
        static AttributeHandleSetSP subscribedAttributeHandleSetSP(
          RTI::AttributeHandleSetFactory::create( 3 )
        );
        return subscribedAttributeHandleSetSP;
    }

private:
    static bool &get_is_initialized() {
        static bool isInitialized = false;
        return isInitialized;
    }

protected:
    /*
     * THIS FUNCTION INITIALIZES ALL OF THE HANDLES ASSOCIATED WITH THIS OBJECT CLASS
     * IT NEEDS THE RTI TO DO SO.
     */
    static void init(RTI::RTIambassador *rti);

    // ----------------------------------------------------------
    // END OF STATIC DATAMEMBERS AND CODE THAT DEAL WITH HANDLES.
    // ----------------------------------------------------------


    //-------------------------------------------------
    // METHODS FOR PUBLISHING/SUBSCRIBING-TO THIS CLASS
    //-------------------------------------------------

private:
    static bool &get_is_published() {
        static bool isPublished = false;
        return isPublished;
    }

public:
    /**
     * Publishes the org.cpswt.hla.ObjectRoot_p.FederateObject object class for a federate.
     *
     * @param rti handle to the Local RTI Component
     */
    static void publish_object(RTI::RTIambassador *rti);

    /**
     * Publishes the object class of this instance of the class for a federate.
     * Polymorphic equalivalent of publish_object static method.
     *
     * @param rti handle to the Local RTI Component
     */
    virtual void publishObject(RTI::RTIambassador *rti) {
        publish_object(rti);
    }


    /**
     * Unpublishes the org.cpswt.hla.ObjectRoot_p.FederateObject object class for a federate.
     *
     * @param rti handle to the Local RTI Component, usu. obtained through the
     *            {@link SynchronizedFederate#getLRC()} call
     */
    static void unpublish_object(RTI::RTIambassador *rti);

    /**
     * Unpublishes the object class of this instance of this class for a federate.
     * Polymorphic equivalent of unpublish_object static method.
     *
     * @param rti handle to the Local RTI Component
     */
    virtual void unpublishObject(RTI::RTIambassador *rti) {
        unpublish_object(rti);
    }

private:
    static bool &get_is_subscribed() {
        static bool isSubscribed = false;
        return isSubscribed;
    }

/**
 * Subscribes a federate to the org.cpswt.hla.ObjectRoot_p.FederateObject object class.
 *
 * @param rti handle to the Local RTI Component
 */
public:
    static void subscribe_object(RTI::RTIambassador *rti);

    /**
     * Subscribes a federate to the object class of this instance of this class.
     * Polymorphic equivalent of subscribe_object static method.
     *
     * @param rti handle to the Local RTI Component
     */
    virtual void subscribeObject(RTI::RTIambassador *rti) {
        subscribe_object(rti);
    }

    /**
     * Unsubscribes a federate from the org.cpswt.hla.ObjectRoot_p.FederateObject object class.
     *
     * @param rti handle to the Local RTI Component
     */
    static void unsubscribe_object(RTI::RTIambassador *rti);

public:
    /**
     * Unsubscribes a federate from the object class of this instance of this class.
     *
     * @param rti handle to the Local RTI Component
     */
    virtual void unsubscribeObject(RTI::RTIambassador *rti) {
        unsubscribe_object(rti);
    }

    //-----------------------------------------------------
    // END METHODS FOR PUBLISHING/SUBSCRIBING-TO THIS CLASS
    //-----------------------------------------------------

public:
    /**
     * Return true if "handle" is equal to the handle (RTI assigned) of this class
     * (that is, the org.cpswt.hla.ObjectRoot_p.FederateObject object class).
     *
     * @param handle handle to compare to the value of the handle (RTI assigned) of
     * this class (the org.cpswt.hla.ObjectRoot_p.FederateObject object class).
     * @return "true" if "handle" matches the value of the handle of this class
     * (that is, the org.cpswt.hla.ObjectRoot_p.FederateObject object class).
     */
    static bool match(int handle) {
        return handle == get_class_handle();
    }


    //--------------------------------
    // DATAMEMBER MANIPULATION METHODS
    //--------------------------------
public:


    /**
     * Set the value of the "FederateHandle" parameter to "value" for this parameter.
     *
     * @param value the new value for the "FederateHandle" parameter
     */
    void set_FederateHandle(int newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "FederateHandle");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
        value.setTime(getTime());
    }

    /**
     * Returns the value of the "FederateHandle" parameter of this interaction.
     *
     * @return the value of the "FederateHandle" parameter
     */
    int get_FederateHandle() {
        ClassAndPropertyName key(get_hla_class_name(), "FederateHandle");
        return static_cast<int>(*_classAndPropertyNameValueSPMap[key]);
    }

    /**
     * Returns the current timestamp of the "FederateHandle" attribute of this object.
     *
     * @return the current timestamp of the "FederateHandle" attribute
     */
    double get_FederateHandle_time() {
        ClassAndPropertyName key(get_hla_class_name(), "FederateHandle");
        return _classAndPropertyNameValueSPMap[key]->getTime();
    }


    /**
     * Set the value of the "FederateHost" parameter to "value" for this parameter.
     *
     * @param value the new value for the "FederateHost" parameter
     */
    void set_FederateHost(const std::string & newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "FederateHost");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
        value.setTime(getTime());
    }

    /**
     * Returns the value of the "FederateHost" parameter of this interaction.
     *
     * @return the value of the "FederateHost" parameter
     */
    std::string get_FederateHost() {
        ClassAndPropertyName key(get_hla_class_name(), "FederateHost");
        return static_cast<std::string>(*_classAndPropertyNameValueSPMap[key]);
    }

    /**
     * Returns the current timestamp of the "FederateHost" attribute of this object.
     *
     * @return the current timestamp of the "FederateHost" attribute
     */
    double get_FederateHost_time() {
        ClassAndPropertyName key(get_hla_class_name(), "FederateHost");
        return _classAndPropertyNameValueSPMap[key]->getTime();
    }


    /**
     * Set the value of the "FederateType" parameter to "value" for this parameter.
     *
     * @param value the new value for the "FederateType" parameter
     */
    void set_FederateType(const std::string & newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "FederateType");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
        value.setTime(getTime());
    }

    /**
     * Returns the value of the "FederateType" parameter of this interaction.
     *
     * @return the value of the "FederateType" parameter
     */
    std::string get_FederateType() {
        ClassAndPropertyName key(get_hla_class_name(), "FederateType");
        return static_cast<std::string>(*_classAndPropertyNameValueSPMap[key]);
    }

    /**
     * Returns the current timestamp of the "FederateType" attribute of this object.
     *
     * @return the current timestamp of the "FederateType" attribute
     */
    double get_FederateType_time() {
        ClassAndPropertyName key(get_hla_class_name(), "FederateType");
        return _classAndPropertyNameValueSPMap[key]->getTime();
    }

protected:
    virtual PropertyClassNameAndValueSP getAttributeAux(
      const std::string &className, const std::string &propertyName
    ) const;

    void classAndPropertyNameValueSPMapInit() {

        _classAndPropertyNameValueSPMap.emplace( std::make_pair(
          ClassAndPropertyName(get_hla_class_name(), "FederateHandle"),
          ValueSP(  new Value( static_cast<int>(0) )  )
        ) );

        _classAndPropertyNameValueSPMap.emplace( std::make_pair(
          ClassAndPropertyName(get_hla_class_name(), "FederateHost"),
          ValueSP(  new Value( std::string("") )  )
        ) );

        _classAndPropertyNameValueSPMap.emplace( std::make_pair(
          ClassAndPropertyName(get_hla_class_name(), "FederateType"),
          ValueSP(  new Value( std::string("") )  )
        ) );
    }

    //------------------------------------
    // END DATAMEMBER MANIPULATION METHODS
    //------------------------------------

    //-------------
    // CONSTRUCTORS
    //-------------
    
    FederateObject() {
        FederateObject::classAndPropertyNameValueSPMapInit();
    }

    FederateObject( const PropertyHandleValuePairSet &propertyMap ) {
        FederateObject::classAndPropertyNameValueSPMapInit();
        setAttributes(propertyMap);
    }

    FederateObject( const RTIfedTime &rtiFedTime ) {
        FederateObject::classAndPropertyNameValueSPMapInit();
    }

    FederateObject(const PropertyHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime) {
        FederateObject::classAndPropertyNameValueSPMapInit();
        setAttributes(propertyMap);
        setTime(rtiFedTime);
    }


    //--------------------------
    // INSTANCE CREATION METHODS
    //--------------------------
public:
    static SP create() {
        return SP(new FederateObject());
    }

    static ObjectRoot::SP create_object() {
        return SP(new FederateObject());
    }

    virtual ObjectRoot::SP createObject() {
        return create_object();
    }

    static SP create(
      const RTI::AttributeHandleValuePairSet &propertyMap
    ) {
        return SP(new FederateObject(propertyMap));
    }

    static ObjectRoot::SP create_object(
      const RTI::AttributeHandleValuePairSet &propertyMap
    ) {
        return SP(new FederateObject(propertyMap));
    }

    virtual ObjectRoot::SP createObject(
      const RTI::AttributeHandleValuePairSet &propertyMap
    ) {
        return create_object(propertyMap);
    }

    static SP create(const RTIfedTime &rtiFedTime) {
        return SP(new FederateObject(rtiFedTime));
    }

    static ObjectRoot::SP create_object(const RTIfedTime &rtiFedTime) {
        return SP(new FederateObject(rtiFedTime));
    }

    virtual ObjectRoot::SP createObject(const RTIfedTime &rtiFedTime) {
        return create_object(rtiFedTime);
    }

    static SP create(
      const RTI::AttributeHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) {
        return SP(new FederateObject(propertyMap, rtiFedTime));
    }

    static ObjectRoot::SP create_object(
      const RTI::AttributeHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) {
        return SP(new FederateObject(propertyMap, rtiFedTime));
    }

    virtual ObjectRoot::SP createObject(
      const RTI::AttributeHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime) {
        return create_object(propertyMap, rtiFedTime);
    }

    virtual ObjectRoot::SP cloneObject() {
        return ObjectRoot::SP( new FederateObject( *this )  );
    }

    //------------------------------
    // END INSTANCE CREATION METHODS
    //------------------------------

    /**
    * Publishes the "FederateHandle" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "FederateHandle" attribute for publication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador rti ) ).
    */
    static void publish_FederateHandle_attribute() {
        get_published_class_and_property_name_set_sp()->emplace(get_hla_class_name(), "FederateHandle");
    }

    /**
    * Unpublishes the "FederateHandle" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "FederateHandle" attribute for unpublication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador rti ) ).
    */
    static void unpublish_FederateHandle_attribute() {
        get_published_class_and_property_name_set_sp()->erase(
          ClassAndPropertyName(get_hla_class_name(), "FederateHandle")
        );
    }

    /**
    * Subscribes a federate to the "FederateHandle" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "FederateHandle" attribute for subscription.
    * To actually subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador rti ) ).
    */
    static void subscribe_FederateHandle_attribute() {
        get_subscribed_class_and_property_name_set_sp()->emplace(get_hla_class_name(), "FederateHandle");
    }

    /**
    * Unsubscribes a federate from the "FederateHandle" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "FederateHandle" attribute for unsubscription.
    * To actually unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador rti ) ).
    */
    static void unsubscribe_FederateHandle_attribute() {
        get_subscribed_class_and_property_name_set_sp()->erase(ClassAndPropertyName(
          get_hla_class_name(), "FederateHandle"
        ));
    }

    /**
    * Publishes the "FederateHost" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "FederateHost" attribute for publication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador rti ) ).
    */
    static void publish_FederateHost_attribute() {
        get_published_class_and_property_name_set_sp()->emplace(get_hla_class_name(), "FederateHost");
    }

    /**
    * Unpublishes the "FederateHost" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "FederateHost" attribute for unpublication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador rti ) ).
    */
    static void unpublish_FederateHost_attribute() {
        get_published_class_and_property_name_set_sp()->erase(
          ClassAndPropertyName(get_hla_class_name(), "FederateHost")
        );
    }

    /**
    * Subscribes a federate to the "FederateHost" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "FederateHost" attribute for subscription.
    * To actually subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador rti ) ).
    */
    static void subscribe_FederateHost_attribute() {
        get_subscribed_class_and_property_name_set_sp()->emplace(get_hla_class_name(), "FederateHost");
    }

    /**
    * Unsubscribes a federate from the "FederateHost" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "FederateHost" attribute for unsubscription.
    * To actually unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador rti ) ).
    */
    static void unsubscribe_FederateHost_attribute() {
        get_subscribed_class_and_property_name_set_sp()->erase(ClassAndPropertyName(
          get_hla_class_name(), "FederateHost"
        ));
    }

    /**
    * Publishes the "FederateType" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "FederateType" attribute for publication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador rti ) ).
    */
    static void publish_FederateType_attribute() {
        get_published_class_and_property_name_set_sp()->emplace(get_hla_class_name(), "FederateType");
    }

    /**
    * Unpublishes the "FederateType" attribute of the attribute's containing object
    * class for a federate.
    * Note:  This method only marks the "FederateType" attribute for unpublication.
    * To actually publish the attribute, the federate must (re)publish its containing
    * object class.
    * (using <objectClassName>.publish_object( RTIambassador rti ) ).
    */
    static void unpublish_FederateType_attribute() {
        get_published_class_and_property_name_set_sp()->erase(
          ClassAndPropertyName(get_hla_class_name(), "FederateType")
        );
    }

    /**
    * Subscribes a federate to the "FederateType" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "FederateType" attribute for subscription.
    * To actually subscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador rti ) ).
    */
    static void subscribe_FederateType_attribute() {
        get_subscribed_class_and_property_name_set_sp()->emplace(get_hla_class_name(), "FederateType");
    }

    /**
    * Unsubscribes a federate from the "FederateType" attribute of the attribute's
    * containing object class.
    * Note:  This method only marks the "FederateType" attribute for unsubscription.
    * To actually unsubscribe to the attribute, the federate must (re)subscribe to its
    * containing object class.
    * (using <objectClassName>.subscribe_object( RTIambassador rti ) ).
    */
    static void unsubscribe_FederateType_attribute() {
        get_subscribed_class_and_property_name_set_sp()->erase(ClassAndPropertyName(
          get_hla_class_name(), "FederateType"
        ));
    }

};
   } // NAMESPACE "ObjectRoot_p"
  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"

inline std::ostream &operator<<( std::ostream &os, ::org::cpswt::hla::ObjectRoot_p::FederateObject::SP messagingSP ) {
    return os << *messagingSP;
}

#endif // _org_cpswt_hla_ObjectRoot_p_FederateObject_CLASS