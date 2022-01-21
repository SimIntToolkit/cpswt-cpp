
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



#ifndef _org_cpswt_hla_InteractionRoot_p_C2WInteractionRoot_CLASS
#define _org_cpswt_hla_InteractionRoot_p_C2WInteractionRoot_CLASS

#include "InteractionRoot.hpp"
#include "C2WException.hpp"

#include <boost/unordered_set.hpp>

using ::org::cpswt::hla::InteractionRoot;


namespace org {
 namespace cpswt {
  namespace hla {
   namespace InteractionRoot_p {

class C2WInteractionRoot : public ::org::cpswt::hla::InteractionRoot {
public:
    typedef ::org::cpswt::hla::InteractionRoot Super;
    typedef boost::shared_ptr< C2WInteractionRoot > SP;

    // ----------------------------------------------------------------------------
    // STATIC DATAMEMBERS AND CODE THAT DEAL WITH NAMES
    // THIS CODE IS STATIC BECAUSE IT IS CLASS-DEPENDENT AND NOT INSTANCE-DEPENDENT
    // ----------------------------------------------------------------------------

public:
    /**
     * Returns the fully-qualified (dot-delimited) name of the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot interaction class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the name of the class pertaining to the reference,
     * rather than the name of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getJavaClassName()}.
     *
     * @return the fully-qualified Java class name for this interaction class
     */
    static const std::string &get_cpp_class_name() {
        static const std::string cppClassName("::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot");
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
     * class name) of the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot interaction class.
     *
     * @return the name of this interaction class
     */
    static const std::string &get_simple_class_name() {
        static const std::string simpleClassName("C2WInteractionRoot");
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
     * InteractionRoot.C2WInteractionRoot interaction class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the federation name of the class pertaining to the reference,
     * rather than the name of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getHlaClassName()}.
     *
     * @return the fully-qualified federation (HLA) class name for this interaction class
     */
    static const std::string &get_hla_class_name() {
        static const std::string hlaClassName("InteractionRoot.C2WInteractionRoot");
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
     * org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot interaction class.
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
     * org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot interaction class.
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
     * Returns the handle (RTI assigned) of the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot interaction class.
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
     * this interaction class (i.e. "org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot") given the parameter's name.
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
     * Publishes the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot interaction class for a federate.
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
     * Unpublishes the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot interaction class for a federate.
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
 * Subscribes a federate to the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot interaction class.
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
     * Unsubscribes a federate from the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot interaction class.
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
     * (that is, the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot interaction class).
     *
     * @param handle handle to compare to the value of the handle (RTI assigned) of
     * this class (the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot interaction class).
     * @return "true" if "handle" matches the value of the handle of this class
     * (that is, the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot interaction class).
     */
    static bool match(int handle) {
        return handle == get_class_handle();
    }


    //--------------------------------
    // DATAMEMBER MANIPULATION METHODS
    //--------------------------------
public:


    /**
     * Set the value of the "actualLogicalGenerationTime" parameter to "value" for this parameter.
     *
     * @param value the new value for the "actualLogicalGenerationTime" parameter
     */
    void set_actualLogicalGenerationTime(double newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "actualLogicalGenerationTime");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
    }

    /**
     * Returns the value of the "actualLogicalGenerationTime" parameter of this interaction.
     *
     * @return the value of the "actualLogicalGenerationTime" parameter
     */
    double get_actualLogicalGenerationTime() {
        ClassAndPropertyName key(get_hla_class_name(), "actualLogicalGenerationTime");
        return static_cast<double>(*_classAndPropertyNameValueSPMap[key]);
    }


    /**
     * Set the value of the "federateFilter" parameter to "value" for this parameter.
     *
     * @param value the new value for the "federateFilter" parameter
     */
    void set_federateFilter(const std::string & newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "federateFilter");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
    }

    /**
     * Returns the value of the "federateFilter" parameter of this interaction.
     *
     * @return the value of the "federateFilter" parameter
     */
    std::string get_federateFilter() {
        ClassAndPropertyName key(get_hla_class_name(), "federateFilter");
        return static_cast<std::string>(*_classAndPropertyNameValueSPMap[key]);
    }


    /**
     * Set the value of the "originFed" parameter to "value" for this parameter.
     *
     * @param value the new value for the "originFed" parameter
     */
    void set_originFed(const std::string & newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "originFed");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
    }

    /**
     * Returns the value of the "originFed" parameter of this interaction.
     *
     * @return the value of the "originFed" parameter
     */
    std::string get_originFed() {
        ClassAndPropertyName key(get_hla_class_name(), "originFed");
        return static_cast<std::string>(*_classAndPropertyNameValueSPMap[key]);
    }


