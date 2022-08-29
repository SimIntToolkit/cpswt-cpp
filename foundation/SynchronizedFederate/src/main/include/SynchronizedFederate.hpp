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


class SynchronizedFederate : public NullFederateAmbassador {

public:
    using ObjectRoot = ::org::cpswt::hla::ObjectRoot;
    using InteractionRoot = ::org::cpswt::hla::InteractionRoot;
    using C2WInteractionRoot = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot;
    using EmbeddedMessaging = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::EmbeddedMessaging;
    using SimEnd = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::SimulationControl_p::SimEnd;
    using FederateJoinInteraction = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::FederateJoinInteraction;
    using FederateResignInteraction = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::FederateResignInteraction;

    static const std::string FEDERATION_MANAGER_NAME;
    enum TimeAdvanceMode { SF_TIME_ADVANCE_REQUEST, SF_NEXT_EVENT_REQUEST, SF_TIME_ADVANCE_REQUEST_AVAILABLE, SF_NEXT_EVENT_REQUEST_AVAILABLE };


private:
    RTI::RTIambassador *_rti;

    std::string _federateId;
    std::string _federationId;
//    std::string _lockFileName;

    std::string _FederateId;
    std::string _FederateType;

    std::string _federationJsonFileName;
    std::string _federateDynamicMessagingClassesJsonFileName;
    std::string _rejectSourceFederateIdJsonFileName;

    bool _IsLateJoiner;



public:
    static const std::string ReadyToPopulateSynch;
    static const std::string ReadyToRunSynch;
    static const std::string ReadyToResignSynch;

private:
    typedef std::set< std::string > StringSet;
    StringSet _achievedSynchronizationPoints;

    bool _timeConstrainedNotEnabled;
    bool _timeRegulationNotEnabled;
    bool _timeAdvanceNotGranted;
    bool _simEndNotSubscribed;

    double _currentTime;
    double _lookahead;
    double _stepSize;
    TimeAdvanceMode _timeAdvanceMode;

public:
    void setStepSize(double stepSize) {
        _stepSize = stepSize;
    }
    double getStepSize(void) {
        return _stepSize;
    }

    void setLookahead( double lookahead ) {
        _lookahead = lookahead;
    }
    double getLookahead() {
        return _lookahead;
    }

    void setTimeAdvanceMode ( TimeAdvanceMode timeAdvanceMode ) { _timeAdvanceMode = timeAdvanceMode; }
    TimeAdvanceMode getTimeAdvanceMode() { return _timeAdvanceMode; }

private:
    bool getTimeAdvanceNotGranted( void ) { return _timeAdvanceNotGranted; }
    void setTimeAdvanceNotGranted( bool timeAdvanceNotGranted ) { _timeAdvanceNotGranted = timeAdvanceNotGranted; }

protected:
    static C2WLogger* _logger;

    SynchronizedFederate( void ) :
      _federateId( "" ),
      _federationId( "" ),
      _timeConstrainedNotEnabled( true ),
      _timeRegulationNotEnabled( true ),
      _simEndNotSubscribed( true ),
      _currentTime( 0 ),
      _lookahead( 0 ),
      _IsLateJoiner(false),
      _FederateType("") {

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
        this->_timeConstrainedNotEnabled = true;
        this->_timeRegulationNotEnabled = true;
        this->_simEndNotSubscribed = true;
        //    = fedconfig->
        setLookahead(fedconfig->lookAhead);
        this->_IsLateJoiner= fedconfig->isLateJoiner;
        this->_FederateType = fedconfig->federateType;
        this->_federationJsonFileName = fedconfig->federationJsonFileName;
        this->_federateDynamicMessagingClassesJsonFileName = fedconfig->federateDynamicMessagingClassesJsonFileName;
        this->_rejectSourceFederateIdJsonFileName = fedconfig->rejectSourceFederateIdJsonFileName;


        setStepSize(fedconfig->stepSize);



        std::stringstream temp;  //temp as in temporary
        int random_variable = std::rand();
        temp<<fedconfig->federateType<<random_variable;
        this->_federateId=temp.str();      //str is temp as string
        setpgid( 0, 0 );

        //   _lockFileName = getenv( "EXEDIR" );
        //   if ( !_lockFileName.empty() ) {
        //       _lockFileName += "/";
        //   }
        //   _lockFileName += "__lock__";

        this->_timeAdvanceMode = SF_TIME_ADVANCE_REQUEST;
    }

