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

#include "InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/NetworkPacket.hpp"
namespace edu {
 namespace vanderbilt {
  namespace vuisis {
   namespace cpswt {
    namespace hla {
     namespace InteractionRoot_p {
      namespace C2WInteractionRoot_p {
       namespace ActionBase_p {

bool NetworkPacket::static_init_var = NetworkPacket::static_init();

bool NetworkPacket::static_init() {
    BOOST_LOG_SEV(get_logger(), info) << "Class \"::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::NetworkPacket\" loaded.";

    // ADD THIS CLASS TO THE _classNameSet DEFINED IN InteractionRoot
    get_hla_class_name_set().insert(get_hla_class_name());

    InteractionRoot::NoInstanceInit noInstanceInit;
    SP instanceSP = SP( new NetworkPacket(noInstanceInit) );
    get_hla_class_name_instance_sp_map()[get_hla_class_name()] = instanceSP;

    ClassAndPropertyNameSetSP classAndPropertyNameSetSP( new ClassAndPropertyNameSet() );

    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "data"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "data" )] =
      ValueSP( new Value( std::string("") ));

    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "numBytes"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "numBytes" )] =
      ValueSP( new Value( static_cast<int>(0) ));

    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "packetType"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "packetType" )] =
      ValueSP( new Value( std::string("") ));

    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "receiverAppIndex"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "receiverAppIndex" )] =
      ValueSP( new Value( static_cast<int>(0) ));

    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "receiverAppInterface"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "receiverAppInterface" )] =
      ValueSP( new Value( std::string("") ));

    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "receiverHost"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "receiverHost" )] =
      ValueSP( new Value( std::string("") ));

    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "receiverHostApp"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "receiverHostApp" )] =
      ValueSP( new Value( std::string("") ));

    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "senderAppIndex"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "senderAppIndex" )] =
      ValueSP( new Value( static_cast<int>(0) ));

    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "senderHost"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "senderHost" )] =
      ValueSP( new Value( std::string("") ));

    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "senderHostApp"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "senderHostApp" )] =
      ValueSP( new Value( std::string("") ));

    // ADD THIS CLASS'S _classAndPropertyNameSet TO _classNamePropertyNameSetMap DEFINED
    // IN InteractionRoot
    get_class_name_class_and_property_name_set_sp_map()[get_hla_class_name()] = classAndPropertyNameSetSP;

    ClassAndPropertyNameSetSP allClassAndPropertyNameSetSP( new ClassAndPropertyNameSet() );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "data"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "numBytes"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "packetType"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "receiverAppIndex"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "receiverAppInterface"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "receiverHost"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "receiverHostApp"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "senderAppIndex"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "senderHost"
    );

    allClassAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot.ActionBase.NetworkPacket", "senderHostApp"
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

       } // NAMESPACE "ActionBase_p"
      } // NAMESPACE "C2WInteractionRoot_p"
     } // NAMESPACE "InteractionRoot_p"
    } // NAMESPACE "hla"
   } // NAMESPACE "cpswt"
  } // NAMESPACE "vuisis"
 } // NAMESPACE "vanderbilt"
} // NAMESPACE "edu"
