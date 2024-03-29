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

#ifndef _C2WLOGGER_HPP
#define _C2WLOGGER_HPP

#include <string>

#include "StringCollections.hpp"

#include "InteractionRootInterface.hpp"
#include "ObjectRootInterface.hpp"

using ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRootInterface;
using ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRootInterface;

class C2WLogger {

public:
	virtual void init( const ArgVector &argVector ) = 0;
	virtual void addLog(const std::string &interaction, const std::string &fed, bool publish=true) = 0;
	virtual void addLog(const std::string &object, const std::string &attribute, const std::string &fed, bool publish=true) = 0;
	virtual void addLog(const std::string &federate) = 0;
	virtual void addLog( const std::string &id, const std::string &parameter, const std::string &value, const std::string &ptype, double time = 0, const std::string &level = "" ) = 0;
	virtual void addLog(const std::string &id, const InteractionRootInterface &interactionRoot, double time = 0, const std::string &level = "" ) = 0;
	virtual void addLog(const std::string &id, const ObjectRootInterface &objectRoot, double time = 0, const std::string &level = "" ) = 0;
	virtual void addLog(const std::string &federate, const std::string &info, const std::string &level, double time) = 0;
	virtual int getLogLevel(const std::string &loglevel) = 0;
};

#endif //_C2WLOGGER
