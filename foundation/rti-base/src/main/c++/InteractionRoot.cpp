
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

#include <sstream>
#include "InteractionRoot.hpp"


namespace org {
 namespace cpswt {
  namespace hla {

bool InteractionRoot::static_init_var = InteractionRoot::static_init();

std::string InteractionRoot::join(const std::list<std::string> &joinList, const std::string &delimiter) {
    std::string retval;

    if (joinList.empty()) {
        return retval;
    }

    std::list<std::string>::const_iterator strItr = joinList.begin();
    retval += *strItr++;
    while(strItr != joinList.end()) {
        retval += delimiter + *strItr++;
    }

    return retval;
}


ClassAndPropertyNameSP InteractionRoot::findProperty(const std::string &className, const std::string &propertyName) {

    std::list<std::string> classNameComponents;
    boost::algorithm::split(classNameComponents, className, boost::is_any_of("."));

    while(!classNameComponents.empty()) {
        std::string localClassName = boost::algorithm::join(classNameComponents, ".");

        ClassAndPropertyName key(localClassName, propertyName);
        if (get_class_and_property_name_handle_map().find(key) != get_class_and_property_name_handle_map().end()) {
            return ClassAndPropertyNameSP(new ClassAndPropertyName(key));
        }

        classNameComponents.pop_back();
    }

    return ClassAndPropertyNameSP();
}InteractionRoot::SP InteractionRoot::create_interaction( int classHandle, const RTI::ParameterHandleValuePairSet &propertyMap ) {
	IntegerStringMap::iterator ismItr = get_class_handle_name_map().find( classHandle );
	if ( ismItr == get_class_handle_name_map().end() ) {
		return SP();
	}

	StringInstanceSPMap::iterator simItr = get_class_name_instance_sp_map().find( ismItr->second );
	if ( simItr == get_class_name_instance_sp_map().end() ) {
		return SP();
	}

	SP sp = simItr->second->createInteraction();
	sp->setParameters( propertyMap );

	return sp;
}

InteractionRoot::SP InteractionRoot::create_interaction( int classHandle, const RTI::ParameterHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime ) {
	IntegerStringMap::iterator ismItr = get_class_handle_name_map().find( classHandle );
	if ( ismItr == get_class_handle_name_map().end() ) {
		return SP();
	}

	StringInstanceSPMap::iterator simItr = get_class_name_instance_sp_map().find( ismItr->second );
	if ( simItr == get_class_name_instance_sp_map().end() ) {
		return SP();
	}

	SP sp = simItr->second->createInteraction(rtiFedTime);
	sp->setParameters( propertyMap );
	sp->setTime( rtiFedTime.getTime() );

	return sp;
}

const InteractionRoot::Value &InteractionRoot::getParameter( int propertyHandle ) const {
    static const Value valueDefault(false);
    IntegerClassAndPropertyNameSPMap::const_iterator icmCit =
      get_handle_class_and_property_name_sp_map().find(propertyHandle);
    if (icmCit == get_handle_class_and_property_name_sp_map().end()) {
//        logger.error("getParameter: propertyHandle {} does not exist.", propertyHandle);
        return valueDefault;
    }

    const ValueSP valueSP = _classAndPropertyNameValueSPMap.find(*icmCit->second)->second;
    return *valueSP;
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
            std::cerr << "setParameters: Exception caught!" << std::endl;
        }
    }
}


bool InteractionRoot::static_init() {
    // ADD THIS CLASS TO THE _classNameSet DEFINED IN InteractionRoot
    get_class_name_set().insert(get_hla_class_name());

    // ADD CLASS OBJECT OF THIS CLASS TO _classNameClassMap DEFINED IN InteractionRoot
    get_class_name_instance_sp_map()[get_hla_class_name()] = SP(new InteractionRoot());

    // ADD THIS CLASS'S _classAndPropertyNameSet TO _classNamePropertyNameSetMap DEFINED
    // IN InteractionRoot
    get_class_name_class_and_property_name_set_sp_map()[get_hla_class_name()] = get_class_and_property_name_set_sp();

    // ADD THIS CLASS'S _allClassAndPropertyNameSet TO _classNameAllPropertyNameSetMap DEFINED
    // IN InteractionRoot
    get_class_name_all_class_and_property_name_set_sp_map()[get_hla_class_name()] =
      get_all_class_and_property_name_set_sp();

    return true;
}


int InteractionRoot::get_parameter_handle_aux(const std::string &className, const std::string &propertyName) {
    ClassAndPropertyName key(get_hla_class_name(), propertyName);
    ClassAndPropertyNameIntegerMap::const_iterator cimCit = get_class_and_property_name_handle_map().find(key);
    if (cimCit != get_class_and_property_name_handle_map().end()) {
        return cimCit->second;
    }
//    logger.error(
//      "get_parameter_handle: could not find handle for \"{}\" parameter of class \"{}\" or its " +
//      "superclasses.", propertyName, className
//    );
    return -1;
}


void InteractionRoot::init(RTI::RTIambassador *rti) {
    if (get_is_initialized()) return;
    get_is_initialized() = true;

    bool isNotInitialized = true;
    while(isNotInitialized) {
        try {
            get_class_handle() = rti->getInteractionClassHandle(get_hla_class_name().c_str());
            isNotInitialized = false;
        } catch (RTI::FederateNotExecutionMember e) {
//            logger.error("could not initialize: Federate Not Execution Member", e);
            return;
        } catch (RTI::NameNotFound e) {
//            logger.error("could not initialize: Name Not Found", e);
            return;
        } catch (...) {
//            logger.error(e);
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
        }
    }

    get_class_name_handle_map()[get_hla_class_name()] = get_class_handle();
    get_class_handle_name_map()[get_class_handle()] = get_hla_class_name();
    get_class_handle_simple_name_map()[get_class_handle()] = get_simple_class_name();
}


void InteractionRoot::publish_interaction(RTI::RTIambassador *rti) {
    if (get_is_published()) {
        return;
    }
    get_is_published() = true;

    init(rti);

    bool isNotPublished = true;
    while(isNotPublished) {
        try {
            rti->publishInteractionClass(get_class_handle());
            isNotPublished = false;
        } catch (RTI::FederateNotExecutionMember e) {
//            logger.error("could not publish: Federate Not Execution Member", e);
            return;
        } catch (RTI::InteractionClassNotDefined e) {
//            logger.error("could not publish: Interaction Class Not Defined", e);
            return;
        } catch (...) {
//            logger.error(e);
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
        }
    }

//    logger.debug("publish: {}", get_hla_class_name());
}


void InteractionRoot::unpublish_interaction(RTI::RTIambassador *rti) {
    if (!get_is_published()) return;
    get_is_published() = false;

    init(rti);

    bool isNotUnpublished = true;
    while(isNotUnpublished) {
        try {
            rti->unpublishInteractionClass(get_class_handle());
            isNotUnpublished = false;
        } catch (RTI::FederateNotExecutionMember e) {
//            logger.error("could not unpublish: Federate Not Execution Member", e);
            return;
        } catch (RTI::InteractionClassNotDefined e) {
//            logger.error("could not unpublish: Interaction Class Not Defined", e);
            return;
        } catch (RTI::InteractionClassNotPublished e) {
//            logger.error("could not unpublish: Interaction Class Not Published", e);
            return;
        } catch (...) {
//            logger.error(e);
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
        }
    }

//    logger.debug("unpublish: {}", get_hla_class_name());
}


void InteractionRoot::subscribe_interaction(RTI::RTIambassador *rti) {
    if (get_is_subscribed()) {
        return;
    }
    get_is_subscribed() = true;

    init(rti);

    bool isNotSubscribed = true;
    while(isNotSubscribed) {
        try {
            rti->subscribeInteractionClass(get_class_handle());
            isNotSubscribed = false;
        } catch (RTI::FederateNotExecutionMember e) {
//            logger.error("could not subscribe: Federate Not Execution Member", e);
            return;
        } catch (RTI::InteractionClassNotDefined e) {
//            logger.error("could not subscribe: Interaction Class Not Defined", e);
            return;
        } catch (...) {
//            logger.error(e);
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
        }
    }

//    logger.debug("subscribe: {}", get_hla_class_name());
}


void InteractionRoot::unsubscribe_interaction(RTI::RTIambassador *rti) {
    if (!get_is_subscribed()) return;
    get_is_subscribed() = false;

    init(rti);

    bool isNotUnsubscribed = true;
    while(isNotUnsubscribed) {
        try {
            rti->unsubscribeInteractionClass(get_class_handle());
            isNotUnsubscribed = false;
        } catch (RTI::FederateNotExecutionMember e) {
//            logger.error("could not unsubscribe: Federate Not Execution Member", e);
            return;
        } catch (RTI::InteractionClassNotDefined e) {
//            logger.error("could not unsubscribe: Interaction Class Not Defined", e);
            return;
        } catch (RTI::InteractionClassNotSubscribed e) {
//            logger.error("could not unsubscribe: Interaction Class Not Subscribed", e);
            return;
        } catch (...) {
//            logger.error(e);
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
        }
    }

//    logger.debug("unsubscribe: {}", get_hla_class_name());
}


InteractionRoot::PropertyClassNameAndValueSP InteractionRoot::getParameterAux(
  const std::string &className, const std::string &propertyName
) const {

    ClassAndPropertyNameSP classAndPropertyNameSP = findProperty(className, propertyName);
    return classAndPropertyNameSP
      ? PropertyClassNameAndValueSP( new PropertyClassNameAndValue(
          classAndPropertyNameSP->getClassName(),
          _classAndPropertyNameValueSPMap.find(*classAndPropertyNameSP)->second
      ) )
      : PropertyClassNameAndValueSP();
}

InteractionRoot::PropertyHandleValuePairSetSP InteractionRoot::createPropertyHandleValuePairSetSP() {

    int count = _classAndPropertyNameValueSPMap.size();
    PropertyHandleValuePairSetSP propertyHandleValuePairSetSP(  RTI::ParameterSetFactory::create( count )  );

    PropertyHandleValuePairSet &propertyHandleValuePairSet = *propertyHandleValuePairSetSP;
    for(
      ClassAndPropertyNameValueSPMap::iterator cvmItr = _classAndPropertyNameValueSPMap.begin();
      cvmItr != _classAndPropertyNameValueSPMap.end();
      ++cvmItr
    ) {
        const ClassAndPropertyName &classAndPropertyName(cvmItr->first);
        int handle = get_class_and_property_name_handle_map()[classAndPropertyName];
        std::string value = static_cast<std::string>(*cvmItr->second);
        propertyHandleValuePairSet.add(handle, value.c_str(), value.size() + 1);
    }

    return propertyHandleValuePairSetSP;
}

void InteractionRoot::sendInteraction( RTI::RTIambassador *rti, double time ) {
    bool interactionNotSent = true;
    while ( interactionNotSent ) {
        try {
            PropertyHandleValuePairSetSP datamembers = createPropertyHandleValuePairSetSP();
            rti->sendInteraction(  getClassHandle(), *datamembers, RTIfedTime( time ), 0  );
//            createLog( time, true );
            interactionNotSent = false;
        } catch ( RTI::InteractionClassNotDefined & ) {
            std::cerr << "ERROR:  " << getCppClassName() << ":  could not send interaction:  Interaction Class Not Defined" << std::endl;
            return;
        } catch ( RTI::InteractionClassNotPublished & ) {
            std::cerr << "ERROR:  " << getCppClassName() << ":  could not send interaction:  Interaction Class Not Published" << std::endl;
            return;
        } catch ( RTI::InteractionParameterNotDefined & ) {
            std::cerr << "ERROR:  " << getCppClassName() << ":  could not send interaction:  Interaction Parameter Not Defined" << std::endl;
            return;
        } catch ( RTI::InvalidFederationTime & ) {
            std::cerr << "ERROR:  " << getCppClassName() << ":  could not send interaction:  Invalid Federation Time" << std::endl;
            return;
        } catch ( RTI::FederateNotExecutionMember & ) {
            std::cerr << "ERROR:  " << getCppClassName() << ":  could not send interaction:  Federate Not Execution Member" << std::endl;
            return;
        } catch ( RTI::ConcurrentAccessAttempted & ) {
            std::cerr << "ERROR:  " << getCppClassName() << ":  could not send interaction:  ConcurrentAccessAttempted" << std::endl;
            return;
        } catch ( ... ) {
            std::cerr << "ERROR:  " << getCppClassName() << ":  could not send interaction:  Exception caught ... retry" << std::endl;
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
        }
    }
}

void InteractionRoot::sendInteraction( RTI::RTIambassador *rti ) {
    bool interactionNotSent = true;
    while ( interactionNotSent ) {
        try {
            PropertyHandleValuePairSetSP datamembers = createPropertyHandleValuePairSetSP();
            rti->sendInteraction(  getClassHandle(), *datamembers, 0  );
//            createLog( 0, true );
        } catch ( RTI::InteractionClassNotDefined & ) {
            std::cerr << "ERROR:  " << getCppClassName() << ":  could not send interaction:  Interaction Class Not Defined" << std::endl;
            return;
        } catch ( RTI::InteractionClassNotPublished & ) {
            std::cerr << "ERROR:  " << getCppClassName() << ":  could not send interaction:  Interaction Class Not Published" << std::endl;
            return;
        } catch ( RTI::InteractionParameterNotDefined & ) {
            std::cerr << "ERROR:  " << getCppClassName() << ":  could not send interaction:  Interaction Parameter Not Defined" << std::endl;
            return;
        } catch ( RTI::FederateNotExecutionMember & ) {
            std::cerr << "ERROR:  " << getCppClassName() << ":  could not send interaction:  Federate Not Execution Member" << std::endl;
            return;
        } catch ( RTI::ConcurrentAccessAttempted & ) {
            std::cerr << "ERROR:  " << getCppClassName() << ":  could not send interaction:  ConcurrentAccessAttempted" << std::endl;
            return;
        } catch ( ... ) {
            std::cerr << "ERROR:  " << getCppClassName() << ":  could not send interaction:  Exception caught ... retry" << std::endl;
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
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
    streamWriterBuilder["commandStyle"] = "None";
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

    const std::string className(topLevelJSONObject["messaging_name"].asString());
    SP interactionRootSP = create_interaction(className);
    if (!interactionRootSP) {
//        logger.error("InteractionRoot:  fromJson(std::string):  no such interaction class \"{}\"", className);
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


  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"

std::ostream &operator<<( std::ostream &os, const ::org::cpswt::hla::InteractionRoot &messaging ) {

    typedef ::org::cpswt::hla::InteractionRoot::ClassAndPropertyNameValueSPMap::const_iterator const_iterator;
    const ::org::cpswt::hla::InteractionRoot::ClassAndPropertyNameValueSPMap &classAndPropertyNameValueSPMap =
      messaging.getClassAndPropertyNameValueSPMap();
    os << messaging.getCppClassName() << "(";
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
            case TypeMedley::BOOLEAN: os << static_cast<bool>(value);
            case TypeMedley::CHARACTER: os << static_cast<char>(value);
            case TypeMedley::SHORT: os << static_cast<short>(value);
            case TypeMedley::INTEGER: os << static_cast<int>(value);
            case TypeMedley::LONG: os << static_cast<long>(value);
            case TypeMedley::FLOAT: os << static_cast<float>(value);
            case TypeMedley::DOUBLE: os << static_cast<double>(value);
            case TypeMedley::STRING: os << "\"" << static_cast<std::string>(value) << "\"";
        }
    }
    return os << ")";
}
