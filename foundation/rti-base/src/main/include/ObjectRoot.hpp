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


#ifndef _OBJECT_ROOT_CLASS
#define _OBJECT_ROOT_CLASS

#define BOOST_LOG_DYN_LINK

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <unordered_map>
#include <list>
#include <cctype>
#include <cstdlib>
#include <typeinfo>

#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string.hpp>

#include <boost/log/expressions/keyword.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

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

namespace logging = boost::log;
namespace logging_source = boost::log::sources;
namespace attrs = boost::log::attributes;

using namespace logging::trivial;

class ObjectRoot : public ObjectRootInterface {

public:
    typedef logging_source::severity_logger< severity_level > severity_logger;

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
    typedef std::map<std::string, bool> StringBooleanMap;
    
    typedef boost::shared_ptr<StringSet> StringSetSP;
    typedef std::map<std::string, StringSetSP> StringStringSetSPMap;

    typedef RTI::AttributeHandleSet AttributeHandleSet;
    typedef boost::shared_ptr<AttributeHandleSet> AttributeHandleSetSP;

    typedef std::map<std::string, SP> StringInstanceSPMap;

    typedef Attribute Value;

    typedef boost::shared_ptr<Value> ValueSP;
    typedef std::unordered_map<ClassAndPropertyName, ValueSP> ClassAndPropertyNameValueSPMap;

    typedef void (*PubsubFunctionPtr)( RTI::RTIambassador * );
    typedef std::map< std::string, PubsubFunctionPtr > ClassNamePubSubMap;
    typedef std::map< std::string, std::string> PropertyTypeMap;typedef std::map< std::string, AttributeHandleSetSP > StringAttributesHandleSetSPMap;
    typedef std::unordered_map< int, SP > ObjectHandleInstanceSPMap;
    typedef std::set<int> IntegerSet;
    typedef boost::shared_ptr<IntegerSet> IntegerSetSP;
    typedef std::map<std::string, IntegerSetSP> StringIntegerSetSPMap;

protected:
    static void defaultSleep() {
#ifdef _WIN32
        Sleep( 500 );
#else
        usleep( 500000 );
#endif
    }

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

private:
    static bool &get_is_initialized_aux() {
        static bool isInitialized = false;
        return isInitialized;
    }

    static bool get_is_initialized() {
        return get_is_initialized_aux();
    }

    static void set_is_initialized() {
        get_is_initialized_aux() = true;
    }

    static StringBooleanMap &get_hla_class_name_is_initialized_map() {
        static StringBooleanMap hlaClassNameIsInitializedMap;
        return hlaClassNameIsInitializedMap;
    }

    static bool get_hla_class_name_is_initialized(const std::string &hlaClassName) {
        StringBooleanMap::const_iterator sbmCit = get_hla_class_name_is_initialized_map().find(hlaClassName);
        return sbmCit == get_hla_class_name_is_initialized_map().end() ? false : sbmCit->second;
    }

    static void set_hla_class_name_is_initialized(const std::string &hlaClassName) {
        get_hla_class_name_is_initialized_map()[hlaClassName] = true;
    }

public:
    static void init(const std::string &hlaClassName, RTI::RTIambassador *rtiAmbassador);

    static void init(RTI::RTIambassador *rtiAmbassador) {
        if (get_is_initialized()) {
            return;
        }
        set_is_initialized();

        //-------------------------------------------------------------------------
        // hlaClassNameSet (get_hla_class_name_set()) IS POPULATED BY
        // - STATIC INITIALIZATION BLOCKS IN THE DERIVED INTERACTION/OBJECT CLASSES
        // - THE DYNAMIC-MESSAGE-CLASSES FILE
        //-------------------------------------------------------------------------
        for(const std::string &hlaClassName: get_hla_class_name_set()) {
            init(hlaClassName, rtiAmbassador);
        }
    }

private:
    std::string _instanceHlaClassName;
    
public:
    const std::string &getInstanceHlaClassName() const {
        return _instanceHlaClassName;
    }

    bool isInstanceOfHlaClass( const std::string &hlaClassName ) {
        return getInstanceHlaClassName() == hlaClassName;
    }

    bool isInstanceHlaClassDerivedFromHlaClass( const std::string &hlaClassName ) {
        std::string prefix = hlaClassName + ".";
        return isInstanceOfHlaClass( hlaClassName ) || getInstanceHlaClassName().substr(0, prefix.length()) == prefix;
    }

protected:
    void setInstanceHlaClassName(const std::string &instanceHlaClassName) {
        _instanceHlaClassName = instanceHlaClassName;
    }

public:
    static std::string get_simple_class_name(const std::string &hlaClassName) {
        size_t position = hlaClassName.find_last_of('.');
        return position == std::string::npos ? hlaClassName : hlaClassName.substr(position + 1);
    }

private:
    static ClassAndPropertyNameValueSPMap getClassAndPropertyNameValueSPMap(
      const RTI::AttributeHandleValuePairSet &propertyMap
    );

public:
    class ObjectReflector {
    public:
        typedef boost::shared_ptr<ObjectReflector> SP;

    private:
        RTI::ObjectHandle _objectHandle;
        std::string _hlaClassName;
        std::string _federateSequence;
        ClassAndPropertyNameValueSPMap _classAndPropertyNameValueSPMap;
        double _time;

        void initHlaClassName() {
            ObjectRoot::SP objectRootSP = get_object( _objectHandle );
            if (objectRootSP) {
                _hlaClassName = objectRootSP->getInstanceHlaClassName();
            }
        }

    public:
//        ObjectReflector() : _objectHandle(0), _time(-1), _federateSequence("[]") { }

        ObjectReflector(
         RTI::ObjectHandle objectHandle, const ClassAndPropertyNameValueSPMap &classAndPropertyNameValueSPMap
        ) :
         _objectHandle(objectHandle),
         _federateSequence("[]"),
         _classAndPropertyNameValueSPMap( classAndPropertyNameValueSPMap ),
         _time(-1) {
            initHlaClassName();
        }

        ObjectReflector(
         RTI::ObjectHandle objectHandle,
         const RTI::AttributeHandleValuePairSet& theAttributes
        ) :
         _objectHandle(objectHandle),
         _federateSequence("[]"),
         _classAndPropertyNameValueSPMap(ObjectRoot::getClassAndPropertyNameValueSPMap(theAttributes)),
         _time(-1) {
            initHlaClassName();
        }


        ObjectReflector(
         RTI::ObjectHandle objectHandle,
         const ClassAndPropertyNameValueSPMap &classAndPropertyNameValueSPMap,
         double time
        ) :
         _objectHandle( objectHandle ),
         _federateSequence("[]"),
         _classAndPropertyNameValueSPMap( classAndPropertyNameValueSPMap ),
         _time( time ) {
            initHlaClassName();
        }

        ObjectReflector(
         RTI::ObjectHandle objectHandle,
         const RTI::AttributeHandleValuePairSet& theAttributes,
         double time
        ) :
         _objectHandle( objectHandle ),
         _federateSequence("[]"),
         _classAndPropertyNameValueSPMap(ObjectRoot::getClassAndPropertyNameValueSPMap(theAttributes)),
         _time( time ) {
            initHlaClassName();
        }


        ObjectReflector(
         RTI::ObjectHandle objectHandle,
         const ClassAndPropertyNameValueSPMap &classAndPropertyNameValueSPMap,
         const RTI::FedTime &fedTime
        ) :
         _objectHandle( objectHandle ),
         _federateSequence("[]"),
         _classAndPropertyNameValueSPMap( classAndPropertyNameValueSPMap ),
         _time(  RTIfedTime( fedTime ).getTime()  ) {
            initHlaClassName();
        }

        ObjectReflector(
         RTI::ObjectHandle objectHandle,
         const RTI::AttributeHandleValuePairSet& theAttributes,
         const RTI::FedTime &fedTime
        ) :
         _objectHandle( objectHandle ),
         _federateSequence("[]"),
         _classAndPropertyNameValueSPMap(ObjectRoot::getClassAndPropertyNameValueSPMap(theAttributes)),
          _time(  RTIfedTime( fedTime ).getTime()  ) {
            initHlaClassName();
         }

        void reflect() const {
            if ( _time < 0 ) ObjectRoot::reflect( _objectHandle, _classAndPropertyNameValueSPMap );
            else  ObjectRoot::reflect( _objectHandle, _classAndPropertyNameValueSPMap, _time );
        }

        const ClassAndPropertyNameValueSPMap &getClassAndPropertyNameValueSPMap() const {
            return _classAndPropertyNameValueSPMap;
        }

