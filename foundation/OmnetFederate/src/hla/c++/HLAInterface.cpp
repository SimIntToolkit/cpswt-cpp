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

#include <fstream>

#include <HLAInterface.h>
#include "C2WConsoleLogger.hpp"
#include <boost/lexical_cast.hpp>

#include "OmnetFOMInteractions.h"
#include "RTIRootHeaders.hpp"
#include "OmnetFOMMessageDefs.h"

#include "SubscribedInteractionFilter.hpp"

#include <inet/common/packet/Packet.h>

#include "CPSWTIpv4.h"


Define_Module(HLAInterface);


using AddRouteToRoutingTable = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::AddRouteToRoutingTable;
using DropRouteFromRoutingTable = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::DropRouteFromRoutingTable;

using CommandExecutionStatus = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::CommandExecutionStatus;

// USED IN HEADER FILE
//using C2WInteractionRoot = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot;

using EmbeddedMessaging = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::EmbeddedMessaging;

using OmnetCommand = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand;

using ObjectReflector = ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot::ObjectReflector;

using AddRouteToRoutingTable = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::AddRouteToRoutingTable;
using DropRouteFromRoutingTable = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::DropRouteFromRoutingTable;

using StartDataInjectionAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::AttacksNotYetImplemented_p::StartDataInjectionAttack;
using StopDataInjectionAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::AttacksNotYetImplemented_p::StopDataInjectionAttack;

using StartDNSPoisoningAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::AttacksNotYetImplemented_p::StartDNSPoisoningAttack;
using StopDNSPoisoningAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::AttacksNotYetImplemented_p::StopDNSPoisoningAttack;

using StartLinkAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::AttacksNotYetImplemented_p::StartLinkAttack;
using StopLinkAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::AttacksNotYetImplemented_p::StopLinkAttack;

using StartMasqueradingAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::AttacksNotYetImplemented_p::StartMasqueradingAttack;
using StopMasqueradingAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::AttacksNotYetImplemented_p::StopMasqueradingAttack;

using BecomeObservable = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::BecomeObservable;
using BecomeNotObservable = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::BecomeNotObservable;

using StartDelayNodeAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::StartDelayNodeAttack;
using StopDelayNodeAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::StopDelayNodeAttack;

using StartDisableNetworkAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::StartDisableNetworkAttack;
using StopDisableNetworkAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::StopDisableNetworkAttack;

using StartIntegrityAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::StartIntegrityAttack;
using StopIntegrityAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::StopIntegrityAttack;

using StartModifyFromHLAPacketsAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::StartModifyFromHLAPacketsAttack;
using StopModifyFromHLAPacketsAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::StopModifyFromHLAPacketsAttack;

using StartModifyToHLAPacketsAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::StartModifyToHLAPacketsAttack;
using StopModifyToHLAPacketsAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::StopModifyToHLAPacketsAttack;

using StartNetworkFilterAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::StartNetworkFilterAttack;
using StopNetworkFilterAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::StopNetworkFilterAttack;

using StartNetworkIPFirewall = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::StartNetworkIPFirewall;
using StopNetworkIPFirewall = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::StopNetworkIPFirewall;

using StartNodeAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::StartNodeAttack;
using StopNodeAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::StopNodeAttack;

using StartOutOfOrderPacketsAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::StartOutOfOrderPacketsAttack;
using StopOutOfOrderPacketsAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::StopOutOfOrderPacketsAttack;

using StartReplayAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::StartReplayAttack;
using StopReplayAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::StopReplayAttack;

using StartSnifferAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::StartSnifferAttack;
using StopSnifferAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::StopSnifferAttack;

using StartRecordingPacketsForReplayAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p
  ::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StartRecordingPacketsForReplayAttack;
using StopRecordingPacketsForReplayAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p
  ::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StopRecordingPacketsForReplayAttack;
using EraseRecordedPacketsForReplayAttack = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p
  ::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::EraseRecordedPacketsForReplayAttack;

using TakeOwnership = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::TakeOwnership;
using LoseOwnership = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::ActionBase_p::OmnetCommand_p::LoseOwnership;

using NetworkStatus = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::NetworkStatus;
using NetworkStatusRequest = ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p
  ::NetworkStatusRequest;


void HLAInterface::FederateHostConfig::assignFromJson(const Json::Value &jsonValue) {

    if (jsonValue.isMember("Host")) {
        host = jsonValue["Host"].asString();
    }
    if (jsonValue.isMember("HostApp")) {
        hostApp = jsonValue["HostApp"].asString();
    }
    if (jsonValue.isMember("AppIndex")) {
        appIndex = jsonValue["AppIndex"].asInt();
    }
    if (jsonValue.isMember("AppInterface")) {
        appInterface = jsonValue["AppInterface"].asString();
    }
}

void HLAInterface::initializeFederateHostConfigMap(const std::string &federateHostConfigJsonFileName) {

    Json::Value federate_host_config_json;

    std::ifstream federateHostConfigJsonInputStream(federateHostConfigJsonFileName);
    federateHostConfigJsonInputStream >> federate_host_config_json;
    federateHostConfigJsonInputStream.close();

    for(
      Json::Value::const_iterator fcmCit = federate_host_config_json.begin() ;
      fcmCit != federate_host_config_json.end() ;
      ++fcmCit
    ) {
        std::string federateName = fcmCit.key().asString();
        Json::Value hostConfig = federate_host_config_json[ federateName ];
        _federateNameToHostConfigMap.emplace(federateName, hostConfig);
    }
}

void HLAInterface::initializeFederateSequenceToMessagingInfoMap(
  const std::string &federateSequenceToMessagingInfoJsonFileName
) {

    Json::Value federate_sequence_to_messaging_info_json;

    std::ifstream federateSequenceToMessagingInfoJsonInputStream(federateSequenceToMessagingInfoJsonFileName);
    federateSequenceToMessagingInfoJsonInputStream >> federate_sequence_to_messaging_info_json;
    federateSequenceToMessagingInfoJsonInputStream.close();

    for(
      Json::Value::const_iterator fsmCit = federate_sequence_to_messaging_info_json.begin() ;
      fsmCit != federate_sequence_to_messaging_info_json.end() ;
      ++fsmCit
    ) {

        std::string receivingFullHlaClassName( fsmCit.key().asString() );

        _dynamicSoftSubscribeFullHlaClassNameSet.insert( receivingFullHlaClassName );
        _dynamicPublishFullHlaClassNameSet.insert( receivingFullHlaClassName );

        Json::Value federateSequenceMessagingInfoArray =
          federate_sequence_to_messaging_info_json[ receivingFullHlaClassName ];

        FederateSequenceMessagingInfoVectorMap federateSequenceMessagingInfoVectorMap;

        for(int ix = 0 ; ix < federateSequenceMessagingInfoArray.size() ; ++ix) {

            Json::Value federateSequenceMessagingInfoVectorJsonArray = federateSequenceMessagingInfoArray[ix];

            Json::Value federateSequenceJson = federateSequenceMessagingInfoVectorJsonArray[ "federate_sequence" ];
            StringList federateSequenceList;

            for(int jx = 0 ; jx < federateSequenceJson.size() ; ++jx) {
                federateSequenceList.push_back( federateSequenceJson[jx].asString() );
            }

            Json::Value messaging_info_json_array = federateSequenceMessagingInfoVectorJsonArray[ "messaging_info" ];

            MessagingInfoVector messagingInfoVector;
            for(int jx = 0 ; jx < messaging_info_json_array.size() ; ++jx) {

                Json::Value messaging_info_json = messaging_info_json_array[ jx ];

                std::string publishFederateName( messaging_info_json[ "full_hla_class_name" ].asString() );
                _dynamicPublishFullHlaClassNameSet.insert(
                  EmbeddedMessaging::get_hla_class_name() + "." + publishFederateName
                );

                MessagingInfo messagingInfo( publishFederateName, messaging_info_json[ "payload_size" ].asInt() );

                messagingInfoVector.push_back( messagingInfo );
            }

            federateSequenceMessagingInfoVectorMap.emplace(federateSequenceList, messagingInfoVector);
        }

        _messagingFederateSequenceMessagingInfoVectorMap[ receivingFullHlaClassName ] =
          federateSequenceMessagingInfoVectorMap;
    }

}

