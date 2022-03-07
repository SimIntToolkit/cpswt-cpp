/*
 * HLAInterface.cc
 *
 */

#include <HLAInterface.h>
#include "C2WConsoleLogger.hpp"
#include <boost/lexical_cast.hpp>

#include "OmnetFOMInteractions.h"
#include "RTIRootHeaders.hpp"
#include "OmnetFOMMessageDefs.h"

#include "SubscribedInteractionFilter.hpp"

#include <inet/common/packet/Packet.h>

#include <messages/InteractionMsg_m.h>

#include "CPSWTIpv4.h"


Define_Module(HLAInterface);


using AddRouteToRoutingTable = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::AddRouteToRoutingTable;
using DropRouteFromRoutingTable = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::DropRouteFromRoutingTable;

using CommandExecutionStatus = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::CommandExecutionStatus;

using C2WInteractionRoot = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot;

using NetworkPacket = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::NetworkPacket;

using OmnetCommand = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand;

using RecordPacketsForReplayAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::RecordPacketsForReplayAttack;
using CeaseReplayAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::CeaseReplayAttack;

using StartDataInjectionAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::AttacksNotYetImplemented_p::StartDataInjectionAttack;
using StopDataInjectionAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::AttacksNotYetImplemented_p::StopDataInjectionAttack;

using StartDelayNodeAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StartDelayNodeAttack;
using StopDelayNodeAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StopDelayNodeAttack;

using StartDisableNetworkAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StartDisableNetworkAttack;
using StopDisableNetworkAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StopDisableNetworkAttack;

using StartDNSPoisoningAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::AttacksNotYetImplemented_p::StartDNSPoisoningAttack;
using StopDNSPoisoningAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::AttacksNotYetImplemented_p::StopDNSPoisoningAttack;

using StartIntegrityAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StartIntegrityAttack;
using StopIntegrityAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StopIntegrityAttack;

using StartLinkAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::AttacksNotYetImplemented_p::StartLinkAttack;
using StopLinkAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::AttacksNotYetImplemented_p::StopLinkAttack;

using StartMasqueradingAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::AttacksNotYetImplemented_p::StartMasqueradingAttack;
using StopMasqueradingAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::AttacksNotYetImplemented_p::StopMasqueradingAttack;

using StartModifyFromHLAPacketsAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StartModifyFromHLAPacketsAttack;
using StopModifyFromHLAPacketsAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StopModifyFromHLAPacketsAttack;

using StartModifyToHLAPacketsAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StartModifyToHLAPacketsAttack;
using StopModifyToHLAPacketsAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StopModifyToHLAPacketsAttack;

using StartNetworkFilterAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StartNetworkFilterAttack;
using StopNetworkFilterAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StopNetworkFilterAttack;

using StartNetworkIPFirewall = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StartNetworkIPFirewall;
using StopNetworkIPFirewall = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StopNetworkIPFirewall;

using StartNodeAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StartNodeAttack;
using StopNodeAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StopNodeAttack;

using StartOutOfOrderPacketsAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StartOutOfOrderPacketsAttack;
using StopOutOfOrderPacketsAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StopOutOfOrderPacketsAttack;

using StartReplayAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StartReplayAttack;
using TerminateReplayAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::TerminateReplayAttack;

using StartSnifferAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StartSnifferAttack;
using StopSnifferAttack = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StopSnifferAttack;


