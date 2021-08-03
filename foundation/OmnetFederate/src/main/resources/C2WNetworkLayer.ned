//
// Copyright (C) 2004 Andras Varga
// Copyright (C) 2000 Institut fuer Telematik, Universitaet Karlsruhe
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

package OmnetFederate;

import inet.networklayer.arp.ipv4.Arp;
import inet.networklayer.configurator.ipv4.Ipv4NodeConfigurator;
import inet.networklayer.ipv4.Icmp;
import inet.networklayer.ipv4.IIgmp;
import inet.networklayer.ipv4.Ipv4;


//
// Network layer of an IPv4 node.
//
// Interfaces to transport layer: TCP, UDP, echo/ping, RSVP
//
module C2WNetworkLayer
{
    parameters:
        string igmpType = default("IGMPv2");
        *.routingTableModule = default("^.^.routingTable");
        @display("i=block/fork");
    gates:
        input ifIn[] @labels(IPv4Datagram);
        output ifOut[] @labels(IPv4Datagram);
        input transportIn[] @labels(IPv4ControlInfo/down);
        output transportOut[] @labels(IPv4ControlInfo/up);
        input pingIn[] @labels(PingPayload/down);
        output pingOut[] @labels(PingPayload/up);
        input igmpIn;
        output igmpOut;

    submodules:
        configurator: Ipv4NodeConfigurator {
            @display("p=39,158");
        }
        ip: C2WIPv4 {
            parameters:
                useProxyARP = true; // as routes with unspecified next-hop addr are quite common
                @display("p=85,95;q=queue");
            gates:
                queueIn[sizeof(ifIn)];
                queueOut[sizeof(ifOut)];
        }
        arp: Arp {
            parameters:
                @display("p=202,142;q=pendingQueue");
        }
        icmp: Icmp {
            parameters:
                @display("p=160,63");
        }
        igmp: <igmpType> like IIgmp {
            parameters:
                @display("p=39,33");
        }
//        errorHandling: ErrorHandling {
//            parameters:
//                @display("p=239,63");
//        }

    connections allowunconnected:
        for i=0..sizeof(transportIn)-1 {
            transportIn[i] --> { @display("m=n"); } --> ip.transportIn++;
        }
        for i=0..sizeof(transportOut)-1 {
            ip.transportOut++ --> { @display("m=n"); } --> transportOut[i];
        }

        ip.transportOut++ --> icmp.ipIn;
        ip.transportIn++ <-- icmp.ipOut;

        ip.transportOut++ --> igmp.ipIn;
        ip.transportIn++ <-- igmp.ipOut;

        for i=0..sizeof(pingOut)-1 {
            icmp.transportOut --> { @display("m=n"); } --> pingOut[i];
        }
        for i=0..sizeof(pingIn)-1 {
            icmp.ipIn <-- { @display("m=n"); } <-- pingIn[i];
        }

//        icmp.errorOut --> errorHandling.in;

        ip.arpOut --> arp.netwIn;
        ip.arpIn <-- arp.netwOut;

        igmp.routerOut --> igmpOut;
        igmp.routerIn <-- igmpIn;

        for i=0..sizeof(ifIn)-1 {
            ip.queueIn[i] <-- { @display("m=s"); } <-- ifIn[i];
        }
        for i=0..sizeof(ifOut)-1 {
            ip.queueOut[i] --> { @display("m=s"); } --> ifOut[i];
        }
}