void HLAInterface::populateHlaMsg(
  HlaMsg &hlaMsg, const std::string &sendingFederateName, const std::string &receivingFederateName
) {

    {
        const FederateHostConfig &federateHostConfig = _federateNameToHostConfigMap[ sendingFederateName ];

        hlaMsg.setSenderHost( federateHostConfig.host.c_str() );
        hlaMsg.setSenderHostApp( federateHostConfig.hostApp.c_str() );
        hlaMsg.setSenderAppIndex( federateHostConfig.appIndex );
    }

    {
        const FederateHostConfig &federateHostConfig = _federateNameToHostConfigMap[ receivingFederateName ];

        hlaMsg.setReceiverHost( federateHostConfig.host.c_str() );
        hlaMsg.setReceiverHostApp( federateHostConfig.hostApp.c_str() );
        hlaMsg.setReceiverAppIndex( federateHostConfig.appIndex );
        hlaMsg.setReceiverAppInterface( federateHostConfig.appInterface.c_str() );
        hlaMsg.setReceiverFederateName( receivingFederateName.c_str() );
    }
}

void HLAInterface::processMessaging(
    const std::string &hlaClassName,
    const StringList &federateSequenceList,
    const InteractionRoot::SP &interactionRootSP,
    const ObjectReflector::SP &objectReflectorSP
) {

    MessagingFederateSequenceMessagingInfoVectorMap::const_iterator mfmCit =
      _messagingFederateSequenceMessagingInfoVectorMap.find( hlaClassName );
    if ( mfmCit == _messagingFederateSequenceMessagingInfoVectorMap.end() ) {
        BOOST_LOG_SEV(get_logger(), warning) << "No entry for HLA class \"" << hlaClassName
          << "\" in _messagingFederateSequenceMessagingInfoVectorMap: skipping ...";
        return;
    }

    // IF FEDERATE SEQUENCE IS EMPTY, SOMETHING IS WRONG
    if ( federateSequenceList.empty() ) {
        BOOST_LOG_SEV(get_logger(), warning) << "FederateSequence for instance of HLA class \""
          << hlaClassName << "\" is empty: skipping ...";
        return;
    }

    // MAKE SURE SENDING FEDERATE (LAST FEDERATE IN SEQUENCE) HAS A HOST ASSIGNED TO IT
    std::string sendingFederateName( federateSequenceList.back() );
    FederateNameToHostConfigMap::const_iterator fhmCit = _federateNameToHostConfigMap.find(sendingFederateName);
    if ( fhmCit == _federateNameToHostConfigMap.end() ) {
        BOOST_LOG_SEV(get_logger(), warning) << "Name of sending federate \"" << sendingFederateName
          << "\" not found in federate-host-config table: skipping ...";
        return;
    }
    const FederateSequenceMessagingInfoVectorMap &federateSequenceMessagingInfoVectorMap = mfmCit->second;

    // CHECK FOR FEDERATE SEQUENCE IN MAP
    // EACH federateSequenceListKey IN federateSequenceMessagingInfoVectorMap
    // IS MATCHED AGAINST THE LAST PORTION OF federateSequenceList
    FederateSequenceMessagingInfoVectorMap::const_iterator fmmCit;
    for(
      fmmCit = federateSequenceMessagingInfoVectorMap.begin() ;
      fmmCit != federateSequenceMessagingInfoVectorMap.end() ;
      ++fmmCit
    ) {
        const StringList &federateSequenceListKey = fmmCit->first;
        StringList::const_reverse_iterator fskCit = federateSequenceListKey.rbegin();
        StringList::const_reverse_iterator fslCit = federateSequenceList.rbegin();

        bool match = true;
        while(fskCit != federateSequenceListKey.rend() & fslCit != federateSequenceList.rend()) {
            if (*fskCit != *fslCit) {
                match = false;
                break;
            }
            ++fskCit;
            ++fslCit;
        }

        if (match && fskCit == federateSequenceListKey.rend()) {
            break;
        }
    }

    // IF NOT THERE, REPORT
    if ( fmmCit == federateSequenceMessagingInfoVectorMap.end() ) {
        std::string message = "No entry for federateSequence [ ";
        bool first = true;
        for(
          StringList::const_iterator fslCit = federateSequenceList.begin() ;
          fslCit != federateSequenceList.end() ;
          ++fslCit
        ) {
            if (first) {
                first = false;
            } else {
                message += ", ";
            }

            message += "\"" + *fslCit + "\"";
        }
        message += " ] for HLA class \"" + hlaClassName + "\": skipping ...";
        BOOST_LOG_SEV(get_logger(), warning) << message;
        return;
    }

    const MessagingInfoVector &messagingInfoVector = fmmCit->second;

    // OTHERWISE, TRANSLATE RECEIVED INTERACTION TO FEDERATE-SPECIFIC INTERACTIONS AND SEND THROUGH NETWORK
    for(
      MessagingInfoVector::const_iterator mivCit = messagingInfoVector.begin() ;
      mivCit != messagingInfoVector.end() ;
      ++mivCit
    ) {

        const MessagingInfo &messagingInfo( *mivCit );

        std::string publishFederateName( messagingInfo.getPublishFederateName() );

        // MAKE SURE THERE IS A HOST FOR THE RECEIVING FEDERATE
        FederateNameToHostConfigMap::const_iterator fhmCit = _federateNameToHostConfigMap.find(publishFederateName);
        if ( fhmCit == _federateNameToHostConfigMap.end() ) {
            BOOST_LOG_SEV(get_logger(), warning) << "Name of receiving federate \"" << publishFederateName
              << "\" not found in federate-host-config table: skipping ...";
            continue;
        }

        HlaMsg *hlaMsgPtr = new HlaMsg( getHlaMessageLabel().c_str() );
        hlaMsgPtr->setToHLA( true );
        hlaMsgPtr->setMessageNo( AttackCoordinator::getUniqueNo() );

        if (interactionRootSP) {
            InteractionRoot::SP interactionRootCopySP(new InteractionRoot(*interactionRootSP));
            hlaMsgPtr->setInteractionRootSP( interactionRootCopySP );
            hlaMsgPtr->setTimestamp( interactionRootCopySP->getTime() );
        } else {
            ObjectReflector::SP objectReflectorCopySP(new ObjectReflector(*objectReflectorSP));
            hlaMsgPtr->setObjectReflectorSP( objectReflectorCopySP );
            hlaMsgPtr->setTimestamp( objectReflectorCopySP->getTime() );
        }
        hlaMsgPtr->setByteLength( messagingInfo.getPayloadSize() );

        populateHlaMsg( *hlaMsgPtr, sendingFederateName, publishFederateName );

        auto c_packetChunk = inet::makeShared<inet::cPacketChunk>(hlaMsgPtr);
        inet::Packet *packet = new inet::Packet(getHlaMessageLabel().c_str(), c_packetChunk);

        // SEND PACKET TO "SENDER" HOST
        cModule *udpAppWrapperModule = AttackCoordinator::getSingleton().getAppSpecModule(
                hlaMsgPtr->getSenderHost(), hlaMsgPtr->getSenderHostApp(), hlaMsgPtr->getSenderAppIndex()
        );
        if ( udpAppWrapperModule != 0 ) {
           sendDirect( packet, udpAppWrapperModule, "hlaIn" );
        } else {
            BOOST_LOG_SEV(get_logger(), warning)
              << "HLAInterface:  could not find module corresponding to (hostname,appName) = ("
              << hlaMsgPtr->getSenderHost() << "," << hlaMsgPtr->getSenderHostApp() << ")\nCurrent modules are: "
              << AttackCoordinator::getSingleton().listAppSpecProperties();
        }
    }

}

