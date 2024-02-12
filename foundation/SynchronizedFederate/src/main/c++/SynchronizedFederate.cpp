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

#include "SynchronizedFederate.hpp"


#include <sys/types.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <ctime>
#include <cstdlib>
#include <sstream>


// const double SynchronizedFederate::_stepSize = 0.2;

#if __cplusplus >= 201703L
#define MultiArgThrow17
#define Throw17 noexcept
#define throw(...) __VA_OPT__(MultiArg)##Throw17
#endif

void SynchronizedFederate::deleteProxy(const std::string &federateName) {
    if (!hasProxy(federateName)) {
        BOOST_LOG_SEV( get_logger(), warning ) << "deleteProxy:  There is currently no proxy for federate \""
           << federateName << "\".  Nothing to delete.";
        return;
    }

    const StringSP currentProxyFederateNameSP = federateNameToProxyFederateNameSPMap[federateName];
    const std::string &currentProxyFederateName = *currentProxyFederateNameSP;
    federateNameToProxyFederateNameSPMap.erase(federateName);

    StringSetSP proxiedFederateNameSetSP = proxyFederateNameToFederateNameSetSPMap[currentProxyFederateName];
    StringSet proxiedFederateNameSet = *proxiedFederateNameSetSP;
    proxiedFederateNameSet.erase(federateName);

    if (proxiedFederateNameSet.empty()) {
        proxyFederateNameToFederateNameSetSPMap.erase(currentProxyFederateName);
    }
}

void SynchronizedFederate::addProxy(const std::string &federateName, const std::string &proxyFederateName) {
    if (hasProxy(federateName)) {
        const StringSP currentProxyFederateNameSP = federateNameToProxyFederateNameSPMap[federateName];
        const std::string &currentProxyFederateName = *currentProxyFederateNameSP;

        BOOST_LOG_SEV( get_logger(), warning ) << "Federate \"" << federateName
          << "\" is already proxied by federate \"" << currentProxyFederateName
          << "SynchronizedFederate::\".  You should delete this proxy before establishing a new one.  Federate \"" << federateName
          << "\" will now be proxied by federate \"" << proxyFederateName << "\"";
        deleteProxy(federateName);
    }

    if (
      proxyFederateNameToFederateNameSetSPMap.find(proxyFederateName) ==
        proxyFederateNameToFederateNameSetSPMap.end()
    ) {
        proxyFederateNameToFederateNameSetSPMap.insert(
          std::make_pair(proxyFederateName, StringSetSP(new StringSet()))
        );
    }
    proxyFederateNameToFederateNameSetSPMap[proxyFederateName]->insert(federateName);
}

void SynchronizedFederate::createRTI( void ) {

    bool rtiNotPresent = true;
    
    if ( get_federation_manager_name().compare( getFederateId() ) != 0 ) {
        // Himanshu: This is a regular federate, wait 1 seconds for federation manager to initialize first
        std::cout << "Regular federate waiting 1 secs for Federation Manager to initialize" << std:: endl << std::flush;
#ifdef _WIN32
            Sleep( 1000 );
#else
            usleep( 1000000 );
#endif
    }
    while( rtiNotPresent ) {
        try {
            std::cout << "acquiring connection to RTI ... " << std::flush;
            _rti = new RTI::RTIambassador();
            std::cout << "done." << std::endl;

            rtiNotPresent = false;
        } catch ( RTI::RTIinternalError ) {
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
        }
    }

}

void SynchronizedFederate::notifyFederationOfJoin() {

    // Federate state interaction pubsub
    FederateJoinInteraction::publish_interaction( getRTI() );
    FederateResignInteraction::publish_interaction( getRTI() );

    FederateJoinInteraction intJoin;

    intJoin.set_FederateType( getFederateType() );
    intJoin.set_FederateId( getFederateId() );
    intJoin.set_IsLateJoiner(get_IsLateJoiner());


    std::cout << "Sending Join interaction #-"  << std::endl;
    sendInteraction(intJoin, _currentTime);
}

