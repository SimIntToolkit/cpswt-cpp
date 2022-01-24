
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



#ifndef _OBJECT_ROOT_CLASS
#define _OBJECT_ROOT_CLASS

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <list>
#include <cctype>
#include <cstdlib>

#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>

#include <jsoncpp/json/json.h>

#include "ObjectRootInterface.hpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "RTILogger.hpp"

#ifndef C2W_RTI_LOGGER_CLS
#define C2W_RTI_LOGGER_CLS C2WConsoleLogger
#endif


namespace org {
 namespace cpswt {
  namespace hla {

class ObjectRoot : public ObjectRootInterface {

public:
    typedef boost::shared_ptr<ObjectRoot> SP;
    typedef RTI::AttributeHandleValuePairSet PropertyHandleValuePairSet;
    typedef boost::shared_ptr<PropertyHandleValuePairSet> PropertyHandleValuePairSetSP;

    typedef boost::shared_ptr<ClassAndPropertyNameSet> ClassAndPropertyNameSetSP;

    typedef std::map<std::string, ClassAndPropertyNameSetSP> StringClassAndPropertyNameSetSPMap;
    typedef std::map< std::string, StringVector > NameStringVectorPtrMap;
    typedef std::map< ClassAndPropertyName, int > ClassAndPropertyNameIntegerMap;
    typedef std::map<int, ClassAndPropertyNameSP> IntegerClassAndPropertyNameSPMap;
    typedef std::map<int, std::string> IntegerStringMap;
    typedef std::map<std::string, int> StringIntegerMap;

    typedef RTI::AttributeHandleSet AttributeHandleSet;
    typedef boost::shared_ptr<AttributeHandleSet> AttributeHandleSetSP;

    typedef std::map<std::string, SP> StringInstanceSPMap;

    typedef Attribute Value;

    typedef boost::shared_ptr<Value> ValueSP;
    typedef std::unordered_map<ClassAndPropertyName, ValueSP> ClassAndPropertyNameValueSPMap;

    typedef void (*PubsubFunctionPtr)( RTI::RTIambassador * );
    typedef std::map< std::string, PubsubFunctionPtr > ClassNamePubSubMap;
    typedef std::map< std::string, std::string> DatamemberTypeMap;typedef std::map< std::string, AttributeHandleSetSP > StringAttributesHandleSetSPMap;
    typedef std::unordered_map< int, SP > ObjectHandleInstanceSPMap;

private:
    static int generate_unique_id() {
        static int globalUniqueId = 0;
        return globalUniqueId++;
    }

    const int _uniqueId;

public:
    int getUniqueId() override {
        return _uniqueId;
    }

    //---------------
    // CLASS-NAME SET
    //---------------
protected:
    static StringSet &get_hla_class_name_set( void ) {
        static StringSet hlaClassNameSet;
        return hlaClassNameSet;
    }

    //--------------------------------
    // METHODS THAT USE CLASS-NAME-SET
    //--------------------------------
public:
    static const StringSet &get_object_hla_class_name_set( void ) {
        return get_hla_class_name_set();
    }

    //-------------------
    // END CLASS-NAME-SET
    //-------------------

    //----------------------------
    // CLASS-NAME CLASS-HANDLE MAP
    //----------------------------
protected:
    static StringIntegerMap &get_class_name_handle_map( void ) {
        static StringIntegerMap classNameHandleMap;
        return classNameHandleMap;
    }

    //---------------------------------------------
    // METHODS THAT USE CLASS-NAME CLASS-HANDLE MAP
    //---------------------------------------------
public:
    static int get_class_handle(const std::string &className) {
        StringIntegerMap::iterator simItr = get_class_name_handle_map().find(className);
        return simItr == get_class_name_handle_map().end() ? -1 : simItr->second;
    }
    static int get_class_handle(const char *className) {
        return get_class_handle(std::string(className));
    }

    //--------------------------------
    // END CLASS-NAME CLASS-HANDLE MAP
    //--------------------------------

    //-----------------------------------
    // CLASS-NAME DATAMEMBER-NAME-SET MAP
    //-----------------------------------
protected:
    static StringClassAndPropertyNameSetSPMap &get_class_name_class_and_property_name_set_sp_map() {
        static StringClassAndPropertyNameSetSPMap classNamePropertyNameSetSPMap;
        return classNamePropertyNameSetSPMap;
    }