void HLAInterface::processInteractions() {

    InteractionRoot::SP interactionRootSP;
    while(  ( interactionRootSP = getNextInteraction() ) != 0  ) {

        BOOST_LOG_SEV(get_logger(), severity_level::info) << "Processing interaction of type \""
          << interactionRootSP->getInstanceHlaClassName() << "\"";

        int classHandle = interactionRootSP->getClassHandle();

        // IS INTERACTION ONE THAT MIGHT BE PROPAGATED THROUGH THE SIMULATED NETWORK?
        if ( interactionRootSP->isDynamicInstance() ) {

            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Interaction \""
              << interactionRootSP->getInstanceHlaClassName() << "\" is dynamic";
            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Interaction: " << interactionRootSP;

            // GET FULL HLA CLASS NAME OF INTERACTION
            std::string instanceHlaClassName = interactionRootSP->getInstanceHlaClassName();

            // IS THIS CLASS NAME ONE THAT COULD BE PROPAGATED?
            // IF SO, CHECK SEQUENCE OF FEDERATES IT CAME TRHOUGH
            StringList federateSequenceList(  C2WInteractionRoot::get_federate_sequence_list( *interactionRootSP )  );

            processMessaging(instanceHlaClassName, federateSequenceList, interactionRootSP, ObjectReflector::SP());

            continue;
        }

        if (  NetworkStatusRequest::match( classHandle) ) {
            NetworkStatus networkStatus;
            networkStatus.set_networkStatusJson(AttackCoordinator::getSingleton().getStatus());
            networkStatus.set_actualLogicalGenerationTime(getCurrentTime());
            networkStatus.set_federateFilter("");
            sendInteraction(networkStatus);
            continue;
        }

        if (  BecomeObservable::match( classHandle )) {
            BecomeObservable::SP becomeObservableSP = boost::static_pointer_cast<BecomeObservable>(interactionRootSP);

            std::string nodeFullPath = becomeObservableSP->get_nodeFullPath();
            std::string observerId = becomeObservableSP->get_observerId();

            AttackCoordinator::getSingleton().setObservable(nodeFullPath, observerId, true);
            continue;
        }

        if (  BecomeNotObservable::match( classHandle )) {
            BecomeNotObservable::SP becomeNotObservableSP = \
              boost::static_pointer_cast<BecomeNotObservable>(interactionRootSP);

            std::string nodeFullPath = becomeNotObservableSP->get_nodeFullPath();
            std::string observerId = becomeNotObservableSP->get_observerId();

            AttackCoordinator::getSingleton().setObservable(nodeFullPath, observerId, false);
            continue;
        }

        if (  StartNodeAttack::match( classHandle )  ) {
            StartNodeAttack::SP startNodeAttackSP = boost::static_pointer_cast< StartNodeAttack >( interactionRootSP );

            std::string nodeFullPath = startNodeAttackSP->get_nodeFullPath();

            AttackCoordinator::getSingleton().setNodeAttack( nodeFullPath, true );
            continue;
        }


        if (  StopNodeAttack::match( classHandle )  ) {
            StopNodeAttack::SP stopNodeAttackSP = boost::static_pointer_cast< StopNodeAttack >( interactionRootSP );

            std::string nodeFullPath = stopNodeAttackSP->get_nodeFullPath();

            AttackCoordinator::getSingleton().setNodeAttack( nodeFullPath, false );
            continue;
        }


        if (  StartDelayNodeAttack::match( classHandle )  ) {
            StartDelayNodeAttack::SP startDelayNodeAttackSP =
              boost::static_pointer_cast< StartDelayNodeAttack >( interactionRootSP );

            std::string nodeFullPath = startDelayNodeAttackSP->get_nodeFullPath();
            float mean = startDelayNodeAttackSP->get_delayMean();
            float standardDeviation = startDelayNodeAttackSP->get_delayStdDev();

            AttackCoordinator::getSingleton().startDelayNodeAttack(nodeFullPath, mean, standardDeviation);
            continue;
        }


        if (  StopDelayNodeAttack::match( classHandle )  ) {
            StopDelayNodeAttack::SP stopDelayNodeAttackSP =
              boost::static_pointer_cast< StopDelayNodeAttack >( interactionRootSP );

            std::string nodeFullPath = stopDelayNodeAttackSP->get_nodeFullPath();

            AttackCoordinator::getSingleton().stopDelayNodeAttack(nodeFullPath);
            continue;
        }


        if (  StartSnifferAttack::match( classHandle )  ) {
            StartSnifferAttack::SP startSnifferAttackSP =
              boost::static_pointer_cast< StartSnifferAttack >( interactionRootSP );

            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received START SNIFFER ATTACK: "
              << startSnifferAttackSP;
            std::string nodeFullPath = startSnifferAttackSP->get_nodeFullPath();

            SnifferAttackMsg *snifferAttackMsg = new SnifferAttackMsg;
            snifferAttackMsg->setListenerNodeFullPath( startSnifferAttackSP->get_listenerNodeFullPath().c_str() );
            snifferAttackMsg->setListenerInterface( startSnifferAttackSP->get_listenerInterface().c_str() );
            snifferAttackMsg->setListen( true );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  snifferAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                BOOST_LOG_SEV(get_logger(), warning) << "StartSnifferAttack:  NO MODULE FOR NODE \""
                  << nodeFullPath << "\".  Current modules are:  "
                  << AttackCoordinator::getSingleton().listIPModuleProperties();
            }
            continue;
        }

        if (  StopSnifferAttack::match( classHandle )  ) {
            StopSnifferAttack::SP stopSnifferAttackSP =
              boost::static_pointer_cast< StopSnifferAttack >( interactionRootSP );

            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received STOP SNIFFER ATTACK: "
              << stopSnifferAttackSP;

            std::string nodeFullPath = stopSnifferAttackSP->get_nodeFullPath();

            SnifferAttackMsg *snifferAttackMsg = new SnifferAttackMsg;
            snifferAttackMsg->setListenerNodeFullPath( stopSnifferAttackSP->get_listenerNodeFullPath().c_str() );
            snifferAttackMsg->setListenerInterface( stopSnifferAttackSP->get_listenerInterface().c_str() );
            snifferAttackMsg->setListen( false );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  snifferAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                BOOST_LOG_SEV(get_logger(), warning) << "StopSnifferAttack:  NO MODULE FOR NODE \""
                  << nodeFullPath << "\".  Current modules are:  "
                  << AttackCoordinator::getSingleton().listIPModuleProperties();
            }
            continue;
        }

        if (  StartNetworkFilterAttack::match( classHandle )  ) {
            StartNetworkFilterAttack::SP startNetworkFilterAttackSP =
              boost::static_pointer_cast< StartNetworkFilterAttack >( interactionRootSP );

            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received START NETWORK FILTER ATTACK: "
              << startNetworkFilterAttackSP;

            std::string recordingNodeFullPath = startNetworkFilterAttackSP->get_nodeFullPath();

            FilterAttackMsg *filterAttackMsg = new FilterAttackMsg;
            filterAttackMsg->setSourceNetworkAddress( startNetworkFilterAttackSP->get_srcNetworkAddress().c_str() );
            filterAttackMsg->setDestinationNetworkAddress( startNetworkFilterAttackSP->get_dstNetworkAddress().c_str() );
            filterAttackMsg->setEnable( true );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( recordingNodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  filterAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                BOOST_LOG_SEV(get_logger(), warning) << "StartNetworkFilterAttack:  NO MODULE FOR NODE \""
                  << recordingNodeFullPath << "\"";
            }
            continue;
        }

        if (  StopNetworkFilterAttack::match( classHandle )  ) {
            StopNetworkFilterAttack::SP stopNetworkFilterAttackSP =
              boost::static_pointer_cast< StopNetworkFilterAttack >( interactionRootSP );

            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received STOP NETWORK FILTER ATTACK: "
              << stopNetworkFilterAttackSP;

            std::string recordingNodeFullPath = stopNetworkFilterAttackSP->get_nodeFullPath();

            FilterAttackMsg *filterAttackMsg = new FilterAttackMsg;
            filterAttackMsg->setSourceNetworkAddress( stopNetworkFilterAttackSP->get_srcNetworkAddress().c_str() );
            filterAttackMsg->setDestinationNetworkAddress( stopNetworkFilterAttackSP->get_dstNetworkAddress().c_str() );
            filterAttackMsg->setEnable( false );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( recordingNodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  filterAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                BOOST_LOG_SEV(get_logger(), warning) << "StopNetworkFilterAttack:  NO MODULE FOR NODE \""
                  << recordingNodeFullPath << "\"";
            }
            continue;
        }

        if (  StartNetworkIPFirewall::match( classHandle )  ) {
            StartNetworkIPFirewall::SP startNetworkIPFirewallSP =
              boost::static_pointer_cast< StartNetworkIPFirewall >( interactionRootSP );

            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received START NETWORK IP FIREWALL: "
              << startNetworkIPFirewallSP;

            std::string nodeFullPath = startNetworkIPFirewallSP->get_nodeFullPath();

            IPFirewallMsg *ipFirewallMsg = new IPFirewallMsg;
            ipFirewallMsg->setSourceNetworkAddress( startNetworkIPFirewallSP->get_srcNetworkAddress().c_str() );
            ipFirewallMsg->setDestinationNetworkAddress( startNetworkIPFirewallSP->get_dstNetworkAddress().c_str() );
            ipFirewallMsg->setEnable( true );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  ipFirewallMsg, cModulePtr, "hlaIn"  );
            } else {
                BOOST_LOG_SEV(get_logger(), warning) << "StartNetworkIPFirewall:  NO MODULE FOR NODE \""
                  << nodeFullPath << "\"";
            }
            continue;
        }

        if (  StopNetworkIPFirewall::match( classHandle )  ) {
            StopNetworkIPFirewall::SP stopNetworkIPFirewallSP =
              boost::static_pointer_cast< StopNetworkIPFirewall >( interactionRootSP );

            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received STOP NETWORK IP FIREWALL: "
              << stopNetworkIPFirewallSP;

            std::string nodeFullPath = stopNetworkIPFirewallSP->get_nodeFullPath();

            IPFirewallMsg *ipFirewallMsg = new IPFirewallMsg;
            ipFirewallMsg->setSourceNetworkAddress( stopNetworkIPFirewallSP->get_srcNetworkAddress().c_str() );
            ipFirewallMsg->setDestinationNetworkAddress( stopNetworkIPFirewallSP->get_dstNetworkAddress().c_str() );
            ipFirewallMsg->setEnable( false );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  ipFirewallMsg, cModulePtr, "hlaIn"  );
            } else {
                BOOST_LOG_SEV(get_logger(), warning) << "StopNetworkIPFirewall:  NO MODULE FOR NODE \""
                  << nodeFullPath << "\"";
            }
            continue;
        }

        if (  StartDisableNetworkAttack::match( classHandle )  ) {

            StartDisableNetworkAttack::SP startDisableNetworkAttackSP =
              boost::static_pointer_cast< StartDisableNetworkAttack >( interactionRootSP );

            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received START DISABLE NETWORK ATTACK: "
              << startDisableNetworkAttackSP;

            std::string networkAddressStr = startDisableNetworkAttackSP->get_networkAddress();

            AttackCoordinator::NetworkAddress networkAddress( networkAddressStr );
            AttackCoordinator::CModuleSet cModuleSet = AttackCoordinator::getSingleton().getCModuleSet(networkAddress);

            if (cModuleSet.empty()) {
                BOOST_LOG_SEV(get_logger(), warning) << "StartDisableNetworkAttack:  CModuleSet for network \""
                  << networkAddressStr << "\" is empty.";
            } else {
                for(
                  AttackCoordinator::CModuleSet::iterator cmsItr = cModuleSet.begin() ;
                  cmsItr != cModuleSet.end() ;
                  ++cmsItr
                ) {
                    NetworkAttackMsg *networkAttackMsg = new NetworkAttackMsg;
                    networkAttackMsg->setNetworkAddress( networkAddressStr.c_str() );
                    networkAttackMsg->setEnable( true );

                    sendDirect(  networkAttackMsg, *cmsItr, "hlaIn"  );
                }
            }

            continue;
        }

        if (  StopDisableNetworkAttack::match( classHandle )  ) {
            StopDisableNetworkAttack::SP stopDisableNetworkAttackSP =
              boost::static_pointer_cast< StopDisableNetworkAttack >( interactionRootSP );

            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received STOP DISABLE NETWORK ATTACK: "
              << stopDisableNetworkAttackSP;

            std::string networkAddressStr = stopDisableNetworkAttackSP->get_networkAddress();

            AttackCoordinator::NetworkAddress networkAddress( networkAddressStr );
            AttackCoordinator::CModuleSet cModuleSet = AttackCoordinator::getSingleton().getCModuleSet(networkAddress);

            if (cModuleSet.empty()) {
                BOOST_LOG_SEV(get_logger(), warning) << "StopDisableNetworkAttack:  CModuleSet for network \""
                  << networkAddressStr << "\" is empty.";
            } else {
                for(
                  AttackCoordinator::CModuleSet::iterator cmsItr = cModuleSet.begin() ;
                  cmsItr != cModuleSet.end() ;
                  ++cmsItr
                ) {
                    NetworkAttackMsg *networkAttackMsg = new NetworkAttackMsg;
                    networkAttackMsg->setNetworkAddress( networkAddressStr.c_str() );
                    networkAttackMsg->setEnable( false );

                    sendDirect(  networkAttackMsg, *cmsItr, "hlaIn"  );
                }
            }

            continue;
        }

        if (  StartRecordingPacketsForReplayAttack::match( classHandle )  ) {
            StartRecordingPacketsForReplayAttack::SP startRecordingPacketsForReplayAttackSP =
              boost::static_pointer_cast< StartRecordingPacketsForReplayAttack >( interactionRootSP );

            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received RECORD PACKETS FOR REPLAY ATTACK: "
              << startRecordingPacketsForReplayAttackSP;

            std::string nodeFullPath = startRecordingPacketsForReplayAttackSP->get_recordingNodeFullPath();

            RecordReplayAttackMsg *recordReplayAttackMsg = new RecordReplayAttackMsg;
            recordReplayAttackMsg->setSourceNetworkAddress(
              startRecordingPacketsForReplayAttackSP->get_srcNetworkAddress().c_str()
            );
            recordReplayAttackMsg->setDestinationNetworkAddress(
              startRecordingPacketsForReplayAttackSP->get_dstNetworkAddress().c_str()
            );
            recordReplayAttackMsg->setRecordDuration( 0 );
            recordReplayAttackMsg->setEnable( true );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  recordReplayAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                BOOST_LOG_SEV(get_logger(), warning) << "RecordPacketsForReplayAttack:  NO MODULE FOR NODE \""
                  << nodeFullPath << "\"";
            }
            continue;
        }

        if (  StopRecordingPacketsForReplayAttack::match( classHandle )  ) {
            StopRecordingPacketsForReplayAttack::SP stopRecordingPacketsForReplayAttackSP =
              boost::static_pointer_cast< StopRecordingPacketsForReplayAttack >( interactionRootSP );

            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received TERMINATE REPLAY ATTACK: "
              << stopRecordingPacketsForReplayAttackSP;

            std::string nodeFullPath = stopRecordingPacketsForReplayAttackSP->get_recordingNodeFullPath();

            RecordReplayAttackMsg *recordReplayAttackMsg = new RecordReplayAttackMsg;
            recordReplayAttackMsg->setSourceNetworkAddress( stopRecordingPacketsForReplayAttackSP->get_srcNetworkAddress().c_str() );
            recordReplayAttackMsg->setDestinationNetworkAddress(
              stopRecordingPacketsForReplayAttackSP->get_dstNetworkAddress().c_str()
            );
            recordReplayAttackMsg->setRecordDuration( -1 );
            recordReplayAttackMsg->setEnable( false );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  recordReplayAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                BOOST_LOG_SEV(get_logger(), warning) << "TerminateReplayAttack:  NO MODULE FOR NODE \""
                  << nodeFullPath << "\"";
            }
            continue;
        }

        if (  StartReplayAttack::match( classHandle )  ) {
            StartReplayAttack::SP startReplayAttackSP =
              boost::static_pointer_cast< StartReplayAttack >( interactionRootSP );

            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received START REPLAY ATTACK: "
              << startReplayAttackSP;

            std::string nodeFullPath = startReplayAttackSP->get_recordingNodeFullPath();

            ReplayAttackMsg *replayAttackMsg = new ReplayAttackMsg;
            replayAttackMsg->setSourceNetworkAddress( startReplayAttackSP->get_srcNetworkAddress().c_str() );
            replayAttackMsg->setDestinationNetworkAddress( startReplayAttackSP->get_dstNetworkAddress().c_str() );
            replayAttackMsg->setPlay( true );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  replayAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                BOOST_LOG_SEV(get_logger(), warning) << "StartReplayAttack:  NO MODULE FOR NODE \""
                  << nodeFullPath << "\"";
            }
            continue;
        }

