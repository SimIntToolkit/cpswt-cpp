//
// InteractionMsg.msg
//

cplusplus {{
#include <InteractionRoot.hpp>

using InteractionRoot = ::org::cpswt::hla::InteractionRoot;
}};

class noncobject InteractionRoot::SP;

message InteractionMsg extends cPacket {
	bool toHLA;
	int messageNo;
    InteractionRoot::SP interactionRootSP;
}