        RTI::ObjectHandle getObjectHandle() const {
            return _objectHandle;
        }

        const std::string &getHlaClassName() const {
            return _hlaClassName;
        }

        void setFederateSequence(const std::string &federateSequence) {
            _federateSequence = federateSequence;
        }

        const std::string &getFederateSequence() const {
            return _federateSequence;
        }

        std::string toJson() const;

        ObjectRoot::SP getObjectRootSP() const {
            return ObjectRoot::get_object( _objectHandle );
        }

        double getTime() const {
            return _time;
        }
    };

    class ObjectReflectorSPComparator {
    public:
        bool operator()(const ObjectReflector::SP &objectReflectorSP1, const ObjectReflector::SP &objectReflectorSP2) {
            return objectReflectorSP1->getTime() < objectReflectorSP2->getTime();
        }
    };

    //-------------------------------------------------------------------------
    // HLA CLASS-NAME SET
    //
    // POPULATED BY:
    // - STATIC INITIALIZATION BLOCKS IN THE DERIVED INTERACTION/OBJECT CLASSES
    // - THE DYNAMIC-MESSAGE-CLASSES FILE
    //-------------------------------------------------------------------------
protected:
    static StringSet &get_hla_class_name_set() {
        static StringSet hlaClassNameSet;
        return hlaClassNameSet;
    }

    //--------------------------------------------------------------------------
    // METHODS THAT USE HLA CLASS-NAME-SET
    //
    // ALSO USED BY:
    // - ObjectRoot( const std::string &hlaClassName ) DYNAMIC CONSTRUCTOR
    // - readFederateDynamicMessageClasses(Reader reader) BELOW
    //--------------------------------------------------------------------------
public:
    static const StringSet &get_object_hla_class_name_set() {
        return get_hla_class_name_set();
    }

    //-----------------------
    // END HLA CLASS-NAME-SET
    //-----------------------

    //---------------------------
    // DYNAMIC HLA CLASS-NAME SET
    //---------------------------
private:
    static StringSet &get_dynamic_hla_class_name_set_aux() {
        static StringSet dynamicHlaClassNameSet;
        return dynamicHlaClassNameSet;
    }

    //--------------------------------------------
    // METHODS THAT USE DYNAMIC HLA CLASS-NAME SET
    //--------------------------------------------
public:
    static const StringSet &get_dynamic_hla_class_name_set() {
        return get_dynamic_hla_class_name_set_aux();
    }

    static bool is_dynamic_class(const std::string &hlaClassName) {
        return get_dynamic_hla_class_name_set().find(hlaClassName) != get_dynamic_hla_class_name_set().end();
    }

    bool isDynamicInstance() {
        return getHlaClassName() != getInstanceHlaClassName();
    }

    //-------------------------------
    // END DYNAMIC HLA CLASS-NAME SET
    //-------------------------------

    //-------------------------------------------------------------------------
    // CLASS-NAME PROPERTY-NAME-SET MAP
    //
    // POPULATED BY:
    // - STATIC INITIALIZATION BLOCKS IN THE DERIVED INTERACTION/OBJECT CLASSES
    // - THE DYNAMIC-MESSAGE-CLASSES FILE
    //-------------------------------------------------------------------------
protected:
    static StringClassAndPropertyNameSetSPMap &get_class_name_class_and_property_name_set_sp_map() {
        static StringClassAndPropertyNameSetSPMap classNamePropertyNameSetSPMap;
        return classNamePropertyNameSetSPMap;
    }

    //---------------------------------------------------------
    // METHODS THAT USE CLASS-NAME PROPERTY-NAME-SET MAP
    //
    // ALSO USED BY:
    // - readFederateDynamicMessageClasses(Reader reader) BELOW
    //---------------------------------------------------------
public:
    static ClassAndPropertyNameList get_attribute_names(const std::string &hlaClassName) {
       StringClassAndPropertyNameSetSPMap::iterator scmItr =
         get_class_name_class_and_property_name_set_sp_map().find(hlaClassName);

       const ClassAndPropertyNameSet &classAndPropertyNameSet =
         scmItr == get_class_name_class_and_property_name_set_sp_map().end() ?
           *ClassAndPropertyNameSetSP(new ClassAndPropertyNameSet()) : *scmItr->second;

       ClassAndPropertyNameList classAndPropertyNameList(
         classAndPropertyNameSet.begin(), classAndPropertyNameSet.end()
       );

       classAndPropertyNameList.sort();
       return classAndPropertyNameList;
    }

    //-------------------------------------
    // END CLASS-NAME PROPERTY-NAME-SET MAP
    //-------------------------------------

    //-------------------------------------
    // CLASS-NAME ALL-PROPERTY-NAME-SET MAP
    //-------------------------------------
protected:
    static StringClassAndPropertyNameSetSPMap &get_class_name_all_class_and_property_name_set_sp_map() {
        static StringClassAndPropertyNameSetSPMap classNameAllPropertyNameSetSPMap;
        return classNameAllPropertyNameSetSPMap;
    }

