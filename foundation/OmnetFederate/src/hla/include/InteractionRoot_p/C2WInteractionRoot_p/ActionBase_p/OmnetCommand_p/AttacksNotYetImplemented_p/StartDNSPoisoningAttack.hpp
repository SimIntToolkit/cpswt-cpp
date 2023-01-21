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

#ifndef _edu_vanderbilt_vuisis_cpswt_hla_InteractionRoot_p_C2WInteractionRoot_p_ActionBase_p_OmnetCommand_p_AttacksNotYetImplemented_p_StartDNSPoisoningAttack_CLASS
#define _edu_vanderbilt_vuisis_cpswt_hla_InteractionRoot_p_C2WInteractionRoot_p_ActionBase_p_OmnetCommand_p_AttacksNotYetImplemented_p_StartDNSPoisoningAttack_CLASS

#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/AttacksNotYetImplemented.hpp"
#include "C2WException.hpp"

#include <boost/unordered_set.hpp>


namespace edu {
 namespace vanderbilt {
  namespace vuisis {
   namespace cpswt {
    namespace hla {
     namespace InteractionRoot_p {
      namespace C2WInteractionRoot_p {
       namespace ActionBase_p {
        namespace OmnetCommand_p {
         namespace AttacksNotYetImplemented_p {

class StartDNSPoisoningAttack : public ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::AttacksNotYetImplemented {
public:
//    using ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot;
    typedef ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::AttacksNotYetImplemented Super;
    typedef boost::shared_ptr< StartDNSPoisoningAttack > SP;

private:
    static severity_logger &get_logger_aux() {
        static severity_logger logger;
        logger.add_attribute("MessagingClassName", attrs::constant< std::string >(
          "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StartDNSPoisoningAttack"
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
     * Returns the fully-qualified (dot-delimited) name of the ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::AttacksNotYetImplemented_p::StartDNSPoisoningAttack interaction class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the name of the class pertaining to the reference,
     * rather than the name of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getJavaClassName()}.
     *
     * @return the fully-qualified Java class name for this interaction class
     */
    static const std::string &get_cpp_class_name() {
        static const std::string cppClassName("::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::AttacksNotYetImplemented_p::StartDNSPoisoningAttack");
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
     * class name) of the edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.AttacksNotYetImplemented_p.StartDNSPoisoningAttack interaction class.
     *
     * @return the name of this interaction class
     */
    static const std::string get_simple_class_name() {
        return InteractionRoot::get_simple_class_name(get_hla_class_name());
    }

    /**
     * Returns the fully-qualified (dot-delimited) hla class name of the
     * InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StartDNSPoisoningAttack interaction class.
     * Note: As this is a static method, it is NOT polymorphic, and so, if called on
     * a reference will return the federation name of the class pertaining to the reference,
     * rather than the name of the class for the instance referred to by the reference.
     * For the polymorphic version of this method, use {@link #getHlaClassName()}.
     *
     * @return the fully-qualified federation (HLA) class name for this interaction class
     */
    static const std::string &get_hla_class_name() {
        static const std::string hlaClassName("InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StartDNSPoisoningAttack");
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
     * edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.AttacksNotYetImplemented_p.StartDNSPoisoningAttack interaction class.
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
     * edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.AttacksNotYetImplemented_p.StartDNSPoisoningAttack interaction class.
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
     * Returns the handle (RTI assigned) of the edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.AttacksNotYetImplemented_p.StartDNSPoisoningAttack interaction class.
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
     * this interaction class (i.e. "edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.AttacksNotYetImplemented_p.StartDNSPoisoningAttack") given the parameter's name.
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
     * Publishes the edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.AttacksNotYetImplemented_p.StartDNSPoisoningAttack interaction class for a federate.
     *
     * @param rti handle to the Local RTI Component
     */
    static void publish_interaction(RTI::RTIambassador *rti) {
        InteractionRoot::publish_interaction( get_hla_class_name(), rti );
    }

    static bool get_is_published() {
        return InteractionRoot::get_is_published(get_hla_class_name());
    }

    /**
     * Unpublishes the edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.AttacksNotYetImplemented_p.StartDNSPoisoningAttack interaction class for a federate.
     *
     * @param rti handle to the Local RTI Component, usu. obtained through the
     *            {@link SynchronizedFederate#getRTI()} call
     */
    static void unpublish_interaction(RTI::RTIambassador *rti) {
        InteractionRoot::unpublish_interaction( get_hla_class_name(), rti);
    }

/**
 * Subscribes a federate to the edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.AttacksNotYetImplemented_p.StartDNSPoisoningAttack interaction class.
 *
 * @param rti handle to the Local RTI Component
 */
    static void subscribe_interaction(RTI::RTIambassador *rti) {
        InteractionRoot::subscribe_interaction( get_hla_class_name(), rti );
    }

    static bool get_is_subscribed() {
        return InteractionRoot::get_is_subscribed(get_hla_class_name());
    }

    static void soft_subscribe_interaction(RTI::RTIambassador *rti) {
        InteractionRoot::soft_subscribe_interaction(get_hla_class_name(), rti);
    }

    static bool get_is_soft_subscribed() {
        return InteractionRoot::get_is_soft_subscribed(get_hla_class_name());
    }

    /**
     * Unsubscribes a federate from the edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.AttacksNotYetImplemented_p.StartDNSPoisoningAttack interaction class.
     *
     * @param rti handle to the Local RTI Component
     */
    static void unsubscribe_interaction(RTI::RTIambassador *rti) {
        InteractionRoot::unsubscribe_interaction( get_hla_class_name(), rti );
    }

    static void soft_unsubscribe_interaction(RTI::RTIambassador *rti) {
        InteractionRoot::soft_unsubscribe_interaction(get_hla_class_name(), rti);
    }

    static void add_federate_name_soft_publish(const std::string &networkFederateName) {
        InteractionRoot::add_federate_name_soft_publish(get_hla_class_name(), networkFederateName);
    }

    static void remove_federate_name_soft_publish(const std::string &networkFederateName) {
        InteractionRoot::remove_federate_name_soft_publish(get_hla_class_name(), networkFederateName);
    }

    //-----------------------------------------------------
    // END METHODS FOR PUBLISHING/SUBSCRIBING-TO THIS CLASS
    //-----------------------------------------------------

    /**
     * Return true if "handle" is equal to the handle (RTI assigned) of this class
     * (that is, the edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.AttacksNotYetImplemented_p.StartDNSPoisoningAttack interaction class).
     *
     * @param handle handle to compare to the value of the handle (RTI assigned) of
     * this class (the edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.AttacksNotYetImplemented_p.StartDNSPoisoningAttack interaction class).
     * @return "true" if "handle" matches the value of the handle of this class
     * (that is, the edu.vanderbilt.vuisis.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.AttacksNotYetImplemented_p.StartDNSPoisoningAttack interaction class).
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


    /**
     * Set the value of the "affectedHost" parameter to "value" for this parameter.
     *
     * @param value the new value for the "affectedHost" parameter
     */
    void set_affectedHost(const std::string & newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "affectedHost");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
    }

    /**
     * Returns the value of the "affectedHost" parameter of this interaction.
     *
     * @return the value of the "affectedHost" parameter
     */
    std::string get_affectedHost() {
        ClassAndPropertyName key(get_hla_class_name(), "affectedHost");
        return static_cast<std::string>(*_classAndPropertyNameValueSPMap[key]);
    }


    /**
     * Set the value of the "dnsHost" parameter to "value" for this parameter.
     *
     * @param value the new value for the "dnsHost" parameter
     */
    void set_dnsHost(const std::string & newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "dnsHost");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
    }

    /**
     * Returns the value of the "dnsHost" parameter of this interaction.
     *
     * @return the value of the "dnsHost" parameter
     */
    std::string get_dnsHost() {
        ClassAndPropertyName key(get_hla_class_name(), "dnsHost");
        return static_cast<std::string>(*_classAndPropertyNameValueSPMap[key]);
    }


    /**
     * Set the value of the "listenerHost" parameter to "value" for this parameter.
     *
     * @param value the new value for the "listenerHost" parameter
     */
    void set_listenerHost(const std::string & newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "listenerHost");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
    }

