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

#ifndef _SYNCHRONIZED_FEDERATE_HPP
#define _SYNCHRONIZED_FEDERATE_HPP

#ifndef RTI_USES_STD_FSTREAM
#define RTI_USES_STD_FSTREAM
#endif

#include <fstream>
#include <sys/stat.h>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <cstdlib>

#include <iostream>

#define BOOST_LOG_DYN_LINK

#include <boost/log/expressions/keyword.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#ifndef CPSWT_TEST

#if __cplusplus >= 201703L
#define MultiArgThrow17
#define Throw17 noexcept
#define throw(...) __VA_OPT__(MultiArg)##Throw17
#endif

#include "NullFederateAmbassador.hh"

#if __cplusplus >= 201703L
#undef MultiArgThrow17
#undef Throw17
#undef throw
#endif

#endif // CPSWT_TEST

#include "InteractionRoot.hpp"
#include "ObjectRoot.hpp"

#include "InteractionRoot_p/AddProxy.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/EmbeddedMessaging.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/FederateResignInteraction.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/FederateJoinInteraction.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/SimulationControl_p/SimEnd.hpp"
#include "InteractionRoot_p/DeleteProxy.hpp"


#include "FederateLogger.hpp"

#include "FederateConfig.h"

#ifndef C2W_FED_LOGGER_CLS
#define C2W_FED_LOGGER_CLS C2WConsoleLogger
#endif 

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#if __cplusplus >= 201703L
#define MultiArgThrow17
#define Throw17 noexcept
#define throw(...) __VA_OPT__(MultiArg)##Throw17
#endif

namespace logging = boost::log;
namespace logging_source = boost::log::sources;
namespace attrs = boost::log::attributes;

using namespace logging::trivial;

class SynchronizedFederate : public NullFederateAmbassador {

public:
    typedef logging_source::severity_logger< severity_level > severity_logger;

    using AddProxy = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::AddProxy;
    using C2WInteractionRoot = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot;
    using DeleteProxy = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::DeleteProxy;
    using EmbeddedMessaging = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::EmbeddedMessaging;
    using FederateJoinInteraction =
      ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::FederateJoinInteraction;
    using FederateResignInteraction =
      ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::FederateResignInteraction;
    using InteractionRoot = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot;
    using ObjectRoot = ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot;
    using ObjectReflector = ObjectRoot::ObjectReflector;
    using ObjectReflectorSPComparator = ObjectRoot::ObjectReflectorSPComparator;
    using SimEnd = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::SimulationControl_p::SimEnd;

    typedef boost::shared_ptr<std::string> StringSP;

    typedef std::set<std::string> StringSet;
    typedef boost::shared_ptr<StringSet> StringSetSP;

    typedef std::list<std::string> StringList;

    typedef std::map<std::string, StringSP> StringStringSPMap;
    typedef std::map<std::string, StringSetSP> StringStringSetSPMap;

    typedef std::list<InteractionRoot::SP> InteractionRootSPList;

    typedef std::map<double, InteractionRootSPList> DoubleToInteractionSPListMap;
    typedef std::map<std::string, InteractionRootSPList> StringToInteractionSPListMap;

    typedef std::set<double> DoubleSet;

    static const std::string &get_federation_manager_name() {
        static const std::string federationManagerName("FederationManager");
        return federationManagerName;
    }

    static const std::string &get_ready_to_populate_synch() {
        static const std::string readyToPopulateSynch("readyToPopulate");
        return readyToPopulateSynch;
    }

    static const std::string &get_ready_to_run_synch() {
        static const std::string readyToRunSynch("readyToRun");
        return readyToRunSynch;
    }

    static const std::string &get_ready_to_resign_synch() {
        static const std::string readyToResignSynch("readyToResign");
        return readyToResignSynch;
    }

    enum TimeAdvanceMode {
        SF_TIME_ADVANCE_REQUEST,
        SF_NEXT_EVENT_REQUEST,
        SF_TIME_ADVANCE_REQUEST_AVAILABLE,
        SF_NEXT_EVENT_REQUEST_AVAILABLE
    };

private:
    StringStringSPMap federateNameToProxyFederateNameSPMap;
    StringStringSetSPMap proxyFederateNameToFederateNameSetSPMap;