    //------------------------------------------------------
    // METHODS THAT USE CLASS-NAME ALL-PROPERTY-NAME-SET MAP
    //------------------------------------------------------
public:
    static const ClassAndPropertyNameList get_all_attribute_names(const std::string &hlaClassName) {
        StringClassAndPropertyNameSetSPMap::iterator scmItr =
          get_class_name_all_class_and_property_name_set_sp_map().find(hlaClassName);

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
    // END CLASS-NAME All-PROPERTY-NAME-SET MAP
    //-------------------------------------------

    //----------------------------
    // CLASS-NAME CLASS-HANDLE MAP
    //
    // POPULATED BY:
    // - init(RTIambassador) ABOVE
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
    static int get_class_handle(const std::string &hlaClassName) {
        StringIntegerMap::iterator simItr = get_class_name_handle_map().find(hlaClassName);
        if (simItr == get_class_name_handle_map().end()) {
            BOOST_LOG_SEV( get_logger(), error ) << "Could not get handle for hla class \"" <<
              hlaClassName << "\":  class not defined";
            return -1;
        }
        return simItr->second;
    }

    static int get_class_handle(const char *hlaClassName) {
        return get_class_handle(std::string(hlaClassName));
    }

    //--------------------------------
    // END CLASS-NAME CLASS-HANDLE MAP
    //--------------------------------

    //----------------------------
    // CLASS-HANDLE CLASS-NAME MAP
    //
    // POPULATED BY:
    // - init(RTIambassador) ABOVE
    //----------------------------
protected:
    static IntegerStringMap &get_class_handle_name_map() {
        static IntegerStringMap classHandleNameMap;
        return classHandleNameMap;
    }

    //--------------------------------------------------
    // METHODS THAT USE ONLY CLASS-HANDLE CLASS-NAME MAP
    //
    // ALSO USED BY:
    // - discover(class_handle, object_handle ) BELOW
    //--------------------------------------------------
public:
    static const std::string &get_hla_class_name(int classHandle) {
        static std::string emptyString;
        IntegerStringMap::iterator ismItr = get_class_handle_name_map().find(classHandle);
        return ismItr == get_class_handle_name_map().end() ? emptyString : ismItr->second;
    }

    static const std::string get_simple_class_name(int classHandle) {
        IntegerStringMap::const_iterator cnmCit = get_class_handle_name_map().find(classHandle);
        return cnmCit == get_class_handle_name_map().end() ? std::string("") : get_simple_class_name(cnmCit->second);
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

    static SP create_object(
      int classHandle, const RTI::AttributeHandleValuePairSet &propertyMap
    ) {
        IntegerStringMap::iterator ismItr = get_class_handle_name_map().find( classHandle );
        return ismItr == get_class_handle_name_map().end() ? SP()
          : create_object( ismItr->second, propertyMap );
    }

    static SP create_object(
      int classHandle, const RTI::AttributeHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) {
        IntegerStringMap::iterator ismItr = get_class_handle_name_map().find( classHandle );
        return ismItr == get_class_handle_name_map().end() ? SP()
          : create_object( ismItr->second, propertyMap, rtiFedTime );
    }

    //------------------------------------------------------
    // END METHODS THAT USE ONLY CLASS-HANDLE CLASS-NAME MAP
    //------------------------------------------------------

    //-------------------------------------------------------------------------
    // CLASS-NAME INSTANCE MAP
    //
    // POPULATED BY:
    // - STATIC INITIALIZATION BLOCKS IN THE DERIVED INTERACTION/OBJECT CLASSES
    //-------------------------------------------------------------------------
protected:
    static StringInstanceSPMap &get_hla_class_name_instance_sp_map() {
        static StringInstanceSPMap hlaClassNameInstanceSPMap;
        return hlaClassNameInstanceSPMap;
    }

    //---------------------------------------------
    // METHODS THAT USER CLASS-NAME INSTANCE-SP MAP
    //---------------------------------------------
public:
    static SP create_object(const std::string &hlaClassName) {
        StringInstanceSPMap::iterator cimItr = get_hla_class_name_instance_sp_map().find(hlaClassName);
        return cimItr == get_hla_class_name_instance_sp_map().end()
            ? get_hla_class_name_set().find(hlaClassName) == get_hla_class_name_set().end()
              ? SP() : SP( new ObjectRoot( hlaClassName ) )
            : cimItr->second->createObject();
    }

    static SP create_object(const std::string &hlaClassName, const RTIfedTime &rtiFedTime) {
        StringInstanceSPMap::iterator cimItr = get_hla_class_name_instance_sp_map().find( hlaClassName );
        return cimItr == get_hla_class_name_instance_sp_map().end()
          ? get_hla_class_name_set().find(hlaClassName) == get_hla_class_name_set().end()
            ? SP() : SP( new ObjectRoot( hlaClassName, rtiFedTime ) )
          : cimItr->second->createObject(rtiFedTime);
    }

    static SP create_object(
      const std::string &hlaClassName, const RTI::AttributeHandleValuePairSet &propertyMap
    ) {
        StringInstanceSPMap::iterator cimItr = get_hla_class_name_instance_sp_map().find( hlaClassName );
        return cimItr == get_hla_class_name_instance_sp_map().end()
          ? get_hla_class_name_set().find(hlaClassName) == get_hla_class_name_set().end()
            ? SP() : SP( new ObjectRoot( hlaClassName, propertyMap ) )
          : cimItr->second->createObject( propertyMap );
    }

    static SP create_object(
      const std::string &hlaClassName,
      const RTI::AttributeHandleValuePairSet &propertyMap,
      const RTIfedTime &rtiFedTime
    ) {
        StringInstanceSPMap::iterator cimItr = get_hla_class_name_instance_sp_map().find( hlaClassName );
        return cimItr == get_hla_class_name_instance_sp_map().end()
          ? get_hla_class_name_set().find(hlaClassName) == get_hla_class_name_set().end()
            ? SP() : SP( new ObjectRoot( hlaClassName, propertyMap, rtiFedTime ) )
          : cimItr->second->createObject( propertyMap, rtiFedTime );
    }

    //-------------------------------
    // END CLASS-NAME INSTANCE-SP MAP
    //-------------------------------

    //------------------------------
    // CLASS-NAME PUBLISH-STATUS MAP
    //
    // POPULATED BY:
    // - init(RTIambassador) ABOVE
    //------------------------------
private:
    static StringBooleanMap &get_class_name_publish_status_map() {
        static StringBooleanMap classNamePublishStatusMap;
        return classNamePublishStatusMap;
    }

    //-----------------------------------------------
    // METHODS THAT USE CLASS-NAME PUBLISH-STATUS MAP
    //-----------------------------------------------
    static bool get_is_published_aux(const std::string &hlaClassName, bool default_value) {
        StringBooleanMap::const_iterator sbmCit = get_class_name_publish_status_map().find(hlaClassName);
        if (sbmCit == get_class_name_publish_status_map().end()) {
            BOOST_LOG_SEV(get_logger(), error) << "could not get publish status for hla class \"" << hlaClassName
              << "\":  class does not exist";
            return default_value;
        }
        return sbmCit->second;
    }

public:
    static bool get_is_published(const std::string &hlaClassName) {
        return get_is_published_aux(hlaClassName, false);
    }

    bool getIsPublished() {
        return get_is_published(getInstanceHlaClassName());
    }

private:
    static void set_is_published(const std::string &hlaClassName, bool publishStatus) {

        StringBooleanMap::iterator sbmItr = get_class_name_publish_status_map().find(hlaClassName);
        readFederateDynamicMessageClass(hlaClassName);
        if (sbmItr == get_class_name_publish_status_map().end()) {
            BOOST_LOG_SEV(get_logger(), error) << "could not set publish status for hla class \"" << hlaClassName
              << "\":  class does not exist";
            return;
        }

        sbmItr->second = publishStatus;
    }

    //----------------------------------
    // END CLASS-NAME PUBLISH-STATUS MAP
    //----------------------------------

    //--------------------------------
    // CLASS-NAME SUBSCRIBE-STATUS MAP
    //
    // POPULATED BY:
    // - init(RTIambassador) ABOVE
    //--------------------------------
private:
    static StringBooleanMap &get_class_name_subscribe_status_map() {
        static StringBooleanMap classNameSubscribeStatusMap;
        return classNameSubscribeStatusMap;
    }

    //-------------------------------------------------
    // METHODS THAT USE CLASS-NAME SUBSCRIBE-STATUS MAP
    //-------------------------------------------------
    static bool get_is_subscribed_aux(const std::string &hlaClassName, bool default_value) {
        StringBooleanMap::const_iterator sbmCit = get_class_name_subscribe_status_map().find(hlaClassName);
        if (sbmCit == get_class_name_subscribe_status_map().end()) {
            BOOST_LOG_SEV(get_logger(), error) << "could not get subscribe status for hla class \"" << hlaClassName
              << "\":  class does not exist";
            return default_value;
        }
        return sbmCit->second;
    }

public:
    static bool get_is_subscribed(const std::string &hlaClassName) {
        return get_is_subscribed_aux(hlaClassName, false);
    }

    bool getIsSubscribed() {
        return get_is_subscribed(getInstanceHlaClassName());
    }

private:
    static void set_is_subscribed(const std::string &hlaClassName, bool subscribeStatus) {
        StringBooleanMap::iterator sbmItr = get_class_name_subscribe_status_map().find(hlaClassName);
        if (sbmItr == get_class_name_subscribe_status_map().end()) {
            BOOST_LOG_SEV(get_logger(), error) << "could not set subscribe status for hla class \"" << hlaClassName
              << "\":  class does not exist";
            return;
        }

        sbmItr->second = subscribeStatus;
    }

    //------------------------------------
    // END CLASS-NAME SUBSCRIBE-STATUS MAP
    //------------------------------------

    //-------------------------------------
    // CLASS-NAME SOFT-SUBSCRIBE-STATUS MAP
    //
    // POPULATED BY:
    // - init(RTIambassador) ABOVE
    //-------------------------------------
private:
    static StringBooleanMap &get_class_name_soft_subscribe_status_map() {
        static StringBooleanMap classNameSoftSubscribeStatusMap;
        return classNameSoftSubscribeStatusMap;
    }

    //-------------------------------------------------
    // METHODS THAT USE CLASS-NAME SUBSCRIBE-STATUS MAP
    //-------------------------------------------------
    static bool get_is_soft_subscribed_aux(const std::string &hlaClassName, bool default_value) {
        StringBooleanMap::const_iterator sbmCit = get_class_name_soft_subscribe_status_map().find(hlaClassName);
        if (sbmCit == get_class_name_soft_subscribe_status_map().end()) {
            BOOST_LOG_SEV(get_logger(), error) << "could not get soft subscribe status for hla class \""
              << hlaClassName << "\":  class does not exist";
            return default_value;
        }
        return sbmCit->second;
    }

public:
    static bool get_is_soft_subscribed(const std::string &hlaClassName) {
        return get_is_soft_subscribed_aux(hlaClassName, false);
    }

    bool getIsSoftSubscribed() {
        return get_is_soft_subscribed(getInstanceHlaClassName());
    }

private:
    static void set_is_soft_subscribed(const std::string &hlaClassName, bool softSubscribeStatus) {
        StringBooleanMap::iterator sbmItr = get_class_name_soft_subscribe_status_map().find(hlaClassName);
        if (sbmItr == get_class_name_soft_subscribe_status_map().end()) {
            BOOST_LOG_SEV(get_logger(), error) << "could not set soft subscribe status for hla class \""
              << hlaClassName << "\":  class does not exist";
            return;
        }

        sbmItr->second = softSubscribeStatus;
    }

    //-----------------------------------------
    // END CLASS-NAME SOFT-SUBSCRIBE-STATUS MAP
    //-----------------------------------------

    //----------------------------------------
    // CLASS-NAME PUBLISHED-ATTRIBUTE-NAME SET
    //
    // INITIALIZED BY:
    // - init(RTIambassador) ABOVE
    //----------------------------------------
protected:
    static StringClassAndPropertyNameSetSPMap &get_class_name_published_class_and_property_name_set_sp_map() {
        static StringClassAndPropertyNameSetSPMap classNamePublishedClassAndPropertyNameSetSPMap;
        return classNamePublishedClassAndPropertyNameSetSPMap;
    }

    //---------------------------------------------------------
    // METHODS THAT USE CLASS-NAME PUBLISHED-ATTRIBUTE-NAME SET
    //
    // ALSO USED BY:
    // - createSuppliedAttributes(bool force) BELOW
    // - publish_object BELOW
    //---------------------------------------------------------
public:
    static const ClassAndPropertyNameSetSP &get_published_class_and_property_name_set_sp(
      const std::string &hlaClassName
    ) {
        static ClassAndPropertyNameSetSP classAndPropertyNameSetSP( new ClassAndPropertyNameSet() );
        StringClassAndPropertyNameSetSPMap::const_iterator scmCit =
          get_class_name_published_class_and_property_name_set_sp_map().find( hlaClassName );

        return scmCit == get_class_name_published_class_and_property_name_set_sp_map().end()
          ? classAndPropertyNameSetSP : scmCit->second;
    }

private:
    static void pub_sub_class_and_property_name(
      const StringClassAndPropertyNameSetSPMap &stringClassAndPropertyNameSetSPMap,
      const std::string &hlaClassName,
      const std::string &attributeClassName,
      const std::string &attributeName,
      bool publish,
      bool insert
    );

public:
    static void publish_attribute(
      const std::string &hlaClassName, const std::string &attributeClassName, const std::string &attributeName
    ) {
        pub_sub_class_and_property_name(
          get_class_name_published_class_and_property_name_set_sp_map(),
          hlaClassName, attributeClassName, attributeName, true, true
        );
    }

    static void publish_attribute(const std::string &hlaClassName, const std::string &attributeName) {
        publish_attribute(hlaClassName, hlaClassName, attributeName);
    }

    static void unpublish_attribute(
      const std::string &hlaClassName, const std::string &attributeClassName, const std::string &attributeName
    ) {
        pub_sub_class_and_property_name(
          get_class_name_published_class_and_property_name_set_sp_map(),
          hlaClassName, attributeClassName, attributeName, true, false
        );
    }

    static void unpublish_attribute(const std::string &hlaClassName, const std::string &attributeName) {
        unpublish_attribute(hlaClassName, hlaClassName, attributeName);
    }

    //--------------------------------------------
    // END CLASS-NAME PUBLISHED-ATTRIBUTE-NAME SET
    //--------------------------------------------

    //-----------------------------------------
    // CLASS-NAME SUBSCRIBED-ATTRIBUTE-NAME SET
    //-----------------------------------------
protected:
    static StringClassAndPropertyNameSetSPMap &get_class_name_subscribed_class_and_property_name_set_sp_map() {
        static StringClassAndPropertyNameSetSPMap classNameSubscribedClassAndPropertyNameSetSPMap;
        return classNameSubscribedClassAndPropertyNameSetSPMap;
    }

    //---------------------------------------------------------
    // METHODS THAT USE CLASS-NAME SUBSCRIBED-ATTRIBUTE-NAME SET
    //---------------------------------------------------------
public:
    static const ClassAndPropertyNameSetSP &get_subscribed_class_and_property_name_set_sp(
      const std::string &hlaClassName
    ) {
        static ClassAndPropertyNameSetSP classAndPropertyNameSetSP( new ClassAndPropertyNameSet() );
        StringClassAndPropertyNameSetSPMap::const_iterator scmCit =
          get_class_name_subscribed_class_and_property_name_set_sp_map().find( hlaClassName );

        return scmCit == get_class_name_subscribed_class_and_property_name_set_sp_map().end()
          ? classAndPropertyNameSetSP : scmCit->second;
    }

    static void subscribe_attribute(
      const std::string &hlaClassName, const std::string &attributeClassName, const std::string &attributeName
    ) {
        pub_sub_class_and_property_name(
          get_class_name_subscribed_class_and_property_name_set_sp_map(),
          hlaClassName, attributeClassName, attributeName, false, true
        );
    }

    static void subscribe_attribute(const std::string &hlaClassName, const std::string &attributeName) {
        subscribe_attribute(hlaClassName, hlaClassName, attributeName);
    }

    static void unsubscribe_attribute(
      const std::string &hlaClassName, const std::string &attributeClassName, const std::string &attributeName
    ) {
        pub_sub_class_and_property_name(
          get_class_name_subscribed_class_and_property_name_set_sp_map(),
          hlaClassName, attributeClassName, attributeName, false, false
        );
    }

    static void unsubscribe_attribute(const std::string &hlaClassName, const std::string &attributeName) {
        unsubscribe_attribute(hlaClassName, hlaClassName, attributeName);
    }

    //---------------------------------------------
    // END CLASS-NAME SUBSCRIBED-ATTRIBUTE-NAME SET
    //---------------------------------------------

    //--------------------------------------------
    // CLASS-AND-PROPERTY-NAME PROPERTY-HANDLE MAP
    //--------------------------------------------
    static ClassAndPropertyNameIntegerMap &get_class_and_property_name_handle_map() {
        static ClassAndPropertyNameIntegerMap classAndPropertyNameIntegerMap;
        return classAndPropertyNameIntegerMap;
    }

    //--------------------------------------------------------------
    // METHODS THAT USE CLASS-NAME-PROPERTY-NAME PROPERTY-HANDLE MAP
    //--------------------------------------------------------------
public:
    static ClassAndPropertyNameSP findProperty(const std::string &hlaClassName, const std::string &propertyName);

    static int get_attribute_handle(const std::string &hlaClassName, const std::string &propertyName) {
        ClassAndPropertyNameSP key = findProperty(hlaClassName, propertyName);
        if (!key) {
            return -1;
        }

        return get_class_and_property_name_handle_map()[*key];
    }

    PropertyHandleValuePairSetSP createPropertyHandleValuePairSetSP( bool force );

    //------------------------------------------------
    // END CLASS-AND-PROPERTY-NAME PROPERTY-HANDLE MAP
    //------------------------------------------------

    //-----------------------------------------------
    // PROPERTY-HANDLE CLASS-AND-PROPERTY-NAME-SP MAP
    //
    // POPULATED BY:
    // - init(RTIambassador) ABOVE
    //-----------------------------------------------
protected:
    static IntegerClassAndPropertyNameSPMap &get_handle_class_and_property_name_sp_map() {
        static IntegerClassAndPropertyNameSPMap handleClassAndPropertyNameSPMap;
        return handleClassAndPropertyNameSPMap;
    }

    //----------------------------------------------------------------
    // METHODS THAT USE PROPERTY-HANDLE CLASS-AND-PROPERTY-NAME-SP MAP
    //----------------------------------------------------------------
public:
    static ClassAndPropertyNameSP get_class_and_attribute_name(int propertyHandle) {
        IntegerClassAndPropertyNameSPMap::iterator icmItr =
          get_handle_class_and_property_name_sp_map().find(propertyHandle);
        return icmItr == get_handle_class_and_property_name_sp_map().end()
          ? ClassAndPropertyNameSP() : icmItr->second;
    }

    const static std::string &get_attribute_name(int propertyHandle) {
        static std::string emptyString;
        ClassAndPropertyNameSP classAndPropertyNameSP = get_class_and_attribute_name(propertyHandle);
        return classAndPropertyNameSP ? classAndPropertyNameSP->getPropertyName() : emptyString;
    }

    static int get_num_attributes(const std::string &hlaClassName) {
        StringClassAndPropertyNameSetSPMap::iterator scmItr =
          get_class_name_all_class_and_property_name_set_sp_map().find(hlaClassName);

        return scmItr == get_class_name_all_class_and_property_name_set_sp_map().end() ?
          -1 : scmItr->second->size();
    }

    int getNumAttributes() {
        return get_class_name_all_class_and_property_name_set_sp_map()[getInstanceHlaClassName()]->size();
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
    // END PROPERTY-HANDLE CLASS-AND-PROPERTY-NAME-SP MAP
    //---------------------------------------------------

    //-------------------------------------------------
    // CLASS-NAME PUBLISHED-ATTRIBUTE-HANDLE-SET-SP MAP
    //
    // INITIALIZED BY:
    // - init(RTIambassador) ABOVE
    //-------------------------------------------------
protected:
    static StringAttributesHandleSetSPMap &get_class_name_published_attribute_handle_set_sp_map() {
        static StringAttributesHandleSetSPMap classNamePublishedAttributesHandleSetSPMap;
        return classNamePublishedAttributesHandleSetSPMap;
    }

    //------------------------------------------------------------------
    // METHODS THAT USE CLASS-NAME PUBLISHED-ATTRIBUTE-HANDLE-SET-SP MAP
    //------------------------------------------------------------------
public:
    static void publish_object(const std::string &hlaClassName, RTI::RTIambassador *rti);

    static const AttributeHandleSetSP &get_published_attribute_handle_set_sp(const std::string &hlaClassName) {
        static AttributeHandleSetSP attributeHandleSetSP( RTI::AttributeHandleSetFactory::create(0) );

        StringAttributesHandleSetSPMap::const_iterator samCit =
          get_class_name_published_attribute_handle_set_sp_map().find(hlaClassName);

        return samCit == get_class_name_published_attribute_handle_set_sp_map().end() ? attributeHandleSetSP
          : samCit->second;
    }

    //-----------------------------------------------------
    // END CLASS-NAME PUBLISHED-ATTRIBUTE-HANDLE-SET-SP MAP
    //-----------------------------------------------------

    //--------------------------------------------------
    // CLASS-NAME SUBSCRIBED-ATTRIBUTE-HANDLE-SET-SP MAP
    //
    // INITIALIZED BY:
    // - init(RTIambassador) ABOVE
    //--------------------------------------------------
protected:
    static StringAttributesHandleSetSPMap &get_class_name_subscribed_attribute_handle_set_sp_map() {
        static StringAttributesHandleSetSPMap classNameSubscribedAttributesHandleSetSPMap;
        return classNameSubscribedAttributesHandleSetSPMap;
    }

    //-------------------------------------------------------------------
    // METHODS THAT USE CLASS-NAME SUBSCRIBED-ATTRIBUTE-HANDLE-SET-SP MAP
    //-------------------------------------------------------------------

public:
    static void subscribe_object(const std::string &hlaClassName, RTI::RTIambassador *rti);

    static void soft_subscribe_object(const std::string &hlaClassName, RTI::RTIambassador *rti) {
        if (!loadDynamicHlaClass(hlaClassName, rti)) {
            BOOST_LOG_SEV(get_logger(), warning) << "soft_subscribe_object(\"" <<
              hlaClassName << "\"):  no such class";
            return;
        }

        set_is_soft_subscribed(hlaClassName, true);
    }

    static const AttributeHandleSetSP &get_subscribed_attribute_handle_set_sp(const std::string &hlaClassName) {
        static AttributeHandleSetSP attributeHandleSetSP( RTI::AttributeHandleSetFactory::create(0) );

        StringAttributesHandleSetSPMap::const_iterator samCit =
          get_class_name_subscribed_attribute_handle_set_sp_map().find(hlaClassName);

        return samCit == get_class_name_subscribed_attribute_handle_set_sp_map().end() ? attributeHandleSetSP
          : samCit->second;
    }

    //---------------------------------------------------
    // END CLASS-NAME SUBSCRIBED-ATTRIBUTE-HANDLE-SET MAP
    //---------------------------------------------------

    static void unpublish_object(const std::string &hlaClassName, RTI::RTIambassador *rti);

    static void unsubscribe_object(const std::string &hlaClassName, RTI::RTIambassador *rti);

    static void soft_unsubscribe_object(const std::string &hlaClassName, RTI::RTIambassador *rti) {
        if (!loadDynamicHlaClass(hlaClassName, rti)) {
            BOOST_LOG_SEV(get_logger(), warning) << "soft_subscribe_object(\"" <<
              hlaClassName << "\"):  no such class";
            return;
        }

        set_is_soft_subscribed(hlaClassName, false);
    }

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

    //----------------------------------
    // OBJECT-HANDLE OBJECT-INSTANCE MAP
    //----------------------------------
private:
    static ObjectHandleInstanceSPMap &get_object_handle_instance_sp_map() {
        static ObjectHandleInstanceSPMap objectHandleInstanceSPMap;
        return objectHandleInstanceSPMap;
    }

    //--------------------------------------------------------
    // METHODS THAT USE ONLY OBJECT-HANDLE OBJECT-INSTANCE MAP
    //--------------------------------------------------------
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

private:
    void setAttributes(const ClassAndPropertyNameValueSPMap &classAndPropertyNameValueSPMap) {
        for(
          ClassAndPropertyNameValueSPMap::const_iterator cvmCit = classAndPropertyNameValueSPMap.begin() ;
          cvmCit != classAndPropertyNameValueSPMap.end() ;
          ++cvmCit
        ) {
            const ClassAndPropertyName &classAndPropertyName(cvmCit->first);
            Value &value(*cvmCit->second);
            _classAndPropertyNameValueSPMap[classAndPropertyName]->setValue(value);
        }
    }

public:
    static SP reflect( int object_handle, const ClassAndPropertyNameValueSPMap &classAndPropertyNameValueSPMap ) {
        SP objectRootSP = get_object( object_handle );
        if ( !objectRootSP ) {
            return objectRootSP;
        }

        objectRootSP->setTime( -1 );
        objectRootSP->setAttributes( classAndPropertyNameValueSPMap );
        return objectRootSP;
    }

    static SP reflect( int object_handle, const RTI::AttributeHandleValuePairSet &propertyMap ) {
        return reflect(object_handle, getClassAndPropertyNameValueSPMap(propertyMap));
    }


    static SP reflect(
      int object_handle,
      const ClassAndPropertyNameValueSPMap &classAndPropertyNameValueSPMap,
      const RTIfedTime &rtiFedTime
    ) {
        SP objectRootSP = get_object( object_handle );
        if ( !objectRootSP ) {
            return objectRootSP;
        }

        objectRootSP->setTime( rtiFedTime.getTime() );
        objectRootSP->setAttributes( classAndPropertyNameValueSPMap );
        return objectRootSP;
    }

    static SP reflect(
      int object_handle, const RTI::AttributeHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) {
        return reflect(object_handle, getClassAndPropertyNameValueSPMap(propertyMap), rtiFedTime);
    }


    static SP reflect(
      int object_handle,
      const ClassAndPropertyNameValueSPMap &classAndPropertyNameValueSPMap,
      double theTime
    ) {
        SP objectRootSP = get_object( object_handle );
        if ( !objectRootSP ) {
            return objectRootSP;
        }

        objectRootSP->setTime( theTime );
        objectRootSP->setAttributes( classAndPropertyNameValueSPMap );
        return objectRootSP;
    }

    static SP reflect( int object_handle, const RTI::AttributeHandleValuePairSet &propertyMap, double theTime ) {
        return reflect(object_handle, getClassAndPropertyNameValueSPMap(propertyMap), theTime);
    }

    //-------------------------------------
    // END METHODS THAT USE ONLY OBJECT MAP
    //-------------------------------------

    //---------------------------------------------------
    // METHODS THAT USE BOTH OBJECT MAP AND OBJECT HANDLE
    //---------------------------------------------------
private:
    void setObjectHandle(int objectHandle) {
        _objectHandle = objectHandle;
    }

    void static set_object_handle( SP objectRootSP, int object_handle ) {
        remove_object( object_handle );
        objectRootSP->setObjectHandle(object_handle);
        get_object_handle_instance_sp_map().insert(  std::make_pair( object_handle, objectRootSP )  );
    }

    //-------------------------------------------------------
    // END METHODS THAT USE BOTH OBJECT MAP AND OBJECT HANDLE
    //-------------------------------------------------------

    //--------------------------------------------
    // METHODS THAT USE OBJECT-HANDLE INSTANCE MAP
    //--------------------------------------------
public:
    static SP discover( int class_handle, int object_handle ) {
        SP objectRootSP = create_object( class_handle );
        if (objectRootSP) {
            set_object_handle(objectRootSP, object_handle);
        }
        return objectRootSP;
    }

    //------------------------------------------------
    // END METHODS THAT USE OBJECT-HANDLE INSTANCE MAP
    //------------------------------------------------

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

    void requestUpdate( RTI::RTIambassador *rti );

    //----------------------------------------------
    // CLASS-AND-PROPERTY-NAME PROPERTY-VALUE-SP MAP
    //----------------------------------------------
protected:
    ClassAndPropertyNameValueSPMap _classAndPropertyNameValueSPMap;

    //---------------------------------------------------------------
    // METHODS THAT USE CLASS-AND-PROPERTY-NAME PROPERTY-VALUE-SP MAP
    //---------------------------------------------------------------
public:
    const ClassAndPropertyNameValueSPMap &getClassAndPropertyNameValueSPMap() const {
        return _classAndPropertyNameValueSPMap;
    }

    template<typename T>
    void setAttribute(
      const std::string &hlaClassName, const std::string &propertyName, const T &value
    ) {
        ClassAndPropertyNameSP classAndPropertyNameSP = findProperty(hlaClassName, propertyName);

        if (!classAndPropertyNameSP) {
            BOOST_LOG_SEV(get_logger(), error) << "setAttribute(\"" << hlaClassName << "\", "
              << "\"" << propertyName << "\", " << typeid(T).name() << " value): could not find \"" << propertyName
              << "\" attribute in class \"" << hlaClassName << "\" or any of its superclasses.";
            return;
        }

        Value &currentValue = *_classAndPropertyNameValueSPMap[*classAndPropertyNameSP];

        if (!currentValue.setValue(value)) {
            BOOST_LOG_SEV(get_logger(), error) << "setAttribute(\"" << propertyName << "\", "
              << typeid(T).name() << " value): \"value\" is incorrect type \"" << typeid(T).name()
              << "\" for \"" << propertyName << "\" attribute, should be of type \""
              << currentValue.getTypeName() << "\"";
        }
    }

    template<typename T>
    void setAttribute(const ClassAndPropertyName &classAndPropertyName, const T &value) {
        setAttribute(
          classAndPropertyName.getClassName(), classAndPropertyName.getPropertyName(), value
        );
    }

    template<typename T>
    void setAttribute(const ClassAndPropertyNameSP &classAndPropertyNameSP, const T &value) {
        setAttribute(*classAndPropertyNameSP, value);
    }

    template<typename T>
    void setAttribute(const std::string &propertyName, const T &value) {
        setAttribute(getInstanceHlaClassName(), propertyName, value);
    }

public:
    bool hasAttribute(const std::string &hlaClassName, const std::string &propertyName) {
        return static_cast<bool>(findProperty(hlaClassName, propertyName));
    }

    bool hasAttribute(const std::string &propertyName) {
        return hasAttribute(getInstanceHlaClassName(), propertyName);
    }

    const Value &getAttribute(
      const std::string &hlaClassName, const std::string &propertyName
    ) const override {
        static Value value(0);

        ClassAndPropertyNameSP classAndPropertyNameSP = findProperty(hlaClassName, propertyName);

        return classAndPropertyNameSP ? *(_classAndPropertyNameValueSPMap.find(*classAndPropertyNameSP)->second) : value;
    }

    const Value &getAttribute(const ClassAndPropertyName &classAndPropertyName) {
        return getAttribute(
          classAndPropertyName.getClassName(), classAndPropertyName.getPropertyName()
        );
    }

    const Value &getAttribute(const ClassAndPropertyNameSP &classAndPropertyNameSP) {
        return getAttribute(*classAndPropertyNameSP);
    }

    const Value &getAttribute(const std::string &propertyName) const override {
        return getAttribute(getInstanceHlaClassName(), propertyName);
    }

    //--------------------------------------------------
    // END CLASS-AND-PROPERTY-NAME PROPERTY-VALUE-SP MAP
    //--------------------------------------------------

    //---------------------------
    // START OF INCLUDED TEMPLATE
    //---------------------------



private:
    static severity_logger &get_logger_aux() {
        static severity_logger logger;
        logger.add_attribute("MessagingClassName", attrs::constant< std::string >(
          "ObjectRoot"
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
     * Returns the fully-qualified (dot-delimited) name of the ::org::cpswt::hla::ObjectRoot object class.
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
    static const std::string get_simple_class_name() {
        return get_simple_class_name(get_hla_class_name());
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
        return get_attribute_names( get_hla_class_name() );
    }

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
        return get_all_attribute_names( get_hla_class_name() );
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
     * Returns the handle (RTI assigned) of the org.cpswt.hla.ObjectRoot object class.
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
     * this object class (i.e. "org.cpswt.hla.ObjectRoot") given the attribute's name.
     *
     * @param propertyName name of attribute
     * @return the handle (RTI assigned) of the attribute "propertyName" of object class "hlaClassName"
     */
    static int get_attribute_handle(const std::string &propertyName) {
        return get_attribute_handle(get_hla_class_name(), propertyName);
    }

    static AttributeHandleSetSP get_published_attribute_handle_set_sp() {
        return get_published_attribute_handle_set_sp( get_hla_class_name() );
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
        return get_subscribed_attribute_handle_set_sp( get_hla_class_name() );
    }

    // ----------------------------------------------------------
    // END OF STATIC PROPERTYS AND CODE THAT DEAL WITH HANDLES.
    // ----------------------------------------------------------


    //-------------------------------------------------
    // METHODS FOR PUBLISHING/SUBSCRIBING-TO THIS CLASS
    //-------------------------------------------------

    /**
     * Publishes the org.cpswt.hla.ObjectRoot object class for a federate.
     *
     * @param rti handle to the Local RTI Component
     */
    static void publish_object(RTI::RTIambassador *rti) {
        publish_object( get_hla_class_name(), rti );
    }

    static bool get_is_published() {
        return get_is_published(get_hla_class_name());
    }

    /**
     * Unpublishes the org.cpswt.hla.ObjectRoot object class for a federate.
     *
     * @param rti handle to the Local RTI Component, usu. obtained through the
     *            {@link SynchronizedFederate#getLRC()} call
     */
    static void unpublish_object(RTI::RTIambassador *rti) {
        unpublish_object( get_hla_class_name(), rti);
    }

/**
 * Subscribes a federate to the org.cpswt.hla.ObjectRoot object class.
 *
 * @param rti handle to the Local RTI Component
 */
    static void subscribe_object(RTI::RTIambassador *rti) {
        subscribe_object( get_hla_class_name(), rti );
    }

    static bool get_is_subscribed() {
        return get_is_subscribed(get_hla_class_name());
    }

    static void soft_subscribe_object(RTI::RTIambassador *rti) {
        soft_subscribe_object(get_hla_class_name(), rti);
    }

    static bool get_is_soft_subscribed() {
        return get_is_soft_subscribed(get_hla_class_name());
    }

    /**
     * Unsubscribes a federate from the org.cpswt.hla.ObjectRoot object class.
     *
     * @param rti handle to the Local RTI Component
     */
    static void unsubscribe_object(RTI::RTIambassador *rti) {
        unsubscribe_object( get_hla_class_name(), rti );
    }

    static void soft_unsubscribe_object(RTI::RTIambassador *rti) {
        soft_unsubscribe_object(get_hla_class_name(), rti);
    }

    static ClassAndPropertyNameSetSP get_published_attribute_name_set_sp() {
        return get_class_name_published_class_and_property_name_set_sp_map()[get_hla_class_name()];
    }

    static ClassAndPropertyNameSetSP get_subscribed_attribute_name_set_sp() {
        return get_class_name_subscribed_class_and_property_name_set_sp_map()[get_hla_class_name()];
    }

    static void add_object_update_embedded_only_id(int id) {
        add_object_update_embedded_only_id(get_hla_class_name(), id);
    }

    static void remove_object_update_embedded_only_id(int id) {
        remove_object_update_embedded_only_id(get_hla_class_name(), id);
    }

    static const IntegerSetSP &get_object_update_embedded_only_id_set_sp() {
        return get_object_update_embedded_only_id_set_sp(get_hla_class_name());
    }

    static bool get_is_object_update_embedded_only_id(int id) {
        return get_is_object_update_embedded_only_id(get_hla_class_name(), id);
    }

    static void add_federate_name_soft_publish_direct(const std::string &federateName) {
        add_federate_name_soft_publish_direct(get_hla_class_name(), federateName);
    }

    static void remove_federate_name_soft_publish_direct(const std::string &federateName) {
        remove_federate_name_soft_publish_direct(get_hla_class_name(), federateName);
    }

    static const StringSetSP &get_federate_name_soft_publish_direct_set() {
        return get_federate_name_soft_publish_direct_set_sp(get_hla_class_name());
    }

    static void add_federate_name_soft_publish(const std::string &networkFederateName) {
        add_federate_name_soft_publish(get_hla_class_name(), networkFederateName);
    }

    static void remove_federate_name_soft_publish(const std::string &networkFederateName) {
        remove_federate_name_soft_publish(get_hla_class_name(), networkFederateName);
    }

    //-----------------------------------------------------
    // END METHODS FOR PUBLISHING/SUBSCRIBING-TO THIS CLASS
    //-----------------------------------------------------

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

    static int get_num_attributes() {
        return get_class_name_all_class_and_property_name_set_sp_map()[get_hla_class_name()]->size();
    }

    //------------------------------
    // PROPERTY MANIPULATION METHODS
    //------------------------------

    //------------------------------------
    // END PROPERTY MANIPULATION METHODS
    //------------------------------------

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

    //---------------------------------------------
    // CLASS-AND-PROPERTY-NAME INITIAL-VALUE-SP MAP
    //---------------------------------------------
protected:
    static ClassAndPropertyNameValueSPMap &get_class_and_property_name_initial_value_sp_map() {
        static ClassAndPropertyNameValueSPMap classAndPropertyNameValueSPMap;
        return classAndPropertyNameValueSPMap;
    }

    //-------------
    // CONSTRUCTORS
    //-------------
    class NoInstanceInit { };
    ObjectRoot(NoInstanceInit &noInstanceInit) : _uniqueId(generate_unique_id()) { }

private:
    void initializeProperties(const std::string &hlaClassName);

    /**
     * Creates a new ObjectRoot instance.
     */
    // THE CONSTRUCTORS IN THE ANALOGOUS POSITION TO THIS POSITION IN THE JavaMessagingRoot.jinja2 FILE ARE IN THE
    // CppMessagingHeaderCommon.jinja2 FILE FOR C++ AS C++ DOES NOT SUPPORT INSTANCE-INITIALIZATION BLOCKS.
    //
public:

    ObjectRoot() : _uniqueId(generate_unique_id()) {
        initializeProperties(get_hla_class_name());
    }

    ObjectRoot( const RTIfedTime &rtiFedTime) : _uniqueId(generate_unique_id()) {
        initializeProperties(get_hla_class_name());
        setTime(rtiFedTime.getTime());
    }

    ObjectRoot(const RTI::AttributeHandleValuePairSet &propertyMap)
      : _uniqueId(generate_unique_id()) {
        initializeProperties(get_hla_class_name());
        setAttributes( propertyMap );
    }

    ObjectRoot(
      const RTI::AttributeHandleValuePairSet &propertyMap,
      const RTIfedTime &rtiFedTime
    ) : _uniqueId(generate_unique_id()) {
        initializeProperties(get_hla_class_name());
        setAttributes( propertyMap );
        setTime(rtiFedTime.getTime());
    }

    ObjectRoot( const std::string &hlaClassName ) : _uniqueId(generate_unique_id()) {
        initializeProperties(hlaClassName);
    }

    ObjectRoot( const std::string &hlaClassName, const RTIfedTime &rtiFedTime) : _uniqueId(generate_unique_id()) {
        initializeProperties(hlaClassName);
        setTime(rtiFedTime.getTime());
    }

    ObjectRoot(
      const std::string &hlaClassName, const RTI::AttributeHandleValuePairSet &propertyMap
    ) : _uniqueId(generate_unique_id()) {
        initializeProperties(hlaClassName);
        setAttributes( propertyMap );
    }

    ObjectRoot(
      const std::string &hlaClassName,
      const RTI::AttributeHandleValuePairSet &propertyMap,
      const RTIfedTime &rtiFedTime
    ) : _uniqueId(generate_unique_id()) {
        initializeProperties(hlaClassName);
        setAttributes( propertyMap );
        setTime(rtiFedTime.getTime());
    }

    //-----------------
    // END CONSTRUCTORS
    //-----------------

public:
    void setAttributes( const RTI::AttributeHandleValuePairSet &propertyMap );

    template<typename T>
    void setAttribute(int propertyHandle, const T &value) {

        IntegerClassAndPropertyNameSPMap::iterator hcmItr =
          get_handle_class_and_property_name_sp_map().find(propertyHandle);

        if (hcmItr == get_handle_class_and_property_name_sp_map().end()) {
            BOOST_LOG_SEV(get_logger(), error) << "setAttribute(int propertyHandle, "
              << typeid(T).name() << " value): propertyHandle (" << propertyHandle << ") does not exist.";
            return;
        }

        ClassAndPropertyName &classAndPropertyName = *hcmItr->second;

        ClassAndPropertyNameValueSPMap::iterator cvmItr = _classAndPropertyNameValueSPMap.find(classAndPropertyName);
        if (cvmItr == _classAndPropertyNameValueSPMap.end()) {
            BOOST_LOG_SEV(get_logger(), error) << "setAttribute(int propertyHandle, "
            << typeid(T).name() << " value): propertyHandle (" << propertyHandle
            << ") corresponds to property of name \"" << classAndPropertyName.getPropertyName()
            << "\", which does not exist in class \"" << getInstanceHlaClassName() << "\" (it's defined in class \""
            << classAndPropertyName.getClassName() << "\")";
        }

        Value &currentValue = *_classAndPropertyNameValueSPMap[*hcmItr->second];
        if (!currentValue.setValue(value)) {
            BOOST_LOG_SEV(get_logger(), error) << "setAttribute(int propertyHandle, "
              << typeid(T).name() << " value): \"value\" is incorrect type \"" << typeid(T).name()
              << "\" for \"" << classAndPropertyName.getPropertyName() << "\" attribute, should be of type \""
              << currentValue.getTypeName() << "\"";
        }
    }

    void updateAttributeValues( RTI::RTIambassador *rti, double time, bool force );

    void updateAttributeValues( RTI::RTIambassador *rti, double time ) {
        updateAttributeValues( rti, time, false );
    }

    void updateAttributeValues( RTI::RTIambassador *rti, bool force );

    void updateAttributeValues( RTI::RTIambassador *rti ) {
        updateAttributeValues( rti, false );
    }

    //---------------------------------------------------------------
    // INSTANCE VERSIONS OF STATIC METHODS DEFINED IN DERIVED CLASSES
    //---------------------------------------------------------------

    /**
     * Returns the simple name (last name in its fully-qualified dot-delimited name)
     * of this instance's object class.
     * Polymorphic equivalent of the get_simple_class_name static method.
     *
     * @return the simple name of this instance's object class
     */
    const std::string getSimpleClassName() const override {
        return get_simple_class_name( getInstanceHlaClassName() );
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
        return get_attribute_names( getInstanceHlaClassName() );
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
        return get_all_attribute_names( getInstanceHlaClassName() );
    }

    /**
     * Returns the handle (RTI assigned) of this instance's object class.
     * Polymorphic equivalent for get_class_handle static method.
     *
     * @return the handle (RTI assigned) if this instance's object class
     */
    int getClassHandle() const override {
        return get_class_handle( getInstanceHlaClassName() );
    }

    int getAttributeHandle(const std::string &propertyName) {
        return get_attribute_handle( getInstanceHlaClassName(), propertyName );
    }

    AttributeHandleSetSP getPublishedAttributeHandleSetSP() {
        return get_published_attribute_handle_set_sp( getInstanceHlaClassName() );
    }

    AttributeHandleSetSP getSubscribedAttributeHandleSetSP() {
        return get_subscribed_attribute_handle_set_sp( getInstanceHlaClassName() );
    }

    ClassAndPropertyNameSetSP getPublishedClassAndPropertyNameSetSP() {
        return get_published_class_and_property_name_set_sp( getInstanceHlaClassName() );
    }

    ClassAndPropertyNameSetSP getSubscribedClassAndPropertyNameSetSP() {
        return get_subscribed_class_and_property_name_set_sp( getInstanceHlaClassName() );
    }

    /**
     * Publishes the object class of this instance of the class for a federate.
     * Polymorphic equalivalent of publish_object static method.
     *
     * @param rti handle to the Local RTI Component
     */
    void publishObject(RTI::RTIambassador *rti) {
        publish_object(getInstanceHlaClassName(), rti);
    }

    /**
     * Unpublishes the object class of this instance of this class for a federate.
     * Polymorphic equivalent of unpublish_object static method.
     *
     * @param rti handle to the Local RTI Component
     */
    void unpublishObject(RTI::RTIambassador *rti) {
        unpublish_object(getInstanceHlaClassName(), rti);
    }

    /**
     * Subscribes a federate to the object class of this instance of this class.
     * Polymorphic equivalent of subscribe_object static method.
     *
     * @param rti handle to the Local RTI Component
     */
    void subscribeObject(RTI::RTIambassador *rti) {
        subscribe_object(getInstanceHlaClassName(), rti);
    }

    /**
     * Unsubscribes a federate from the object class of this instance of this class.
     *
     * @param rti handle to the Local RTI Component
     */
    void unsubscribeObject(RTI::RTIambassador *rti) {
        unsubscribe_object(getInstanceHlaClassName(), rti);
    }

    void softSubscribeObject(RTI::RTIambassador *rti) {
        soft_subscribe_object(getInstanceHlaClassName(), rti);
    }

    void softUnsubscribeObject(RTI::RTIambassador *rti) {
        soft_unsubscribe_object(getInstanceHlaClassName(), rti);
    }


    //-------------------------------------------------------------------
    // END INSTANCE VERSIONS OF STATIC METHODS DEFINED IN DERIVED CLASSES
    //-------------------------------------------------------------------

    std::string toJson();

    static ObjectReflector::SP fromJson(const std::string &jsonString);

private:
    static StringIntegerSetSPMap &get_hla_class_name_object_update_embedded_only_id_set_sp_map() {
        static StringIntegerSetSPMap hlaClassNameObjectUpdateEmbeddedOnlyIdSetSPMap;
        return hlaClassNameObjectUpdateEmbeddedOnlyIdSetSPMap;
    }

public:
    static void add_object_update_embedded_only_id(const std::string &hlaClassName, int id);

    static void remove_object_update_embedded_only_id(const std::string &hlaClassName, int id);

    static const IntegerSetSP &get_object_update_embedded_only_id_set_sp(const std::string &hlaClassName) {
        static IntegerSetSP defaultIntegerSetSP( new IntegerSet() );
        StringIntegerSetSPMap::const_iterator simCit =
          get_hla_class_name_object_update_embedded_only_id_set_sp_map().find(hlaClassName);
        return simCit == get_hla_class_name_object_update_embedded_only_id_set_sp_map().end() ?
            defaultIntegerSetSP : simCit->second;
    }

    static bool get_is_object_update_embedded_only_id(const std::string &hlaClassName, int id) {
        const IntegerSet &integerSet = *get_object_update_embedded_only_id_set_sp(hlaClassName);
        return integerSet.find(id) != integerSet.end();
    }

    static bool get_is_object_update_embedded_only_id(int classId, int id) {
        IntegerStringMap::const_iterator ismCit = get_class_handle_name_map().find(classId);
        return ismCit == get_class_handle_name_map().end() ?
          false : get_is_object_update_embedded_only_id(ismCit->second, id);
    }

private:
    static StringStringSetSPMap &get_hla_class_name_to_federate_name_soft_publish_direct_set_sp_map() {
        static StringStringSetSPMap hlaClassNameToFederateNameSoftPublishDirectSetMap;
        return hlaClassNameToFederateNameSoftPublishDirectSetMap;
    }

public:
    static void add_federate_name_soft_publish_direct(const std::string &hlaClassName, const std::string &federateName);

    static void remove_federate_name_soft_publish_direct(
      const std::string &hlaClassName, const std::string &federateName
    );

    static const StringSetSP &get_federate_name_soft_publish_direct_set_sp(const std::string &hlaClassName) {
        static StringSetSP defaultStringSetSP ( new StringSet() );
        return get_hla_class_name_to_federate_name_soft_publish_direct_set_sp_map().find(hlaClassName) ==
          get_hla_class_name_to_federate_name_soft_publish_direct_set_sp_map().end() ?
            defaultStringSetSP : get_hla_class_name_to_federate_name_soft_publish_direct_set_sp_map()[hlaClassName];
    }

    const StringSetSP &getFederateNameSoftPublishDirectSetSP() {
        return get_federate_name_soft_publish_direct_set_sp(getInstanceHlaClassName());
    }

private:
    static StringStringSetSPMap &get_hla_class_name_to_federate_name_soft_publish_set_sp_map() {
        static StringStringSetSPMap hlaClassNameToFederateNameSoftPublishSetMap;
        return hlaClassNameToFederateNameSoftPublishSetMap;
    }

public:
    static void add_federate_name_soft_publish(const std::string &hlaClassName, const std::string &federateName);

    void addFederateNameSoftPublish(const std::string &federateName) {
        add_federate_name_soft_publish(getInstanceHlaClassName(), federateName);
    }

    static void remove_federate_name_soft_publish(const std::string &hlaClassName, const std::string &federateName);

    void removeFederateNameSoftPublish(const std::string &federateName) {
        remove_federate_name_soft_publish(getInstanceHlaClassName(), federateName);
    }

    const StringSetSP &get_federate_name_soft_publish_set_sp(const std::string &hlaClassName) {
        static StringSetSP defaultStringSetSP( new StringSet() );
        return get_hla_class_name_to_federate_name_soft_publish_set_sp_map().find(hlaClassName) ==
          get_hla_class_name_to_federate_name_soft_publish_set_sp_map().end() ?
            defaultStringSetSP : get_hla_class_name_to_federate_name_soft_publish_set_sp_map()[hlaClassName];
    }

    const StringSetSP &getFederateNameSoftPublishSetSP() {
        return get_federate_name_soft_publish_set_sp(getInstanceHlaClassName());
    }

private:
    static Json::Value &get_federation_json() {
        static Json::Value federationJson;
        return federationJson;
    }

    typedef std::map<std::string, ValueSP> TypeInitialValueSPMap;
    static TypeInitialValueSPMap &get_type_initial_value_sp_map_aux() {
        static TypeInitialValueSPMap typeInitialValueSPMap;

        typeInitialValueSPMap[ "boolean" ] = ValueSP( new Value(false) );
        typeInitialValueSPMap[ "byte" ] = ValueSP( new Value(static_cast<char>(0)) );
        typeInitialValueSPMap[ "char" ] = ValueSP( new Value(static_cast<char>(0)) );
        typeInitialValueSPMap[ "double" ] = ValueSP( new Value(static_cast<double>(0)) );
        typeInitialValueSPMap[ "float" ] = ValueSP( new Value(static_cast<float>(0)) );
        typeInitialValueSPMap[ "int" ] = ValueSP( new Value(0) );
        typeInitialValueSPMap[ "long" ] = ValueSP( new Value(static_cast<long>(0)) );
        typeInitialValueSPMap[ "short" ] = ValueSP( new Value(static_cast<short>(0)) );
        typeInitialValueSPMap[ "String" ] = ValueSP( new Value(std::string("")) );

        return typeInitialValueSPMap;
    }

    static TypeInitialValueSPMap &get_type_initial_value_sp_map() {
        static TypeInitialValueSPMap &typeInitialValueSPMap = get_type_initial_value_sp_map_aux();
        return typeInitialValueSPMap;
    }

public:
    static void readFederationJson(const std::string &federationJsonFileString) {
        std::ifstream inputJsonFileStream(federationJsonFileString);
        readFederationJson(inputJsonFileStream);
        inputJsonFileStream.close();
    }

    static void readFederationJson(std::istream &federationJsonInputStream) {
        federationJsonInputStream >> get_federation_json();
    }

    static void readFederateDynamicMessageClasses( const std::string &dynamicMessageTypesJsonFileString ) {
        std::ifstream dynamicMessageTypesInputFileStream( dynamicMessageTypesJsonFileString );
        readFederateDynamicMessageClasses(dynamicMessageTypesInputFileStream);
        dynamicMessageTypesInputFileStream.close();
    }

    static void readFederateDynamicMessageClasses(std::istream &dynamicMessagingTypesInputStream);

    static void readFederateDynamicMessageClasses(const StringSet &dynamicHlaClassNameSet) {
        for(const std::string &hlaClassName: dynamicHlaClassNameSet) {
            readFederateDynamicMessageClass(hlaClassName);
        }
    }

    static void readFederateDynamicMessageClass(const std::string &dynamicHlaClassName);

    static void loadDynamicClassFederationData(
      std::istream &federationJsonReader, std::istream &federateDynamicMessageClassesReader
    ) {
        readFederationJson(federationJsonReader);
        readFederateDynamicMessageClasses(federateDynamicMessageClassesReader);
    }

    static void loadDynamicClassFederationData(
      const std::string &federationJsonFileString, const std::string &dynamicMessageTypesJsonFileString
    ) {
        readFederationJson(federationJsonFileString);
        readFederateDynamicMessageClasses(dynamicMessageTypesJsonFileString);
    }

private:
    static bool loadDynamicHlaClass(const std::string &hlaClassName, RTI::RTIambassador *rti) {
        if (get_hla_class_name_set().find(hlaClassName) == get_hla_class_name_set().end()) {
            readFederateDynamicMessageClass(hlaClassName);
            if (get_hla_class_name_set().find(hlaClassName) == get_hla_class_name_set().end()) {
                return false;
            }
            init(hlaClassName, rti);
        }
        return true;
    }
};
  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"

std::ostream &operator<<( std::ostream &os, const ::org::cpswt::hla::ObjectRoot &messaging );
inline std::ostream &operator<<( std::ostream &os, ::org::cpswt::hla::ObjectRoot::SP messagingSP ) {
    return os << *messagingSP;
}

std::ostream &operator<<( std::ostream &os, const ::org::cpswt::hla::ObjectRoot::ObjectReflector &objectReflector );
inline std::ostream &operator<<(
  std::ostream &os, ::org::cpswt::hla::ObjectRoot::ObjectReflector::SP objectReflectorSP
) {
    return os << *objectReflectorSP;
}

#endif // _OBJECT_ROOT
