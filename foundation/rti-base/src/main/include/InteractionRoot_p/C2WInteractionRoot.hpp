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

#ifndef _org_cpswt_hla_InteractionRoot_p_C2WInteractionRoot_CLASS
#define _org_cpswt_hla_InteractionRoot_p_C2WInteractionRoot_CLASS

#include "InteractionRoot.hpp"
#include "C2WException.hpp"

#include <list>

#include <boost/unordered_set.hpp>


namespace org {
 namespace cpswt {
  namespace hla {
   namespace InteractionRoot_p {

class C2WInteractionRoot : public ::org::cpswt::hla::InteractionRoot {
public:
//    using ::org::cpswt::hla::InteractionRoot;
    typedef ::org::cpswt::hla::InteractionRoot Super;
    typedef boost::shared_ptr< C2WInteractionRoot > SP;

    typedef std::list<std::string> StringList;
    typedef std::set<std::string> StringSet;
    typedef boost::shared_ptr<StringSet> StringSetSP;

private:
    static severity_logger &get_logger_aux() {
        static severity_logger logger;
        logger.add_attribute("MessagingClassName", attrs::constant< std::string >(
          "InteractionRoot.C2WInteractionRoot"
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
     * Returns the fully-qualified (dot-delimited) name of the ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot interaction class.
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
    static const std::string get_simple_class_name() {
        return InteractionRoot::get_simple_class_name(get_hla_class_name());
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
        return InteractionRoot::get_parameter_names( get_hla_class_name() );
    }

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
     * Returns the handle (RTI assigned) of the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot interaction class.
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
     * this interaction class (i.e. "org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot") given the parameter's name.
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
     * Publishes the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot interaction class for a federate.
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
     * Unpublishes the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot interaction class for a federate.
     *
     * @param rti handle to the Local RTI Component, usu. obtained through the
     *            {@link SynchronizedFederate#getLRC()} call
     */
    static void unpublish_interaction(RTI::RTIambassador *rti) {
        InteractionRoot::unpublish_interaction( get_hla_class_name(), rti);
    }

/**
 * Subscribes a federate to the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot interaction class.
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
     * Unsubscribes a federate from the org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot interaction class.
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

    std::set<std::string> getFederateNameSoftPublishSet() {
        return InteractionRoot::get_federate_name_soft_publish_set(get_hla_class_name());
    }

    //-----------------------------------------------------
    // END METHODS FOR PUBLISHING/SUBSCRIBING-TO THIS CLASS
    //-----------------------------------------------------

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

    static int get_num_parameters() {
        return get_class_name_all_class_and_property_name_set_sp_map()[get_hla_class_name()]->size();
    }

    //------------------------------
    // PROPERTY MANIPULATION METHODS
    //------------------------------


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
     * Set the value of the "federateSequence" parameter to "value" for this parameter.
     *
     * @param value the new value for the "federateSequence" parameter
     */
    void set_federateSequence(const std::string & newValue) {
        ClassAndPropertyName key(get_hla_class_name(), "federateSequence");
        Value &value(*_classAndPropertyNameValueSPMap[key]);
        value.setValue(newValue);
    }

    /**
     * Returns the value of the "federateSequence" parameter of this interaction.
     *
     * @return the value of the "federateSequence" parameter
     */
    std::string get_federateSequence() {
        ClassAndPropertyName key(get_hla_class_name(), "federateSequence");
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
        return SP(new C2WInteractionRoot());
    }

    static InteractionRoot::SP create_interaction() {
        return SP(new C2WInteractionRoot());
    }

    virtual InteractionRoot::SP createInteraction() {
        return create_interaction();
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
private:
    static bool is_federate_sequence(const std::string &federateSequence);

    static void update_federate_sequence_aux(::org::cpswt::hla::InteractionRoot &interactionRoot, const std::string &federateId);
    static StringList get_federate_sequence_list_aux(const ::org::cpswt::hla::InteractionRoot &interactionRoot);

public:
    static void update_federate_sequence(::org::cpswt::hla::InteractionRoot &interactionRoot, const std::string &federateId) {
        const std::string &instanceHlaClassName = interactionRoot.getInstanceHlaClassName();

        if ( instanceHlaClassName.find("InteractionRoot.C2WInteractionRoot", 0) == 0 ) {
            update_federate_sequence_aux(interactionRoot, federateId);
        }
    }

    static void update_federate_sequence(::org::cpswt::hla::InteractionRoot::SP &interactionRootSP, const std::string &federateId) {
        return update_federate_sequence(*interactionRootSP, federateId);
    }

    void updateFederateSequence(const std::string &federateId) {
        update_federate_sequence_aux(*this, federateId);
    }

    static StringList get_federate_sequence_list(const ::org::cpswt::hla::InteractionRoot &interactionRoot) {
        const std::string &instanceHlaClassName = interactionRoot.getInstanceHlaClassName();

        return instanceHlaClassName.find("InteractionRoot.C2WInteractionRoot", 0) == 0 ?
            get_federate_sequence_list_aux(interactionRoot) : StringList();
    }

    static StringList get_federate_sequence_list(::org::cpswt::hla::InteractionRoot::SP interactionRootSP) {
        return get_federate_sequence_list(*interactionRootSP);
    }

    StringList getFederateSequenceList() {
        return get_federate_sequence_list(*this);
    }

    static std::string get_origin_federate_id( const ::org::cpswt::hla::InteractionRoot &interactionRoot ) {
        StringList federateSequenceList = get_federate_sequence_list(interactionRoot);
        return federateSequenceList.empty() ? std::string() : federateSequenceList.front();
    }

    static std::string get_origin_federate_id( ::org::cpswt::hla::InteractionRoot::SP &interactionRootSP ) {
        return get_origin_federate_id( *interactionRootSP );
    }

    std::string getOriginFederateId() const {
        return  get_origin_federate_id(*this);
    }

    static std::string get_source_federate_id( const ::org::cpswt::hla::InteractionRoot &interactionRoot ) {
        StringList federateSequenceList = get_federate_sequence_list( interactionRoot );
        return federateSequenceList.empty() ? std::string() : federateSequenceList.back();
    }

    static std::string get_source_federate_id( ::org::cpswt::hla::InteractionRoot::SP &interactionRootSP ) {
        return get_source_federate_id( *interactionRootSP );
    }

    std::string getSourceFederateId() const {
        return  get_source_federate_id(*this);
    }

private:
    static std::map<std::string, StringSetSP> &get_hla_class_name_to_reject_source_federate_id_set_sp_map() {
        static std::map< std::string, StringSetSP> hla_class_name_to_reject_source_federate_id_set_sp_map;
        return hla_class_name_to_reject_source_federate_id_set_sp_map;
    }

public:
    static void add_reject_source_federate_id(const std::string &hlaClassName, const std::string &federateId);

    void addRejectSourceFederateId(const std::string &federateId) {
        add_reject_source_federate_id(getInstanceHlaClassName(), federateId);
    }

    static bool is_reject_source_federate_id(const std::string &hlaClassName, const std::string &federateId);

    static bool is_reject_source_federate_id(
      ::org::cpswt::hla::InteractionRoot &interactionRoot
    ) {
        return is_reject_source_federate_id(
          interactionRoot.getInstanceHlaClassName(), get_source_federate_id(interactionRoot)
        );
    }

    static bool is_reject_source_federate_id(
      ::org::cpswt::hla::InteractionRoot::SP &interactionRootSP
    ) {
        return is_reject_source_federate_id(*interactionRootSP);
    }

    bool isRejectSourceFederateId() {
        return is_reject_source_federate_id(*this);
    }

    static void remove_reject_source_federate_id(const std::string &hlaClassName, const std::string &federateId);

    void removeRejectSourceFederateId(const std::string &federateId) {
        remove_reject_source_federate_id(getInstanceHlaClassName(), federateId);
    }

    // THIS METHOD ACTS AS AN ERROR DETECTOR -- ALL INSTANCES OF C2WInteractionRoot
    // SHOULD HAVE A NON-EMPTY JSON-ARRAY VALUE FOR THEIR federateSequence PARAMETER.
    void sendInteraction( RTI::RTIambassador *rtiAmbassador, double time ) override {
        if (  !is_federate_sequence( get_federateSequence() )  ) {
            BOOST_LOG_SEV(get_logger(), error) << "federateSequence parameter is invalid: must contain sequence " <<
                "of federate-ids of federates that have handled this interaction.";
            return;
        }
        Super::sendInteraction( rtiAmbassador, time );
    }

    // THIS METHOD ACTS AS AN ERROR DETECTOR -- ALL INSTANCES OF C2WInteractionRoot
    // SHOULD HAVE A NON-EMPTY JSON-ARRAY VALUE FOR THEIR federateSequence PARAMETER.
    void sendInteraction( RTI::RTIambassador *rtiAmbassador ) override {
        if (  !is_federate_sequence( get_federateSequence() )   ) {
            BOOST_LOG_SEV(get_logger(), error) << "federateSequence parameter is invalid: must contain sequence " <<
                "of federate-ids of federates that have handled this interaction.";
            return;
        }
        Super::sendInteraction( rtiAmbassador );
    }

    static void readRejectSourceFederateIdData(const std::string &rejectSourceFederateIdJsonFileString) {
        std::ifstream rejectSourceFederateIdInputFileStream( rejectSourceFederateIdJsonFileString );
        readRejectSourceFederateIdData(rejectSourceFederateIdInputFileStream);
        rejectSourceFederateIdInputFileStream.close();
    }

    static void readRejectSourceFederateIdData(std::istream &rejectSourceFederateIdInputFileStream) {
        Json::Value rejectSourceFederateIdData;
        rejectSourceFederateIdInputFileStream >> rejectSourceFederateIdData;

        for(
          Json::Value::const_iterator sfdCit = rejectSourceFederateIdData.begin() ;
          sfdCit != rejectSourceFederateIdData.end() ;
          ++sfdCit
        ) {
            const std::string &hlaClassName = sfdCit.key().asString();
            for(Json::Value federateId: *sfdCit) {
                add_reject_source_federate_id(hlaClassName, federateId.asString());
            }
        }
    }

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
    C2WInteractionRoot() : Super( get_hla_class_name() ) { }

    C2WInteractionRoot( const PropertyHandleValuePairSet &propertyMap ) : Super( get_hla_class_name(), propertyMap ) { }

    C2WInteractionRoot( const RTIfedTime &rtiFedTime ) : Super( get_hla_class_name(), rtiFedTime ) { }

    C2WInteractionRoot(const PropertyHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime) :
       Super( get_hla_class_name(), propertyMap, rtiFedTime ) { }

protected:
    C2WInteractionRoot(InteractionRoot::NoInstanceInit &noInstanceInit) : Super(noInstanceInit) { }

    C2WInteractionRoot( const std::string &hlaClassName ) : Super( hlaClassName ) { }

    C2WInteractionRoot( const std::string &hlaClassName, const PropertyHandleValuePairSet &propertyMap ) :
      Super( hlaClassName, propertyMap ) { }

    C2WInteractionRoot( const std::string &hlaClassName, const RTIfedTime &rtiFedTime ) :
      Super( hlaClassName, rtiFedTime ) { }

    C2WInteractionRoot(
      const std::string &hlaClassName, const PropertyHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime
    ) : Super( hlaClassName, propertyMap, rtiFedTime ) { }

};
   } // NAMESPACE "InteractionRoot_p"
  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"

inline std::ostream &operator<<( std::ostream &os, ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot::SP messagingSP ) {
    return os << *messagingSP;
}

#endif // _org_cpswt_hla_InteractionRoot_p_C2WInteractionRoot_CLASS
