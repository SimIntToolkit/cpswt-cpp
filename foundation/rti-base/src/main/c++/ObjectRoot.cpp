
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

bool ObjectRoot::static_init_var = ObjectRoot::static_init();

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
            BOOST_LOG_SEV(get_logger(), error) << getCppClassName()
              << ": could not register object:  object class not defined";
            return;
        } catch ( RTI::ObjectClassNotPublished & ) {
            BOOST_LOG_SEV(get_logger(), error) << getCppClassName()
              << ": could not register object:  object class not published";
            return;
        } catch ( RTI::FederateNotExecutionMember & ) {
            BOOST_LOG_SEV(get_logger(), error) << getCppClassName()
              << ": could not register object:  federate not execution member";
            return;
        } catch ( ... ) {
            BOOST_LOG_SEV(get_logger(), error) << getCppClassName()
              << ": could not register object:  unspecified exception caught ... retry";
        }
    }

}

void ObjectRoot::registerObject( RTI::RTIambassador *rti, const std::string &name ) {
    while( !_isRegistered ) {
        try {
            _objectHandle = rti->registerObjectInstance( getClassHandle(), name.c_str() );
            _isRegistered = true;
        } catch ( RTI::ObjectClassNotDefined & ) {
            BOOST_LOG_SEV(get_logger(), error) << getCppClassName()
              << ": could not register object:  object class not defined";
            return;
        } catch ( RTI::ObjectClassNotPublished & ) {
            BOOST_LOG_SEV(get_logger(), error) << getCppClassName()
              << ": could not register object:  object class not published";
            return;
        } catch ( RTI::FederateNotExecutionMember & ) {
            BOOST_LOG_SEV(get_logger(), error) << getCppClassName()
              << ": could not register object:  federate not execution member";
            return;
        } catch ( RTI::ObjectAlreadyRegistered & ) {
            BOOST_LOG_SEV(get_logger(), warning) << getCppClassName()
              << ": could not register object:  object with name \"" << name << "\" already registered";
            return;
        } catch ( ... ) {
            BOOST_LOG_SEV(get_logger(), error) << getCppClassName()
              << ": could not register object:  unspecified exception caught ... retry";
        }
    }
}

void ObjectRoot::unregisterObject( RTI::RTIambassador *rti ) {

    while( _isRegistered ) {
        try {
            rti->deleteObjectInstance( getObjectHandle(), 0 );
            _isRegistered = false;
        } catch ( RTI::ObjectNotKnown & ) {
            BOOST_LOG_SEV(get_logger(), error) << getCppClassName()
              << ": could not unregister object:  object not known";
            return;
        } catch ( RTI::DeletePrivilegeNotHeld & ) {
            BOOST_LOG_SEV(get_logger(), error) << getCppClassName()
              << ": could not unregister object:  delete privilege not held";
            return;
        } catch ( RTI::FederateNotExecutionMember & ) {
            BOOST_LOG_SEV(get_logger(), error) << getCppClassName()
              << ": could not unregister object:  federate not execution member";
            return;
        } catch ( ... ) {
            BOOST_LOG_SEV(get_logger(), error) << getCppClassName()
              << ": could not unregister object:  unspecified exception caught ... retry";
        }
    }
}

void ObjectRoot::get_class_pub_sub_class_and_property_name_sp(
  const StringClassAndPropertyNameSetSPMap &stringClassAndPropertyNameSetSPMap,
  const std::string &className,
  const std::string &attributeName,
  bool publish,
  bool insert
) {
    StringClassAndPropertyNameSetSPMap::const_iterator samItr =
      stringClassAndPropertyNameSetSPMap.find( className );
    if ( samItr == stringClassAndPropertyNameSetSPMap.end() ) {

        std::string prefix = insert ? "" : "un";
        std::string pubsub = publish ? "publish" : "subscribe";

        BOOST_LOG_SEV(get_logger(), error) << "Could not " << prefix << pubsub
          << " \"" << attributeName << "\" attribute of object class \"" << className
          << "\": class does not exist";

        return;
    }

    ClassAndPropertyNameSP classAndPropertyNameSP = findProperty(className, attributeName);
    if (!classAndPropertyNameSP) {

        std::string prefix = insert ? "" : "un";
        std::string pubsub = publish ? "publish" : "subscribe";

        BOOST_LOG_SEV(get_logger(), error) << "Could not " << prefix << pubsub
          << " \"" << attributeName << "\" attribute of object class \"" << className
          << "\": \"" << attributeName << "\" attribute does not exist in the \""
          << className << "\" class or any of its base classes";

        return;
    }

    if (insert) {
        samItr->second->insert(*classAndPropertyNameSP);
    } else {
        samItr->second->erase(*classAndPropertyNameSP);
    }
}

