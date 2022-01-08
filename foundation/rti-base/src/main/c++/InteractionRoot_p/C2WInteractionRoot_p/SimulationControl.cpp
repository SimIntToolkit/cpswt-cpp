#include "InteractionRoot_p/C2WInteractionRoot_p/SimulationControl.hpp"
namespace org {
 namespace cpswt {
  namespace hla {
   namespace InteractionRoot_p {
    namespace C2WInteractionRoot_p {

bool SimulationControl::static_init() {
    // ADD THIS CLASS TO THE _classNameSet DEFINED IN InteractionRoot
    get_class_name_set().insert(get_hla_class_name());

    // ADD CLASS OBJECT OF THIS CLASS TO _classNameClassMap DEFINED IN InteractionRoot
    get_class_name_instance_sp_map()[get_hla_class_name()] = SP(new SimulationControl());

    // ADD THIS CLASS'S _classAndPropertyNameSet TO _classNamePropertyNameSetMap DEFINED
    // IN InteractionRoot
    get_class_name_class_and_property_name_set_sp_map()[get_hla_class_name()] = get_class_and_property_name_set_sp();

    // ADD THIS CLASS'S _allClassAndPropertyNameSet TO _classNameAllPropertyNameSetMap DEFINED
    // IN InteractionRoot
    get_class_name_all_class_and_property_name_set_sp_map()[get_hla_class_name()] =
      get_all_class_and_property_name_set_sp();

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


int SimulationControl::get_parameter_handle_aux(const std::string &className, const std::string &propertyName) {
    ClassAndPropertyName key(get_hla_class_name(), propertyName);
    ClassAndPropertyNameIntegerMap::const_iterator cimCit = get_class_and_property_name_handle_map().find(key);
    if (cimCit != get_class_and_property_name_handle_map().end()) {
        return cimCit->second;
    }
    return Super::get_parameter_handle_aux(className, propertyName);
}


void SimulationControl::init(RTI::RTIambassador *rti) {
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
}


void SimulationControl::publish_interaction(RTI::RTIambassador *rti) {
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


void SimulationControl::unpublish_interaction(RTI::RTIambassador *rti) {
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


void SimulationControl::subscribe_interaction(RTI::RTIambassador *rti) {
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


void SimulationControl::unsubscribe_interaction(RTI::RTIambassador *rti) {
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


SimulationControl::PropertyClassNameAndValueSP SimulationControl::getParameterAux(
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