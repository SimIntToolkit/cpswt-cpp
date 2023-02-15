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

#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/TerminateReplayAttack.hpp"
namespace edu {
 namespace vanderbilt {
  namespace vuisis {
   namespace cpswt {
    namespace hla {
     namespace InteractionRoot_p {
      namespace C2WInteractionRoot_p {
       namespace ActionBase_p {
        namespace OmnetCommand_p {

bool TerminateReplayAttack::static_init_var = TerminateReplayAttack::static_init();

bool TerminateReplayAttack::static_init() {
    BOOST_LOG_SEV(get_logger(), info) << "Class \"::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::TerminateReplayAttack\" loaded.";

    // ADD THIS CLASS TO THE _classNameSet DEFINED IN InteractionRoot
    get_hla_class_name_set().insert(get_hla_class_name());

    InteractionRoot::NoInstanceInit noInstanceInit;
    SP instanceSP = SP( new TerminateReplayAttack(noInstanceInit) );
    get_hla_class_name_instance_sp_map()[get_hla_class_name()] = instanceSP;

    ClassAndPropertyNameSetSP classAndPropertyNameSetSP( new ClassAndPropertyNameSet() );

    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.TerminateReplayAttack", "dstNetworkAddress"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.TerminateReplayAttack", "dstNetworkAddress" )] =
      ValueSP( new Value( std::string("") ));

    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.TerminateReplayAttack", "recordingNodeFullPath"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.TerminateReplayAttack", "recordingNodeFullPath" )] =
      ValueSP( new Value( std::string("") ));

    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.TerminateReplayAttack", "srcNetworkAddress"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.TerminateReplayAttack", "srcNetworkAddress" )] =
      ValueSP( new Value( std::string("") ));

    // ADD THIS CLASS'S _classAndPropertyNameSet TO _classNamePropertyNameSetMap DEFINED
    // IN InteractionRoot
    get_class_name_class_and_property_name_set_sp_map()[get_hla_class_name()] = classAndPropertyNameSetSP;

    get_complete_class_and_property_name_set().insert(
      classAndPropertyNameSetSP->begin(), classAndPropertyNameSetSP->end()
    );

    ClassAndPropertyNameSetSP allClassAndPropertyNameSetSP( new ClassAndPropertyNameSet() );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.TerminateReplayAttack", "dstNetworkAddress"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.TerminateReplayAttack", "recordingNodeFullPath"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.TerminateReplayAttack", "srcNetworkAddress"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand", "uniqueCommandID"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot", "actualLogicalGenerationTime"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot", "federateFilter"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot", "federateSequence"
    );// ADD THIS CLASS'S _allClassAndPropertyNameSet TO _classNameAllPropertyNameSetMap DEFINED
    // IN InteractionRoot
    get_class_name_all_class_and_property_name_set_sp_map()[get_hla_class_name()] = allClassAndPropertyNameSetSP;

    common_init(get_hla_class_name());
    return true;
}

        } // NAMESPACE "OmnetCommand_p"
       } // NAMESPACE "ActionBase_p"
      } // NAMESPACE "C2WInteractionRoot_p"
     } // NAMESPACE "InteractionRoot_p"
    } // NAMESPACE "hla"
   } // NAMESPACE "cpswt"
  } // NAMESPACE "vuisis"
 } // NAMESPACE "vanderbilt"
} // NAMESPACE "edu"