    /**
     * Returns the value of the "listenerHost" parameter of this interaction.
     *
     * @return the value of the "listenerHost" parameter
     */
    std::string get_listenerHost() {
        ClassAndPropertyName key(get_hla_class_name(), "listenerHost");
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
        return SP(new StartDNSPoisoningAttack());
    }

    static InteractionRoot::SP create_interaction() {
        return SP(new StartDNSPoisoningAttack());
    }

    virtual InteractionRoot::SP createInteraction() {
        return create_interaction();
    }

    static SP create(const RTIfedTime &rtiFedTime) {
        return SP(new StartDNSPoisoningAttack(rtiFedTime));
    }

    static InteractionRoot::SP create_interaction(const RTIfedTime &rtiFedTime) {
        return SP(new StartDNSPoisoningAttack(rtiFedTime));
    }

    virtual InteractionRoot::SP createInteraction(const RTIfedTime &rtiFedTime) {
        return create_interaction(rtiFedTime);
    }

    static SP create(
      const RTI::ParameterHandleValuePairSet &propertyMap
    ) {
        return SP(new StartDNSPoisoningAttack(propertyMap));
    }

    static InteractionRoot::SP create_interaction(
      const RTI::ParameterHandleValuePairSet &propertyMap
    ) {
        return SP(new StartDNSPoisoningAttack(propertyMap));
    }

