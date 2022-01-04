#include "InteractionRoot.hpp"


namespace org {
 namespace cpswt {
  namespace hla {

std::string InteractionRoot::join(const std::list<std::string> &joinList, cons std:string &delimiter) {
    std::string retval;

    if (joinList.empty()) {
        return retval;
    }

    std::list<std::string>::iterator strItr = joinList.begin();
    retval += *strItr++;
    while(strItr != joinList.end()) {
        retval += delimiter + *strItr++
    }

    return retval;
}


ClassAndPropertyNameSP InteractionRoot::findProperty(const std:string &className, const std::string &propertyName) {

    std::list<std::string> classNameComponents;
    boost::algorithm:split(classNameComponents, className, boost::is_any_of("."));

    while(!classNameComponents.empty()) {
        std::string localClassName = boost:algorithm::join(classNameComponents, ".");

        ClassAndPropertyName key(localClassName, propertyName);
        if (get_class_and_property_name_handle_map().find(key) != get_class_and_property_name_handle_map().end()) {
            return ClassAndPropertyNameSP(new ClassAndPropertyName(key));
        }

        classNameComponents.pop_back();
    }

    return ClassAndPropertyNameSP(static_cast<ClassAndPropertyName *>(0));
}InteractionRoot::SP InteractionRoot::create_interaction( int classHandle, const RTI::ParameterHandleValuePairSet &propertyMap ) {
	IntegerStringMap::iterator ismItr = getClassHandleNameMap().find( classHandle );
	if ( ismItr == getClassHandleNameMap().end() ) {
		return SP( (InteractionRoot *)0 );
	}

	StringInstanceSPMap::iterator simItr = get_class_name_instance_sp_map().find( ismItr->second );
	if ( simItr == get_class_name_instance_sp_map().end() ) {
		return SP( (InteractionRoot *)0 );
	}

	SP sp = simItr->second->createInteraction();
	sp->setParameters( propertyMap );

	return sp;
}

InteractionRoot::SP InteractionRoot::create_interaction( int classHandle, const RTI::{ property_type|title }}HandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime ) {
	IntegerStringMap::iterator ismItr = getClassHandleNameMap().find( classHandle );
	if ( ismItr == getClassHandleNameMap().end() ) {
		return SP( (InteractionRoot *)0 );
	}

	StringInstanceSPMap::iterator simItr = get_class_name_instance_sp_map().find( ismItr->second );
	if ( simItr == get_class_name_instance_sp_map().end() ) {
		return SP( (InteractionRoot *)0 );
	}

	SP sp = simItr->second->createInteraction(rtiFedTime);
	sp->setParameters( propertyMap );
	sp->setTime( rtiFedTime.getTime() );

	return sp;
}

const Value &InteractionRoot::getParameter( int propertyHandle ) {
    const Value valueDefault(false);
    ClassAndPropertyNameSP classAndPropertyNameSP = _handleClassAndPropertyNameMap.get(propertyHandle);
    if (!classAndPropertyNameSP) {
//        logger.error("getParameter: propertyHandle {} does not exist.", propertyHandle);
        return valueDefault;
    }
    const std::string &propertyName = classAndPropertyName.getPropertyName();
    const ValueSP valueSP = getParameter(propertyName);
    if (!valueSP) {
//        logger.error(
//            "getParameter: propertyHandle {} corresponds to property of name \"{}\", which " +
//            "does not exist in class \"{}\" (it's defined in class\"{}\")",
//            propertyHandle, propertyName, getClass(), classAndPropertyName.getClassName()
//        );
    }

    return *valueSP;
}

void InteractionRoot::setParameters( const RTI::ParameterHandleValuePairSet &propertyMap ) {

    RTI::ULong valueLength;

    int size = propertyMap.size();
    for( int ix = 0 ; ix < size ; ++ix ) {
        try {
            char *value = propertyMap.getValuePointer( ix, valueLength );
            ClassAndPropertyNameSP classAndPropertyNameSP =
              get_handle_class_and_property_name_sp_map()[ propertyName.getHandle( ix ) ]
            _classAndPropertyNameValueSPMap[*classAndPropertyNameSP]->setValue(  std::string( value, valueLength )  );
        } catch ( ... ) {
            std::cerr << "setParameters: Exception caught!" << std::endl;
        }
    }
}


void InteractionRoot::setParameter(int handle, const std::string &value) {
    IntegerClassAndPropertyNameSPMap::const_iterator icmCit =
      get_handle_class_and_property_name_sp_map().find(handle);

    if (icmCit == get_handle_class_and_property_name_sp_map().end()) {
        //ERROR
        return;
    }

    const ClassAndPropertyName &classAndPropertyName = *icmCit->second;
    ValueSP valueSP = _classAndPropertyNameValueSPMap[classAndPropertyName];
    valueSP->setValue(value);
}

bool InteractionRoot::static_init() {
    // ADD THIS CLASS TO THE _classNameSet DEFINED IN InteractionRoot
    get_class_name_set().add(get_hla_class_name());

    // ADD CLASS OBJECT OF THIS CLASS TO _classNameClassMap DEFINED IN InteractionRoot
    get_class_name_instance_sp_map()[get_hla_class_name()] = SP(new InteractionRoot());

    // ADD THIS CLASS'S _classAndPropertyNameSet TO _classNamePropertyNameSetMap DEFINED
    // IN InteractionRoot
    get_class_name_property_name_set_sp_map()[get_hla_class_name()] = get_class_and_property_name_set_sp();

    // ADD THIS CLASS'S _allClassAndPropertyNameSet TO _classNameAllPropertyNameSetMap DEFINED
    // IN InteractionRoot
    get_class_name_all_property_name_set_sp_map()[get_hla_class_name()] = get_all_class_and_property_name_set_sp();
}


int InteractionRoot::get_parameter_handle_aux(const std::string &className, const std:string &propertyName) {
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


void InteractionRoot::init(RTIambassador rti) {
    if (get_is_initialized()) return;
    get_is_initialized() = true;

    boolean isNotInitialized = true;
    while(isNotInitialized) {
        try {
            get_class_handle() = rti.getInteractionClassHandle(get_hla_class_name());
            isNotInitialized = false;
        } catch (FederateNotExecutionMember e) {
            logger.error("could not initialize: Federate Not Execution Member", e);
            return;
        } catch (NameNotFound e) {
            logger.error("could not initialize: Name Not Found", e);
            return;
        } catch (Exception e) {
            logger.error(e);
            CpswtUtils.sleepDefault();
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

    boolean isNotPublished = true;
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
            CpswtUtils.sleepDefault();
        }
    }

//    logger.debug("publish: {}", get_hla_class_name());
}


void InteractionRoot::unpublish_interaction(RTI::RTIambassador *rti) {
    if (!get_is_published()) return;
    get_is_published() = false;

    init(rti);

    boolean isNotUnpublished = true;
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
            CpswtUtils.sleepDefault();
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

    boolean isNotSubscribed = true;
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
            CpswtUtils.sleepDefault();
        }
    }

//    logger.debug("subscribe: {}", get_hla_class_name());
}


void InteractionRoot::unsubscribe_interaction(RTIambassador rti) {
    if (!get_is_subscribed()) return;
    get_is_subscribed() = false;

    init(rti);

    boolean isNotUnsubscribed = true;
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
        } catch (Exception e) {
//            logger.error(e);
            CpswtUtils.sleepDefault();
        }
    }

