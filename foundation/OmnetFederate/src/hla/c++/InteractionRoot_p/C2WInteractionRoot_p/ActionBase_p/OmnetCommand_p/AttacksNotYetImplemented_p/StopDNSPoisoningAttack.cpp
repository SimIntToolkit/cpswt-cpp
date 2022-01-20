
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

#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/AttacksNotYetImplemented_p/StopDNSPoisoningAttack.hpp"
namespace org {
 namespace cpswt {
  namespace hla {
   namespace InteractionRoot_p {
    namespace C2WInteractionRoot_p {
     namespace ActionBase_p {
      namespace OmnetCommand_p {
       namespace AttacksNotYetImplemented_p {

bool StopDNSPoisoningAttack::static_init_var = StopDNSPoisoningAttack::static_init();

bool StopDNSPoisoningAttack::static_init() {
    // ADD THIS CLASS TO THE _classNameSet DEFINED IN InteractionRoot
    get_class_name_set().insert(get_hla_class_name());

    // ADD CLASS OBJECT OF THIS CLASS TO _classNameClassMap DEFINED IN InteractionRoot
    get_class_name_instance_sp_map()[get_hla_class_name()] = SP(new StopDNSPoisoningAttack());

    // ADD THIS CLASS'S _classAndPropertyNameSet TO _classNamePropertyNameSetMap DEFINED
    // IN InteractionRoot
    get_class_name_class_and_property_name_set_sp_map()[get_hla_class_name()] = get_class_and_property_name_set_sp();

    // ADD THIS CLASS'S _allClassAndPropertyNameSet TO _classNameAllPropertyNameSetMap DEFINED
    // IN InteractionRoot
    get_class_name_all_class_and_property_name_set_sp_map()[get_hla_class_name()] =
      get_all_class_and_property_name_set_sp();
    get_class_and_property_name_set_sp()->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StopDNSPoisoningAttack", "affectedHost"
    );
    get_class_and_property_name_set_sp()->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StopDNSPoisoningAttack", "dnsHost"
    );
    get_class_and_property_name_set_sp()->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StopDNSPoisoningAttack", "listenerHost"
    );

    get_class_and_property_name_set_sp()->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StopDNSPoisoningAttack", "affectedHost"
    );

    get_class_and_property_name_set_sp()->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StopDNSPoisoningAttack", "dnsHost"
    );

    get_class_and_property_name_set_sp()->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StopDNSPoisoningAttack", "listenerHost"
    );

    get_class_and_property_name_set_sp()->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand", "uniqueCommandID"
    );

    get_class_and_property_name_set_sp()->emplace(
        "InteractionRoot.C2WInteractionRoot", "actualLogicalGenerationTime"
    );

    get_class_and_property_name_set_sp()->emplace(
        "InteractionRoot.C2WInteractionRoot", "federateFilter"
    );

    get_class_and_property_name_set_sp()->emplace(
        "InteractionRoot.C2WInteractionRoot", "originFed"
    );

    get_class_and_property_name_set_sp()->emplace(
        "InteractionRoot.C2WInteractionRoot", "sourceFed"
    );

    return true;
}


int StopDNSPoisoningAttack::get_parameter_handle_aux(const std::string &className, const std::string &propertyName) {
    ClassAndPropertyName key(get_hla_class_name(), propertyName);
    ClassAndPropertyNameIntegerMap::const_iterator cimCit = get_class_and_property_name_handle_map().find(key);
    if (cimCit != get_class_and_property_name_handle_map().end()) {
        return cimCit->second;
    }
    return Super::get_parameter_handle_aux(className, propertyName);
}


void StopDNSPoisoningAttack::init(RTI::RTIambassador *rti) {
    if (get_is_initialized()) return;
    get_is_initialized() = true;
    Super::init(rti);

    bool isNotInitialized = true;
    while(isNotInitialized) {
        try {
            get_class_handle() = rti->getInteractionClassHandle(get_hla_class_name().c_str());
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

            propertyHandle = rti->getParameterHandle("affectedHost", get_class_handle());
            classAndPropertyNameSP = ClassAndPropertyNameSP( new ClassAndPropertyName(
              get_hla_class_name(), "affectedHost"
            ) );
            get_class_and_property_name_handle_map()[*classAndPropertyNameSP] = propertyHandle;
            get_handle_class_and_property_name_sp_map()[propertyHandle] = classAndPropertyNameSP;

            propertyHandle = rti->getParameterHandle("dnsHost", get_class_handle());
            classAndPropertyNameSP = ClassAndPropertyNameSP( new ClassAndPropertyName(
              get_hla_class_name(), "dnsHost"
            ) );
            get_class_and_property_name_handle_map()[*classAndPropertyNameSP] = propertyHandle;
            get_handle_class_and_property_name_sp_map()[propertyHandle] = classAndPropertyNameSP;

            propertyHandle = rti->getParameterHandle("listenerHost", get_class_handle());
            classAndPropertyNameSP = ClassAndPropertyNameSP( new ClassAndPropertyName(
              get_hla_class_name(), "listenerHost"
            ) );
            get_class_and_property_name_handle_map()[*classAndPropertyNameSP] = propertyHandle;
            get_handle_class_and_property_name_sp_map()[propertyHandle] = classAndPropertyNameSP;

            isNotInitialized = false;
        } catch (RTI::FederateNotExecutionMember e) {
//            logger.error("could not initialize: Federate Not Execution Member", e);
            return;
        } catch (RTI::InteractionClassNotDefined e) {
//            logger.error("could not initialize: Interaction Class Not Defined", e);
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


void StopDNSPoisoningAttack::publish_interaction(RTI::RTIambassador *rti) {
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
//            logger.error("could not publish: Federate Not Execution Member", e);
            return;
        } catch (RTI::InteractionClassNotDefined e) {
//            logger.error("could not publish: Interaction Class Not Defined", e);
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


void StopDNSPoisoningAttack::unpublish_interaction(RTI::RTIambassador *rti) {
    if (!get_is_published()) return;
    get_is_published() = false;

    init(rti);

    bool isNotUnpublished = true;
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
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
        }
    }

//    logger.debug("unpublish: {}", get_hla_class_name());
}


void StopDNSPoisoningAttack::subscribe_interaction(RTI::RTIambassador *rti) {
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
//            logger.error("could not subscribe: Federate Not Execution Member", e);
            return;
        } catch (RTI::InteractionClassNotDefined e) {
//            logger.error("could not subscribe: Interaction Class Not Defined", e);
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


void StopDNSPoisoningAttack::unsubscribe_interaction(RTI::RTIambassador *rti) {
    if (!get_is_subscribed()) return;
    get_is_subscribed() = false;

    init(rti);

    bool isNotUnsubscribed = true;
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


StopDNSPoisoningAttack::PropertyClassNameAndValueSP StopDNSPoisoningAttack::getParameterAux(
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
       } // NAMESPACE "AttacksNotYetImplemented_p"
      } // NAMESPACE "OmnetCommand_p"
     } // NAMESPACE "ActionBase_p"
    } // NAMESPACE "C2WInteractionRoot_p"
   } // NAMESPACE "InteractionRoot_p"
  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"