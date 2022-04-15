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

#include "BasicUdpAppWrapper.h"
#include <boost/lexical_cast.hpp>
#include <inet/common/packet/chunk/cPacketChunk.h>

#include <messages/InteractionMsg_m.h>

#include <typeinfo>

Define_Module(BasicUdpAppWrapper);


using NetworkPacket = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::NetworkPacket;


void BasicUdpAppWrapper::recordInterfaceIPAddresses( void ) {

	AttackCoordinator::InterfaceIPAddressMap &interfaceIPAddressMap =
	 AttackCoordinator::getSingleton().getAppInterfaceIPAddressMap( getHostName(), getAppName(), getIndex() );

	interfaceIPAddressMap.clear();

	int noEntries = getInterfaceTable()->getNumInterfaces();
	for( int ix = 0 ; ix < noEntries ; ++ix ) {

		inet::InterfaceEntry *interfaceEntry = getInterfaceTable()->getInterface( ix );
		inet::Ipv4Address ipAddress = interfaceEntry->getIpv4Address();
		if ( ipAddress.isUnspecified() ) {
			continue;
		}

		interfaceIPAddressMap.insert(  std::make_pair( static_cast<cModule *>(interfaceEntry)->getName(), ipAddress )  );
	}
}

int BasicUdpAppWrapper::numInitStages( void ) const {
	return std::max( Super::numInitStages(), 6 );
}

void BasicUdpAppWrapper::initialize( int stage ) {

	Super::initialize( stage );

	switch( stage ) {
		case inet::INITSTAGE_LOCAL: {
		    setName( getAppName().c_str() );
			AttackCoordinator::getSingleton().registerAppSpecProperties( getHostName(), getAppName(), getIndex(), this, getPort() );
			getNotificationBoard()->emit(inet::l2AssociatedSignal, this);
			break;
		}
		case inet::INITSTAGE_LAST: {
			recordInterfaceIPAddresses();
			_hlaModulePtr = getModuleByPath("hlaInterface");
            if (_hlaModulePtr == nullptr) {
                std::cerr << "ERROR:  BasicUdpAppWrapper:  \"" << getHostName() << "\" no hlaInterface detected:  ceasing execution." << std::endl;
                throw omnetpp::cException(omnetpp::E_CANCEL);
            }
			break;
		}
	}

}

void BasicUdpAppWrapper::handleMessage( omnetpp::cMessage *msg ) {

    inet::Packet* packet = dynamic_cast< inet::Packet * > ( msg );
    if ( packet == nullptr ) {
        std::cerr << "WARNING:  Hostname \"" << getHostName() << "\":  BasicUdpAppWrapper:  handleMessage method:  received message is not an inet::Packet:  ignoring." << std::endl;
        delete msg;
        return;
    }

    auto c_packetChunkPtr = packet->template peekAtFront<inet::cPacketChunk>();
    inet::cPacket *c_packetPtr = c_packetChunkPtr->getPacket();

    InteractionMsg *interactionMsg = dynamic_cast< InteractionMsg * >( c_packetPtr );
    if ( interactionMsg != 0 ) {
        int messageNo = interactionMsg->getMessageNo();
        if ( !interactionMsg->getToHLA() && !_messageTracker.addInt( messageNo )  ) {
//          std::cout << "BasicUdpAppWrapper: \"" << getHostName() << "\" dropping duplicate message (" << messageNo << ")." << std::endl;
            delete msg;
            return;  // DROP MESSAGE
        }
        interactionMsg->setToHLA( !interactionMsg->getToHLA() );
    }
    // std::cout << "BasicUdpAppWrapper: \"" << getHostName() << "\" received message, forwarding to wrapped module." << std::endl;

    Super::handleMessage( msg );
}

