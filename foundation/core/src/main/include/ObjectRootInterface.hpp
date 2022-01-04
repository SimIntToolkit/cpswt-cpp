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

#ifndef _OBJECT_ROOT_INTERFACE
#define _OBJECT_ROOT_INTERFACE

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif

#ifndef RTI_USES_STD_FSTREAM
#define RTI_USES_STD_FSTREAM
#endif

#include <string>
#include <vector>
#include <RTI.hh>

#include <TypeMedley.hpp>
#include <ClassAndPropertyName.hpp>

#include <StringCollections.hpp>


namespace org {
 namespace cpswt {
  namespace hla {

struct ObjectRootInterface {

    virtual int getUniqueId() = 0;

    virtual int getClassHandle() const = 0;

    virtual const std::string &getCppClassName() const = 0;

    virtual const std::string &getSimpleClassName() const = 0;

    virtual const std::string &getHlaClassName() const = 0;

    virtual const ClassAndPropertyNameList &getAttributeNames() const = 0;

    virtual const ClassAndPropertyNameList &getAllAttributeNames() const = 0;

    virtual void publishObject(RTI::RTIambassador *rtiAmbassador) = 0;

    virtual void unpublishObject(RTI::RTIambassador *rtiAmbassador) = 0;

    virtual void subscribeObject(RTI::RTIambassador *rtiAmbassador) = 0;

    virtual void unsubscribeObject(RTI::RTIambassador *rtiAmbassador) = 0;

    virtual double getTime() = 0;

    virtual void setTime(double time) = 0;

    virtual void setTime(const RTI::FedTime &rtiFedTime) = 0;

    virtual const TypeMedley &getAttribute( const std::string &propertyName ) const = 0;

    virtual const TypeMedley &getAttribute( int propertyHandle ) const = 0;

    virtual void setAttributes(const RTI::AttributeHandleValuePairSet &propertyMap) = 0;

    virtual void setAttribute(const std::string &propertyName, TypeMedley value ) = 0;

//    virtual RTI::AttributeHandleSet getSubscribedAttributeHandleSet() = 0;

    virtual void requestUpdate(RTI::RTIambassador *rtiAmbassador) = 0;

    virtual int getObjectHandle() = 0;

    virtual void registerObject(RTI::RTIambassador *rtiAmbassador) = 0;

    virtual void registerObject(RTI::RTIambassador *rtiAmbassador, const std::string &name) = 0;

    virtual void unregisterObject(RTI::RTIambassador *rtiAmbassador) = 0;

    virtual void updateAttributeValues(RTI::RTIambassador *rtiAmbassador, double time, bool force) = 0;

    virtual void updateAttributeValues(RTI::RTIambassador *rtiAmbassador, double time) = 0;

    virtual void updateAttributeValues(RTI::RTIambassador *rtiAmbassador, bool force) = 0;

    virtual void updateAttributeValues(RTI::RTIambassador *rtiAmbassador) = 0;
};


  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"

#endif // - _OBJECT_ROOT_INTERFACE