//    logger.debug("unsubscribe: {}", get_hla_class_name());
}


PropertyClassNameAndValueSP InteractionRoot::getParameterAux(
  const std::string &className, const std::string &propertyName
) {
    ClassAndPropertyName key(get_hla_class_name(), "");

    ClassAndPropertyNameValueSPMap::const_iterator cvmCit = _classAndPropertyNameValueSPMap.find(key);
    if (cvmCit != _classAndPropertyNameValueSPMap.end()) {
        ValueSP valueSP = classAndPropertyNameValueMap[key];
        return PropertyClassNameAndValueSP(new PropertyClassNameAndValue(get_hla_class_name(), valueSP));
    }

//    logger.error(
//      "getparameter(\"{}\"): could not find value for \"{}\" parameter of class \"{}\" or " +
//      "its superclasses.", propertyName, propertyName, className
//    );

    return PropertyClassMemberNameAndValueSP(static_cast<PropertyClassNameAndValue *>(0));
}

PropertyHandleValuePairSetSP InteractionRoot::createPropertyHandleValuePairSet() {

    int count = _classAndPropertyNameValueSPMap.size();
    PropertyHandleValuePairSetSP propertyHandleValuePairSetSP(  RTI::ParameterSetFactory::create( count )  );

    PropertyHandleValuePairSet &propertyHandleValuePairSet = *propertyHandleValuePairSetSP;
    for(
      ClassAndPropertyNameValueSPMap::iterator cvmItr = _classAndPropertyNameValueSPMap.begin();
      cvmItr != _classAndPropertyNameValueSPMap.end();
      ++cvmItr
    ) {
        ClassAndPropertyName &classAndPropertyName(cvmItr->first);
        int handle = get_class_and_property_name_handle_map()[classAndPropertyName];
        std::string value = cvmItr->second.getValue();
        propertyHandleValuePairSet.add(handle, value.c_str(), value.size() + 1);
    }

    return propertyHandleValuePairSetSP;
}

