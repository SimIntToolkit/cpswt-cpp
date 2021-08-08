/*
 * InteractionRoot.cc
 *
 *  Created on: Aug 7, 2021
 *      Author: hnine999
 */

#include <InteractionRoot.hpp>
#include <NetworkPacket.hpp>


InteractionRootSP InteractionRoot::create_interaction(const std::string &className) {
    return InteractionRootSP(new NetworkPacket());
}