void SynchronizedFederate::notifyFederationOfResign() {
    FederateResignInteraction intResign;
    intResign.set_FederateType( getFederateType() );
    intResign.set_FederateId( getFederateId() );
    intResign.set_IsLateJoiner(get_IsLateJoiner());

    std::cout << "Sending Resign interaction #-"  << std::endl;
    sendInteraction(intResign, _currentTime);
}

void SynchronizedFederate::initializeDynamicMessaging(
  const std::string &federationJsonFileName,
  const std::string &federateDynamicMessagingClassesJsonFileName
) {
    if (federationJsonFileName.empty() || federateDynamicMessagingClassesJsonFileName.empty()) {
        initializeMessaging();
        return;
    }

    std::ifstream federationJsonInputStream(federationJsonFileName);
    std::ifstream federateDynamicMessagingClassJsonInputStream(federateDynamicMessagingClassesJsonFileName);

    initializeDynamicMessaging(
      federationJsonInputStream,
      federateDynamicMessagingClassJsonInputStream
    );

    federationJsonInputStream.close();
    federateDynamicMessagingClassJsonInputStream.close();
}


void SynchronizedFederate::joinFederation() {

    std::cout << " federate joining federation ... " << std::flush;

    bool federationNotPresent = true;
    while( federationNotPresent ) {
        try {
            getRTI()->joinFederationExecution( this->_federateId.c_str(), this->_federationId.c_str(), this );
            federationNotPresent = false;
        } catch ( RTI::FederateAlreadyExecutionMember & ) {
            std::cout << "failed (already execution member)." << std::endl;
            return;
        } catch ( ... ) {
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
        }
    }

    // IT APPEARS THERE IS A RACE CONDITION THAT OCCURS BETWEEN A SUCCESSFUL CALL TO "joinFederationExecution" AND "enableTimeConstrained"
    // FOR THE RTI, AND, GENERALLY, THE LATTER IS CALLED IMMEDIATELY AFTER THE FORMER.
    // IF THE LATTER IS CALLED TOO QUICKLY AFTER THE FORMER, A SEGFAULT OCCURS IN THE JVM'S JNI DUE TO A NULL POINTER.
    // THE BELOW "WAITING PERIOD" SEEMS TO WORK-AROUND THIS PROBLEM.
#ifdef _WIN32
    Sleep( 3000 );
#else
    usleep( 3000000 );
#endif

    std::cout << "done." << std::endl;

    initializeDynamicMessaging(_federationJsonFileName, _federateDynamicMessagingClassesJsonFileName);

    ensureSimEndPubsub();

    AddProxy::subscribe_interaction(getRTI());
    AddProxy::publish_interaction(getRTI());

    DeleteProxy::subscribe_interaction(getRTI());
    DeleteProxy::publish_interaction(getRTI());

    notifyFederationOfJoin();
}

void SynchronizedFederate::sendInteraction(
  InteractionRoot &interactionRoot, const StringSet &federateNameSet, double time
) {

    if (!interactionRoot.isInstanceHlaClassDerivedFromHlaClass(EmbeddedMessaging::get_hla_class_name())) {

        std::string interactionJson = interactionRoot.toJson();

        for (const std::string &federateName : federateNameSet) {

            const std::string embeddedMessagingHlaClassName =
              EmbeddedMessaging::get_hla_class_name() + "." + federateName;
            InteractionRoot::SP embeddedMessagingForNetworkFederateSP(
              new InteractionRoot(embeddedMessagingHlaClassName)
            );
            if (interactionRoot.isInstanceHlaClassDerivedFromHlaClass(C2WInteractionRoot::get_hla_class_name())) {
                embeddedMessagingForNetworkFederateSP->setParameter(
                        "federateSequence",
                        interactionRoot.getParameter("federateSequence")
                );
                embeddedMessagingForNetworkFederateSP->setFederateAppendedToFederateSequence(true);
            }
            embeddedMessagingForNetworkFederateSP->setParameter("command", "interaction");
            embeddedMessagingForNetworkFederateSP->setParameter(
                    "hlaClassName", interactionRoot.getInstanceHlaClassName()
            );
            embeddedMessagingForNetworkFederateSP->setParameter("messagingJson", interactionJson);

            if (time >= 0) {
                sendInteraction(*embeddedMessagingForNetworkFederateSP, time);
            } else {
                sendInteraction(*embeddedMessagingForNetworkFederateSP);
            }
        }
    }
}