void ObjectRoot::requestUpdate( RTI::RTIambassador *rti ) {
	bool requestNotSubmitted = true;
	while( requestNotSubmitted ) {
		try {
			rti->requestObjectAttributeValueUpdate( getObjectHandle(), *get_subscribed_attribute_handle_set_sp() );
			requestNotSubmitted = false;
		} catch ( RTI::FederateNotExecutionMember & ) {
            BOOST_LOG_SEV(get_logger(), error) << getCppClassName()
              << ": request for update failed:  federate not execution member";
			return;
		} catch ( RTI::ObjectNotKnown & ) {
            BOOST_LOG_SEV(get_logger(), error) <<  getCppClassName()
              << ": request for update failed:  object not known";
			return;
		} catch ( RTI::AttributeNotDefined & ) {
            BOOST_LOG_SEV(get_logger(), error) <<  getCppClassName()
			  << ": request for update failed:  undefined attribute";
			return;
		} catch ( ... ) {
            BOOST_LOG_SEV(get_logger(), error) <<  getCppClassName()
			  << ": request for update failed:  unspecified exception";
		}
	}
}

const ObjectRoot::Value &ObjectRoot::getAttribute( int propertyHandle ) const {
    static const Value valueDefault(false);
    IntegerClassAndPropertyNameSPMap::const_iterator icmCit =
      get_handle_class_and_property_name_sp_map().find(propertyHandle);
    if (icmCit == get_handle_class_and_property_name_sp_map().end()) {
        BOOST_LOG_SEV(get_logger(), error) << "getAttribute: propertyHandle (" << propertyHandle
          <<") does not exist";
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
            BOOST_LOG_SEV(get_logger(), error) << "setParameters: Exception caught!";
        }
    }
}