    //----------------------------------------------------
    // METHODS THAT USE CLASS-NAME DATAMEMBER-NAME-SET MAP
    //----------------------------------------------------
public:
    static ClassAndPropertyNameList get_attribute_names(const std::string &className) {
       StringClassAndPropertyNameSetSPMap::iterator scmItr =
         get_class_name_class_and_property_name_set_sp_map().find(className);

       const ClassAndPropertyNameSet &classAndPropertyNameSet =
         scmItr == get_class_name_class_and_property_name_set_sp_map().end() ?
           *ClassAndPropertyNameSetSP(new ClassAndPropertyNameSet()) : *scmItr->second;

       ClassAndPropertyNameList classAndPropertyNameList(
         classAndPropertyNameSet.begin(), classAndPropertyNameSet.end()
       );

       classAndPropertyNameList.sort();
       return classAndPropertyNameList;
    }

    //---------------------------------------
    // END CLASS-NAME DATAMEMBER-NAME-SET MAP
    //---------------------------------------

    //---------------------------------------
    // CLASS-NAME ALL-DATAMEMBER-NAME-SET MAP
    //---------------------------------------
protected:
    static StringClassAndPropertyNameSetSPMap &get_class_name_all_class_and_property_name_set_sp_map() {
        static StringClassAndPropertyNameSetSPMap classNameAllPropertyNameSetSPMap;
        return classNameAllPropertyNameSetSPMap;
    }

    //--------------------------------------------------------
    // METHODS THAT USE CLASS-NAME ALL-DATAMEMBER-NAME-SET MAP
    //--------------------------------------------------------
public:
    static const ClassAndPropertyNameList get_all_attribute_names(const std::string &className) {
       StringClassAndPropertyNameSetSPMap::iterator scmItr =
         get_class_name_all_class_and_property_name_set_sp_map().find(className);

       const ClassAndPropertyNameSet &classAndPropertyNameSet =
         scmItr == get_class_name_all_class_and_property_name_set_sp_map().end() ?
           *ClassAndPropertyNameSetSP(new ClassAndPropertyNameSet()) : *scmItr->second;

       ClassAndPropertyNameList classAndPropertyNameList(
         classAndPropertyNameSet.begin(), classAndPropertyNameSet.end()
       );

       classAndPropertyNameList.sort();
       return classAndPropertyNameList;
    }

    //-------------------------------------------
    // END CLASS-NAME All-DATAMEMBER-NAME-SET MAP
    //-------------------------------------------

    //--------------------------------------------
    // CLASS-AND-PROPERTY-NAME PROPERTY-HANDLE MAP
    //--------------------------------------------
protected:
    static ClassAndPropertyNameIntegerMap &get_class_and_property_name_handle_map() {
        static ClassAndPropertyNameIntegerMap classAndPropertyNameIntegerMap;
        return classAndPropertyNameIntegerMap;
    }

    //------------------------------------------------------------------
    // METHODS THAT USE CLASS-NAME-DATAMEMBER-NAME DATAMEMBER-HANDLE MAP
    //------------------------------------------------------------------
private:
    static std::string join(const std::list<std::string> &joinList, const std::string &delimiter);

public:
    static ClassAndPropertyNameSP findProperty(const std::string &className, const std::string &propertyName);

    static int get_attribute_handle(const std::string &className, const std::string &propertyName) {
        ClassAndPropertyNameSP key = findProperty(className, propertyName);
        if (!key) {
            return -1;
        }

        return get_class_and_property_name_handle_map()[*key];
    }
    //-----------------------------------------------------
    // END CLASS-NAME-DATAMEMBER-NAME DATAMEMBER-HANDLE MAP
    //-----------------------------------------------------


    //------------------------------------------------
    // DATAMEMBER-HANDLE CLASS-AND-DATAMEMBER-NAME MAP
    //------------------------------------------------
protected:
    static IntegerClassAndPropertyNameSPMap get_handle_class_and_property_name_sp_map() {
        static IntegerClassAndPropertyNameSPMap handleClassAndPropertyNameSPMap;
        return handleClassAndPropertyNameSPMap;
    }

    //-----------------------------------------------------------------
    // METHODS THAT USE DATAMEMBER-HANDLE CLASS-AND-DATAMEMBER-NAME MAP
    //-----------------------------------------------------------------
public:
    static ClassAndPropertyNameSP get_class_and_attribute_name(int propertyHandle) {
        IntegerClassAndPropertyNameSPMap::iterator icmItr =
          get_handle_class_and_property_name_sp_map().find(propertyHandle);
        return icmItr == get_handle_class_and_property_name_sp_map().end()
          ? ClassAndPropertyNameSP() : icmItr->second;
    }

    ClassAndPropertyNameSP getClassAndAttributeName(int propertyHandle) {
        return get_class_and_attribute_name(propertyHandle);
    }

    const std::string &getAttributeName(int propertyHandle) {
        static std::string emptyString;
        ClassAndPropertyNameSP classAndPropertyNameSP = get_class_and_attribute_name(propertyHandle);
        return classAndPropertyNameSP ? classAndPropertyNameSP->getPropertyName() : emptyString;
    }