void HLAInterface::processInteractions( void ) {

    InteractionRoot::SP interactionRootSP;
    while(  ( interactionRootSP = getNextInteraction() ) != 0  ) {

        // std::cerr << "Processing interaction of type \"" << interactionRootSP->getClassName() << "\"" << std::endl;

        int classHandle = interactionRootSP->getClassHandle();

        if ( interactionRootSP->isDynamicInstance() ) {
            InteractionMsg *interactionMsgPtr = new InteractionMsg( getInteractionMessageLabel().c_str() );
            interactionMsgPtr->setToHLA( true );
            interactionMsgPtr->setMessageNo( AttackCoordinator::getUniqueNo() );
            interactionMsgPtr->setInteractionRootSP( interactionRootSP );
            interactionMsgPtr->setTimestamp( networkPacketSP->getTime() );
            interactionMsgPtr->setByteLength(networkPacketSP->get_numBytes());

             std::string hostName = networkPacketSP->get_senderHost();
             std::string appName = networkPacketSP->get_senderHostApp();
             int appIndex = networkPacketSP->get_senderAppIndex();

            auto c_packetChunk = inet::makeShared<inet::cPacketChunk>(interactionMsgPtr);
            inet::Packet *packet = new inet::Packet(getInteractionMessageLabel().c_str(), c_packetChunk);

             cModule *udpAppWrapperModule = AttackCoordinator::getSingleton().getAppSpecModule( hostName, appName, appIndex );
             if ( udpAppWrapperModule != 0 ) {
                sendDirect( packet, udpAppWrapperModule, "hlaIn" );
             } else {
                 std::cerr << "WARNING:  HLAInterface:  could not find module corresponding to (hostname,appName) = (" <<
                  hostName << "," << appName << ")" << std::endl;
                 std::cerr << "Current modules are: " << std::endl;
                 std::cerr << AttackCoordinator::getSingleton().listAppSpecProperties();
                 std::cerr << std::endl;
             }
             continue;
        }


        if (  StartNodeAttack::match( classHandle )  ) {
            StartNodeAttack::SP startNodeAttackSP = boost::static_pointer_cast< StartNodeAttack >( interactionRootSP );

            std::string recordingNodeFullPath = startNodeAttackSP->get_recordingNodeFullPath();

            NodeAttackMsg *nodeAttackMsg = new NodeAttackMsg;
            nodeAttackMsg->setAttackInProgress( true );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( recordingNodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  nodeAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                std::cout << "WARNING:  StartNodeAttack:  NO MODULE FOR NODE \"" << recordingNodeFullPath << "\"" << std::endl;
            }
            continue;
        }


        if (  StopNodeAttack::match( classHandle )  ) {
            StopNodeAttack::SP stopNodeAttackSP = boost::static_pointer_cast< StopNodeAttack >( interactionRootSP );

            std::string recordingNodeFullPath = stopNodeAttackSP->get_recordingNodeFullPath();

            NodeAttackMsg *nodeAttackMsg = new NodeAttackMsg;
            nodeAttackMsg->setAttackInProgress( false );



            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( recordingNodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  nodeAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                std::cout << "WARNING:  StopNodeAttack:  NO MODULE FOR NODE \"" << recordingNodeFullPath << "\"" << std::endl;
            }
            continue;
        }


        if (  StartDelayNodeAttack::match( classHandle )  ) {
            StartDelayNodeAttack::SP startDelayNodeAttackSP = boost::static_pointer_cast< StartDelayNodeAttack >( interactionRootSP );

            std::string nodeFullPath = startDelayNodeAttackSP->get_nodeFullPath();

            DelayNodeAttackMsg *delayNodeAttackMsg = new DelayNodeAttackMsg;
            delayNodeAttackMsg->setAttackInProgress( true );
            delayNodeAttackMsg->setDelayMean( startDelayNodeAttackSP->get_delayMean() );
            delayNodeAttackMsg->setDelayStdDev( startDelayNodeAttackSP->get_delayStdDev() );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  delayNodeAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                std::cout << "WARNING:  StartDelayNodeAttack:  NO MODULE FOR NODE \"" << nodeFullPath << "\"" << std::endl;
            }
            continue;
        }


        if (  StopDelayNodeAttack::match( classHandle )  ) {
            StopDelayNodeAttack::SP stopDelayNodeAttackSP = boost::static_pointer_cast< StopDelayNodeAttack >( interactionRootSP );

            std::string nodeFullPath = stopDelayNodeAttackSP->get_nodeFullPath();

            DelayNodeAttackMsg *delayNodeAttackMsg = new DelayNodeAttackMsg;
            delayNodeAttackMsg->setAttackInProgress( false );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  delayNodeAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                std::cout << "WARNING:  StopDelayNodeAttack:  NO MODULE FOR NODE \"" << nodeFullPath << "\"" << std::endl;
            }
            continue;
        }


        if (  StartSnifferAttack::match( classHandle )  ) {
            StartSnifferAttack::SP startSnifferAttackSP = boost::static_pointer_cast< StartSnifferAttack >( interactionRootSP );

            std::string nodeFullPath = startSnifferAttackSP->get_nodeFullPath();

            SnifferAttackMsg *snifferAttackMsg = new SnifferAttackMsg;
            snifferAttackMsg->setListenerNodeFullPath( startSnifferAttackSP->get_listenerNodeFullPath().c_str() );
            snifferAttackMsg->setListenerInterface( startSnifferAttackSP->get_listenerInterface().c_str() );
            snifferAttackMsg->setListen( true );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  snifferAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                std::cout << "WARNING:  StartSnifferAttack:  NO MODULE FOR NODE \"" << nodeFullPath << "\"" << std::endl;
                std::cout << "Current modules are:" << std::endl;
                std::cout << AttackCoordinator::getSingleton().listIPModuleProperties() << std::endl;
            }
            continue;
        }

        if (  StopSnifferAttack::match( classHandle )  ) {
            StopSnifferAttack::SP stopSnifferAttackSP = boost::static_pointer_cast< StopSnifferAttack >( interactionRootSP );

            std::string nodeFullPath = stopSnifferAttackSP->get_nodeFullPath();

            SnifferAttackMsg *snifferAttackMsg = new SnifferAttackMsg;
            snifferAttackMsg->setListenerNodeFullPath( stopSnifferAttackSP->get_listenerNodeFullPath().c_str() );
            snifferAttackMsg->setListenerInterface( stopSnifferAttackSP->get_listenerInterface().c_str() );
            snifferAttackMsg->setListen( false );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  snifferAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                std::cout << "WARNING:  StopSnifferAttack:  NO MODULE FOR NODE \"" << nodeFullPath << "\"" << std::endl;
                std::cout << "Current modules are:" << std::endl;
                std::cout << AttackCoordinator::getSingleton().listIPModuleProperties() << std::endl;
            }
            continue;
        }

        if (  StartNetworkFilterAttack::match( classHandle )  ) {
            StartNetworkFilterAttack::SP startNetworkFilterAttackSP = boost::static_pointer_cast< StartNetworkFilterAttack >( interactionRootSP );

            std::string recordingNodeFullPath = startNetworkFilterAttackSP->get_recordingNodeFullPath();

            FilterAttackMsg *filterAttackMsg = new FilterAttackMsg;
            filterAttackMsg->setSourceNetworkAddress( startNetworkFilterAttackSP->get_srcNetworkAddress().c_str() );
            filterAttackMsg->setDestinationNetworkAddress( startNetworkFilterAttackSP->get_dstNetworkAddress().c_str() );
            filterAttackMsg->setEnable( true );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( recordingNodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  filterAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                std::cout << "WARNING:  StartNetworkFilterAttack:  NO MODULE FOR NODE \"" << recordingNodeFullPath << "\"" << std::endl;
            }
            continue;
        }

        if (  StopNetworkFilterAttack::match( classHandle )  ) {
            StopNetworkFilterAttack::SP stopNetworkFilterAttackSP = boost::static_pointer_cast< StopNetworkFilterAttack >( interactionRootSP );

            std::string recordingNodeFullPath = stopNetworkFilterAttackSP->get_recordingNodeFullPath();

            FilterAttackMsg *filterAttackMsg = new FilterAttackMsg;
            filterAttackMsg->setSourceNetworkAddress( stopNetworkFilterAttackSP->get_srcNetworkAddress().c_str() );
            filterAttackMsg->setDestinationNetworkAddress( stopNetworkFilterAttackSP->get_dstNetworkAddress().c_str() );
            filterAttackMsg->setEnable( false );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( recordingNodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  filterAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                std::cout << "WARNING:  StopNetworkFilterAttack:  NO MODULE FOR NODE \"" << recordingNodeFullPath << "\"" << std::endl;
            }
            continue;
        }

        if (  StartNetworkIPFirewall::match( classHandle )  ) {
            StartNetworkIPFirewall::SP startNetworkIPFirewallSP = boost::static_pointer_cast< StartNetworkIPFirewall >( interactionRootSP );

            std::string nodeFullPath = startNetworkIPFirewallSP->get_nodeFullPath();

            IPFirewallMsg *ipFirewallMsg = new IPFirewallMsg;
            ipFirewallMsg->setSourceNetworkAddress( startNetworkIPFirewallSP->get_srcNetworkAddress().c_str() );
            ipFirewallMsg->setDestinationNetworkAddress( startNetworkIPFirewallSP->get_dstNetworkAddress().c_str() );
            ipFirewallMsg->setEnable( true );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  ipFirewallMsg, cModulePtr, "hlaIn"  );
            } else {
                std::cout << "WARNING:  StartNetworkIPFirewall:  NO MODULE FOR NODE \"" << nodeFullPath << "\"" << std::endl;
            }
            continue;
        }

        if (  StopNetworkIPFirewall::match( classHandle )  ) {
            StopNetworkIPFirewall::SP stopNetworkIPFirewallSP = boost::static_pointer_cast< StopNetworkIPFirewall >( interactionRootSP );

            std::string nodeFullPath = stopNetworkIPFirewallSP->get_nodeFullPath();

            IPFirewallMsg *ipFirewallMsg = new IPFirewallMsg;
            ipFirewallMsg->setSourceNetworkAddress( stopNetworkIPFirewallSP->get_srcNetworkAddress().c_str() );
            ipFirewallMsg->setDestinationNetworkAddress( stopNetworkIPFirewallSP->get_dstNetworkAddress().c_str() );
            ipFirewallMsg->setEnable( false );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  ipFirewallMsg, cModulePtr, "hlaIn"  );
            } else {
                std::cout << "WARNING:  StopNetworkIPFirewall:  NO MODULE FOR NODE \"" << nodeFullPath << "\"" << std::endl;
            }
            continue;
        }

        if (  StartDisableNetworkAttack::match( classHandle )  ) {

            StartDisableNetworkAttack::SP startDisableNetworkAttackSP = boost::static_pointer_cast< StartDisableNetworkAttack >( interactionRootSP );

            std::string networkAddressStr = startDisableNetworkAttackSP->get_networkAddress();

            AttackCoordinator::NetworkAddress networkAddress( networkAddressStr );
            AttackCoordinator::CModuleSet cModuleSet = AttackCoordinator::getSingleton().getCModuleSet(networkAddress);

            for( AttackCoordinator::CModuleSet::iterator cmsItr = cModuleSet.begin() ; cmsItr != cModuleSet.end() ; ++cmsItr ) {
                NetworkAttackMsg *networkAttackMsg = new NetworkAttackMsg;
                networkAttackMsg->setNetworkAddress( networkAddressStr.c_str() );
                networkAttackMsg->setEnable( true );

                sendDirect(  networkAttackMsg, *cmsItr, "hlaIn"  );
            }

            continue;
        }

        if (  StopDisableNetworkAttack::match( classHandle )  ) {
            StopDisableNetworkAttack::SP stopDisableNetworkAttackSP = boost::static_pointer_cast< StopDisableNetworkAttack >( interactionRootSP );

            std::string networkAddressStr = stopDisableNetworkAttackSP->get_networkAddress();

            AttackCoordinator::NetworkAddress networkAddress( networkAddressStr );
            AttackCoordinator::CModuleSet cModuleSet = AttackCoordinator::getSingleton().getCModuleSet(networkAddress);

            for( AttackCoordinator::CModuleSet::iterator cmsItr = cModuleSet.begin() ; cmsItr != cModuleSet.end() ; ++cmsItr ) {
                NetworkAttackMsg *networkAttackMsg = new NetworkAttackMsg;
                networkAttackMsg->setNetworkAddress( networkAddressStr.c_str() );
                networkAttackMsg->setEnable( false );

                sendDirect(  networkAttackMsg, *cmsItr, "hlaIn"  );
            }

            continue;
        }

        if (  RecordPacketsForReplayAttack::match( classHandle )  ) {
            RecordPacketsForReplayAttack::SP recordPacketsForReplayAttackSP = boost::static_pointer_cast< RecordPacketsForReplayAttack >( interactionRootSP );

            std::string nodeFullPath = recordPacketsForReplayAttackSP->get_recordingNodeFullPath();

            RecordReplayAttackMsg *recordReplayAttackMsg = new RecordReplayAttackMsg;
            recordReplayAttackMsg->setSourceNetworkAddress( recordPacketsForReplayAttackSP->get_srcNetworkAddress().c_str() );
            recordReplayAttackMsg->setDestinationNetworkAddress( recordPacketsForReplayAttackSP->get_dstNetworkAddress().c_str() );
            recordReplayAttackMsg->setRecordDuration( recordPacketsForReplayAttackSP->get_recordDurationInSecs() );
            recordReplayAttackMsg->setEnable( true );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  recordReplayAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                std::cout << "WARNING:  RecordPacketsForReplayAttack:  NO MODULE FOR NODE \"" << nodeFullPath << "\"" << std::endl;
            }
            continue;
        }

        if (  TerminateReplayAttack::match( classHandle )  ) {
            TerminateReplayAttack::SP terminateReplayAttackSP = boost::static_pointer_cast< TerminateReplayAttack >( interactionRootSP );

            std::string nodeFullPath = terminateReplayAttackSP->get_recordingNodeFullPath();

            RecordReplayAttackMsg *recordReplayAttackMsg = new RecordReplayAttackMsg;
            recordReplayAttackMsg->setSourceNetworkAddress( terminateReplayAttackSP->get_srcNetworkAddress().c_str() );
            recordReplayAttackMsg->setDestinationNetworkAddress( terminateReplayAttackSP->get_dstNetworkAddress().c_str() );
            recordReplayAttackMsg->setRecordDuration( -1 );
            recordReplayAttackMsg->setEnable( false );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  recordReplayAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                std::cout << "WARNING:  TerminateReplayAttack:  NO MODULE FOR NODE \"" << nodeFullPath << "\"" << std::endl;
            }
            continue;
        }

        if (  StartReplayAttack::match( classHandle )  ) {
            StartReplayAttack::SP startReplayAttackSP = boost::static_pointer_cast< StartReplayAttack >( interactionRootSP );

            std::string nodeFullPath = startReplayAttackSP->get_recordingNodeFullPath();

            ReplayAttackMsg *replayAttackMsg = new ReplayAttackMsg;
            replayAttackMsg->setSourceNetworkAddress( startReplayAttackSP->get_srcNetworkAddress().c_str() );
            replayAttackMsg->setDestinationNetworkAddress( startReplayAttackSP->get_dstNetworkAddress().c_str() );
            replayAttackMsg->setPlay( true );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  replayAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                std::cout << "WARNING:  StartReplayAttack:  NO MODULE FOR NODE \"" << nodeFullPath << "\"" << std::endl;
            }
            continue;
        }

        if (  CeaseReplayAttack::match( classHandle )  ) {
            CeaseReplayAttack::SP ceaseReplayAttackSP = boost::static_pointer_cast< CeaseReplayAttack >( interactionRootSP );

            std::string nodeFullPath = ceaseReplayAttackSP->get_recordingNodeFullPath();

            ReplayAttackMsg *replayAttackMsg = new ReplayAttackMsg;
            replayAttackMsg->setSourceNetworkAddress( ceaseReplayAttackSP->get_srcNetworkAddress().c_str() );
            replayAttackMsg->setDestinationNetworkAddress( ceaseReplayAttackSP->get_dstNetworkAddress().c_str() );
            replayAttackMsg->setPlay( false );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  replayAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                std::cout << "WARNING:  CeaseReplayAttack:  NO MODULE FOR NODE \"" << nodeFullPath << "\"" << std::endl;
            }
            continue;
        }

        if (  StartOutOfOrderPacketsAttack::match( classHandle )  ) {
            StartOutOfOrderPacketsAttack::SP startOutOfOrderPacketsAttackSP = boost::static_pointer_cast< StartOutOfOrderPacketsAttack >( interactionRootSP );

            std::string nodeFullPath = startOutOfOrderPacketsAttackSP->get_recordingNodeFullPath();

            OutOfOrderAttackMsg *outOfOrderAttackMsg = new OutOfOrderAttackMsg;
            outOfOrderAttackMsg->setSourceNetworkAddress( startOutOfOrderPacketsAttackSP->get_srcNetworkAddress().c_str() );
            outOfOrderAttackMsg->setDestinationNetworkAddress( startOutOfOrderPacketsAttackSP->get_dstNetworkAddress().c_str() );
            outOfOrderAttackMsg->setRecordDuration( startOutOfOrderPacketsAttackSP->get_recordDurationInSecs() );
            outOfOrderAttackMsg->setPlay( true );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  outOfOrderAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                std::cout << "WARNING:  StartOutOfOrderPacketsAttack:  NO MODULE FOR NODE \"" << nodeFullPath << "\"" << std::endl;
            }
            continue;
        }

        if (  StopOutOfOrderPacketsAttack::match( classHandle )  ) {
            StopOutOfOrderPacketsAttack::SP stopOutOfOrderPacketsAttackSP = boost::static_pointer_cast< StopOutOfOrderPacketsAttack >( interactionRootSP );

            std::string nodeFullPath = stopOutOfOrderPacketsAttackSP->get_recordingNodeFullPath();

            OutOfOrderAttackMsg *outOfOrderAttackMsg = new OutOfOrderAttackMsg;
            outOfOrderAttackMsg->setSourceNetworkAddress( stopOutOfOrderPacketsAttackSP->get_srcNetworkAddress().c_str() );
            outOfOrderAttackMsg->setDestinationNetworkAddress( stopOutOfOrderPacketsAttackSP->get_dstNetworkAddress().c_str() );
            outOfOrderAttackMsg->setRecordDuration( -1 );
            outOfOrderAttackMsg->setPlay( false );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect(  outOfOrderAttackMsg, cModulePtr, "hlaIn"  );
            } else {
                std::cout << "WARNING:  StopOutOfOrderPacketsAttack:  NO MODULE FOR NODE \"" << nodeFullPath << "\"" << std::endl;
            }
            continue;
        }

        if ( AddRouteToRoutingTable::match( classHandle ) ) {
            AddRouteToRoutingTable::SP addRouteToRoutingTableSP =
             boost::static_pointer_cast< AddRouteToRoutingTable >( interactionRootSP );

            std::string nodeFullPath = addRouteToRoutingTableSP->get_nodeFullPath();
            std::string interfaceEntry = addRouteToRoutingTableSP->get_interfaceEntry();
            AttackCoordinator::NetworkAddress networkAddress( addRouteToRoutingTableSP->get_networkAddress() );
            AttackCoordinator::NetworkAddress gatewayAddress( addRouteToRoutingTableSP->get_gatewayAddress() );

            AttackCoordinator::RouteEntrySP routeEntrySP = AttackCoordinator::getSingleton().createRouteEntrySP( nodeFullPath, interfaceEntry, networkAddress, gatewayAddress );

            AddRouteEntryMsg *addRouteEntryMsg = new AddRouteEntryMsg;
            addRouteEntryMsg->setRouteEntrySP( routeEntrySP );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect( addRouteEntryMsg, cModulePtr, "hlaIn" );
            } else {
                std::cout << "WARNING:  AddRouteToRoutingTable:  NO MODULE FOR NODE \"" << nodeFullPath << "\"" << std::endl;
            }
            continue;
        }

        if ( DropRouteFromRoutingTable::match( classHandle ) ) {
            DropRouteFromRoutingTable::SP dropRouteFromRoutingTableSP =
             boost::static_pointer_cast< DropRouteFromRoutingTable >( interactionRootSP );

            std::string nodeFullPath = dropRouteFromRoutingTableSP->get_nodeFullPath();
            std::string interfaceEntry = dropRouteFromRoutingTableSP->get_interfaceEntry();
            AttackCoordinator::NetworkAddress networkAddress( dropRouteFromRoutingTableSP->get_networkAddress() );
            AttackCoordinator::NetworkAddress gatewayAddress( dropRouteFromRoutingTableSP->get_gatewayAddress() );

            AttackCoordinator::RouteEntrySP routeEntrySP = AttackCoordinator::getSingleton().createRouteEntrySP( nodeFullPath, interfaceEntry, networkAddress, gatewayAddress );

            DropRouteEntryMsg *dropRouteEntryMsg = new DropRouteEntryMsg;
            dropRouteEntryMsg->setRouteEntrySP( routeEntrySP );

            cModule *cModulePtr = AttackCoordinator::getSingleton().getIPModule( nodeFullPath );
            if ( cModulePtr != 0 ) {
                sendDirect( dropRouteEntryMsg, cModulePtr, "hlaIn" );
            } else {
                std::cout << "WARNING:  DropRouteFromRoutingTable:  NO MODULE FOR NODE \"" << nodeFullPath << "\"" << std::endl;
            }
            continue;
        }

        if ( StartModifyToHLAPacketsAttack::match( classHandle ) ) {
            StartModifyToHLAPacketsAttack::SP startModifyToHLAPacketsAttackSP =
             boost::static_pointer_cast< StartModifyToHLAPacketsAttack >( interactionRootSP );

            std::string nodeFullPath = startModifyToHLAPacketsAttackSP->get_nodeFullPath();

            AttackCoordinator::getSingleton().setModifyToHLAPackets( nodeFullPath, true );
            continue;
        }

        if ( StopModifyToHLAPacketsAttack::match( classHandle ) ) {
            StopModifyToHLAPacketsAttack::SP stopModifyToHLAPacketsAttackSP =
             boost::static_pointer_cast< StopModifyToHLAPacketsAttack >( interactionRootSP );

            std::string nodeFullPath = stopModifyToHLAPacketsAttackSP->get_nodeFullPath();

            AttackCoordinator::getSingleton().setModifyToHLAPackets( nodeFullPath, false );
            continue;
        }

        if ( StartModifyFromHLAPacketsAttack::match( classHandle ) ) {
            StartModifyFromHLAPacketsAttack::SP startModifyFromHLAPacketsAttackSP =
             boost::static_pointer_cast< StartModifyFromHLAPacketsAttack >( interactionRootSP );

            std::string nodeFullPath = startModifyFromHLAPacketsAttackSP->get_nodeFullPath();

            AttackCoordinator::getSingleton().setModifyFromHLAPackets( nodeFullPath, true );
            continue;
        }

        if ( StopModifyFromHLAPacketsAttack::match( classHandle ) ) {
            StopModifyFromHLAPacketsAttack::SP stopModifyFromHLAPacketsAttackSP =
             boost::static_pointer_cast< StopModifyFromHLAPacketsAttack >( interactionRootSP );

            std::string nodeFullPath = stopModifyFromHLAPacketsAttackSP->get_nodeFullPath();

            AttackCoordinator::getSingleton().setModifyFromHLAPackets( nodeFullPath, false );
            continue;
        }

        if ( StartIntegrityAttack::match( classHandle ) ) {
            StartIntegrityAttack::SP startIntegrityAttackSP =
             boost::static_pointer_cast< StartIntegrityAttack >( interactionRootSP );

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

            std::string nodeFullPath = stopIntegrityAttackSP->get_nodeFullPath();
            AttackCoordinator::getSingleton().disableIntegrityAttack( nodeFullPath );
            continue;
        }

        //
        // PROCESSING FOR ATTACK-DIRECTIVE INTERACTIONS
        //

        std::cerr << "ERROR:  HLAInterface:  received unexpected interaction:" << std::endl;
        std::cerr << *interactionRootSP << std::endl << std::endl;

    }

}