bool ObjectRoot::static_init() {
    // ADD THIS CLASS TO THE _classNameSet DEFINED IN ObjectRoot
    get_hla_class_name_set().insert(get_hla_class_name());

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
    BOOST_LOG_SEV(get_logger(), error) << "get_attribute_handle: could not find handle for \""
      << propertyName << "\" attribute of class \"" << className << "\" or its superclasses";
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
            BOOST_LOG_SEV(get_logger(), error) << "could not initialize class handle: federate not execution member";
            return;
        } catch (RTI::NameNotFound e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not initialize class handle: name not found";
            return;
        } catch (...) {
            BOOST_LOG_SEV(get_logger(), error) << "could not initialize class handle: unspecified exception ... retry";
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
            BOOST_LOG_SEV(get_logger(), trace) << "publish_object: adding \"" << cnsCit->getPropertyName()
              << "\" attribute to attribute set";
        } catch (...) {
            BOOST_LOG_SEV(get_logger(), error) << "could not publish \"" << cnsCit->getPropertyName()
              << "\" attribute";
        }
    }

    bool isNotPublished = true;
    while(isNotPublished) {
        try {
            rti->publishObjectClass(get_class_handle(), *get_published_attribute_handle_set_sp());
            isNotPublished = false;
        } catch (RTI::FederateNotExecutionMember e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not publish: federate not execution member";
            return;
        } catch (RTI::ObjectClassNotDefined e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not publish: object class not defined";
            return;
        } catch (...) {
            BOOST_LOG_SEV(get_logger(), error) << "could not publish: unspecified exception ... retry";
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
        }
    }

    BOOST_LOG_SEV(get_logger(), debug) << "publish_object: object published";
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
            BOOST_LOG_SEV(get_logger(), error) << "could not unpublish: federate not execution member";
            return;
        } catch (RTI::ObjectClassNotDefined e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unpublish: object class not defined";
            return;
        } catch (RTI::ObjectClassNotPublished e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unpublish: object class not published";
            return;
        } catch (...) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unpublish: unspecified exception ... retry";
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
        }
    }

    BOOST_LOG_SEV(get_logger(), debug) << "unpublish_object: object unpublished";
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
            BOOST_LOG_SEV(get_logger(), trace) << "subscribe_object: adding \"" << cnsCit->getPropertyName()
              << "\" attribute to attribute set";
        } catch (...) {
            BOOST_LOG_SEV(get_logger(), error) << "could not subscribe to \"" << cnsCit->getPropertyName()
              << "\" attribute";
        }
    }

    bool isNotSubscribed = true;
    while(isNotSubscribed) {
        try {
            rti->subscribeObjectClassAttributes(get_class_handle(), *get_subscribed_attribute_handle_set_sp());
            isNotSubscribed = false;
        } catch (RTI::FederateNotExecutionMember e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not subscribe: federate not execution member";
            return;
        } catch (RTI::ObjectClassNotDefined e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not subscribe: class not defined";
            return;
        } catch (...) {
            BOOST_LOG_SEV(get_logger(), error) << "could not subscribe: unspecified exception ... retry";
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
        }
    }

    BOOST_LOG_SEV(get_logger(), debug) << "subscribe_object: object subscribed";
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
            BOOST_LOG_SEV(get_logger(), error) << "could not unsubscribe: federate not execution member";
            return;
        } catch (RTI::ObjectClassNotDefined e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unsubscribe: class not defined";
            return;
        } catch (RTI::ObjectClassNotSubscribed e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unsubscribe: class not subscribed";
            return;
        } catch (...) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unsubscribe: unspecified exception ... retry";
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
        }
    }

    BOOST_LOG_SEV(get_logger(), debug) << "unsubscribe_object: object unsubscribed";
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
        BOOST_LOG_SEV(get_logger(), error) << "could not update attributes:  object not known";
        return;
    } catch ( RTI::FederateNotExecutionMember & ) {
        BOOST_LOG_SEV(get_logger(), error) << "could not update attributes:  federate not execution member";
        return;
    } catch ( RTI::AttributeNotDefined & ) {
        BOOST_LOG_SEV(get_logger(), error) << "could not update attributes:  attribute not defined";
        return;
    } catch ( RTI::AttributeNotOwned & ) {
        BOOST_LOG_SEV(get_logger(), error) << "could not update attributes:  attribute not owned";
        return;
    } catch ( RTI::ConcurrentAccessAttempted & ) {
        BOOST_LOG_SEV(get_logger(), error) << "could not update attributes:  concurrent access attempted";
        return;
    } catch ( RTI::InvalidFederationTime & ) {
        BOOST_LOG_SEV(get_logger(), error) << "could not update attributes:  invalid federation time";
        return;
    } catch ( ... ) {
        BOOST_LOG_SEV(get_logger(), error) << "could not update attributes:  unspecified exception caught";
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
        BOOST_LOG_SEV(get_logger(), error) << "could not update attributes:  object not known";
        return;
    } catch ( RTI::FederateNotExecutionMember & ) {
        BOOST_LOG_SEV(get_logger(), error) << "could not update attributes:  federate not execution member";
        return;
    } catch ( RTI::AttributeNotDefined & ) {
        BOOST_LOG_SEV(get_logger(), error) << "could not update attributes:  attribute not defined";
        return;
    } catch ( RTI::AttributeNotOwned & ) {
        BOOST_LOG_SEV(get_logger(), error) << "could not update attributes:  attribute not owned";
        return;
    } catch ( RTI::ConcurrentAccessAttempted & ) {
        BOOST_LOG_SEV(get_logger(), error) << "could not update attributes:  concurrent access attempted";
        return;
    } catch ( ... ) {
        BOOST_LOG_SEV(get_logger(), error) << "could not update attributes:  unspecified exception caught";
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
        BOOST_LOG_SEV(get_logger(), error) << "fromJson:  no registered object exists with received object-handle ("
          << objectHandle << ")";
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

std::ostream &operator<<( std::ostream &os, const ::org::cpswt::hla::ObjectRoot &messaging ) {

    typedef ::org::cpswt::hla::ObjectRoot::ClassAndPropertyNameValueSPMap::const_iterator const_iterator;
    const ::org::cpswt::hla::ObjectRoot::ClassAndPropertyNameValueSPMap &classAndPropertyNameValueSPMap =
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