void SynchronizedFederate::registerObject(ObjectRoot &objectRoot) {
    objectRoot.registerObject(getRTI());
}

void SynchronizedFederate::sendInteraction(
  const std::string &objectReflectorJson,
  const std::string &hlaClassName,
  const std::string &federateSequence,
  const StringSet &federateNameSet,
  double time
) {
    for(const std::string &federateName : federateNameSet) {
        const std::string embeddedMessagingHlaClassName =
          EmbeddedMessaging::get_hla_class_name() + "." + federateName;
        InteractionRoot::SP embeddedMessagingForNetworkFederateSP(new InteractionRoot(embeddedMessagingHlaClassName));
        embeddedMessagingForNetworkFederateSP->setParameter("command", "object");
        embeddedMessagingForNetworkFederateSP->setParameter("federateSequence", federateSequence);
        embeddedMessagingForNetworkFederateSP->setParameter("hlaClassName", hlaClassName);
        embeddedMessagingForNetworkFederateSP->setParameter("messagingJson", objectReflectorJson);

        if (time >= 0) {
            sendInteraction(*embeddedMessagingForNetworkFederateSP, time);
        } else {
            sendInteraction(*embeddedMessagingForNetworkFederateSP);
        }
    }
}

void SynchronizedFederate::enableTimeConstrained( void ) throw( RTI::FederateNotExecutionMember ){
    if ( !_timeConstrainedNotEnabled ) return;

    bool timeConstrainedEnabledNotCalled = true;
    while( timeConstrainedEnabledNotCalled ) {
        try {
            getRTI()->enableTimeConstrained();
            timeConstrainedEnabledNotCalled = false;
        } catch ( RTI::TimeConstrainedAlreadyEnabled & ) {
            return;
        } catch ( RTI::EnableTimeConstrainedPending & ) {
            timeConstrainedEnabledNotCalled = false;
        } catch ( RTI::FederateNotExecutionMember &f ) {
            throw f;
        } catch ( ... ) {
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
        }
    }

    tick();
    while( _timeConstrainedNotEnabled ) {
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
        tick();
    }
}

void SynchronizedFederate::enableTimeRegulation( double time, double lookahead )
    throw( RTI::InvalidFederationTime, RTI::InvalidLookahead, RTI::FederateNotExecutionMember ) {

    if ( !_timeRegulationNotEnabled ) return;

    bool timeRegulationEnabledNotCalled = true;
    while( timeRegulationEnabledNotCalled ) {
        try {
            getRTI()->enableTimeRegulation(  RTIfedTime( time ), RTIfedTime( lookahead )  );
            timeRegulationEnabledNotCalled = false;
        } catch ( RTI::TimeRegulationAlreadyEnabled & ) {
            return;
        } catch ( RTI::EnableTimeRegulationPending & ) {
            timeRegulationEnabledNotCalled = false;
        } catch ( RTI::FederateNotExecutionMember &f ) {
            throw f;
        } catch ( RTI::InvalidFederationTime &i ) {
            throw i;
        } catch ( RTI::InvalidLookahead &i ) {
            throw i;
        } catch ( ... ) {
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
        }
    }

    //  INITIAL TICK
    tick();
    while( _timeRegulationNotEnabled ) {
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
        tick();
    }

    setLookahead( lookahead );
}