void HLAInterface::interactionArrival( void ) {
    Enter_Method_Silent( "interactionArrival" );
    if ( _noInteractionArrivalFlag ) {
        scheduleAt( omnetpp::simTime(), _interactionArrivalMsg );
        _noInteractionArrivalFlag = false;
    }
}

void HLAInterface::receiveInteraction(
 RTI::InteractionClassHandle theInteraction,
 const RTI::ParameterHandleValuePairSet& theParameters,
 const RTI::FedTime& theTime,
 const char *theTag,
 RTI::EventRetractionHandle theHandle
)
 throw ( RTI::InteractionClassNotKnown, RTI::InteractionParameterNotKnown, RTI::InvalidFederationTime, RTI::FederateInternalError ) {

    static bool notPrinted = true;
    if ( notPrinted ) {
        std::cerr << AttackCoordinator::getSingleton().listAppSpecProperties() << std::endl;
        notPrinted = false;
    }

    InteractionRoot::SP interactionRootSP = InteractionRoot::create_interaction( theInteraction, theParameters, theTime );
    C2WInteractionRoot::SP c2wInteractionRootSP = boost::dynamic_pointer_cast< C2WInteractionRoot >( interactionRootSP );

    // Filter interaction if src/origin fed requirements (if any) are met
    if (  c2wInteractionRootSP != 0 && SubscribedInteractionFilter::get_singleton().filterC2WInteraction( getFederateId(), c2wInteractionRootSP )  ) {
        return;
    }

    //std::cerr << "Received interaction with timestamp " << boost::lexical_cast< std::string >(  static_cast< RTIfedTime >( theTime ).getTime()  ) << " at federate time " <<
    // boost::lexical_cast< std::string >( getCurrentTime() ) <<  std::endl;

    Super::receiveInteraction( theInteraction, theParameters, theTime, theTag, theHandle );

    interactionArrival();
}

