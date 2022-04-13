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

#ifndef _CLASS_AND_PROPERTY_NAME_HPP
#define _CLASS_AND_PROPERTY_NAME_HPP

#include <string>
#include <utility>
#include <boost/shared_ptr.hpp>
#include <unordered_set>
#include <list>
#include <iostream>

class ClassAndPropertyName {

private:
    static const std::string &getSeparatorChar() {
        static const std::string separatorChar(">");
        return separatorChar;
    }

    std::string _className;
    std::string _propertyName;

public:
    ClassAndPropertyName(std::string className, std::string propertyName):
            _className(std::move(className)), _propertyName(std::move(propertyName)) { }

    explicit ClassAndPropertyName(const std::string &classAndPropertyNameString) {
        size_t separatorCharPosition = classAndPropertyNameString.find(getSeparatorChar());
        if (separatorCharPosition == std::string::npos) {
            _className = classAndPropertyNameString;
            _propertyName = classAndPropertyNameString;
        } else {
            _className = classAndPropertyNameString.substr(0, separatorCharPosition);
            _propertyName = classAndPropertyNameString.substr(separatorCharPosition + 1);
        }
    }

    const std::string &getClassName() const {
        return _className;
    }

    const std::string &getPropertyName() const {
        return _propertyName;
    }

    explicit operator std::string() const {
        static std::string stringValue(_className + getSeparatorChar() + _propertyName);
        return stringValue;
    }

    size_t hashCode() const {
        static std::hash<std::string> localHash;
        return localHash(static_cast<std::string>(*this));
    }

    bool operator==(const ClassAndPropertyName &other) const {
        return _className == other._className && _propertyName == other._propertyName;
    }

    bool operator<(const ClassAndPropertyName &other) const {
        if (_className < other._className) {
            return true;
        }
        if (_className > other._className) {
            return false;
        }
        return _propertyName < other._propertyName;
    }

    bool operator>(const ClassAndPropertyName &other) const {
        if (_className > other._className) {
            return true;
        }
        if (_className < other._className) {
            return false;
        }
        return _propertyName > other._propertyName;
    }
};

template<>
struct std::hash<ClassAndPropertyName> {
    size_t operator()(const ClassAndPropertyName &classAndPropertyName) const noexcept {
        return classAndPropertyName.hashCode();
    }
};

typedef boost::shared_ptr<ClassAndPropertyName> ClassAndPropertyNameSP;
typedef std::unordered_set<ClassAndPropertyName> ClassAndPropertyNameSet;
typedef std::list<ClassAndPropertyName> ClassAndPropertyNameList;

inline std::ostream &operator<<(std::ostream &os, const ClassAndPropertyName &classAndPropertyName) {
    os << static_cast<std::string>(classAndPropertyName);
    return os;
}

#endif // _CLASS_AND_PROPERTY_NAME_HPP
