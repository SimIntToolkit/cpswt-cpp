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
#include "ObjectRoot.hpp"


namespace org {
 namespace cpswt {
  namespace hla {

bool ObjectRoot::static_init_var = ObjectRoot::static_init();

void ObjectRoot::init(RTI::RTIambassador *rtiAmbassador) {
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
                classHandle = rtiAmbassador->getObjectClassHandle(hlaClassName.c_str());
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
                    int propertyHandle = rtiAmbassador->getAttributeHandle(
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
                } catch (RTI::ObjectClassNotDefined e) {
                    BOOST_LOG_SEV(get_logger(), error) <<
                      "could not initialize: object class not defined";
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
        //------------------------------------------------------------------------------------------------------
        // FOR OBJECTS, INITIALIZE
        // - _classNamePublishedAttributeHandleSetMap (get_class_name_published_attribute_handle_set_sp_map())
        // - _classNameSubscribedAttributeHandleSetMap (get_class_name_subscribed_attribute_handle_set_sp_map())
        // - _classNamePublishedAttributeNameSetMap (get_class_name_published_attribute_name_set_sp_map())
        // - _classNameSubscribedAttributeNameSetMap (get_class_name_subscribed_attribute_name_set_sp_map())
        //
        // EACH hlaClassName INITIALLY HAS
        // - NO PUBLISHED ATTRIBUTE HANDLES/NAMES
        // - NO SUBSCRIBED ATTRIBUTE HANDLES/NAMES
        //------------------------------------------------------------------------------------------------------
        AttributeHandleSetSP publishedAttributeHandleSetSP(
          RTI::AttributeHandleSetFactory::create( 0 )
        );
        get_class_name_published_attribute_handle_set_sp_map()[hlaClassName] = publishedAttributeHandleSetSP;

        AttributeHandleSetSP subscribedAttributeHandleSetSP(
          RTI::AttributeHandleSetFactory::create( 0 )
        );
        get_class_name_subscribed_attribute_handle_set_sp_map()[hlaClassName] = subscribedAttributeHandleSetSP;

        ClassAndPropertyNameSetSP publishedAttributeNameSetSP(new ClassAndPropertyNameSet());
        get_class_name_published_class_and_property_name_set_sp_map()[hlaClassName] = publishedAttributeNameSetSP;

        ClassAndPropertyNameSetSP subscribedAttributeNameSetSP(new ClassAndPropertyNameSet());
        get_class_name_subscribed_class_and_property_name_set_sp_map()[hlaClassName] = subscribedAttributeNameSetSP;
    }
}

void ObjectRoot::get_class_pub_sub_class_and_property_name_sp(
  const StringClassAndPropertyNameSetSPMap &stringClassAndPropertyNameSetSPMap,
  const std::string &hlaClassName,
  const std::string &attributeName,
  bool publish,
  bool insert
) {
    StringClassAndPropertyNameSetSPMap::const_iterator samItr =
      stringClassAndPropertyNameSetSPMap.find( hlaClassName );
    if ( samItr == stringClassAndPropertyNameSetSPMap.end() ) {

        std::string prefix = insert ? "" : "un";
        std::string pubsub = publish ? "publish" : "subscribe";

        BOOST_LOG_SEV(get_logger(), error) << "Could not " << prefix << pubsub
          << " \"" << attributeName << "\" attribute of object class \"" << hlaClassName
          << "\": class does not exist";

        return;
    }

    ClassAndPropertyNameSP classAndPropertyNameSP = findProperty(hlaClassName, attributeName);
    if (!classAndPropertyNameSP) {

        std::string prefix = insert ? "" : "un";
        std::string pubsub = publish ? "publish" : "subscribe";

        BOOST_LOG_SEV(get_logger(), error) << "Could not " << prefix << pubsub
          << " \"" << attributeName << "\" attribute of object class \"" << hlaClassName
          << "\": \"" << attributeName << "\" attribute does not exist in the \""
          << hlaClassName << "\" class or any of its base classes";

        return;
    }

    if (insert) {
        samItr->second->insert(*classAndPropertyNameSP);
    } else {
        samItr->second->erase(*classAndPropertyNameSP);
    }
}

ClassAndPropertyNameSP ObjectRoot::findProperty(
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
        if (cvmCit->second->shouldBeUpdated(force)) {
            int handle = get_class_and_property_name_handle_map()[cvmCit->first];
            std::string value = cvmCit->second->getStringRepresentation();
            propertyHandleValuePairSet.add(handle, value.c_str(), value.size());
        }
    }

