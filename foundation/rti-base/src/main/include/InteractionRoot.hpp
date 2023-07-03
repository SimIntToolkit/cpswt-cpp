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


#ifndef _INTERACTION_ROOT_CLASS
#define _INTERACTION_ROOT_CLASS

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

#include "InteractionRootInterface.hpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "RTILogger.hpp"

#ifndef C2W_RTI_LOGGER_CLS
#define C2W_RTI_LOGGER_CLS C2WConsoleLogger
#endif


namespace edu {
 namespace vanderbilt {
  namespace vuisis {
   namespace cpswt {
    namespace hla {

namespace logging = boost::log;
namespace logging_source = boost::log::sources;
namespace attrs = boost::log::attributes;

using namespace logging::trivial;

class InteractionRoot : public InteractionRootInterface {

public:
    typedef logging_source::severity_logger< severity_level > severity_logger;

    typedef boost::shared_ptr<InteractionRoot> SP;
    typedef RTI::ParameterHandleValuePairSet PropertyHandleValuePairSet;
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

    typedef TypeMedley Value;

    typedef boost::shared_ptr<Value> ValueSP;
    typedef std::unordered_map<ClassAndPropertyName, ValueSP> ClassAndPropertyNameValueSPMap;

    typedef void (*PubsubFunctionPtr)( RTI::RTIambassador * );
    typedef std::map< std::string, PubsubFunctionPtr > ClassNamePubSubMap;
    typedef std::map< std::string, std::string> PropertyTypeMap;

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

protected:
    static void common_init(const std::string &hlaClassName);

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

    // FOR INTERACTIONS DERIVED FROM InteractionRoot.C2WInteractionRoot
    bool federateAppendedToFederateSequence = false;

public:
    void setFederateAppendedToFederateSequence(bool value) {
        federateAppendedToFederateSequence = value;
    }

    bool getFederateAppendedToFederateSequence() {
        return federateAppendedToFederateSequence;
    }

public:
    static std::string get_simple_class_name(const std::string &hlaClassName) {
        size_t position = hlaClassName.find_last_of('.');
        return position == std::string::npos ? hlaClassName : hlaClassName.substr(position + 1);
    }

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

    static ClassAndPropertyNameSet &get_complete_class_and_property_name_set() {
        static ClassAndPropertyNameSet classAndPropertyNameSet;
        return classAndPropertyNameSet;
    }