void SynchronizedFederate::disableTimeRegulation()
 throw( RTI::RTIinternalError, RTI::FederateNotExecutionMember ){

    if ( _timeRegulationNotEnabled ) return;

        bool timeRegulationDisabledNotCalled = true;
        while( timeRegulationDisabledNotCalled ) {
            try {
                getRTI()->disableTimeRegulation();
                _timeRegulationNotEnabled = true;
                timeRegulationDisabledNotCalled = false;
            } catch ( RTI::TimeRegulationWasNotEnabled & ) {
                return;
            } catch ( RTI::SaveInProgress & f) {
                timeRegulationDisabledNotCalled = false;
                //throw f;
            } catch ( RTI::ConcurrentAccessAttempted & f) {
                //throw f;
                timeRegulationDisabledNotCalled = false;
            } catch ( RTI::RestoreInProgress & f ) {
                timeRegulationDisabledNotCalled = false;
                //throw f;
            } catch ( RTI::FederateNotExecutionMember &i ) {
                throw i;
            } catch ( RTI::RTIinternalError &i ) {
                throw i;
            } catch ( ... ) {
    #ifdef _WIN32
                Sleep( 500 );
    #else
                usleep( 500000 );
    #endif
            }
        }

        tick();
        while( !_timeRegulationNotEnabled ) {
    #ifdef _WIN32
                Sleep( 500 );
    #else
                usleep( 500000 );
    #endif
            tick();
        }
}

void SynchronizedFederate::resignFederationExecution( RTI::ResignAction resignAction ) {
    bool federationNotResigned = true;
    int resignAttempts = 10;
    while( federationNotResigned ) {
        try {
            getRTI()->resignFederationExecution( resignAction );
            federationNotResigned = false;
        } catch ( RTI::InvalidResignAction &i ) {
            std::cerr << "WARNING:  Invalid resign action when attempting to resign federation.  Changing resign action to DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES." << std::endl;
            resignAction = RTI::DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES;
        } catch ( RTI::FederateNotExecutionMember f ) {
            std::cerr << "WARNING:  While resigning federation:  federate not execution member." << std::endl;
            return;
        } catch ( RTI::FederateOwnsAttributes f ) {
            std::cerr << "WARNING:  While resigning federation:  federate owns attributes.  Releasing attributes." << std::endl;
            resignAction = static_cast< RTI::ResignAction >(  static_cast< int >( resignAction ) | static_cast< int >( RTI::RELEASE_ATTRIBUTES )  );
        } catch ( ... ) {
            if (resignAttempts == 10) {
                std::cerr << "WARNING:  problem encountered while resigning federation execution:  retry" << std::endl;
            }

            if( resignAttempts-- < 1){
                std::cerr << "Resigned Failed. Exiting from the Federation" << std::endl;
                federationNotResigned = false;
            } else {
#ifdef _WIN32
                Sleep( 500 );
#else
                usleep( 500000 );
#endif
                std::cerr << ".";
            }
        }
    }
}

void SynchronizedFederate::achieveSynchronizationPoint( const std::string &label )
        throw( RTI::FederateNotExecutionMember, RTI::RTIinternalError ) {
    bool synchronizationPointNotAccepted = true;
    while( synchronizationPointNotAccepted ) {
        try {
            std::cout << "Synchronizing on label \"" << label << "\"" << std::endl;
            getRTI()->synchronizationPointAchieved( label.c_str() );
            while(  _achievedSynchronizationPoints.find( label ) == _achievedSynchronizationPoints.end()  ) {
#ifdef _WIN32
                Sleep( 500 );
#else
                usleep( 500000 );
#endif
                tick();
            }
            synchronizationPointNotAccepted = false;
        } catch ( RTI::FederateNotExecutionMember &f ) {
            throw f;
        } catch ( RTI::SynchronizationPointLabelWasNotAnnounced & ) {
            if (  _achievedSynchronizationPoints.find( label ) != _achievedSynchronizationPoints.end()  ) {
                synchronizationPointNotAccepted = false;
            } else {
                try {
                    tick();
                } catch ( RTI::RTIinternalError &r ) {
                    throw r;
                } catch ( ... ) {
#ifdef _WIN32
                    Sleep( 500 );
#else
                    usleep( 500000 );
#endif
                }
            }
        } catch( ... ) {
#ifdef _WIN32
            Sleep( 500 );
#else
            usleep( 500000 );
#endif
        }
    }
}