    //----------------------------------------------------
    // END DATAMEMBER-HANDLE CLASS-AND-DATAMEMBER-NAME MAP
    //----------------------------------------------------


    //-----------------------------------
    // CLASS-HANDLE CLASS-SIMPLE-NAME MAP
    //-----------------------------------
protected:
    static IntegerStringMap &get_class_handle_simple_name_map() {
        static IntegerStringMap integerStringMap;
        return integerStringMap;
    }

    //----------------------------------------------------
    // METHODS THAT USE CLASS-HANDLE CLASS-SIMPLE-NAME MAP
    //----------------------------------------------------
public:
    static const std::string &get_simple_class_name(int classHandle) {
        static std::string emptyString;
        IntegerStringMap::iterator ismItr = get_class_handle_simple_name_map().find(classHandle);
        return ismItr == get_class_handle_simple_name_map().end() ? emptyString : ismItr->second;
    }

    //---------------------------------------
    // END CLASS-HANDLE CLASS-SIMPLE-NAME MAP
    //---------------------------------------


    //-----------------------
    // CLASS-NAME ROOT-SP MAP
    //-----------------------
protected:
    static StringInstanceSPMap &get_class_name_instance_sp_map() {
        static StringInstanceSPMap classNameInstanceSPMap;
        return classNameInstanceSPMap;
    }

    //-----------------------------------------
    // METHODS THAT USER CLASS-NAME ROOT-SP MAP
    //-----------------------------------------
public:

    static SP create_object(const std::string &className) {
        StringInstanceSPMap::iterator cimItr = get_class_name_instance_sp_map().find(className);
        return cimItr == get_class_name_instance_sp_map().end()
          ? SP() : cimItr->second->createObject();
    }

    static SP create_object(const std::string &className, const RTIfedTime &rtiFedTime) {
        StringInstanceSPMap::iterator cimItr = get_class_name_instance_sp_map().find( className );
        return cimItr == get_class_name_instance_sp_map().end()
          ? SP() : cimItr->second->createObject(rtiFedTime);
    }

    static void publish_object(const std::string &className, RTI::RTIambassador *rtiAmbassador) {
        StringInstanceSPMap::iterator cimItr = get_class_name_instance_sp_map().find(className);
        if (cimItr != get_class_name_instance_sp_map().end()) {
            cimItr->second->publishObject(rtiAmbassador);
        }
    }

    static void unpublish_object(const std::string &className, RTI::RTIambassador *rtiAmbassador) {
        StringInstanceSPMap::iterator cimItr = get_class_name_instance_sp_map().find(className);
        if (cimItr != get_class_name_instance_sp_map().end()) {
            cimItr->second->unpublishObject(rtiAmbassador);
        }
    }

    static void subscribe_object(const std::string &className, RTI::RTIambassador *rtiAmbassador) {
        StringInstanceSPMap::iterator cimItr = get_class_name_instance_sp_map().find(className);
        if (cimItr != get_class_name_instance_sp_map().end()) {
            cimItr->second->subscribeObject(rtiAmbassador);
        }
    }

    static void unsubscribe_object(const std::string &className, RTI::RTIambassador *rtiAmbassador) {
        StringInstanceSPMap::iterator cimItr = get_class_name_instance_sp_map().find(className);
        if (cimItr != get_class_name_instance_sp_map().end()) {
            cimItr->second->unsubscribeObject(rtiAmbassador);
        }
    }

    //---------------------------
    // END CLASS-NAME ROOT-SP MAP
    //---------------------------


    //----------------------------
    // CLASS-HANDLE CLASS-NAME MAP
    //----------------------------
protected:
    static IntegerStringMap &get_class_handle_name_map() {
        static IntegerStringMap classHandleNameMap;
        return classHandleNameMap;
    }

    //--------------------------------------------------
    // METHODS THAT USE ONLY CLASS-HANDLE CLASS-NAME MAP
    //--------------------------------------------------
public:
    static const std::string get_hla_class_name(int classHandle) {
        IntegerStringMap::iterator ismItr = get_class_handle_name_map().find(classHandle);
        return ismItr == get_class_handle_name_map().end() ? "" : ismItr->second;
    }

    static SP create_object(int classHandle) {
        IntegerStringMap::iterator ismItr = get_class_handle_name_map().find(classHandle);
        return ismItr == get_class_handle_name_map().end()
          ? SP() : create_object(ismItr->second);
    }

    static SP create_object(int classHandle, const RTIfedTime &rtiFedTime) {
        IntegerStringMap::iterator ismItr = get_class_handle_name_map().find(classHandle);
        return ismItr == get_class_handle_name_map().end()
          ? SP() : create_object(ismItr->second, rtiFedTime);
    }