    DoubleToInteractionSPListMap timeToSentInteractionSPListMap;

protected:
    bool hasProxy(const std::string &federateName) {
        return federateNameToProxyFederateNameSPMap.find(federateName) != federateNameToProxyFederateNameSPMap.end();
    }

    const StringSP getProxyFor(const std::string &federateName) {
        StringStringSPMap::const_iterator ssmCit = federateNameToProxyFederateNameSPMap.find(federateName);
        return ssmCit == federateNameToProxyFederateNameSPMap.end() ? StringSP() : ssmCit->second;
    }

    const StringSetSP getProxiedFederateNameSet(const std::string &federateName) {
        StringStringSetSPMap::const_iterator ssmCit = proxyFederateNameToFederateNameSetSPMap.find(federateName);
        return ssmCit == proxyFederateNameToFederateNameSetSPMap.end() ? StringSetSP() : ssmCit->second;
    }

    const StringSetSP getProxiedFederateNameSet() {
        return getProxiedFederateNameSet(getFederateType());
    }

    void queueInteraction(InteractionRoot::SP &interactionRootSP, double time) {
        if (timeToSentInteractionSPListMap.find(time) == timeToSentInteractionSPListMap.end()) {
            timeToSentInteractionSPListMap.insert(std::make_pair(time, InteractionRootSPList()));
        }
        timeToSentInteractionSPListMap[time].emplace_back(interactionRootSP);
    }

private:
    void addProxy(const std::string &federateName, const std::string &proxyFederateName);
    void deleteProxy(const std::string &federateName);

protected:
    void addProxiedFederate(const std::string &federateName);
    void deleteProxiedFederate(const std::string &federateName);

    RTI::RTIambassador *_rti;

    double _currentTime;

    bool exitCondition;

    void setStatus(int status) {
        _status = status;
    }

    int getStatus() {
        return _status;
    }

private:

    int _status;

    std::string _federationId;
//    std::string _lockFileName;

    std::string _federateType;
    std::string _federateId;

    std::string _federationJsonFileName;
    std::string _federateDynamicMessagingClassesJsonFileName;

    bool _isLateJoiner;

    StringSet _achievedSynchronizationPoints;

    bool _timeConstrainedNotEnabled;
    bool _timeRegulationNotEnabled;
    bool _timeAdvanceNotGranted;
    bool _simEndNotPubsub;

    double _lookahead;
    double _stepSize;
    TimeAdvanceMode _timeAdvanceMode;

    static severity_logger &get_logger_aux() {
        static severity_logger logger;
        logging::add_common_attributes();
        return logger;
    }

public:
    static severity_logger &get_logger() {
        static severity_logger &logger = get_logger_aux();
        return logger;
    }

    RTI::RTIambassador *getRTI( void ) {
        return _rti;
    }

    void setFederationId(const std::string &federationId) {
        _federationId = federationId;
    }
    std::string getFederationId( void ) const {
        return _federationId;
    }

    void setFederateType( const std::string &federateType ) {
        _federateType = federateType;
    }
    std::string getFederateType( void ) const {
        return _federateType;
    }

    void setFederateId(const std::string &federateId) {
        _federateId = federateId;
    }
    std::string getFederateId( void ) const {
        return _federateId;
    }

    void setFederationJsonFileName( const std::string &federationJsonFileName ) {
        _federationJsonFileName = federationJsonFileName;
    }
    std::string getFederationJsonFileName( void ) const {
        return _federationJsonFileName;
    }

    void setFederateDynamicMessagingClassesJsonFileName(
      const std::string &federateDynamicMessagingClassesJsonFileName
    ) {
        _federateDynamicMessagingClassesJsonFileName = federateDynamicMessagingClassesJsonFileName;
    }

    bool get_IsLateJoiner( void ) const { return _isLateJoiner; }

    void setLookahead( double lookahead ) {
        _lookahead = lookahead;
    }
    double getLookahead() {
        return _lookahead;
    }

    void setStepSize(double stepSize) {
        _stepSize = stepSize;
    }
    double getStepSize(void) {
        return _stepSize;
    }

