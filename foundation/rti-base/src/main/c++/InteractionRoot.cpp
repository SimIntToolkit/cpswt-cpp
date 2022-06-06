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


#include <sstream>
#include "InteractionRoot.hpp"


namespace org {
 namespace cpswt {
  namespace hla {

bool InteractionRoot::static_init_var = InteractionRoot::static_init();

void InteractionRoot::init(RTI::RTIambassador *rtiAmbassador) {
    if (get_is_initialized()) {
        return;
    }
    set_is_initialized(true);

    //-------------------------------------------------------------------------
    // hlaClassNameSet (get_hla_class_name_set()) IS POPULATED BY
    // - STATIC INITIALIZATION BLOCKS IN THE DERIVED INTERACTION/OBJECT CLASSES
    // - THE DYNAMIC-MESSAGE-CLASSES FILE
    //-------------------------------------------------------------------------
    for(const std::string &hlaClassName: get_hla_class_name_set()) {

        if (get_hla_class_name_instance_sp_map().find(hlaClassName) == get_hla_class_name_instance_sp_map().end()) {
            get_dynamic_hla_class_name_set_aux().insert(hlaClassName);
        }

        //----------------------------------------------------
        // GET HANDLE FOR hlaClassName TO INITIALIZE
        // - _classNameHandleMap (get_class_name_handle_map())
        // - _classHandleNameMap (get_class_handle_name_map())
        //----------------------------------------------------
        bool isNotInitialized = true;
        int classHandle = 0;
        while(isNotInitialized) {
            try {
                classHandle = rtiAmbassador->getInteractionClassHandle(hlaClassName.c_str());
                get_class_name_handle_map()[hlaClassName] = classHandle;
                get_class_handle_name_map()[classHandle] = hlaClassName;
                isNotInitialized = false;
            } catch (RTI::FederateNotExecutionMember e) {
                BOOST_LOG_SEV(get_logger(), error) << "could not initialize: federate not execution member";
                return;
            } catch (RTI::NameNotFound e) {
                BOOST_LOG_SEV(get_logger(), error) << "could not initialize: name not found";
                return;
            } catch (...) {
                BOOST_LOG_SEV(get_logger(), error) <<
                  "could not initialize:  unspecified exception caught ... retry";
                defaultSleep();
            }
        }

        //------------------------------------------------------------------------------------
        // _classAndPropertyNameSetSPMap (get_class_name_class_and_property_name_set_sp_map())
        // MAPS hlaClassName TO THE PROPERTIES (PARAMETERS OR ATTRIBUTES)
        // DEFINED *DIRECTLY* IN THE hlaClassName CLASS
        //
        // GET HANDLE FOR THESE PROPERTIES TO INITIALIZE
        // - _classAndPropertyNameHandleMap (get_class_and_property_name_handle_map())
        // - _handleClassAndPropertyNameMap (get_handle_class_and_property_name_sp_map())
        //------------------------------------------------------------------------------------
        ClassAndPropertyNameSet &classAndPropertyNameSet =
          *get_class_name_class_and_property_name_set_sp_map()[hlaClassName];
        for(const ClassAndPropertyName &classAndPropertyName: classAndPropertyNameSet) {
            isNotInitialized = true;
            while(isNotInitialized) {
                try {
                    int propertyHandle = rtiAmbassador->getParameterHandle(
                      classAndPropertyName.getPropertyName().c_str(), classHandle
                    );
                    get_class_and_property_name_handle_map()[classAndPropertyName] = propertyHandle;
                    get_handle_class_and_property_name_sp_map()[propertyHandle] = ClassAndPropertyNameSP(
                        new ClassAndPropertyName(classAndPropertyName)
                    );
                    isNotInitialized = false;
                } catch (RTI::FederateNotExecutionMember e) {
                    BOOST_LOG_SEV(get_logger(), error) << "could not initialize: federate not execution member";
                    return;
                } catch (RTI::InteractionClassNotDefined e) {
                    BOOST_LOG_SEV(get_logger(), error) <<
                      "could not initialize: interaction class not defined";
                    return;
                } catch (RTI::NameNotFound e) {
                    BOOST_LOG_SEV(get_logger(), error) << "could not initialize: name not found";
                    return;
                } catch (...) {
                    BOOST_LOG_SEV(get_logger(), error) <<
                      "could not initialize:  unspecified exception caught ... retry";
                    defaultSleep();
                }
            }
        }

        //-------------------------------------------------------
        // INITIALIZE ALL CLASSES TO NOT-PUBLISHED NOT-SUBSCRIBED
        //-------------------------------------------------------
        get_class_name_publish_status_map()[hlaClassName] = false;
        get_class_name_subscribe_status_map()[hlaClassName] = false;
    }
}

ClassAndPropertyNameSP InteractionRoot::findProperty(
  const std::string &hlaClassName, const std::string &propertyName
) {

    std::list<std::string> classNameComponents;
    boost::algorithm::split(classNameComponents, hlaClassName, boost::is_any_of("."));

    while(!classNameComponents.empty()) {
        std::string localClassName = boost::algorithm::join(classNameComponents, ".");

        ClassAndPropertyName key(localClassName, propertyName);
        if (get_class_and_property_name_handle_map().find(key) != get_class_and_property_name_handle_map().end()) {
            return ClassAndPropertyNameSP(new ClassAndPropertyName(key));
        }

        classNameComponents.pop_back();
    }

    return ClassAndPropertyNameSP();
}

InteractionRoot::PropertyHandleValuePairSetSP InteractionRoot::createPropertyHandleValuePairSetSP() {

    int count = _classAndPropertyNameValueSPMap.size();
    PropertyHandleValuePairSetSP propertyHandleValuePairSetSP(  RTI::ParameterSetFactory::create( count )  );

    PropertyHandleValuePairSet &propertyHandleValuePairSet = *propertyHandleValuePairSetSP;
    for(
      ClassAndPropertyNameValueSPMap::const_iterator cvmCit = _classAndPropertyNameValueSPMap.begin();
      cvmCit != _classAndPropertyNameValueSPMap.end();
      ++cvmCit
    ) {
        const ClassAndPropertyName &classAndPropertyName(cvmCit->first);
        int handle = get_class_and_property_name_handle_map()[classAndPropertyName];
        std::string value = cvmCit->second->getStringRepresentation();
        propertyHandleValuePairSet.add(handle, value.c_str(), value.size());
    }

    return propertyHandleValuePairSetSP;
}

const InteractionRoot::Value &InteractionRoot::getParameter( int propertyHandle ) const {
    static const Value valueDefault(false);
    IntegerClassAndPropertyNameSPMap::const_iterator icmCit =
      get_handle_class_and_property_name_sp_map().find(propertyHandle);
    if (icmCit == get_handle_class_and_property_name_sp_map().end()) {
        BOOST_LOG_SEV(get_logger(), error) << "getParameter: propertyHandle (" << propertyHandle
          <<") does not exist";
        return valueDefault;
    }

    const ValueSP valueSP = _classAndPropertyNameValueSPMap.find(*icmCit->second)->second;
    return *valueSP;
}

void InteractionRoot::publish_interaction(const std::string &hlaClassName, RTI::RTIambassador *rti) {

    if (get_is_published_aux(hlaClassName, true)) {
        return;
    }

    int classHandle = get_class_name_handle_map()[hlaClassName];
    bool isNotPublished = true;
    while(isNotPublished) {
        try {
            rti->publishInteractionClass(classHandle);
            isNotPublished = false;
        } catch (RTI::FederateNotExecutionMember e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not publish: federate not execution member";
            return;
        } catch (RTI::InteractionClassNotDefined e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not publish: interaction class not defined";
            return;
        } catch (...) {
            BOOST_LOG_SEV(get_logger(), error) << "could not publish: unspecified exception caught ... retry";
            defaultSleep();
        }
    }

    BOOST_LOG_SEV(get_logger(), debug) << "publish_interaction: \"" << hlaClassName << "\" interaction published";

    set_is_published(hlaClassName, true);
}

void InteractionRoot::subscribe_interaction(const std::string &hlaClassName, RTI::RTIambassador *rti) {

    if (get_is_subscribed_aux(hlaClassName, true)) {
        return;
    }

    int classHandle = get_class_name_handle_map()[hlaClassName];
    bool isNotSubscribed = true;
    while(isNotSubscribed) {
        try {
            rti->subscribeInteractionClass(classHandle);
            isNotSubscribed = false;
        } catch (RTI::FederateNotExecutionMember e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not subscribe: federate not execution member";
            return;
        } catch (RTI::InteractionClassNotDefined e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not subscribe: interaction class not defined";
            return;
        } catch (...) {
            BOOST_LOG_SEV(get_logger(), error) << "could not subscribe: unspecified exception caught ... retry";
            defaultSleep();
        }
    }

    BOOST_LOG_SEV(get_logger(), debug) << "subscribe_interaction: \"" << hlaClassName << "\" interaction subscribed";

    set_is_subscribed(hlaClassName, true);
}

void InteractionRoot::unpublish_interaction(const std::string &hlaClassName, RTI::RTIambassador *rti) {

    if (!get_is_published_aux(hlaClassName, false)) {
        return;
    }

    int classHandle = get_class_name_handle_map()[hlaClassName];

    bool isNotUnpublished = true;
    while(isNotUnpublished) {
        try {
            rti->unpublishInteractionClass(classHandle);
            isNotUnpublished = false;
        } catch (RTI::FederateNotExecutionMember e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unpublish: federate not execution member";
            return;
        } catch (RTI::InteractionClassNotDefined e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unpublish: interaction class not defined";
            return;
        } catch (RTI::InteractionClassNotPublished e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unpublish: interaction class not published";
            return;
        } catch (...) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unpublish: unspecified exception caught ... retry";
            defaultSleep();
        }
    }
    BOOST_LOG_SEV(get_logger(), debug) << "unpublish_interaction: \"" << hlaClassName << "\" interaction unpublished";

