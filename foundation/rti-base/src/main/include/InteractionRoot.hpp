

/*
 * Copyright (c) 2008, Institute for Software Integrated Systems, Vanderbilt University
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice, the following
 * two paragraphs and the author appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE VANDERBILT UNIVERSITY BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE VANDERBILT
 * UNIVERSITY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE VANDERBILT UNIVERSITY SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE VANDERBILT UNIVERSITY HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 */

#ifndef _INTERACTION_ROOT_CLASS
#define _INTERACTION_ROOT_CLASS

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <set>
#include <map>
#include <list>
#include <cctype>
#include <cstdlib>

#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>

#include <jsoncpp/json/json.h>
#include <TypeMedley.hpp>

#include <StringCollections.hpp>

#include "RTI.hh"
#include "fedtime.hh"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "RTILogger.hpp"

#ifndef C2W_RTI_LOGGER_CLS
#define C2W_RTI_LOGGER_CLS C2WConsoleLogger
#endif

#include "InteractionRootInterface.hpp"


namespace org {
 namespace cpswt {
  namespace hla {

class Interaction : public InteractionInterface {

public:
    typedef boost::shared_ptr<Interaction> SP;
    typedef boost::shared_ptr<RTI::ParameterHandleValuePairSet> PopertyHandleValuePairSetSP;

    typedef boost::shared_ptr<ClassAndPropertyNameSet> ClassAndPropertyNameSetSP;

    typedef std::map<std::string, ClassAndPropertyNameSetSP> StringClassAndPropertyNameSetSPMap;
    typedef std::map< std::string, StringVector > NameStringVectorPtrMap;
    typedef std::map< ClassAndPropertyName, int > ClassAndPropertyNameIntegerMap;
    typedef std::map<int, ClassAndPropertyNameSP> IntegerClassAndPropertyNameSPMap;
    typedef std::map<int, std:string> IntegerStringMap;

    typedef RTI::AttributeHandleSet AttributeHandleSet;
    typedef boost::shared_ptr<AttributeHandleSet> AttributeHandleSetSP;

    typesef std::map<std::string, SP> StringInstanceSPMap;

    typedef TypeMedley Value;
    typedef RTI::ParameterHandleValuePairSet PropertyHandleValuePairSet;

    typedef boost::shared_ptr<Value> ValueSP
    typedef std::unordered_map<ClassAndPropertyName, ValueSP> ClassAndPropertyNameValueSPMap;
    typedef boost::shared_ptr<PropertyHandleValuePairSet> PropertyHandleValuePairSetSP;

    typedef void (*PubsubFunctionPtr)( RTI::RTIambassador * );
    typedef std::map< std::string, PubsubFunctionPtr > ClassNamePubSubMap;
    typedef std::map< std::string, std::string> DatamemberTypeMap;

private:
    static int generateUniqueID() {
        static int globalUniqueID = 0;
        return globalUniqueID++;
    }

    const int _uniqueID;

public:
    int getUniqueID() {
        return _uniqueID;
    }

    //---------------
    // CLASS-NAME SET
    //---------------
protected:
    static StringSet &get_class_name_set( void ) {
        static StringSet classNameSet;
        return classNameSet;
    }