    void setTimeAdvanceMode(TimeAdvanceMode timeAdvanceMode) {
        _timeAdvanceMode = timeAdvanceMode;
    }
    TimeAdvanceMode getTimeAdvanceMode() {
        return _timeAdvanceMode;
    }

private:
    bool getTimeAdvanceNotGranted( void ) {
        return _timeAdvanceNotGranted;
    }
    void setTimeAdvanceNotGranted(bool timeAdvanceNotGranted) {
        _timeAdvanceNotGranted = timeAdvanceNotGranted;
    }

public:
    SynchronizedFederate( void ):
      _moreATRs(true),
      _rti(nullptr),

      exitCondition(false),
      _status(0),

      _federateId( "" ),
      _federateType(""),
      _federationId( "" ),

      _isLateJoiner(false),

      _timeConstrainedNotEnabled( true ),
      _timeRegulationNotEnabled( true ),
      _simEndNotPubsub( true ),

      _currentTime( 0 ),
      _lookahead( 0 )
    {
         setpgid( 0, 0 );
//          _lockFileName = getenv( "EXEDIR" );
//          if ( !_lockFileName.empty() ) {
//              _lockFileName += "/";
//          }
//          _lockFileName += "__lock__";

         _timeAdvanceMode = SF_TIME_ADVANCE_REQUEST;
    }

    SynchronizedFederate( FederateConfig *fedconfig) :
      _moreATRs(true), _rti(nullptr), exitCondition(false), _status(0) {
        this->_federationId = fedconfig->federationId;
        this->_federateType = fedconfig->federateType;
        this->_federateId = fedconfig->federateType + std::to_string(rand());

        this->_isLateJoiner= fedconfig->isLateJoiner;

        this->_federationJsonFileName = fedconfig->federationJsonFileName;
        this->_federateDynamicMessagingClassesJsonFileName = fedconfig->federateDynamicMessagingClassesJsonFileName;

        this->_timeConstrainedNotEnabled = true;
        this->_timeRegulationNotEnabled = true;
        this->_simEndNotPubsub = true;

        setLookahead(fedconfig->lookahead);
        setStepSize(fedconfig->stepSize);

        setpgid( 0, 0 );

        this->_timeAdvanceMode = SF_TIME_ADVANCE_REQUEST;
    }

    virtual ~SynchronizedFederate() throw (RTI::FederateInternalError) {
         destroyRTI();
    }

    void createRTI( void );

    void destroyRTI( void ) {
        // delete _rti;
        _rti = nullptr;
    }

    void initializeMessaging() {
        InteractionRoot::init(getRTI());
        ObjectRoot::init(getRTI());
    }

    void initializeDynamicMessaging(
      std::istream &federationJsonInputStream, std::istream &federateDynamicMessagingClassesJsonInputStream
    ) {
        InteractionRoot::loadDynamicClassFederationData(
          federationJsonInputStream, federateDynamicMessagingClassesJsonInputStream
        );

        federationJsonInputStream.seekg(0);
        federateDynamicMessagingClassesJsonInputStream.seekg(0);

        ObjectRoot::loadDynamicClassFederationData(
          federationJsonInputStream, federateDynamicMessagingClassesJsonInputStream
        );

        initializeMessaging();
    }

    void initializeDynamicMessaging(
      const std::string &federationJsonFileName,
      const std::string &federateDynamicMessagingClassesJsonFileName
    );

    void notifyFederationOfJoin();
    void notifyFederationOfResign();

    void ensureSimEndPubsub( void ) {
        if ( _simEndNotPubsub ) {
            // Auto-subscribing also ensures that there is no filter set for SimEnd
            SimEnd::subscribe_interaction( getRTI() );
            SimEnd::publish_interaction( getRTI() );
            _simEndNotPubsub = false;
        }
    }

    // void joinFederation( const std::string &federation_id, const std::string &federate_id, bool ignoreLockFile = true );
    void joinFederation();

    InteractionRoot::SP updateFederateSequence(InteractionRoot &interactionRoot);

    void sendInteraction(InteractionRoot &interactionRoot, const StringSet &federateNameSet, double time);

    void sendInteraction(InteractionRoot &interactionRoot, const std::string &federateName, double time) {

        std::set<std::string> stringSet;
        stringSet.emplace(federateName);
        sendInteraction(interactionRoot, stringSet, time);
    }

