//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

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

    InteractionMsg *interactionMsg = dynamic_cast< InteractionMsg * >( c_packetPtr );
	if ( interactionMsg == 0 ) {
		std::cerr << "Hostname \"" << getHostName() << "\":  BasicUdpAppWrapper:  sendToUDP method:  sending non-InteractionMsg-containing-Packet into network." << std::endl;
		Super::sendToUDP( packet, destAddr, destPort );
		return;
	}

    InteractionRoot::SP interactionRootSP = interactionMsg->getInteractionRootSP();

    // Integrity attack, if any
    if ( NetworkPacket::match( interactionRootSP->getClassHandle() ) && AttackCoordinator::getSingleton().isIntegrityAttackEnabled( getHostName() ) ) {

        // std::cout << "Got network packet, and integrity attack is enabled" << std::endl;
        // std::cout << "Got interaction is: " << interactionRootSP << std::endl;

        NetworkPacket::SP networkPacketSP = boost::static_pointer_cast< NetworkPacket >( interactionRootSP );

        // std::cout << "The corresponding NetworkPacketSP = ";
        // if ( networkPacketSP ) {
        //     std::cout << networkPacketSP << std::endl;
        // } else {
        //     std::cout << "NULL";
        // }

        AttackCoordinator::IntegrityAttackParams &iap = AttackCoordinator::getSingleton().getIntegrityAttackParams( this, getHostName() );
        networkPacketSP = tweakIncoming(
                networkPacketSP,
                iap.getIntMultiplier(),
                iap.getIntAdder(),
                iap.getLongMultiplier(),
                iap.getLongAdder(),
                iap.getDoubleMultiplier(),
                iap.getDoubleAdder(),
                iap.getBooleanEnableFlip(),
                iap.getStringReplacement()
        );
        interactionMsg->setInteractionRootSP(  boost::static_pointer_cast< InteractionRoot >( networkPacketSP )  );
    }

    if ( interactionMsg->getToHLA() ) {

        // std::cout << "BasicUdpAppWrapper: \"" << getHostName() << "\" sending cPacket to HLA" << std::endl;

		if (  NetworkPacket::match( interactionRootSP->getClassHandle() ) && AttackCoordinator::getSingleton().modifyToHLAPackets( getHostName() )  ) {
		    NetworkPacket::SP networkPacketSP = boost::static_pointer_cast< NetworkPacket >( interactionRootSP );
		    networkPacketSP = modifyOutgoing( networkPacketSP );
		    interactionMsg->setInteractionRootSP(  boost::static_pointer_cast< InteractionRoot >( networkPacketSP )  );
		}

        sendDirect( packet, _hlaModulePtr, "hlaOut" );

		return;
	}

	if (  !NetworkPacket::match( interactionRootSP->getClassHandle() )  ) {
		std::cerr << "WARNING:  Hostname \"" << getHostName() << "\":  BasicUdpAppWrapper:  handleMessage method:  Wrapped interaction is not of type \"NetworkPacket\":  ignoring" << std::endl;
		delete packet;
		return;
	}

	NetworkPacket::SP networkPacketSP = boost::static_pointer_cast< NetworkPacket >( interactionRootSP );
	if (  AttackCoordinator::getSingleton().modifyFromHLAPackets( getHostName() )  ) {
        networkPacketSP = modifyIncoming( networkPacketSP );
        interactionRootSP = boost::static_pointer_cast< InteractionRoot >( networkPacketSP );
        interactionMsg->setInteractionRootSP( interactionRootSP );
	}

	std::string receiverHost( networkPacketSP->get_receiverHost() );
	std::string receiverHostApp( networkPacketSP->get_receiverHostApp() );
	int receiverAppIndex( networkPacketSP->get_receiverAppIndex() );
	std::string receiverAppInterface( networkPacketSP->get_receiverAppInterface() );

	// Udpate message length
	interactionMsg->setByteLength( networkPacketSP->get_numBytes() );

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

NetworkPacket::SP BasicUdpAppWrapper::modifyIncoming( NetworkPacket::SP networkPacketSP ) {
    std::string data = networkPacketSP->get_data();
    int dataLen = data.length();
    if(dataLen == 0) {
        dataLen++;
    }
    std::stringstream dataSS;
    for(int i=0; i<dataLen; i++) {
        dataSS << "#";
    }
    networkPacketSP->set_data( dataSS.str() );
    return networkPacketSP;
}

NetworkPacket::SP BasicUdpAppWrapper::modifyOutgoing( NetworkPacket::SP networkPacketSP ) {
    std::string data = networkPacketSP->get_data();
    int dataLen = data.length();
    if(dataLen == 0) {
        dataLen++;
    }
    std::stringstream dataSS;
    for(int i=0; i<dataLen; i++) {
        dataSS << "#";
    }
    networkPacketSP->set_data( dataSS.str() );
    return networkPacketSP;
}

NetworkPacket::SP BasicUdpAppWrapper::tweakIncoming( NetworkPacket::SP networkPacketSP, int intMultiplier, int intAdder, long longMultiplier, long longAdder, double doubleMultiplier, double doubleAdder, bool booleanEnableFlip, const std::string &stringReplacement ) {


    std::string interactionJson = networkPacketSP->get_data();

    InteractionRoot::SP wrappedInteractionSP = InteractionRoot::fromJson(interactionJson);

    const InteractionRoot::ClassAndPropertyNameValueSPMap &classAndPropertyValueSPMap = wrappedInteractionSP->getClassAndPropertyNameValueSPMap();

    for(
      InteractionRoot::ClassAndPropertyNameValueSPMap::const_iterator cvmCit = classAndPropertyValueSPMap.begin() ;
      cvmCit != classAndPropertyValueSPMap.end() ;
      ++cvmCit
    ) {
        TypeMedley &value = *cvmCit->second;

        TypeMedley::DataType dataType = value.getDataType();

        switch(dataType) {

            case TypeMedley::INTEGER: {
                int currentValue = static_cast<int>(value);
                int newValue = (currentValue * intMultiplier) + intAdder;
                value.setValue(newValue);
                break;
            }

            case TypeMedley::LONG: {
                long currentValue = static_cast<long>(value);
                long newValue = (currentValue * longMultiplier) + longAdder;
                value.setValue(newValue);
                break;
            }

            case TypeMedley::DOUBLE: {
                double currentValue = static_cast<double>(value);
                double newValue = (currentValue * doubleMultiplier) + doubleAdder;
                value.setValue(newValue);
                break;
            }

            case TypeMedley::BOOLEAN: {
                bool currentValue = static_cast<bool>(value);
                bool newValue = booleanEnableFlip ? !currentValue : currentValue;
                value.setValue(newValue);
                break;
            }

            case TypeMedley::STRING: {
                std::string currentValue = static_cast<std::string>(value);
                std::string newValue = stringReplacement.empty() ? currentValue : stringReplacement;
                value.setValue(newValue);
                break;
            }
        }
    }
    networkPacketSP->set_data(wrappedInteractionSP->toJson());
    return networkPacketSP;
}
