//
// AddRouteEntryMsg.msg
//

cplusplus {{
#include "AttackCoordinator.h"
}};

class noncobject AttackCoordinator::RouteEntrySP;

message AddRouteEntryMsg extends cPacket {
    AttackCoordinator::RouteEntrySP routeEntrySP;
}