//        if (  CeaseReplayAttack::match( classHandle )  ) {
//            CeaseReplayAttack::SP ceaseReplayAttackSP =
//              boost::static_pointer_cast< CeaseReplayAttack >( interactionRootSP );
//
//            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received CEASE REPLAY ATTACK: "
//              << ceaseReplayAttackSP;
//
//            std::string nodeFullPath = ceaseReplayAttackSP->get_recordingNodeFullPath();
//
//            ReplayAttackMsg *replayAttackMsg = new ReplayAttackMsg;
//            replayAttackMsg->setSourceNetworkAddress( ceaseReplayAttackSP->get_srcNetworkAddress().c_str() );
//            replayAttackMsg->setDestinationNetworkAddress( ceaseReplayAttackSP->get_dstNetworkAddress().c_str() );
//            replayAttackMsg->setPlay( false );
//
//            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
//            if ( cModulePtr != 0 ) {
//                sendDirect(  replayAttackMsg, cModulePtr, "hlaIn"  );
//            } else {
//                BOOST_LOG_SEV(get_logger(), warning) << "CeaseReplayAttack:  NO MODULE FOR NODE \""
//                  << nodeFullPath << "\"";
//            }
//            continue;
//        }

        if (  StartOutOfOrderPacketsAttack::match( classHandle )  ) {
            StartOutOfOrderPacketsAttack::SP startOutOfOrderPacketsAttackSP =
              boost::static_pointer_cast< StartOutOfOrderPacketsAttack >( interactionRootSP );

            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received START OUT-OF-ORDER PACKETS ATTACK: "
              << startOutOfOrderPacketsAttackSP;

            std::string nodeFullPath = startOutOfOrderPacketsAttackSP->get_nodeFullPath();

            OutOfOrderAttackMsg *outOfOrderAttackMsg = new OutOfOrderAttackMsg;
            outOfOrderAttackMsg->setSourceNetworkAddress(
              startOutOfOrderPacketsAttackSP->get_srcNetworkAddress().c_str()
            );
            outOfOrderAttackMsg->setDestinationNetworkAddress(
              startOutOfOrderPacketsAttackSP->get_dstNetworkAddress().c_str()
            );
            outOfOrderAttackMsg->setRecordDuration( startOutOfOrderPacketsAttackSP->get_recordDurationInSecs() );
            outOfOrderAttackMsg->setPlay( true );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  outOfOrderAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                BOOST_LOG_SEV(get_logger(), warning) << "StartOutOfOrderPacketsAttack:  NO MODULE FOR NODE \""
                  << nodeFullPath << "\"";
            }
            continue;
        }

        if (  StopOutOfOrderPacketsAttack::match( classHandle )  ) {
            StopOutOfOrderPacketsAttack::SP stopOutOfOrderPacketsAttackSP =
              boost::static_pointer_cast< StopOutOfOrderPacketsAttack >( interactionRootSP );

            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received STOP OUT-OF-ORDER PACKETS ATTACK: "
              << stopOutOfOrderPacketsAttackSP;

            std::string nodeFullPath = stopOutOfOrderPacketsAttackSP->get_nodeFullPath();

            OutOfOrderAttackMsg *outOfOrderAttackMsg = new OutOfOrderAttackMsg;
            outOfOrderAttackMsg->setSourceNetworkAddress(
              stopOutOfOrderPacketsAttackSP->get_srcNetworkAddress().c_str()
            );
            outOfOrderAttackMsg->setDestinationNetworkAddress(
              stopOutOfOrderPacketsAttackSP->get_dstNetworkAddress().c_str()
            );
            outOfOrderAttackMsg->setRecordDuration( -1 );
            outOfOrderAttackMsg->setPlay( false );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  outOfOrderAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                BOOST_LOG_SEV(get_logger(), warning) << "StopOutOfOrderPacketsAttack:  NO MODULE FOR NODE \""
                  << nodeFullPath << "\"";
            }
            continue;
        }

        if ( AddRouteToRoutingTable::match( classHandle ) ) {
            AddRouteToRoutingTable::SP addRouteToRoutingTableSP =
              boost::static_pointer_cast< AddRouteToRoutingTable >( interactionRootSP );

            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received ADD ROUTE TO ROUTING TABLE: "
              << addRouteToRoutingTableSP;

            std::string nodeFullPath = addRouteToRoutingTableSP->get_nodeFullPath();
            std::string interfaceEntry = addRouteToRoutingTableSP->get_interfaceEntry();
            AttackCoordinator::NetworkAddress networkAddress( addRouteToRoutingTableSP->get_networkAddress() );
            AttackCoordinator::NetworkAddress gatewayAddress( addRouteToRoutingTableSP->get_gatewayAddress() );

            AttackCoordinator::RouteEntrySP routeEntrySP = AttackCoordinator::getSingleton().createRouteEntrySP(
              nodeFullPath, interfaceEntry, networkAddress, gatewayAddress
            );

            AddRouteEntryMsg *addRouteEntryMsg = new AddRouteEntryMsg;
            addRouteEntryMsg->setRouteEntrySP( routeEntrySP );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect( addRouteEntryMsg, cModulePtr, "hlaIn" );
            } else {
                BOOST_LOG_SEV(get_logger(), warning) << "AddRouteToRoutingTable:  NO MODULE FOR NODE \""
                  << nodeFullPath << "\"";
            }
            continue;
        }

        if ( DropRouteFromRoutingTable::match( classHandle ) ) {
            DropRouteFromRoutingTable::SP dropRouteFromRoutingTableSP =
             boost::static_pointer_cast< DropRouteFromRoutingTable >( interactionRootSP );

            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received DROP ROUTE FROM ROUTING TABLE: "
              << dropRouteFromRoutingTableSP;

            std::string nodeFullPath = dropRouteFromRoutingTableSP->get_nodeFullPath();
            std::string interfaceEntry = dropRouteFromRoutingTableSP->get_interfaceEntry();
            AttackCoordinator::NetworkAddress networkAddress( dropRouteFromRoutingTableSP->get_networkAddress() );
            AttackCoordinator::NetworkAddress gatewayAddress( dropRouteFromRoutingTableSP->get_gatewayAddress() );

            AttackCoordinator::RouteEntrySP routeEntrySP = AttackCoordinator::getSingleton().createRouteEntrySP(
              nodeFullPath, interfaceEntry, networkAddress, gatewayAddress
            );

            DropRouteEntryMsg *dropRouteEntryMsg = new DropRouteEntryMsg;
            dropRouteEntryMsg->setRouteEntrySP( routeEntrySP );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect( dropRouteEntryMsg, cModulePtr, "hlaIn" );
            } else {
                BOOST_LOG_SEV(get_logger(), warning) << "DropRouteFromRoutingTable:  NO MODULE FOR NODE \""
                  << nodeFullPath << "\"";
            }
            continue;
        }

        if ( StartModifyToHLAPacketsAttack::match( classHandle ) ) {
            StartModifyToHLAPacketsAttack::SP startModifyToHLAPacketsAttackSP =
             boost::static_pointer_cast< StartModifyToHLAPacketsAttack >( interactionRootSP );

            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received START MODIFY TO HLA PACKETS ATTACK: "
              << startModifyToHLAPacketsAttackSP;

            std::string nodeFullPath = startModifyToHLAPacketsAttackSP->get_nodeFullPath();

            AttackCoordinator::getSingleton().setModifyToHLAPackets( nodeFullPath, true );
            continue;
        }

        if ( StopModifyToHLAPacketsAttack::match( classHandle ) ) {
            StopModifyToHLAPacketsAttack::SP stopModifyToHLAPacketsAttackSP =
             boost::static_pointer_cast< StopModifyToHLAPacketsAttack >( interactionRootSP );

            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received STOP MODIFY TO HLA PACKETS ATTACK: "
              << stopModifyToHLAPacketsAttackSP;

            std::string nodeFullPath = stopModifyToHLAPacketsAttackSP->get_nodeFullPath();

            AttackCoordinator::getSingleton().setModifyToHLAPackets( nodeFullPath, false );
            continue;
        }

        if ( StartModifyFromHLAPacketsAttack::match( classHandle ) ) {
            StartModifyFromHLAPacketsAttack::SP startModifyFromHLAPacketsAttackSP =
             boost::static_pointer_cast< StartModifyFromHLAPacketsAttack >( interactionRootSP );

            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received START MODIFY FROM HLA PACKETS ATTACK: "
              << startModifyFromHLAPacketsAttackSP;

            std::string nodeFullPath = startModifyFromHLAPacketsAttackSP->get_nodeFullPath();

            AttackCoordinator::getSingleton().setModifyFromHLAPackets( nodeFullPath, true );
            continue;
        }

        if ( StopModifyFromHLAPacketsAttack::match( classHandle ) ) {
            StopModifyFromHLAPacketsAttack::SP stopModifyFromHLAPacketsAttackSP =
             boost::static_pointer_cast< StopModifyFromHLAPacketsAttack >( interactionRootSP );

            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received STOP MODIFY FROM HLA PACKETS ATTACK: "
              << stopModifyFromHLAPacketsAttackSP;

            std::string nodeFullPath = stopModifyFromHLAPacketsAttackSP->get_nodeFullPath();

            AttackCoordinator::getSingleton().setModifyFromHLAPackets( nodeFullPath, false );
            continue;
        }

        if ( StartIntegrityAttack::match( classHandle ) ) {
            StartIntegrityAttack::SP startIntegrityAttackSP =
             boost::static_pointer_cast< StartIntegrityAttack >( interactionRootSP );

            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received START INTEGRITY ATTACK: "
              << startIntegrityAttackSP;

            std::string nodeFullPath = startIntegrityAttackSP->get_nodeFullPath();

            AttackCoordinator::getSingleton().enableIntegrityAttack(
                    nodeFullPath,
                    startIntegrityAttackSP->get_intMultiplier(),
                    startIntegrityAttackSP->get_intAdder(),
                    startIntegrityAttackSP->get_longMultiplier(),
                    startIntegrityAttackSP->get_longAdder(),
                    startIntegrityAttackSP->get_doubleMultiplier(),
                    startIntegrityAttackSP->get_doubleAdder(),
                    startIntegrityAttackSP->get_booleanEnableFlip(),
                    startIntegrityAttackSP->get_stringReplacement()
            );
            continue;
        }

        if ( StopIntegrityAttack::match( classHandle ) ) {
            StopIntegrityAttack::SP stopIntegrityAttackSP =
             boost::static_pointer_cast< StopIntegrityAttack >( interactionRootSP );

            BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received STOP INTEGRITY ATTACK: "
              << stopIntegrityAttackSP;

            std::string nodeFullPath = stopIntegrityAttackSP->get_nodeFullPath();
            AttackCoordinator::getSingleton().disableIntegrityAttack( nodeFullPath );
            continue;
        }

        if (  TakeOwnership::match( classHandle )) {
            TakeOwnership::SP takeOwnershipSP = boost::static_pointer_cast<TakeOwnership>(interactionRootSP);

            std::string nodeFullPath = takeOwnershipSP->get_nodeFullPath();
            std::string ownerId = takeOwnershipSP->get_ownerId();

            AttackCoordinator::getSingleton().setOwnership(nodeFullPath, ownerId, true);
            continue;
        }

        if (  LoseOwnership::match( classHandle )) {
            LoseOwnership::SP loseOwnershipSP = boost::static_pointer_cast<LoseOwnership>(interactionRootSP);

            std::string nodeFullPath = loseOwnershipSP->get_nodeFullPath();
            std::string ownerId = loseOwnershipSP->get_ownerId();

            AttackCoordinator::getSingleton().setOwnership(nodeFullPath, ownerId, false);
            continue;
        }

        //
        // PROCESSING FOR ATTACK-DIRECTIVE INTERACTIONS
        //

        BOOST_LOG_SEV(get_logger(), warning) << "HLAInterface:  received unexpected interaction: "
          << interactionRootSP;
    }

}

