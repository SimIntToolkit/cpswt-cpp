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

#ifndef FedTimeTest_h
#define FedTimeTest_h

#include <sys/types.h>
#include <string.h>
#include <iostream>

class RTI_EXPORT_FEDTIME RTIfedTime : public RTI::FedTime {
//-----------------------------------------------------------------
// Constructors and Destructors
//-----------------------------------------------------------------
public:
  RTIfedTime();
  RTIfedTime(const RTI::Double&);
  RTIfedTime(const RTI::FedTime&);
  RTIfedTime(const RTIfedTime&);
  virtual ~RTIfedTime();

//-----------------------------------------------------------------
// Overloaded functions from RTI::FedTime
//-----------------------------------------------------------------
public:
  virtual void                setZero();
  virtual RTI::Boolean        isZero();
  virtual void                setEpsilon();
  virtual void                setPositiveInfinity();
  virtual RTI::Boolean        isPositiveInfinity();
  virtual int                 encodedLength() const;
  virtual void                encode(char *buff) const;
  virtual int                 getPrintableLength() const;
  virtual void                getPrintableString(char*);

//-----------------------------------------------------------------
// Overloaded operators from RTI::FedTime
//-----------------------------------------------------------------
public:
  virtual RTI::FedTime& operator+= (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator-= (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::Boolean operator<= (const RTI::FedTime&) const
    throw (RTI::InvalidFederationTime);

  virtual RTI::Boolean operator< (const RTI::FedTime&) const
    throw (RTI::InvalidFederationTime);

   virtual RTI::Boolean operator>= (const RTI::FedTime&) const
    throw (RTI::InvalidFederationTime);

  virtual RTI::Boolean operator> (const RTI::FedTime&) const
    throw (RTI::InvalidFederationTime);

  virtual RTI::Boolean operator== (const RTI::FedTime&) const
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator= (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

//-----------------------------------------------------------------
// Implementation functions
//-----------------------------------------------------------------
public:
  virtual RTI::Double         getTime() const;

//-----------------------------------------------------------------
// Implementation operators
//-----------------------------------------------------------------
  virtual RTI::Boolean operator== (const RTI::Double&) const
    throw (RTI::InvalidFederationTime);

  virtual RTI::Boolean operator!= (const RTI::FedTime&) const
    throw (RTI::InvalidFederationTime);

  virtual RTI::Boolean operator!= (const RTI::Double&) const
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator= (const RTIfedTime&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator= (const RTI::Double&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator*= (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator/= (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator+= (const RTI::Double&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator-= (const RTI::Double&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator*= (const RTI::Double&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator/= (const RTI::Double&)
    throw (RTI::InvalidFederationTime);

  virtual RTIfedTime operator+ (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

  virtual RTIfedTime operator+ (const RTI::Double&)
    throw (RTI::InvalidFederationTime);

  virtual RTIfedTime operator- (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

  virtual RTIfedTime operator- (const RTI::Double&)
    throw (RTI::InvalidFederationTime);

  virtual RTIfedTime operator* (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

  virtual RTIfedTime operator* (const RTI::Double&)
    throw (RTI::InvalidFederationTime);

  virtual RTIfedTime operator/ (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

  virtual RTIfedTime operator/ (const RTI::Double&)
    throw (RTI::InvalidFederationTime);

//-----------------------------------------------------------------
// Implementation friends
//-----------------------------------------------------------------
public:
  //
  // RTI_STD was added for the RTI 1.3NG to allow the use of the Standard C++
  // ostream or to use the legacy ostream.  The issue concerns whether ostream
  // is in the global namespace or in namespace std.
  //
  friend RTI_STD::ostream RTI_EXPORT & operator<< (RTI_STD::ostream&, const RTI::FedTime&);

//-----------------------------------------------------------------
// Implementation member variables
//-----------------------------------------------------------------
private:
  RTI::Double                 _fedTime;
  RTI::Double                 _zero;
  RTI::Double                 _epsilon;
  RTI::Double                 _positiveInfinity;
};

//-----------------------------------------------------------------
// Global operators
//-----------------------------------------------------------------

RTIfedTime operator+ (const RTI::Double&, const RTI::FedTime&);
RTIfedTime operator- (const RTI::Double&, const RTI::FedTime&);
RTIfedTime operator* (const RTI::Double&, const RTI::FedTime&);
RTIfedTime operator/ (const RTI::Double&, const RTI::FedTime&);

#endif