    void sendInteraction( InteractionRoot &interactionRoot, double time ) {

        if (interactionRoot.getIsPublished()) {
            InteractionRoot::SP newInteractionRootSP = updateFederateSequence(interactionRoot);
            queueInteraction(newInteractionRootSP, time);
//            newInteractionRootSP->sendInteraction(getRTI());
        }

        sendInteraction(interactionRoot, *interactionRoot.getFederateNameSoftPublishSetSP(), time);
    }

    void sendInteraction(InteractionRoot &interactionRoot) {

        if (interactionRoot.getIsPublished()) {
            InteractionRoot::SP newInteractionRootSP = updateFederateSequence(interactionRoot);
            newInteractionRootSP->sendInteraction(getRTI());
        }
        sendInteraction(interactionRoot, *interactionRoot.getFederateNameSoftPublishSetSP(), -1);
    }

    void sendInteraction(InteractionRoot &interactionRoot, const std::string &federateName) {

        std::set<std::string> stringSet;
        stringSet.emplace(federateName);
        sendInteraction(interactionRoot, stringSet, -1);
    }

    void registerObject(ObjectRoot &objectRoot);

    void unregisterObject(ObjectRoot &objectRoot) {
        objectRoot.unregisterObject(getRTI());
    }

    void sendInteraction(
      const std::string &objectReflectorJson,
      const std::string &hlaClassName,
      const std::string &federateSequence,
      const StringSet &federateNameSet,
      double time
    );

    void sendInteraction(ObjectReflector &objectReflector, const StringSet &federateNameSet, double time) {
        sendInteraction(
          objectReflector.toJson(time),
          objectReflector.getHlaClassName(),
          objectReflector.getFederateSequence(),
          federateNameSet,
          time
        );
    }

    void sendInteraction(ObjectRoot &objectRoot, const StringSet &federateNameSet, double time, bool force) {
        sendInteraction(
          objectRoot.toJson(force, time), objectRoot.getInstanceHlaClassName(), std::string("[]"), federateNameSet, time
        );
    }

    void sendInteraction(ObjectRoot &objectRoot, const StringSet &federateNameSet, double time) {
        sendInteraction(objectRoot, federateNameSet, time, false);
    }

    void sendInteraction(ObjectReflector &objectReflector, const std::string &federateName, double time) {
        StringSet stringSet;
        stringSet.emplace(federateName);
        sendInteraction(objectReflector, stringSet, time);
    }

    void sendInteraction(ObjectRoot &objectRoot, const std::string &federateName, double time) {
        StringSet stringSet;
        stringSet.emplace(federateName);
        sendInteraction(objectRoot, stringSet, time);
    }

    void sendInteraction(ObjectReflector &objectReflector, const std::string &federateName) {
        std::set<std::string> stringSet;
        stringSet.emplace(federateName);
        sendInteraction(objectReflector, stringSet, -1);
    }

    void sendInteraction(ObjectRoot &objectRoot, const std::string &federateName) {
        std::set<std::string> stringSet;
        stringSet.emplace(federateName);
        sendInteraction(objectRoot, stringSet, -1);
    }

    void updateAttributeValues(ObjectRoot &objectRoot, double time, bool force) {
        ClassAndPropertyNameSet attributesToBeUpdatedClassAndPropertyNameSet =
                objectRoot.getAttributesToBeUpdatedClassAndPropertyNameSet();

        objectRoot.updateAttributeValues(getRTI(), time, force);

        objectRoot.restoreAttributesToBeUpdated(attributesToBeUpdatedClassAndPropertyNameSet);
        sendInteraction(objectRoot, *objectRoot.getFederateNameSoftPublishSetSP(), time, force);
    }

    void updateAttributeValues(ObjectRoot &objectRoot, double time) {
        updateAttributeValues(objectRoot, time, false);
    }

    void updateAttributeValues(ObjectRoot &objectRoot, bool force) {
        ClassAndPropertyNameSet attributesToBeUpdatedClassAndPropertyNameSet =
                objectRoot.getAttributesToBeUpdatedClassAndPropertyNameSet();

        objectRoot.updateAttributeValues(getRTI(), force);

        objectRoot.restoreAttributesToBeUpdated(attributesToBeUpdatedClassAndPropertyNameSet);
        sendInteraction(objectRoot, *objectRoot.getFederateNameSoftPublishSetSP(), -1, force);
    }