    return propertyHandleValuePairSetSP;
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

void ObjectRoot::publish_object(const std::string &hlaClassName, RTI::RTIambassador *rti) {

    if (get_is_published_aux(hlaClassName, true)) {
        return;
    }

    RTI::AttributeHandleSet &publishedAttributeHandleSet =
      *get_class_name_published_attribute_handle_set_sp_map()[hlaClassName];
    publishedAttributeHandleSet.empty();

    ClassAndPropertyNameSet &publishedAttributeNameSet =
      *get_class_name_published_class_and_property_name_set_sp_map()[hlaClassName];

    for(ClassAndPropertyName key : publishedAttributeNameSet) {
        try {
            publishedAttributeHandleSet.add(get_class_and_property_name_handle_map()[key]);
            BOOST_LOG_SEV(get_logger(), trace) << "publish " << hlaClassName << ":" << key;
        } catch (...) {
            BOOST_LOG_SEV(get_logger(), error) << "could not publish \"" << key << "\" attribute.";
        }
    }

    int classHandle = get_class_name_handle_map()[hlaClassName];
    bool isNotPublished = true;
    while(isNotPublished) {
        try {
            rti->publishObjectClass(classHandle, publishedAttributeHandleSet);
            isNotPublished = false;
        } catch (RTI::FederateNotExecutionMember e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not publish: federate not execution member";
            return;
        } catch (RTI::ObjectClassNotDefined e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not publish: object class not defined";
            return;
        } catch (...) {
            BOOST_LOG_SEV(get_logger(), error) << "could not publish: unspecified exception caught ... retry";
            defaultSleep();
        }
    }

    BOOST_LOG_SEV(get_logger(), debug) << "publish_object: \"" << hlaClassName << "\" object published";

    set_is_published(hlaClassName, true);
}

void ObjectRoot::subscribe_object(const std::string &hlaClassName, RTI::RTIambassador *rti) {

    if (get_is_subscribed_aux(hlaClassName, true)) {
        return;
    }

    RTI::AttributeHandleSet &subscribedAttributeHandleSet =
      *get_class_name_subscribed_attribute_handle_set_sp_map()[hlaClassName];
    subscribedAttributeHandleSet.empty();

    ClassAndPropertyNameSet &subscribedAttributeNameSet =
      *get_class_name_subscribed_class_and_property_name_set_sp_map()[hlaClassName];

    for(ClassAndPropertyName key : subscribedAttributeNameSet) {
        try {
            subscribedAttributeHandleSet.add(get_class_and_property_name_handle_map()[key]);
            BOOST_LOG_SEV(get_logger(), trace) << "subscribe " << hlaClassName << ":" << key;
        } catch (...) {
            BOOST_LOG_SEV(get_logger(), error) << "could not subscribe \"" << key << "\" attribute.";
        }
    }

    int classHandle = get_class_name_handle_map()[hlaClassName];
    bool isNotSubscribed = true;
    while(isNotSubscribed) {
        try {
            rti->subscribeObjectClassAttributes(classHandle, subscribedAttributeHandleSet);
            isNotSubscribed = false;
        } catch (RTI::FederateNotExecutionMember e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not subscribe: federate not execution member";
            return;
        } catch (RTI::ObjectClassNotDefined e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not subscribe: object class not defined";
            return;
        } catch (...) {
            BOOST_LOG_SEV(get_logger(), error) << "could not subscribe: unspecified exception caught ... retry";
            defaultSleep();
        }
    }

    BOOST_LOG_SEV(get_logger(), debug) << "subscribe_object: \"" << hlaClassName << "\" object subscribed";

    set_is_subscribed(hlaClassName, true);
}

void ObjectRoot::unpublish_object(const std::string &hlaClassName, RTI::RTIambassador *rti) {

    if (!get_is_published_aux(hlaClassName, false)) {
        return;
    }

    int classHandle = get_class_name_handle_map()[hlaClassName];

    bool isNotUnpublished = true;
    while(isNotUnpublished) {
        try {
            rti->unpublishObjectClass(classHandle);
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
            BOOST_LOG_SEV(get_logger(), error) << "could not unpublish: unspecified exception caught ... retry";
            defaultSleep();
        }
    }
    BOOST_LOG_SEV(get_logger(), debug) << "unpublish_object: \"" << hlaClassName << "\" object unpublished";

    set_is_published(hlaClassName, false);
}

void ObjectRoot::unsubscribe_object(const std::string &hlaClassName, RTI::RTIambassador *rti) {

    if (!get_is_subscribed_aux(hlaClassName, false)) {
        return;
    }

    int classHandle = get_class_name_handle_map()[hlaClassName];

    bool isNotUnsubscribed = true;
    while(isNotUnsubscribed) {
        try {
            rti->unsubscribeObjectClass(classHandle);
            isNotUnsubscribed = false;
        } catch (RTI::FederateNotExecutionMember e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unsubscribe: federate not execution member";
            return;
        } catch (RTI::ObjectClassNotDefined e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unsubscribe: object class not defined";
            return;
        } catch (RTI::ObjectClassNotSubscribed e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unsubscribe: object class not subscribed";
            return;
        } catch (...) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unsubscribe: unspecified exception caught ... retry";
            defaultSleep();
        }
    }
    BOOST_LOG_SEV(get_logger(), debug) << "unsubscribe_object: \"" << hlaClassName << "\" object unsubscribed";

