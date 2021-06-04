//
// Copyright (C) 2008 Juan-Carlos Maureira
// Copyright (C) INRIA
// Copyright (C) 2013 OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#ifndef __C2WDHCPSERVER_H__
#define __C2WDHCPSERVER_H__

#include <vector>
#include <map>

//#include "INETDefs.h"

#include <inet/common/lifecycle/ModuleOperations.h>
#include <inet/transportlayer/contract/udp/UdpSocket.h>
#include <inet/applications/dhcp/DhcpMessage_m.h>
#include <inet/applications/dhcp/DhcpLease.h>
#include <inet/networklayer/common/InterfaceTable.h>
#include <inet/networklayer/arp/ipv4/Arp.h>
#include <inet/networklayer/common/InterfaceTable.h>
#include <inet/networklayer/contract/ipv4/Ipv4Address.h>

//class NotificationBoard;

/**
 * Implements a DHCP server. See NED file for more details.
 */
class INET_API C2WDHCPServer : public omnetpp::cSimpleModule, public omnetpp::cListener, public inet::ILifecycle
{
    protected:
        typedef std::map<inet::Ipv4Address, inet::DhcpLease> DHCPLeased;
        enum TimerType
        {
            START_DHCP
        };
        DHCPLeased leased; // lookup table for lease infos

        bool isOperational; // lifecycle
        int numSent; // num of sent UDP packets
        int numReceived; // num of received UDP packets
        int serverPort; // server port
        int clientPort; // client port

        /* Set by management, see DHCPServer NED file. */
        unsigned int maxNumOfClients;
        unsigned int leaseTime;
        inet::Ipv4Address subnetMask;
        inet::Ipv4Address gateway;
        inet::Ipv4Address ipAddressStart;
        inet::Ipv4Address ipv4Address;

        inet::InterfaceEntry *ie; // interface to serve DHCP requests on
        omnetpp::cModule *nb;
        inet::UdpSocket socket;
        omnetpp::simtime_t startTime; // application start time
        omnetpp::cMessage *startTimer; // self message to start DHCP server

    protected:
        virtual int numInitStages() const override { return 4; }
        virtual void initialize(int stage) override;
        virtual void handleMessage(omnetpp::cMessage *msg) override;

        /*
         * Opens a UDP socket for client-server communication.
         */
        virtual void openSocket();

        /*
         * Performs a database lookup by MAC address for lease information.
         */
        virtual inet::DhcpLease* getLeaseByMac(inet::MacAddress mac);

        /*
         * Gets the next available lease to be assigned.
         */
        virtual inet::DhcpLease* getAvailableLease(inet::Ipv4Address requestedAddress, const inet::MacAddress& clientMAC);

        /*
         * Implements the server's state machine.
         */
        virtual void processDHCPMessage(inet::Packet *packet);

        /*
         * Send DHCPOFFER message to client in response to DHCPDISCOVER with offer of configuration
         * parameters.
         */
        virtual void sendOffer(inet::DhcpLease* lease);

        /*
         * Send DHCPACK message to client with configuration parameters, including committed network address.
         */
        virtual void sendACK(inet::DhcpLease* lease, const inet::DhcpMessage * dhcpMessage);

        /*
         * Send DHCPNAK message to client indicating client's notion of network address is incorrect
         * (e.g., client has moved to new subnet) or client's lease as expired.
         */
        virtual void sendNAK(const inet::DhcpMessage* msg);

        virtual void handleSelfMessages(omnetpp::cMessage * msg);
        virtual inet::InterfaceEntry *chooseInterface();
        virtual void sendToUDP(inet::Packet *msg, int srcPort, const inet::L3Address& destAddr, int destPort);
        virtual void receiveChangeNotification(int category, const omnetpp::cObject *details);
        virtual void startApp();
        virtual void stopApp();

    public:
        C2WDHCPServer();
        virtual ~C2WDHCPServer();

        /*
         * For lifecycle management.
         */
        virtual bool handleOperationStage(inet::LifecycleOperation *operation, inet::IDoneCallback *doneCallback) override;
};

#endif