    void updateAttributeValues(ObjectRoot &objectRoot) {
        updateAttributeValues(objectRoot, false);
    }


    virtual void timeConstrainedEnabled( const RTI::FedTime &t )
     throw( RTI::InvalidFederationTime, RTI::EnableTimeConstrainedWasNotPending, RTI::FederateInternalError ) {
        _timeConstrainedNotEnabled = false;
    }

    void enableTimeConstrained( void ) throw( RTI::FederateNotExecutionMember );


    virtual void timeRegulationEnabled( const RTI::FedTime &t )
     throw ( RTI::InvalidFederationTime, RTI::EnableTimeRegulationWasNotPending, RTI::FederateInternalError ) {
        _timeRegulationNotEnabled = false;
    }

    void enableTimeRegulation( double time, double lookahead )
     throw( RTI::InvalidFederationTime, RTI::InvalidLookahead, RTI::FederateNotExecutionMember );

    void enableTimeRegulation( double lookahead )
     throw( RTI::InvalidFederationTime, RTI::InvalidLookahead, RTI::FederateNotExecutionMember ) {
        enableTimeRegulation( 0, lookahead );
    }

    void tick(void) {
        try {
            getRTI()->tick();
        } catch ( RTI::RTIinternalError &r ) {
            throw r;
        } catch( ... ) { }
    }


    void disableTimeRegulation()
     throw( RTI::RTIinternalError, RTI::FederateNotExecutionMember );


    void enableAsynchronousDelivery( void ) {
        bool asynchronousDeliveryNotEnabled = true;
        while(asynchronousDeliveryNotEnabled) {
            try {
                getRTI()->enableAsynchronousDelivery();
                asynchronousDeliveryNotEnabled = false;
            } catch (RTI::FederateNotExecutionMember &f) {
                BOOST_LOG_SEV( get_logger(), error ) <<
                  "ERROR:  Could not enable asynchronous delivery:  Federate Not Execution Member";
                return;
            } catch (RTI::AsynchronousDeliveryAlreadyEnabled &a) {
                return;
            } catch (...) {
                BOOST_LOG_SEV( get_logger(), warning ) <<
                  "WARNING:  problem encountered enabling asynchronous delivery:  retry";
#ifdef _WIN32
                Sleep( 500 );
#else
                usleep( 500000 );
#endif
            }
        }
    }


    void resignFederationExecution( RTI::ResignAction resignAction );
    void resignFederationExecution( void ) {
        resignFederationExecution( RTI::DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES );
    }

public:
    virtual void federationSynchronized( const char *label ) throw( RTI::FederateInternalError ) {
        BOOST_LOG_SEV( get_logger(), info) << "federationSynchronized on label \"" << label << "\"";
        _achievedSynchronizationPoints.insert( label );
    }

    void readyToPopulate( void ) throw( RTI::FederateNotExecutionMember, RTI::RTIinternalError ) {
        achieveSynchronizationPoint( get_ready_to_populate_synch() );
    }
    void readyToRun( void ) throw( RTI::FederateNotExecutionMember, RTI::RTIinternalError ) {
        achieveSynchronizationPoint( get_ready_to_run_synch() );
    }
    void readyToResign( void ) throw( RTI::FederateNotExecutionMember, RTI::RTIinternalError ) {
        achieveSynchronizationPoint( get_ready_to_resign_synch() );
    }
    void achieveSynchronizationPoint( const std::string &label )
     throw( RTI::FederateNotExecutionMember, RTI::RTIinternalError );

    virtual void timeAdvanceGrant( const RTI::FedTime &fedTime )
     throw( RTI::InvalidFederationTime, RTI::TimeAdvanceWasNotInProgress, RTI::FederateInternalError ) {
        _timeAdvanceNotGranted = false;
    }

    double getCurrentTime( void );
    double getLBTS( void );
    double getMinTSOTimestamp( void );
    double getCurrentTimeLocal( void ) {
        return _currentTime;
    }

    class ATRCallback {
    public:
        typedef boost::shared_ptr< ATRCallback > SP;
        virtual void execute( void ) = 0;
        virtual SP clone( void ) = 0;
        virtual ~ATRCallback() {}
    };

