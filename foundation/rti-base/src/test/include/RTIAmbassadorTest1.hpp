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

#ifndef RTI_AMBASSADOR_TEST_1_HH
#define RTI_AMBASSADOR_TEST_1_HH

#include "RTIAmbassadorProxy.hpp"

#include <map>
#include <set>

class ClassAndPropertyName;

class RTIAmbassadorTest1: public RTIProxy::RTIAmbassadorProxy {

public:
    typedef std::map<std::string, RTI::InteractionClassHandle> ClassNameHandleMap;
    typedef std::map<RTI::InteractionClassHandle, std::string> ClassHandleNameMap;
    typedef std::map<ClassAndPropertyName, int> ClassAndPropertyNameHandleMap;
    typedef std::set<std::string> StringSet;

private:
    static const ClassNameHandleMap &get_class_name_handle_map_aux();
    static const ClassHandleNameMap &get_class_handle_name_map_aux();

    static int get_new_int_value() {
        static int value = 0;
        return value++;
    }
    static const ClassAndPropertyNameHandleMap &get_interaction_class_and_property_name_handle_map_aux();
    static const ClassAndPropertyNameHandleMap &get_object_class_and_property_name_handle_map_aux();

    static StringSet &get_published_interaction_class_name_set_aux() {
        static StringSet publishedInteractionClassNameSet;
        return publishedInteractionClassNameSet;
    }

    static StringSet &get_subscribed_interaction_class_name_set_aux() {
        static StringSet subscribedInteractionClassNameSet;
        return subscribedInteractionClassNameSet;
    }

public:
    static const ClassNameHandleMap &get_class_name_handle_map() {
        static const ClassNameHandleMap &classNameHandleMap = get_class_name_handle_map_aux();
        return classNameHandleMap;
    }

    static const ClassHandleNameMap &get_class_handle_name_map() {
        static const ClassHandleNameMap &classHandleNameMap = get_class_handle_name_map_aux();
        return classHandleNameMap;
    }

    static const ClassAndPropertyNameHandleMap &get_interaction_class_and_property_name_handle_map() {
        static const ClassAndPropertyNameHandleMap &classAndPropertyNameHandleMap =
          get_interaction_class_and_property_name_handle_map_aux();
        return classAndPropertyNameHandleMap;
    }

    static const ClassAndPropertyNameHandleMap &get_object_class_and_property_name_handle_map() {
        static const ClassAndPropertyNameHandleMap &classAndPropertyNameHandleMap =
          get_object_class_and_property_name_handle_map_aux();
        return classAndPropertyNameHandleMap;
    }

    static const StringSet &get_published_interaction_class_name_set() {
        return get_published_interaction_class_name_set_aux();
    }

    static const StringSet &get_subscribed_interaction_class_name_set() {
        return get_subscribed_interaction_class_name_set_aux();
    }

    static void clearPubSub() {
        get_published_interaction_class_name_set_aux().clear();
        get_subscribed_interaction_class_name_set_aux().clear();
    }

    RTI::InteractionClassHandle getInteractionClassHandle (const char *theName) throw (
      RTI::NameNotFound, RTI::FederateNotExecutionMember, RTI::ConcurrentAccessAttempted, RTI::RTIinternalError
    ) override;

    RTI::ParameterHandle getParameterHandle (const char *theName, RTI::InteractionClassHandle whichClass) throw (
      RTI::InteractionClassNotDefined,
      RTI::NameNotFound,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    ) override;

    RTI::AttributeHandle getAttributeHandle (const char *theName, RTI::ObjectClassHandle whichClass) throw (
      RTI::ObjectClassNotDefined,
      RTI::NameNotFound,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::RTIinternalError
    ) override;

    void publishInteractionClass(RTI::InteractionClassHandle theInteraction) throw (
      RTI::InteractionClassNotDefined,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    ) override;

    void subscribeInteractionClass(RTI::InteractionClassHandle theInteraction, RTI::Boolean active = RTI::RTI_TRUE)
    throw (
      RTI::InteractionClassNotDefined,
      RTI::FederateNotExecutionMember,
      RTI::ConcurrentAccessAttempted,
      RTI::SaveInProgress,
      RTI::RestoreInProgress,
      RTI::RTIinternalError
    ) override;
};

#endif  // RTI_AMBASSADOR_TEST_1_HH