void HLAInterface::processObjectReflectors() {

    Enter_Method( "processObjectReflectors" );

    ObjectReflector::SP objectReflectorSP;
    while(  ( objectReflectorSP = getNextObjectReflectorSP() ) != 0  ) {

        // GET FULL HLA CLASS NAME OF INTERACTION
        std::string hlaClassName = objectReflectorSP->getHlaClassName();
        BOOST_LOG_SEV(get_logger(), severity_level::info) << "Received reflector for \"" << hlaClassName << "\": "
          << "Reflector: " << objectReflectorSP;
        // IS THIS CLASS NAME ONE THAT COULD BE PROPAGATED?
        // IF SO, CHECK SEQUENCE OF FEDERATES IT CAME TRHOUGH
        StringList federateSequenceList(
          C2WInteractionRoot::get_federate_sequence_list( objectReflectorSP->getFederateSequence() )
        );

        processMessaging(hlaClassName, federateSequenceList, InteractionRoot::SP(), objectReflectorSP);
    }
}

void HLAInterface::hlaArrival() {
    Enter_Method_Silent( "hlaArrival" );
    if ( _noHlaArrivalFlag ) {
        scheduleAt( omnetpp::simTime(), _hlaArrivalMsg );
        _noHlaArrivalFlag = false;
    }
}