    static SP create_object(int classHandle, const RTI::AttributeHandleValuePairSet &datamemberMap);
    static SP create_object(int classHandle, const RTI::AttributeHandleValuePairSet &datamemberMap, const RTIfedTime &rtiFedTime);

    //------------------------------------------------------
    // END METHODS THAT USE ONLY CLASS-HANDLE CLASS-NAME MAP
    //------------------------------------------------------


    //--------------
    // OBJECT HANDLE
    //--------------
private:
    int _objectHandle;

    //------------------------------------
    // METHODS THAT USE ONLY OBJECT HANDLE
    //------------------------------------
public:
    int getObjectHandle() {
        return _objectHandle;
    }

    //----------------------------------------
    // END METHODS THAT USE ONLY OBJECT HANDLE
    //----------------------------------------


    //-----------
    // OBJECT MAP
    //-----------
private:
    static ObjectHandleInstanceSPMap &get_object_handle_instance_sp_map() {
        static ObjectHandleInstanceSPMap objectHandleInstanceSPMap;
        return objectHandleInstanceSPMap;
    }

    //---------------------------------
    // METHODS THAT USE ONLY OBJECT MAP
    //---------------------------------
public:
    static SP get_object( int object_handle ) {
        ObjectHandleInstanceSPMap::iterator oimItr = get_object_handle_instance_sp_map().find( object_handle );
        return oimItr == get_object_handle_instance_sp_map().end() ? SP() : oimItr->second;
    }

    static SP remove_object( int object_handle ) {
        SP objectRootSP = get_object( object_handle );
        get_object_handle_instance_sp_map().erase( object_handle );
        return objectRootSP;
    }

    static SP reflect( int object_handle, const RTI::AttributeHandleValuePairSet &datamemberMap ) {
        SP objectRootSP = get_object( object_handle );
        if ( !objectRootSP ) {
            return objectRootSP;
        }

        objectRootSP->setTime( -1 );
        objectRootSP->setAttributes( datamemberMap );
        return objectRootSP;
    }

    static SP reflect(
      int object_handle, const RTI::AttributeHandleValuePairSet &datamemberMap, const RTIfedTime &rtiFedTime
    ) {
        SP objectRootSP = get_object( object_handle );
        if ( !objectRootSP ) {
            return objectRootSP;
        }

        objectRootSP->setTime( rtiFedTime.getTime() );
        objectRootSP->setAttributes( datamemberMap );
        return objectRootSP;
    }

    static SP reflect( int object_handle, const RTI::AttributeHandleValuePairSet &datamemberMap, double theTime ) {
        SP objectRootSP = get_object( object_handle );
        if ( !objectRootSP ) {
            return objectRootSP;
        }

        objectRootSP->setTime( theTime );
        objectRootSP->setAttributes( datamemberMap );
        return objectRootSP;
    }

    //-------------------------------------
    // END METHODS THAT USE ONLY OBJECT MAP
    //-------------------------------------


    //---------------------------------------------------
    // METHODS THAT USE BOTH OBJECT MAP AND OBJECT HANDLE
    //---------------------------------------------------
private:
    void setObjectHandle( int object_handle ) {
        remove_object( object_handle );
        _objectHandle = object_handle;
        get_object_handle_instance_sp_map().insert(  std::make_pair( object_handle, SP(this) )  );
    }

    //-------------------------------------------------------
    // END METHODS THAT USE BOTH OBJECT MAP AND OBJECT HANDLE
    //-------------------------------------------------------


    //--------------------------------------------------------------------------------------------------
    // METHODS THAT USE OBJECT MAP, OBJECT HANDLE, CLASS-NAME CLASS MAP, AND CLASS-HANDLE CLASS-NAME MAP
    //--------------------------------------------------------------------------------------------------
public:
    static SP discover( int class_handle, int object_handle ) {
        SP objectRootSP = create_object( class_handle );
        if (objectRootSP) {
            get_object_handle_instance_sp_map().insert( std::make_pair(object_handle, objectRootSP) );
        }
        return objectRootSP;
    }

    //------------------------------------------------------------------------------------------------------
    // END METHODS THAT USE OBJECT MAP, OBJECT HANDLE, CLASS-NAME CLASS MAP, AND CLASS-HANDLE CLASS-NAME MAP
    //------------------------------------------------------------------------------------------------------

    //-------------------------
    // END CLASS-NAME CLASS MAP
    //-------------------------

    //--------------------------------
    // END CLASS-HANDLE CLASS-NAME MAP
    //--------------------------------

    //--------------
    // IS REGISTERED
    //--------------
private:
    bool _isRegistered = false;

    //--------------------------------------------------------------
    // METHODS THAT USE OBJECT MAP, OBJECT HANDLE, AND IS REGISTERED
    //--------------------------------------------------------------
public:
    void registerObject( RTI::RTIambassador *rti ) override;

