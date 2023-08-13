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

#include "TypeMedley.hpp"
#include <algorithm>

bool TypeMedley::string_to_bool(const std::string &value) {
    if (value.empty()) {
        return false;
    }
    if (hasDoubleFormat(value)) {
        return static_cast<bool>(boost::lexical_cast<double>(value));
    }

    std::string valueCopy(value);
    boost::algorithm::to_lower(valueCopy);
    return valueCopy == "true";
}


bool TypeMedley::setValue(const std::string &value) {
    try {
        switch(_dataType) {
            case BOOLEAN: {
                _value = boost::lexical_cast<std::string>(string_to_bool(value));
                break;
            }
            case CHARACTER: {
                _value = convert_to_string<short>(value);
                break;
            }
            case SHORT: {
                _value = convert_to_string<short>(value);
                break;
            }
            case INTEGER: {
                _value = convert_to_string<int>(value);
                break;
            }
            case LONG: {
                _value = convert_to_string<long>(value);
                break;
            }
            case FLOAT: {
                _value = convert_to_string<float>(value);
                break;
            }
            case DOUBLE: {
                _value = convert_to_string<double>(value);
                break;
            }
            case JSON:
            case STRING: {
                _value = value;
                break;
            }
        }
        return true;
    } catch(...) { }
    return false;
}