void HLAInterface::receiveInteraction(
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
    static bool notPrinted = true;
    if ( notPrinted ) {
        BOOST_LOG_SEV(get_logger(), severity_level::info) << AttackCoordinator::getSingleton().listAppSpecProperties();
        notPrinted = false;
    }

    InteractionRoot::SP interactionRootSP = InteractionRoot::create_interaction(theInteraction, theParameters, theTime);
    C2WInteractionRoot::SP c2wInteractionRootSP = boost::dynamic_pointer_cast< C2WInteractionRoot >(interactionRootSP);

    // Filter interaction if src/origin fed requirements (if any) are met
    if (
      c2wInteractionRootSP != 0 &&
        SubscribedInteractionFilter::get_singleton().filterC2WInteraction(getFederateId(), c2wInteractionRootSP)
    ) {
        return;
    }

    Super::receiveInteraction( theInteraction, theParameters, theTime, theTag, theHandle );

    hlaArrival();
}

void HLAInterface::receiveInteraction(
 RTI::InteractionClassHandle theInteraction,
 const RTI::ParameterHandleValuePairSet& theParameters,
 const char *theTag
)
 throw ( RTI::InteractionClassNotKnown, RTI::InteractionParameterNotKnown, RTI::FederateInternalError ) {

    InteractionRoot::SP interactionRootSP = InteractionRoot::create_interaction(theInteraction, theParameters);
    C2WInteractionRoot::SP c2wInteractionRootSP = boost::dynamic_pointer_cast< C2WInteractionRoot >(interactionRootSP);
    if (
      c2wInteractionRootSP != 0 &&
      SubscribedInteractionFilter::get_singleton().filterC2WInteraction(getFederateId(), c2wInteractionRootSP)
    ) {
        return;
    }

    Super::receiveInteraction(theInteraction, theParameters, theTag);

    hlaArrival();
}

