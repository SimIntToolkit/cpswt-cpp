
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
    get_hla_class_name_set().insert(get_hla_class_name());

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

    get_all_class_and_property_name_set_sp()->emplace(
        "ObjectRoot.FederateObject", "FederateHandle"
    );

    get_all_class_and_property_name_set_sp()->emplace(
        "ObjectRoot.FederateObject", "FederateHost"
    );

    get_all_class_and_property_name_set_sp()->emplace(
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
            BOOST_LOG_SEV(get_logger(), error)
              << "could not initialize attribute handle: federate not execution member";
            return;
        } catch (RTI::ObjectClassNotDefined e) {
            BOOST_LOG_SEV(get_logger(), error)
              << "could not initialize attribute handle: object class not defined";
            return;
        } catch (RTI::NameNotFound e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not initialize attribute handle: name not found";
            return;
        } catch (...) {
            BOOST_LOG_SEV(get_logger(), error)
              << "could not initialize attribute handle: unspecified exception ... retry";
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