void InteractionRoot::sendInteraction( RTI::RTIambassador *rti, double time ) {
    bool interactionNotSent = true;
    while ( interactionNotSent ) {
        try {
            ParameterHandleValuePairSetSP datamembers = createDatamemberHandleValuePairSet( 0 );
            rti->sendInteraction(  getClassHandle(), *datamembers, RTIfedTime( time ), 0  );
            createLog( time, true );
            interactionNotSent = false;
        } catch ( RTI::InteractionClassNotDefined & ) {
            std::cerr << "ERROR:  " << getClassName() << ":  could not send interaction:  Interaction Class Not Defined" << std::endl;
            return;
        } catch ( RTI::InteractionClassNotPublished & ) {
            std::cerr << "ERROR:  " << getClassName() << ":  could not send interaction:  Interaction Class Not Published" << std::endl;
            return;
        } catch ( RTI::InteractionParameterNotDefined & ) {
            std::cerr << "ERROR:  " << getClassName() << ":  could not send interaction:  Interaction Parameter Not Defined" << std::endl;
            return;
        } catch ( RTI::InvalidFederationTime & ) {
            std::cerr << "ERROR:  " << getClassName() << ":  could not send interaction:  Invalid Federation Time" << std::endl;
            return;
        } catch ( RTI::FederateNotExecutionMember & ) {
            std::cerr << "ERROR:  " << getClassName() << ":  could not send interaction:  Federate Not Execution Member" << std::endl;
            return;
        } catch ( RTI::ConcurrentAccessAttempted & ) {
            std::cerr << "ERROR:  " << getClassName() << ":  could not send interaction:  ConcurrentAccessAttempted" << std::endl;
            return;
        } catch ( ... ) {
            std::cerr << "ERROR:  " << getClassName() << ":  could not send interaction:  Exception caught ... retry" << std::endl;
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
            ParameterHandleValuePairSetSP datamembers = createDatamemberHandleValuePairSet( 0 );
            rti->sendInteraction(  getClassHandle(), *datamembers, 0  );
            createLog( 0, true );
        } catch ( RTI::InteractionClassNotDefined & ) {
            std::cerr << "ERROR:  " << getClassName() << ":  could not send interaction:  Interaction Class Not Defined" << std::endl;
            return;
        } catch ( RTI::InteractionClassNotPublished & ) {
            std::cerr << "ERROR:  " << getClassName() << ":  could not send interaction:  Interaction Class Not Published" << std::endl;
            return;
        } catch ( RTI::InteractionParameterNotDefined & ) {
            std::cerr << "ERROR:  " << getClassName() << ":  could not send interaction:  Interaction Parameter Not Defined" << std::endl;
            return;
        } catch ( RTI::FederateNotExecutionMember & ) {
            std::cerr << "ERROR:  " << getClassName() << ":  could not send interaction:  Federate Not Execution Member" << std::endl;
            return;
        } catch ( RTI::ConcurrentAccessAttempted & ) {
            std::cerr << "ERROR:  " << getClassName() << ":  could not send interaction:  ConcurrentAccessAttempted" << std::endl;
            return;
        } catch ( ... ) {
            std::cerr << "ERROR:  " << getClassName() << ":  could not send interaction:  Exception caught ... retry" << std::endl;
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
        }
    }
}

