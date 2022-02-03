
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

#include "InteractionRoot_p/C2WInteractionRoot_p/FederateResignInteraction.hpp"
namespace org {
 namespace cpswt {
  namespace hla {
   namespace InteractionRoot_p {
    namespace C2WInteractionRoot_p {

bool FederateResignInteraction::static_init_var = FederateResignInteraction::static_init();

bool FederateResignInteraction::static_init() {
    // ADD THIS CLASS TO THE _classNameSet DEFINED IN InteractionRoot
    get_hla_class_name_set().insert(get_hla_class_name());

    // ADD CLASS OBJECT OF THIS CLASS TO _classNameClassMap DEFINED IN InteractionRoot
    get_class_name_instance_sp_map()[get_hla_class_name()] = SP(new FederateResignInteraction());

    // ADD THIS CLASS'S _classAndPropertyNameSet TO _classNamePropertyNameSetMap DEFINED
    // IN InteractionRoot
    get_class_name_class_and_property_name_set_sp_map()[get_hla_class_name()] = get_class_and_property_name_set_sp();

    // ADD THIS CLASS'S _allClassAndPropertyNameSet TO _classNameAllPropertyNameSetMap DEFINED
    // IN InteractionRoot
    get_class_name_all_class_and_property_name_set_sp_map()[get_hla_class_name()] =
      get_all_class_and_property_name_set_sp();
    get_class_and_property_name_set_sp()->emplace(
        "InteractionRoot.C2WInteractionRoot.FederateResignInteraction", "FederateId"
    );
    get_class_and_property_name_set_sp()->emplace(
        "InteractionRoot.C2WInteractionRoot.FederateResignInteraction", "FederateType"
    );
    get_class_and_property_name_set_sp()->emplace(
        "InteractionRoot.C2WInteractionRoot.FederateResignInteraction", "IsLateJoiner"
    );

    get_all_class_and_property_name_set_sp()->emplace(
        "InteractionRoot.C2WInteractionRoot.FederateResignInteraction", "FederateId"
    );

    get_all_class_and_property_name_set_sp()->emplace(
        "InteractionRoot.C2WInteractionRoot.FederateResignInteraction", "FederateType"
    );

    get_all_class_and_property_name_set_sp()->emplace(
        "InteractionRoot.C2WInteractionRoot.FederateResignInteraction", "IsLateJoiner"
    );

    get_all_class_and_property_name_set_sp()->emplace(
        "InteractionRoot.C2WInteractionRoot", "actualLogicalGenerationTime"
    );

    get_all_class_and_property_name_set_sp()->emplace(
        "InteractionRoot.C2WInteractionRoot", "federateFilter"
    );

    get_all_class_and_property_name_set_sp()->emplace(
        "InteractionRoot.C2WInteractionRoot", "originFed"
    );

    get_all_class_and_property_name_set_sp()->emplace(
        "InteractionRoot.C2WInteractionRoot", "sourceFed"
    );

    return true;
}


int FederateResignInteraction::get_parameter_handle_aux(const std::string &className, const std::string &propertyName) {
    ClassAndPropertyName key(get_hla_class_name(), propertyName);
    ClassAndPropertyNameIntegerMap::const_iterator cimCit = get_class_and_property_name_handle_map().find(key);
    if (cimCit != get_class_and_property_name_handle_map().end()) {
        return cimCit->second;
    }
    return Super::get_parameter_handle_aux(className, propertyName);
}


void FederateResignInteraction::init(RTI::RTIambassador *rti) {
    if (get_is_initialized()) return;
    get_is_initialized() = true;
    Super::init(rti);

    bool isNotInitialized = true;
    while(isNotInitialized) {
        try {
            get_class_handle() = rti->getInteractionClassHandle(get_hla_class_name().c_str());
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

            propertyHandle = rti->getParameterHandle("FederateId", get_class_handle());
            classAndPropertyNameSP = ClassAndPropertyNameSP( new ClassAndPropertyName(
              get_hla_class_name(), "FederateId"
            ) );
            get_class_and_property_name_handle_map()[*classAndPropertyNameSP] = propertyHandle;
            get_handle_class_and_property_name_sp_map()[propertyHandle] = classAndPropertyNameSP;

            propertyHandle = rti->getParameterHandle("FederateType", get_class_handle());
            classAndPropertyNameSP = ClassAndPropertyNameSP( new ClassAndPropertyName(
              get_hla_class_name(), "FederateType"
            ) );
            get_class_and_property_name_handle_map()[*classAndPropertyNameSP] = propertyHandle;
            get_handle_class_and_property_name_sp_map()[propertyHandle] = classAndPropertyNameSP;

            propertyHandle = rti->getParameterHandle("IsLateJoiner", get_class_handle());
            classAndPropertyNameSP = ClassAndPropertyNameSP( new ClassAndPropertyName(
              get_hla_class_name(), "IsLateJoiner"
            ) );
            get_class_and_property_name_handle_map()[*classAndPropertyNameSP] = propertyHandle;
            get_handle_class_and_property_name_sp_map()[propertyHandle] = classAndPropertyNameSP;

            isNotInitialized = false;
        } catch (RTI::FederateNotExecutionMember e) {
            BOOST_LOG_SEV(get_logger(), error)
              << "could not initialize parameter handle: federate not execution member";
            return;
        } catch (RTI::InteractionClassNotDefined e) {
            BOOST_LOG_SEV(get_logger(), error)
              << "could not initialize parameter handle: interaction class not defined";
            return;
        } catch (RTI::NameNotFound e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not initialize parameter handle: name not found";
            return;
        } catch (...) {
            BOOST_LOG_SEV(get_logger(), error)
              << "could not initialize parameter handle: unspecified exception ... retry";
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
        }
    }
}


void FederateResignInteraction::publish_interaction(RTI::RTIambassador *rti) {
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
            BOOST_LOG_SEV(get_logger(), error) << "could not publish: federate not execution member";
            return;
        } catch (RTI::InteractionClassNotDefined e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not publish: interaction class not defined";
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

    BOOST_LOG_SEV(get_logger(), debug) << "publish_interaction: interaction published";
}


void FederateResignInteraction::unpublish_interaction(RTI::RTIambassador *rti) {
    if (!get_is_published()) return;
    get_is_published() = false;

    init(rti);

    bool isNotUnpublished = true;
    while(isNotUnpublished) {
        try {
            rti->unpublishInteractionClass(get_class_handle());
            isNotUnpublished = false;
        } catch (RTI::FederateNotExecutionMember e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unpublish: federate not execution member";
            return;
        } catch (RTI::InteractionClassNotDefined e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unpublish: interaction class not defined";
            return;
        } catch (RTI::InteractionClassNotPublished e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unpublish: interaction class not published";
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

    BOOST_LOG_SEV(get_logger(), debug) << "unpublish_interaction: interaction unpublished";
}


void FederateResignInteraction::subscribe_interaction(RTI::RTIambassador *rti) {
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
            BOOST_LOG_SEV(get_logger(), error) << "could not subscribe: federate not execution member";
            return;
        } catch (RTI::InteractionClassNotDefined e) {
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

    BOOST_LOG_SEV(get_logger(), debug) << "subscribe_interaction: interaction subscribed";
}


void FederateResignInteraction::unsubscribe_interaction(RTI::RTIambassador *rti) {
    if (!get_is_subscribed()) return;
    get_is_subscribed() = false;

    init(rti);

    bool isNotUnsubscribed = true;
    while(isNotUnsubscribed) {
        try {
            rti->unsubscribeInteractionClass(get_class_handle());
            isNotUnsubscribed = false;
        } catch (RTI::FederateNotExecutionMember e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unsubscribe: federate not execution member";
            return;
        } catch (RTI::InteractionClassNotDefined e) {
            BOOST_LOG_SEV(get_logger(), error) << "could not unsubscribe: class not defined";
            return;
        } catch (RTI::InteractionClassNotSubscribed e) {
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

    BOOST_LOG_SEV(get_logger(), debug) << "unsubscribe_interaction: interaction unsubscribed";
}


FederateResignInteraction::PropertyClassNameAndValueSP FederateResignInteraction::getParameterAux(
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
    } // NAMESPACE "C2WInteractionRoot_p"
   } // NAMESPACE "InteractionRoot_p"
  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"