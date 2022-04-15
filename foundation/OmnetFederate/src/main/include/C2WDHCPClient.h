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

#ifndef __C2WDHCPCLIENT_H__
#define __C2WDHCPCLIENT_H__

#include <vector>
#include <inet/common/lifecycle/ModuleOperations.h>
#include <inet/linklayer/common/MacAddress.h>
#include <inet/applications/dhcp/DhcpMessage_m.h>
#include <inet/applications/dhcp/DhcpLease.h>
#include <inet/networklayer/common/InterfaceTable.h>
//#include "RoutingTable.h"
#include <inet/transportlayer/contract/udp/UdpSocket.h>
#include <inet/common/lifecycle/ILifecycle.h>
#include <inet/networklayer/contract/ipv4/Ipv4Address.h>
#include <inet/networklayer/ipv4/Ipv4Route.h>

/**
 * Implements a DHCP client. See NED file for more details.
 */
class INET_API C2WDHCPClient : public omnetpp::cSimpleModule, public omnetpp::cListener, public inet::ILifecycle
{
    using cListener::finish;

    protected:
        int serverPort;
        int clientPort;
        inet::UdpSocket socket; // UDP socket for client-server communication
        bool isOperational; // lifecycle
        omnetpp::cMessage* timerT1; // time at which the client enters the RENEWING state
        omnetpp::cMessage* timerT2; // time at which the client enters the REBINDING state
        omnetpp::cMessage* timerTo; // response timeout: WAIT_ACK, WAIT_OFFER
        omnetpp::cMessage* leaseTimer; // length of time the lease is valid
        omnetpp::cMessage* startTimer; // self message to start DHCP initialization

        // DHCP timer types (RFC 2131 4.4.5)
        enum TimerType
        {
            WAIT_OFFER, WAIT_ACK, T1, T2, LEASE_TIMEOUT, START_DHCP
        };

        // DHCP client states (RFC 2131, Figure 5: state transition diagram)
        enum ClientState
        {
            IDLE, INIT, INIT_REBOOT, REBOOTING, SELECTING, REQUESTING, BOUND, RENEWING, REBINDING
        };

        std::string hostName;
        int numSent; // number of sent DHCP messages
        int numReceived; // number of received DHCP messages
        int responseTimeout; // timeout waiting for DHCPACKs, DHCPOFFERs
        unsigned int xid; // transaction id; to associate messages and responses between a client and a server
        ClientState clientState; // current state
        omnetpp::simtime_t startTime; // application start time

        inet::MacAddress macAddress; // client's MAC address
        omnetpp::cModule * nb; // notification board
        inet::InterfaceEntry *ie; // interface to configure
        inet::IIpv4RoutingTable *irt; // routing table to update
        inet::DhcpLease *lease; // leased IP information
        inet::Ipv4Route *route; // last added route
        inet::Ipv4Address ipv4Address;
    protected:
        // Simulation methods.
        virtual int numInitStages() const override { return 4; }
        virtual void initialize(int stage) override;
        virtual void finish() override;
        virtual void handleMessage(omnetpp::cMessage * msg) override;

        /*
         * Opens a UDP socket for client-server communication.
         */
        virtual void openSocket();

        /*
         * Handles incoming DHCP messages, and implements the
         * state-transition diagram for DHCP clients.
         */
        virtual void handleDHCPMessage(inet::DhcpMessage * msg);

        /*
         * Performs state changes and requests according to the timer expiration events
         * (e. g. retransmits DHCPREQUEST after the WAIT_ACK timeout expires).
         */
        virtual void handleTimer(omnetpp::cMessage * msg);


        virtual void receiveChangeNotification(int category, const omnetpp::cObject * details);

        /*
         * Performs UDP transmission.
         */
        virtual void sendToUDP(inet::Packet * msg, int srcPort, const inet::L3Address& destAddr, int destPort);

        /*
         * Client broadcast to locate available servers.
         */
        virtual void sendDiscover();

        /*
         * Client message to servers either (a) requesting offered parameters
         * from one server and implicitly declining offers from all others,
         * (b) confirming correctness of previously allocated address after,
         * e.g., system reboot, or (c) extending the lease on a particular
         * network address.
         */
        virtual void sendRequest();

        /*
         * Client to server indicating network address is already in use.
         */
        virtual void sendDecline(inet::Ipv4Address declinedIp);

        /*
         * Records configuration parameters from a DHCPACK message.
         */
        virtual void recordLease(inet::DhcpMessage * dhcpACK);

        /*
         * Records minimal configuration parameters from a DHCPOFFER message.
         */
        virtual void recordOffer(inet::DhcpMessage * dhcpOffer);

        /*
         * Assigns the IP address to the interface.
         */
        virtual void bindLease();

        /*
         * Removes the configured IP address (e. g. when clients get a DHCPNAK message in REBINDING or RENEWING states
         * or the lease time expires).
         */
        virtual void unboundLease();

        /*
         * Starts the DHCP configuration process with sending a DHCPDISCOVER.
         */
        virtual void initClient();

        /*
         * Starts the DHCP configuration process with known network address.
         */
        virtual void initRebootedClient();

        /*
         * Handles DHCPACK in any state. Note that, handleDHCPACK() doesn't handle DHCPACK messages
         * in response to DHCPINFORM messages.
         */
        virtual void handleDHCPACK(inet::DhcpMessage * msg);

        virtual inet::InterfaceEntry *chooseInterface();
        virtual void scheduleTimerTO(TimerType type);
        virtual void scheduleTimerT1();
        virtual void scheduleTimerT2();
        static const char *getStateName(ClientState state);
        const char *getAndCheckMessageTypeName(inet::DhcpMessageType type);
        virtual void updateDisplayString();
        virtual void startApp();
        virtual void stopApp();

    public:
        C2WDHCPClient();
        virtual ~C2WDHCPClient();

        virtual bool handleOperationStage(inet::LifecycleOperation *operation, inet::IDoneCallback *doneCallback) override;
};

#endif

