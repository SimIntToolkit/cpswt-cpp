/*
 * Certain portions of this software are Copyright (C) 2006-present
 * Vanderbilt University, Institute for Software Integrated Systems.
 *
 * Certain portions of this software are contributed as a public service by
 * The National Institute of Standards and Technology (NIST) and are not
 * subject to U.S. Copyright.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above Vanderbilt University copyright notice, NIST contribution
 * notice and this permission and disclaimer notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE. THE AUTHORS OR COPYRIGHT HOLDERS SHALL NOT HAVE
 * ANY OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS,
 * OR MODIFICATIONS.
 */

#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/CommandExecutionStatus.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/AddRouteToRoutingTable.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/DropRouteFromRoutingTable.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/AttacksNotYetImplemented.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/AttacksNotYetImplemented_p/StartDataInjectionAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/AttacksNotYetImplemented_p/StopDataInjectionAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/AttacksNotYetImplemented_p/StartDNSPoisoningAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/AttacksNotYetImplemented_p/StopDNSPoisoningAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/AttacksNotYetImplemented_p/StartLinkAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/AttacksNotYetImplemented_p/StopLinkAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/AttacksNotYetImplemented_p/StartMasqueradingAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/AttacksNotYetImplemented_p/StopMasqueradingAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/BecomeObservable.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/BecomeNotObservable.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StartDelayNodeAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StopDelayNodeAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StartDisableNetworkAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StopDisableNetworkAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StartIntegrityAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StopIntegrityAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StartModifyFromHLAPacketsAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StopModifyFromHLAPacketsAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StartModifyToHLAPacketsAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StopModifyToHLAPacketsAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StartNetworkFilterAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StopNetworkFilterAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StartNetworkIPFirewall.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StopNetworkIPFirewall.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StartNodeAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StopNodeAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StartOutOfOrderPacketsAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StopOutOfOrderPacketsAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StartRecordingPacketsForReplayAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StopRecordingPacketsForReplayAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/EraseRecordedPacketsForReplayAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StartReplayAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StopReplayAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StartSnifferAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StopSnifferAttack.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/TakeOwnership.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/LoseOwnership.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/NetworkStatus.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/NetworkStatusRequest.hpp"
#include "InteractionRoot_p/C2WInteractionRoot_p/OutcomeBase.hpp"