void SynchronizedFederate::receiveEmbeddedInteraction(EmbeddedMessaging::SP embeddedMessagingSP, double timestamp) {
    const std::string command = embeddedMessagingSP->get_command();
    const std::string hlaClassName = embeddedMessagingSP->get_hlaClassName();
    const std::string federateSequence = embeddedMessagingSP->get_federateSequence();

    if (command == "interaction") {
        if (!InteractionRoot::get_is_soft_subscribed(hlaClassName)) {
            BOOST_LOG_SEV( get_logger(), warning ) << "SynchronizedFederate.receiveEmbeddedInteraction: "
              << "interaction class \"" << hlaClassName << "\" not soft subscribed";
            return;
        }

        InteractionRoot::SP embeddedInteractionSP =
          InteractionRoot::fromJson(embeddedMessagingSP->get_messagingJson());
        embeddedInteractionSP->setTime(embeddedMessagingSP->getTime());

        receiveInteractionAux(embeddedInteractionSP, timestamp);
        return;
    }

    if (command == "object") {
        if (!ObjectRoot::get_is_soft_subscribed(hlaClassName)) {
            BOOST_LOG_SEV( get_logger(), warning ) << "SynchronizedFederate.receiveEmbeddedInteraction: "
              << "object class \"" << hlaClassName << "\" neither subscribed nor soft subscribed";
            return;
        }

        ObjectRoot::ObjectReflector::SP objectReflectorSP =
          ObjectRoot::fromJson(embeddedMessagingSP->get_messagingJson());
        objectReflectorSP->setTime(embeddedMessagingSP->getTime());
        objectReflectorSP->setFederateSequence(federateSequence);

        const ClassAndPropertyNameSet &attributeClassAndPropertyNameSet =
          *ObjectRoot::get_soft_subscribed_class_and_property_name_set_sp(objectReflectorSP->getHlaClassName());

        ObjectRoot::ClassAndPropertyNameValueSPMap &classAndPropertyNameValueSPMap =
          objectReflectorSP->getClassAndPropertyNameValueSPMap();

        ClassAndPropertyNameSet keys;
        for(
          ObjectRoot::ClassAndPropertyNameValueSPMap::const_iterator cnmCit = classAndPropertyNameValueSPMap.begin() ;
          cnmCit != classAndPropertyNameValueSPMap.end() ;
          ++cnmCit
        ) {
            keys.insert(cnmCit->first);
        }

        for(const ClassAndPropertyName &classAndPropertyName: keys) {
            if (attributeClassAndPropertyNameSet.find(classAndPropertyName) == attributeClassAndPropertyNameSet.end()) {
                classAndPropertyNameValueSPMap.erase(classAndPropertyName);
            }
        }

        addObjectReflectorSP(objectReflectorSP);
        return;
    }

    BOOST_LOG_SEV( get_logger(), warning ) << "SynchronizedFederate.receiveEmbeddedInteraction: "
      << "unrecognized command \"" << command << "\"";
}


/**
 * Returns the current time for this federate.
 *
 * @return the current time for this federate
 */
double SynchronizedFederate::getCurrentTime( void ) {
    RTIfedTime fedTime;

    bool timeNotAcquired = true;
    while( timeNotAcquired ) {
        try {
            getRTI()->queryFederateTime( fedTime );
            timeNotAcquired = false;
        } catch ( RTI::FederateNotExecutionMember & ) {
            std::cerr << "SynchronizedFederate:  getCurrentTime:  ERROR:  Federate not execution member" << std::endl;
            return -1;
        } catch ( ... ) {
            std::cerr << "SynchronizedFederate:  getCurrentTime:  Exception caught:  " << std::endl;
            return -1;
        }
    }

    return fedTime.getTime();
}