void HLAInterface::receiveInteraction(
 RTI::InteractionClassHandle theInteraction,
 const RTI::ParameterHandleValuePairSet& theParameters,
 const char *theTag
)
 throw ( RTI::InteractionClassNotKnown, RTI::InteractionParameterNotKnown, RTI::FederateInternalError ) {

    InteractionRoot::SP interactionRootSP = InteractionRoot::create_interaction( theInteraction, theParameters );
    C2WInteractionRoot::SP c2wInteractionRootSP = boost::dynamic_pointer_cast< C2WInteractionRoot >( interactionRootSP );
    if (  c2wInteractionRootSP != 0 && SubscribedInteractionFilter::get_singleton().filterC2WInteraction( getFederateId(), c2wInteractionRootSP )  ) {
        return;
    }

    // std::cerr << "Received interaction at federate time " << boost::lexical_cast< std::string >( getCurrentTime() ) <<  std::endl;

    Super::receiveInteraction( theInteraction, theParameters, theTag );

    interactionArrival();
}

void HLAInterface::processObjectReflectors( void ) {

    Enter_Method( "processObjectReflectors" );

//    ObjectReflector objectReflector;
//    while(  !( objectReflector = getNextObjectReflector() ).isNull()  ) {
//
//        objectReflector.reflect();
//        ObjectRootSP objectRootSP = objectReflector.getObjectRootSP();
//
//         ObjectMsg *objectMsg = new ObjectMsg( "Object" );
//         objectMsg->setObjectRootSP( objectRootSP );
//         objectMsg->setTimestamp( objectRootSP->getTime() );
//         objectMsg->setKind( OBJECT );
//
//        sendDirect( objectMsg, HLAGateway::get_InstancePtr(), "hlaIn" );
//    }
}

