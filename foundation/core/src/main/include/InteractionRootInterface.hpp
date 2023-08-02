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

#ifndef _INTERACTION_ROOT_INTERFACE
#define _INTERACTION_ROOT_INTERFACE

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif


#ifndef CPSWT_TEST

#ifndef RTI_USES_STD_FSTREAM
#define RTI_USES_STD_FSTREAM
#endif

#if __cplusplus >= 201703L
#define MultiArgThrow17
#define Throw17 noexcept
#define throw(...) __VA_OPT__(MultiArg)##Throw17
#endif

#include <RTI.hh>
#include "fedtime.hh"

#if __cplusplus >= 201703L
#undef MultiArgThrow17
#undef Throw17
#undef throw
#endif


#endif // CPSWT_TEST


#include <string>
#include <vector>

#include <TypeMedley.hpp>

#include <ClassAndPropertyName.hpp>

#include <StringCollections.hpp>


namespace edu {
 namespace vanderbilt {
  namespace vuisis {
   namespace cpswt {
    namespace hla {

struct InteractionRootInterface {

    typedef TypeMedley Value;

    virtual int getUniqueId() = 0;

    virtual int getClassHandle() const = 0;

    virtual const std::string &getCppClassName() const = 0;

    virtual const std::string getSimpleClassName() const = 0;

    virtual const std::string &getHlaClassName() const = 0;

    virtual const ClassAndPropertyNameList getParameterNames() const = 0;

    virtual const ClassAndPropertyNameList getAllParameterNames() const = 0;

    virtual void publishInteraction(RTI::RTIambassador *rtiAmbassador) = 0;

    virtual void unpublishInteraction(RTI::RTIambassador *rtiAmbassador) = 0;

    virtual void subscribeInteraction(RTI::RTIambassador *rtiAmbassador) = 0;

    virtual void unsubscribeInteraction(RTI::RTIambassador *rtiAmbassador) = 0;

    virtual double getTime() = 0;

    virtual void setTime(double time) = 0;

    virtual void setTime(const RTIfedTime &rtiFedTime) = 0;

    virtual const Value &getParameter(
      const std::string &className, const std::string &propertyName
    ) const = 0;

    virtual const Value &getParameter( const std::string &propertyName ) const = 0;

    virtual const Value &getParameter( int propertyHandle ) const = 0;

    virtual void setParameters(const RTI::ParameterHandleValuePairSet &propertyMap) = 0;

//    virtual void setParameter(const std::string &propertyName, TypeMedley value ) = 0;

    virtual void sendInteraction(RTI::RTIambassador *rtiAmbassador, double time) = 0;

    virtual void sendInteraction(RTI::RTIambassador *rtiAmbassador) = 0;
};


    } // NAMESPACE "hla"
   } // NAMESPACE "cpswt"
  } // NAMESPACE "vuisis"
 } // NAMESPACE "vanderbilt"
} // NAMESPACE "edu"

#endif // - _INTERACTION_ROOT_INTERFACE
