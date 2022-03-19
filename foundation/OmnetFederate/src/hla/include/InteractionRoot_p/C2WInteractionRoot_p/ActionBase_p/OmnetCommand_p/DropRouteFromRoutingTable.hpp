
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



#ifndef _org_cpswt_hla_InteractionRoot_p_C2WInteractionRoot_p_ActionBase_p_OmnetCommand_p_DropRouteFromRoutingTable_CLASS
#define _org_cpswt_hla_InteractionRoot_p_C2WInteractionRoot_p_ActionBase_p_OmnetCommand_p_DropRouteFromRoutingTable_CLASS

#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand.hpp"
#include "C2WException.hpp"

#include <boost/unordered_set.hpp>


namespace org {
 namespace cpswt {
  namespace hla {
   namespace InteractionRoot_p {
    namespace C2WInteractionRoot_p {
     namespace ActionBase_p {
      namespace OmnetCommand_p {

class DropRouteFromRoutingTable : public ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand {
public:
//    using ::org::cpswt::hla::InteractionRoot;
    typedef ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand Super;
    typedef boost::shared_ptr< DropRouteFromRoutingTable > SP;

private:
    static severity_logger &get_logger_aux() {
        static severity_logger logger;
        logger.add_attribute("MessagingClassName", attrs::constant< std::string >(
          "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.DropRouteFromRoutingTable"
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
     * Returns the fully-qualified (dot-delimited) name of the ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::DropRouteFromRoutingTable interaction class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the name of the class pertaining to the reference,
     * rather than the name of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getJavaClassName()}.
     *
     * @return the fully-qualified Java class name for this interaction class
     */
    static const std::string &get_cpp_class_name() {
        static const std::string cppClassName("::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::DropRouteFromRoutingTable");
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
     * class name) of the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.DropRouteFromRoutingTable interaction class.
     *
     * @return the name of this interaction class
     */
    static const std::string get_simple_class_name() {
        return InteractionRoot::get_simple_class_name(get_hla_class_name());
    }

    /**
     * Returns the fully-qualified (dot-delimited) hla class name of the
     * InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.DropRouteFromRoutingTable interaction class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the federation name of the class pertaining to the reference,
     * rather than the name of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getHlaClassName()}.
     *
     * @return the fully-qualified federation (HLA) class name for this interaction class
     */
    static const std::string &get_hla_class_name() {
        static const std::string hlaClassName("InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.DropRouteFromRoutingTable");
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
     * org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.DropRouteFromRoutingTable interaction class.
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
        return InteractionRoot::get_parameter_names( get_hla_class_name() );
    }

    /**
     * Returns a sorted list containing the names of all of the parameters in the
     * org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.DropRouteFromRoutingTable interaction class.
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
        return InteractionRoot::get_all_parameter_names( get_hla_class_name() );
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
     * Returns the handle (RTI assigned) of the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.DropRouteFromRoutingTable interaction class.
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
     * this interaction class (i.e. "org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.DropRouteFromRoutingTable") given the parameter's name.
     *
     * @param propertyName name of parameter
     * @return the handle (RTI assigned) of the parameter "propertyName" of interaction class "hlaClassName"
     */
    static int get_parameter_handle(const std::string &propertyName) {
        return InteractionRoot::get_parameter_handle(get_hla_class_name(), propertyName);
    }

    // ----------------------------------------------------------
    // END OF STATIC PROPERTYS AND CODE THAT DEAL WITH HANDLES.
    // ----------------------------------------------------------


    //-------------------------------------------------
    // METHODS FOR PUBLISHING/SUBSCRIBING-TO THIS CLASS
    //-------------------------------------------------

    /**
     * Publishes the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.DropRouteFromRoutingTable interaction class for a federate.
     *
     * @param rti handle to the Local RTI Component
     */
    static void publish_interaction(RTI::RTIambassador *rti) {
        InteractionRoot::publish_interaction( get_hla_class_name(), rti );
    }

    /**
     * Unpublishes the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.DropRouteFromRoutingTable interaction class for a federate.
     *
     * @param rti handle to the Local RTI Component, usu. obtained through the
     *            {@link SynchronizedFederate#getLRC()} call
     */
    static void unpublish_interaction(RTI::RTIambassador *rti) {
        InteractionRoot::unpublish_interaction( get_hla_class_name(), rti);
    }

/**
 * Subscribes a federate to the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.DropRouteFromRoutingTable interaction class.
 *
 * @param rti handle to the Local RTI Component
 */
    static void subscribe_interaction(RTI::RTIambassador *rti) {
        InteractionRoot::subscribe_interaction( get_hla_class_name(), rti );
    }

    /**
     * Unsubscribes a federate from the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.DropRouteFromRoutingTable interaction class.
     *
     * @param rti handle to the Local RTI Component
     */
    static void unsubscribe_interaction(RTI::RTIambassador *rti) {
        InteractionRoot::unsubscribe_interaction( get_hla_class_name(), rti );
    }

    //-----------------------------------------------------
    // END METHODS FOR PUBLISHING/SUBSCRIBING-TO THIS CLASS
    //-----------------------------------------------------

    /**
     * Return true if "handle" is equal to the handle (RTI assigned) of this class
     * (that is, the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.DropRouteFromRoutingTable interaction class).
     *
     * @param handle handle to compare to the value of the handle (RTI assigned) of
     * this class (the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.DropRouteFromRoutingTable interaction class).
     * @return "true" if "handle" matches the value of the handle of this class
     * (that is, the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.DropRouteFromRoutingTable interaction class).
     */
    static bool match(int handle) {
        return handle == get_class_handle();
    }

    //------------------------------
    // PROPERTY MANIPULATION METHODS
    //------------------------------


    /**
     * Set the value of the "gatewayAddress" parameter to "value" for this parameter.
     *
     * @param value the new value for the "gatewayAddress" parameter
     */
    void set_gatewayAddress(const std::string & newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "gatewayAddress");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
    }

    /**
     * Returns the value of the "gatewayAddress" parameter of this interaction.
     *
     * @return the value of the "gatewayAddress" parameter
     */
    std::string get_gatewayAddress() {
        ClassAndPropertyName key(get_hla_class_name(), "gatewayAddress");
        return static_cast<std::string>(*_classAndPropertyNameValueSPMap[key]);
    }


    /**
     * Set the value of the "interfaceEntry" parameter to "value" for this parameter.
     *
     * @param value the new value for the "interfaceEntry" parameter
     */
    void set_interfaceEntry(const std::string & newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "interfaceEntry");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
    }

