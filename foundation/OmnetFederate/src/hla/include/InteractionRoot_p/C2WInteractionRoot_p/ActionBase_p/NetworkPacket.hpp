
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



#ifndef _org_cpswt_hla_InteractionRoot_p_C2WInteractionRoot_p_ActionBase_p_NetworkPacket_CLASS
#define _org_cpswt_hla_InteractionRoot_p_C2WInteractionRoot_p_ActionBase_p_NetworkPacket_CLASS

#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase.hpp"
#include "C2WException.hpp"

#include <boost/unordered_set.hpp>

using ::org::cpswt::hla::InteractionRoot;


namespace org {
 namespace cpswt {
  namespace hla {
   namespace InteractionRoot_p {
    namespace C2WInteractionRoot_p {
     namespace ActionBase_p {

class NetworkPacket : public ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase {
public:
    typedef ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase Super;
    typedef boost::shared_ptr< NetworkPacket > SP;

    // ----------------------------------------------------------------------------
    // STATIC DATAMEMBERS AND CODE THAT DEAL WITH NAMES
    // THIS CODE IS STATIC BECAUSE IT IS CLASS-DEPENDENT AND NOT INSTANCE-DEPENDENT
    // ----------------------------------------------------------------------------

public:
    /**
     * Returns the fully-qualified (dot-delimited) name of the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.NetworkPacket interaction class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the name of the class pertaining to the reference,
     * rather than the name of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getJavaClassName()}.
     *
     * @return the fully-qualified Java class name for this interaction class
     */
    static const std::string &get_cpp_class_name() {
        static const std::string cppClassName("::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::NetworkPacket");
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
     * class name) of the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.NetworkPacket interaction class.
     *
     * @return the name of this interaction class
     */
    static const std::string &get_simple_class_name() {
        static const std::string simpleClassName("NetworkPacket");
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
     * InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket interaction class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the federation name of the class pertaining to the reference,
     * rather than the name of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getHlaClassName()}.
     *
     * @return the fully-qualified federation (HLA) class name for this interaction class
     */
    static const std::string &get_hla_class_name() {
        static const std::string hlaClassName("InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket");
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
     * org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.NetworkPacket interaction class.
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
     * org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.NetworkPacket interaction class.
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
     * Returns the handle (RTI assigned) of the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.NetworkPacket interaction class.
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
     * this interaction class (i.e. "org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.NetworkPacket") given the parameter's name.
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
     * Publishes the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.NetworkPacket interaction class for a federate.
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
     * Unpublishes the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.NetworkPacket interaction class for a federate.
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
 * Subscribes a federate to the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.NetworkPacket interaction class.
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
     * Unsubscribes a federate from the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.NetworkPacket interaction class.
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
     * (that is, the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.NetworkPacket interaction class).
     *
     * @param handle handle to compare to the value of the handle (RTI assigned) of
     * this class (the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.NetworkPacket interaction class).
     * @return "true" if "handle" matches the value of the handle of this class
     * (that is, the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.NetworkPacket interaction class).
     */
    static bool match(int handle) {
        return handle == get_class_handle();
    }


    //--------------------------------
    // DATAMEMBER MANIPULATION METHODS
    //--------------------------------
public:


    /**
     * Set the value of the "data" parameter to "value" for this parameter.
     *
     * @param value the new value for the "data" parameter
     */
    void set_data(const std::string & newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "data");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
    }

    /**
     * Returns the value of the "data" parameter of this interaction.
     *
     * @return the value of the "data" parameter
     */
    std::string get_data() {
        ClassAndPropertyName key(get_hla_class_name(), "data");
        return static_cast<std::string>(*_classAndPropertyNameValueSPMap[key]);
    }


    /**
     * Set the value of the "numBytes" parameter to "value" for this parameter.
     *
     * @param value the new value for the "numBytes" parameter
     */
    void set_numBytes(int newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "numBytes");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
    }

    /**
     * Returns the value of the "numBytes" parameter of this interaction.
     *
     * @return the value of the "numBytes" parameter
     */
    int get_numBytes() {
        ClassAndPropertyName key(get_hla_class_name(), "numBytes");
        return static_cast<int>(*_classAndPropertyNameValueSPMap[key]);
    }


    /**
     * Set the value of the "packetType" parameter to "value" for this parameter.
     *
     * @param value the new value for the "packetType" parameter
     */
    void set_packetType(const std::string & newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "packetType");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
    }

    /**
     * Returns the value of the "packetType" parameter of this interaction.
     *
     * @return the value of the "packetType" parameter
     */
    std::string get_packetType() {
        ClassAndPropertyName key(get_hla_class_name(), "packetType");
        return static_cast<std::string>(*_classAndPropertyNameValueSPMap[key]);
    }