HLAInterface::HLAInterface( void ) :
 cSimpleModule(), SynchronizedFederate(),
 _interactionArrivalMsg(  new omnetpp::cMessage( "interactionArrival" )  ),
 _noInteractionArrivalFlag( true )
{
    setInstancePtr( this );
}

HLAInterface::~HLAInterface( void ) throw() { }


void HLAInterface::initialize(int stage) {
    // UDPEndpointApp registers at stage 0
    // HLAInterface initializes at stage 1

    if ( stage == inet::INITSTAGE_LOCAL ) {

        setFederationId(par( "federation_name" ).stringValue());
        setFederateId(par( "federate_name" ).stringValue());
        setFederateType(getFederateId());
        setStepSize(par( "federate_step_size" ).doubleValue());
        setLookahead(par( "federate_lookahead" ).doubleValue());

        std::string federation_json_file_name = par( "federation_json_file_name" ).stringValue();
        std::string dynamic_messaging_classes_json_file_name = par( "dynamic_messaging_classes_json_file_name" ).stringValue();

        if (!federation_json_file_name.empty() && !dynamic_messaging_classes_json_file_name.empty()){
            initializeDynamicMessaging(federation_json_file_name, dynamic_messaging_classes_json_file_name);
        }

        setup();
    }

    if ( stage == inet::INITSTAGE_LAST ) {
        std::cerr << "AppSpecProperties:" << std::endl;
        std::cerr << AttackCoordinator::getSingleton().listAppSpecProperties() << std::endl;
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
    NetworkPacket::publish_interaction( getRTI() );
    CommandExecutionStatus::publish_interaction( getRTI() );

    // subscribe interactions
    StartNodeAttack::subscribe_interaction( getRTI() );
    StartLinkAttack::subscribe_interaction( getRTI() );
    NetworkPacket::subscribe_interaction( getRTI() );
    StartDisableNetworkAttack::subscribe_interaction( getRTI() );
    StopDisableNetworkAttack::subscribe_interaction( getRTI() );
    StopNodeAttack::subscribe_interaction( getRTI() );
    StopLinkAttack::subscribe_interaction( getRTI() );
    StartDataInjectionAttack::subscribe_interaction( getRTI() );
    StopDataInjectionAttack::subscribe_interaction( getRTI() );
    StartSnifferAttack::subscribe_interaction( getRTI() );
    StopSnifferAttack::subscribe_interaction( getRTI() );
    StartMasqueradingAttack::subscribe_interaction( getRTI() );
    StopMasqueradingAttack::subscribe_interaction( getRTI() );
    CeaseReplayAttack::subscribe_interaction( getRTI() );
    RecordPacketsForReplayAttack::subscribe_interaction( getRTI() );
    StopDNSPoisoningAttack::subscribe_interaction( getRTI() );
    StartDNSPoisoningAttack::subscribe_interaction( getRTI() );
    OmnetCommand::subscribe_interaction( getRTI() );
    StartReplayAttack::subscribe_interaction( getRTI() );
    TerminateReplayAttack::subscribe_interaction( getRTI() );
    StopOutOfOrderPacketsAttack::subscribe_interaction( getRTI() );
    StartOutOfOrderPacketsAttack::subscribe_interaction( getRTI() );
    DropRouteFromRoutingTable::subscribe_interaction( getRTI() );
    AddRouteToRoutingTable::subscribe_interaction( getRTI() );
    StartNetworkFilterAttack::subscribe_interaction( getRTI() );
    StopNetworkFilterAttack::subscribe_interaction( getRTI() );
    StopDelayNodeAttack::subscribe_interaction( getRTI() );
    StartDelayNodeAttack::subscribe_interaction( getRTI() );
    StartModifyFromHLAPacketsAttack::subscribe_interaction( getRTI() );
    StopModifyFromHLAPacketsAttack::subscribe_interaction( getRTI() );
    StartModifyToHLAPacketsAttack::subscribe_interaction( getRTI() );
    StopModifyToHLAPacketsAttack::subscribe_interaction( getRTI() );
    StartIntegrityAttack::subscribe_interaction( getRTI() );
    StopIntegrityAttack::subscribe_interaction( getRTI() );

    StartNetworkIPFirewall::subscribe_interaction( getRTI() );
    StopNetworkIPFirewall::subscribe_interaction( getRTI() );

    for(const std::string &dynamicHlaClassName: InteractionRoot::get_dynamic_class_name_set()) {
        InteractionRoot::publish_interaction(dynamicHlaClassName);
        InteractionRoot::subscribe_interaction(dynamicHlaClassName);
    }

    SubscribedInteractionFilter::get_singleton().initialize();

    //publish objects

    //subscribe objects

//    if ( !dbname.empty() ) {
//        NetworkPacket::enablePublishLog("NetworkPacket", "OmnetFederate", "NORMAL", _logLevel);
//        CommandExecutionStatus::enablePublishLog("CommandExecutionStatus", "OmnetFederate", "NORMAL", _logLevel);
//
//        StartNodeAttack::enableSubscribeLog("StartNodeAttack", "OmnetFederate", "NORMAL", _logLevel);
//        StartLinkAttack::enableSubscribeLog("StartLinkAttack", "OmnetFederate", "NORMAL", _logLevel);
//        NetworkPacket::enableSubscribeLog("NetworkPacket", "OmnetFederate", "NORMAL", _logLevel);
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
    std::cout << "sending \"ready to populate\"" << std::endl;
    readyToPopulate();
    std::cout << "sending \"ready to run\"" << std::endl;
    readyToRun();
    std::cout << "Past synchronization points." << std::endl;

    // Keep a message in the queue so the simulation doesn't end too soon
    _keepAliveMsg = new omnetpp::cMessage( "keepAlive" );
    scheduleAt( omnetpp::simTime(), _keepAliveMsg );

    _readyToRunMsg = new omnetpp::cMessage ( "readyToRun" );
    scheduleAt( omnetpp::simTime(), _readyToRunMsg );
}

void HLAInterface::handleMessage( omnetpp::cMessage* msg ) {

    // Check ready to run message
    if( msg == _readyToRunMsg ) {
        readyToRun();
        return;
    }

    // PROCESS ANY INCOMING INTERACTIONS
    if ( msg == _interactionArrivalMsg ) {
        processInteractions();
        _noInteractionArrivalFlag = true;
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

    if ( msgName == getInteractionMessageLabel().c_str() ) {
        inet::Packet* packet = dynamic_cast< inet::Packet * > ( msg );
        if ( packet == nullptr ) {
            std::cerr << "WARNING:  HLAInterace received message of name \"" << getInteractionMessageLabel() << "\" but received message is not an inet::Packet:  ignoring." << std::endl;
            cancelAndDelete( msg );
            return;
        }

        auto c_packetChunkPtr = packet->peekAtFront<inet::cPacketChunk>();
        inet::cPacket *c_packetPtr = c_packetChunkPtr->getPacket();

        InteractionMsg *interactionMsg = dynamic_cast< InteractionMsg * >( c_packetPtr );

        NetworkPacket::SP networkPacketSP = boost::static_pointer_cast< NetworkPacket >( interactionMsg->getInteractionRootSP() );
        networkPacketSP->set_sourceFed( getFederateId() );
        networkPacketSP->sendInteraction( getRTI(), timestamp );
        // std::cerr << "Sending interaction with timestamp " << boost::lexical_cast< std::string >( timestamp ) << std::endl;
//    } else if ( msgKind == OBJECT ) {
//        ObjectMsg *objectMsgPtr = static_cast< ObjectMsg * >( msg );
//        ObjectRootSP objectRootSP = objectMsgPtr->getObjectRootSP();
//        objectRootSP->registerObject( getRTI() ); // NOP IF ALREADY REGISTERED.
//        objectRootSP->updateAttributeValues( getRTI(), timestamp );
    } else {
        std::cerr << "ERROR:  HLAInterface:  Unexpected message received (name,kind):  (" <<
         msgName << "," << msg->getKind() << ")" << std::endl << std::endl;
    }

    cancelAndDelete( msg );
}

void HLAInterface::sendKeepAliveMsg() {
    scheduleAt(omnetpp::simTime() + getStepSize(), _keepAliveMsg);
}


