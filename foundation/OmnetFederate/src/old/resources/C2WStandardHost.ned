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
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

package OmnetFederate;

import inet.applications.contract.IApp;
import inet.transportlayer.contract.ISctp;
import inet.transportlayer.contract.ITcp;
import inet.transportlayer.contract.IUdp;

import inet.applications.tcpapp.TcpClientApp;
import inet.applications.tcpapp.TcpServerApp;
import inet.applications.udpapp.UdpApp;
import inet.applications.sctpapp.SctpClient;
import inet.applications.sctpapp.SctpServer;
import inet.applications.pingapp.PingApp;

//
// IPv4 host with SCTP, TCP, UDP layers and applications.
// IP forwarding is disabled by default (see IPForward).
// - Can be connected via ethernet interface to other nodes using
//   the ethg gate. By default full-duplex connections are supported
//   only (twisted pair). Set **.eth[*].typename="EthernetInterface" for
//   a full/half-duplex CSMA/CD implementation (coaxial cable)
// - By default contains no wireless cards, however it can be configured
//   by the numRadios parameter. Wirless card type is configured by the
//   **.wlan[*].typename parameter. see:  inet.linklayer.ieee80211 or other
//   modules implementing ~IWirelessNic
// - Also external interfaces can be configured for HW in the loop simulation
//   using the numExtInterfaces parameter and setting the type using
//   **.ext[*].typename in the INI file. see: ~ExtInterface and ~IExternalNic
// - If wireless card is present, node mobility can be set using **.mobilityType
//   see: inet.mobility and ~IMobility
//
module C2WStandardHost extends C2WNodeBase
{
    parameters:
        @display("i=device/pc2");
        int numTcpClientApps = default(0);  // no of TCP client apps. These should all inherit from TcpClientApp
        bool hasTcpClientApps = default(numTcpClientApps > 0);

        int numTcpServerApps = default(0);  // no of TCP server apps. These should all inherit from TcpServerApp
        bool hasTcpServerApps = default(numTcpClientApps > 0);

        bool hasTcpApps = hasTcpClientApps || hasTcpServerApps;

        string tcpType = default(firstAvailable("Tcp", "TcpLwip", "TcpNsc", "TcpNone"));  // tcp implementation (e.g. ~TCP, ~TCP_lwIP, ~TCP_NSC) or ~TCPSpoof

        int numUdpApps = default(0);  // no of UDP apps. They should all inherit from UdpApp.
        bool hasUdpApps = default(numUdpApps > 0);
        string udpType = default(firstAvailable("Udp","UdpNone"));

        int numSctpClientApps = default(0); // no of SCTP client apps. They should all inherit from SctpClientApp
        bool hasSctpClientApps = default(numSctpClientApps > 0);

        int numSctpServerApps = default(0); // no of SCTP server apps. They should all inherit from SctpServerApp
        bool hasSctpServerApps = default(numSctpServerApps > 0);

        bool hasSctpApps = hasSctpClientApps || hasSctpServerApps;

        string sctpType = default(firstAvailable("Sctp","SctpNone"));

        int numPingApps = default(0);  // no of PING apps. Specify the app types in INI file with pingApp[0..1].typename="PingApp" syntax
        bool hasPingApps = numPingApps > 0;

        IPForward = default(false);  // disable routing by default
    //        networkLayer.proxyARP = default(false);
    submodules:
        tcpClientApp[numTcpClientApps]: TcpClientApp if hasTcpClientApps {
            parameters:
                @display("p=212,42,row,60");
        }
        tcpServerApp[numTcpServerApps]: TcpServerApp if hasTcpServerApps {
            parameters:
                @display("p=400,58,row,60");
        }
        tcp: <tcpType> like ITcp if hasTcpApps {
            parameters:
                @display("p=264,141");
        }

        udpApp[numUdpApps]: UdpApp if hasUdpApps {
            parameters:
                @display("p=559,42,row,60");
        }
        udp: <udpType> like IUdp if hasUdpApps || numC2WDHCPClients > 0 {
            parameters:
                @display("p=559,141");
        }

        sctpClientApp[numSctpClientApps]: SctpClient if hasSctpClientApps {
            parameters:
                @display("p=693,58,row,60");
        }
        sctpServerApp[numSctpServerApps]: SctpServer if hasSctpServerApps {
            parameters:
                @display("p=849,42,row,60");
        }
        sctp: <sctpType> like ISctp if hasSctpApps {
            @display("p=773,141");
        }

        pingApp[numPingApps]: PingApp if hasPingApps {
            parameters:
                @display("p=773,269,row,60");
        }

    connections allowunconnected:
        for i=0..numTcpClientApps-1 {
            tcpClientApp[i].socketOut --> tcp.appIn;
            tcpClientApp[i].socketIn <-- tcp.appOut;
        }

        for i=0..numTcpServerApps-1 {
            tcpServerApp[i].socketOut --> tcp.appIn;
            tcpServerApp[i].socketIn <-- tcp.appOut;
        }

        tcp.ipOut --> networkLayer.transportIn++ if hasTcpApps;
        tcp.ipIn <-- networkLayer.transportOut++ if hasTcpApps;

        for i=0..numUdpApps-1 {
            udpApp[i].socketOut --> udp.appIn;
            udpApp[i].socketIn <-- udp.appOut;
        }

        udp.ipOut --> networkLayer.transportIn++ if hasUdpApps;
        udp.ipIn <-- networkLayer.transportOut++ if hasUdpApps;

        for i=0..numSctpClientApps-1 {
            sctpClientApp[i].socketOut --> sctp.appIn;
            sctp.appOut --> sctpClientApp[i].socketIn;
        }

        for i=0..numSctpServerApps-1 {
            sctpServerApp[i].socketOut --> sctp.appIn;
            sctp.appOut --> sctpServerApp[i].socketIn;
        }

        sctp.ipOut --> networkLayer.transportIn++ if hasSctpApps;
        networkLayer.transportOut++ --> sctp.ipIn if hasSctpApps;

        for i=0..numPingApps-1 {
            networkLayer.pingOut++ --> pingApp[i].socketIn;
            networkLayer.pingIn++ <-- pingApp[i].socketOut;
        }
}
