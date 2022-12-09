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
#include <string>
#include <set>
#include <map>
#include <algorithm>

#include <iostream>

#define BOOST_LOG_DYN_LINK

#include <boost/log/expressions/keyword.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include "NullFederateAmbassador.hh"
#include "RTI.hh"
#include "fedtime.hh"
#include "InteractionRoot.hpp"
#include "ObjectRoot.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/SimulationControl_p/SimEnd.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/EmbeddedMessaging.hpp"

#include "InteractionRoot_p/C2WInteractionRoot_p/FederateResignInteraction.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/FederateJoinInteraction.hpp"

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

namespace logging = boost::log;
namespace logging_source = boost::log::sources;
namespace attrs = boost::log::attributes;

using namespace logging::trivial;

class SynchronizedFederate : public NullFederateAmbassador {

public:
    typedef logging_source::severity_logger< severity_level > severity_logger;

    using ObjectRoot = ::org::cpswt::hla::ObjectRoot;
    using ObjectReflector = ObjectRoot::ObjectReflector;
    using ObjectReflectorSPComparator = ObjectRoot::ObjectReflectorSPComparator;
    using InteractionRoot = ::org::cpswt::hla::InteractionRoot;
    using C2WInteractionRoot = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot;
    using EmbeddedMessaging = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::EmbeddedMessaging;
    using SimEnd = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::SimulationControl_p::SimEnd;
    using FederateJoinInteraction =
      ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::FederateJoinInteraction;
    using FederateResignInteraction =
      ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::FederateResignInteraction;

    static const std::string FEDERATION_MANAGER_NAME;

    static const std::string ReadyToPopulateSynch;
    static const std::string ReadyToRunSynch;
    static const std::string ReadyToResignSynch;

    enum TimeAdvanceMode {
        SF_TIME_ADVANCE_REQUEST,
        SF_NEXT_EVENT_REQUEST,
        SF_TIME_ADVANCE_REQUEST_AVAILABLE,
        SF_NEXT_EVENT_REQUEST_AVAILABLE
    };

private:
    RTI::RTIambassador *_rti;

    std::string _federationId;
//    std::string _lockFileName;

    std::string _federateType;
    std::string _federateId;

    std::string _federationJsonFileName;
    std::string _federateDynamicMessagingClassesJsonFileName;
    std::string _rejectSourceFederateIdJsonFileName;

    bool _isLateJoiner;

    typedef boost::shared_ptr<StringSet> StringSetSP;

    StringSet _achievedSynchronizationPoints;

    bool _timeConstrainedNotEnabled;
    bool _timeRegulationNotEnabled;
    bool _timeAdvanceNotGranted;
    bool _simEndNotSubscribed;

    double _lookahead;
    double _stepSize;
    TimeAdvanceMode _timeAdvanceMode;

    double _currentTime;

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

