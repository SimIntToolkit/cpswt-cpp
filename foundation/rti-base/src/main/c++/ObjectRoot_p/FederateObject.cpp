
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

#include "ObjectRoot_p/FederateObject.hpp"
namespace org {
 namespace cpswt {
  namespace hla {
   namespace ObjectRoot_p {

bool FederateObject::static_init_var = FederateObject::static_init();

bool FederateObject::static_init() {
    // ADD THIS CLASS TO THE _classNameSet DEFINED IN ObjectRoot
    get_class_name_set().insert(get_hla_class_name());

    // ADD CLASS OBJECT OF THIS CLASS TO _classNameClassMap DEFINED IN ObjectRoot
    get_class_name_instance_sp_map()[get_hla_class_name()] = SP(new FederateObject());

    // ADD THIS CLASS'S _classAndPropertyNameSet TO _classNamePropertyNameSetMap DEFINED
    // IN ObjectRoot
    get_class_name_class_and_property_name_set_sp_map()[get_hla_class_name()] = get_class_and_property_name_set_sp();

    // ADD THIS CLASS'S _allClassAndPropertyNameSet TO _classNameAllPropertyNameSetMap DEFINED
    // IN ObjectRoot
    get_class_name_all_class_and_property_name_set_sp_map()[get_hla_class_name()] =
      get_all_class_and_property_name_set_sp();
    get_class_and_property_name_set_sp()->emplace(
        "ObjectRoot.FederateObject", "FederateHandle"
    );
    get_class_and_property_name_set_sp()->emplace(
        "ObjectRoot.FederateObject", "FederateHost"
    );
    get_class_and_property_name_set_sp()->emplace(
        "ObjectRoot.FederateObject", "FederateType"
    );

    get_class_and_property_name_set_sp()->emplace(
        "ObjectRoot.FederateObject", "FederateHandle"
    );

    get_class_and_property_name_set_sp()->emplace(
        "ObjectRoot.FederateObject", "FederateHost"
    );

    get_class_and_property_name_set_sp()->emplace(
        "ObjectRoot.FederateObject", "FederateType"
    );

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


int FederateObject::get_attribute_handle_aux(const std::string &className, const std::string &propertyName) {
    ClassAndPropertyName key(get_hla_class_name(), propertyName);
    ClassAndPropertyNameIntegerMap::const_iterator cimCit = get_class_and_property_name_handle_map().find(key);
    if (cimCit != get_class_and_property_name_handle_map().end()) {
        return cimCit->second;
    }
    return Super::get_attribute_handle_aux(className, propertyName);
}


void FederateObject::init(RTI::RTIambassador *rti) {
    if (get_is_initialized()) return;
    get_is_initialized() = true;
    Super::init(rti);

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

    ClassAndPropertyNameSP classAndPropertyNameSP;

    isNotInitialized = true;
    int propertyHandle;
    while(isNotInitialized) {
        try {

            propertyHandle = rti->getAttributeHandle("FederateHandle", get_class_handle());
            classAndPropertyNameSP = ClassAndPropertyNameSP( new ClassAndPropertyName(
              get_hla_class_name(), "FederateHandle"
            ) );
            get_class_and_property_name_handle_map()[*classAndPropertyNameSP] = propertyHandle;
            get_handle_class_and_property_name_sp_map()[propertyHandle] = classAndPropertyNameSP;

            propertyHandle = rti->getAttributeHandle("FederateHost", get_class_handle());
            classAndPropertyNameSP = ClassAndPropertyNameSP( new ClassAndPropertyName(
              get_hla_class_name(), "FederateHost"
            ) );
            get_class_and_property_name_handle_map()[*classAndPropertyNameSP] = propertyHandle;
            get_handle_class_and_property_name_sp_map()[propertyHandle] = classAndPropertyNameSP;

            propertyHandle = rti->getAttributeHandle("FederateType", get_class_handle());
            classAndPropertyNameSP = ClassAndPropertyNameSP( new ClassAndPropertyName(
              get_hla_class_name(), "FederateType"
            ) );
            get_class_and_property_name_handle_map()[*classAndPropertyNameSP] = propertyHandle;
            get_handle_class_and_property_name_sp_map()[propertyHandle] = classAndPropertyNameSP;

            isNotInitialized = false;
        } catch (RTI::FederateNotExecutionMember e) {
//            logger.error("could not initialize: Federate Not Execution Member", e);
            return;
        } catch (RTI::ObjectClassNotDefined e) {
//            logger.error("could not initialize: Object Class Not Defined", e);
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
}


void FederateObject::publish_object(RTI::RTIambassador *rti) {
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


void FederateObject::unpublish_object(RTI::RTIambassador *rti) {
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


void FederateObject::subscribe_object(RTI::RTIambassador *rti) {
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


void FederateObject::unsubscribe_object(RTI::RTIambassador *rti) {
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


FederateObject::PropertyClassNameAndValueSP FederateObject::getAttributeAux(
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
   } // NAMESPACE "ObjectRoot_p"
  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"