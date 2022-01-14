
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



#ifndef _INTERACTION_ROOT_CLASS
#define _INTERACTION_ROOT_CLASS

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


namespace org {
 namespace cpswt {
  namespace hla {

class InteractionRoot : public InteractionRootInterface {

public:
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

    typedef RTI::AttributeHandleSet AttributeHandleSet;
    typedef boost::shared_ptr<AttributeHandleSet> AttributeHandleSetSP;

    typedef std::map<std::string, SP> StringInstanceSPMap;

    typedef TypeMedley Value;

    typedef boost::shared_ptr<Value> ValueSP;
    typedef std::unordered_map<ClassAndPropertyName, ValueSP> ClassAndPropertyNameValueSPMap;

    typedef void (*PubsubFunctionPtr)( RTI::RTIambassador * );
    typedef std::map< std::string, PubsubFunctionPtr > ClassNamePubSubMap;
    typedef std::map< std::string, std::string> DatamemberTypeMap;

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
    static StringSet &get_class_name_set( void ) {
        static StringSet classNameSet;
        return classNameSet;
    }

    //--------------------------------
    // METHODS THAT USE CLASS-NAME-SET
    //--------------------------------
public:
    static const StringSet &get_interaction_name_set( void ) {
        return get_class_name_set();
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
    static StringClassAndPropertyNameSetSPMap &get_class_name_class_and_property_name_set_sp_map() {
        static StringClassAndPropertyNameSetSPMap classNamePropertyNameSetSPMap;
        return classNamePropertyNameSetSPMap;
    }

    //----------------------------------------------------
    // METHODS THAT USE CLASS-NAME DATAMEMBER-NAME-SET MAP
    //----------------------------------------------------
public:
    static const ClassAndPropertyNameSetSP get_parameter_names(const std::string &className) {
       StringClassAndPropertyNameSetSPMap::iterator scmItr =
         get_class_name_class_and_property_name_set_sp_map().find(className);

       return scmItr == get_class_name_class_and_property_name_set_sp_map().end()
         ? ClassAndPropertyNameSetSP() : scmItr->second;
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
    static const ClassAndPropertyNameSetSP get_all_parameter_names(const std::string &className) {
       StringClassAndPropertyNameSetSPMap::iterator scmItr =
         get_class_name_all_class_and_property_name_set_sp_map().find(className);

       return scmItr == get_class_name_all_class_and_property_name_set_sp_map().end()
         ? ClassAndPropertyNameSetSP()
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
    static std::string join(const std::list<std::string> &joinList, const std::string &delimiter);

public:
    static ClassAndPropertyNameSP findProperty(const std::string &className, const std::string &propertyName);

    static int get_parameter_handle(const std::string &className, const std::string &propertyName) {
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
    static ClassAndPropertyNameSP get_class_and_parameter_name(int propertyHandle) {
        IntegerClassAndPropertyNameSPMap::iterator icmItr =
          get_handle_class_and_property_name_sp_map().find(propertyHandle);
        return icmItr == get_handle_class_and_property_name_sp_map().end()
          ? ClassAndPropertyNameSP() : icmItr->second;
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

    static SP create_interaction(const std::string &className) {
        StringInstanceSPMap::iterator cimItr = get_class_name_instance_sp_map().find(className);
        return cimItr == get_class_name_instance_sp_map().end()
          ? SP() : cimItr->second->createInteraction();
    }

    static SP create_interaction(const std::string &className, const RTIfedTime &rtiFedTime) {
        StringInstanceSPMap::iterator cimItr = get_class_name_instance_sp_map().find( className );
        return cimItr == get_class_name_instance_sp_map().end()
          ? SP() : cimItr->second->createInteraction(rtiFedTime);
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
    static const std::string get_hla_class_name(int classHandle) {
        IntegerStringMap::iterator ismItr = get_class_handle_name_map().find(classHandle);
        return ismItr == get_class_handle_name_map().end() ? "" : ismItr->second;
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

    template<typename T>
    void setParameter(int propertyHandle, const T &value) {

        IntegerClassAndPropertyNameSPMap::iterator hcmItr =
          get_handle_class_and_property_name_sp_map().find(propertyHandle);

        if (hcmItr == get_handle_class_and_property_name_sp_map().end()) {
//            logger.error(
//              "setParameter(int, Object value): propertyHandle {} does not exist.",
//              propertyHandle
//            );
            return;
        }

        Value &currentValue = *_classAndPropertyNameValueSPMap[*hcmItr->second];
        if (!currentValue.setValue(value)) {
//            logger.error(
//                "setParameter: propertyHandle {} corresponds to property of name \"{}\", which " +
//                "does not exist in class \"{}\" (it's defined in class\"{}\")",
//                propertyHandle, propertyName, getClass(), classAndPropertyName.getClassName()
//            );
        }
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
    const Value &getParameter(const std::string &propertyName) const override {
        return *getParameterAux(getHlaClassName(), propertyName)->getValueSP();
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
    const std::string &getCppClassName() const override {
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
    const std::string &getSimpleClassName() const override {
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
    const ClassAndPropertyNameList getParameterNames() const override {
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
    const ClassAndPropertyNameList getAllParameterNames() const override {
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
     * THIS METHOD IS INDIRECTLY CALLED VIA THE "get_parameter_handle(String)" METHOD BELOW, WHICH PROVIDES THE
     * VALUE FOR THE "className" ARGUMENT.
     */
    static int get_parameter_handle_aux(const std::string &className, const std::string &propertyName);

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
    static void unsubscribe_interaction(RTI::RTIambassador *rti);

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
    ) const;

    //------------------------------------
    // END DATAMEMBER MANIPULATION METHODS
    //------------------------------------

    //-------------
    // CONSTRUCTORS
    //-------------
    
    InteractionRoot(): _uniqueId(generate_unique_id()) {
    }

    InteractionRoot( const PropertyHandleValuePairSet &propertyMap ): _uniqueId(generate_unique_id()) {
        setParameters(propertyMap);
    }

    InteractionRoot( const RTIfedTime &rtiFedTime ): _uniqueId(generate_unique_id()) {
    }

    InteractionRoot(const PropertyHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime):
      _uniqueId(generate_unique_id()) {
        setParameters(propertyMap);
        setTime(rtiFedTime);
    }


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

    //-------------
    // CONSTRUCTORS
    //-------------

    /**
     * Creates a new InteractionRoot instance.
     */
// private:
//     void setParameter(int propertyHandle, const std::string &value) {
//         ClassAndPropertyNameSP classAndPropertyNameSP = get_class_and_parameter_name(propertyHandle);
//         if (!classAndPropertyNameSP) {
//             // ERROR
//             return;
//         }
//         const ClassAndPropertyName &classAndPropertyName = *classAndPropertyNameSP;
//         _classAndPropertyNameValueSPMap[classAndPropertyName]->setValue(value);
//     }

public:
    void setParameters( const RTI::ParameterHandleValuePairSet &propertyMap );

protected:


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
    /**
     * Like {@link #InteractionRoot( const RTI::ParameterHandleValuePairSet &propertyMap )},
     * except the new instance has an initial timestamp of "logicalTime".
     *
     * @param propertyMap contains parameter values for the newly created
     * interaction
     * @param logicalTime initial timestamp for newly created interaction instance
     */

    //-----------------
    // END CONSTRUCTORS
    //-----------------

public:

    PropertyHandleValuePairSetSP createPropertyHandleValuePairSetSP();

    void sendInteraction( RTI::RTIambassador *rti, double time );
    void sendInteraction( RTI::RTIambassador *rti );

    std::string toJson();

    static SP fromJson(const std::string &jsonString);


public:
    static ClassAndPropertyNameSP get_parameter_name( int propertyHandle ) {
        IntegerClassAndPropertyNameSPMap::iterator icmItr =
          get_handle_class_and_property_name_sp_map().find( propertyHandle );
        return icmItr == get_handle_class_and_property_name_sp_map().end() ? ClassAndPropertyNameSP() : icmItr->second;
    }

};
  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"

static bool static_init_0 = ::org::cpswt::hla::InteractionRoot::static_init();

std::ostream &operator<<( std::ostream &os, ::org::cpswt::hla::InteractionRoot::SP entitySP );
std::ostream &operator<<( std::ostream &os, const ::org::cpswt::hla::InteractionRoot &entity );

#endif // _INTERACTION_ROOT