    /**
     * Returns the value of the "interfaceEntry" parameter of this interaction.
     *
     * @return the value of the "interfaceEntry" parameter
     */
    std::string get_interfaceEntry() {
        ClassAndPropertyName key(get_hla_class_name(), "interfaceEntry");
        return static_cast<std::string>(*_classAndPropertyNameValueSPMap[key]);
    }


    /**
     * Set the value of the "networkAddress" parameter to "value" for this parameter.
     *
     * @param value the new value for the "networkAddress" parameter
     */
    void set_networkAddress(const std::string & newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "networkAddress");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
    }

    /**
     * Returns the value of the "networkAddress" parameter of this interaction.
     *
     * @return the value of the "networkAddress" parameter
     */
    std::string get_networkAddress() {
        ClassAndPropertyName key(get_hla_class_name(), "networkAddress");
        return static_cast<std::string>(*_classAndPropertyNameValueSPMap[key]);
    }


    /**
     * Set the value of the "nodeFullPath" parameter to "value" for this parameter.
     *
     * @param value the new value for the "nodeFullPath" parameter
     */
    void set_nodeFullPath(const std::string & newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "nodeFullPath");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
    }

    /**
     * Returns the value of the "nodeFullPath" parameter of this interaction.
     *
     * @return the value of the "nodeFullPath" parameter
     */
    std::string get_nodeFullPath() {
        ClassAndPropertyName key(get_hla_class_name(), "nodeFullPath");
        return static_cast<std::string>(*_classAndPropertyNameValueSPMap[key]);
    }

    //------------------------------------
    // END PROPERTY MANIPULATION METHODS
    //------------------------------------