    void registerObject( RTI::RTIambassador *rti, const std::string &name ) override;

    void unregisterObject( RTI::RTIambassador *rti ) override;

    //------------------------------------------------------------------
    // END METHODS THAT USE OBJECT MAP, OBJECT HANDLE, AND IS REGISTERED
    //------------------------------------------------------------------

    //------------------
    // END IS REGISTERED
    //------------------

    //---------------
    // END OBJECT MAP
    //---------------

    //------------------
    // END OBJECT HANDLE
    //------------------

private:
    static void get_class_pub_sub_class_and_property_name_sp(
      const StringClassAndPropertyNameSetSPMap &stringClassAndPropertyNameSetSPMap,
      const std::string &className,
      const std::string &attributeName,
      bool publish,
      bool insert
    ) {
        StringClassAndPropertyNameSetSPMap::const_iterator samItr =
          stringClassAndPropertyNameSetSPMap.find( className );
        if ( samItr == stringClassAndPropertyNameSetSPMap.end() ) {
            // ERROR
            return;
        }

        ClassAndPropertyNameSP classAndPropertyNameSP = findProperty(className, attributeName);
        if (!classAndPropertyNameSP) {
            // ERROR
            return;
        }

        if (insert) {
            samItr->second->insert(*classAndPropertyNameSP);
        } else {
            samItr->second->erase(*classAndPropertyNameSP);
        }
    }

    //----------------------------------------
    // CLASS-NAME PUBLISHED-ATTRIBUTE-NAME SET
    //----------------------------------------
protected:
    static StringClassAndPropertyNameSetSPMap &get_class_name_published_attribute_name_set_sp_map() {
        static StringClassAndPropertyNameSetSPMap classNamePublishedAttributeNameSetSPMap;
        return classNamePublishedAttributeNameSetSPMap;
    }

    //---------------------------------------------------------
    // METHODS THAT USE CLASS-NAME PUBLISHED-ATTRIBUTE-NAME SET
    //---------------------------------------------------------
public:
    static void publish_attribute( const std::string &className, const std::string &attributeName ) {
        get_class_pub_sub_class_and_property_name_sp(
          get_class_name_published_attribute_name_set_sp_map(), className, attributeName, true, true
        );
    }

    static void unpublish_attribute( const std::string &className, const std::string &attributeName ) {
        get_class_pub_sub_class_and_property_name_sp(
          get_class_name_published_attribute_name_set_sp_map(), className, attributeName, true, false
        );
    }

    //--------------------------------------------
    // END CLASS-NAME PUBLISHED-ATTRIBUTE-NAME SET
    //--------------------------------------------


    //-----------------------------------------
    // CLASS-NAME SUBSCRIBED-ATTRIBUTE-NAME SET
    //-----------------------------------------
protected:
    static StringClassAndPropertyNameSetSPMap &get_class_name_subscribed_attribute_name_set_sp_map() {
        static StringClassAndPropertyNameSetSPMap classNameSubscribedAttributeNameSetSPMap;
        return classNameSubscribedAttributeNameSetSPMap;
    }

    //---------------------------------------------------------
    // METHODS THAT USE CLASS-NAME SUBSCRIBED-ATTRIBUTE-NAME SET
    //---------------------------------------------------------
public:
    static void subscribe_attribute( const std::string &className, const std::string &attributeName ) {
        get_class_pub_sub_class_and_property_name_sp(
          get_class_name_published_attribute_name_set_sp_map(), className, attributeName, false, true
        );
    }

    static void unsubscribe_attribute( const std::string &className, const std::string &attributeName ) {
        get_class_pub_sub_class_and_property_name_sp(
          get_class_name_published_attribute_name_set_sp_map(), className, attributeName, false, false
        );
    }

    //---------------------------------------------
    // END CLASS-NAME SUBSCRIBED-ATTRIBUTE-NAME SET
    //---------------------------------------------


    //-------------------------------------------------------------------------------------------------
    // CLASS-NAME PUBLISHED-ATTRIBUTE-HANDLE-SET MAP AND CLASS-NAME SUBSCRIBED-ATTRIBUTE-HANDLE-SET MAP
    //-------------------------------------------------------------------------------------------------
protected:
    static StringAttributesHandleSetSPMap &get_class_name_published_attribute_handle_set_sp_map() {
        static StringAttributesHandleSetSPMap classNamePublishedAttributesHandleSetSPMap;
        return  classNamePublishedAttributesHandleSetSPMap;
    }

    static StringAttributesHandleSetSPMap &get_class_name_subscribed_attribute_handle_set_sp_map() {
        static StringAttributesHandleSetSPMap classNameSubscribedAttributesHandleSetSPMap;
        return  classNameSubscribedAttributesHandleSetSPMap;
    }