    //template< typename T >
    //class ATRCallback : public ATRCallbackBase {
    //private:
    //    T _executor;
    //public:
    //    ATRCallback( const T &executor) : _executor( executor ) { }
    //    void execute( void ) {
    //
    //    }
    //};

private:
    typedef std::multimap< double, ATRCallback::SP > ATRQueue;
    ATRQueue _atrQueue;
    bool _moreATRs;

    void noMoreATRs( void ) { _moreATRs = false; }

    class AdvanceTimeRequest {
    private:
        double _requestedTime;
        ATRCallback::SP _atrCallbackSP;

    public:
        AdvanceTimeRequest( void ) :
         _requestedTime( -1 ), _atrCallbackSP( (ATRCallback *)0 ) { }
        AdvanceTimeRequest( ATRQueue::value_type init ) :
         _requestedTime( init.first ), _atrCallbackSP( init.second ) { }
        AdvanceTimeRequest( double requestedTime, ATRCallback &atrCallback ) :
         _requestedTime( requestedTime ), _atrCallbackSP( atrCallback.clone() ) { }

        bool isNull( void ) { return _atrCallbackSP == 0; }
        void setNull( void ) { _atrCallbackSP = ATRCallback::SP( (ATRCallback *)0 ); }
        double getRequestedTime( void ) { return _requestedTime; }
        ATRCallback &getATRCallback( void ) { return *_atrCallbackSP; }

        operator ATRQueue::value_type( void ) {
            return std::make_pair( _requestedTime, _atrCallbackSP );
        }
    };

public:
    bool getMoreATRs( void ) {
        return _moreATRs;
    }

    void putAdvanceTimeRequest( double time, ATRCallback &atrCallback ) {
        _atrQueue.insert(  std::make_pair( time, atrCallback.clone() )  );
    }

private:
    AdvanceTimeRequest takeNextAdvanceTimeRequest( void ) {
        if ( _atrQueue.empty() ) return AdvanceTimeRequest();
        AdvanceTimeRequest advanceTimeRequest( *_atrQueue.begin() );
        _atrQueue.erase( _atrQueue.begin() );
        return advanceTimeRequest;
    }

    class InteractionRootSPComparator {
    public:
        bool operator()(
          const InteractionRoot::SP &interactionRootSP1, const InteractionRoot::SP &interactionRootSP2
        ) const {
            if ( interactionRootSP1->getTime() < interactionRootSP2->getTime() ) {
                return true;
            } else if ( interactionRootSP1->getTime() > interactionRootSP2->getTime() ) {
                return false;
            } else {
                boost::shared_ptr< C2WInteractionRoot > c2wInteractionRootSP1(   boost::static_pointer_cast< C2WInteractionRoot >( interactionRootSP1 )  );
                boost::shared_ptr< C2WInteractionRoot > c2wInteractionRootSP2(   boost::static_pointer_cast< C2WInteractionRoot >( interactionRootSP2 )  );
                if ( c2wInteractionRootSP1 != 0 && c2wInteractionRootSP2 != 0 ) {
                    if ( c2wInteractionRootSP1->get_actualLogicalGenerationTime() < c2wInteractionRootSP2->get_actualLogicalGenerationTime() ) {
                        return true;
                    } else if ( c2wInteractionRootSP2->get_actualLogicalGenerationTime() < c2wInteractionRootSP1->get_actualLogicalGenerationTime() ) {
                        return false;
                    }
                }
            }

            return interactionRootSP1->getUniqueId() < interactionRootSP2->getUniqueId();
        }
    };

    typedef std::multiset< InteractionRoot::SP, InteractionRootSPComparator > InteractionQueue;

    InteractionQueue interactionQueue;

public:
    void addInteraction( InteractionRoot::SP interactionRootSP ) {
        interactionQueue.insert( interactionRootSP );
    }

    InteractionRoot::SP getNextInteraction( void ) {

        InteractionRoot::SP nullInteractionRootSP;
        if ( interactionQueue.empty() ) {
            return nullInteractionRootSP;
        }

        InteractionQueue::iterator inqItr = interactionQueue.begin();
        InteractionRoot::SP interactionRootSP = *inqItr;

        if (interactionRootSP->getTime() > getCurrentTime()) {
            return nullInteractionRootSP;
        }

        interactionQueue.erase( inqItr );
        return interactionRootSP;
    }