    virtual InteractionRoot::SP createInteraction(
      const RTI::ParameterHandleValuePairSet &propertyMap
    ) {
        return create_interaction(propertyMap);
    }

    static SP create(
      const RTI::ParameterHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) {
        return SP(new StartDNSPoisoningAttack(propertyMap, rtiFedTime));
    }

    static InteractionRoot::SP create_interaction(
      const RTI::ParameterHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) {
        return SP(new StartDNSPoisoningAttack(propertyMap, rtiFedTime));
    }

    virtual InteractionRoot::SP createInteraction(
      const RTI::ParameterHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime) {
        return create_interaction(propertyMap, rtiFedTime);
    }

    virtual InteractionRoot::SP cloneInteraction() {
        return InteractionRoot::SP( new StartDNSPoisoningAttack( *this )  );
    }

    //------------------------------
    // END INSTANCE CREATION METHODS
    //------------------------------

    using ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot::add_reject_source_federate_id;
    using ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot::is_reject_source_federate_id;
    using ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot::remove_reject_source_federate_id;

    static void add_reject_source_federate_id(const std::string &federateId) {
        add_reject_source_federate_id(get_hla_class_name(), federateId);
    }

    static bool is_reject_source_federate_id(const std::string &federateId) {
        return is_reject_source_federate_id(get_hla_class_name(), federateId);
    }

    static void remove_reject_source_federate_id(const std::string &federateId) {
        remove_reject_source_federate_id(get_hla_class_name(), federateId);
    }

    //-------------
    // CONSTRUCTORS
    //-------------
public:
    StartDNSPoisoningAttack() : Super( get_hla_class_name() ) { }

    StartDNSPoisoningAttack( const PropertyHandleValuePairSet &propertyMap ) : Super( get_hla_class_name(), propertyMap ) { }

    StartDNSPoisoningAttack( const RTIfedTime &rtiFedTime ) : Super( get_hla_class_name(), rtiFedTime ) { }

    StartDNSPoisoningAttack(const PropertyHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime) :
       Super( get_hla_class_name(), propertyMap, rtiFedTime ) { }

protected:
    StartDNSPoisoningAttack(InteractionRoot::NoInstanceInit &noInstanceInit) : Super(noInstanceInit) { }

    StartDNSPoisoningAttack( const std::string &hlaClassName ) : Super( hlaClassName ) { }

    StartDNSPoisoningAttack( const std::string &hlaClassName, const PropertyHandleValuePairSet &propertyMap ) :
      Super( hlaClassName, propertyMap ) { }

    StartDNSPoisoningAttack( const std::string &hlaClassName, const RTIfedTime &rtiFedTime ) :
      Super( hlaClassName, rtiFedTime ) { }

    StartDNSPoisoningAttack(
      const std::string &hlaClassName, const PropertyHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) : Super( hlaClassName, propertyMap, rtiFedTime ) { }

};
         } // NAMESPACE "AttacksNotYetImplemented_p"
        } // NAMESPACE "OmnetCommand_p"
       } // NAMESPACE "ActionBase_p"
      } // NAMESPACE "C2WInteractionRoot_p"
     } // NAMESPACE "InteractionRoot_p"
    } // NAMESPACE "hla"
   } // NAMESPACE "cpswt"
  } // NAMESPACE "vuisis"
 } // NAMESPACE "vanderbilt"
} // NAMESPACE "edu"

inline std::ostream &operator<<( std::ostream &os, ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::AttacksNotYetImplemented_p::StartDNSPoisoningAttack::SP messagingSP ) {
    return os << *messagingSP;
}

#endif // _edu_vanderbilt_vuisis_cpswt_hla_InteractionRoot_p_C2WInteractionRoot_p_ActionBase_p_OmnetCommand_p_AttacksNotYetImplemented_p_StartDNSPoisoningAttack_CLASS
