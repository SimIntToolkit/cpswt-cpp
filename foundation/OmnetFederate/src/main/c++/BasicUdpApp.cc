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

#include <inet/networklayer/common/InterfaceTable.h>
#include <inet/networklayer/ipv4/Ipv4InterfaceData.h>

#include "BasicUdpApp.h"
#include <messages/InteractionMsg_m.h>

#include "HLAInterface.h"

Define_Module(BasicUdpApp);

int BasicUdpApp::numInitStages( void ) const {
	return 6;
}

void BasicUdpApp::initialize( int stage ) {

	// REGISTER HOST IN HOSTNAME-IPADDRESS MAP

    switch( stage ) {
        case 0: {
            _interfaceTable = inet::getModuleFromPar<inet::IInterfaceTable>(par("interfaceTableModule"), this);
            _notificationBoard = inet::getContainingNode(this);
            break;
        }
        case 3: {
            _hostModule = getParentModule();
            _hostName = _hostModule->getFullPath();

            _port = par( "port" );
            _defaultDestPort = par( "destPort" );

            _socket.setOutputGate(  gate( "udpOut" )  );
            _socket.bind( _port );

            break;
        }
        case 4: {
            _notificationBoard->subscribe( inet::interfaceIpv4ConfigChangedSignal, this );
            break;
        }
    }

}

void BasicUdpApp::receiveChangeNotification( int category, const omnetpp::cObject *details ) {

    Enter_Method_Silent( "receiveChangeNotification" );

    if ( category == inet::interfaceIpv4ConfigChangedSignal ) {

        // NOP

    } else {

        std::cerr << "WARNING:  unexpected notification \"" << category << "\" from the cModule that is the NotificationBoard:  unsubscribing.";
// THE FOLLOWING LINE WILL CAUSE A SEGFAULT DUE TO THE USE OF VECTORS IN cModule that is the NotificationBoard MODULE FOR LISTENERS.
//      _notificationBoard->unsubscribe( this, category );

    }
}

void BasicUdpApp::handleMessage( omnetpp::cMessage *msg ) {

	inet::Packet* msgPkt = dynamic_cast< inet::Packet * > ( msg );
	if ( msgPkt == 0 ) {
		std::cerr << "WARNING:  Hostname \"" << _hostName << "\":  BasicUdpApp:  handleMessage method:  received message is not a omnetpp::cPacket:  ignoring." << std::endl;
		cancelAndDelete( msg );
		return;
	}

	InteractionMsg *interactionMsg = dynamic_cast< InteractionMsg * >( msg );
	if ( interactionMsg == 0 ) {
		std::cerr << "WARNING:  Hostname \"" << _hostName << "\":  BasicUdpApp:  handleMessage method:  routing of non-InteractionMsg packet not implemented:  dropping packet." << std::endl;
//		TODO:		BasicUdpApp::sendToUDP( msg, srcPort, destAddr, destPort );
		cancelAndDelete( msg );
		return;
	}

    sendToUDP(   msgPkt, inet::Ipv4Address(  static_cast< uint32_t >( 0 )  ), getDefaultDestPort()   );
}

void BasicUdpApp::sendToUDP( inet::Packet *msgPkt, const inet::Ipv4Address& destAddr, int destPort ){
    // std::cout << "BasicUdpApp:  sendToUDP:  sending packet to " << destAddr << "(" << destPort << ")" << std::endl;
    _socket.sendTo( msgPkt, destAddr, destPort );
}
