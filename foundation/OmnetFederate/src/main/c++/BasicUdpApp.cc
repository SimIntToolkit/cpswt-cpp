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

Define_Module(BasicUdpApp);

void BasicUdpApp::initialize( int stage ) {

	// REGISTER HOST IN HOSTNAME-IPADDRESS MAP

    switch( stage ) {
        case inet::INITSTAGE_LOCAL: {
            _interfaceTable = inet::getModuleFromPar<inet::IInterfaceTable>(par("interfaceTableModule"), this);
            _notificationBoard = inet::getContainingNode(this);

            _hostModule = getParentModule();
            _hostName = _hostModule->getFullPath();

            _port = par( "port" );
            _defaultDestPort = par( "destPort" );

            _socket.setOutputGate(  gate( "udpOut" )  );
            _socket.bind( _port );

            break;
        }
        case inet::INITSTAGE_LAST: {
            // SHOULD BE LAST BECAUSE MODULE WHERE SUBSCRIPTION TAKES PLACE MUST EXIST -- COULD BE ANY NODE
            _notificationBoard->subscribe( inet::interfaceIpv4ConfigChangedSignal, this );
            break;
        }
    }

}

void BasicUdpApp::receiveSignal(omnetpp::cComponent *source, omnetpp::simsignal_t signalID, omnetpp::cObject *obj, omnetpp::cObject *details) {

    Enter_Method_Silent( "receiveChangeNotification" );

    if ( signalID == inet::interfaceIpv4ConfigChangedSignal ) {

        // NOP

    } else {

        std::cerr << "WARNING:  unexpected notification \"" << getSignalName(signalID) << "\" from the cModule that is the NotificationBoard.";
// THE FOLLOWING LINE WILL CAUSE A SEGFAULT DUE TO THE USE OF VECTORS IN cModule that is the NotificationBoard MODULE FOR LISTENERS.
//      _notificationBoard->unsubscribe( this, category );

    }
}

void BasicUdpApp::handleMessage( omnetpp::cMessage *msg ) {

	inet::Packet* packet = dynamic_cast< inet::Packet * > ( msg );
	if ( packet == nullptr ) {
		std::cerr << "WARNING:  Hostname \"" << _hostName << "\":  BasicUdpApp:  handleMessage method:  received message is not an inet::Packet:  ignoring." << std::endl;
		cancelAndDelete( msg );
		return;
	}

    sendToUDP(   packet, inet::Ipv4Address(  static_cast< uint32_t >( 0 )  ), getDefaultDestPort()   );
}

void BasicUdpApp::sendToUDP( inet::Packet *msgPkt, const inet::Ipv4Address& destAddr, int destPort ){
    // std::cout << "BasicUdpApp:  sendToUDP:  sending packet to " << destAddr << "(" << destPort << ")" << std::endl;
    _socket.sendTo( msgPkt, destAddr, destPort );
}