const std::string InteractionRoot::toJson() {
    Json::Value topLevelJSONObject(Json::objectValue);
    topLevelJSONObject["messaging_type"] = "interaction";
    topLevelJSONObject["messaging_name"] = getHlaClassName();

    Json::Value propertyJSONObject(Json::objectValue);
    topLevelJSONObject["properties"] = propertyJSONObject);
    for(
      ClassAndPropertyNameValueSPMap::iterator cvmItr = _classAndPropertyNameValueSPMap.begin() ;
      cvmItr != _classAndPropertyNameValueSPMap.end() ;
      ++cvmItr
    ) {
        const std::string &key(cvmItr->first);
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
                propertyJSONObject[key] = static_cast<long>(value);
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

static SP InteractionRoot::fromJson(const std::string &jsonString) {
    Json::CharReaderBuilder charReaderBbuilder;
    std::unique_ptr<Json::CharReader> const charReaderUPtr(charReaderBbuilder.newCharReader());

    const char[] jsonCString = strcpy(jsonString.c_str());

    Json::Value topLevelJSONObject(Json::objectValue);
    std::string errorString;
    reader->parse(jsonCString, jsonCString + jsonString.size(), &topLevelJSONObject, &errorString);

    const std::string className(topLevelJSONObject["messaging_name"].asString();
    SP interactionRootSP = create_interaction(className);
    if (!interactionRootSP) {
//        logger.error("InteractionRoot:  fromJson(String):  no such interaction class \"{}\"", className);
        return SP(static_cast<InteractionRoot *>(0));
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
                classAndPropertyNameValueSPMap[classAndPropertyName] =
                  ValueSP(new Value(propertyJSONObject[memberName].asBool()));
                break;
            case TypeMedley::CHARACTER:
                classAndPropertyNameValueSPMap[classAndPropertyName] =
                  ValueSP(new Value(static_cast<char>(propertyJSONObject[memberName].asInt())));
                break;
            case TypeMedley::SHORT:
                classAndPropertyNameValueSPMap[classAndPropertyName] =
                  ValueSP(new Value(static_cast<short>(propertyJSONObject[memberName].asInt())));
                break;
            case TypeMedley::INTEGER:
                classAndPropertyNameValueSPMap[classAndPropertyName] =
                  ValueSP(new Value(propertyJSONObject[memberName].asInt()));
                break;
            case TypeMedley::LONG:
                propertyJSONObject[classAndPropertyName] =
                  ValueSP(new Value(propertyJSONObject[memberName].asInt64()));
                break;
            case TypeMedley::STRING:
                propertyJSONObject[classAndPropertyName] =
                  ValueSP(new Value(propertyJSONObject[memberName].asString()));
                break;
        }
    }

    return interactionRootSP;
}


  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"