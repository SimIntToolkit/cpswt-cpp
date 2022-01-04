#include "ObjectRoot/FederateObject.hpp"
namespace org {
 namespace cpswt {
  namespace hla {
   namespace ObjectRoot {

bool ObjectRoot::static_init() {
    // ADD THIS CLASS TO THE _classNameSet DEFINED IN ObjectRoot
    get_class_name_set().add(get_hla_class_name());

    // ADD CLASS OBJECT OF THIS CLASS TO _classNameClassMap DEFINED IN ObjectRoot
    get_class_name_instance_sp_map()[get_hla_class_name()] = SP(new FederateObject());

    // ADD THIS CLASS'S _classAndPropertyNameSet TO _classNamePropertyNameSetMap DEFINED
    // IN ObjectRoot
    get_class_name_property_name_set_sp_map()[get_hla_class_name()] = get_class_and_property_name_set_sp();

    // ADD THIS CLASS'S _allClassAndPropertyNameSet TO _classNameAllPropertyNameSetMap DEFINED
    // IN ObjectRoot
    get_class_name_all_property_name_set_sp_map()[get_hla_class_name()] = get_all_class_and_property_name_set_sp();
    get_class_and_property_name_set_sp()->emplace(
        "ObjectRoot.FederateObject", "FederateHandle"
    );
    get_class_and_property_name_set_sp()->emplace(
        "ObjectRoot.FederateObject", "FederateHost"
    );
    get_class_and_property_name_set_sp()->emplace(
        "ObjectRoot.FederateObject", "FederateType"
    );

    get_class_and_property_name_set_sp().emplace(
        "ObjectRoot.FederateObject", "FederateHandle"
    );

    get_class_and_property_name_set_sp().emplace(
        "ObjectRoot.FederateObject", "FederateHost"
    );

    get_class_and_property_name_set_sp().emplace(
        "ObjectRoot.FederateObject", "FederateType"
    );

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
    return Super::get_attribute_handle_aux(className, propertyName);
}


void ObjectRoot::init(RTIambassador rti) {
    if (get_is_initialized()) return;
    get_is_initialized() = true;
    Super::init(rti);

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

    ClassAndPropertyNameSP classAndPropertyNameSP;

    isNotInitialized = true;
    int propertyHandle;
    while(isNotInitialized) {
        try {

            propertyHandle = rti.getAttributeHandle("FederateHandle", get_class_handle());
            classAndPropertyNameSP = ClassAndPropertyNameSP(get_hla_class_name(), "FederateHandle");
            get_class_and_property_name_handle_map()[*classAndPropertyNameSP] = propertyHandle;
            get_handle_class_and_property_name_sp_map[propertyHandle] = classAndPropertyNameSP;

            propertyHandle = rti.getAttributeHandle("FederateHost", get_class_handle());
            classAndPropertyNameSP = ClassAndPropertyNameSP(get_hla_class_name(), "FederateHost");
            get_class_and_property_name_handle_map()[*classAndPropertyNameSP] = propertyHandle;
            get_handle_class_and_property_name_sp_map[propertyHandle] = classAndPropertyNameSP;

            propertyHandle = rti.getAttributeHandle("FederateType", get_class_handle());
            classAndPropertyNameSP = ClassAndPropertyNameSP(get_hla_class_name(), "FederateType");
            get_class_and_property_name_handle_map()[*classAndPropertyNameSP] = propertyHandle;
            get_handle_class_and_property_name_sp_map[propertyHandle] = classAndPropertyNameSP;

            isNotInitialized = false;
        } catch (FederateNotExecutionMember e) {
            logger.error("could not initialize: Federate Not Execution Member", e);
            return;
        } catch (ObjectClassNotDefined e) {
            logger.error("could not initialize: Object Class Not Defined", e);
            return;
        } catch (NameNotFound e) {
            logger.error("could not initialize: Name Not Found", e);
            return;
        } catch (Exception e) {
            logger.error(e);
            CpswtUtils.sleepDefault();
        }
    }
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

    return Super::getAttributeAux(className, propertyName);
}
   } // NAMESPACE "ObjectRoot"
  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"