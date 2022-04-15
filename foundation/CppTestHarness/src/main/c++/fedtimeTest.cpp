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

#include "RTITest.hh"
#include <limits>


RTI::FedTime::~FedTime() { }

RTIfedTime::RTIfedTime() :
  _fedTime(0), _zero(0), _epsilon(0.001), _positiveInfinity(std::numeric_limits<RTI::Double>::infinity()) { }

RTIfedTime::RTIfedTime(const RTI::Double &timeValue) :
  _fedTime(timeValue), _zero(0), _epsilon(0.001), _positiveInfinity(std::numeric_limits<RTI::Double>::infinity()) { }

RTIfedTime::RTIfedTime(const RTI::FedTime &other) :
  _zero(0), _epsilon(0.001), _positiveInfinity(std::numeric_limits<RTI::Double>::infinity()) {
    RTIfedTime const *rtiFedTimePtr = dynamic_cast<RTIfedTime const *>(&other);
    _fedTime = rtiFedTimePtr == nullptr ? 0 : rtiFedTimePtr->_fedTime;
}

RTIfedTime::RTIfedTime(const RTIfedTime &other) :
  _zero(0), _epsilon(0.001), _positiveInfinity(std::numeric_limits<RTI::Double>::infinity()) {
    _fedTime = other._fedTime;
}

RTIfedTime::~RTIfedTime() { }

//-----------------------------------------------------------------
// Overloaded functions from RTI::FedTime
//-----------------------------------------------------------------
void RTIfedTime::setZero() {
    _fedTime = _zero;
}

RTI::Boolean RTIfedTime::isZero() {
    return _fedTime == _zero ? RTI::RTI_TRUE : RTI::RTI_FALSE;
}

void RTIfedTime::setEpsilon() {
    _fedTime = _epsilon;
}

void RTIfedTime::setPositiveInfinity() {
    _fedTime = _positiveInfinity;
}

RTI::Boolean RTIfedTime::isPositiveInfinity() {
    return _fedTime == _positiveInfinity ? RTI::RTI_TRUE : RTI::RTI_FALSE;
}

int RTIfedTime::encodedLength() const {
    return 0;
}

void RTIfedTime::encode(char *buff) const { }

int RTIfedTime::getPrintableLength() const {
    return 0;
}

void RTIfedTime::getPrintableString(char*) { }

//-----------------------------------------------------------------
// Overloaded operators from RTI::FedTime
//-----------------------------------------------------------------
RTI::FedTime& RTIfedTime::operator+= (const RTI::FedTime &other) throw (RTI::InvalidFederationTime) {
    RTIfedTime const *rtiFedTimePtr = dynamic_cast<RTIfedTime const *>(&other);
    if (rtiFedTimePtr == nullptr) {
        return *this;
    }
    _fedTime += rtiFedTimePtr->_fedTime;
    return *this;
}

RTI::FedTime& RTIfedTime::operator-= (const RTI::FedTime &other) throw (RTI::InvalidFederationTime) {
    RTIfedTime const *rtiFedTimePtr = dynamic_cast<RTIfedTime const *>(&other);
    if (rtiFedTimePtr == nullptr) {
        return *this;
    }
    _fedTime -= rtiFedTimePtr->_fedTime;
    return *this;
}

RTI::Boolean RTIfedTime::operator<= (const RTI::FedTime &other) const throw (RTI::InvalidFederationTime) {
    RTIfedTime const *rtiFedTimePtr = dynamic_cast<RTIfedTime const *>(&other);
    return rtiFedTimePtr == nullptr ? RTI::RTI_FALSE : static_cast<RTI::Boolean>(_fedTime <= rtiFedTimePtr->_fedTime);
}

RTI::Boolean RTIfedTime::operator< (const RTI::FedTime &other) const throw (RTI::InvalidFederationTime) {
    RTIfedTime const *rtiFedTimePtr = dynamic_cast<RTIfedTime const *>(&other);
    return rtiFedTimePtr == nullptr ? RTI::RTI_FALSE : static_cast<RTI::Boolean>(_fedTime < rtiFedTimePtr->_fedTime);
}