HLAInterface::HLAInterface() :
 cSimpleModule(), SynchronizedFederate(),
 _hlaArrivalMsg(  new omnetpp::cMessage( "hlaArrival" )  ),
 _noHlaArrivalFlag( true )
{
    setInstancePtr( this );
}

HLAInterface::~HLAInterface() throw() { }


void HLAInterface::initialize(int stage) {
    // UDPEndpointApp registers at stage 0
    // HLAInterface initializes at stage 1

    if ( stage == inet::INITSTAGE_LOCAL ) {

        setFederationId(par( "federation_name" ).stringValue());
        setFederateId(par( "federate_name" ).stringValue());
        setFederateType(getFederateId());
        setStepSize(par( "federate_step_size" ).doubleValue());
        setLookahead(par( "federate_lookahead" ).doubleValue());

        setFederationJsonFileName( par( "federation_json_file_name" ).stringValue() );
        setFederateDynamicMessagingClassesJsonFileName(par("dynamic_messaging_classes_json_file_name").stringValue());

        std::string federateHostConfigJsonFileName = par("federate_host_config_json_file_name").stringValue();

        initializeFederateHostConfigMap(federateHostConfigJsonFileName);

        std::string federateSequenceToMessagingInfoJsonFileName =
          par("federate_sequence_to_messaging_info_json_file_name").stringValue();

        initializeFederateSequenceToMessagingInfoMap(federateSequenceToMessagingInfoJsonFileName);

        setup();
    }

    if ( stage == inet::INITSTAGE_LAST ) {
        BOOST_LOG_SEV(get_logger(), severity_level::info) << "AppSpecProperties:"
          << AttackCoordinator::getSingleton().listAppSpecProperties();
        BOOST_LOG_SEV(get_logger(), severity_level::info) << AttackCoordinator::getSingleton().getStatus();
    }
}

void HLAInterface::setup() {

    const char *c2wdburl = getenv( "C2WDBURL" );
    std::string dburl(c2wdburl == nullptr ? "" : c2wdburl);

    const char *c2wdbfile = getenv( "C2WDBFILE" );
    std::string dbname(c2wdbfile == nullptr? "" : c2wdbfile);

    if ( !dbname.empty() ) {

        ArgVector argVector;
        argVector.push_back(dbname);

        if ( !dburl.empty() ) {
            argVector.push_back(dburl);
        }
        C2WConsoleLogger::get_singleton().init( argVector );

        _logLevel = getenv( "C2WLOGLEVEL" );
    }

    // Join the federation
    createRTI();
    joinFederation();

    enableTimeConstrained();
    enableTimeRegulation( getLookahead() );
    enableAsynchronousDelivery();

    // publish interactions
    CommandExecutionStatus::publish_interaction( getRTI() );

    NetworkStatus::publish_interaction( getRTI() );

    // subscribe interactions
    AddRouteToRoutingTable::subscribe_interaction( getRTI() );
    DropRouteFromRoutingTable::subscribe_interaction( getRTI() );
    BecomeObservable::subscribe_interaction( getRTI() );
    BecomeNotObservable::subscribe_interaction( getRTI() );
    StartDelayNodeAttack::subscribe_interaction( getRTI() );
    StopDelayNodeAttack::subscribe_interaction( getRTI() );
    StartDisableNetworkAttack::subscribe_interaction( getRTI() );
    StopDisableNetworkAttack::subscribe_interaction( getRTI() );
    StartIntegrityAttack::subscribe_interaction( getRTI() );
    StopIntegrityAttack::subscribe_interaction( getRTI() );
    StartModifyFromHLAPacketsAttack::subscribe_interaction( getRTI() );
    StopModifyFromHLAPacketsAttack::subscribe_interaction( getRTI() );
    StartModifyToHLAPacketsAttack::subscribe_interaction( getRTI() );
    StopModifyToHLAPacketsAttack::subscribe_interaction( getRTI() );
    StartNetworkFilterAttack::subscribe_interaction( getRTI() );
    StopNetworkFilterAttack::subscribe_interaction( getRTI() );
    StartNetworkIPFirewall::subscribe_interaction( getRTI() );
    StopNetworkIPFirewall::subscribe_interaction( getRTI() );
    StartNodeAttack::subscribe_interaction( getRTI() );
    StopNodeAttack::subscribe_interaction( getRTI() );
    StartOutOfOrderPacketsAttack::subscribe_interaction( getRTI() );
    StopOutOfOrderPacketsAttack::subscribe_interaction( getRTI() );
    StartRecordingPacketsForReplayAttack::subscribe_interaction( getRTI() );
    StopRecordingPacketsForReplayAttack::subscribe_interaction( getRTI() );
    EraseRecordedPacketsForReplayAttack::subscribe_interaction( getRTI() );
    StartReplayAttack::subscribe_interaction( getRTI() );
    StopReplayAttack::subscribe_interaction( getRTI() );
    StartSnifferAttack::subscribe_interaction( getRTI() );
    StopSnifferAttack::subscribe_interaction( getRTI() );
    TakeOwnership::subscribe_interaction( getRTI() );
    LoseOwnership::subscribe_interaction( getRTI() );
    NetworkStatusRequest::subscribe_interaction( getRTI() );

    InteractionRoot::subscribe_interaction(EmbeddedMessaging::get_hla_class_name() + "." + getFederateType(), getRTI());

    for(const std::string &dynamicPublishHlaClassName: _dynamicPublishFullHlaClassNameSet) {
        if (
          dynamicPublishHlaClassName == "InteractionRoot" ||
          dynamicPublishHlaClassName.find("InteractionRoot.") == 0
        ) {
            InteractionRoot::publish_interaction(dynamicPublishHlaClassName, getRTI() );
        } else if (
          dynamicPublishHlaClassName == "ObjectRoot" ||
          dynamicPublishHlaClassName.find("ObjectRoot.") == 0
        ) {
            for(
              const ClassAndPropertyName &classAndPropertyName:
                ObjectRoot::get_attribute_names(dynamicPublishHlaClassName)
            ) {
                ObjectRoot::publish_attribute(
                  dynamicPublishHlaClassName,
                  classAndPropertyName.getClassName(),
                  classAndPropertyName.getPropertyName()
                );
            }
            ObjectRoot::publish_object(dynamicPublishHlaClassName, getRTI() );
        }
    }

    for(const std::string &dynamicSubscribeHlaClassName: _dynamicSubscribeFullHlaClassNameSet) {
        InteractionRoot::subscribe_interaction(dynamicSubscribeHlaClassName, getRTI() );
    }

    for(const std::string &dynamicSoftSubscribeHlaClassName: _dynamicSoftSubscribeFullHlaClassNameSet) {
        if (
          dynamicSoftSubscribeHlaClassName == "InteractionRoot" ||
          dynamicSoftSubscribeHlaClassName.find("InteractionRoot.") == 0
        ) {
            InteractionRoot::soft_subscribe_interaction(dynamicSoftSubscribeHlaClassName, getRTI() );
        } else if (
          dynamicSoftSubscribeHlaClassName == "ObjectRoot" ||
          dynamicSoftSubscribeHlaClassName.find("ObjectRoot.") == 0
        ) {
            for(
              const ClassAndPropertyName &classAndPropertyName:
                ObjectRoot::get_attribute_names(dynamicSoftSubscribeHlaClassName)
            ) {
                ObjectRoot::soft_subscribe_attribute(
                  dynamicSoftSubscribeHlaClassName,
                  classAndPropertyName.getClassName(),
                  classAndPropertyName.getPropertyName()
                );
            }
            ObjectRoot::soft_subscribe_object(dynamicSoftSubscribeHlaClassName, getRTI() );
        }
    }

    SubscribedInteractionFilter::get_singleton().initialize();
    //publish objects

    //subscribe objects

//    if ( !dbname.empty() ) {
//        CommandExecutionStatus::enablePublishLog("CommandExecutionStatus", "OmnetFederate", "NORMAL", _logLevel);
//
//        StartNodeAttack::enableSubscribeLog("StartNodeAttack", "OmnetFederate", "NORMAL", _logLevel);
//        StartLinkAttack::enableSubscribeLog("StartLinkAttack", "OmnetFederate", "NORMAL", _logLevel);
//        StartDisableNetworkAttack::enableSubscribeLog("StartDisableNetworkAttack", "OmnetFederate", "NORMAL", _logLevel);
//        StopDisableNetworkAttack::enableSubscribeLog("StopDisableNetworkAttack", "OmnetFederate", "NORMAL", _logLevel);
//        StopNodeAttack::enableSubscribeLog("StopNodeAttack", "OmnetFederate", "NORMAL", _logLevel);
//        StopLinkAttack::enableSubscribeLog("StopLinkAttack", "OmnetFederate", "NORMAL", _logLevel);
//        StartDataInjectionAttack::enableSubscribeLog("StartDataInjectionAttack", "OmnetFederate", "NORMAL", _logLevel);
//        StopDataInjectionAttack::enableSubscribeLog("StopDataInjectionAttack", "OmnetFederate", "NORMAL", _logLevel);
//        StartSnifferAttack::enableSubscribeLog("StartSnifferAttack", "OmnetFederate", "NORMAL", _logLevel);
//        StopSnifferAttack::enableSubscribeLog("StopSnifferAttack", "OmnetFederate", "NORMAL", _logLevel);
//        StartMasqueradingAttack::enableSubscribeLog("StartMasqueradingAttack", "OmnetFederate", "NORMAL", _logLevel);
//        StopMasqueradingAttack::enableSubscribeLog("StopMasqueradingAttack", "OmnetFederate", "NORMAL", _logLevel);
//        CeaseReplayAttack::enableSubscribeLog("CeaseReplayAttack", "OmnetFederate", "NORMAL", _logLevel);
//        RecordPacketsForReplayAttack::enableSubscribeLog("RecordPacketsForReplayAttack", "OmnetFederate", "NORMAL", _logLevel);
//        StopDNSPoisoningAttack::enableSubscribeLog("StopDNSPoisoningAttack", "OmnetFederate", "NORMAL", _logLevel);
//        StartDNSPoisoningAttack::enableSubscribeLog("StartDNSPoisoningAttack", "OmnetFederate", "NORMAL", _logLevel);
//        OmnetCommand::enableSubscribeLog("OmnetCommand", "OmnetFederate", "NORMAL", _logLevel);
//        StartReplayAttack::enableSubscribeLog("StartReplayAttack", "OmnetFederate", "NORMAL", _logLevel);
//        TerminateReplayAttack::enableSubscribeLog("TerminateReplayAttack", "OmnetFederate", "NORMAL", _logLevel);
//        StopOutOfOrderPacketsAttack::enableSubscribeLog("StopOutOfOrderPacketsAttack", "OmnetFederate", "NORMAL", _logLevel);
//        StartOutOfOrderPacketsAttack::enableSubscribeLog("StartOutOfOrderPacketsAttack", "OmnetFederate", "NORMAL", _logLevel);
//        DropRouteFromRoutingTable::enableSubscribeLog("DropRouteFromRoutingTable", "OmnetFederate", "NORMAL", _logLevel);
//        AddRouteToRoutingTable::enableSubscribeLog("AddRouteToRoutingTable", "OmnetFederate", "NORMAL", _logLevel);
//        StartNetworkFilterAttack::enableSubscribeLog("StartNetworkFilterAttack", "OmnetFederate", "NORMAL", _logLevel);
//        StopNetworkFilterAttack::enableSubscribeLog("StopNetworkFilterAttack", "OmnetFederate", "NORMAL", _logLevel);
//        StopDelayNodeAttack::enableSubscribeLog("StopDelayNodeAttack", "OmnetFederate", "NORMAL", _logLevel);
//        StartDelayNodeAttack::enableSubscribeLog("StartDelayNodeAttack", "OmnetFederate", "NORMAL", _logLevel);
//        StartIntegrityAttack::enableSubscribeLog("StartIntegrityAttack", "OmnetFederate", "NORMAL", _logLevel);
//        StopIntegrityAttack::enableSubscribeLog("StopIntegrityAttack", "OmnetFederate", "NORMAL", _logLevel);
//
//        StartNetworkIPFirewall::enableSubscribeLog("StartNetworkIPFirewall", "OmnetFederate", "NORMAL", _logLevel);
//        StopNetworkIPFirewall::enableSubscribeLog("StopNetworkIPFirewall", "OmnetFederate", "NORMAL", _logLevel);
//    }

    // set up dataflows
    BOOST_LOG_SEV(get_logger(), severity_level::info) << "Execution at \"ready to populate\" synchronization point";
    readyToPopulate();
    BOOST_LOG_SEV(get_logger(), severity_level::info) << "Execution at \"ready to run\" synchronization point";
    readyToRun();
    BOOST_LOG_SEV(get_logger(), severity_level::info) << "All synchronization points achieved";

    // Keep a message in the queue so the simulation doesn't end too soon
    _keepAliveMsg = new omnetpp::cMessage( "keepAlive" );
    scheduleAt( omnetpp::simTime(), _keepAliveMsg );

//    _readyToRunMsg = new omnetpp::cMessage ( "readyToRun" );
//    scheduleAt( omnetpp::simTime(), _readyToRunMsg );
}