    bool unmatchingFedFilterProvided( InteractionRoot::SP interactionRootSP ) {
        boost::shared_ptr< C2WInteractionRoot > c2wInteractionRootSP(   boost::static_pointer_cast< C2WInteractionRoot >( interactionRootSP )  );
        std::string fedFilter = c2wInteractionRootSP->get_federateFilter();
        if( fedFilter.length() > 0 ) {
            boost::algorithm::trim(fedFilter);
            if( ( fedFilter.length() > 0 ) && ( fedFilter.compare( getFederateId() ) != 0 ) ) {
                // std::cout << "Filtering due to fed filter: " << fedFilter << std::endl;
                // std::cout << "Filtered interaction was: " << interactionRootSP << std::endl;
                return true;
            }
        }
        return false;
    }

    virtual void receiveInteraction(
      RTI::InteractionClassHandle theInteraction,
      const RTI::ParameterHandleValuePairSet& theParameters,
      const RTI::FedTime& theTime,
      const char *theTag,
      RTI::EventRetractionHandle theHandle
    ) throw (
      RTI::InteractionClassNotKnown,
      RTI::InteractionParameterNotKnown,
      RTI::InvalidFederationTime,
      RTI::FederateInternalError
    ) {
        if ( getMoreATRs() ) {

            InteractionRoot::SP interactionRootSP = InteractionRoot::create_interaction(
              theInteraction, theParameters, theTime
            );

            std::string sourceFederateId = C2WInteractionRoot::get_source_federate_id(*interactionRootSP);
            if (
              !sourceFederateId.empty() &&
                hasProxy(sourceFederateId) &&
                *getProxyFor(sourceFederateId) == getFederateType()
            ) {
                interactionRootSP->setProxiedFederateName(sourceFederateId);
            }

            receiveInteractionAux(interactionRootSP);
        }

    }

    virtual void receiveInteraction(
      RTI::InteractionClassHandle theInteraction,
      const RTI::ParameterHandleValuePairSet& theParameters,
      const char *theTag
    ) throw ( RTI::InteractionClassNotKnown, RTI::InteractionParameterNotKnown, RTI::FederateInternalError) {

        if ( getMoreATRs() ) {

            InteractionRoot::SP interactionRootSP = InteractionRoot::create_interaction(theInteraction, theParameters);

            std::string sourceFederateId = C2WInteractionRoot::get_source_federate_id(*interactionRootSP);
            if (
              !sourceFederateId.empty() &&
                hasProxy(sourceFederateId) &&
                *getProxyFor(sourceFederateId) == getFederateType()
            ) {
                interactionRootSP->setProxiedFederateName(sourceFederateId);
            }

            receiveInteractionAux(interactionRootSP);
        }
    }


private:
    void receiveEmbeddedMessagingInteraction(EmbeddedMessaging::SP embeddedMessagingSP) {
        const std::string jsonValueString = embeddedMessagingSP->get_messagingJson();
        std::istringstream jsonInputStream(jsonValueString);

        Json::Value jsonValue;
        jsonInputStream >> jsonValue;

        if (jsonValue.isArray()) {
            for(const Json::Value &item : jsonValue) {
                processEmbeddedMessagingInteraction(item);
            }
        } else {
            processEmbeddedMessagingInteraction(jsonValue);
        }
    }

    void receiveInteractionAux(InteractionRoot::SP interactionRootSP)
      throw ( RTI::InteractionClassNotKnown, RTI::InteractionParameterNotKnown, RTI::FederateInternalError);

    void processEmbeddedMessagingInteraction(const Json::Value &jsonValue);

public:
    bool iteration( void );
    void run( void );
    void advanceTime( double time );
    void advanceTimeStep( double timeStep ) {
        advanceTime( _currentTime + timeStep );
    }

//    void createLog(
//        RTI::InteractionClassHandle theInteraction,
//        const RTI::ParameterHandleValuePairSet& theParameters,
//        double time=0);

private:
    typedef std::multiset< ObjectReflector::SP, ObjectReflectorSPComparator > ObjectReflectorSPQueue;