RTI::Boolean RTIfedTime::operator>= (const RTI::FedTime &other) const throw (RTI::InvalidFederationTime) {
    RTIfedTime const *rtiFedTimePtr = dynamic_cast<RTIfedTime const *>(&other);
    return rtiFedTimePtr == nullptr ? RTI::RTI_FALSE : static_cast<RTI::Boolean>(_fedTime >= rtiFedTimePtr->_fedTime);
}

RTI::Boolean RTIfedTime::operator> (const RTI::FedTime &other) const throw (RTI::InvalidFederationTime) {
    RTIfedTime const *rtiFedTimePtr = dynamic_cast<RTIfedTime const *>(&other);
    return rtiFedTimePtr == nullptr ? RTI::RTI_FALSE : static_cast<RTI::Boolean>(_fedTime > rtiFedTimePtr->_fedTime);
}

RTI::Boolean RTIfedTime::operator== (const RTI::FedTime &other) const throw (RTI::InvalidFederationTime) {
    RTIfedTime const *rtiFedTimePtr = dynamic_cast<RTIfedTime const *>(&other);
    return rtiFedTimePtr == nullptr ? RTI::RTI_FALSE : static_cast<RTI::Boolean>(_fedTime == rtiFedTimePtr->_fedTime);
}

RTI::FedTime& RTIfedTime::operator= (const RTI::FedTime &other) throw (RTI::InvalidFederationTime) {
    RTIfedTime const *rtiFedTimePtr = dynamic_cast<RTIfedTime const *>(&other);
    if (rtiFedTimePtr != nullptr) {
        _fedTime = rtiFedTimePtr->_fedTime;
    }
    return *this;
}

//-----------------------------------------------------------------
// Implementation functions
//-----------------------------------------------------------------
RTI::Double RTIfedTime::getTime() const {
    return _fedTime;
}

//-----------------------------------------------------------------
// Implementation operators
//-----------------------------------------------------------------
RTI::Boolean RTIfedTime::operator== (const RTI::Double &value) const throw (RTI::InvalidFederationTime) {
    return static_cast<RTI::Boolean>(_fedTime == value);
}

RTI::Boolean RTIfedTime::operator!=(const RTI::FedTime &other) const throw (RTI::InvalidFederationTime) {
    RTIfedTime const *rtiFedTimePtr = dynamic_cast<RTIfedTime const *>(&other);
    return rtiFedTimePtr == nullptr ? RTI::RTI_FALSE : static_cast<RTI::Boolean>(_fedTime != rtiFedTimePtr->_fedTime);
}

RTI::Boolean RTIfedTime::operator!= (const RTI::Double &value) const throw (RTI::InvalidFederationTime) {
    return static_cast<RTI::Boolean>(_fedTime != value);
}

RTI::FedTime& RTIfedTime::operator= (const RTIfedTime &other) throw (RTI::InvalidFederationTime) {
    _fedTime = other._fedTime;
    return *this;
}

RTI::FedTime& RTIfedTime::operator= (const RTI::Double &value) throw (RTI::InvalidFederationTime) {
    _fedTime = value;
    return *this;
}

RTI::FedTime& RTIfedTime::operator*= (const RTI::FedTime &other) throw (RTI::InvalidFederationTime) {
    RTIfedTime const *rtiFedTimePtr = dynamic_cast<RTIfedTime const *>(&other);
    if (rtiFedTimePtr != nullptr) {
        _fedTime *= rtiFedTimePtr->_fedTime;
    }
    return *this;
}