    std::string getFederationManagerName( void ) const {
        return SynchronizedFederate::FEDERATION_MANAGER_NAME;
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

    void setRejectSourceFederateIdJsonFileName(
      const std::string &rejectSourceFederateIdJsonFileName
    ) {
        _rejectSourceFederateIdJsonFileName = rejectSourceFederateIdJsonFileName;
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

protected:
    SynchronizedFederate( void ) :
      _federateId( "" ),
      _federateType(""),
      _federationId( "" ),

      _isLateJoiner(false),

      _timeConstrainedNotEnabled( true ),
      _timeRegulationNotEnabled( true ),
      _simEndNotSubscribed( true ),

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

    SynchronizedFederate( FederateConfig *fedconfig) {
        this->_federationId = fedconfig->federationId;
        this->_federateType = fedconfig->federateType;
        this->_federateId = fedconfig->federateType + std::to_string(rand());

        this->_isLateJoiner= fedconfig->isLateJoiner;

        this->_federationJsonFileName = fedconfig->federationJsonFileName;
        this->_federateDynamicMessagingClassesJsonFileName = fedconfig->federateDynamicMessagingClassesJsonFileName;
        this->_rejectSourceFederateIdJsonFileName = fedconfig->rejectSourceFederateIdJsonFileName;

        this->_timeConstrainedNotEnabled = true;
        this->_timeRegulationNotEnabled = true;
        this->_simEndNotSubscribed = true;

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
      std::istream &federationJsonInputStream,
      std::istream &federateDynamicMessagingClassesJsonInputStream,
      std::istream &rejectSourceFederateIdJsonInputStream
    ) {
        initializeDynamicMessaging(federationJsonInputStream, federateDynamicMessagingClassesJsonInputStream);
        C2WInteractionRoot::readRejectSourceFederateIdData(rejectSourceFederateIdJsonInputStream);
    }

    void initializeDynamicMessaging(
      const std::string &federationJsonFileName,
      const std::string &federateDynamicMessagingClassesJsonFileName,
      const std::string &rejectSourceFederateIdJsonFileName
    ) {
        if (federationJsonFileName.empty() || federateDynamicMessagingClassesJsonFileName.empty()) {
            initializeMessaging();
            return;
        }

        std::ifstream federationJsonInputStream(federationJsonFileName);
        std::ifstream federateDynamicMessagingClassJsonInputStream(federateDynamicMessagingClassesJsonFileName);
        if (rejectSourceFederateIdJsonFileName.empty()) {
            initializeDynamicMessaging(
              federationJsonInputStream,
              federateDynamicMessagingClassJsonInputStream
            );
        } else {
            std::ifstream rejectSourceFederateIdJsonInputStream(rejectSourceFederateIdJsonFileName);
            initializeDynamicMessaging(
              federationJsonInputStream,
              federateDynamicMessagingClassJsonInputStream,
              rejectSourceFederateIdJsonInputStream
            );
            rejectSourceFederateIdJsonInputStream.close();
        }

        federationJsonInputStream.close();
        federateDynamicMessagingClassJsonInputStream.close();
    }

    void notifyFederationOfJoin();
    void notifyFederationOfResign();

    void ensureSimEndSubscription( void ) {
        if ( _simEndNotSubscribed ) {
            // Auto-subscribing also ensures that there is no filter set for SimEnd
            SimEnd::subscribe_interaction( getRTI() );
            _simEndNotSubscribed = false;
        }
    }

    // void joinFederation( const std::string &federation_id, const std::string &federate_id, bool ignoreLockFile = true );
    void joinFederation();

    void sendInteraction(InteractionRoot &interactionRoot, const StringSet &federateNameSet, double time);

    void sendInteraction(InteractionRoot &interactionRoot, const std::string &federateName, double time) {
        std::set<std::string> stringSet;
        stringSet.emplace(federateName);
        sendInteraction(interactionRoot, stringSet, time);
    }

    void sendInteraction( InteractionRoot &interactionRoot, double time ) {
        C2WInteractionRoot::update_federate_sequence(interactionRoot, getFederateType());

        if (interactionRoot.getIsPublished()) {
            interactionRoot.sendInteraction(getRTI(), time);
        }

        sendInteraction(interactionRoot, *interactionRoot.getFederateNameSoftPublishSetSP(), time);
    }

    void sendInteraction(InteractionRoot &interactionRoot) {
        C2WInteractionRoot::update_federate_sequence(interactionRoot, getFederateType());

        if (interactionRoot.getIsPublished()) {
            interactionRoot.sendInteraction(getRTI());
        }
        sendInteraction(interactionRoot, *interactionRoot.getFederateNameSoftPublishSetSP(), -1);
    }

    void sendInteraction(InteractionRoot &interactionRoot, const std::string &federateName) {
        std::set<std::string> stringSet;
        stringSet.emplace(federateName);
        sendInteraction(interactionRoot, stringSet, -1);
    }

    void registerObject(ObjectRoot &objectRoot);

    void sendInteraction(
      const std::string &objectReflectorJson,
      const std::string &hlaClassName,
      const std::string &federateSequence,
      const StringSet &federateNameSet,
      double time
    );

    void sendInteraction(ObjectReflector &objectReflector, const StringSet &federateNameSet, double time) {
        sendInteraction(
          objectReflector.toJson(),
          objectReflector.getHlaClassName(),
          objectReflector.getFederateSequence(),
          federateNameSet,
          time
        );
    }

    void sendInteraction(ObjectRoot &objectRoot, const StringSet &federateNameSet, double time, bool force) {
        sendInteraction(
          objectRoot.toJson(force), objectRoot.getInstanceHlaClassName(), std::string("[]"), federateNameSet, time
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

protected:

    void readyToPopulate( void ) throw( RTI::FederateNotExecutionMember, RTI::RTIinternalError ) {
        achieveSynchronizationPoint( ReadyToPopulateSynch );
    }
    void readyToRun( void ) throw( RTI::FederateNotExecutionMember, RTI::RTIinternalError ) {
        achieveSynchronizationPoint( ReadyToRunSynch );
    }
    void readyToResign( void ) throw( RTI::FederateNotExecutionMember, RTI::RTIinternalError ) {
        achieveSynchronizationPoint( ReadyToResignSynch );
    }
    void achieveSynchronizationPoint( const std::string &label )
     throw( RTI::FederateNotExecutionMember, RTI::RTIinternalError );

    virtual void timeAdvanceGrant( const RTI::FedTime &fedTime )
     throw( RTI::InvalidFederationTime, RTI::TimeAdvanceWasNotInProgress, RTI::FederateInternalError ) {
        _timeAdvanceNotGranted = false;
    }

public:
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
    static ATRQueue &getATRQueue( void ) {
        static ATRQueue atrQueue;
        return atrQueue;
    }

    static void noMoreATRs( void ) { getMoreATRs() = false; }

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
    static bool &getMoreATRs( void ) {
        static bool moreATRs = true;
        return moreATRs;
    }

    static void putAdvanceTimeRequest( double time, ATRCallback &atrCallback ) {
        getATRQueue().insert(  std::make_pair( time, atrCallback.clone() )  );
    }

private:
    static AdvanceTimeRequest takeNextAdvanceTimeRequest( void ) {
        if ( getATRQueue().empty() ) return AdvanceTimeRequest();
        AdvanceTimeRequest advanceTimeRequest( *getATRQueue().begin() );
        getATRQueue().erase( getATRQueue().begin() );
        return advanceTimeRequest;
    }

    class InteractionRootSPComparator {
    public:
        bool operator()( const InteractionRoot::SP &interactionRootSP1, const InteractionRoot::SP &interactionRootSP2 ) {
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

            return false;
        }
    };

    typedef std::multiset< InteractionRoot::SP, InteractionRootSPComparator > InteractionQueue;
    static InteractionQueue &getInteractionQueue( void ) {
        static InteractionQueue interactionQueue;
        return interactionQueue;
    }

public:
    static void addInteraction( InteractionRoot::SP interactionRootSP ) {
        getInteractionQueue().insert( interactionRootSP );
    }

    static InteractionRoot::SP getNextInteraction( void ) {
        if ( getInteractionQueue().empty() ) return InteractionRoot::SP( (InteractionRoot*)0 );

        InteractionQueue::iterator inqItr = getInteractionQueue().begin();
        InteractionRoot::SP interactionRootSP = *inqItr;
        getInteractionQueue().erase( inqItr );
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
            RTIfedTime rtitime(theTime);
            double ltime = rtitime.getTime();

std::cerr << "Received interaction with time" << std::endl;
            InteractionRoot::SP interactionRootSP = InteractionRoot::create_interaction( theInteraction, theParameters, theTime );
            receiveInteractionAux(interactionRootSP, ltime);
//          interactionRootSP->createLog( ltime, false );
        }

    }

    virtual void receiveInteraction(
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
            receiveInteractionAux(interactionRootSP, assumedTimestamp);
//          interactionRootSP->createLog( assumedTimestamp, false );
        }
    }

private:
    void receiveInteractionAux(
      InteractionRoot::SP interactionRootSP, double timestamp
    )
     throw ( RTI::InteractionClassNotKnown, RTI::InteractionParameterNotKnown, RTI::FederateInternalError) {
        if (
          !C2WInteractionRoot::is_reject_source_federate_id(interactionRootSP) &&
          !unmatchingFedFilterProvided(interactionRootSP)
        ) {
            if (interactionRootSP->isInstanceHlaClassDerivedFromHlaClass(EmbeddedMessaging::get_hla_class_name())) {
                receiveEmbeddedInteraction(boost::static_pointer_cast<EmbeddedMessaging>(interactionRootSP), timestamp);
                return;
            }

            handleIfSimEnd(*interactionRootSP, timestamp);
            addInteraction( interactionRootSP );
//             interactionRootSP->createLog( assumedTimestamp, false );
        }
    }

    void receiveEmbeddedInteraction(EmbeddedMessaging::SP embeddedMessagingSP, double timestamp);

protected:

    void finalizeAndTerminate() {
        std::cout << getFederateId() << ": resigning from federation...";
        resignFederationExecution();
        std::cout << "done." << std::endl;

        // Wait for 10 seconds for Federation Manager to recognize that the federate has resigned.
#ifdef _WIN32
        Sleep( 10000 );
#else
        usleep( 10000000 );
#endif

        // TODO: Kill the entire process group (like in SynchronizedFederate.java)

        // Exit
        exit(0);
    }

    void handleIfSimEnd(InteractionRoot &interactionRoot, double timestamp) {
        int classHandle = interactionRoot.getClassHandle();
        if(  SimEnd::match( classHandle )  ) {
            std::cout << getFederateId() << ": SimEnd interaction received, exiting..." << std::endl;
//             interactionRootSP->createLog( timestamp, false );
            finalizeAndTerminate();
        }
    }

public:
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
    static ObjectReflectorSPQueue &getObjectReflectorSPQueue( void ) {
        static ObjectReflectorSPQueue objectReflectorSPQueue;
        return objectReflectorSPQueue;
    }

public:
    static void addObjectReflectorSP( const ObjectReflector::SP &objectReflectorSP ) {
        getObjectReflectorSPQueue().insert( objectReflectorSP );
    }

    static void addObjectReflectorSP( int objectHandle, const RTI::AttributeHandleValuePairSet& theAttributes ) {
        addObjectReflectorSP(ObjectReflector::SP(new ObjectReflector(objectHandle, theAttributes)));
    }
    static void addObjectReflectorSP( int objectHandle, const RTI::AttributeHandleValuePairSet& theAttributes, const RTI::FedTime &theTime ) {
        addObjectReflectorSP(ObjectReflector::SP(new ObjectReflector( objectHandle, theAttributes, theTime)));
    }

    static ObjectReflector::SP getNextObjectReflectorSP( void ) {
        if ( getObjectReflectorSPQueue().empty() ) return ObjectReflector::SP();

        ObjectReflectorSPQueue::iterator orqItr = getObjectReflectorSPQueue().begin();
        ObjectReflector::SP objectReflectorSP = *orqItr;
        getObjectReflectorSPQueue().erase( orqItr );
        return objectReflectorSP;
    }

    virtual void discoverObjectInstance(
      RTI::ObjectHandle theObject, RTI::ObjectClassHandle theObjectClass, const char *objectName
    ) throw ( RTI::CouldNotDiscover, RTI::ObjectClassNotKnown, RTI::FederateInternalError) {
        ObjectRoot::discover( theObjectClass, theObject );
    }

    virtual void removeObjectInstance(RTI::ObjectHandle theObject, const char *userSuppliedTag) {
        ObjectRoot::remove_object(theObject);
    }

    virtual void removeObjectInstance(
      RTI::ObjectHandle theObject,
      const char *userSuppliedTag,
      const RTI::FedTime& theTime,
      RTI::EventRetractionHandle retractionHandle
    ) {
        ObjectRoot::remove_object(theObject);
    }

private:
    bool checkNetworkReflect(int theObject) {
        ObjectRoot::SP objectRootSP = ObjectRoot::get_object(theObject);
        if (!bool(objectRootSP)) {
            BOOST_LOG_SEV( get_logger(), warning ) <<
              "Received \"reflectAttributeValues\" for object handle (" << theObject <<
              ") that has no corresponding object";
            return false;
        }
        const std::string &hlaClassName = objectRootSP->getInstanceHlaClassName();
        const ObjectRoot::IntegerSet &objectHandleSet =
          *ObjectRoot::get_object_update_embedded_only_id_set_sp(hlaClassName);
        if (objectHandleSet.find(theObject) != objectHandleSet.end()) {
            BOOST_LOG_SEV( get_logger(), info ) <<
              "Direct \"reflectAttributeValues\" for Object (" << theObject << ") of class \"" << hlaClassName <<
                "\" rejected as it should only reflect via EmbeddedMessaging";
            return false;
        }
        return true;
    }

public:
    virtual void reflectAttributeValues( RTI::ObjectHandle theObject, const RTI::AttributeHandleValuePairSet& theAttributes, const char *theTag )
     throw ( RTI::ObjectNotKnown, RTI::AttributeNotKnown, RTI::FederateOwnsAttributes, RTI::FederateInternalError ) {

        if (checkNetworkReflect(theObject)) {
            return;
        }

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

        if (checkNetworkReflect(theObject)) {
            return;
        }

        addObjectReflectorSP( theObject, theAttributes, theTime );
        RTIfedTime rtitime(theTime);
        double ltime = rtitime.getTime();
    }

    void exitGracefully() {
        notifyFederationOfResign();

#ifdef _WIN32
        Sleep( 5000 );
#else
        usleep( 5000000 );
#endif

        resignFederationExecution();
    }
};

#endif
