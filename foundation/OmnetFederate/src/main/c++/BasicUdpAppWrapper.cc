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


Define_Module(BasicUdpAppWrapper);


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

void BasicUdpAppWrapper::handleMessage( cMessage *msg ) {

    InteractionMsg *interactionMsg = dynamic_cast< InteractionMsg * >( msg );
    if ( interactionMsg != 0 ) {
        int messageNo = interactionMsg->getMessageNo();
        if ( !interactionMsg->getToHLA() && !_messageTracker.addInt( messageNo )  ) {
//          std::cout << "BasicUdpAppWrapper: \"" << getHostName() << "\" dropping duplicate message (" << messageNo << ")." << std::endl;
            cancelAndDelete( msg );
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

    InteractionRootSP interactionRootSP = interactionMsg->getInteractionRootSP();

    // Integrity attack, if any
    if ( NetworkPacket::match( interactionRootSP->getClassHandle() ) && AttackCoordinator::getSingleton().isIntegrityAttackEnabled( getHostName() ) ) {

        // std::cout << "Got network packet, and integrity attack is enabled" << std::endl;
        // std::cout << "Got interaction is: " << interactionRootSP << std::endl;

        NetworkPacketSP networkPacketSP = boost::static_pointer_cast< NetworkPacket >( interactionRootSP );

        // std::cout << "The corresponding NetworkPacketSP = ";
        // if ( networkPacketSP ) {
        //     std::cout << networkPacketSP << std::endl;
        // } else {
        //     std::cout << "NULL";
        // }

        AttackCoordinator::IntegrityAttackParams &iap = AttackCoordinator::getSingleton().getIntegrityAttackParams( this, getHostName() );
        networkPacketSP = tweakIncoming( networkPacketSP, iap.getIntMultiplier(), iap.getIntAdder(), iap.getLongMultiplier(), iap.getLongAdder(), iap.getDoubleMultiplier(), iap.getDoubleAdder(), iap.getBooleanEnableFlip(), iap.getStringReplacement() );
        interactionMsg->setInteractionRootSP(  boost::static_pointer_cast< InteractionRoot >( networkPacketSP )  );
    }

    if ( interactionMsg->getToHLA() ) {

        // std::cout << "BasicUdpAppWrapper: \"" << getHostName() << "\" sending cPacket to HLA" << std::endl;

		if (  NetworkPacket::match( interactionRootSP->getClassHandle() ) && AttackCoordinator::getSingleton().modifyToHLAPackets( getHostName() )  ) {
		    NetworkPacketSP networkPacketSP = boost::static_pointer_cast< NetworkPacket >( interactionRootSP );
		    networkPacketSP = modifyOutgoing( networkPacketSP );
		    interactionMsg->setInteractionRootSP(  boost::static_pointer_cast< InteractionRoot >( networkPacketSP )  );
		}

        sendDirect( packet, _hlaModulePtr, "hlaOut" );
        cancelAndDelete( packet );

		return;
	}

	if (  !NetworkPacket::match( interactionRootSP->getClassHandle() )  ) {
		std::cerr << "WARNING:  Hostname \"" << getHostName() << "\":  BasicUdpAppWrapper:  handleMessage method:  Wrapped interaction is not of type \"NetworkPacket\":  ignoring" << std::endl;
		cancelAndDelete( packet );
		return;
	}

	NetworkPacketSP networkPacketSP = boost::static_pointer_cast< NetworkPacket >( interactionRootSP );
	if (  AttackCoordinator::getSingleton().modifyFromHLAPackets( getHostName() )  ) {
        networkPacketSP = modifyIncoming( networkPacketSP );
        interactionRootSP = boost::static_pointer_cast< InteractionRoot >( networkPacketSP );
        interactionMsg->setInteractionRootSP( interactionRootSP );
	}

	std::string receiverHost( networkPacketSP->get_receiverHost() );
	std::string receiverHostApp( networkPacketSP->get_receiverHostApp() );
	int receiverAppIndex( networkPacketSP->get_receiverAppIndex() );
	std::string receiverAppInterface( networkPacketSP->get_receiverAppInterface() );

	// Update message length
	packet->setByteLength( networkPacketSP->get_numBytes() );

	if ( receiverAppIndex == -1 ) {
		// std::cerr << "Hostname \"" << getHostName() << "\":  BasicUdpAppWrapper:  handleMessage method:  sending InteractionMsg to application-specified destination in network." << std::endl;
		Super::sendToUDP( packet, destAddr, destPort );

	}

	AttackCoordinator::AppSpec appSpec( receiverHost, receiverHostApp, receiverAppIndex );
	AttackCoordinator::AppProperties appProperties = AttackCoordinator::getSingleton().getAppSpecProperties( appSpec );
	if ( appProperties.getPort() == -1 ) {
		// std::cerr << "ERROR:  Hostname \"" << getHostName() << "\":  BasicUdpAppWrapper:  handleMessage method:  Could not find app properties for \"" << appSpec << "\":  dropping message." << std::endl;
		cancelAndDelete( packet );
		return;
	}

	inet::Ipv4Address destinationIPAddress = appProperties.getIPAddress( receiverAppInterface );
	int destinationPort = appProperties.getPort();
	// std::cerr << "BasicUDPAppWrapper: sending packet to " << destinationIPAddress << "(" << destinationPort << ")" << std::endl;

	// std::cerr << "Hostname \"" << getHostName() << "\":  BasicUdpAppWrapper:  handleMessage method:  sending InteractionMsg to NetworkPacket-specified destination in network." << std::endl;
	Super::sendToUDP( packet, destinationIPAddress, destinationPort );
}

NetworkPacketSP BasicUdpAppWrapper::modifyIncoming( NetworkPacketSP networkPacketSP ) {
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

NetworkPacketSP BasicUdpAppWrapper::modifyOutgoing( NetworkPacketSP networkPacketSP ) {
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

NetworkPacketSP BasicUdpAppWrapper::tweakIncoming( NetworkPacketSP networkPacketSP, int intMultiplier, int intAdder, long longMultiplier, long longAdder, double doubleMultiplier, double doubleAdder, bool booleanEnableFlip, const std::string &stringReplacement ) {
    // std::cout << "BasicUdpAppWrapper::tweakIncoming() called..." << std::endl;

    // Create a dummy interaction of the packetType to extract its data types
    std::string packetType = networkPacketSP->get_packetType();

    // std::cout << "PacketType = " << packetType << std::endl;
    InteractionRoot::SP interactionRootSP = InteractionRoot::create_interaction( packetType );
    StringVector intrParamNamesList = interactionRootSP->getParameterNames();
    StringVector intrDataTypesList;

    // std::cout << "interaction created = " << interactionRootSP << std::endl;
    // std::cout << "params size = " << intrParamNamesList.size() << std::endl;

    for (StringVector::const_iterator it = intrParamNamesList.begin(); it!=intrParamNamesList.end(); ++it) {
        std::string paramName = *it;

        // std::cout << "Param name: " << paramName << std::endl;
        std::string paramType = interactionRootSP->getParameter(paramName).getTypeName();

        // std::cout << "Param type: " << paramType << std::endl;
        intrDataTypesList.push_back( paramType );
    }

    // Parse all data tokens in the payload of the network packet interaction
    std::string data = networkPacketSP->get_data();
    std::vector< std::string > dataTokens;
    std::string tokenSeparatorString = "*@*";
    size_t  pos = data.find(tokenSeparatorString);

    // std::cout << "Parsing data tokens now..." << std::endl;
    while (pos != std::string::npos)
    {
        std::string newTok = data.substr(0, pos); // find new token
        // std::cout << "Found token: " << newTok << std::endl;

        dataTokens.push_back(newTok); // add new token to the list
        data.erase(0, pos + 3); // remove last token and tokenSeparatorString from original string
        pos = data.find(tokenSeparatorString); // find more tokens
    }
    // std::cout << "Found token: " << data << std::endl;
    dataTokens.push_back(data); // last token

    // If there are no parameters, nothing to tweak
    if(intrDataTypesList.size() == 0) {
        return networkPacketSP;
    }

    // Make sure the quantity of data type names and payload data tokens is the same
    if(intrDataTypesList.size() != dataTokens.size()) {
        std::cerr << "ERROR:  BasicUdpAppWrapper:  \"" << getHostName() << "\" No. of data type tokens in the interaction of type '" << packetType << "' is not equal to no. of data tokens in the payload:\n\t" << data << std::endl;
    }

    // Replace the data value according to integrity attack
    std::stringstream updatedDataSS;
    std::vector<std::string>::const_iterator dtIt = intrDataTypesList.begin();
    std::string nextDataType = *dtIt;
    for(std::vector<std::string>::const_iterator tokIt = dataTokens.begin() ; tokIt != dataTokens.end() ; tokIt++) {
        std::string dataToken = *tokIt;
        if(nextDataType == "int" ) {
            int curVal = boost::lexical_cast< int >( dataToken );
            int newVal = (curVal * intMultiplier) + intAdder;
            updatedDataSS << newVal;
        } else if(nextDataType == "long" ) {
            long curVal = boost::lexical_cast< long >( dataToken );
            long newVal = (curVal * longMultiplier) + longAdder;
            updatedDataSS << newVal;
        } else if(nextDataType == "double" ) {
            double curVal = boost::lexical_cast< double >( dataToken );
            double newVal = (curVal * doubleMultiplier) + doubleAdder;
            updatedDataSS << newVal;
        } else if(nextDataType == "bool" ) {
            std::stringstream ssTemp;
            ssTemp << dataToken;
            bool curVal = false;
            ssTemp >> curVal;
            if(booleanEnableFlip) {
                if(curVal) {
                    updatedDataSS << "false";
                } else {
                    updatedDataSS << "true";
                }
            } else {
                if(curVal) {
                    updatedDataSS << "true";
                } else {
                    updatedDataSS << "false";
                }
            }
        } else if(nextDataType == "std::string" ) {
            if(stringReplacement == "") {
                updatedDataSS << dataToken;
            } else {
                updatedDataSS << stringReplacement;
            }
        } else {
            // Not int, long, double, boolean, or std::string, so simply use the same data token
            updatedDataSS << dataToken;
        }

        dtIt++;

        // If there are more tokens, add the separator
        if(dtIt != intrDataTypesList.end()) {
            updatedDataSS << tokenSeparatorString;
            nextDataType = *dtIt;
        }
    }

    // std::cout << "The tweaked data due to integrity attack is: " << updatedDataSS.str() << std::endl;
    networkPacketSP->set_data(updatedDataSS.str());
    return networkPacketSP;
}
