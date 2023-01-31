cplusplus {{
#include "/opt/inet4/src/inet/common/packet/Packet.h"
typedef inet::Packet *InetPacketPtr;
}};

class noncobject inet::Packet;
class noncobject InetPacketPtr;

message DelayNodeAttackMsg {
    InetPacketPtr delayedPacket;
}