    /**
     * Set the value of the "receiverAppIndex" parameter to "value" for this parameter.
     *
     * @param value the new value for the "receiverAppIndex" parameter
     */
    void set_receiverAppIndex(int newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "receiverAppIndex");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
    }

    /**
     * Returns the value of the "receiverAppIndex" parameter of this interaction.
     *
     * @return the value of the "receiverAppIndex" parameter
     */
    int get_receiverAppIndex() {
        ClassAndPropertyName key(get_hla_class_name(), "receiverAppIndex");
        return static_cast<int>(*_classAndPropertyNameValueSPMap[key]);
    }


    /**
     * Set the value of the "receiverAppInterface" parameter to "value" for this parameter.
     *
     * @param value the new value for the "receiverAppInterface" parameter
     */
    void set_receiverAppInterface(const std::string & newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "receiverAppInterface");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
    }

    /**
     * Returns the value of the "receiverAppInterface" parameter of this interaction.
     *
     * @return the value of the "receiverAppInterface" parameter
     */
    std::string get_receiverAppInterface() {
        ClassAndPropertyName key(get_hla_class_name(), "receiverAppInterface");
        return static_cast<std::string>(*_classAndPropertyNameValueSPMap[key]);
    }


    /**
     * Set the value of the "receiverHost" parameter to "value" for this parameter.
     *
     * @param value the new value for the "receiverHost" parameter
     */
    void set_receiverHost(const std::string & newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "receiverHost");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
    }

    /**
     * Returns the value of the "receiverHost" parameter of this interaction.
     *
     * @return the value of the "receiverHost" parameter
     */
    std::string get_receiverHost() {
        ClassAndPropertyName key(get_hla_class_name(), "receiverHost");
        return static_cast<std::string>(*_classAndPropertyNameValueSPMap[key]);
    }


    /**
     * Set the value of the "receiverHostApp" parameter to "value" for this parameter.
     *
     * @param value the new value for the "receiverHostApp" parameter
     */
    void set_receiverHostApp(const std::string & newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "receiverHostApp");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
    }

    /**
     * Returns the value of the "receiverHostApp" parameter of this interaction.
     *
     * @return the value of the "receiverHostApp" parameter
     */
    std::string get_receiverHostApp() {
        ClassAndPropertyName key(get_hla_class_name(), "receiverHostApp");
        return static_cast<std::string>(*_classAndPropertyNameValueSPMap[key]);
    }


    /**
     * Set the value of the "senderAppIndex" parameter to "value" for this parameter.
     *
     * @param value the new value for the "senderAppIndex" parameter
     */
    void set_senderAppIndex(int newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "senderAppIndex");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
    }

    /**
     * Returns the value of the "senderAppIndex" parameter of this interaction.
     *
     * @return the value of the "senderAppIndex" parameter
     */
    int get_senderAppIndex() {
        ClassAndPropertyName key(get_hla_class_name(), "senderAppIndex");
        return static_cast<int>(*_classAndPropertyNameValueSPMap[key]);
    }


    /**
     * Set the value of the "senderHost" parameter to "value" for this parameter.
     *
     * @param value the new value for the "senderHost" parameter
     */
    void set_senderHost(const std::string & newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "senderHost");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
    }

    /**
     * Returns the value of the "senderHost" parameter of this interaction.
     *
     * @return the value of the "senderHost" parameter
     */
    std::string get_senderHost() {
        ClassAndPropertyName key(get_hla_class_name(), "senderHost");
        return static_cast<std::string>(*_classAndPropertyNameValueSPMap[key]);
    }


    /**
     * Set the value of the "senderHostApp" parameter to "value" for this parameter.
     *
     * @param value the new value for the "senderHostApp" parameter
     */
    void set_senderHostApp(const std::string & newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "senderHostApp");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
    }

    /**
     * Returns the value of the "senderHostApp" parameter of this interaction.
     *
     * @return the value of the "senderHostApp" parameter
     */
    std::string get_senderHostApp() {
        ClassAndPropertyName key(get_hla_class_name(), "senderHostApp");
        return static_cast<std::string>(*_classAndPropertyNameValueSPMap[key]);
    }