void HLAInterface::handleMessage( omnetpp::cMessage* msg ) {

    // Check ready to run message
//    if( msg == _readyToRunMsg ) {
//        readyToRun();
//        return;
//    }

    // PROCESS ANY INCOMING INTERACTIONS
    if ( msg == _hlaArrivalMsg ) {
        processInteractions();
        processObjectReflectors();
        _noHlaArrivalFlag = true;
        return;
    }

    // Keep a message in the queue so the simulation doesn't end too soon
    if ( msg == _keepAliveMsg ) {
        sendKeepAliveMsg();
        return;
    }

    double minTime = getMinTSOTimestamp();
    double timestamp = msg->getTimestamp().dbl();
    if ( timestamp < minTime ) {
        timestamp = minTime;
    }

    std::string msgName = msg->getName();

    if ( msgName == getHlaMessageLabel().c_str() ) {
        inet::Packet* packet = dynamic_cast< inet::Packet * > ( msg );
        if ( packet == nullptr ) {
            BOOST_LOG_SEV(get_logger(), warning) << "HLAInterace received message of name \"" << getHlaMessageLabel()
              << "\" but received message is not an inet::Packet:  ignoring.";
            cancelAndDelete( msg );
            return;
        }

        auto c_packetChunkPtr = packet->peekAtFront<inet::cPacketChunk>();
        inet::cPacket *c_packetPtr = c_packetChunkPtr->getPacket();

        HlaMsg *hlaMsg = dynamic_cast< HlaMsg * >( c_packetPtr );

        InteractionRoot::SP interactionRootSP = hlaMsg->getInteractionRootSP();
        ObjectReflector::SP objectReflectorSP = hlaMsg->getObjectReflectorSP();
        if (interactionRootSP) {
            std::string receivingFederateName(hlaMsg->getReceiverFederateName());
            BOOST_LOG_SEV(get_logger(), severity_level::info) << "HLAInterface sending interaction to HLA: "
              << interactionRootSP;
            sendInteraction(*interactionRootSP, receivingFederateName, getCurrentTime() + getLookahead());
        } else if (objectReflectorSP) {
            std::string receivingFederateName(hlaMsg->getReceiverFederateName());
            sendInteraction(*objectReflectorSP, receivingFederateName, getCurrentTime() + getLookahead());
            BOOST_LOG_SEV(get_logger(), severity_level::info) << "HLAInterface sending object reflector to HLA: "
              << objectReflectorSP;
        } else {
            BOOST_LOG_SEV(get_logger(), warning) << "HLAInterface unable to send messaing to HLA:  Bad Pointer";
        }
    } else {
        BOOST_LOG_SEV(get_logger(), warning) << "HLAInterface:  Unexpected message received (name,kind):  ("
          << msgName << "," << msg->getKind() << ")";
    }

    cancelAndDelete( msg );
}

void HLAInterface::sendKeepAliveMsg() {
    scheduleAt(omnetpp::simTime() + getStepSize(), _keepAliveMsg);
}


