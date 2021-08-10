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

package OmnetFederate;


//
// NodeAttackTest.ned
//

import ned.DatarateChannel;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;

import inet.node.inet.Router;
import inet.node.inet.StandardHost;

import OmnetFederate.CPSWTIpv4;
import OmnetFederate.BasicUdpAppWrapper;

channel FO1 extends DatarateChannel
{
    delay = 0.1us;
    datarate = 1Gbps;
    // delay = 10us;
    // datarate = 0.01Gbps;
    ber = 0;
}

network NodeAttackTestNetwork
{
    parameters:
        @display("bgb=708,404");

        host*.numApps = 1;
        host*.app[0].typename = "BasicUdpAppWrapper";

        host*.ipv4.ip.typename = "CPSWTIpv4";
        router*.ipv4.ip.typename = "CPSWTIpv4";

    submodules:
        configurator: Ipv4NetworkConfigurator {
            @display("p=174,29");
        }
        hlaInterface: NodeAttackTest {
            @display("p=49,29;i=block/dispatch");
        }
        host1: StandardHost {
            @display("p=98,266;i=,yellow");
        }
        host2: StandardHost {
            @display("p=338,154;i=,yellow");
        }
        host3: StandardHost {
            @display("p=560,266;i=,yellow");
        }
        router1: Router {
            @display("p=246,265;i=old/router2,lavender");
        }
        router2: Router {
            @display("p=413,265;i=old/router2,lavender");
        }
    connections:
        host1.ethg++ <--> FO1 <--> router1.ethg++;
        router1.ethg++ <--> FO1 <--> host2.ethg++;
        router1.ethg++ <--> FO1 <--> router2.ethg++;
        host2.ethg++ <--> FO1 <--> router2.ethg++;
        router2.ethg++ <--> FO1 <--> host3.ethg++;
}

