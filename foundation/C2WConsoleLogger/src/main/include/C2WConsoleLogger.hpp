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

#ifndef _C2WCONSOLELOGGER_HPP
#define _C2WCONSOLELOGGER_HPP

#include <string>
#include <vector>

#include "C2WLogger.hpp"


class C2WConsoleLogger : public C2WLogger {

private:
	int _logId;

	C2WConsoleLogger( void ) : _logId( -1 ){}

public:
	
	static C2WConsoleLogger &get_singleton( void ) {
		static C2WConsoleLogger c2wLogger;
		return c2wLogger;
	}

	void init( const ArgVector &argVector );
	void addLog(const std::string &interaction, const std::string &fed, bool publish=true);
 	void addLog(const std::string &object, const std::string &attribute, const std::string &fed, bool publish=true);
	void addLog(const std::string &federate);
	void addLog( const std::string &id, const std::string &parameter, const std::string &value, const std::string &ptype, double time = 0, const std::string &level = "" );
	void addLog(const std::string &id, const InteractionRootInterface &interactionRoot, double time = 0, const std::string &level = "" );
	void addLog(const std::string &id, const ObjectRootInterface &objectRoot, double time = 0, const std::string &level = "" );
	void addLog(const std::string &federate, const std::string &info, const std::string &level, double time);
	int getLogLevel(const std::string &loglevel);
};

#endif //_C2WCONSOLELOGGER_HPP
