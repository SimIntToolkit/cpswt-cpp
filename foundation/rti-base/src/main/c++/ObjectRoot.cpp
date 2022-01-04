#include "ObjectRoot.hpp"


namespace org {
 namespace cpswt {
  namespace hla {

std::string ObjectRoot::join(const std::list<std::string> &joinList, cons std:string &delimiter) {
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


ClassAndPropertyNameSP ObjectRoot::findProperty(const std:string &className, const std::string &propertyName) {

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
}ObjectRoot::SP ObjectRoot::create_object( int classHandle, const RTI::AttributeHandleValuePairSet &propertyMap ) {
	IntegerStringMap::iterator ismItr = getClassHandleNameMap().find( classHandle );
	if ( ismItr == getClassHandleNameMap().end() ) {
		return SP( (InteractionRoot *)0 );
	}

	StringInstanceSPMap::iterator simItr = get_class_name_instance_sp_map().find( ismItr->second );
	if ( simItr == get_class_name_instance_sp_map().end() ) {
		return SP( (InteractionRoot *)0 );
	}

	SP sp = simItr->second->createObject();
	sp->setParameters( propertyMap );

	return sp;
}

ObjectRoot::SP ObjectRoot::create_object( int classHandle, const RTI::{ property_type|title }}HandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime ) {
	IntegerStringMap::iterator ismItr = getClassHandleNameMap().find( classHandle );
	if ( ismItr == getClassHandleNameMap().end() ) {
		return SP( (InteractionRoot *)0 );
	}

	StringInstanceSPMap::iterator simItr = get_class_name_instance_sp_map().find( ismItr->second );
	if ( simItr == get_class_name_instance_sp_map().end() ) {
		return SP( (InteractionRoot *)0 );
	}

	SP sp = simItr->second->createObject(rtiFedTime);
	sp->setParameters( propertyMap );
	sp->setTime( rtiFedTime.getTime() );

	return sp;
}

void ObjectRoot::registerObject( RTI::RTIambassador *rti ) {

    while( !_isRegistered ) {
        try {
            _object_handle = rti->registerObjectInstance( getClassHandle() );
            _isRegistered = true;
        } catch ( RTI::ObjectClassNotDefined & ) {
        	std::cerr << "ERROR:  InteractionRoot::registerObject:  Object Class Not Defined" << std::endl;
            return;
        } catch ( RTI::ObjectClassNotPublished & ) {
        	std::cerr << "ERROR:  InteractionRoot::registerObject:  Object Class Not Published" << std::endl;
            return;
        } catch ( RTI::FederateNotExecutionMember & ) {
        	std::cerr << "ERROR:  InteractionRoot::registerObject:  Federate Not Execution Member" << std::endl;
            return;
        } catch ( ... ) {
        	std::cerr << "InteractionRoot::registerObject:  Exception caught ... retry" << std::endl;
        }
    }

}

void ObjectRoot::registerObject( RTI::RTIambassador *rti, const std::string &name ) throw ( RTI::ObjectAlreadyRegistered ) {
    while( !_isRegistered ) {
        try {
            _object_handle = rti->registerObjectInstance( getClassHandle(), name.c_str() );
            _isRegistered = true;
        } catch ( RTI::ObjectClassNotDefined & ) {
            std::cerr << "ERROR:  InteractionRoot::registerObject:  Object Class Not Defined" << std::endl;
            return;
        } catch ( RTI::ObjectClassNotPublished & ) {
            std::cerr << "ERROR:  InteractionRoot::registerObject:  Object Class Not Published" << std::endl;
            return;
        } catch ( RTI::FederateNotExecutionMember & ) {
            std::cerr << "ERROR:  InteractionRoot::registerObject:  Federate Not Execution Member" << std::endl;
            return;
        } catch ( RTI::ObjectAlreadyRegistered & ) {
            throw;
        } catch ( ... ) {
            std::cerr << "InteractionRoot::registerObject:  Exception caught ... retry" << std::endl;
        }
    }
}

void ObjectRoot::unregisterObject( RTI::RTIambassador *rti ) {

    while( _isRegistered ) {
        try {
            rti->deleteObjectInstance( getObjectHandle(), 0 );
            _isRegistered = false;
        } catch ( RTI::ObjectNotKnown & ) {
        	std::cerr << "ERROR:  InteractionRoot::unregisterObject:  Object Not Known" << std::endl;
            return;
        } catch ( RTI::DeletePrivilegeNotHeld & ) {
        	std::cerr << "ERROR:  InteractionRoot::unregisterObject:  Delete Privilege Not Held" << std::endl;
            return;
        } catch ( RTI::FederateNotExecutionMember & ) {
        	std::cerr << "ERROR:  InteractionRoot::unregisterObject:  Federate Not Execution Member" << std::endl;
            return;
        } catch ( ... ) {
        	std::cerr << "InteractionRoot::unregisterObject:  Exception caught ... retry" << std::endl;
        }
    }
}

void ObjectRoot::requestUpdate( RTI::RTIambassador *rti ) {
	bool requestNotSubmitted = true;
	while( requestNotSubmitted ) {
		try {		
			rti->requestObjectAttributeValueUpdate( getObjectHandle(), getSubscribedAttributeHandleSet_var() );
			requestNotSubmitted = false;
		} catch ( RTI::FederateNotExecutionMember & ) {
			std::cerr << "ERROR: " << getClassName() << "request for update failed:  Federate Not Execution Member" << std::endl;
			return;				
		} catch ( RTI::ObjectNotKnown & ) {
			std::cerr << "ERROR: " << getClassName() << "request for update failed:  Object Not Known" << std::endl;
			return;				
		} catch ( RTI::AttributeNotDefined & ) {
			std::cerr << "ERROR: " << getClassName() << "request for update failed:  Name Not Found" << std::endl;
			return;				
		} catch ( ... ) {
			std::cerr << "ERROR: " << getClassName() << "request for update failed:  Unknown Exception" << std::endl;			}
	}
}

const Value &ObjectRoot::getAttribute( int propertyHandle ) {
    const Value valueDefault(false);
    ClassAndPropertyNameSP classAndPropertyNameSP = _handleClassAndPropertyNameMap.get(propertyHandle);
    if (!classAndPropertyNameSP) {
//        logger.error("getAttribute: propertyHandle {} does not exist.", propertyHandle);
        return valueDefault;
    }
    const std::string &propertyName = classAndPropertyName.getPropertyName();
    const ValueSP valueSP = getAttribute(propertyName);
    if (!valueSP) {
//        logger.error(
//            "getAttribute: propertyHandle {} corresponds to property of name \"{}\", which " +
//            "does not exist in class \"{}\" (it's defined in class\"{}\")",
//            propertyHandle, propertyName, getClass(), classAndPropertyName.getClassName()
//        );
    }

    return *valueSP;
}

void ObjectRoot::setAttributes( const RTI::AttributeHandleValuePairSet &propertyMap ) {

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


void ObjectRoot::setAttribute(int handle, const std::string &value) {
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

bool ObjectRoot::static_init() {
    // ADD THIS CLASS TO THE _classNameSet DEFINED IN ObjectRoot
    get_class_name_set().add(get_hla_class_name());

    // ADD CLASS OBJECT OF THIS CLASS TO _classNameClassMap DEFINED IN ObjectRoot
    get_class_name_instance_sp_map()[get_hla_class_name()] = SP(new ObjectRoot());

    // ADD THIS CLASS'S _classAndPropertyNameSet TO _classNamePropertyNameSetMap DEFINED
    // IN ObjectRoot
    get_class_name_property_name_set_sp_map()[get_hla_class_name()] = get_class_and_property_name_set_sp();

    // ADD THIS CLASS'S _allClassAndPropertyNameSet TO _classNameAllPropertyNameSetMap DEFINED
    // IN ObjectRoot
    get_class_name_all_property_name_set_sp_map()[get_hla_class_name()] = get_all_class_and_property_name_set_sp();

    get_class_name_published_attribute_name_set_sp_map()[get_hla_class_name()] =
      get_published_attribute_name_set_sp());
    get_class_name_published_attribute_name_set_sp_map()[get_hla_class_name()] =
      get_subscribed_attribute_name_set_sp());

    get_class_name_published_attribute_handle_set_sp_map()[get_hla_class_name()] =
      get_published_attribute_handle_set_sp();

    get_class_name_subscribed_attribute_handle_set_sp_map()[get_hla_class_name()] =
      get_subscribed_attribute_handle_set_sp();
}


int ObjectRoot::get_attribute_handle_aux(const std::string &className, const std:string &propertyName) {
    ClassAndPropertyName key(get_hla_class_name(), propertyName);
    ClassAndPropertyNameIntegerMap::const_iterator cimCit = get_class_and_property_name_handle_map().find(key);
    if (cimCit != get_class_and_property_name_handle_map().end()) {
        return cimCit->second;
    }
//    logger.error(
//      "get_attribute_handle: could not find handle for \"{}\" attribute of class \"{}\" or its " +
//      "superclasses.", propertyName, className
//    );
    return -1;
}


void ObjectRoot::init(RTIambassador rti) {
    if (get_is_initialized()) return;
    get_is_initialized() = true;

    boolean isNotInitialized = true;
    while(isNotInitialized) {
        try {
            get_class_handle() = rti.getObjectClassHandle(get_hla_class_name());
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


void ObjectRoot::publish_object(RTI::RTIambassador *rti) {
    if (get_is_published()) {
        return;
    }
    get_is_published() = true;

    init(rti);

    get_published_attribute_handle_set_sp()->empty();
    for(
      ClassAndPropertyNameSet::const_iterator cnsCit = get_published_attribute_name_set_sp()->begin() ;
      cnsCit != get_published_attribute_name_set_sp()->end() ;
      ++cnsCit
    ) {
        try {
            get_published_attribute_handle_set_sp()->add(get_class_and_property_name_handle_map()[*cnsCit]);
//            logger.trace("publish {}:{}", get_hla_class_name(), key.toString());
        } catch (Exception e) {
//            logger.error("could not publish \"" + key.toString() + "\" attribute.", e);
        }
    }

    boolean isNotPublished = true;
    while(isNotPublished) {
        try {
            rti->publishObjectClass(get_class_handle(), *get_published_attribute_handle_set_sp());
            isNotPublished = false;
        } catch (RTI::FederateNotExecutionMember e) {
//            logger.error("could not publish: Federate Not Execution Member", e);
            return;
        } catch (RTI::ObjectClassNotDefined e) {
//            logger.error("could not publish: Object Class Not Defined", e);
            return;
        } catch (...) {
//            logger.error(e);
            CpswtUtils.sleepDefault();
        }
    }

//    logger.debug("publish: {}", get_hla_class_name());
}


void ObjectRoot::unpublish_object(RTI::RTIambassador *rti) {
    if (!get_is_published()) return;
    get_is_published() = false;

    init(rti);

    boolean isNotUnpublished = true;
    while(isNotUnpublished) {
        try {
            rti->unpublishObjectClass(get_class_handle());
            isNotUnpublished = false;
        } catch (RTI::FederateNotExecutionMember e) {
//            logger.error("could not unpublish: Federate Not Execution Member", e);
            return;
        } catch (RTI::ObjectClassNotDefined e) {
//            logger.error("could not unpublish: Object Class Not Defined", e);
            return;
        } catch (RTI::ObjectClassNotPublished e) {
//            logger.error("could not unpublish: Object Class Not Published", e);
            return;
        } catch (...) {
//            logger.error(e);
            CpswtUtils.sleepDefault();
        }
    }

//    logger.debug("unpublish: {}", get_hla_class_name());
}


void ObjectRoot::subscribe_object(RTI::RTIambassador *rti) {
    if (get_is_subscribed()) {
        return;
    }
    get_is_subscribed() = true;

    init(rti);

    get_subscribed_attribute_handle_set_sp().empty();
    for(
      ClassAndPropertyNameSet::const_iterator cnsCit = get_subscribed_attribute_name_set_sp()->begin() ;
      cnsCit != get_subscribed_attribute_name_set_sp()->end() ;
      ++cnsCit
    ) {
        try {
            get_subscribed_attribute_handle_set_sp()->add(get_class_and_property_name_handle_map()[*cnsCit]);
//            logger.trace("subscribe {}:{}", get_hla_class_name(), key.toString());
        } catch (Exception e) {
//            logger.error("could not subscribe to \"" + key + "\" attribute.", e);
        }
    }

    boolean isNotSubscribed = true;
    while(isNotSubscribed) {
        try {
            rti->subscribeObjectClassAttributes(get_class_handle(), *get_subscribed_attribute_handle_set_sp());
            isNotSubscribed = false;
        } catch (RTI::FederateNotExecutionMember e) {
//            logger.error("could not subscribe: Federate Not Execution Member", e);
            return;
        } catch (RTI::ObjectClassNotDefined e) {
//            logger.error("could not subscribe: Object Class Not Defined", e);
            return;
        } catch (...) {
//            logger.error(e);
            CpswtUtils.sleepDefault();
        }
    }

//    logger.debug("subscribe: {}", get_hla_class_name());
}


void ObjectRoot::unsubscribe_object(RTIambassador rti) {
    if (!get_is_subscribed()) return;
    get_is_subscribed() = false;

    init(rti);

    boolean isNotUnsubscribed = true;
    while(isNotUnsubscribed) {
        try {
            rti->unsubscribeObjectClass(get_class_handle());
            isNotUnsubscribed = false;
        } catch (RTI::FederateNotExecutionMember e) {
//            logger.error("could not unsubscribe: Federate Not Execution Member", e);
            return;
        } catch (RTI::ObjectClassNotDefined e) {
//            logger.error("could not unsubscribe: Object Class Not Defined", e);
            return;
        } catch (RTI::ObjectClassNotSubscribed e) {
//            logger.error("could not unsubscribe: Object Class Not Subscribed", e);
            return;
        } catch (Exception e) {
//            logger.error(e);
            CpswtUtils.sleepDefault();
        }
    }

//    logger.debug("unsubscribe: {}", get_hla_class_name());
}


PropertyClassNameAndValueSP ObjectRoot::getAttributeAux(
  const std::string &className, const std::string &propertyName
) {
    ClassAndPropertyName key(get_hla_class_name(), "");

    ClassAndPropertyNameValueSPMap::const_iterator cvmCit = _classAndPropertyNameValueSPMap.find(key);
    if (cvmCit != _classAndPropertyNameValueSPMap.end()) {
        ValueSP valueSP = classAndPropertyNameValueMap[key];
        return PropertyClassNameAndValueSP(new PropertyClassNameAndValue(get_hla_class_name(), valueSP));
    }

//    logger.error(
//      "getattribute(\"{}\"): could not find value for \"{}\" attribute of class \"{}\" or " +
//      "its superclasses.", propertyName, propertyName, className
//    );

    return PropertyClassMemberNameAndValueSP(static_cast<PropertyClassNameAndValue *>(0));
}

PropertyHandleValuePairSetSP ObjectRoot::createPropertyHandleValuePairSet() {

    int count = getPublishedAttributeSet().size();
    PropertyHandleValuePairSetSP propertyHandleValuePairSetSP(  RTI::AttributeSetFactory::create( count )  );

    ClassAndPropertyNameSet classAndPropertyNameSet = getPublishedClassAndPropertyNameSet();
    PropertyHandleValuePairSet &propertyHandleValuePairSet = *propertyHandleValuePairSetSP;
    for(
      ClassAndPropertyNameSet::iterator cnsItr = classAndPropertyNameSet.begin();
      cnsItr != classAndPropertyNameSet.end();
      ++cvmItr
    ) {
        const ClassAndPropertyName &classAndPropertyName(*cvmItr);
        int handle = get_class_and_property_name_handle_map()[classAndPropertyName];
        std::string value = _classAndPropertyNameValueSPMap[classAndPropertyName].getValue();
        propertyHandleValuePairSet.add(handle, value.c_str(), value.size() + 1);
    }

    return propertyHandleValuePairSetSP;
}

void ObjectRoot::updateAttributeValues( RTI::RTIambassador *rti, double time, bool force ) {
    AttributeHandleValuePairSetSP suppliedAttributesSP = createDatamemberHandleValuePairSet( force );
    if ( suppliedAttributesSP->size() == 0 ) {
        return;
    }
    try {
        rti->updateAttributeValues(  getObjectHandle(), *suppliedAttributesSP, RTIfedTime( time ), 0  );
        createLog( time, true );
    } catch ( RTI::ObjectNotKnown & ) {
        std::cerr << "ERROR:  " << getClassName() << ":  could not update attributes:  Object Not Known" << std::endl;
        return;
    } catch ( RTI::FederateNotExecutionMember & ) {
        std::cerr << "ERROR:  " << getClassName() << ":  could not update attributes:  Federate Not Execution Member" << std::endl;
        return;
    } catch ( RTI::AttributeNotDefined & ) {
        std::cerr << "ERROR:  " << getClassName() << ":  could not update attributes:  Attribute Not Defined" << std::endl;
        return;
    } catch ( RTI::AttributeNotOwned & ) {
        std::cerr << "ERROR:  " << getClassName() << ":  could not update attributes:  Attribute Not Owned" << std::endl;
        return;
    } catch ( RTI::ConcurrentAccessAttempted & ) {
        std::cerr << "ERROR:  " << getClassName() << ":  could not update attributes:  Concurrent Access Attempted" << std::endl;
        return;
    } catch ( RTI::InvalidFederationTime & ) {
        std::cerr << "ERROR:  " << getClassName() << ":  could not update attributes:  Invalid Federation Time" << std::endl;
        return;
    } catch ( ... ) {
        std::cerr << "ERROR:  " << getClassName() << ":  could not update attributes:  exception caught" << std::endl;
    }
}

void ObjectRoot::updateAttributeValues( RTI::RTIambassador *rti, bool force ) {
    AttributeHandleValuePairSetSP suppliedAttributesSP = createDatamemberHandleValuePairSet( force );
    if ( suppliedAttributesSP->size() == 0 ) {
        return;
    }
    try {
        rti->updateAttributeValues( getObjectHandle(), *suppliedAttributesSP, 0 );
        createLog( 0, true );
    } catch ( RTI::ObjectNotKnown & ) {
        std::cerr << "ERROR:  " << getClassName() << ":  could not update attributes:  Object Not Known" << std::endl;
        return;
    } catch ( RTI::FederateNotExecutionMember & ) {
        std::cerr << "ERROR:  " << getClassName() << ":  could not update attributes:  Federate Not Execution Member" << std::endl;
        return;
    } catch ( RTI::AttributeNotDefined & ) {
        std::cerr << "ERROR:  " << getClassName() << ":  could not update attributes:  Attribute Not Defined" << std::endl;
        return;
    } catch ( RTI::AttributeNotOwned & ) {
        std::cerr << "ERROR:  " << getClassName() << ":  could not update attributes:  Attribute Not Owned" << std::endl;
        return;
    } catch ( RTI::ConcurrentAccessAttempted & ) {
        std::cerr << "ERROR:  " << getClassName() << ":  could not update attributes:  Concurrent Access Attempted" << std::endl;
        return;
    } catch ( RTI::InvalidFederationTime & ) {
        std::cerr << "ERROR:  " << getClassName() << ":  could not update attributes:  Invalid Federation Time" << std::endl;
        return;
    } catch ( ... ) {
        std::cerr << "ERROR:  " << getClassName() << ":  could not update attributes:  exception caught" << std::endl;
    }
}

std::string ObjectRoot::toJson() {
    Json::Value topLevelJSONObject(Json::objectValue);
    topLevelJSONObject["messaging_type"] = "interaction";
    topLevelJSONObject["object_handle"] = getObjectHandle();

    Json::Value propertyJSONObject(Json::objectValue);
    topLevelJSONObject["properties"] = propertyJSONObject;
    for(
      ClassAndPropertyNameSet::const_iterator cnsCit = getPublishedAttributeNameSetSP()->begin() ;
      cnsCit != getPublishedAttributeNameSetSP()->end() ;
      ++cnsCit
    ) {
        const std::string &key(cvmItr->first);
        Attribute &value = *cvmItr->second;
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

static void ObjectRoot::fromJson(const std::string &jsonString) {
    Json::CharReaderBuilder charReaderBbuilder;
    std::unique_ptr<Json::CharReader> const charReaderUPtr(charReaderBbuilder.newCharReader());

    const char[] jsonCString = strcpy(jsonString.c_str());

    Json::Value topLevelJSONObject(Json::objectValue);
    std::string errorString;
    reader->parse(jsonCString, jsonCString + jsonString.size(), &topLevelJSONObject, &errorString);

    int objectHandle = topLevelJSONObject["object_handle"].asInt();
    SP objectRootSP = get_object_handle_instance_map().get(objectHandle, SP(static_cast<ObjectRoot>(0)));
    if (!objectRootSP) {
//        logger.error(
//                "ObjectRoot:  fromJson:  no registered object exists with recieved object-handle ({})",
//                objectHandle
//        );
        return;
    }

    ClassAndPropertyNameValueSPMap &classAndPropertyNameValueSPMap(
      interactionRootSP->_classAndPropertyNameValueSPMap
    );
    const Json::Value &propertyJSONObject(topLevelJSONObject["properties"]);
    ClassAndPropertyNameSet &subscribedAttributeNameSet = *objectRootSP->getSubscribedAttributeNameSetSP();

    Json::Value::Members members(propertyJSONObject.getMemberNames());
    for(Json::Value::Members::const_iterator mbrCit = members.begin() ; mbrCit != members.end() ; ++mbrCit) {
        const std::string memberName(*mbrCit);
        ClassAndPropertyName classAndPropertyName(memberName);

        if (subscribedAttributeNameSet.find(classAndPropertyName) == subscribedAttributeNameSet.end()) {
            // LOG ERROR
            continue;
        }

        switch(_classAndPropertyNameValueSPMap[classAndPropertyName].getDataType()) {
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
}


  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"