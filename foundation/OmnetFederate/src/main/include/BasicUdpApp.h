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

#ifndef BASICUDPAPP_H
#define BASICUDPAPP_H

#include <omnetpp.h>
#include <inet/transportlayer/contract/udp/UdpSocket.h>

#include <inet/networklayer/common/InterfaceTable.h>
#include <inet/networklayer/ipv4/Ipv4InterfaceData.h>
#include <inet/common/ModuleAccess.h>

#include "HLAInterface.h"


/**
 * TODO - Generated class
 */
class BasicUdpApp : public omnetpp::cSimpleModule, public omnetpp::cListener {

private:
    inet::UdpSocket _socket;
	std::string _hostName;
	inet::cModule *_hostModule;
	int _port;
	int _defaultDestPort;

    inet::IInterfaceTable *_interfaceTable;
    inet::cModule *_notificationBoard;

protected:
	virtual int numInitStages( void ) const override;
	virtual void initialize( int stage ) override;
	virtual void receiveChangeNotification( int category, const omnetpp::cObject *details );
	virtual void handleMessage(inet::cMessage *msg) override;

	inet::IInterfaceTable *getInterfaceTable( void ) { return _interfaceTable; }
	inet::cModule *getNotificationBoard( void ) { return _notificationBoard; }

public:
	inet::cModule *getHostModule( void ) const {
		return _hostModule;
	}

	const std::string &getHostName( void ) const {
		return _hostName;
	}

	int getPort( void ) {
		return _port;
	}
	int getDefaultDestPort( void ) {
	    return _defaultDestPort;
	}

    virtual void sendToUDP( inet::Packet *msg, const inet::Ipv4Address& destAddr, int destPort );
};

#endif