    ObjectReflectorSPQueue objectReflectorSPQueue;

public:
    void addObjectReflectorSP( const ObjectReflector::SP &objectReflectorSP ) {
        objectReflectorSPQueue.insert( objectReflectorSP );
    }

    void addObjectReflectorSP( int objectHandle, const RTI::AttributeHandleValuePairSet& theAttributes ) {
        addObjectReflectorSP(ObjectReflector::SP(new ObjectReflector(objectHandle, theAttributes)));
    }
    void addObjectReflectorSP( int objectHandle, const RTI::AttributeHandleValuePairSet& theAttributes, const RTI::FedTime &theTime ) {
        addObjectReflectorSP(ObjectReflector::SP(new ObjectReflector( objectHandle, theAttributes, theTime)));
    }

    ObjectReflector::SP getNextObjectReflectorSP( void ) {
        if ( objectReflectorSPQueue.empty() ) return ObjectReflector::SP();

        ObjectReflectorSPQueue::iterator orqItr = objectReflectorSPQueue.begin();
        ObjectReflector::SP objectReflectorSP = *orqItr;

        if (objectReflectorSP->getTime() > getCurrentTime()) {
            return ObjectReflector::SP();
        }

        objectReflectorSPQueue.erase( orqItr );
        return objectReflectorSP;
    }

    virtual void discoverObjectInstance(
      RTI::ObjectHandle theObject, RTI::ObjectClassHandle theObjectClass, const char *objectName
    ) throw ( RTI::CouldNotDiscover, RTI::ObjectClassNotKnown, RTI::FederateInternalError) {
        ObjectRoot::discover( theObjectClass, theObject );
    }

    virtual void removeObjectInstance(RTI::ObjectHandle theObject, const char *userSuppliedTag)
      throw (RTI::ObjectNotKnown, RTI:: FederateInternalError) {
        ObjectRoot::remove_object(theObject);
    }

    virtual void removeObjectInstance(
      RTI::ObjectHandle theObject,
      const char *userSuppliedTag,
      const RTI::FedTime& theTime,
      RTI::EventRetractionHandle retractionHandle
    ) throw (RTI::ObjectNotKnown, RTI::InvalidFederationTime, RTI::FederateInternalError) {
        ObjectRoot::remove_object(theObject);
    }

public:
    virtual void reflectAttributeValues( RTI::ObjectHandle theObject, const RTI::AttributeHandleValuePairSet& theAttributes, const char *theTag )
     throw ( RTI::ObjectNotKnown, RTI::AttributeNotKnown, RTI::FederateOwnsAttributes, RTI::FederateInternalError ) {

        addObjectReflectorSP( theObject, theAttributes );
//        createLog(theObject, theAttributes);
    }

    virtual void reflectAttributeValues(
     RTI::ObjectHandle theObject,
     const RTI::AttributeHandleValuePairSet& theAttributes,
     const RTI::FedTime& theTime,
     const char *theTag,
     RTI::EventRetractionHandle theHandle
    )
     throw ( RTI::ObjectNotKnown, RTI::AttributeNotKnown, RTI::FederateOwnsAttributes, RTI::InvalidFederationTime, RTI::FederateInternalError ) {

        addObjectReflectorSP( theObject, theAttributes, theTime );
//        RTIfedTime rtitime(theTime);
//        double ltime = rtitime.getTime();
    }

    void notifyFederationOfSimEnd() {
        SimEnd simEnd;

        sendInteraction(simEnd);
        getRTI()->tick();
    }

    void writeStatus() {
        mkdir("StatusDirectory", 0755);
        std::ofstream outputFileStream("StatusDirectory/exitStatus");
        outputFileStream << getStatus() << std::endl;
        outputFileStream.close();
    }

    void exitGracefully() {

        notifyFederationOfSimEnd();

        writeStatus();

        // SLEEP 3 SECONDS TO ALLOW SimEnd TO BE SENT
#ifdef _WIN32
        Sleep( 3000 );
#else
        usleep( 3000000 );
#endif
    }

    void exitImmediately() {
        writeStatus();

        exit(0);
    }
};

#if __cplusplus >= 201703L
#undef MultiArgThrow17
#undef Throw17
#undef throw
#endif

#endif