    set_is_subscribed(hlaClassName, false);
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

void ObjectRoot::requestUpdate( RTI::RTIambassador *rti ) {
	bool requestNotSubmitted = true;
	while( requestNotSubmitted ) {
		try {
			rti->requestObjectAttributeValueUpdate(
			  getObjectHandle(), *get_subscribed_attribute_handle_set_sp( getInstanceHlaClassName() )
			);
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

void ObjectRoot::initializeProperties(const std::string &hlaClassName) {
    setInstanceHlaClassName(hlaClassName);
    if (get_hla_class_name_set().find(hlaClassName) == get_hla_class_name_set().end()) {
        BOOST_LOG_SEV(get_logger(), error)
          << "ObjectRoot( const std::string &hlaClassName ): hlaClassName \"" << hlaClassName
          << "\" is not defined -- creating dummy object with fictitious type \"" << hlaClassName
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
    BOOST_LOG_SEV(get_logger(), info) << "Class \"::org::cpswt::hla::ObjectRoot\" loaded.";

    // ADD THIS CLASS TO THE _classNameSet DEFINED IN ObjectRoot
    get_hla_class_name_set().insert(get_hla_class_name());

    ObjectRoot::NoInstanceInit noInstanceInit;
    SP instanceSP = SP( new ObjectRoot(noInstanceInit) );
    get_hla_class_name_instance_sp_map()[get_hla_class_name()] = instanceSP;

    ClassAndPropertyNameSetSP classAndPropertyNameSetSP( new ClassAndPropertyNameSet() );

    // ADD THIS CLASS'S _classAndPropertyNameSet TO _classNamePropertyNameSetMap DEFINED
    // IN ObjectRoot
    get_class_name_class_and_property_name_set_sp_map()[get_hla_class_name()] = classAndPropertyNameSetSP;

    ClassAndPropertyNameSetSP allClassAndPropertyNameSetSP( new ClassAndPropertyNameSet() );// ADD THIS CLASS'S _allClassAndPropertyNameSet TO _classNameAllPropertyNameSetMap DEFINED
    // IN ObjectRoot
    get_class_name_all_class_and_property_name_set_sp_map()[get_hla_class_name()] = allClassAndPropertyNameSetSP;

    return true;
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

void ObjectRoot::readFederateDynamicMessageClasses(std::istream &dynamicMessagingTypesInputStream) {

    Json::Value dynamicMessageTypes;
    dynamicMessagingTypesInputStream >> dynamicMessageTypes;

    Json::Value federationMessaging = get_federation_json()["objects"];

    std::unordered_set< std::string > localHlaClassNameSet;

    Json::Value dynamicHlaClassNames = dynamicMessageTypes["objects"];
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
                const std::string propertyTypeString = typeDataMap["AttributeType"].asString();
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

std::ostream &operator<<( std::ostream &os, const ::org::cpswt::hla::ObjectRoot &messaging ) {

    typedef ::org::cpswt::hla::ObjectRoot::ClassAndPropertyNameValueSPMap::const_iterator const_iterator;
    const ::org::cpswt::hla::ObjectRoot::ClassAndPropertyNameValueSPMap &classAndPropertyNameValueSPMap =
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
