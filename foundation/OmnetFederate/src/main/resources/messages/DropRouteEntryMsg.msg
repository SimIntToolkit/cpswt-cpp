//
// DropRouteEntryMsg
//

cplusplus {{
#include "AttackCoordinator.h"
}};

class noncobject AttackCoordinator::RouteEntrySP;

message DropRouteEntryMsg extends cPacket {
    AttackCoordinator::RouteEntrySP routeEntrySP;
}
