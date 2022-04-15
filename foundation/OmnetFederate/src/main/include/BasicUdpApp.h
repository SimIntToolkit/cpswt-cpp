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

#ifndef BASICUDPAPP_H
#define BASICUDPAPP_H

#include <omnetpp.h>
#include <inet/transportlayer/contract/udp/UdpSocket.h>

#include <inet/networklayer/common/InterfaceTable.h>
#include <inet/networklayer/ipv4/Ipv4InterfaceData.h>
#include <inet/common/ModuleAccess.h>

#include <inet/common/INETDefs.h>


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
    virtual int numInitStages() const override { return inet::NUM_INIT_STAGES; }
	virtual void initialize( int stage ) override;
	virtual void receiveSignal(omnetpp::cComponent *source, omnetpp::simsignal_t signalID, omnetpp::cObject *obj, omnetpp::cObject *details) override;
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