    //--------------------------------
    // METHODS THAT USE CLASS-NAME-SET
    //--------------------------------
public:
    static const StringSet &get_interaction_names( void ) {
        return getClassNameSet();
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

    //--------------------------------
    // END CLASS-NAME CLASS-HANDLE MAP
    //--------------------------------

    //-----------------------------------
    // CLASS-NAME DATAMEMBER-NAME-SET MAP
    //-----------------------------------
protected:
    static StringClassAndPropertyNameSetSPMap &get_class_name_property_name_set_sp_map() {
        static StringClassAndPropertyNameSetSPMap classNamePropertyNameSetSPMap;
        return classNamePropertyNameSetSPMap;
    }

    //----------------------------------------------------
    // METHODS THAT USE CLASS-NAME DATAMEMBER-NAME-SET MAP
    //----------------------------------------------------
public:
    static const ClassAndPropertyNameSetSP &get_parameter_names(const std::string &className) {
       StringClassAndPropertyNameSetSPMap::iterator scmItr =
         get_class_name_property_name_set_ptr_map().find(className);

       return scmItr == get_class_name_property_name_set_ptr_map().end()
         ? ClassAndPropertyNameSetSP(static_cast<ClassAndPropertyNameSet *>(0))
         : scmItr->second;
    }

    //---------------------------------------
    // END CLASS-NAME DATAMEMBER-NAME-SET MAP
    //---------------------------------------

    //---------------------------------------
    // CLASS-NAME ALL-DATAMEMBER-NAME-SET MAP
    //---------------------------------------
protected:
    static StringClassAndPropertyNameSetSPMap &get_class_name_all_property_name_set_sp_map() {
        static StringClassAndPropertyNameSetSPMap classNameAllPropertyNameSetSPMap;
        return classNameAllPropertyNameSetSPMap;
    }

    //--------------------------------------------------------
    // METHODS THAT USE CLASS-NAME ALL-DATAMEMBER-NAME-SET MAP
    //--------------------------------------------------------
public:
    static const ClassAndPropertyNameSetSP &get_all_parameter_names(const std::string &className) {
       StringClassAndPropertyNameSetSPMap::iterator scmItr =
         get_class_name_all_property_name_set_ptr_map().find(className);

       return scmItr == get_class_name_all_property_name_set_ptr_map().end()
         ? ClassAndPropertyNameSetSP(static_cast<ClassAndPropertyNameSet *>(0))
         : scmItr->second;
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
    static std::string join(const std::list<std::string> &joinList, cons std:string &delimiter);

public:
    static ClassAndPropertyNameSP findProperty(const std:string &className, const std::string &propertyName);

    static int get__handle(const std::string &className, const std::string &propertyName) {
        ClassAndPropertyNameSP key = findProperty(className, propertyName);
        if (!key) {
            return -1
        }

        return get_class_and_property_name_handle_map()[key];
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
    static ClassAndPropertyNameSP get_class_and_parameter_name(int propertyHandle) {
        IntegerClassAndPropertyNameSPMap::iterator icmItr =
          get_handle_class_and_property_name_sp_map().find(propertyHandle);
        return icmItr == get_handle_class_and_property_name_sp_map().end()
          ? ClassAndPropertyNameSP(static_cast<ClassAndPropertyName *>0) : icmItr->second;
    }

    ClassAndPropertyNameSP getClassAndParameterName(int propertyHandle) {
        return get_class_and_parameter_name(propertyHandle);
    }

    const std::string &getParameterName(int propertyHandle) {
        static std::string emptyString;
        ClassAndPropertyNameSP classAndPropertyNameSP = get_class_and_parameter_name(propertyHandle);
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
    static StringInstanceSPMap &get_class_name_instance_sp_map() {
        static StringInstanceSPMap classNameInstanceMap;
        return classNameInstanceMap;
    }

    static SP create_interaction(const std::string &className) {
        StringInstanceSPMap::iterator cimItr = get_class_name_instance_sp_map().find(className);
        return cimItr == get_class_name_instance_sp_map().end()
          ? SP( ( *)0 )
          : cimItr->second->createInteraction();
    }

    static SP create_interaction(const std::string &className, const RTIfedTime &rtiFedTime) {
        StringInstanceSPMap::iterator cimItr = get_class_name_instance_sp_map().find( className );
        return cimItr == get_class_name_instance_sp_map().end()
          ? SP( ( *)0 )
          : cimItr->second->createcreateInteraction(rtiFedTime);
    }

    static void publish_interaction(const std::string &className, RTI::RTIambassador *rtiAmbassador) {
        StringInstanceSPMap::iterator cimItr = get_class_name_instance_sp_map().find(className);
        if (cimItr != get_class_name_instance_sp_map().end()) {
            cimItr->second->publishInteraction(rtiAmbassador);
        }
    }

    static void unpublish_interaction(const std::string &className, RTI::RTIambassador *rtiAmbassador) {
        StringInstanceSPMap::iterator cimItr = get_class_name_instance_sp_map().find(className);
        if (cimItr != get_class_name_instance_sp_map().end()) {
            cimItr->second->unpublishInteraction(rtiAmbassador);
        }
    }

    static void subscribe_interaction(const std::string &className, RTI::RTIambassador *rtiAmbassador) {
        StringInstanceSPMap::iterator cimItr = get_class_name_instance_sp_map().find(className);
        if (cimItr != get_class_name_instance_sp_map().end()) {
            cimItr->second->subscribeInteraction(rtiAmbassador);
        }
    }

    static void unsubscribe_interaction(const std::string &className, RTI::RTIambassador *rtiAmbassador) {
        StringInstanceSPMap::iterator cimItr = get_class_name_instance_sp_map().find(className);
        if (cimItr != get_class_name_instance_sp_map().end()) {
            cimItr->second->unsubscribeInteraction(rtiAmbassador);
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
    static String get_hla_class_name(int classHandle) {
        IntegerStringMap::iterator ismItr = get_class_handle_name_map().find(classHandle);
        return ismItr == get_class_handle_name_map().end() ? "" : ismitr->second;
    }

    static SP create_interaction(int classHandle) {
        IntegerStringMap::iterator ismItr = get_class_handle_name_map().find(classHandle);
        return ismItr == get_class_handle_name_map().end()
          ? SP( (Interaction *)0 )
          : create_interaction(ismItr->second);
    }

    static SP create_interaction(int classHandle, const RTIfedTime &rtiFedTime) {
        IntegerStringMap::iterator ismItr = get_class_handle_name_map().find(classHandle);
        return ismItr == get_class_handle_name_map().end()
          ? SP( ( *)0 )
          : create_interaction(ismItr->second, rtiFedTime);
    }

    static SP create_interaction(int classHandle, const RTI::ParameterHandleValuePairSet &datamemberMap);
    static SP create_interaction(int classHandle, const RTI::ParameterHandleValuePairSet &datamemberMap, const RTIfedTime &rtiFedTime);

    //------------------------------------------------------
    // END METHODS THAT USE ONLY CLASS-HANDLE CLASS-NAME MAP
    //------------------------------------------------------


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
        PropertyClassNameAndValue(const std::string &className, ValueSP &localValueS{)
         className(className), valueSP(localValueSP) {}

        const std::string &getClassName() {
            return className;
        }

        const ValueSP &getValueSP() {
            return valueSP;
        }
    };

    typedef boost:shared_ptr<PropertyClassNameAndValue> PropertyClassNameAndValueSP;

    //------------------------------------------------------------
    // METHODS THAT USE CLASS-AND-PROPERTY-NAME PROPERTY-VALUE MAP
    //------------------------------------------------------------
public:
    template<typename T>
    void setParameter(const std::string &propertyName, const T &value) {

        PropertyClassNameAndValueSP propertyClassNameAndValueSP =
          getParameterAux(getHlaClassName(), propertyName);

        if (!propertyClassNameAndValueSP) {
//            logger.error(
//              "setparameter(\"{}\", {} value): could not find \"{}\" parameter of class \"{}\" or its " +
//              "superclasses.", propertyName, value.getClass().getName(), propertyName, getHlaClassName()
//            );
            return;
        }

        Value currentValue = *propertyClassNameAndValueSP->getValueSP();

        if (!currentValue.setValue(value)) {
//            logger.error(
//              "setparameter(\"{}\", {} value): \"value\" is incorrect type \"{}\" for \"{}\" parameter, " +
//              "should be of type \"{}\".",
//              propertyName,
//              value.getClass().getName(),
//              value.getClass().getName(),
//              propertyName,
//              currentValue.getClass().getName()
//            );
        }
    }

    void setParameter(int propertyHandle, Object value) {
        ClassAndPropertyNameSP classAndPropertyNameSP = _handleClassAndPropertyNameMap.get(propertyHandle);
        if (!classAndPropertyNameSP) {
//            logger.error(
//              "setParameter(int, Object value): propertyHandle {} does not exist.",
//              propertyHandle
//            );
            return;
        }

        String propertyName = classAndPropertyNameSP->getPropertyName();
        ValueSP valueSP = getParameter(propertyName);
        if (!valueSP) {
//            logger.error(
//                "setParameter: propertyHandle {} corresponds to property of name \"{}\", which " +
//                "does not exist in class \"{}\" (it's defined in class\"{}\")",
//                propertyHandle, propertyName, getClass(), classAndPropertyName.getClassName()
//            );
        }

        setParameter(propertyName, value);
    }

    //
    // getParameterAux METHODS ARE DEFINED IN SUBCLASSES.
    //

    /**
     * Returns the value of the parameter named "propertyName" for this
     * interaction.
     *
     * @param propertyName name of parameter whose value to retrieve
     * @return the value of the parameter whose name is "propertyName"
     */
    const Value &getParameter(const std::string &propertyName) {
        return *getParameterAux(getHlaClassName(), propertyName)->getValue();
    }

    /**
     * Returns the value of the parameter whose handle is "propertyHandle"
     * (RTI assigned) for this interaction.
     *
     * @param propertyHandle handle (RTI assigned) of parameter whose
     * value to retrieve
     * @return the value of the parameter whose handle is "propertyHandle"
     */
    public const Value &getParameter( int propertyHandle );

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
     * Returns the fully-qualified (dot-delimited) name of the org.cpswt.hla.InteractionRoot interaction class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the name of the class pertaining to the reference,
     * rather than the name of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getJavaClassName()}.
     *
     * @return the fully-qualified Java class name for this interaction class
     */
    static const std::string &get_cpp_class_name() {
        static const std::string cppClassName("::org::cpswt::hla::InteractionRoot");
        return cppClassName;
    }

    /**
     * Returns the fully-qualified (dot-delimited) name of this instance's interaction class.
     * Polymorphic equivalent of get_java_class_name static method.
     *
     * @return the fully-qualified (dot-delimited) name of this instance's interaction class
     */
    virtual const std::string &getCppClassName() {
        return get_cpp_class_name();
    }

    /**
     * Returns the simple name (the last name in the dot-delimited fully-qualified
     * class name) of the org.cpswt.hla.InteractionRoot interaction class.
     *
     * @return the name of this interaction class
     */
    static const std::string &get_simple_class_name() {
        static const std::string simpleClassName("InteractionRoot");
        return simpleClassName;
    }

    /**
     * Returns the simple name (last name in its fully-qualified dot-delimited name)
     * of this instance's interaction class.
     * Polymorphic equivalent of the get_simple_class_name static method.
     *
     * @return the simple name of this instance's interaction class
     */
    virtual const std::string &getSimpleClassName() {
        return get_simple_class_name();
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
    virtual const std::string &getHlaClassName() {
        return get_hla_class_name();
    }

private:
    static ClassAndPropertyNameSetSP &get_class_and_property_name_set_sp() {
        static ClassAndPropertyNameSetSP classAndPropertyNameSetSP(new ClassAndPropertyNameSet());
        return classAndPropertyNameSetSP;
    }

public:
    /**
     * Returns a sorted list containing the names of all of the non-hidden parameters in the
     * org.cpswt.hla.InteractionRoot interaction class.
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
        const ClassAndPropertyNameSet &classAndPropertyNameSet(*get_class_and_property_name_set_sp());
        std::list<ClassAndPropertyName> classAndPropertyNameList(
          classAndPropertyNameSet.begin(), classAndPropertyNameSet.end()
        );
        classAndPropertyNameList.sort();
        return classAndPropertyNameList;
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
    virtual ClassAndPropertyNameList getParameterNames() {
        return get_parameter_names();
    }

private:
    static ClassAndPropertyNameSetSP &get_all_class_and_property_name_set_sp() {
        static ClassAndPropertyNameSetSP allClassAndPropertyNameSetSP(new ClassAndPropertyNameSet());
        return allClassAndPropertyNameSetSP;
    }

public:
    /**
     * Returns a sorted list containing the names of all of the parameters in the
     * org.cpswt.hla.InteractionRoot interaction class.
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
        const ClassAndPropertyNameSet &allClassAndPropertyNameSet(*get_all_class_and_property_name_set_sp());
        ClassAndPropertyNameList allClassAndPropertyNameList(
          allClassAndPropertyNameSet.begin(), allClassAndPropertyNameSet.end()
        );
        allClassAndPropertyNameList.sort();
        return allClassAndPropertyNameList;
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
    virtual ClassAndPropertyNameList getAllParameterNames() {
        return get_all_parameter_names();
    }


public:
    /*
     * INITIALIZE STATIC DATAMEMBERS THAT DEAL WITH NAMES
     */
    static bool static_init();

    // --------------------------------------------------------
    // END OF STATIC DATAMEMBERS AND CODE THAT DEAL WITH NAMES.
    // --------------------------------------------------------


public:
    // ----------------------------------------------------------------------------
    // STATIC DATAMEMBERS AND CODE THAT DEAL WITH HANDLES.
    // THIS CODE IS STATIC BECAUSE IT IS CLASS-DEPENDENT AND NOT INSTANCE-DEPENDENT
    // ----------------------------------------------------------------------------
    /**
     * Returns the handle (RTI assigned) of the org.cpswt.hla.InteractionRoot interaction class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the handle of the class pertaining to the reference,
     * rather than the handle of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getClassHandle()}.
     *
     * @return the RTI assigned integer handle that represents this interaction class
     */
    static int &get_class_handle() {
        static int _handle;
        return _handle;
    }

    /**
     * Returns the handle (RTI assigned) of this instance's interaction class.
     * Polymorphic equivalent for get_class_handle static method.
     *
     * @return the handle (RTI assigned) if this instance's interaction class
     */
    virtual int getClassHandle() {
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
     * THIS METHOD IS INDIRECTLY CALLED VIA THE "get_parameter_handle(String)" METHOD BELOW, WHICH PROVIDES THE
     * VALUE FOR THE "className" ARGUMENT.
     */
    static int get_parameter_handle_aux(const std::string &className, const std:string &propertyName);

public:
    /**
     * Returns the handle of an parameter (RTI assigned) of
     * this interaction class (i.e. "org.cpswt.hla.InteractionRoot") given the parameter's name.
     *
     * @param propertyName name of parameter
     * @return the handle (RTI assigned) of the parameter "propertyName" of interaction class "className"
     */
    static int get_parameter_handle(const std::string &propertyName) {
        return get_parameter_handle_aux(get_hla_class_name(), propertyName);
    }

    /**
     * Returns the handle associated with the given parameter name for an interaction class instance
     * Polymorphic equivalent of get_parameter_handle static method.
     *
     * @param propertyName the name of a parameter that belongs to this interaction class
     * @return the RTI handle associated with the parameter name, or -1 if not found
     */
    virtual int getParameterHandle(const std::string &propertyName) {
        return get_parameter_handle(propertyName);
    }

private:
    static bool &get_is_initialized() {
        static bool isInitialized = false;
        return isInitialized;
    }

protected:
    /*
     * THIS FUNCTION INITIALIZES ALL OF THE HANDLES ASSOCIATED WITH THIS INTERACTION CLASS
     * IT NEEDS THE RTI TO DO SO.
     */
    static void init(RTIambassador rti);

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
     * Publishes the org.cpswt.hla.InteractionRoot interaction class for a federate.
     *
     * @param rti handle to the Local RTI Component
     */
    static void publish_interaction(RTI::RTIambassador *rti);

    /**
     * Publishes the interaction class of this instance of the class for a federate.
     * Polymorphic equalivalent of publish_interaction static method.
     *
     * @param rti handle to the Local RTI Component
     */
    virtual void publishInteraction(RTI::RTIambassador *rti) {
        publish_interaction(rti);
    }


    /**
     * Unpublishes the org.cpswt.hla.InteractionRoot interaction class for a federate.
     *
     * @param rti handle to the Local RTI Component, usu. obtained through the
     *            {@link SynchronizedFederate#getLRC()} call
     */
    static void unpublish_interaction(RTI::RTIambassador *rti);

    /**
     * Unpublishes the interaction class of this instance of this class for a federate.
     * Polymorphic equivalent of unpublish_interaction static method.
     *
     * @param rti handle to the Local RTI Component
     */
    virtual void unpublishInteraction(RTI::RTIambassador *rti) {
        unpublish_interaction(rti);
    }

private:
    static bool &get_is_subscribed() {
        static bool isSubscribed = false;
        return isSubscribed;
    }

/**
 * Subscribes a federate to the org.cpswt.hla.InteractionRoot interaction class.
 *
 * @param rti handle to the Local RTI Component
 */
public:
    static void subscribe_interaction(RTI::RTIambassador *rti);

    /**
     * Subscribes a federate to the interaction class of this instance of this class.
     * Polymorphic equivalent of subscribe_interaction static method.
     *
     * @param rti handle to the Local RTI Component
     */
    virtual void subscribeInteraction(RTI::RTIambassador *rti) {
        subscribe_interaction(rti);
    }

    /**
     * Unsubscribes a federate from the org.cpswt.hla.InteractionRoot interaction class.
     *
     * @param rti handle to the Local RTI Component
     */
    static void unsubscribe_interaction(RTIambassador rti);

public:
    /**
     * Unsubscribes a federate from the interaction class of this instance of this class.
     *
     * @param rti handle to the Local RTI Component
     */
    virtual void unsubscribeInteraction(RTI::RTIambassador *rti) {
        unsubscribe_interaction(rti);
    }

    //-----------------------------------------------------
    // END METHODS FOR PUBLISHING/SUBSCRIBING-TO THIS CLASS
    //-----------------------------------------------------

public:
    /**
     * Return true if "handle" is equal to the handle (RTI assigned) of this class
     * (that is, the org.cpswt.hla.InteractionRoot interaction class).
     *
     * @param handle handle to compare to the value of the handle (RTI assigned) of
     * this class (the org.cpswt.hla.InteractionRoot interaction class).
     * @return "true" if "handle" matches the value of the handle of this class
     * (that is, the org.cpswt.hla.InteractionRoot interaction class).
     */
    static bool match(int handle) {
        return handle == get_class_handle();
    }


    //--------------------------------
    // DATAMEMBER MANIPULATION METHODS
    //--------------------------------

public:

protected:
    virtual PropertyClassNameAndValueSP getParameterAux(
      const std::string &className, const std::string &propertyName
    );

    //------------------------------------
    // END DATAMEMBER MANIPULATION METHODS
    //------------------------------------


    //--------------------------
    // INSTANCE CREATION METHODS
    //--------------------------
public:
    static SP create_interaction() {
        return SP(new Interaction());
    }

    virtual SP createInteraction() {
        return create_interaction();
    }

    static SP create_interaction(const RTIfedTime &rtiFedTime) {
        SP messagingRootSP(new Interaction());
        messagingRootSP->setTime(rtiFedTime.getTime());
        return messagingRootSP;
    }

    virtual SP createInteraction(const RTIfedTime &rtiFedTime) {
        return create_interaction(rtiFedTime);
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
    void setTime( const RTIfedTime &rtiFedTime ) {
        setTime( rtiFedTime.getTime() );
    }

    //-----------------
    // END TIME SET/GET
    //-----------------

    //-------------
    // CONSTRUCTORS
    //-------------

    /**
     * Creates a new Interaction instance.
     */
private:
    void defaultConstructorInit() {
        _uniqueID = generateUniqueID();
    }

    void propertyMapInitFlagConstructorInit(RTI::ParameterHandleValuePairSet propertyMap, bool initFlag) {
        defaultConstructorInit();
        if ( initFlag ) setParameters( propertyMap );
    }

    void propertyMapTimeInitFlagConstructorInit( RTI::ParameterHandleValuePairSet propertyMap, const RTIfedTime &rtiFedTime, boolean initFlag) {
        propertyMapInitFlagConstructorInit(propertyMap, initFlag);
        setTime( rtiFedTime );
    }

public:
    Interaction() {
        defaultConstructorInit();
    }

private:
    void setParameter(int propertyHandle, const std::string &value) {
        ClassAndPropertyNameSP classAndPropertyNameSP = get_class_and_parameter_name(propertyHandle);
        if (!classAndPropertyNameSP) {
            // ERROR
            return;
        }
        const ClassAndPropertyName &classAndPropertyName = *classAndPropertyNameSP;
        _classAndPropertyNameValueSPMap[classAndPropertyName].setValue(value);
    }

public:
    void setParameters( const RTI::ParameterHandleValuePairSet &propertyMap );

private:
    void setParameter(int handle, const std::string &value);

protected:
    Interaction( RTI::ParameterHandleValuePairSet propertyMap, bool initFlag ) {
        propertyMapInitFlagConstructorInit(propertyMap, initFlag);
    }

    Interaction( RTI::ParameterHandleValuePairSet propertyMap, const RTIfedTime &rtiFedTime, boolean initFlag ) {
        propertyMapTimeInitFlagConstructor(propertyMap, rtiFedTime, initFlag);
    }


    /**
     * Creates a new interaction instance and initializes its parameters
     * using the "propertyMap" -- this constructor is usually called as a
     * super-class constructor to create and initialize an instance of an
     * interaction further down in the inheritance hierarchy.  "propertyMap"
     * is usually acquired as an argument to an RTI federate callback method, such
     * as "receiveInteraction".
     *
     * @param propertyMap contains parameter values for the newly created
     * interaction
     */
public:
    public Interaction( RTI::ParameterHandleValuePairSet propertyMap ) {
        propertyMapInitFlagConstructorInit( propertyMap, true );
    }

    /**
     * Like {@link #Interaction( ReceivedInteraction propertyMap )},
     * except the new instance has an initial timestamp of "logicalTime".
     *
     * @param propertyMap contains parameter values for the newly created
     * interaction
     * @param logicalTime initial timestamp for newly created interaction instance
     */
    public Interaction( ReceivedInteraction propertyMap, LogicalTime logicalTime ) {
        propertyMapTimeInitFlagConstructorInit( propertyMap, logicalTime, true );
    }

    //-----------------
    // END CONSTRUCTORS
    //-----------------

public:
    PropertyHandleValuePairSetSP createPropertyHandleValuePairSet();

    void sendInteraction( RTI::RTIambassador *rti, double time );
    void sendInteraction( RTI::RTIambassador *rti );

    const std::string toJson();

    static SP fromJson(const std::string &jsonString);


public:
    static std::string get__name( int datamemberHandle ) {
        IntegerStringMap::iterator ismItr = getDatamemberHandleNameMap().find( datamemberHandle );
        return ismItr == getDatamemberHandleNameMap().end() ? std::string() : ismItr->second;
    }

    static int get__handle( const std::string &className, const std::string &datamemberName ) {
        StringIntegerMap::iterator simItr = getDatamemberNameHandleMap().find( className + "." + datamemberName );
        if ( simItr == getDatamemberNameHandleMap().end() ) {
            std::cerr << "Bad  \"" << datamemberName << "\" for class \"" << className << "\" on get__handle." << std::endl;
            return -1;
        }
        return simItr->second;
    }


    static ClassAndPropertyNameSP get_class_pub_sub_class_and_property_name_sp(
      const StringClassAndPropertyNameSetSPMap &stringClassAndPropertyNameSetSPMap,
      const std::string &className,
      const std::string &attributeName
      bool publish;
      bool insert;
    ) {
        StringClassAndPropertyNameSetSPMap::iterator samItr = stringClassAndPropertyNameSetSPMap.find( className );
        if ( samItr == get_class_name_published_attribute_name_set_sp_map().end() ) {
            // ERROR
            return;
        }

        ClassAndPropertyNameSP classAndPropertyNameSP = findProperty(classNamd, attributeName);
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

    static void publish_attribute( const std::string &className, const std::string &attributeName ) {
        get_class_name_published_attribute_name_set_sp_map(), className, attributeName, true, true);
    }

    static void unpublish_attribute( const std::string &className, const std::string &attributeName ) {
        get_class_name_published_attribute_name_set_sp_map(), className, attributeName, true, false);
    }

    static void subscribe_attribute( const std::string &className, const std::string &attributeName ) {
        get_class_name_published_attribute_name_set_sp_map(), className, attributeName, false, true);
    }

    static void subscribe_attribute( const std::string &className, const std::string &attributeName ) {
        get_class_name_published_attribute_name_set_sp_map(), className, attributeName, false, false);
    }

};
  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"

static bool static_init_0 = ::org::cpswt::hla::InteractionRoot::static_init();

std::ostream &operator<<( std::ostream &os, ::org::cpswt::hla::InteractionRoot::SP entitySP );
std::ostream &operator<<( std::ostream &os, const ::org::cpswt::hla::InteractionRoot &entity );

#endif // _INTERACTION_ROOT