/**
 * Returns the current Lower Bound on Time-Stamps (LBTS) for this federate.
 *
 * @return the current time for this federate
 */
double SynchronizedFederate::getLBTS( void ) {
    RTIfedTime lbtsTime;

    bool timeNotAcquired = true;
    while( timeNotAcquired ) {
        try {
            getRTI()->queryLBTS( lbtsTime );
            timeNotAcquired = false;
        } catch ( RTI::FederateNotExecutionMember & ) {
            std::cerr << "SynchronizedFederate:  getLBTS:  ERROR:  Federate not execution member" << std::endl;
            return -1;
        } catch ( ... ) {
            std::cerr << "SynchronizedFederate:  getLBTS:  Exception caught:  " << std::endl;
            return -1;
        }
    }

    return lbtsTime.getTime();
}

/**
 * When sending an interaction in timestamp order, we should use
 * currentTime+Lookahead or LBTS whichever is greater. Current Portico RTI
 * implementation dictates to use a timestamp which is greater than or
 * equal to federate's LBTS.
 *
 * @return the timestamp to use for outgoing TSO interactions
 */
double SynchronizedFederate::getMinTSOTimestamp( void ) {
    RTIfedTime lbtsTime;
    RTIfedTime fedTime;

    bool timeNotAcquired = true;
    while( timeNotAcquired ) {
        try {
            getRTI()->queryFederateTime( fedTime );
            getRTI()->queryLBTS( lbtsTime );
            timeNotAcquired = false;
        } catch ( RTI::FederateNotExecutionMember & ) {
            std::cerr << "SynchronizedFederate:  getMinTSOTimestamp:  ERROR:  Federate not execution member" << std::endl;
            return -1;
        } catch ( ... ) {
            std::cerr << "SynchronizedFederate:  getMinTSOTimestamp:  Exception caught:  " << std::endl;
            return -1;
        }
    }

    fedTime += getLookahead();

    if(fedTime >= lbtsTime)
        return fedTime.getTime();
    else
        return lbtsTime.getTime();
}

void SynchronizedFederate::receiveInteraction(
 RTI::InteractionClassHandle theInteraction,
 const RTI::ParameterHandleValuePairSet& theParameters,
 const char *theTag
)
 throw ( RTI::InteractionClassNotKnown, RTI::InteractionParameterNotKnown, RTI::FederateInternalError) {

    if ( getMoreATRs() ) {
        // Himanshu: We normally use only TSO updates, so this shouldn't be
        // called, but due to an RTI bug, it seemingly is getting called. So,
        // for now, use the federate's current time or LBTS whichever is greater
        // as the timestamp
        double assumedTimestamp = std::max(getLBTS(), getCurrentTime());

        InteractionRoot::SP interactionRootSP = InteractionRoot::create_interaction(theInteraction, theParameters);
        if (interactionRootSP->isInstanceOfHlaClass(SimEnd::get_hla_class_name())) {
            exitImmediately();
        }

        if (interactionRootSP->isInstanceOfHlaClass(AddProxy::get_hla_class_name())) {
            AddProxy::SP addProxySP = boost::static_pointer_cast<AddProxy>(interactionRootSP);
            addProxy(addProxySP->get_federateName(), addProxySP->get_proxyFederateName());
            return;
        }

        if (interactionRootSP->isInstanceOfHlaClass(DeleteProxy::get_hla_class_name())) {
            DeleteProxy::SP deleteProxySP = boost::static_pointer_cast<DeleteProxy>(interactionRootSP);
            deleteProxy(deleteProxySP->get_federateName());
            return;
        }

        receiveInteractionAux(interactionRootSP, assumedTimestamp);
    }
}