    virtual ~SynchronizedFederate() throw (RTI::FederateInternalError) {
         destroyRTI();
    }

    RTI::RTIambassador *getRTI( void ) {
        return _rti;
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

    // void joinFederation( const std::string &federation_id, const std::string &federate_id, bool ignoreLockFile = true );
    void joinFederation();

    void sendInteraction(InteractionRoot &interactionRoot, const StringSet &federateNameSet, double time) {

        if (!interactionRoot.isInstanceHlaClassDerivedFromHlaClass(EmbeddedMessaging::get_hla_class_name())) {

            std::string interactionJson = interactionRoot.toJson();

            for (
              StringSet::const_iterator sstCit = federateNameSet.begin() ; sstCit != federateNameSet.end() ; ++sstCit
            ) {
                const std::string &federateName = *sstCit;
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
                embeddedMessagingForNetworkFederateSP->setParameter(
                        "hlaClassName", interactionRoot.getInstanceHlaClassName()
                );
                embeddedMessagingForNetworkFederateSP->setParameter("messagingJson", interactionJson);

                if (time >= 0) {
                    sendInteraction(embeddedMessagingForNetworkFederateSP, time);
                } else {
                    sendInteraction(embeddedMessagingForNetworkFederateSP);
                }
            }
        }
    }

    void sendInteraction(InteractionRoot::SP interactionRootSP, const StringSet &federateNameSet, double time) {
        sendInteraction(*interactionRootSP, federateNameSet, time);
    }

    void sendInteraction(InteractionRoot &interactionRoot, const std::string &federateName, double time) {
        std::set<std::string> stringSet;
        stringSet.emplace(federateName);
        sendInteraction(interactionRoot, stringSet, time);
    }

    void sendInteraction(InteractionRoot::SP interactionRootSP, const std::string &federateName, double time) {
        sendInteraction(*interactionRootSP, federateName, time);
    }

    void sendInteraction( InteractionRoot &interactionRoot, double time ) {
        C2WInteractionRoot::update_federate_sequence(interactionRoot, getFederateType());

        if (interactionRoot.getIsPublished()) {
            interactionRoot.sendInteraction(getRTI(), time);
        }
        sendInteraction(interactionRoot, interactionRoot.getFederateNameSoftPublishSet(), time);
    }

    void sendInteraction( InteractionRoot::SP interactionRootSP, double time ) {
        sendInteraction(*interactionRootSP, time);
    }

    void sendInteraction(InteractionRoot &interactionRoot) {
        C2WInteractionRoot::update_federate_sequence(interactionRoot, getFederateType());

        if (interactionRoot.getIsPublished()) {
            interactionRoot.sendInteraction(getRTI());
        }
        sendInteraction(interactionRoot, interactionRoot.getFederateNameSoftPublishSet(), -1);
    }

    void sendInteraction( InteractionRoot::SP interactionRootSP ) {
        sendInteraction(*interactionRootSP);
    }

    void sendInteraction(InteractionRoot &interactionRoot, const std::string &federateName) {
        std::set<std::string> stringSet;
        stringSet.emplace(federateName);
        sendInteraction(interactionRoot, stringSet, -1);
    }

    void sendInteraction(InteractionRoot::SP interactionRootSP, const std::string &federateName) {
        sendInteraction(*interactionRootSP, federateName);
    }

    void setFederateId(const std::string &federateId) {
        _federateId = federateId;
    }
    std::string getFederateId( void ) const {
        return _federateId;
    }


    void setFederationId(const std::string &federationId) {
        _federationId = federationId;
    }
    std::string getFederationId( void ) const {
        return _federationId;
    }

    std::string getFederationManagerName( void ) const {
        return SynchronizedFederate::FEDERATION_MANAGER_NAME;
    }

    void setFederateType( const std::string &federateType ) {
        _FederateType = federateType;
    }
    std::string getFederateType( void ) const {
        return _FederateType;
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

    bool get_IsLateJoiner( void ) const { return _IsLateJoiner; }


    void enableTimeConstrained( void ) throw( RTI::FederateNotExecutionMember );
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

//     TimeRegulationWasNotEnabled,
//  ConcurrentAccessAttempted,
//  FederateNotExecutionMember,
//  SaveInProgress,
 // RestoreInProgress,
 // RTIinternalError

    
    void resignFederationExecution( RTI::ResignAction resignAction );
    void resignFederationExecution( void ) {
        resignFederationExecution( RTI::DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES );
    }

    void enableAsynchronousDelivery( void ) { getRTI()->enableAsynchronousDelivery(); }

    void ensureSimEndSubscription( void ) {
        if ( _simEndNotSubscribed ) {
            // Auto-subscribing also ensures that there is no filter set for SimEnd
            SimEnd::subscribe_interaction( getRTI() );
            _simEndNotSubscribed = false;
        }
    }

    void readyToPopulate( void ) throw( RTI::FederateNotExecutionMember, RTI::RTIinternalError ) {
        ensureSimEndSubscription();
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

public:
    virtual void timeConstrainedEnabled( const RTI::FedTime &t )
     throw( RTI::InvalidFederationTime, RTI::EnableTimeConstrainedWasNotPending, RTI::FederateInternalError ) { _timeConstrainedNotEnabled = false; }
    virtual void timeRegulationEnabled( const RTI::FedTime &t )
     throw ( RTI::InvalidFederationTime, RTI::EnableTimeRegulationWasNotPending, RTI::FederateInternalError ) { _timeRegulationNotEnabled = false; }
    virtual void timeAdvanceGrant( const RTI::FedTime &fedTime )
      throw( RTI::InvalidFederationTime, RTI::TimeAdvanceWasNotInProgress, RTI::FederateInternalError ) { _timeAdvanceNotGranted = false; }

    virtual void federationSynchronized( const char *label ) throw( RTI::FederateInternalError ) {
        std::cout << "federationSynchronized on label \"" << label << "\"" << std::endl;
        _achievedSynchronizationPoints.insert( label );
    }

private:
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
    void receiveEmbeddedInteraction(EmbeddedMessaging::SP embeddedMessagingSP, double timestamp) {
        std::string hlaClassName = embeddedMessagingSP->get_hlaClassName();
        if (!InteractionRoot::get_is_soft_subscribed(hlaClassName)) {
            return;
        }

        InteractionRoot::SP embeddedInteractionSP =
                InteractionRoot::fromJson(embeddedMessagingSP->get_messagingJson());
        receiveInteractionAux(embeddedInteractionSP, timestamp);
    }

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

            handleIfSimEnd(interactionRootSP, timestamp);
            addInteraction( interactionRootSP );
//             interactionRootSP->createLog( assumedTimestamp, false );
        }
    }

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

    void handleIfSimEnd(InteractionRoot::SP interactionRootSP, double timestamp) {
        handleIfSimEnd(*interactionRootSP, timestamp);
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

    class ObjectReflector {
    private:
        RTI::ObjectHandle _objectHandle;
        RTI::AttributeHandleValuePairSet *_theAttributes;
        double _time;

        void init( const RTI::AttributeHandleValuePairSet &theAttributes ) {
            for(RTI::ULong ix = 0 ; ix < theAttributes.size() ; (void)++ix ) {
                RTI::ULong valueLength = theAttributes.getValueLength( ix );
                _theAttributes->add( theAttributes.getHandle( ix ), theAttributes.getValuePointer( ix, valueLength ), theAttributes.getValueLength( ix )  );
            }
        }

    public:
        ObjectReflector( void ) : _theAttributes( (RTI::AttributeHandleValuePairSet *)0 ) { }

        ObjectReflector(
         RTI::ObjectHandle objectHandle,
         const RTI::AttributeHandleValuePairSet& theAttributes
        ) : _objectHandle( objectHandle ), _theAttributes(  RTI::AttributeSetFactory::create( theAttributes.size() )  ), _time( -1 ) {
            init( theAttributes );
        }

        ObjectReflector(
         RTI::ObjectHandle objectHandle,
         const RTI::AttributeHandleValuePairSet& theAttributes,
         double time
        ) : _objectHandle( objectHandle ), _theAttributes(  RTI::AttributeSetFactory::create( theAttributes.size() )  ), _time( time ) {
            init( theAttributes );
        }

        ObjectReflector(
         RTI::ObjectHandle objectHandle,
         const RTI::AttributeHandleValuePairSet& theAttributes,
         const RTI::FedTime &fedTime
        ) : _objectHandle( objectHandle ), _theAttributes(  RTI::AttributeSetFactory::create( theAttributes.size() )  ), _time(  RTIfedTime( fedTime ).getTime()  ) {
            init( theAttributes );
        }

        ~ObjectReflector() {
            delete _theAttributes;
        }

        void reflect() const {
            if ( _theAttributes == 0 ) {
                std::cerr << "WARNING:  attempt to reflect null ObjectReflector" << std::endl;
                return;
            }
            if ( _time < 0 ) ObjectRoot::reflect( _objectHandle, *_theAttributes );
            else  ObjectRoot::reflect( _objectHandle, *_theAttributes, _time );
        }

        ObjectRoot::SP getObjectRootSP() const { return ObjectRoot::get_object( _objectHandle ); }
        double getTime() const { return _time; }

        bool isNull( void ) const { return _theAttributes == 0; }
    };

private:
    class ObjectReflectorComparator {
    public:
        bool operator()( const ObjectReflector &objectReflector1, const ObjectReflector &objectReflector2 ) {
            return objectReflector1.getTime() < objectReflector2.getTime();
        }
    };

    typedef std::multiset< ObjectReflector, ObjectReflectorComparator > ObjectReflectorQueue;
    static ObjectReflectorQueue &getObjectReflectorQueue( void ) {
        static ObjectReflectorQueue objectReflectorQueue;
        return objectReflectorQueue;
    }

public:
    static void addObjectReflector( const ObjectReflector &objectReflector ) {
        getObjectReflectorQueue().insert( objectReflector );
    }

    static void addObjectReflector( int objectHandle, const RTI::AttributeHandleValuePairSet& theAttributes ) {
        addObjectReflector(  ObjectReflector( objectHandle, theAttributes )  );
    }
    static void addObjectReflector( int objectHandle, const RTI::AttributeHandleValuePairSet& theAttributes, const RTI::FedTime &theTime ) {
        addObjectReflector(  ObjectReflector( objectHandle, theAttributes, theTime )  );
    }

    static ObjectReflector getNextObjectReflector( void ) {
        if ( getObjectReflectorQueue().empty() ) return ObjectReflector();

        ObjectReflectorQueue::iterator orqItr = getObjectReflectorQueue().begin();
        ObjectReflector objectReflector = *orqItr;
        getObjectReflectorQueue().erase( orqItr );
        return objectReflector;
    }


    virtual void discoverObjectInstance( RTI::ObjectHandle theObject, RTI::ObjectClassHandle theObjectClass, const char *objectName )
     throw ( RTI::CouldNotDiscover, RTI::ObjectClassNotKnown, RTI::FederateInternalError) {
        ObjectRoot::discover( theObjectClass, theObject );
    }

    virtual void reflectAttributeValues( RTI::ObjectHandle theObject, const RTI::AttributeHandleValuePairSet& theAttributes, const char *theTag )
     throw ( RTI::ObjectNotKnown, RTI::AttributeNotKnown, RTI::FederateOwnsAttributes, RTI::FederateInternalError ) {
        addObjectReflector( theObject, theAttributes );
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
        addObjectReflector( theObject, theAttributes, theTime );
        RTIfedTime rtitime(theTime);
        double ltime = rtitime.getTime();
//        createLog(theObject, theAttributes, ltime);
    }

//    void createLog(
//        RTI::ObjectHandle theObject,
//        const RTI::AttributeHandleValuePairSet& theAttributes,
//        double time=0);
};

#endif