    //--------------------------
    // INSTANCE CREATION METHODS
    //--------------------------
public:
    static SP create() {
        return SP(new DropRouteFromRoutingTable());
    }

    static InteractionRoot::SP create_interaction() {
        return SP(new DropRouteFromRoutingTable());
    }

    virtual InteractionRoot::SP createInteraction() {
        return create_interaction();
    }

    static SP create(const RTIfedTime &rtiFedTime) {
        return SP(new DropRouteFromRoutingTable(rtiFedTime));
    }

    static InteractionRoot::SP create_interaction(const RTIfedTime &rtiFedTime) {
        return SP(new DropRouteFromRoutingTable(rtiFedTime));
    }

    virtual InteractionRoot::SP createInteraction(const RTIfedTime &rtiFedTime) {
        return create_interaction(rtiFedTime);
    }

    static SP create(
      const RTI::ParameterHandleValuePairSet &propertyMap
    ) {
        return SP(new DropRouteFromRoutingTable(propertyMap));
    }

    static InteractionRoot::SP create_interaction(
      const RTI::ParameterHandleValuePairSet &propertyMap
    ) {
        return SP(new DropRouteFromRoutingTable(propertyMap));
    }

    virtual InteractionRoot::SP createInteraction(
      const RTI::ParameterHandleValuePairSet &propertyMap
    ) {
        return create_interaction(propertyMap);
    }

    static SP create(
      const RTI::ParameterHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) {
        return SP(new DropRouteFromRoutingTable(propertyMap, rtiFedTime));
    }

    static InteractionRoot::SP create_interaction(
      const RTI::ParameterHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) {
        return SP(new DropRouteFromRoutingTable(propertyMap, rtiFedTime));
    }

    virtual InteractionRoot::SP createInteraction(
      const RTI::ParameterHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime) {
        return create_interaction(propertyMap, rtiFedTime);
    }

    virtual InteractionRoot::SP cloneInteraction() {
        return InteractionRoot::SP( new DropRouteFromRoutingTable( *this )  );
    }

    //------------------------------
    // END INSTANCE CREATION METHODS
    //------------------------------

    //-------------
    // CONSTRUCTORS
    //-------------
public:
    DropRouteFromRoutingTable() : Super( get_hla_class_name() ) { }

    DropRouteFromRoutingTable( const PropertyHandleValuePairSet &propertyMap ) : Super( get_hla_class_name(), propertyMap ) { }

    DropRouteFromRoutingTable( const RTIfedTime &rtiFedTime ) : Super( get_hla_class_name(), rtiFedTime ) { }

    DropRouteFromRoutingTable(const PropertyHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime) :
       Super( get_hla_class_name(), propertyMap, rtiFedTime ) { }

protected:
    DropRouteFromRoutingTable(InteractionRoot::NoInstanceInit &noInstanceInit) : Super(noInstanceInit) { }

    DropRouteFromRoutingTable( const std::string &hlaClassName ) : Super( hlaClassName ) { }

    DropRouteFromRoutingTable( const std::string &hlaClassName, const PropertyHandleValuePairSet &propertyMap ) :
      Super( hlaClassName, propertyMap ) { }

    DropRouteFromRoutingTable( const std::string &hlaClassName, const RTIfedTime &rtiFedTime ) :
      Super( hlaClassName, rtiFedTime ) { }

    DropRouteFromRoutingTable(
      const std::string &hlaClassName, const PropertyHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) : Super( hlaClassName, propertyMap, rtiFedTime ) { }

};
      } // NAMESPACE "OmnetCommand_p"
     } // NAMESPACE "ActionBase_p"
    } // NAMESPACE "C2WInteractionRoot_p"
   } // NAMESPACE "InteractionRoot_p"
  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"

inline std::ostream &operator<<( std::ostream &os, ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::DropRouteFromRoutingTable::SP messagingSP ) {
    return os << *messagingSP;
}

#endif // _org_cpswt_hla_InteractionRoot_p_C2WInteractionRoot_p_ActionBase_p_OmnetCommand_p_DropRouteFromRoutingTable_CLASS