    //--------------------------------------------------------------------------
    // METHODS THAT USE HLA CLASS-NAME-SET
    //
    // ALSO USED BY:
    // - InteractionRoot( const std::string &hlaClassName ) DYNAMIC CONSTRUCTOR
    // - readFederateDynamicMessageClasses(Reader reader) BELOW
    //--------------------------------------------------------------------------
public:
    static const StringSet &get_interaction_hla_class_name_set() {
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
    static ClassAndPropertyNameList get_parameter_names(const std::string &hlaClassName) {
        if (get_hla_class_name_set().find(hlaClassName) == get_hla_class_name_set().end()) {
            readFederateDynamicMessageClass(hlaClassName);
        }

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
    static const ClassAndPropertyNameList get_all_parameter_names(const std::string &hlaClassName) {
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

    static SP create_interaction(int classHandle) {
        IntegerStringMap::iterator ismItr = get_class_handle_name_map().find(classHandle);
        return ismItr == get_class_handle_name_map().end()
          ? SP() : create_interaction(ismItr->second);
    }

    static SP create_interaction(int classHandle, const RTIfedTime &rtiFedTime) {
        IntegerStringMap::iterator ismItr = get_class_handle_name_map().find(classHandle);
        return ismItr == get_class_handle_name_map().end()
          ? SP() : create_interaction(ismItr->second, rtiFedTime);
    }

    static SP create_interaction(
      int classHandle, const RTI::ParameterHandleValuePairSet &propertyMap
    ) {
        IntegerStringMap::iterator ismItr = get_class_handle_name_map().find( classHandle );
        return ismItr == get_class_handle_name_map().end() ? SP()
          : create_interaction( ismItr->second, propertyMap );
    }

    static SP create_interaction(
      int classHandle, const RTI::ParameterHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) {
        IntegerStringMap::iterator ismItr = get_class_handle_name_map().find( classHandle );
        return ismItr == get_class_handle_name_map().end() ? SP()
          : create_interaction( ismItr->second, propertyMap, rtiFedTime );
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
    static SP create_interaction(const std::string &hlaClassName) {
        StringInstanceSPMap::iterator cimItr = get_hla_class_name_instance_sp_map().find(hlaClassName);
        return cimItr == get_hla_class_name_instance_sp_map().end()
            ? get_class_name_handle_map().find(hlaClassName) == get_class_name_handle_map().end()
              ? SP() : SP( new InteractionRoot( hlaClassName ) )
            : cimItr->second->createInteraction();
    }

    static SP create_interaction(const std::string &hlaClassName, const RTIfedTime &rtiFedTime) {
        StringInstanceSPMap::iterator cimItr = get_hla_class_name_instance_sp_map().find( hlaClassName );
        return cimItr == get_hla_class_name_instance_sp_map().end()
          ? get_class_name_handle_map().find(hlaClassName) == get_class_name_handle_map().end()
            ? SP() : SP( new InteractionRoot( hlaClassName, rtiFedTime ) )
          : cimItr->second->createInteraction(rtiFedTime);
    }

    static SP create_interaction(
      const std::string &hlaClassName, const RTI::ParameterHandleValuePairSet &propertyMap
    ) {
        StringInstanceSPMap::iterator cimItr = get_hla_class_name_instance_sp_map().find( hlaClassName );
        return cimItr == get_hla_class_name_instance_sp_map().end()
          ? get_class_name_handle_map().find(hlaClassName) == get_class_name_handle_map().end()
            ? SP() : SP( new InteractionRoot( hlaClassName, propertyMap ) )
          : cimItr->second->createInteraction( propertyMap );
    }

    static SP create_interaction(
      const std::string &hlaClassName,
      const RTI::ParameterHandleValuePairSet &propertyMap,
      const RTIfedTime &rtiFedTime
    ) {
        StringInstanceSPMap::iterator cimItr = get_hla_class_name_instance_sp_map().find( hlaClassName );
        return cimItr == get_hla_class_name_instance_sp_map().end()
          ? get_class_name_handle_map().find(hlaClassName) == get_class_name_handle_map().end()
            ? SP() : SP( new InteractionRoot( hlaClassName, propertyMap, rtiFedTime ) )
          : cimItr->second->createInteraction( propertyMap, rtiFedTime );
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

    static int get_parameter_handle(const std::string &hlaClassName, const std::string &propertyName) {
        ClassAndPropertyNameSP key = findProperty(hlaClassName, propertyName);
        if (!key) {
            return -1;
        }

        return get_class_and_property_name_handle_map()[*key];
    }

    PropertyHandleValuePairSetSP createPropertyHandleValuePairSetSP();

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
    static ClassAndPropertyNameSP get_class_and_parameter_name(int propertyHandle) {
        IntegerClassAndPropertyNameSPMap::iterator icmItr =
          get_handle_class_and_property_name_sp_map().find(propertyHandle);
        return icmItr == get_handle_class_and_property_name_sp_map().end()
          ? ClassAndPropertyNameSP() : icmItr->second;
    }

    const static std::string &get_parameter_name(int propertyHandle) {
        static std::string emptyString;
        ClassAndPropertyNameSP classAndPropertyNameSP = get_class_and_parameter_name(propertyHandle);
        return classAndPropertyNameSP ? classAndPropertyNameSP->getPropertyName() : emptyString;
    }

    static int get_num_parameters(const std::string &hlaClassName) {
        StringClassAndPropertyNameSetSPMap::iterator scmItr =
          get_class_name_all_class_and_property_name_set_sp_map().find(hlaClassName);

        return scmItr == get_class_name_all_class_and_property_name_set_sp_map().end() ?
          -1 : scmItr->second->size();
    }

    int getNumParameters() {
        return get_class_name_all_class_and_property_name_set_sp_map()[getInstanceHlaClassName()]->size();
    }

    /**
     * Returns the value of the parameter whose handle is "propertyHandle"
     * (RTI assigned) for this interaction.
     *
     * @param propertyHandle handle (RTI assigned) of parameter whose
     * value to retrieve
     * @return the value of the parameter whose handle is "propertyHandle"
     */
    const Value &getParameter( int propertyHandle ) const override;

    //---------------------------------------------------
    // END PROPERTY-HANDLE CLASS-AND-PROPERTY-NAME-SP MAP
    //---------------------------------------------------
public:
    static void publish_interaction(const std::string &hlaClassName, RTI::RTIambassador *rti);

public:
    static void subscribe_interaction(const std::string &hlaClassName, RTI::RTIambassador *rti);

    static void soft_subscribe_interaction(const std::string &hlaClassName, RTI::RTIambassador *rti) {
        if (!loadDynamicHlaClass(hlaClassName, rti)) {
            BOOST_LOG_SEV(get_logger(), warning) << "soft_subscribe_interaction(\"" <<
              hlaClassName << "\"):  no such class";
            return;
        }

        set_is_soft_subscribed(hlaClassName, true);
    }

    static void unpublish_interaction(const std::string &hlaClassName, RTI::RTIambassador *rti);

    static void unsubscribe_interaction(const std::string &hlaClassName, RTI::RTIambassador *rti);

    static void soft_unsubscribe_interaction(const std::string &hlaClassName, RTI::RTIambassador *rti) {
        if (!loadDynamicHlaClass(hlaClassName, rti)) {
            BOOST_LOG_SEV(get_logger(), warning) << "soft_subscribe_interaction(\"" <<
              hlaClassName << "\"):  no such class";
            return;
        }

        set_is_soft_subscribed(hlaClassName, false);
    }

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
    void setParameter(
      const std::string &hlaClassName, const std::string &propertyName, const T &value
    ) {
        ClassAndPropertyNameSP classAndPropertyNameSP = findProperty(hlaClassName, propertyName);

        if (!classAndPropertyNameSP) {
            BOOST_LOG_SEV(get_logger(), error) << "setParameter(\"" << hlaClassName << "\", "
              << "\"" << propertyName << "\", " << typeid(T).name() << " value): could not find \"" << propertyName
              << "\" parameter in class \"" << hlaClassName << "\" or any of its superclasses.";
            return;
        }

        Value &currentValue = *_classAndPropertyNameValueSPMap[*classAndPropertyNameSP];

        if (!currentValue.setValue(value)) {
            BOOST_LOG_SEV(get_logger(), error) << "setParameter(\"" << propertyName << "\", "
              << typeid(T).name() << " value): \"value\" is incorrect type \"" << typeid(T).name()
              << "\" for \"" << propertyName << "\" parameter, should be of type \""
              << currentValue.getTypeName() << "\"";
        }
    }

    template<typename T>
    void setParameter(const ClassAndPropertyName &classAndPropertyName, const T &value) {
        setParameter(
          classAndPropertyName.getClassName(), classAndPropertyName.getPropertyName(), value
        );
    }

    template<typename T>
    void setParameter(const ClassAndPropertyNameSP &classAndPropertyNameSP, const T &value) {
        setParameter(*classAndPropertyNameSP, value);
    }

    template<typename T>
    void setParameter(const std::string &propertyName, const T &value) {
        setParameter(getInstanceHlaClassName(), propertyName, value);
    }

public:
    bool hasParameter(const std::string &hlaClassName, const std::string &propertyName) {
        return static_cast<bool>(findProperty(hlaClassName, propertyName));
    }

    bool hasParameter(const std::string &propertyName) {
        return hasParameter(getInstanceHlaClassName(), propertyName);
    }

    const Value &getParameter(
      const std::string &hlaClassName, const std::string &propertyName
    ) const override {
        static Value value(0);

        ClassAndPropertyNameSP classAndPropertyNameSP = findProperty(hlaClassName, propertyName);

        return classAndPropertyNameSP ? *(_classAndPropertyNameValueSPMap.find(*classAndPropertyNameSP)->second) : value;
    }

    const Value &getParameter(const ClassAndPropertyName &classAndPropertyName) {
        return getParameter(
          classAndPropertyName.getClassName(), classAndPropertyName.getPropertyName()
        );
    }

    const Value &getParameter(const ClassAndPropertyNameSP &classAndPropertyNameSP) {
        return getParameter(*classAndPropertyNameSP);
    }

    const Value &getParameter(const std::string &propertyName) const override {
        return getParameter(getInstanceHlaClassName(), propertyName);
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
          "InteractionRoot"
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
     * Returns the fully-qualified (dot-delimited) name of the ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot interaction class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the name of the class pertaining to the reference,
     * rather than the name of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getJavaClassName()}.
     *
     * @return the fully-qualified Java class name for this interaction class
     */
    static const std::string &get_cpp_class_name() {
        static const std::string cppClassName("::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot");
        return cppClassName;
    }

    /**
     * Returns the fully-qualified (dot-delimited) name of this instance's interaction class.
     * Polymorphic equivalent of get_java_class_name static method.
     *
     * @return the fully-qualified (dot-delimited) name of this instance's interaction class
     */
    const std::string &getCppClassName() const override {
        return get_cpp_class_name();
    }

    /**
     * Returns the simple name (the last name in the dot-delimited fully-qualified
     * class name) of the edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot interaction class.
     *
     * @return the name of this interaction class
     */
    static const std::string get_simple_class_name() {
        return get_simple_class_name(get_hla_class_name());
    }

    /**
     * Returns the fully-qualified (dot-delimited) hla class name of the
     * InteractionRoot interaction class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the federation name of the class pertaining to the reference,
     * rather than the name of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getHlaClassName()}.
     *
     * @return the fully-qualified federation (HLA) class name for this interaction class
     */
    static const std::string &get_hla_class_name() {
        static const std::string hlaClassName("InteractionRoot");
        return hlaClassName;
    }

    /**
     * Returns the fully-qualified (dot-delimited) hla class name of this instance's interaction class.
     * Polymorphic equivalent of get_hla_class_name static method.
     *
     * @return the fully-qualified (dot-delimited) name of this instance's interaction class
     */
    const std::string &getHlaClassName() const override {
        return get_hla_class_name();
    }

    /**
     * Returns a sorted list containing the names of all of the non-hidden parameters in the
     * edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot interaction class.
     * The property names are paired with name of the hla class in which they are defined in a
     * ClassAndPropertyName POJO.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return a set of class-and0parameter names pertaining to the reference,
     * rather than the parameter names of the class for the instance referred to by
     * the reference.  For the polymorphic version of this method, use
     * {@link #getParameterNames()}.
     *
     * @return a sorted list of the non-hidden parameter names for this interaction class
     * paired with name of the hla class in which they are defined in a ClassAndPropertyName POJO.
     */
    static ClassAndPropertyNameList get_parameter_names() {
        return get_parameter_names( get_hla_class_name() );
    }

    /**
     * Returns a sorted list containing the names of all of the parameters in the
     * edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot interaction class.
     * The property names are paired with name of the hla class in which they are defined in a
     * ClassAndPropertyName POJO.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return a set of parameter names pertaining to the reference,
     * rather than the parameter names of the class for the instance referred to by
     * the reference.  For the polymorphic version of this method, use
     * {@link #getParameterNames()}.
     *
     * @return a sorted list of the parameter names for this interaction class
     * paired with name of the hla class in which they are defined in a ClassAndPropertyName POJO.
     */
    static ClassAndPropertyNameList get_all_parameter_names() {
        return get_all_parameter_names( get_hla_class_name() );
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
     * Returns the handle (RTI assigned) of the edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot interaction class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the handle of the class pertaining to the reference,
     * rather than the handle of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getClassHandle()}.
     *
     * @return the RTI assigned integer handle that represents this interaction class
     */
    static int get_class_handle() {
        return get_class_name_handle_map()[get_hla_class_name()];
    }

    /**
     * Returns the handle of an parameter (RTI assigned) of
     * this interaction class (i.e. "edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot") given the parameter's name.
     *
     * @param propertyName name of parameter
     * @return the handle (RTI assigned) of the parameter "propertyName" of interaction class "hlaClassName"
     */
    static int get_parameter_handle(const std::string &propertyName) {
        return get_parameter_handle(get_hla_class_name(), propertyName);
    }

    // ----------------------------------------------------------
    // END OF STATIC PROPERTYS AND CODE THAT DEAL WITH HANDLES.
    // ----------------------------------------------------------


    //-------------------------------------------------
    // METHODS FOR PUBLISHING/SUBSCRIBING-TO THIS CLASS
    //-------------------------------------------------

    /**
     * Publishes the edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot interaction class for a federate.
     *
     * @param rti handle to the Local RTI Component
     */
    static void publish_interaction(RTI::RTIambassador *rti) {
        publish_interaction( get_hla_class_name(), rti );
    }

    static bool get_is_published() {
        return get_is_published(get_hla_class_name());
    }

    /**
     * Unpublishes the edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot interaction class for a federate.
     *
     * @param rti handle to the Local RTI Component, usu. obtained through the
     *            {@link SynchronizedFederate#getRTI()} call
     */
    static void unpublish_interaction(RTI::RTIambassador *rti) {
        unpublish_interaction( get_hla_class_name(), rti);
    }

/**
 * Subscribes a federate to the edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot interaction class.
 *
 * @param rti handle to the Local RTI Component
 */
    static void subscribe_interaction(RTI::RTIambassador *rti) {
        subscribe_interaction( get_hla_class_name(), rti );
    }

    static bool get_is_subscribed() {
        return get_is_subscribed(get_hla_class_name());
    }

    static void soft_subscribe_interaction(RTI::RTIambassador *rti) {
        soft_subscribe_interaction(get_hla_class_name(), rti);
    }

    static bool get_is_soft_subscribed() {
        return get_is_soft_subscribed(get_hla_class_name());
    }

    /**
     * Unsubscribes a federate from the edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot interaction class.
     *
     * @param rti handle to the Local RTI Component
     */
    static void unsubscribe_interaction(RTI::RTIambassador *rti) {
        unsubscribe_interaction( get_hla_class_name(), rti );
    }

    static void soft_unsubscribe_interaction(RTI::RTIambassador *rti) {
        soft_unsubscribe_interaction(get_hla_class_name(), rti);
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
     * (that is, the edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot interaction class).
     *
     * @param handle handle to compare to the value of the handle (RTI assigned) of
     * this class (the edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot interaction class).
     * @return "true" if "handle" matches the value of the handle of this class
     * (that is, the edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot interaction class).
     */
    static bool match(int handle) {
        return handle == get_class_handle();
    }

    static int get_num_parameters() {
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
        return SP(new InteractionRoot());
    }

    static SP create_interaction() {
        return SP(new InteractionRoot());
    }

    virtual SP createInteraction() {
        return create_interaction();
    }

    static SP create(const RTIfedTime &rtiFedTime) {
        return SP(new InteractionRoot(rtiFedTime));
    }

    static SP create_interaction(const RTIfedTime &rtiFedTime) {
        return SP(new InteractionRoot(rtiFedTime));
    }

    virtual SP createInteraction(const RTIfedTime &rtiFedTime) {
        return create_interaction(rtiFedTime);
    }

    static SP create(
      const RTI::ParameterHandleValuePairSet &propertyMap
    ) {
        return SP(new InteractionRoot(propertyMap));
    }

    static SP create_interaction(
      const RTI::ParameterHandleValuePairSet &propertyMap
    ) {
        return SP(new InteractionRoot(propertyMap));
    }

    virtual SP createInteraction(
      const RTI::ParameterHandleValuePairSet &propertyMap
    ) {
        return create_interaction(propertyMap);
    }

    static SP create(
      const RTI::ParameterHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) {
        return SP(new InteractionRoot(propertyMap, rtiFedTime));
    }

    static SP create_interaction(
      const RTI::ParameterHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) {
        return SP(new InteractionRoot(propertyMap, rtiFedTime));
    }

    virtual SP createInteraction(
      const RTI::ParameterHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime) {
        return create_interaction(propertyMap, rtiFedTime);
    }

    virtual SP cloneInteraction() {
        return SP( new InteractionRoot( *this )  );
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
     * Returns the timestamp for this interaction.  "receive order" interactions
     * should have a timestamp of -1.
     *
     * @return timestamp for this interaction
     */
public:
    double getTime() {
        return _time;
    }

    /**
     * Sets the timestamp of this interaction to "time".
     *
     * @param time new timestamp for this interaction
     */
    void setTime( double time ) {
        _time = time;
    }

    /**
     * Sets the timestamp of this interaction to "logicalTime".
     *
     * @param logicalTime new timestamp for this interaction
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
    InteractionRoot(NoInstanceInit &noInstanceInit) : _uniqueId(generate_unique_id()) { }

private:
    void initializeProperties(const std::string &hlaClassName);

    /**
     * Creates a new InteractionRoot instance.
     */
    // THE CONSTRUCTORS IN THE ANALOGOUS POSITION TO THIS POSITION IN THE JavaMessagingRoot.jinja2 FILE ARE IN THE
    // CppMessagingHeaderCommon.jinja2 FILE FOR C++ AS C++ DOES NOT SUPPORT INSTANCE-INITIALIZATION BLOCKS.
    //
public:

    InteractionRoot(const InteractionRoot &copyFrom) :
      _uniqueId(generate_unique_id()) {
        setInstanceHlaClassName(copyFrom.getInstanceHlaClassName());
        for(
          typename ClassAndPropertyNameValueSPMap::const_iterator cvmCit =
            copyFrom.getClassAndPropertyNameValueSPMap().begin() ;
          cvmCit != copyFrom.getClassAndPropertyNameValueSPMap().end() ;
          ++cvmCit
        ) {
            _classAndPropertyNameValueSPMap.emplace(cvmCit->first, ValueSP(new Value(*cvmCit->second)));
        }
    }


    InteractionRoot() : _uniqueId(generate_unique_id()) {
        initializeProperties(get_hla_class_name());
    }

    InteractionRoot( const RTIfedTime &rtiFedTime) :
      _uniqueId(generate_unique_id()) {
        initializeProperties(get_hla_class_name());
        setTime(rtiFedTime.getTime());
    }

    InteractionRoot(const RTI::ParameterHandleValuePairSet &propertyMap)
      : _uniqueId(generate_unique_id()) {
        initializeProperties(get_hla_class_name());
        setParameters( propertyMap );
    }

    InteractionRoot(
      const RTI::ParameterHandleValuePairSet &propertyMap,
      const RTIfedTime &rtiFedTime
    ) : _uniqueId(generate_unique_id()) {
        initializeProperties(get_hla_class_name());
        setParameters( propertyMap );
        setTime(rtiFedTime.getTime());
    }

    InteractionRoot( const std::string &hlaClassName ) : _uniqueId(generate_unique_id()) {
        initializeProperties(hlaClassName);
    }

    InteractionRoot( const std::string &hlaClassName, const RTIfedTime &rtiFedTime) :
      _uniqueId(generate_unique_id()) {
        initializeProperties(hlaClassName);
        setTime(rtiFedTime.getTime());
    }

    InteractionRoot(
      const std::string &hlaClassName, const RTI::ParameterHandleValuePairSet &propertyMap
    ) : _uniqueId(generate_unique_id()) {
        initializeProperties(hlaClassName);
        setParameters( propertyMap );
    }

    InteractionRoot(
      const std::string &hlaClassName,
      const RTI::ParameterHandleValuePairSet &propertyMap,
      const RTIfedTime &rtiFedTime
    ) : _uniqueId(generate_unique_id()) {
        initializeProperties(hlaClassName);
        setParameters( propertyMap );
        setTime(rtiFedTime.getTime());
    }

    //-----------------
    // END CONSTRUCTORS
    //-----------------

public:
    void setParameters( const RTI::ParameterHandleValuePairSet &propertyMap );

    template<typename T>
    void setParameter(int propertyHandle, const T &value) {

        IntegerClassAndPropertyNameSPMap::iterator hcmItr =
          get_handle_class_and_property_name_sp_map().find(propertyHandle);

        if (hcmItr == get_handle_class_and_property_name_sp_map().end()) {
            BOOST_LOG_SEV(get_logger(), error) << "setParameter(int propertyHandle, "
              << typeid(T).name() << " value): propertyHandle (" << propertyHandle << ") does not exist.";
            return;
        }

        ClassAndPropertyName &classAndPropertyName = *hcmItr->second;

        ClassAndPropertyNameValueSPMap::iterator cvmItr = _classAndPropertyNameValueSPMap.find(classAndPropertyName);
        if (cvmItr == _classAndPropertyNameValueSPMap.end()) {
            BOOST_LOG_SEV(get_logger(), error) << "setParameter(int propertyHandle, "
            << typeid(T).name() << " value): propertyHandle (" << propertyHandle
            << ") corresponds to property of name \"" << classAndPropertyName.getPropertyName()
            << "\", which does not exist in class \"" << getInstanceHlaClassName() << "\" (it's defined in class \""
            << classAndPropertyName.getClassName() << "\")";
        }

        Value &currentValue = *_classAndPropertyNameValueSPMap[*hcmItr->second];
        if (!currentValue.setValue(value)) {
            BOOST_LOG_SEV(get_logger(), error) << "setParameter(int propertyHandle, "
              << typeid(T).name() << " value): \"value\" is incorrect type \"" << typeid(T).name()
              << "\" for \"" << classAndPropertyName.getPropertyName() << "\" parameter, should be of type \""
              << currentValue.getTypeName() << "\"";
        }
    }

    void sendInteraction( RTI::RTIambassador *rti, double time );
    void sendInteraction( RTI::RTIambassador *rti );

    //---------------------------------------------------------------
    // INSTANCE VERSIONS OF STATIC METHODS DEFINED IN DERIVED CLASSES
    //---------------------------------------------------------------

    /**
     * Returns the simple name (last name in its fully-qualified dot-delimited name)
     * of this instance's interaction class.
     * Polymorphic equivalent of the get_simple_class_name static method.
     *
     * @return the simple name of this instance's interaction class
     */
    const std::string getSimpleClassName() const override {
        return get_simple_class_name( getInstanceHlaClassName() );
    }

    /**
     * Returns a sorted list containing the names of all of the non-hiddenparameters of an
     * interaction class instance.
     * The property names are paired with name of the hla class in which they are defined in a
     * ClassAndPropertyName POJO.
     * Polymorphic equivalent to get_parameter_names static method.
     *
     * @return sorted list containing the names of all of the parameters of an
     * interaction class instance paired with name of the hla class in which they are defined in a
     * ClassAndPropertyName POJO.
     */
    const ClassAndPropertyNameList getParameterNames() const override {
        return get_parameter_names( getInstanceHlaClassName() );
    }

    /**
     * Returns a sorted list containing the names of all of the parameters of an
     * interaction class instance.
     * The property names are paired with name of the hla class in which they are defined in a
     * ClassAndPropertyName POJO.
     * Polymorphic equivalent of get_all_parameter_names() static method.
     *
     * @return sorted list containing the names of all of the parameters of an
     * interaction class instance paired with name of the hla class in which they are defined in a
     * ClassAndPropertyName POJO.
     */
    const ClassAndPropertyNameList getAllParameterNames() const override {
        return get_all_parameter_names( getInstanceHlaClassName() );
    }

    /**
     * Returns the handle (RTI assigned) of this instance's interaction class.
     * Polymorphic equivalent for get_class_handle static method.
     *
     * @return the handle (RTI assigned) if this instance's interaction class
     */
    int getClassHandle() const override {
        return get_class_handle( getInstanceHlaClassName() );
    }

    int getParameterHandle(const std::string &propertyName) {
        return get_parameter_handle( getInstanceHlaClassName(), propertyName );
    }

    /**
     * Publishes the interaction class of this instance of the class for a federate.
     * Polymorphic equalivalent of publish_interaction static method.
     *
     * @param rti handle to the Local RTI Component
     */
    void publishInteraction(RTI::RTIambassador *rti) {
        publish_interaction(getInstanceHlaClassName(), rti);
    }

    /**
     * Unpublishes the interaction class of this instance of this class for a federate.
     * Polymorphic equivalent of unpublish_interaction static method.
     *
     * @param rti handle to the Local RTI Component
     */
    void unpublishInteraction(RTI::RTIambassador *rti) {
        unpublish_interaction(getInstanceHlaClassName(), rti);
    }

    /**
     * Subscribes a federate to the interaction class of this instance of this class.
     * Polymorphic equivalent of subscribe_interaction static method.
     *
     * @param rti handle to the Local RTI Component
     */
    void subscribeInteraction(RTI::RTIambassador *rti) {
        subscribe_interaction(getInstanceHlaClassName(), rti);
    }

    /**
     * Unsubscribes a federate from the interaction class of this instance of this class.
     *
     * @param rti handle to the Local RTI Component
     */
    void unsubscribeInteraction(RTI::RTIambassador *rti) {
        unsubscribe_interaction(getInstanceHlaClassName(), rti);
    }

    void softSubscribeInteraction(RTI::RTIambassador *rti) {
        soft_subscribe_interaction(getInstanceHlaClassName(), rti);
    }

    void softUnsubscribeInteraction(RTI::RTIambassador *rti) {
        soft_unsubscribe_interaction(getInstanceHlaClassName(), rti);
    }


    //-------------------------------------------------------------------
    // END INSTANCE VERSIONS OF STATIC METHODS DEFINED IN DERIVED CLASSES
    //-------------------------------------------------------------------

    std::string toJson();

    static SP fromJson(const std::string &jsonString);

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
        if (get_class_name_handle_map().find(hlaClassName) == get_class_name_handle_map().end()) {
            if (get_hla_class_name_set().find(hlaClassName) == get_hla_class_name_set().end()) {
                readFederateDynamicMessageClass(hlaClassName);
                if (get_hla_class_name_set().find(hlaClassName) == get_hla_class_name_set().end()) {
                    return false;
                }
            }
            init(hlaClassName, rti);
        }
        return true;
    }

public:
    explicit operator std::string() const;
};
    } // NAMESPACE "hla"
   } // NAMESPACE "cpswt"
  } // NAMESPACE "vuisis"
 } // NAMESPACE "vanderbilt"
} // NAMESPACE "edu"

inline std::ostream &operator<<(
  std::ostream &os, const ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot &messaging
) {
    return os << static_cast<std::string>(messaging);
}
inline std::ostream &operator<<(
  std::ostream &os, ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot::SP messagingSP
) {
    return os << static_cast<std::string>(*messagingSP);
}

inline boost::log::formatting_ostream& operator<<(
  boost::log::formatting_ostream& os, const ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot &messaging
) {
    return os << static_cast<std::string>(messaging);
}
inline boost::log::formatting_ostream &operator<<(
  boost::log::formatting_ostream &os, ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot::SP messagingSP
) {
    return os << static_cast<std::string>(*messagingSP);
}

#endif // _INTERACTION_ROOT
