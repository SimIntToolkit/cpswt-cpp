/*
 * Copyright (c) 2016, Institute for Software Integrated Systems, Vanderbilt University
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice, the following
 * two paragraphs and the author appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE VANDERBILT UNIVERSITY BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE VANDERBILT
 * UNIVERSITY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE VANDERBILT UNIVERSITY SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE VANDERBILT UNIVERSITY HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 * @author Himanshu Neema
 * @author Harmon Nine
 */

#ifndef _INTERACTION_ROOT_INTERFACE
#define _INTERACTION_ROOT_INTERFACE

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif

#ifndef RTI_USES_STD_FSTREAM
#define RTI_USES_STD_FSTREAM
#endif

#include <string>
#include <vector>
#include <RTI.hh>
#include "fedtime.hh"

#include <TypeMedley.hpp>

#include <ClassAndPropertyName.hpp>

#include <StringCollections.hpp>


namespace org {
 namespace cpswt {
  namespace hla {

struct InteractionRootInterface {

    typedef TypeMedley Value;

    virtual int getUniqueId() = 0;

    virtual int getClassHandle() const = 0;

    virtual const std::string &getCppClassName() const = 0;

    virtual const std::string &getSimpleClassName() const = 0;

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

    virtual const Value &getParameter( const std::string &propertyName ) const = 0;

    virtual const Value &getParameter( int propertyHandle ) const = 0;

    virtual void setParameters(const RTI::ParameterHandleValuePairSet &propertyMap) = 0;

//    virtual void setParameter(const std::string &propertyName, TypeMedley value ) = 0;

    virtual void sendInteraction(RTI::RTIambassador *rtiAmbassador, double time) = 0;

    virtual void sendInteraction(RTI::RTIambassador *rtiAmbassador) = 0;
};


  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"

#endif // - _INTERACTION_ROOT_INTERFACE