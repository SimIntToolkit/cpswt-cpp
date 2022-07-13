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

#include "InteractionRoot_p/C2WInteractionRoot.hpp"
namespace org {
 namespace cpswt {
  namespace hla {
   namespace InteractionRoot_p {

bool C2WInteractionRoot::is_federate_sequence(const std::string &federateSequence) {
    Json::Value jsonArray(Json::arrayValue);

    std::istringstream jsonInputStream( federateSequence );
    try {
        jsonInputStream >> jsonArray;
    } catch(...) {
        return false;
    }

    int jsonArrayLength = jsonArray.size();
    for(int ix = 0 ; ix < jsonArrayLength ; ++ix) {
        if (!jsonArray[ix].isString()) {
            return false;
        }
    }
    return true;
}

void C2WInteractionRoot::update_federate_sequence_aux(
  ::org::cpswt::hla::InteractionRoot &interactionRoot, const std::string &federateId
) {
    if (::org::cpswt::hla::InteractionRoot::get_federate_appended_to_federate_sequence(interactionRoot)) {
        return;
    }
    ::org::cpswt::hla::InteractionRoot::set_federate_appended_to_federate_sequence(interactionRoot);

    std::string federateSequence = interactionRoot.getParameter("federateSequence").asString();

    Json::Value jsonArray(Json::arrayValue);
    if (  is_federate_sequence( federateSequence )  ) {
        std::istringstream jsonInputStream( federateSequence );
        jsonInputStream >> jsonArray;
    }

    jsonArray.append( federateId );

    Json::StreamWriterBuilder streamWriterBuilder;
    streamWriterBuilder["commentStyle"] = "None";
    std::unique_ptr<Json::StreamWriter> streamWriterUPtr(streamWriterBuilder.newStreamWriter());
    std::ostringstream stringOutputStream;
    streamWriterUPtr->write(jsonArray, &stringOutputStream);

    interactionRoot.setParameter("federateSequence", stringOutputStream.str());
}

C2WInteractionRoot::StringList C2WInteractionRoot::get_federate_sequence_list_aux(const ::org::cpswt::hla::InteractionRoot &interactionRoot) {
    StringList retval;

    const std::string federateSequence = interactionRoot.getParameter("federateSequence").asString();

    if (  is_federate_sequence( federateSequence )  ) {
        Json::Value jsonArray(Json::arrayValue);

        std::istringstream jsonInputStream( federateSequence );
        jsonInputStream >> jsonArray;

        for(Json::Value::const_iterator jsaCit = jsonArray.begin() ; jsaCit != jsonArray.end() ; ++jsaCit) {
            retval.push_back( jsaCit->asString() );
        }
    }

    return retval;
}

bool C2WInteractionRoot::static_init_var = C2WInteractionRoot::static_init();

bool C2WInteractionRoot::static_init() {
    BOOST_LOG_SEV(get_logger(), info) << "Class \"::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot\" loaded.";

    // ADD THIS CLASS TO THE _classNameSet DEFINED IN InteractionRoot
    get_hla_class_name_set().insert(get_hla_class_name());

    InteractionRoot::NoInstanceInit noInstanceInit;
    SP instanceSP = SP( new C2WInteractionRoot(noInstanceInit) );
    get_hla_class_name_instance_sp_map()[get_hla_class_name()] = instanceSP;

    ClassAndPropertyNameSetSP classAndPropertyNameSetSP( new ClassAndPropertyNameSet() );
    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot", "actualLogicalGenerationTime"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot", "actualLogicalGenerationTime" )] =
      ValueSP( new Value( static_cast<double>(0) ));
    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot", "federateFilter"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot", "federateFilter" )] =
      ValueSP( new Value( std::string("") ));
    classAndPropertyNameSetSP->emplace(
        "InteractionRoot.C2WInteractionRoot", "federateSequence"
    );

    get_class_and_property_name_initial_value_sp_map()[ClassAndPropertyName( "InteractionRoot.C2WInteractionRoot", "federateSequence" )] =
      ValueSP( new Value( std::string("[]") ));

    // ADD THIS CLASS'S _classAndPropertyNameSet TO _classNamePropertyNameSetMap DEFINED
    // IN InteractionRoot
    get_class_name_class_and_property_name_set_sp_map()[get_hla_class_name()] = classAndPropertyNameSetSP;

    ClassAndPropertyNameSetSP allClassAndPropertyNameSetSP( new ClassAndPropertyNameSet() );

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

   } // NAMESPACE "InteractionRoot_p"
  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"