    //-----------------------------------------------------------------------------------------------------
    // END CLASS-NAME PUBLISHED-ATTRIBUTE-HANDLE-SET MAP AND CLASS-NAME SUBSCRIBED-ATTRIBUTE-HANDLE-SET MAP
    //-----------------------------------------------------------------------------------------------------

    void requestUpdate( RTI::RTIambassador *rti );


    //-------------------------------------------
    // CLASS-AND-PROPERTY-NAME PROPERTY-VALUE MAP
    //-------------------------------------------
protected:
    ClassAndPropertyNameValueSPMap _classAndPropertyNameValueSPMap;

    //-----------------------------------------------------------------------------------------------------------
    // PROPERTY-CLASS-NAME AND PROPERTY-VALUE DATA CLASS
    // THIS CLASS IS USED ESPECIALLY FOR THE BENEFIT OF THE SET METHOD BELOW.  WHEN A VALUE IS RETRIEVED FROM THE
    // classPropertyNameValueMap USING A GET METHOD, IT IS PAIRED WITH THE NAME OF THE CLASS IN WHICH THE
    // PROPERTY IS DEFINED. IN THIS WAY, THE SET METHOD CAN PLACE THE NEW VALUE FOR THE PROPERTY USING THE
    // CORRECT (CLASS-NAME, PROPERTY-NAME) KEY.
    //-----------------------------------------------------------------------------------------------------------
    class PropertyClassNameAndValue {
    private:
        const std::string className;
        const ValueSP valueSP;

    public:
        PropertyClassNameAndValue(const std::string &className, const ValueSP &localValueSP) :
         className(className), valueSP(localValueSP) {}

        const std::string &getClassName() const {
            return className;
        }

        const ValueSP &getValueSP() const {
            return valueSP;
        }
    };

    typedef boost::shared_ptr<PropertyClassNameAndValue> PropertyClassNameAndValueSP;

    //------------------------------------------------------------
    // METHODS THAT USE CLASS-AND-PROPERTY-NAME PROPERTY-VALUE MAP
    //------------------------------------------------------------
public:
    const ClassAndPropertyNameValueSPMap &getClassAndPropertyNameValueSPMap() const {
        return _classAndPropertyNameValueSPMap;
    }

    template<typename T>
    void setAttribute(const std::string &propertyName, const T &value) {

        PropertyClassNameAndValueSP propertyClassNameAndValueSP =
          getAttributeAux(getHlaClassName(), propertyName);

        if (!propertyClassNameAndValueSP) {
//            logger.error(
//              "setattribute(\"{}\", {} value): could not find \"{}\" attribute of class \"{}\" or its " +
//              "superclasses.", propertyName, value.getClass().getName(), propertyName, getHlaClassName()
//            );
            return;
        }

        Value currentValue = *propertyClassNameAndValueSP->getValueSP();

        if (!currentValue.setValue(value)) {
//            logger.error(
//              "setattribute(\"{}\", {} value): \"value\" is incorrect type \"{}\" for \"{}\" parameter, " +
//              "should be of type \"{}\".",
//              propertyName,
//              value.getClass().getName(),
//              value.getClass().getName(),
//              propertyName,
//              currentValue.getClass().getName()
//            );
        }
    }

    template<typename T>
    void setAttribute(int propertyHandle, const T &value) {

        IntegerClassAndPropertyNameSPMap::iterator hcmItr =
          get_handle_class_and_property_name_sp_map().find(propertyHandle);

        if (hcmItr == get_handle_class_and_property_name_sp_map().end()) {
//            logger.error(
//              "setAttribute(int, Object value): propertyHandle {} does not exist.",
//              propertyHandle
//            );
            return;
        }

        Value &currentValue = *_classAndPropertyNameValueSPMap[*hcmItr->second];
        if (!currentValue.setValue(value)) {
//            logger.error(
//                "setAttribute: propertyHandle {} corresponds to property of name \"{}\", which " +
//                "does not exist in class \"{}\" (it's defined in class\"{}\")",
//                propertyHandle, propertyName, getClass(), classAndPropertyName.getClassName()
//            );
        }
    }

    //
    // getAttributeAux METHODS ARE DEFINED IN SUBCLASSES.
    //

    /**
     * Returns the value of the attribute named "propertyName" for this
     * object.
     *
     * @param propertyName name of attribute whose value to retrieve
     * @return the value of the attribute whose name is "propertyName"
     */
    const Value &getAttribute(const std::string &propertyName) const override {
        return *getAttributeAux(getHlaClassName(), propertyName)->getValueSP();
    }

