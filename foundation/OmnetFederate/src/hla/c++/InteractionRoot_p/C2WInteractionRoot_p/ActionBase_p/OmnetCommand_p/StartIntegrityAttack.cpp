
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
 *
 * @author Himanshu Neema
 * @author Harmon Nine
 */



#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/OmnetCommand_p/StartIntegrityAttack.hpp"
namespace org {
 namespace cpswt {
  namespace hla {
   namespace InteractionRoot_p {
    namespace C2WInteractionRoot_p {
     namespace ActionBase_p {
      namespace OmnetCommand_p {

bool StartIntegrityAttack::static_init_var = StartIntegrityAttack::static_init();

bool StartIntegrityAttack::static_init() {
    BOOST_LOG_SEV(get_logger(), info) << "Class \"::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::OmnetCommand_p::StartIntegrityAttack\" loaded.";

    // ADD THIS CLASS TO THE _classNameSet DEFINED IN InteractionRoot
    get_hla_class_name_set().insert(get_hla_class_name());

    InteractionRoot::NoInstanceInit noInstanceInit;
    SP instanceSP = SP( new StartIntegrityAttack(noInstanceInit) );
    get_hla_class_name_instance_sp_map()[get_hla_class_name()] = instanceSP;

    ClassAndPropertyNameSetSP classAndPropertyNameSetSP( new ClassAndPropertyNameSet() );
    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "booleanEnableFlip"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "booleanEnableFlip" )] =
      ValueSP( new Value( false ));
    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "doubleAdder"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "doubleAdder" )] =
      ValueSP( new Value( static_cast<double>(0) ));
    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "doubleMultiplier"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "doubleMultiplier" )] =
      ValueSP( new Value( static_cast<double>(0) ));
    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "intAdder"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "intAdder" )] =
      ValueSP( new Value( static_cast<int>(0) ));
    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "intMultiplier"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "intMultiplier" )] =
      ValueSP( new Value( static_cast<int>(0) ));
    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "longAdder"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "longAdder" )] =
      ValueSP( new Value( static_cast<long>(0) ));
    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "longMultiplier"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "longMultiplier" )] =
      ValueSP( new Value( static_cast<long>(0) ));
    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "nodeFullPath"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "nodeFullPath" )] =
      ValueSP( new Value( std::string("") ));
    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "stringReplacement"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "stringReplacement" )] =
      ValueSP( new Value( std::string("") ));

    // ADD THIS CLASS'S _classAndPropertyNameSet TO _classNamePropertyNameSetMap DEFINED
    // IN InteractionRoot
    get_class_name_class_and_property_name_set_sp_map()[get_hla_class_name()] = classAndPropertyNameSetSP;

    ClassAndPropertyNameSetSP allClassAndPropertyNameSetSP( new ClassAndPropertyNameSet() );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "booleanEnableFlip"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "doubleAdder"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "doubleMultiplier"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "intAdder"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "intMultiplier"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "longAdder"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "longMultiplier"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "nodeFullPath"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack", "stringReplacement"
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

    return true;
}

      } // NAMESPACE "OmnetCommand_p"
     } // NAMESPACE "ActionBase_p"
    } // NAMESPACE "C2WInteractionRoot_p"
   } // NAMESPACE "InteractionRoot_p"
  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"
