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

#include <inet/networklayer/common/InterfaceTable.h>
#include <inet/networklayer/ipv4/Ipv4InterfaceData.h>

#include "BasicUdpApp.h"
#include <messages/HlaMsg_m.h>

Define_Module(BasicUdpApp);

void BasicUdpApp::initialize( int stage ) {

	// REGISTER HOST IN HOSTNAME-IPADDRESS MAP

    switch( stage ) {
        case inet::INITSTAGE_LOCAL: {
            _interfaceTable = inet::getModuleFromPar<inet::IInterfaceTable>(par("interfaceTableModule"), this);
            _notificationBoard = inet::getContainingNode(this);

            _hostModule = getParentModule();
            _hostFullName = _hostModule->getFullPath();

            _port = par( "port" );
            _defaultDestPort = par( "destPort" );

            break;
        }
        case inet::INITSTAGE_LAST: {
            _socket.setOutputGate(  gate( "socketOut" )  );
            _socket.bind( _port );

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
		std::cerr << "WARNING:  Hostname \"" << _hostFullName << "\":  BasicUdpApp:  handleMessage method:  received message is not an inet::Packet:  ignoring." << std::endl;
		cancelAndDelete( msg );
		return;
	}

    sendToUDP(   packet, inet::Ipv4Address(  static_cast< uint32_t >( 0 )  ), getDefaultDestPort()   );
}

void BasicUdpApp::sendToUDP( inet::Packet *msgPkt, const inet::Ipv4Address& destAddr, int destPort ){
    // std::cout << "BasicUdpApp:  sendToUDP:  sending packet to " << destAddr << "(" << destPort << ")" << std::endl;
    _socket.sendTo( msgPkt, destAddr, destPort );
}
