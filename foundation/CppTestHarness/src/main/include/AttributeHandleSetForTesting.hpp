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

#ifndef _ATTRIBUTE_HANDLE_SET_TEST
#define _ATTRIBUTE_HANDLE_SET_TEST

#include <set>
#include "RTIForTesting.hpp"

#if __cplusplus >= 201703L
#define throw(x, ...)
#endif

class AttributeHandleSetTest: public RTI::AttributeHandleSet {

public:
    typedef std::set<RTI::AttributeHandle> StdAttributeHandleSet;
private:
    StdAttributeHandleSet attributeHandleSet;

public:
    RTI::ULong size() const override {
        return attributeHandleSet.size();
    }

    RTI::AttributeHandle getHandle(RTI::ULong index) const throw (RTI::ArrayIndexOutOfBounds) override {
        if (index >= size()) {
            return static_cast<RTI::AttributeHandle>(0);
        }

        int ix = 0;
        StdAttributeHandleSet::const_iterator sasCit = attributeHandleSet.begin();
        while(ix <= index) {
            ++sasCit;
            ++ix;
        }

        return static_cast<RTI::AttributeHandle>(*sasCit);
    }

    void add(RTI::AttributeHandle attributeHandle) throw (
      RTI::ArrayIndexOutOfBounds, RTI::AttributeNotDefined
    ) override {
        attributeHandleSet.insert(attributeHandle);
    }

    void remove(RTI::AttributeHandle attributeHandle) throw (RTI::AttributeNotDefined) override {
        attributeHandleSet.erase(attributeHandle);
    }

    void empty() override {
        attributeHandleSet.clear();
    }

    RTI::Boolean isEmpty() const override {
        return attributeHandleSet.empty() ? RTI::RTI_TRUE : RTI::RTI_FALSE;
    }

    RTI::Boolean isMember(RTI::AttributeHandle attributeHandle) const override {
        StdAttributeHandleSet::const_iterator sasCit = attributeHandleSet.find(attributeHandle);
        return sasCit == attributeHandleSet.end() ? RTI::RTI_FALSE : RTI::RTI_TRUE;
    }
};

#if __cplusplus >= 201703L
#undef throw
#endif

#endif // _ATTRIBUTE_HANDLE_SET_TEST