RTI::FedTime& RTIfedTime::operator/= (const RTI::FedTime &other) throw (RTI::InvalidFederationTime) {
    RTIfedTime const *rtiFedTimePtr = dynamic_cast<RTIfedTime const *>(&other);
    if (rtiFedTimePtr != nullptr) {
        _fedTime /= rtiFedTimePtr->_fedTime;
    }
    return *this;
}

RTI::FedTime& RTIfedTime::operator+= (const RTI::Double &value) throw (RTI::InvalidFederationTime) {
    _fedTime += value;
    return *this;
}

RTI::FedTime& RTIfedTime::operator-= (const RTI::Double &value) throw (RTI::InvalidFederationTime) {
    _fedTime -= value;
    return *this;
}

RTI::FedTime& RTIfedTime::operator*= (const RTI::Double &value) throw (RTI::InvalidFederationTime) {
    _fedTime *= value;
    return *this;
}

RTI::FedTime& RTIfedTime::operator/= (const RTI::Double &value) throw (RTI::InvalidFederationTime) {
    _fedTime /= value;
    return *this;
}

RTIfedTime RTIfedTime::operator+ (const RTI::FedTime &other) throw (RTI::InvalidFederationTime) {
    RTIfedTime copy(*this);
    RTIfedTime const *rtiFedTimePtr = dynamic_cast<RTIfedTime const *>(&other);
    if (rtiFedTimePtr != nullptr) {
        copy._fedTime /= rtiFedTimePtr->_fedTime;
    }
    return copy;
}

RTIfedTime RTIfedTime::operator+ (const RTI::Double &value) throw (RTI::InvalidFederationTime) {
    RTIfedTime copy(*this);
    copy._fedTime += value;
    return copy;
}

RTIfedTime RTIfedTime::operator- (const RTI::FedTime &other) throw (RTI::InvalidFederationTime) {
    RTIfedTime copy(*this);
    RTIfedTime const *rtiFedTimePtr = dynamic_cast<RTIfedTime const *>(&other);
    if (rtiFedTimePtr != nullptr) {
        copy._fedTime -= rtiFedTimePtr->_fedTime;
    }
    return copy;
}

RTIfedTime RTIfedTime::operator- (const RTI::Double &value) throw (RTI::InvalidFederationTime) {
    RTIfedTime copy(*this);
    copy._fedTime -= value;
    return copy;
}

RTIfedTime RTIfedTime::operator* (const RTI::FedTime &other) throw (RTI::InvalidFederationTime) {
    RTIfedTime copy(*this);
    RTIfedTime const *rtiFedTimePtr = dynamic_cast<RTIfedTime const *>(&other);
    if (rtiFedTimePtr != nullptr) {
        copy._fedTime *= rtiFedTimePtr->_fedTime;
    }
    return copy;
}

RTIfedTime RTIfedTime::operator* (const RTI::Double &value) throw (RTI::InvalidFederationTime) {
    RTIfedTime copy(*this);
    copy._fedTime *= value;
    return copy;
}

RTIfedTime RTIfedTime::operator/ (const RTI::FedTime &other) throw (RTI::InvalidFederationTime) {
    RTIfedTime copy(*this);
    RTIfedTime const *rtiFedTimePtr = dynamic_cast<RTIfedTime const *>(&other);
    if (rtiFedTimePtr != nullptr) {
        copy._fedTime /= rtiFedTimePtr->_fedTime;
    }
    return copy;
}

RTIfedTime RTIfedTime::operator/ (const RTI::Double &value) throw (RTI::InvalidFederationTime) {
    RTIfedTime copy(*this);
    copy._fedTime /= value;
    return copy;
}

//-----------------------------------------------------------------
// Implementation friends
//-----------------------------------------------------------------
RTI_STD::ostream &operator<< (RTI_STD::ostream &os, const RTI::FedTime &fedTime) {
    RTIfedTime const *rtiFedTimePtr = dynamic_cast<RTIfedTime const *>(&fedTime);
    return os << (rtiFedTimePtr == nullptr ? -1 : rtiFedTimePtr->_fedTime);
}
