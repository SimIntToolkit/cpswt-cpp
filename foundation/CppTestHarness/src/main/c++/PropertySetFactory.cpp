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

#include "RTIForTesting.hpp"
#include "AttributeHandleSetForTesting.hpp"
#include "PropertyHandleValuePairSetForTesting.hpp"

#if __cplusplus >= 201703L
#define MultiArgTuple17
#define Tuple17 noexcept
#define throw(...) __VA_OPT__(MultiArg)##Tuple17
#endif

RTI::ParameterHandleValuePairSet *RTI::ParameterSetFactory::create(ULong count) throw (
  MemoryExhausted, ValueCountExceeded, HandleValuePairMaximumExceeded
) {
    return new PropertyHandleValuePairSetForTesting(count);
}

RTI::AttributeHandleValuePairSet *RTI::AttributeSetFactory::create(ULong count) throw (
  MemoryExhausted, ValueCountExceeded, HandleValuePairMaximumExceeded
) {
    return new PropertyHandleValuePairSetForTesting(count);
}

RTI::AttributeHandleSet* RTI::AttributeHandleSetFactory::create(ULong count) throw (
  MemoryExhausted, ValueCountExceeded
) {
    return new AttributeHandleSetTest();
}

#if __cplusplus >= 201703L
#undef MultiArgTuple17
#undef Tuple17
#undef throw
#endif