    set_is_published(hlaClassName, false);
}

void InteractionRoot::unsubscribe_interaction(const std::string &hlaClassName, RTI::RTIambassador *rti) {

    if (!get_is_subscribed_aux(hlaClassName, false)) {
        return;
    }

    int classHandle = get_class_name_handle_map()[hlaClassName];

    bool isNotUnsubscribed = true;
    while(isNotUnsubscribed) {
        try {
            rti->unsubscribeInteractionClass(classHandle);
            isNotUnsubscribed = false;
        } catch (RTI::FederateNotExecutionMember e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unsubscribe: federate not execution member";
            return;
        } catch (RTI::InteractionClassNotDefined e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unsubscribe: interaction class not defined";
            return;
        } catch (RTI::InteractionClassNotSubscribed e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unsubscribe: interaction class not subscribed";
            return;
        } catch (...) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unsubscribe: unspecified exception caught ... retry";
            defaultSleep();
        }
    }
    BOOST_LOG_SEV(get_logger(), debug) << "unsubscribe_interaction: \"" << hlaClassName << "\" interaction unsubscribed";

    set_is_subscribed(hlaClassName, false);
}

void InteractionRoot::initializeProperties(const std::string &hlaClassName) {
    setInstanceHlaClassName(hlaClassName);
    if (get_hla_class_name_set().find(hlaClassName) == get_hla_class_name_set().end()) {
        BOOST_LOG_SEV(get_logger(), error)
          << "InteractionRoot( const std::string &hlaClassName ): hlaClassName \"" << hlaClassName
          << "\" is not defined -- creating dummy interaction with fictitious type \"" << hlaClassName
          << "\"";
          return;
    }
    StringClassAndPropertyNameSetSPMap::const_iterator ccmCit =
      get_class_name_all_class_and_property_name_set_sp_map().find(hlaClassName);
    const ClassAndPropertyNameSet &allClassAndPropertyNameSet = *ccmCit->second;
    for(const ClassAndPropertyName &classAndPropertyName: allClassAndPropertyNameSet) {
        _classAndPropertyNameValueSPMap[classAndPropertyName] =
          ValueSP( new Value(*get_class_and_property_name_initial_value_sp_map()[classAndPropertyName]) );
    }
}

void InteractionRoot::setParameters( const RTI::ParameterHandleValuePairSet &propertyMap ) {

    RTI::ULong valueLength;

    int size = propertyMap.size();
    for( int ix = 0 ; ix < size ; ++ix ) {
        try {
            char *value = propertyMap.getValuePointer( ix, valueLength );
            ClassAndPropertyNameSP classAndPropertyNameSP =
              get_handle_class_and_property_name_sp_map()[ propertyMap.getHandle( ix ) ];
            _classAndPropertyNameValueSPMap.find(*classAndPropertyNameSP)->second->setValue(
              std::string( value, valueLength )
            );
        } catch ( ... ) {
            BOOST_LOG_SEV(get_logger(), error) << "setParameters: Exception caught!";
        }
    }
}

bool InteractionRoot::static_init() {
    BOOST_LOG_SEV(get_logger(), info) << "Class \"::org::cpswt::hla::InteractionRoot\" loaded.";

    // ADD THIS CLASS TO THE _classNameSet DEFINED IN InteractionRoot
    get_hla_class_name_set().insert(get_hla_class_name());

    InteractionRoot::NoInstanceInit noInstanceInit;
    SP instanceSP = SP( new InteractionRoot(noInstanceInit) );
    get_hla_class_name_instance_sp_map()[get_hla_class_name()] = instanceSP;

    ClassAndPropertyNameSetSP classAndPropertyNameSetSP( new ClassAndPropertyNameSet() );

    // ADD THIS CLASS'S _classAndPropertyNameSet TO _classNamePropertyNameSetMap DEFINED
    // IN InteractionRoot
    get_class_name_class_and_property_name_set_sp_map()[get_hla_class_name()] = classAndPropertyNameSetSP;

    ClassAndPropertyNameSetSP allClassAndPropertyNameSetSP( new ClassAndPropertyNameSet() );// ADD THIS CLASS'S _allClassAndPropertyNameSet TO _classNameAllPropertyNameSetMap DEFINED
    // IN InteractionRoot
    get_class_name_all_class_and_property_name_set_sp_map()[get_hla_class_name()] = allClassAndPropertyNameSetSP;

    return true;
}


void InteractionRoot::sendInteraction( RTI::RTIambassador *rti, double time ) {
    bool interactionNotSent = true;
    while ( interactionNotSent ) {
        try {
            PropertyHandleValuePairSetSP properties = createPropertyHandleValuePairSetSP();
            rti->sendInteraction(  getClassHandle(), *properties, RTIfedTime( time ), 0  );
            interactionNotSent = false;
        } catch ( RTI::InteractionClassNotDefined & ) {
            BOOST_LOG_SEV(get_logger(), error) << "could not send interaction:  interaction class \"" << get_hla_class_name() << "\" not defined";
            return;
        } catch ( RTI::InteractionClassNotPublished & ) {
            BOOST_LOG_SEV(get_logger(), error) << "could not send interaction:  interaction class \"" << get_hla_class_name() << "\" not published";
            return;
        } catch ( RTI::InteractionParameterNotDefined & ) {
            BOOST_LOG_SEV(get_logger(), error) << "could not send interaction:  parameter for interaction class \"" << get_hla_class_name() << "\" not defined";
            return;
        } catch ( RTI::InvalidFederationTime & ) {
            BOOST_LOG_SEV(get_logger(), error) << "could not send interaction:  invalid federation time (" << time << ")";
            return;
        } catch ( RTI::FederateNotExecutionMember & ) {
            BOOST_LOG_SEV(get_logger(), error) << "could not send interaction:  federate not execution member";
            return;
        } catch ( RTI::ConcurrentAccessAttempted & ) {
            BOOST_LOG_SEV(get_logger(), error) << "could not send interaction:  concurrent access attempted";
            return;
        } catch ( ... ) {
            BOOST_LOG_SEV(get_logger(), error) << "could not send interaction:  unspecified exception caught -- retry";
            defaultSleep();
        }
    }
}

void InteractionRoot::sendInteraction( RTI::RTIambassador *rti ) {
    bool interactionNotSent = true;
    while ( interactionNotSent ) {
        try {
            PropertyHandleValuePairSetSP properties = createPropertyHandleValuePairSetSP();
            rti->sendInteraction(  getClassHandle(), *properties, 0  );
//            createLog( 0, true );
        } catch ( RTI::InteractionClassNotDefined & ) {
            BOOST_LOG_SEV(get_logger(), error) << "could not send interaction:  interaction class \"" << get_hla_class_name() << "\" not defined";
            return;
        } catch ( RTI::InteractionClassNotPublished & ) {
            BOOST_LOG_SEV(get_logger(), error) << "could not send interaction:  interaction class \"" << get_hla_class_name() << "\" not published";
            return;
        } catch ( RTI::InteractionParameterNotDefined & ) {
            BOOST_LOG_SEV(get_logger(), error) << "could not send interaction:  parameter for interaction class \"" << get_hla_class_name() << "\" not defined";
            return;
        } catch ( RTI::FederateNotExecutionMember & ) {
            BOOST_LOG_SEV(get_logger(), error) << "could not send interaction:  federate not execution member";
            return;
        } catch ( RTI::ConcurrentAccessAttempted & ) {
            BOOST_LOG_SEV(get_logger(), error) << "could not send interaction:  concurrent access attempted";
            return;
        } catch ( ... ) {
            BOOST_LOG_SEV(get_logger(), error) << "could not send interaction:  unspecified exception caught -- retry";
            defaultSleep();
        }
    }
}

std::string InteractionRoot::toJson() {
    Json::Value topLevelJSONObject(Json::objectValue);
    topLevelJSONObject["messaging_type"] = "interaction";
    topLevelJSONObject["messaging_name"] = getHlaClassName();

    Json::Value propertyJSONObject(Json::objectValue);
    topLevelJSONObject["properties"] = propertyJSONObject;
    for(
      ClassAndPropertyNameValueSPMap::iterator cvmItr = _classAndPropertyNameValueSPMap.begin() ;
      cvmItr != _classAndPropertyNameValueSPMap.end() ;
      ++cvmItr
    ) {
        const std::string key(cvmItr->first);
        Value &value = *cvmItr->second;
        switch(value.getDataType()) {
            case(TypeMedley::BOOLEAN):
                propertyJSONObject[key] = static_cast<bool>(value);
                break;
            case(TypeMedley::CHARACTER):
                propertyJSONObject[key] = static_cast<char>(value);
                break;
            case(TypeMedley::SHORT):
                propertyJSONObject[key] = static_cast<short>(value);
                break;
            case(TypeMedley::INTEGER):
                propertyJSONObject[key] = static_cast<int>(value);
                break;
            case(TypeMedley::LONG):
                propertyJSONObject[key] = static_cast<Json::Value::Int64>(static_cast<long>(value));
                break;
            case(TypeMedley::STRING):
                propertyJSONObject[key] = static_cast<std::string>(value);
                break;
        }
    }
    Json::StreamWriterBuilder streamWriterBuilder;
    streamWriterBuilder["commentStyle"] = "None";
    streamWriterBuilder["indentation"] = "    ";
    std::unique_ptr<Json::StreamWriter> streamWriterUPtr(streamWriterBuilder.newStreamWriter());
    std::ostringstream stringOutputStream;
    streamWriterUPtr->write(topLevelJSONObject, &stringOutputStream);
    return stringOutputStream.str();
}

InteractionRoot::SP InteractionRoot::fromJson(const std::string &jsonString) {
    std::istringstream jsonInputStream(jsonString);

    Json::Value topLevelJSONObject;
    jsonInputStream >> topLevelJSONObject;

    const std::string hlaClassName(topLevelJSONObject["messaging_name"].asString());
    SP interactionRootSP = create_interaction(hlaClassName);
    if (!interactionRootSP) {
        BOOST_LOG_SEV(get_logger(), error) << "fromJson(std::string):  no such interaction class \""
          << hlaClassName << "\"";
        return SP();
    }

    ClassAndPropertyNameValueSPMap &otherClassAndPropertyNameValueSPMap(
      interactionRootSP->_classAndPropertyNameValueSPMap
    );
    const Json::Value &propertyJSONObject(topLevelJSONObject["properties"]);

    Json::Value::Members members(propertyJSONObject.getMemberNames());
    for(Json::Value::Members::const_iterator mbrCit = members.begin() ; mbrCit != members.end() ; ++mbrCit) {
        const std::string memberName(*mbrCit);
        ClassAndPropertyName classAndPropertyName(memberName);

        switch(otherClassAndPropertyNameValueSPMap[classAndPropertyName]->getDataType()) {
            case TypeMedley::BOOLEAN:
                (*otherClassAndPropertyNameValueSPMap[classAndPropertyName]).setValue(
                  propertyJSONObject[memberName].asBool()
                );
                break;
            case TypeMedley::CHARACTER:
                (*otherClassAndPropertyNameValueSPMap[classAndPropertyName]).setValue(
                  static_cast<char>(propertyJSONObject[memberName].asInt())
                );
                break;
            case TypeMedley::SHORT:
                (*otherClassAndPropertyNameValueSPMap[classAndPropertyName]).setValue(
                  static_cast<short>(propertyJSONObject[memberName].asInt())
                );
                break;
            case TypeMedley::INTEGER:
                (*otherClassAndPropertyNameValueSPMap[classAndPropertyName]).setValue(
                  propertyJSONObject[memberName].asInt()
                );
                break;
            case TypeMedley::LONG:
                (*otherClassAndPropertyNameValueSPMap[classAndPropertyName]).setValue(
                  static_cast<long>(propertyJSONObject[memberName].asInt64())
                );
                break;
            case TypeMedley::STRING:
                (*otherClassAndPropertyNameValueSPMap[classAndPropertyName]).setValue(
                  propertyJSONObject[memberName].asString()
                );
                break;
        }
    }

    return interactionRootSP;
}

void InteractionRoot::readFederateDynamicMessageClasses(std::istream &dynamicMessagingTypesInputStream) {

    Json::Value dynamicMessageTypes;
    dynamicMessagingTypesInputStream >> dynamicMessageTypes;

    Json::Value federationMessaging = get_federation_json()["interactions"];

    std::unordered_set< std::string > localHlaClassNameSet;

    Json::Value dynamicHlaClassNames = dynamicMessageTypes["interactions"];
    for(Json::Value hlaClassNameJsonValue: dynamicHlaClassNames) {
        std::string hlaClassName = hlaClassNameJsonValue.asString();
        std::list<std::string> hlaClassNameComponents;
        boost::algorithm::split(hlaClassNameComponents, hlaClassName, boost::is_any_of("."));
        while(!hlaClassNameComponents.empty()) {
            const std::string localHlaClassName( boost::algorithm::join(hlaClassNameComponents, ".") );
            localHlaClassNameSet.insert(localHlaClassName);
            hlaClassNameComponents.pop_back();
        }
    }

    for(const std::string &hlaClassName: localHlaClassNameSet) {

        get_hla_class_name_set().insert(hlaClassName);

        ClassAndPropertyNameSetSP classAndPropertyNameSetSP( new ClassAndPropertyNameSet() );
        ClassAndPropertyNameSet &classAndPropertyNameSet(*classAndPropertyNameSetSP);

        Json::Value messagingPropertyDataMap = federationMessaging[hlaClassName];
        for(const std::string &propertyName: messagingPropertyDataMap.getMemberNames()) {
            ClassAndPropertyName classAndPropertyName(hlaClassName, propertyName);
            classAndPropertyNameSet.insert(classAndPropertyName);

            Json::Value typeDataMap = messagingPropertyDataMap[propertyName];
            if (!typeDataMap["Hidden"].asBool()) {
                const std::string propertyTypeString = typeDataMap["ParameterType"].asString();
                get_class_and_property_name_initial_value_sp_map()[classAndPropertyName] =
                  ValueSP( new Value(*get_type_initial_value_sp_map()[propertyTypeString]) );
            }
        }

        get_class_name_class_and_property_name_set_sp_map()[hlaClassName] = classAndPropertyNameSetSP;
    }

    for(const std::string &hlaClassName: localHlaClassNameSet) {

        ClassAndPropertyNameSetSP allClassAndPropertyNameSetSP( new ClassAndPropertyNameSet() );
        ClassAndPropertyNameSet &allClassAndPropertyNameSet(*allClassAndPropertyNameSetSP);

        std::list<std::string> hlaClassNameComponents;
        boost::algorithm::split(hlaClassNameComponents, hlaClassName, boost::is_any_of("."));
        while(!hlaClassNameComponents.empty()) {
            const std::string localHlaClassName( boost::algorithm::join(hlaClassNameComponents, ".") );
            ClassAndPropertyNameSet &localClassAndPropertyNameSet =
              *get_class_name_class_and_property_name_set_sp_map()[localHlaClassName];
            allClassAndPropertyNameSet.insert(
              localClassAndPropertyNameSet.begin(), localClassAndPropertyNameSet.end()
            );
            hlaClassNameComponents.pop_back();
        }

        get_class_name_all_class_and_property_name_set_sp_map()[hlaClassName] = allClassAndPropertyNameSetSP;
    }
}


  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"

std::ostream &operator<<( std::ostream &os, const ::org::cpswt::hla::InteractionRoot &messaging ) {

    typedef ::org::cpswt::hla::InteractionRoot::ClassAndPropertyNameValueSPMap::const_iterator const_iterator;
    const ::org::cpswt::hla::InteractionRoot::ClassAndPropertyNameValueSPMap &classAndPropertyNameValueSPMap =
      messaging.getClassAndPropertyNameValueSPMap();
    os << messaging.getHlaClassName() << "(";
    bool first = true;
    for(
      const_iterator cvmCit = classAndPropertyNameValueSPMap.begin() ;
      cvmCit != classAndPropertyNameValueSPMap.end() ;
      ++cvmCit
    ) {
        if (first) first = false;
        else os << ", " ;

        os << static_cast<std::string>(cvmCit->first) << ": ";
        TypeMedley &value = *cvmCit->second;
        switch(value.getDataType()) {
            case TypeMedley::DOUBLE: {
                os << static_cast<double>(value);
                break;
            }
            case TypeMedley::FLOAT: {
                os << static_cast<float>(value);
                break;
            }
            case TypeMedley::STRING: {
                os << "\"" << static_cast<std::string>(value) << "\"";
                break;
            }
            default: {
                os << static_cast<std::string>(value);
                break;
            }
        }
    }
    return os << ")";
}