void SynchronizedFederate::run( void ) {

    std::cout << "run called." << std::endl;
    _currentTime = getCurrentTime();
    if ( _currentTime < 0 ) return;

    double timeRequest = -1;
    while( true ) {
        AdvanceTimeRequest advanceTimeRequest = takeNextAdvanceTimeRequest();
        if ( advanceTimeRequest.isNull() ) break;  // NO MORE ADVANCE TIME REQUESTS (REMEMBER, WE'RE SINGLE THREADED)

        timeRequest = advanceTimeRequest.getRequestedTime();

        advanceTime( timeRequest );

        advanceTimeRequest.getATRCallback().execute();
    }

//    noMoreATRs();

//    while( getNextInteraction() != 0 ); // EMPTY THE QUEUE

    exitGracefully();
}

void SynchronizedFederate::advanceTime( double time ) {

    if ( getTimeAdvanceMode() != SF_TIME_ADVANCE_REQUEST_AVAILABLE && getTimeAdvanceMode() != SF_NEXT_EVENT_REQUEST_AVAILABLE &&  time <= _currentTime ) return;

    setTimeAdvanceNotGranted( true );

    bool tarNotCalled = true;
    while( tarNotCalled ) {
        try {
            if ( getTimeAdvanceMode() == SF_TIME_ADVANCE_REQUEST ) {
                getRTI()->timeAdvanceRequest(  RTIfedTime( time )  );
            }
            else if ( getTimeAdvanceMode() == SF_TIME_ADVANCE_REQUEST_AVAILABLE ) {
                getRTI()->timeAdvanceRequestAvailable(  RTIfedTime( time )  );
            }
            else if ( getTimeAdvanceMode() == SF_NEXT_EVENT_REQUEST ) {
                getRTI()->nextEventRequest(  RTIfedTime( time )  );
            }
            else if ( getTimeAdvanceMode() == SF_NEXT_EVENT_REQUEST_AVAILABLE ) {
                getRTI()->nextEventRequestAvailable(  RTIfedTime( time )  );
            }
            tarNotCalled = false;
        } catch ( RTI::FederationTimeAlreadyPassed &f ) {
            std::cerr << "Time already passed detected." << std::endl;
            setTimeAdvanceNotGranted( false );
            tarNotCalled = false;
        } catch ( ... ) { }
    }

    while( getTimeAdvanceNotGranted() ) {
        tick();
#ifdef _WIN32
        Sleep( 10 );
#else
        usleep( 10000 );
#endif
    }

    _currentTime = time;
}

// void SynchronizedFederate::createLog(
//         RTI::ObjectHandle theObject,
//         const RTI::AttributeHandleValuePairSet& theAttributes,
//         double time)
// {
//     if(ObjectRoot::getSubAttributeLogMap().empty()) return;
//     std::string objectName = ObjectRoot::getObject( theObject )->getClassName() ;
//     for(RTI::ULong i=0; i<theAttributes.size(); ++i)
//     {
//         std::string attribute = ObjectRoot::get_attribute_name(theAttributes.getHandle(i));
//         std::map<std::string, std::string>::iterator pos = ObjectRoot::getSubAttributeLogMap().find(attribute);
//         if(pos == ObjectRoot::getSubAttributeLogMap().end()) continue;
//         std::string loglevel = (*pos).second;
//         std::string id = objectName+"_"+attribute+"_sub_"+_federateId;
//         static RTI::ULong valueLength;
//         char* value = theAttributes.getValuePointer( i, valueLength);
//         std::string ptype="";
//         ObjectRoot::DatamemberTypeMap::iterator it = ObjectRoot::getDatamemberTypeMap().find( attribute );
//         if ( it != ObjectRoot::getDatamemberTypeMap().end() )
//             ptype = (*it).second;
//         _logger->addLog(id,attribute,std::string(value, valueLength),ptype,time,loglevel);
//     }
// }

#if __cplusplus >= 201703L
#undef MultiArgThrow17
#undef Throw17
#undef throw
#endif
