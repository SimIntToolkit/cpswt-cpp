
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
#include "ObjectRoot.hpp"



namespace org {
 namespace cpswt {
  namespace hla {

std::string ObjectRoot::join(const std::list<std::string> &joinList, const std::string &delimiter) {
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


ClassAndPropertyNameSP ObjectRoot::findProperty(const std::string &className, const std::string &propertyName) {

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
}ObjectRoot::SP ObjectRoot::create_object( int classHandle, const RTI::AttributeHandleValuePairSet &propertyMap ) {
	IntegerStringMap::iterator ismItr = get_class_handle_name_map().find( classHandle );
	if ( ismItr == get_class_handle_name_map().end() ) {
		return SP();
	}

	StringInstanceSPMap::iterator simItr = get_class_name_instance_sp_map().find( ismItr->second );
	if ( simItr == get_class_name_instance_sp_map().end() ) {
		return SP();
	}

	SP sp = simItr->second->createObject();
	sp->setAttributes( propertyMap );

	return sp;
}

ObjectRoot::SP ObjectRoot::create_object( int classHandle, const RTI::AttributeHandleValuePairSet &propertyMap, const RTIfedTime &rtiFedTime ) {
	IntegerStringMap::iterator ismItr = get_class_handle_name_map().find( classHandle );
	if ( ismItr == get_class_handle_name_map().end() ) {
		return SP();
	}

	StringInstanceSPMap::iterator simItr = get_class_name_instance_sp_map().find( ismItr->second );
	if ( simItr == get_class_name_instance_sp_map().end() ) {
		return SP();
	}

	SP sp = simItr->second->createObject(rtiFedTime);
	sp->setAttributes( propertyMap );
	sp->setTime( rtiFedTime.getTime() );

	return sp;
}

void ObjectRoot::registerObject( RTI::RTIambassador *rti ) {

    while( !_isRegistered ) {
        try {
            _objectHandle = rti->registerObjectInstance( getClassHandle() );
            _isRegistered = true;
        } catch ( RTI::ObjectClassNotDefined & ) {
            std::cerr << "ERROR:  ObjectRoot::registerObject:  Object Class Not Defined" << std::endl;
            return;
        } catch ( RTI::ObjectClassNotPublished & ) {
            std::cerr << "ERROR:  ObjectRoot::registerObject:  Object Class Not Published" << std::endl;
            return;
        } catch ( RTI::FederateNotExecutionMember & ) {
            std::cerr << "ERROR:  ObjectRoot::registerObject:  Federate Not Execution Member" << std::endl;
            return;
        } catch ( ... ) {
            std::cerr << "ObjectRoot::registerObject:  Exception caught ... retry" << std::endl;
        }
    }

}

void ObjectRoot::registerObject( RTI::RTIambassador *rti, const std::string &name ) {
    while( !_isRegistered ) {
        try {
            _objectHandle = rti->registerObjectInstance( getClassHandle(), name.c_str() );
            _isRegistered = true;
        } catch ( RTI::ObjectClassNotDefined & ) {
            std::cerr << "ERROR:  ObjectRoot::registerObject:  Object Class Not Defined" << std::endl;
            return;
        } catch ( RTI::ObjectClassNotPublished & ) {
            std::cerr << "ERROR:  ObjectRoot::registerObject:  Object Class Not Published" << std::endl;
            return;
        } catch ( RTI::FederateNotExecutionMember & ) {
            std::cerr << "ERROR:  ObjectRoot::registerObject:  Federate Not Execution Member" << std::endl;
            return;
        } catch ( RTI::ObjectAlreadyRegistered & ) {
            throw;
        } catch ( ... ) {
            std::cerr << "ObjectRoot::registerObject:  Exception caught ... retry" << std::endl;
        }
    }
}

void ObjectRoot::unregisterObject( RTI::RTIambassador *rti ) {

    while( _isRegistered ) {
        try {
            rti->deleteObjectInstance( getObjectHandle(), 0 );
            _isRegistered = false;
        } catch ( RTI::ObjectNotKnown & ) {
            std::cerr << "ERROR:  ObjectRoot::unregisterObject:  Object Not Known" << std::endl;
            return;
        } catch ( RTI::DeletePrivilegeNotHeld & ) {
            std::cerr << "ERROR:  ObjectRoot::unregisterObject:  Delete Privilege Not Held" << std::endl;
            return;
        } catch ( RTI::FederateNotExecutionMember & ) {
            std::cerr << "ERROR:  ObjectRoot::unregisterObject:  Federate Not Execution Member" << std::endl;
            return;
        } catch ( ... ) {
            std::cerr << "ObjectRoot::unregisterObject:  Exception caught ... retry" << std::endl;
        }
    }
}

void ObjectRoot::requestUpdate( RTI::RTIambassador *rti ) {
	bool requestNotSubmitted = true;
	while( requestNotSubmitted ) {
		try {
			rti->requestObjectAttributeValueUpdate( getObjectHandle(), *get_subscribed_attribute_handle_set_sp() );
			requestNotSubmitted = false;
		} catch ( RTI::FederateNotExecutionMember & ) {
			std::cerr << "ERROR: " << getCppClassName() << "request for update failed:  Federate Not Execution Member" << std::endl;
			return;
		} catch ( RTI::ObjectNotKnown & ) {
			std::cerr << "ERROR: " << getCppClassName() << "request for update failed:  Object Not Known" << std::endl;
			return;
		} catch ( RTI::AttributeNotDefined & ) {
			std::cerr << "ERROR: " << getCppClassName() << "request for update failed:  Name Not Found" << std::endl;
			return;
		} catch ( ... ) {
			std::cerr << "ERROR: " << getCppClassName() << "request for update failed:  Unknown Exception" << std::endl;			}
	}
}

const ObjectRoot::Value &ObjectRoot::getAttribute( int propertyHandle ) const {
    static const Value valueDefault(false);
    IntegerClassAndPropertyNameSPMap::const_iterator icmCit =
      get_handle_class_and_property_name_sp_map().find(propertyHandle);
    if (icmCit == get_handle_class_and_property_name_sp_map().end()) {
//        logger.error("getAttribute: propertyHandle {} does not exist.", propertyHandle);
        return valueDefault;
    }

    const ValueSP valueSP = _classAndPropertyNameValueSPMap.find(*icmCit->second)->second;
    return *valueSP;
}

void ObjectRoot::setAttributes( const RTI::AttributeHandleValuePairSet &propertyMap ) {

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


bool ObjectRoot::static_init() {
    // ADD THIS CLASS TO THE _classNameSet DEFINED IN ObjectRoot
    get_class_name_set().insert(get_hla_class_name());

    // ADD CLASS OBJECT OF THIS CLASS TO _classNameClassMap DEFINED IN ObjectRoot
    get_class_name_instance_sp_map()[get_hla_class_name()] = SP(new ObjectRoot());

    // ADD THIS CLASS'S _classAndPropertyNameSet TO _classNamePropertyNameSetMap DEFINED
    // IN ObjectRoot
    get_class_name_class_and_property_name_set_sp_map()[get_hla_class_name()] = get_class_and_property_name_set_sp();

    // ADD THIS CLASS'S _allClassAndPropertyNameSet TO _classNameAllPropertyNameSetMap DEFINED
    // IN ObjectRoot
    get_class_name_all_class_and_property_name_set_sp_map()[get_hla_class_name()] =
      get_all_class_and_property_name_set_sp();

    get_class_name_published_attribute_name_set_sp_map()[get_hla_class_name()] =
      get_published_class_and_property_name_set_sp();
    get_class_name_published_attribute_name_set_sp_map()[get_hla_class_name()] =
      get_subscribed_class_and_property_name_set_sp();

    get_class_name_published_attribute_handle_set_sp_map()[get_hla_class_name()] =
      get_published_attribute_handle_set_sp();

    get_class_name_subscribed_attribute_handle_set_sp_map()[get_hla_class_name()] =
      get_subscribed_attribute_handle_set_sp();

    return true;
}


int ObjectRoot::get_attribute_handle_aux(const std::string &className, const std::string &propertyName) {
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


void ObjectRoot::init(RTI::RTIambassador *rti) {
    if (get_is_initialized()) return;
    get_is_initialized() = true;

    bool isNotInitialized = true;
    while(isNotInitialized) {
        try {
            get_class_handle() = rti->getObjectClassHandle(get_hla_class_name().c_str());
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


void ObjectRoot::publish_object(RTI::RTIambassador *rti) {
    if (get_is_published()) {
        return;
    }
    get_is_published() = true;

    init(rti);

    get_published_attribute_handle_set_sp()->empty();
    for(
      ClassAndPropertyNameSet::const_iterator cnsCit = get_published_class_and_property_name_set_sp()->begin() ;
      cnsCit != get_published_class_and_property_name_set_sp()->end() ;
      ++cnsCit
    ) {
        try {
            get_published_attribute_handle_set_sp()->add(get_class_and_property_name_handle_map()[*cnsCit]);
//            logger.trace("publish {}:{}", get_hla_class_name(), key.toString());
        } catch (...) {
//            logger.error("could not publish \"" + key.toString() + "\" attribute.", e);
        }
    }

    bool isNotPublished = true;
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
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
        }
    }

//    logger.debug("publish: {}", get_hla_class_name());
}


void ObjectRoot::unpublish_object(RTI::RTIambassador *rti) {
    if (!get_is_published()) return;
    get_is_published() = false;

    init(rti);

    bool isNotUnpublished = true;
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
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
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

    get_subscribed_attribute_handle_set_sp()->empty();
    for(
      ClassAndPropertyNameSet::const_iterator cnsCit = get_subscribed_class_and_property_name_set_sp()->begin() ;
      cnsCit != get_subscribed_class_and_property_name_set_sp()->end() ;
      ++cnsCit
    ) {
        try {
            get_subscribed_attribute_handle_set_sp()->add(get_class_and_property_name_handle_map()[*cnsCit]);
//            logger.trace("subscribe {}:{}", get_hla_class_name(), key.toString());
        } catch (...) {
//            logger.error("could not subscribe to \"" + key + "\" attribute.", e);
        }
    }

    bool isNotSubscribed = true;
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
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
        }
    }

//    logger.debug("subscribe: {}", get_hla_class_name());
}


void ObjectRoot::unsubscribe_object(RTI::RTIambassador *rti) {
    if (!get_is_subscribed()) return;
    get_is_subscribed() = false;

    init(rti);

    bool isNotUnsubscribed = true;
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


ObjectRoot::PropertyClassNameAndValueSP ObjectRoot::getAttributeAux(
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

ObjectRoot::PropertyHandleValuePairSetSP ObjectRoot::createPropertyHandleValuePairSetSP( bool force ) {

    int count;
    if (force) {
        count = _classAndPropertyNameValueSPMap.size();
    } else {
        count = 0;
        for(
          ClassAndPropertyNameValueSPMap::const_iterator cvmCit = _classAndPropertyNameValueSPMap.begin();
          cvmCit != _classAndPropertyNameValueSPMap.end();
          ++cvmCit
        ) {
            if (cvmCit->second->shouldBeUpdated(false)) {
                ++count;
            }
        }
    }

    PropertyHandleValuePairSetSP propertyHandleValuePairSetSP(  RTI::AttributeSetFactory::create( count )  );
    PropertyHandleValuePairSet &propertyHandleValuePairSet = *propertyHandleValuePairSetSP;

    for(
      ClassAndPropertyNameValueSPMap::const_iterator cvmCit = _classAndPropertyNameValueSPMap.begin();
      cvmCit != _classAndPropertyNameValueSPMap.end();
      ++cvmCit
    ) {
        int handle = get_class_and_property_name_handle_map()[cvmCit->first];
        std::string value = static_cast<std::string>(*cvmCit->second);
        propertyHandleValuePairSet.add(handle, value.c_str(), value.size() + 1);
    }

    return propertyHandleValuePairSetSP;
}

void ObjectRoot::updateAttributeValues( RTI::RTIambassador *rti, double time, bool force ) {
    PropertyHandleValuePairSetSP propertyHandleValuePairSetSP = createPropertyHandleValuePairSetSP( force );
    if ( propertyHandleValuePairSetSP->size() == 0 ) {
        return;
    }
    try {
        rti->updateAttributeValues(  getObjectHandle(), *propertyHandleValuePairSetSP, RTIfedTime( time ), 0  );
//        createLog( time, true );
    } catch ( RTI::ObjectNotKnown & ) {
        std::cerr << "ERROR:  " << getCppClassName() << ":  could not update attributes:  Object Not Known" << std::endl;
        return;
    } catch ( RTI::FederateNotExecutionMember & ) {
        std::cerr << "ERROR:  " << getCppClassName() << ":  could not update attributes:  Federate Not Execution Member" << std::endl;
        return;
    } catch ( RTI::AttributeNotDefined & ) {
        std::cerr << "ERROR:  " << getCppClassName() << ":  could not update attributes:  Attribute Not Defined" << std::endl;
        return;
    } catch ( RTI::AttributeNotOwned & ) {
        std::cerr << "ERROR:  " << getCppClassName() << ":  could not update attributes:  Attribute Not Owned" << std::endl;
        return;
    } catch ( RTI::ConcurrentAccessAttempted & ) {
        std::cerr << "ERROR:  " << getCppClassName() << ":  could not update attributes:  Concurrent Access Attempted" << std::endl;
        return;
    } catch ( RTI::InvalidFederationTime & ) {
        std::cerr << "ERROR:  " << getCppClassName() << ":  could not update attributes:  Invalid Federation Time" << std::endl;
        return;
    } catch ( ... ) {
        std::cerr << "ERROR:  " << getCppClassName() << ":  could not update attributes:  exception caught" << std::endl;
    }
}

void ObjectRoot::updateAttributeValues( RTI::RTIambassador *rti, bool force ) {
    PropertyHandleValuePairSetSP propertyHandleValuePairSetSP = createPropertyHandleValuePairSetSP( force );
    if ( propertyHandleValuePairSetSP->size() == 0 ) {
        return;
    }
    try {
        rti->updateAttributeValues( getObjectHandle(), *propertyHandleValuePairSetSP, 0 );
//        createLog( 0, true );
    } catch ( RTI::ObjectNotKnown & ) {
        std::cerr << "ERROR:  " << getCppClassName() << ":  could not update attributes:  Object Not Known" << std::endl;
        return;
    } catch ( RTI::FederateNotExecutionMember & ) {
        std::cerr << "ERROR:  " << getCppClassName() << ":  could not update attributes:  Federate Not Execution Member" << std::endl;
        return;
    } catch ( RTI::AttributeNotDefined & ) {
        std::cerr << "ERROR:  " << getCppClassName() << ":  could not update attributes:  Attribute Not Defined" << std::endl;
        return;
    } catch ( RTI::AttributeNotOwned & ) {
        std::cerr << "ERROR:  " << getCppClassName() << ":  could not update attributes:  Attribute Not Owned" << std::endl;
        return;
    } catch ( RTI::ConcurrentAccessAttempted & ) {
        std::cerr << "ERROR:  " << getCppClassName() << ":  could not update attributes:  Concurrent Access Attempted" << std::endl;
        return;
    } catch ( RTI::InvalidFederationTime & ) {
        std::cerr << "ERROR:  " << getCppClassName() << ":  could not update attributes:  Invalid Federation Time" << std::endl;
        return;
    } catch ( ... ) {
        std::cerr << "ERROR:  " << getCppClassName() << ":  could not update attributes:  exception caught" << std::endl;
    }
}

std::string ObjectRoot::toJson() {
    Json::Value topLevelJSONObject(Json::objectValue);
    topLevelJSONObject["messaging_type"] = "interaction";
    topLevelJSONObject["object_handle"] = getObjectHandle();

    Json::Value propertyJSONObject(Json::objectValue);
    topLevelJSONObject["properties"] = propertyJSONObject;
    for(
      ClassAndPropertyNameValueSPMap::iterator cvmItr = _classAndPropertyNameValueSPMap.begin() ;
      cvmItr != _classAndPropertyNameValueSPMap.end() ;
      ++cvmItr
    ) {
        const std::string key(cvmItr->first);
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

void ObjectRoot::fromJson(const std::string &jsonString) {
    std::istringstream jsonInputStream(jsonString);

    Json::Value topLevelJSONObject;
    jsonInputStream >> topLevelJSONObject;

    int objectHandle = topLevelJSONObject["object_handle"].asInt();
    ObjectHandleInstanceSPMap::iterator oimItr = get_object_handle_instance_sp_map().find(objectHandle);
    if (oimItr != get_object_handle_instance_sp_map().end()) {
//        logger.error(
//                "ObjectRoot:  fromJson:  no registered object exists with recieved object-handle ({})",
//                objectHandle
//        );
        return;
    }

    SP objectRootSP = oimItr->second;
    ClassAndPropertyNameValueSPMap &classAndPropertyNameValueSPMap(
      objectRootSP->_classAndPropertyNameValueSPMap
    );
    const Json::Value &propertyJSONObject(topLevelJSONObject["properties"]);
    ClassAndPropertyNameSet &subscribedAttributeNameSet = *objectRootSP->getSubscribedClassAndPropertyNameSetSP();

    Json::Value::Members members(propertyJSONObject.getMemberNames());
    for(Json::Value::Members::const_iterator mbrCit = members.begin() ; mbrCit != members.end() ; ++mbrCit) {
        const std::string memberName(*mbrCit);
        ClassAndPropertyName classAndPropertyName(memberName);

        if (subscribedAttributeNameSet.find(classAndPropertyName) == subscribedAttributeNameSet.end()) {
            // LOG ERROR
            continue;
        }

        switch(classAndPropertyNameValueSPMap[classAndPropertyName]->getDataType()) {
            case TypeMedley::BOOLEAN:
                (*classAndPropertyNameValueSPMap[classAndPropertyName]).setValue(
                  propertyJSONObject[memberName].asBool()
                );
                break;
            case TypeMedley::CHARACTER:
                (*classAndPropertyNameValueSPMap[classAndPropertyName]).setValue(
                  static_cast<char>(propertyJSONObject[memberName].asInt())
                );
                break;
            case TypeMedley::SHORT:
                (*classAndPropertyNameValueSPMap[classAndPropertyName]).setValue(
                  static_cast<short>(propertyJSONObject[memberName].asInt())
                );
                break;
            case TypeMedley::INTEGER:
                (*classAndPropertyNameValueSPMap[classAndPropertyName]).setValue(
                  propertyJSONObject[memberName].asInt()
                );
                break;
            case TypeMedley::LONG:
                (*classAndPropertyNameValueSPMap[classAndPropertyName]).setValue(
                  static_cast<long>(propertyJSONObject[memberName].asInt64())
                );
                break;
            case TypeMedley::STRING:
                (*classAndPropertyNameValueSPMap[classAndPropertyName]).setValue(
                  propertyJSONObject[memberName].asString()
                );
                break;
        }
    }
}


  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"