    /**
     * Set the value of the "sourceFed" parameter to "value" for this parameter.
     *
     * @param value the new value for the "sourceFed" parameter
     */
    void set_sourceFed(const std::string & newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "sourceFed");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
    }

    /**
     * Returns the value of the "sourceFed" parameter of this interaction.
     *
     * @return the value of the "sourceFed" parameter
     */
    std::string get_sourceFed() {
        ClassAndPropertyName key(get_hla_class_name(), "sourceFed");
        return static_cast<std::string>(*_classAndPropertyNameValueSPMap[key]);
    }

protected:
    virtual PropertyClassNameAndValueSP getParameterAux(
      const std::string &className, const std::string &propertyName
    ) const;

    void classAndPropertyNameValueSPMapInit() {

        _classAndPropertyNameValueSPMap.emplace( std::make_pair(
          ClassAndPropertyName(get_hla_class_name(), "actualLogicalGenerationTime"),
          ValueSP(  new Value( static_cast<double>(0) )  )
        ) );

        _classAndPropertyNameValueSPMap.emplace( std::make_pair(
          ClassAndPropertyName(get_hla_class_name(), "federateFilter"),
          ValueSP(  new Value( std::string("") )  )
        ) );

        _classAndPropertyNameValueSPMap.emplace( std::make_pair(
          ClassAndPropertyName(get_hla_class_name(), "originFed"),
          ValueSP(  new Value( std::string("") )  )
        ) );

        _classAndPropertyNameValueSPMap.emplace( std::make_pair(
          ClassAndPropertyName(get_hla_class_name(), "sourceFed"),
          ValueSP(  new Value( std::string("") )  )
        ) );
    }

    //------------------------------------
    // END DATAMEMBER MANIPULATION METHODS
    //------------------------------------

    //-------------
    // CONSTRUCTORS
    //-------------
    
    C2WInteractionRoot() {
        C2WInteractionRoot::classAndPropertyNameValueSPMapInit();
    }

    C2WInteractionRoot( const PropertyHandleValuePairSet &propertyMap ) {
        C2WInteractionRoot::classAndPropertyNameValueSPMapInit();
        setParameters(propertyMap);
    }

    C2WInteractionRoot( const RTIfedTime &rtiFedTime ) {
        C2WInteractionRoot::classAndPropertyNameValueSPMapInit();
    }

    C2WInteractionRoot(const PropertyHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime) {
        C2WInteractionRoot::classAndPropertyNameValueSPMapInit();
        setParameters(propertyMap);
        setTime(rtiFedTime);
    }


    //--------------------------
    // INSTANCE CREATION METHODS
    //--------------------------
public:
    static SP create() {
        return SP(new C2WInteractionRoot());
    }

    static InteractionRoot::SP create_interaction() {
        return SP(new C2WInteractionRoot());
    }

    virtual InteractionRoot::SP createInteraction() {
        return create_interaction();
    }

    static SP create(
      const RTI::ParameterHandleValuePairSet &propertyMap
    ) {
        return SP(new C2WInteractionRoot(propertyMap));
    }

    static InteractionRoot::SP create_interaction(
      const RTI::ParameterHandleValuePairSet &propertyMap
    ) {
        return SP(new C2WInteractionRoot(propertyMap));
    }

    virtual InteractionRoot::SP createInteraction(
      const RTI::ParameterHandleValuePairSet &propertyMap
    ) {
        return create_interaction(propertyMap);
    }

    static SP create(const RTIfedTime &rtiFedTime) {
        return SP(new C2WInteractionRoot(rtiFedTime));
    }

    static InteractionRoot::SP create_interaction(const RTIfedTime &rtiFedTime) {
        return SP(new C2WInteractionRoot(rtiFedTime));
    }

    virtual InteractionRoot::SP createInteraction(const RTIfedTime &rtiFedTime) {
        return create_interaction(rtiFedTime);
    }

    static SP create(
      const RTI::ParameterHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) {
        return SP(new C2WInteractionRoot(propertyMap, rtiFedTime));
    }

    static InteractionRoot::SP create_interaction(
      const RTI::ParameterHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) {
        return SP(new C2WInteractionRoot(propertyMap, rtiFedTime));
    }

    virtual InteractionRoot::SP createInteraction(
      const RTI::ParameterHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime) {
        return create_interaction(propertyMap, rtiFedTime);
    }

    virtual InteractionRoot::SP cloneInteraction() {
        return InteractionRoot::SP( new C2WInteractionRoot( *this )  );
    }

    //------------------------------
    // END INSTANCE CREATION METHODS
    //------------------------------

};
   } // NAMESPACE "InteractionRoot_p"
  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"

inline std::ostream &operator<<( std::ostream &os, ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot::SP messagingSP ) {
    return os << *messagingSP;
}

#endif // _org_cpswt_hla_InteractionRoot_p_C2WInteractionRoot_CLASS