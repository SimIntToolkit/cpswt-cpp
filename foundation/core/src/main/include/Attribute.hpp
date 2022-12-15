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

#ifndef CPSWT_CPP_ATTRIBUTE_HPP
#define CPSWT_CPP_ATTRIBUTE_HPP

#include "TypeMedley.hpp"

//-----------------------------------------------------
// Attribute CLASS -- USED BY ObjectRoot AND SUBCLASSES
//-----------------------------------------------------
class Attribute: public TypeMedley {
private:
    std::string _oldValue;
    bool _oldValueInit;
    double _time;

public:
    explicit Attribute(bool value) : TypeMedley(value), _oldValueInit(false), _time(-1) { }
    explicit Attribute(char value) : TypeMedley(value), _oldValueInit(false), _time(-1) { }
    explicit Attribute(short value) : TypeMedley(value), _oldValueInit(false), _time(-1) { }
    explicit Attribute(int value) : TypeMedley(value), _oldValueInit(false), _time(-1) { }
    explicit Attribute(long value) : TypeMedley(value), _oldValueInit(false), _time(-1) { }
    explicit Attribute(float value) : TypeMedley(value), _oldValueInit(false), _time(-1) { }
    explicit Attribute(double value) : TypeMedley(value), _oldValueInit(false), _time(-1) { }
    explicit Attribute(const std::string &value) : TypeMedley(value), _oldValueInit(false), _time(-1) { }

    using TypeMedley::setValue;

    bool setValue(const Attribute &other) {
        return TypeMedley::setValue(static_cast<const TypeMedley &>(other));
    }

    double getTime() const {
        return _time;
    }
    void setTime(double time) {
        _time = time;
    }

    void setHasBeenUpdated() {
        _oldValue = _value;
        _oldValueInit = true;
    }

    bool getShouldBeUpdated(bool force) const {
        return force || !_oldValueInit || _oldValue != _value;
    }
    void setShouldBeUpdated(bool shouldBeUpdated) {
        _oldValueInit = !shouldBeUpdated;
    }
};

typedef boost::shared_ptr<Attribute> AttributeSP;

//--------------------
// END Attribute CLASS
//--------------------

#endif //CPSWT_CPP_ATTRIBUTE_HPP