    /**
     * Returns the value of the attribute whose handle is "propertyHandle"
     * (RTI assigned) for this object.
     *
     * @param propertyHandle handle (RTI assigned) of attribute whose
     * value to retrieve
     * @return the value of the attribute whose handle is "propertyHandle"
     */
    const Value &getAttribute( int propertyHandle ) const override;

    //---------------------------------------------------
    // END CLASS-AND-PROPERTY-NAME PROPERTY-VALUE MAP
    //---------------------------------------------------


    //---------------------------
    // START OF INCLUDED TEMPLATE
    //---------------------------



    // ----------------------------------------------------------------------------
    // STATIC DATAMEMBERS AND CODE THAT DEAL WITH NAMES
    // THIS CODE IS STATIC BECAUSE IT IS CLASS-DEPENDENT AND NOT INSTANCE-DEPENDENT
    // ----------------------------------------------------------------------------

public:
    /**
     * Returns the fully-qualified (dot-delimited) name of the org.cpswt.hla.ObjectRoot object class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the name of the class pertaining to the reference,
     * rather than the name of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getJavaClassName()}.
     *
     * @return the fully-qualified Java class name for this object class
     */
    static const std::string &get_cpp_class_name() {
        static const std::string cppClassName("::org::cpswt::hla::ObjectRoot");
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
     * class name) of the org.cpswt.hla.ObjectRoot object class.
     *
     * @return the name of this object class
     */
    static const std::string &get_simple_class_name() {
        static const std::string simpleClassName("ObjectRoot");
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
     * ObjectRoot object class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the federation name of the class pertaining to the reference,
     * rather than the name of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getHlaClassName()}.
     *
     * @return the fully-qualified federation (HLA) class name for this object class
     */
    static const std::string &get_hla_class_name() {
        static const std::string hlaClassName("ObjectRoot");
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
     * org.cpswt.hla.ObjectRoot object class.
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
     * org.cpswt.hla.ObjectRoot object class.
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
     * Returns the handle (RTI assigned) of the org.cpswt.hla.ObjectRoot object class.
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
     * this object class (i.e. "org.cpswt.hla.ObjectRoot") given the attribute's name.
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
          RTI::AttributeHandleSetFactory::create( 0 )
        );
        return publishedAttributeHandleSetSP;
    }

