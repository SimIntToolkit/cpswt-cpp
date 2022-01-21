//
// ObjectMsg.msg
//

cplusplus {{
#include <ObjectRoot.hpp>

using ObjectRoot = ::org::cpswt::hla::ObjectRoot;
}};

class noncobject ObjectRoot::SP;

message ObjectMsg extends cPacket {
    ObjectRoot::SP objectRootSP;
}