void BasicUdpAppWrapper::sendToUDP( inet::Packet *packet, const inet::Ipv4Address& destAddr, int destPort ) {

    auto c_packetChunkPtr = packet->template peekAtFront<inet::cPacketChunk>();
    inet::cPacket *c_packetPtr = c_packetChunkPtr->getPacket();

    InteractionMsg *interactionMsgPtr = dynamic_cast< InteractionMsg * >( c_packetPtr );
	if ( interactionMsgPtr == 0 ) {
		std::cerr << "Hostname \"" << getHostName() << "\":  BasicUdpAppWrapper:  sendToUDP method:  sending non-InteractionMsg-containing-Packet into network." << std::endl;
		Super::sendToUDP( packet, destAddr, destPort );
		return;
	}

    InteractionRoot &interactionRoot = *interactionMsgPtr->getInteractionRootSP();

	//
	// INTEGRITY ATTACK
	//
	if ( AttackCoordinator::getSingleton().isIntegrityAttackEnabled( getHostName() ) ) {

        std::cout << "Got network packet, and integrity attack is enabled" << std::endl;
        std::cout << "Got interaction is: " << interactionRoot << std::endl;

        AttackCoordinator::IntegrityAttackParams &iap = AttackCoordinator::getSingleton().getIntegrityAttackParams( this, getHostName() );

        tweakIncoming( interactionRoot, iap);
    }

    if ( interactionMsgPtr->getToHLA() ) {

        std::cout << "BasicUdpAppWrapper: \"" << getHostName() << "\" sending cPacket to HLA" << std::endl;

		if (  AttackCoordinator::getSingleton().modifyToHLAPackets( getHostName() )  ) {
		    setToDefaultValues( interactionRoot );
		}

        sendDirect( packet, _hlaModulePtr, "hlaOut" );

		return;
	}

	if (  AttackCoordinator::getSingleton().modifyFromHLAPackets( getHostName() )  ) {
	    setToDefaultValues( interactionRoot );
	}

    std::string receiverHost( interactionMsgPtr->getReceiverHost() );
    std::string receiverHostApp( interactionMsgPtr->getReceiverHostApp() );
    int receiverAppIndex( interactionMsgPtr->getReceiverAppIndex() );
    std::string receiverAppInterface( interactionMsgPtr->getReceiverAppInterface() );

	// Udpate message length

	if ( receiverAppIndex == -1 ) {
		// std::cerr << "Hostname \"" << getHostName() << "\":  BasicUdpAppWrapper:  handleMessage method:  sending InteractionMsg to application-specified destination in network." << std::endl;
		Super::sendToUDP( packet, destAddr, destPort );

	}

	AttackCoordinator::AppSpec appSpec( receiverHost, receiverHostApp, receiverAppIndex );
	AttackCoordinator::AppProperties appProperties = AttackCoordinator::getSingleton().getAppSpecProperties( appSpec );
	if ( appProperties.getPort() == -1 ) {
		// std::cerr << "ERROR:  Hostname \"" << getHostName() << "\":  BasicUdpAppWrapper:  handleMessage method:  Could not find app properties for \"" << appSpec << "\":  dropping message." << std::endl;
		delete packet;
		return;
	}

	inet::Ipv4Address destinationIPAddress = appProperties.getIPAddress( receiverAppInterface );
	int destinationPort = appProperties.getPort();
	// std::cerr << "BasicUDPAppWrapper: sending packet to " << destinationIPAddress << "(" << destinationPort << ")" << std::endl;

	// std::cerr << "Hostname \"" << getHostName() << "\":  BasicUdpAppWrapper:  handleMessage method:  sending InteractionMsg to NetworkPacket-specified destination in network." << std::endl;
	Super::sendToUDP( packet, destinationIPAddress, destinationPort );
}

void BasicUdpAppWrapper::setToDefaultValues( InteractionRoot &interactionRoot ) {
    InteractionRoot defaultInteractionRoot( interactionRoot.getInstanceHlaClassName() );

    const InteractionRoot::ClassAndPropertyNameValueSPMap &classAndPropertyValueSPMap = interactionRoot.getClassAndPropertyNameValueSPMap();
    const InteractionRoot::ClassAndPropertyNameValueSPMap &defaultClassAndPropertyValueSPMap = defaultInteractionRoot.getClassAndPropertyNameValueSPMap();

    for(
      InteractionRoot::ClassAndPropertyNameValueSPMap::const_iterator cvmCit = classAndPropertyValueSPMap.begin() ;
      cvmCit != classAndPropertyValueSPMap.end() ;
      ++cvmCit
    ) {
        TypeMedley &value = *cvmCit->second;
        TypeMedley &defaultValue = *defaultClassAndPropertyValueSPMap.find(cvmCit->first)->second;

        value.setValue(defaultValue);
    }
}

void BasicUdpAppWrapper::tweakIncoming( InteractionRoot &interactionRoot, AttackCoordinator::IntegrityAttackParams &iap) {

    const InteractionRoot::ClassAndPropertyNameValueSPMap &classAndPropertyValueSPMap = interactionRoot.getClassAndPropertyNameValueSPMap();

    for(
      InteractionRoot::ClassAndPropertyNameValueSPMap::const_iterator cvmCit = classAndPropertyValueSPMap.begin() ;
      cvmCit != classAndPropertyValueSPMap.end() ;
      ++cvmCit
    ) {
        TypeMedley &value = *cvmCit->second;

        switch( value.getDataType() ) {

            case TypeMedley::BOOLEAN: {
                if ( iap.getBooleanEnableFlip() ) {
                    value.setValue( !value.asBool() );
                }
                break;
            }
            case TypeMedley::DOUBLE: {
                value.setValue( value.asDouble() * iap.getDoubleMultiplier() + iap.getDoubleAdder() );
                break;
            }
            case TypeMedley::INTEGER: {
                value.setValue( value.asInt() * iap.getIntMultiplier() + iap.getIntAdder() );
                break;
            }
            case TypeMedley::LONG: {
                value.setValue( value.asLong() * iap.getLongMultiplier() + iap.getLongAdder() );
                break;
            }
            case TypeMedley::STRING: {
                if (!iap.getStringReplacement().empty()) {
                    value.setValue( iap.getStringReplacement() );
                }
            }
        }
    }
}