protected:
    virtual PropertyClassNameAndValueSP getParameterAux(
      const std::string &className, const std::string &propertyName
    ) const;

    void classAndPropertyNameValueSPMapInit() {

        _classAndPropertyNameValueSPMap.emplace( std::make_pair(
          ClassAndPropertyName(get_hla_class_name(), "data"),
          ValueSP(  new Value( std::string("") )  )
        ) );

        _classAndPropertyNameValueSPMap.emplace( std::make_pair(
          ClassAndPropertyName(get_hla_class_name(), "numBytes"),
          ValueSP(  new Value( static_cast<int>(0) )  )
        ) );

        _classAndPropertyNameValueSPMap.emplace( std::make_pair(
          ClassAndPropertyName(get_hla_class_name(), "packetType"),
          ValueSP(  new Value( std::string("") )  )
        ) );

        _classAndPropertyNameValueSPMap.emplace( std::make_pair(
          ClassAndPropertyName(get_hla_class_name(), "receiverAppIndex"),
          ValueSP(  new Value( static_cast<int>(0) )  )
        ) );

        _classAndPropertyNameValueSPMap.emplace( std::make_pair(
          ClassAndPropertyName(get_hla_class_name(), "receiverAppInterface"),
          ValueSP(  new Value( std::string("") )  )
        ) );

        _classAndPropertyNameValueSPMap.emplace( std::make_pair(
          ClassAndPropertyName(get_hla_class_name(), "receiverHost"),
          ValueSP(  new Value( std::string("") )  )
        ) );

        _classAndPropertyNameValueSPMap.emplace( std::make_pair(
          ClassAndPropertyName(get_hla_class_name(), "receiverHostApp"),
          ValueSP(  new Value( std::string("") )  )
        ) );

        _classAndPropertyNameValueSPMap.emplace( std::make_pair(
          ClassAndPropertyName(get_hla_class_name(), "senderAppIndex"),
          ValueSP(  new Value( static_cast<int>(0) )  )
        ) );

        _classAndPropertyNameValueSPMap.emplace( std::make_pair(
          ClassAndPropertyName(get_hla_class_name(), "senderHost"),
          ValueSP(  new Value( std::string("") )  )
        ) );

        _classAndPropertyNameValueSPMap.emplace( std::make_pair(
          ClassAndPropertyName(get_hla_class_name(), "senderHostApp"),
          ValueSP(  new Value( std::string("") )  )
        ) );
    }

    //------------------------------------
    // END DATAMEMBER MANIPULATION METHODS
    //------------------------------------

    //-------------
    // CONSTRUCTORS
    //-------------
    
    NetworkPacket() {
        NetworkPacket::classAndPropertyNameValueSPMapInit();
    }

    NetworkPacket( const PropertyHandleValuePairSet &propertyMap ) {
        NetworkPacket::classAndPropertyNameValueSPMapInit();
        setParameters(propertyMap);
    }

    NetworkPacket( const RTIfedTime &rtiFedTime ) {
        NetworkPacket::classAndPropertyNameValueSPMapInit();
    }

    NetworkPacket(const PropertyHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime) {
        NetworkPacket::classAndPropertyNameValueSPMapInit();
        setParameters(propertyMap);
        setTime(rtiFedTime);
    }


    //--------------------------
    // INSTANCE CREATION METHODS
    //--------------------------
public:
    static SP create() {
        return SP(new NetworkPacket());
    }

    static InteractionRoot::SP create_interaction() {
        return SP(new NetworkPacket());
    }

    virtual InteractionRoot::SP createInteraction() {
        return create_interaction();
    }

    static SP create(
      const RTI::ParameterHandleValuePairSet &propertyMap
    ) {
        return SP(new NetworkPacket(propertyMap));
    }

    static InteractionRoot::SP create_interaction(
      const RTI::ParameterHandleValuePairSet &propertyMap
    ) {
        return SP(new NetworkPacket(propertyMap));
    }

    virtual InteractionRoot::SP createInteraction(
      const RTI::ParameterHandleValuePairSet &propertyMap
    ) {
        return create_interaction(propertyMap);
    }

    static SP create(const RTIfedTime &rtiFedTime) {
        return SP(new NetworkPacket(rtiFedTime));
    }

    static InteractionRoot::SP create_interaction(const RTIfedTime &rtiFedTime) {
        return SP(new NetworkPacket(rtiFedTime));
    }

    virtual InteractionRoot::SP createInteraction(const RTIfedTime &rtiFedTime) {
        return create_interaction(rtiFedTime);
    }

    static SP create(
      const RTI::ParameterHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) {
        return SP(new NetworkPacket(propertyMap, rtiFedTime));
    }

    static InteractionRoot::SP create_interaction(
      const RTI::ParameterHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) {
        return SP(new NetworkPacket(propertyMap, rtiFedTime));
    }

    virtual InteractionRoot::SP createInteraction(
      const RTI::ParameterHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime) {
        return create_interaction(propertyMap, rtiFedTime);
    }

    virtual InteractionRoot::SP cloneInteraction() {
        return InteractionRoot::SP( new NetworkPacket( *this )  );
    }

    //------------------------------
    // END INSTANCE CREATION METHODS
    //------------------------------

};
     } // NAMESPACE "ActionBase_p"
    } // NAMESPACE "C2WInteractionRoot_p"
   } // NAMESPACE "InteractionRoot_p"
  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"

inline std::ostream &operator<<( std::ostream &os, ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::NetworkPacket::SP messagingSP ) {
    return os << *messagingSP;
}

#endif // _org_cpswt_hla_InteractionRoot_p_C2WInteractionRoot_p_ActionBase_p_NetworkPacket_CLASS