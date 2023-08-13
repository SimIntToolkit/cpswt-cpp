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


namespace edu {
 namespace vanderbilt {
  namespace vuisis {
   namespace cpswt {
    namespace hla {

bool ObjectRoot::static_init_var = ObjectRoot::static_init();

void ObjectRoot::init(const std::string &hlaClassName, RTI::RTIambassador *rtiAmbassador) {

    std::list<std::string> hlaClassNameComponents;
    boost::algorithm::split(hlaClassNameComponents, hlaClassName, boost::is_any_of("."));
    while(!hlaClassNameComponents.empty()) {
        const std::string localHlaClassName( boost::algorithm::join(hlaClassNameComponents, ".") );
        hlaClassNameComponents.pop_back();

        if (get_hla_class_name_is_initialized(localHlaClassName)) {
            continue;
        }
        set_hla_class_name_is_initialized(localHlaClassName);

        if (get_hla_class_name_instance_sp_map().find(localHlaClassName) == get_hla_class_name_instance_sp_map().end()) {
            get_dynamic_hla_class_name_set_aux().insert(localHlaClassName);
        }

        //----------------------------------------------------
        // GET HANDLE FOR localHlaClassName TO INITIALIZE
        // - _classNameHandleMap (get_class_name_handle_map())
        // - _classHandleNameMap (get_class_handle_name_map())
        //----------------------------------------------------
        bool isNotInitialized = true;
        int classHandle = 0;
        while(isNotInitialized) {
            try {
                classHandle = rtiAmbassador->getObjectClassHandle(localHlaClassName.c_str());
                get_class_name_handle_map()[localHlaClassName] = classHandle;
                get_class_handle_name_map()[classHandle] = localHlaClassName;
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
        // MAPS localHlaClassName TO THE PROPERTIES (PARAMETERS OR ATTRIBUTES)
        // DEFINED *DIRECTLY* IN THE localHlaClassName CLASS
        //
        // GET HANDLE FOR THESE PROPERTIES TO INITIALIZE
        // - _classAndPropertyNameHandleMap (get_class_and_property_name_handle_map())
        // - _handleClassAndPropertyNameMap (get_handle_class_and_property_name_sp_map())
        //------------------------------------------------------------------------------------
        ClassAndPropertyNameSet &classAndPropertyNameSet =
          *get_class_name_class_and_property_name_set_sp_map()[localHlaClassName];
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

        //------------------------------------------------------------------------------------------------------
        // FOR OBJECTS, INITIALIZE
        // - _classNamePublishedAttributeHandleSetMap (get_class_name_published_attribute_handle_set_sp_map())
        // - _classNameSubscribedAttributeHandleSetMap (get_class_name_subscribed_attribute_handle_set_sp_map())
        //------------------------------------------------------------------------------------------------------
        AttributeHandleSetSP publishedAttributeHandleSetSP(
          RTI::AttributeHandleSetFactory::create( 0 )
        );
        get_class_name_published_attribute_handle_set_sp_map()[localHlaClassName] = publishedAttributeHandleSetSP;

        AttributeHandleSetSP subscribedAttributeHandleSetSP(
          RTI::AttributeHandleSetFactory::create( 0 )
        );
        get_class_name_subscribed_attribute_handle_set_sp_map()[localHlaClassName] = subscribedAttributeHandleSetSP;
    }
}

void ObjectRoot::common_init(const std::string &hlaClassName) {

    //-------------------------------------------------------
    // INITIALIZE ALL CLASSES TO NOT-PUBLISHED NOT-SUBSCRIBED
    //-------------------------------------------------------
    get_class_name_publish_status_map()[hlaClassName] = false;
    get_class_name_subscribe_status_map()[hlaClassName] = false;
    get_class_name_soft_subscribe_status_map()[hlaClassName] = false;

    //------------------------------------------------------------------------------------------------------
    // FOR OBJECTS, INITIALIZE
    // - _classNamePublishedAttributeNameSetMap (get_class_name_published_attribute_name_set_sp_map())
    // - _classNameSubscribedAttributeNameSetMap (get_class_name_subscribed_attribute_name_set_sp_map())
    // - _classNameSoftSubscribedAttributeNameSetMap (get_class_name_soft_subscribed_attribute_name_set_sp_map())
    //
    // EACH hlaClassName INITIALLY HAS
    // - NO PUBLISHED ATTRIBUTE HANDLES/NAMES
    // - NO SUBSCRIBED ATTRIBUTE HANDLES/NAMES
    //------------------------------------------------------------------------------------------------------
    ClassAndPropertyNameSetSP publishedAttributeNameSetSP(new ClassAndPropertyNameSet());
    get_class_name_published_class_and_property_name_set_sp_map()[hlaClassName] = publishedAttributeNameSetSP;

    ClassAndPropertyNameSetSP subscribedAttributeNameSetSP(new ClassAndPropertyNameSet());
    get_class_name_subscribed_class_and_property_name_set_sp_map()[hlaClassName] = subscribedAttributeNameSetSP;

    ClassAndPropertyNameSetSP softSubscribedAttributeNameSetSP(new ClassAndPropertyNameSet());
    get_class_name_soft_subscribed_class_and_property_name_set_sp_map()[hlaClassName] =
      softSubscribedAttributeNameSetSP;
}

ObjectRoot::ClassAndPropertyNameValueSPMap ObjectRoot::getClassAndPropertyNameValueSPMap(
  const RTI::AttributeHandleValuePairSet &propertyMap
) {
    ClassAndPropertyNameValueSPMap classAndPropertyNameValueSPMap;

    RTI::ULong valueLength;

    int size = propertyMap.size();
    for( int ix = 0 ; ix < size ; ++ix ) {
        try {
            int handle = propertyMap.getHandle(ix);
            char *value = propertyMap.getValuePointer( ix, valueLength );
            ClassAndPropertyNameSP classAndPropertyNameSP =
              get_handle_class_and_property_name_sp_map()[ propertyMap.getHandle( ix ) ];
            ValueSP initialValueSP = get_class_and_property_name_initial_value_sp_map()[*classAndPropertyNameSP];
            ValueSP newValueSP = ValueSP(new Value(*initialValueSP));
            newValueSP->setValue(std::string(value, valueLength));
            classAndPropertyNameValueSPMap[*classAndPropertyNameSP] = newValueSP;
        } catch (...) {
            BOOST_LOG_SEV(get_logger(), error) << "getClassAndPropertyNameValueSPMap: Exception caught!";
        }
    }
    return classAndPropertyNameValueSPMap;
}

std::string ObjectRoot::ObjectReflector::toJson() const {
    Json::Value topLevelJSONObject(Json::objectValue);
    topLevelJSONObject["messaging_type"] = "object";
    topLevelJSONObject["messaging_name"] = _hlaClassName;
    topLevelJSONObject["object_handle"] = static_cast<Json::Value::UInt64>(_objectHandle);
    topLevelJSONObject["federateSequence"] = _federateSequence;


    Json::Value propertyJSONObject(Json::objectValue);
    for(
      ClassAndPropertyNameValueSPMap::const_iterator cvmCit = _classAndPropertyNameValueSPMap.begin() ;
      cvmCit != _classAndPropertyNameValueSPMap.end() ;
      ++cvmCit
    ) {
        const std::string key(cvmCit->first);
        TypeMedley &value = *cvmCit->second;
        switch(value.getDataType()) {
            case TypeMedley::BOOLEAN:
                propertyJSONObject[key] = static_cast<bool>(value);
                break;
            case TypeMedley::CHARACTER:
                propertyJSONObject[key] = static_cast<char>(value);
                break;
            case TypeMedley::SHORT:
                propertyJSONObject[key] = static_cast<short>(value);
                break;
            case TypeMedley::INTEGER:
                propertyJSONObject[key] = static_cast<int>(value);
                break;
            case TypeMedley::LONG:
                propertyJSONObject[key] = static_cast<Json::Value::Int64>(static_cast<long>(value));
                break;
            case TypeMedley::FLOAT:
                propertyJSONObject[key] = static_cast<float>(value);
                break;
            case TypeMedley::DOUBLE:
                propertyJSONObject[key] = static_cast<double>(value);
                break;
            case TypeMedley::STRING:
                propertyJSONObject[key] = static_cast<std::string>(value);
                break;
            case TypeMedley::JSON:
                propertyJSONObject[key] = static_cast<Json::Value>(value);
                break;
        }
    }
    topLevelJSONObject["properties"] = propertyJSONObject;

    Json::StreamWriterBuilder streamWriterBuilder;
    streamWriterBuilder["commandStyle"] = "None";
    streamWriterBuilder["indentation"] = "    ";
    std::unique_ptr<Json::StreamWriter> streamWriterUPtr(streamWriterBuilder.newStreamWriter());
    std::ostringstream stringOutputStream;
    streamWriterUPtr->write(topLevelJSONObject, &stringOutputStream);
    return stringOutputStream.str();
}

ObjectRoot::ObjectReflector::operator std::string() const {
    std::ostringstream stringOutputStream;

    const ClassAndPropertyNameValueSPMap &classAndPropertyNameValueSPMap = getClassAndPropertyNameValueSPMap();
    stringOutputStream << "[" << getHlaClassName() << "," << getObjectHandle() << "," << ""
      << getFederateSequence() << "](";

    bool first = true;
    for(
      ClassAndPropertyNameValueSPMap::const_iterator cvmCit = classAndPropertyNameValueSPMap.begin() ;
      cvmCit != classAndPropertyNameValueSPMap.end() ;
      ++cvmCit
    ) {
        if (first) first = false;
        else stringOutputStream << ", " ;

        stringOutputStream << static_cast<std::string>(cvmCit->first) << ": ";
        TypeMedley &value = *cvmCit->second;
        switch(value.getDataType()) {
            case TypeMedley::DOUBLE: {
                stringOutputStream << static_cast<double>(value);
                break;
            }
            case TypeMedley::FLOAT: {
                stringOutputStream << static_cast<float>(value);
                break;
            }
            case TypeMedley::STRING: {
                stringOutputStream << "\"" << static_cast<std::string>(value) << "\"";
                break;
            }
            default: {
                stringOutputStream << static_cast<std::string>(value);
                break;
            }
        }
    }
    stringOutputStream << ")";

    return stringOutputStream.str();
}

void ObjectRoot::pub_sub_class_and_property_name(
  const std::string &callingFunctionName,
  StringClassAndPropertyNameSetSPMap &stringClassAndPropertyNameSetSPMap,
  const std::string &hlaClassName,
  const std::string &attributeClassName,
  const std::string &attributeName,
  bool publish,
  bool insert
) {
    if (get_hla_class_name_set().find(hlaClassName) == get_hla_class_name_set().end()) {
        readFederateDynamicMessageClass(hlaClassName);
    }

    std::string basePrefix = attributeClassName + ".";

    StringClassAndPropertyNameSetSPMap::const_iterator samItr =
      stringClassAndPropertyNameSetSPMap.find( hlaClassName );
    if ( samItr == stringClassAndPropertyNameSetSPMap.end() ) {
        BOOST_LOG_SEV(get_logger(), error) << callingFunctionName << "(\"" << hlaClassName << "\", \"" <<
          attributeClassName << "\", \"" << attributeName << "\"): \"" << hlaClassName << "\" has no attributes";

        return;
    }

    if (
      hlaClassName != attributeClassName &&
      (hlaClassName.size() < attributeClassName.size() || hlaClassName.substr(0, basePrefix.length()) != basePrefix)
    ) {
        BOOST_LOG_SEV(get_logger(), error) << callingFunctionName << "( \""
          << hlaClassName << "\", \"" << attributeClassName << "\", \"" << attributeName
          << "\"): the \"" << hlaClassName << "\" class cannot access an attribute of class \""
          << attributeClassName << "\" because it is out of its inheritance hierarchy.";
        return;
    }

    ClassAndPropertyNameSP classAndPropertyNameSP = findProperty(attributeClassName, attributeName);
    if (!classAndPropertyNameSP) {

        BOOST_LOG_SEV(get_logger(), error) << callingFunctionName << "( \""
          << hlaClassName << "\", \"" << attributeClassName << "\", \"" << attributeName
          << "\"):  \"" << attributeName << "\" attribute does not exist in \"" << attributeClassName
          << "\" class or any of its base classes";

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
        if (get_complete_class_and_property_name_set().find(key) != get_complete_class_and_property_name_set().end()) {
            return ClassAndPropertyNameSP(new ClassAndPropertyName(key));
        }

        classNameComponents.pop_back();
    }

    return ClassAndPropertyNameSP();
}

ObjectRoot::PropertyHandleValuePairSetSP ObjectRoot::createPropertyHandleValuePairSetSP( bool force ) {

    int count = 0;
    for(
      const ClassAndPropertyName &key:
       *get_class_name_published_class_and_property_name_set_sp_map()[getInstanceHlaClassName()]
    ) {
        Attribute &attribute = *_classAndPropertyNameValueSPMap[key];
        if (attribute.getShouldBeUpdated(force)) {
            ++count;
        }
    }

    PropertyHandleValuePairSetSP propertyHandleValuePairSetSP(  RTI::AttributeSetFactory::create( count )  );
    PropertyHandleValuePairSet &propertyHandleValuePairSet = *propertyHandleValuePairSetSP;

    for(
      const ClassAndPropertyName &key:
       *get_class_name_published_class_and_property_name_set_sp_map()[getInstanceHlaClassName()]
    ) {
        Attribute &attribute = *_classAndPropertyNameValueSPMap[key];
        if (attribute.getShouldBeUpdated(force)) {
            int handle = get_class_and_property_name_handle_map()[key];
            std::string value = attribute.getStringRepresentation();
            propertyHandleValuePairSet.add(handle, value.c_str(), value.size());
            attribute.setHasBeenUpdated();
        }
    }

    return propertyHandleValuePairSetSP;
}

ClassAndPropertyNameSet ObjectRoot::getAttributesToBeUpdatedClassAndPropertyNameSet() {
    ClassAndPropertyNameSet attributesToBeUpdatedSet;
    for(
      const ClassAndPropertyName &key:
       *get_class_name_published_class_and_property_name_set_sp_map()[getInstanceHlaClassName()]
    ) {
        Attribute &attribute = *_classAndPropertyNameValueSPMap[key];
        if (attribute.getShouldBeUpdated(false)) {
            attributesToBeUpdatedSet.insert(key);
        }
    }

    return attributesToBeUpdatedSet;
}

void ObjectRoot::restoreAttributesToBeUpdated(const ClassAndPropertyNameSet &classAndPropertyNameSet) {
    for(
      const ClassAndPropertyName &key:
       *get_class_name_published_class_and_property_name_set_sp_map()[getInstanceHlaClassName()]
    ) {
        Attribute &attribute = *_classAndPropertyNameValueSPMap[key];
        bool shouldBeUpdated = classAndPropertyNameSet.find(key) != classAndPropertyNameSet.end();
        attribute.setShouldBeUpdated(shouldBeUpdated);
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

void ObjectRoot::publish_object(const std::string &hlaClassName, RTI::RTIambassador *rti) {

    if (!loadDynamicHlaClass(hlaClassName, rti)) {
        BOOST_LOG_SEV(get_logger(), warning) << "publish_object(\"" << hlaClassName << "\"):  " <<
          "no such class";
        return;
    }

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

    if (!loadDynamicHlaClass(hlaClassName, rti)) {
        BOOST_LOG_SEV(get_logger(), warning) << "subscribe_object(\"" << hlaClassName << "\"):  " <<
          "no such class";
        return;
    }

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

    if (!loadDynamicHlaClass(hlaClassName, rti)) {
        BOOST_LOG_SEV(get_logger(), warning) << "unpublish_object(\"" << hlaClassName << "\"):  " <<
          "no such class";
        return;
    }

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

    if (!loadDynamicHlaClass(hlaClassName, rti)) {
        BOOST_LOG_SEV(get_logger(), warning) << "unsubscribe_object(\"" << hlaClassName << "\"):  " <<
          "no such class";
        return;
    }

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
    if (get_class_name_handle_map().find(hlaClassName) == get_class_name_handle_map().end()) {
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
    BOOST_LOG_SEV(get_logger(), info) << "Class \"::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot\" loaded.";

    // ADD THIS CLASS TO THE _classNameSet DEFINED IN ObjectRoot
    get_hla_class_name_set().insert(get_hla_class_name());

    ObjectRoot::NoInstanceInit noInstanceInit;
    SP instanceSP = SP( new ObjectRoot(noInstanceInit) );
    get_hla_class_name_instance_sp_map()[get_hla_class_name()] = instanceSP;

    ClassAndPropertyNameSetSP classAndPropertyNameSetSP( new ClassAndPropertyNameSet() );

    // ADD THIS CLASS'S _classAndPropertyNameSet TO _classNamePropertyNameSetMap DEFINED
    // IN ObjectRoot
    get_class_name_class_and_property_name_set_sp_map()[get_hla_class_name()] = classAndPropertyNameSetSP;

    get_complete_class_and_property_name_set().insert(
      classAndPropertyNameSetSP->begin(), classAndPropertyNameSetSP->end()
    );

    ClassAndPropertyNameSetSP allClassAndPropertyNameSetSP( new ClassAndPropertyNameSet() );

    // ADD THIS CLASS'S _allClassAndPropertyNameSet TO _classNameAllPropertyNameSetMap DEFINED
    // IN ObjectRoot
    get_class_name_all_class_and_property_name_set_sp_map()[get_hla_class_name()] = allClassAndPropertyNameSetSP;

    common_init(get_hla_class_name());
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

std::string ObjectRoot::toJson(bool force) {
    Json::Value topLevelJSONObject(Json::objectValue);
    topLevelJSONObject["messaging_type"] = "object";
    topLevelJSONObject["messaging_name"] = getInstanceHlaClassName();
    topLevelJSONObject["object_handle"] = getObjectHandle();
    topLevelJSONObject["federateSequence"] = "[]";

    Json::Value propertyJSONObject(Json::objectValue);

    ClassAndPropertyNameSetSP publishedClassAndPropertyNameSetSP = getPublishedClassAndPropertyNameSetSP();
    ClassAndPropertyNameSet &publishedClassAndPropertyNameSet = *publishedClassAndPropertyNameSetSP;

    for(const ClassAndPropertyName &classAndPropertyName: publishedClassAndPropertyNameSet) {
        const std::string key(classAndPropertyName);
        Attribute &value = *_classAndPropertyNameValueSPMap[classAndPropertyName];
        if (value.getShouldBeUpdated(force)) {
            switch(value.getDataType()) {
                case TypeMedley::BOOLEAN:
                    propertyJSONObject[key] = static_cast<bool>(value);
                    break;
                case TypeMedley::CHARACTER:
                    propertyJSONObject[key] = static_cast<char>(value);
                    break;
                case TypeMedley::SHORT:
                    propertyJSONObject[key] = static_cast<short>(value);
                    break;
                case TypeMedley::INTEGER:
                    propertyJSONObject[key] = static_cast<int>(value);
                    break;
                case TypeMedley::LONG:
                    propertyJSONObject[key] = static_cast<Json::Value::Int64>(static_cast<long>(value));
                    break;
                case TypeMedley::FLOAT:
                    propertyJSONObject[key] = static_cast<float>(value);
                    break;
                case TypeMedley::DOUBLE:
                    propertyJSONObject[key] = static_cast<double>(value);
                    break;
                case TypeMedley::STRING:
                    propertyJSONObject[key] = static_cast<std::string>(value);
                    break;
                case TypeMedley::JSON:
                    propertyJSONObject[key] = static_cast<Json::Value>(value);
                    break;
            }
        }
    }
    topLevelJSONObject["properties"] = propertyJSONObject;

    Json::StreamWriterBuilder streamWriterBuilder;
    streamWriterBuilder["commandStyle"] = "None";
    streamWriterBuilder["indentation"] = "    ";
    std::unique_ptr<Json::StreamWriter> streamWriterUPtr(streamWriterBuilder.newStreamWriter());
    std::ostringstream stringOutputStream;
    streamWriterUPtr->write(topLevelJSONObject, &stringOutputStream);
    return stringOutputStream.str();
}

ObjectRoot::ObjectReflector::SP ObjectRoot::fromJson(const std::string &jsonString) {
    std::istringstream jsonInputStream(jsonString);

    Json::Value topLevelJSONObject;
    jsonInputStream >> topLevelJSONObject;

    int objectHandle = topLevelJSONObject["object_handle"].asInt();
    std::string className = topLevelJSONObject["messaging_name"].asString();
    std::string federateSequence = topLevelJSONObject["federateSequence"].asString();

    StringClassAndPropertyNameSetSPMap::const_iterator scmItr =
      get_class_name_soft_subscribed_class_and_property_name_set_sp_map().find( className );
    if (scmItr == get_class_name_soft_subscribed_class_and_property_name_set_sp_map().end()) {
        BOOST_LOG_SEV(get_logger(), error) << "fromJson:  no class \"" << className << "\" is defined";
        return ObjectReflector::SP();
    }
    ClassAndPropertyNameSet &softSubscribedAttributeNameSet = *scmItr->second;

    ClassAndPropertyNameValueSPMap classAndPropertyNameValueSPMap;

    const Json::Value &propertyJSONObject(topLevelJSONObject["properties"]);

    Json::Value::Members members(propertyJSONObject.getMemberNames());
    for(Json::Value::Members::const_iterator mbrCit = members.begin() ; mbrCit != members.end() ; ++mbrCit) {
        const std::string memberName(*mbrCit);
        ClassAndPropertyName classAndPropertyName(memberName);

        if (softSubscribedAttributeNameSet.find(classAndPropertyName) == softSubscribedAttributeNameSet.end()) {
            // LOG ERROR
            continue;
        }

        Value &initialValue = *get_class_and_property_name_initial_value_sp_map().find(classAndPropertyName)->second;
        classAndPropertyNameValueSPMap[classAndPropertyName] = ValueSP(new Value(initialValue));

        switch(classAndPropertyNameValueSPMap[classAndPropertyName]->getDataType()) {
            case TypeMedley::BOOLEAN:
                classAndPropertyNameValueSPMap[classAndPropertyName]->setValue(
                  propertyJSONObject[memberName].asBool()
                );
                break;
            case TypeMedley::CHARACTER: {
                Json::Value value = propertyJSONObject[memberName];
                int intValue = 0;
                if (value.isString()) {
                    std::string stringValue = value.asString();
                    intValue = stringValue.size() > 0 ? stringValue[0] : 0;
                } else {
                    intValue = value.isNumeric() ? value.asInt() : 0;
                }
                classAndPropertyNameValueSPMap[classAndPropertyName]->setValue(static_cast<char>(intValue));
                break;
            }
            case TypeMedley::SHORT:
                classAndPropertyNameValueSPMap[classAndPropertyName]->setValue(
                  static_cast<short>(propertyJSONObject[memberName].asInt())
                );
                break;
            case TypeMedley::INTEGER:
                classAndPropertyNameValueSPMap[classAndPropertyName]->setValue(
                  propertyJSONObject[memberName].asInt()
                );
                break;
            case TypeMedley::LONG:
                classAndPropertyNameValueSPMap[classAndPropertyName]->setValue(
                  static_cast<long>(propertyJSONObject[memberName].asInt64())
                );
                break;
            case TypeMedley::FLOAT:
                classAndPropertyNameValueSPMap[classAndPropertyName]->setValue(
                  propertyJSONObject[memberName].asFloat()
                );
                break;
            case TypeMedley::DOUBLE:
                classAndPropertyNameValueSPMap[classAndPropertyName]->setValue(
                  propertyJSONObject[memberName].asDouble()
                );
                break;
            case TypeMedley::STRING:
                classAndPropertyNameValueSPMap[classAndPropertyName]->setValue(
                  propertyJSONObject[memberName].asString()
                );
                break;
            case TypeMedley::JSON:
                classAndPropertyNameValueSPMap[classAndPropertyName]->setValue(
                  propertyJSONObject[memberName]
                );
                break;
        }
    }

    ObjectReflector::SP objectReflectorSP(new ObjectReflector(objectHandle, className, classAndPropertyNameValueSPMap));
    objectReflectorSP->setFederateSequence(federateSequence);
    return objectReflectorSP;
}

void ObjectRoot::add_federate_name_soft_publish_direct(
  const std::string &hlaClassName, const std::string &federateName
) {
   if (get_class_name_handle_map().find(hlaClassName) == get_class_name_handle_map().end()) {
        BOOST_LOG_SEV(get_logger(), warning) << "add_federate_name_soft_publish_direct(\"" << hlaClassName
          << ", \"" << federateName << "\") -- no such object class \"" << hlaClassName << "\"";
        return;
    }

    StringStringSetSPMap::iterator ssmItr =
      get_hla_class_name_to_federate_name_soft_publish_direct_set_sp_map().find(hlaClassName);
    if (ssmItr == get_hla_class_name_to_federate_name_soft_publish_direct_set_sp_map().end()) {
        ssmItr = get_hla_class_name_to_federate_name_soft_publish_direct_set_sp_map().emplace(
          hlaClassName, StringSetSP(new StringSet())
        ).first;
    }
    StringSet &stringSet = *ssmItr->second;
    stringSet.insert(federateName);
}

void ObjectRoot::remove_federate_name_soft_publish_direct(
  const std::string &hlaClassName, const std::string &federateName
) {
    StringStringSetSPMap::iterator ssmItr =
      get_hla_class_name_to_federate_name_soft_publish_direct_set_sp_map().find(hlaClassName);

    if (ssmItr != get_hla_class_name_to_federate_name_soft_publish_direct_set_sp_map().end()) {
        return;
    }

    StringSet &stringSet = *ssmItr->second;
    stringSet.erase(federateName);
    if (stringSet.empty()) {
        get_hla_class_name_to_federate_name_soft_publish_direct_set_sp_map().erase(federateName);
    }
}

void ObjectRoot::add_federate_name_soft_publish(
  const std::string &hlaClassName, const std::string &federateName
) {
    if (get_class_name_handle_map().find(hlaClassName) == get_class_name_handle_map().end()) {
        BOOST_LOG_SEV(get_logger(), warning) << "add_federate_name_soft_publish(\"" << hlaClassName << "\", \""
          << federateName << "\") -- no such object class \"" << hlaClassName << "\"";
        return;
    }

    if (
      get_hla_class_name_to_federate_name_soft_publish_set_sp_map().find(hlaClassName) ==
        get_hla_class_name_to_federate_name_soft_publish_set_sp_map().end()
    ) {
        get_hla_class_name_to_federate_name_soft_publish_set_sp_map().emplace(
          hlaClassName, StringSetSP(new StringSet())
        );
    }
    get_hla_class_name_to_federate_name_soft_publish_set_sp_map()[hlaClassName]->insert(federateName);
}

void ObjectRoot::remove_federate_name_soft_publish(
  const std::string &hlaClassName, const std::string &federateName
) {
    if (
      get_hla_class_name_to_federate_name_soft_publish_set_sp_map().find(hlaClassName) !=
        get_hla_class_name_to_federate_name_soft_publish_set_sp_map().end()
    ) {
        std::set<std::string> &federateNameSoftPublishSet =
          *get_hla_class_name_to_federate_name_soft_publish_set_sp_map()[hlaClassName];
        federateNameSoftPublishSet.erase(federateName);
        if (federateNameSoftPublishSet.empty()) {
            get_hla_class_name_to_federate_name_soft_publish_set_sp_map().erase(hlaClassName);
        }
    }
}

void ObjectRoot::readFederateDynamicMessageClasses(std::istream &dynamicMessagingTypesInputStream) {

    Json::Value dynamicMessageTypes;
    dynamicMessagingTypesInputStream >> dynamicMessageTypes;

    Json::Value dynamicHlaClassNames = dynamicMessageTypes["objects"];

    std::set<std::string> dynamicHlaClassNameSet;
    for(Json::Value hlaClassNameJsonValue: dynamicHlaClassNames) {
        std::string hlaClassName = hlaClassNameJsonValue.asString();
        dynamicHlaClassNameSet.insert(hlaClassName);
    }

    readFederateDynamicMessageClasses(dynamicHlaClassNameSet);
}

void ObjectRoot::readFederateDynamicMessageClass(const std::string &hlaClassName) {

    if (get_federation_json().isNull()) {
        BOOST_LOG_SEV(get_logger(), warning) << "readFederateDynamicMessageClasses:  no federation messaging loaded.";
        return;
    }

    Json::Value federationMessaging = get_federation_json()["objects"];

    std::unordered_set< std::string > localHlaClassNameSet;

    std::list<std::string> hlaClassNameComponents;
    boost::algorithm::split(hlaClassNameComponents, hlaClassName, boost::is_any_of("."));
    while(!hlaClassNameComponents.empty()) {
        const std::string localHlaClassName( boost::algorithm::join(hlaClassNameComponents, ".") );
        hlaClassNameComponents.pop_back();

        if (get_hla_class_name_set().find(localHlaClassName) != get_hla_class_name_set().end()) {
            break;
        }
        if (federationMessaging.isMember(localHlaClassName)) {
            localHlaClassNameSet.insert(localHlaClassName);
        } else {
            BOOST_LOG_SEV(get_logger(), warning) << "readFederateDynamicMessageClasses:  could not load hla " <<
              "class \"" << localHlaClassName << "\":  no definition exists.";
        }
    }

    for(const std::string &localHlaClassName: localHlaClassNameSet) {

        get_hla_class_name_set().insert(localHlaClassName);

        ClassAndPropertyNameSetSP classAndPropertyNameSetSP( new ClassAndPropertyNameSet() );
        ClassAndPropertyNameSet &classAndPropertyNameSet(*classAndPropertyNameSetSP);

        Json::Value messagingPropertyDataMap = federationMessaging[localHlaClassName];
        for(const std::string &propertyName: messagingPropertyDataMap.getMemberNames()) {
            ClassAndPropertyName classAndPropertyName(localHlaClassName, propertyName);
            classAndPropertyNameSet.insert(classAndPropertyName);

            Json::Value typeDataMap = messagingPropertyDataMap[propertyName];
            if (!typeDataMap["Hidden"].asBool()) {
                const std::string propertyTypeString = typeDataMap["ParameterType"].asString();
                get_class_and_property_name_initial_value_sp_map()[classAndPropertyName] =
                  ValueSP( new Value(*get_type_initial_value_sp_map()[propertyTypeString]) );
            }
        }

        get_class_name_class_and_property_name_set_sp_map()[localHlaClassName] = classAndPropertyNameSetSP;

        get_complete_class_and_property_name_set().insert(
          classAndPropertyNameSet.begin(), classAndPropertyNameSet.end()
        );
    }

    for(const std::string &localHlaClassName: localHlaClassNameSet) {

        ClassAndPropertyNameSetSP allClassAndPropertyNameSetSP( new ClassAndPropertyNameSet() );
        ClassAndPropertyNameSet &allClassAndPropertyNameSet(*allClassAndPropertyNameSetSP);

        std::list<std::string> hlaClassNameComponents;
        boost::algorithm::split(hlaClassNameComponents, localHlaClassName, boost::is_any_of("."));
        while(!hlaClassNameComponents.empty()) {
            const std::string localHlaClassName( boost::algorithm::join(hlaClassNameComponents, ".") );
            hlaClassNameComponents.pop_back();

            ClassAndPropertyNameSet &localClassAndPropertyNameSet =
              *get_class_name_class_and_property_name_set_sp_map()[localHlaClassName];
            allClassAndPropertyNameSet.insert(
              localClassAndPropertyNameSet.begin(), localClassAndPropertyNameSet.end()
            );
        }

        get_class_name_all_class_and_property_name_set_sp_map()[localHlaClassName] = allClassAndPropertyNameSetSP;

        common_init(localHlaClassName);
    }
}

ObjectRoot::operator std::string() const {
    std::ostringstream stringOutputStream;

    const ClassAndPropertyNameValueSPMap &classAndPropertyNameValueSPMap = getClassAndPropertyNameValueSPMap();
    stringOutputStream << getInstanceHlaClassName() << "(";
    bool first = true;
    for(
      ClassAndPropertyNameValueSPMap::const_iterator cvmCit = classAndPropertyNameValueSPMap.begin() ;
      cvmCit != classAndPropertyNameValueSPMap.end() ;
      ++cvmCit
    ) {
        if (first) first = false;
        else stringOutputStream << ", ";

        stringOutputStream << static_cast<std::string>(cvmCit->first) << ": ";
        TypeMedley &value = *cvmCit->second;
        switch(value.getDataType()) {
            case TypeMedley::DOUBLE: {
                stringOutputStream << static_cast<double>(value);
                break;
            }
            case TypeMedley::FLOAT: {
                stringOutputStream << static_cast<float>(value);
                break;
            }
            case TypeMedley::STRING: {
                stringOutputStream << "\"" << static_cast<std::string>(value) << "\"";
                break;
            }
            default: {
                stringOutputStream << static_cast<std::string>(value);
                break;
            }
        }
    }
    stringOutputStream << ")";

    return stringOutputStream.str();
}

    } // NAMESPACE "hla"
   } // NAMESPACE "cpswt"
  } // NAMESPACE "vuisis"
 } // NAMESPACE "vanderbilt"
} // NAMESPACE "edu"
