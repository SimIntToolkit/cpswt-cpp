//
// Certain portions of this software are Copyright (C) 2006-present
// Vanderbilt University, Institute for Software Integrated Systems.
//
// Certain portions of this software are contributed as a public service by
// The National Institute of Standards and Technology (NIST) and are not
// subject to U.S. Copyright.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above Vanderbilt University copyright notice, NIST contribution
// notice and this permission and disclaimer notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE. THE AUTHORS OR COPYRIGHT HOLDERS SHALL NOT HAVE
// ANY OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS,
// OR MODIFICATIONS.
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