    static AttributeHandleSetSP get_subscribed_attribute_handle_set_sp() {
        static AttributeHandleSetSP subscribedAttributeHandleSetSP(
          RTI::AttributeHandleSetFactory::create( 0 )
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
     * Publishes the org.cpswt.hla.ObjectRoot object class for a federate.
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
     * Unpublishes the org.cpswt.hla.ObjectRoot object class for a federate.
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
 * Subscribes a federate to the org.cpswt.hla.ObjectRoot object class.
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
     * Unsubscribes a federate from the org.cpswt.hla.ObjectRoot object class.
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
     * (that is, the org.cpswt.hla.ObjectRoot object class).
     *
     * @param handle handle to compare to the value of the handle (RTI assigned) of
     * this class (the org.cpswt.hla.ObjectRoot object class).
     * @return "true" if "handle" matches the value of the handle of this class
     * (that is, the org.cpswt.hla.ObjectRoot object class).
     */
    static bool match(int handle) {
        return handle == get_class_handle();
    }


    //--------------------------------
    // DATAMEMBER MANIPULATION METHODS
    //--------------------------------
public:

protected:
    virtual PropertyClassNameAndValueSP getAttributeAux(
      const std::string &className, const std::string &propertyName
    ) const;

    //------------------------------------
    // END DATAMEMBER MANIPULATION METHODS
    //------------------------------------

    //-------------
    // CONSTRUCTORS
    //-------------
    
    ObjectRoot(): _uniqueId(generate_unique_id()) {
    }

    ObjectRoot( const PropertyHandleValuePairSet &propertyMap ): _uniqueId(generate_unique_id()) {
        setAttributes(propertyMap);
    }

    ObjectRoot( const RTIfedTime &rtiFedTime ): _uniqueId(generate_unique_id()) {
    }

    ObjectRoot(const PropertyHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime):
      _uniqueId(generate_unique_id()) {
        setAttributes(propertyMap);
        setTime(rtiFedTime);
    }


    //--------------------------
    // INSTANCE CREATION METHODS
    //--------------------------
public:
    static SP create() {
        return SP(new ObjectRoot());
    }

    static SP create_object() {
        return SP(new ObjectRoot());
    }

    virtual SP createObject() {
        return create_object();
    }

    static SP create(
      const RTI::AttributeHandleValuePairSet &propertyMap
    ) {
        return SP(new ObjectRoot(propertyMap));
    }

    static SP create_object(
      const RTI::AttributeHandleValuePairSet &propertyMap
    ) {
        return SP(new ObjectRoot(propertyMap));
    }

    virtual SP createObject(
      const RTI::AttributeHandleValuePairSet &propertyMap
    ) {
        return create_object(propertyMap);
    }

    static SP create(const RTIfedTime &rtiFedTime) {
        return SP(new ObjectRoot(rtiFedTime));
    }

    static SP create_object(const RTIfedTime &rtiFedTime) {
        return SP(new ObjectRoot(rtiFedTime));
    }

    virtual SP createObject(const RTIfedTime &rtiFedTime) {
        return create_object(rtiFedTime);
    }

    static SP create(
      const RTI::AttributeHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) {
        return SP(new ObjectRoot(propertyMap, rtiFedTime));
    }

    static SP create_object(
      const RTI::AttributeHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) {
        return SP(new ObjectRoot(propertyMap, rtiFedTime));
    }

    virtual SP createObject(
      const RTI::AttributeHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime) {
        return create_object(propertyMap, rtiFedTime);
    }

    virtual SP cloneObject() {
        return SP( new ObjectRoot( *this )  );
    }

    //------------------------------
    // END INSTANCE CREATION METHODS
    //------------------------------


    //-------------------------
    // END OF INCLUDED TEMPLATE
    //-------------------------


    //-------------
    // TIME SET/GET
    //-------------
private:
    double _time = -1;

    /**
     * Returns the timestamp for this object.  "receive order" objects
     * should have a timestamp of -1.
     *
     * @return timestamp for this object
     */
public:
    double getTime() {
        return _time;
    }

    /**
     * Sets the timestamp of this object to "time".
     *
     * @param time new timestamp for this object
     */
    void setTime( double time ) {
        _time = time;
    }

    /**
     * Sets the timestamp of this object to "logicalTime".
     *
     * @param logicalTime new timestamp for this object
     */
    void setTime( const RTIfedTime &rtiFedTime ) override {
        setTime( rtiFedTime.getTime() );
    }

    //-----------------
    // END TIME SET/GET
    //-----------------

    //-------------
    // CONSTRUCTORS
    //-------------

    /**
     * Creates a new ObjectRoot instance.
     */
// private:
//     void setAttribute(int propertyHandle, const std::string &value) {
//         ClassAndPropertyNameSP classAndPropertyNameSP = get_class_and_attribute_name(propertyHandle);
//         if (!classAndPropertyNameSP) {
//             // ERROR
//             return;
//         }
//         const ClassAndPropertyName &classAndPropertyName = *classAndPropertyNameSP;
//         _classAndPropertyNameValueSPMap[classAndPropertyName]->setValue(value);
//     }

public:
    void setAttributes( const RTI::AttributeHandleValuePairSet &propertyMap );

protected:


    /**
     * Creates a new object instance and initializes its attributes
     * using the "propertyMap" -- this constructor is usually called as a
     * super-class constructor to create and initialize an instance of an
     * object further down in the inheritance hierarchy.  "propertyMap"
     * is usually acquired as an argument to an RTI federate callback method, such
     * as "receiveInteraction".
     *
     * @param propertyMap contains attribute values for the newly created
     * object
     */
public:
    /**
     * Like {@link #ObjectRoot( const RTI::AttributeHandleValuePairSet &propertyMap )},
     * except the new instance has an initial timestamp of "logicalTime".
     *
     * @param propertyMap contains attribute values for the newly created
     * object
     * @param logicalTime initial timestamp for newly created object instance
     */

    //-----------------
    // END CONSTRUCTORS
    //-----------------

public:

    PropertyHandleValuePairSetSP createPropertyHandleValuePairSetSP( bool force );

    void updateAttributeValues( RTI::RTIambassador *rti, double time, bool force );

    void updateAttributeValues( RTI::RTIambassador *rti, double time ) {
        updateAttributeValues( rti, time, false );
    }

    void updateAttributeValues( RTI::RTIambassador *rti, bool force );

    void updateAttributeValues( RTI::RTIambassador *rti ) {
        updateAttributeValues( rti, false );
    }

    std::string toJson();

    static void fromJson(const std::string &jsonString);


public:
    static ClassAndPropertyNameSP get_attribute_name( int propertyHandle ) {
        IntegerClassAndPropertyNameSPMap::iterator icmItr =
          get_handle_class_and_property_name_sp_map().find( propertyHandle );
        return icmItr == get_handle_class_and_property_name_sp_map().end() ? ClassAndPropertyNameSP() : icmItr->second;
    }

};
  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"

std::ostream &operator<<( std::ostream &os, const ::org::cpswt::hla::ObjectRoot &messaging );
inline std::ostream &operator<<( std::ostream &os, ::org::cpswt::hla::ObjectRoot::SP messagingSP ) {
    return os << *messagingSP;
}

#endif // _OBJECT_ROOT