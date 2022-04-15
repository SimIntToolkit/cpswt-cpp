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

#include <boost/lexical_cast.hpp>

#include "C2WConsoleLogger.hpp"
#include "TypeMedley.hpp"

#include <iostream>
#include <cstdio>

#if __cplusplus <= 199711L
#define TIME_LOG_FORMAT "%.3f"
#else
#define TIME_LOG_FORMAT "%.3lf"
#endif


void C2WConsoleLogger::init( const ArgVector &argVector ){
	//No initialization needed for the console
}

void C2WConsoleLogger::addLog( const std::string &interaction, const std::string &fed, bool publish ) {

	std::string values;

	if ( publish ) {
		values = "'" + fed+"_pub_"+interaction + "', '" + interaction + "', '', '', '" + fed + "', ''";
	} else {
		values = "'" + interaction+"_sub_"+fed + "', '" + interaction + "', '', '', '', '" + fed + "'";
	}

	std::cout << values;
}

void C2WConsoleLogger::addLog( const std::string &object, const std::string &attribute, const std::string &fed, bool publish ) {

	std::string values;

	if ( publish ) {
		values = "'" + fed+"_pub_"+object+"_"+attribute + "', '', '" + object + "', '" + attribute + "', '" + fed + "', ''";
	} else {
		values = "'" + object+"_"+attribute+"_sub_"+fed + "', '', '" + object + "', '" + attribute + "', '', '" + fed + "'";
	}

	std::cout << values;
}

void C2WConsoleLogger::addLog( const std::string &federate ) {

	std::string values = "'" + federate + "', '', '', '', '', ''";
	std::cout << values;
}

void C2WConsoleLogger::addLog(
 const std::string &id, const std::string &parameter, const std::string &value, const std::string &ptype, double time, const std::string &level
) {

	std::string logIdString = boost::lexical_cast< std::string >( ++_logId );
	std::string levelString = level.empty() ? "''" : "'" + level + "'";

	char timeCharArray[60];
	snprintf( timeCharArray, 60, TIME_LOG_FORMAT, time );
	std::string timeString( timeCharArray );

	std::string values = "'" + id + "', " + timeString + ", '" + parameter + "', '" + value + "', '" + ptype +
	 "', " + levelString + ", '" + logIdString + "'";

	std::cout << values;
}

void C2WConsoleLogger::addLog(const std::string &id, const InteractionRootInterface &interactionRoot, double time, const std::string &level ) {

	std::string logIdString = boost::lexical_cast< std::string >( ++_logId );
	std::string levelString = level.empty() ? "''" : "'" + level + "'";

	char timeCharArray[60];
	snprintf( timeCharArray, 60, TIME_LOG_FORMAT, time );
	std::string timeString( timeCharArray );

	ClassAndPropertyNameList classAndPropertyNameList = interactionRoot.getParameterNames();
	if ( classAndPropertyNameList.empty() ) {
		std::string values = "'" + id + "', " + timeString + ", '', '', '', " + levelString +", '" + logIdString + "'";

		std::cout << values;
	}
	for(
            ClassAndPropertyNameList::iterator cplItr = classAndPropertyNameList.begin() ;
            cplItr != classAndPropertyNameList.end() ;
            ++cplItr
    ) {

		std::string parameterName( *cplItr );

		TypeMedley parameterValue = interactionRoot.getParameter( parameterName );
		std::string parameterValueString( parameterValue );
		std::string parameterTypeString( parameterValue.getTypeName() );

		if ( parameterTypeString == "std::string" ) {
			parameterTypeString = "String";
		}

		std::string values = "'" + id + "', " + timeString + ", '" + parameterName + "', '" + parameterValueString + "', '" + parameterTypeString +
		 "', " + levelString +", '" + logIdString + "'";

		std::cout << values;
	}

}

void C2WConsoleLogger::addLog(const std::string &id, const ObjectRootInterface &objectRoot, double time, const std::string &level ) {

	std::string logIdString = boost::lexical_cast< std::string >( ++_logId );

	char timeCharArray[60];
	snprintf( timeCharArray, 60, TIME_LOG_FORMAT, time );
	std::string timeString( timeCharArray );
	std::string levelString = level.empty() ? "''" : "'" + level + "'";

    ClassAndPropertyNameList classAndPropertyNameList = objectRoot.getAttributeNames();
	if ( classAndPropertyNameList.empty() ) {
		std::string values = "'" + id + "', " + timeString + ", '', '', '', " + levelString +", '" + logIdString + "'";

		std::cout << values;
	}
    for(
            ClassAndPropertyNameList::iterator cplItr = classAndPropertyNameList.begin() ;
            cplItr != classAndPropertyNameList.end() ;
            ++cplItr
    ) {

		std::string attributeName( *cplItr );

		TypeMedley attributeValue = objectRoot.getAttribute( attributeName );
		std::string attributeValueString( attributeValue );
		std::string attributeTypeString( attributeValue.getTypeName() );

		if ( attributeTypeString == "std::string" ) {
			attributeTypeString = "String";
		}

		std::string values = "'" + id + "', " + timeString + ", '" + attributeName + "', '" + attributeValueString + "', '" + attributeTypeString +
		 "', " + levelString +", '" + logIdString + "'";

		std::cout << values;
	}

}

void C2WConsoleLogger::addLog( const std::string &federate, const std::string &info, const std::string &level, double time ) {
	char timeCharArray[60];
	snprintf( timeCharArray, 60, TIME_LOG_FORMAT, time );
	std::string timeString( timeCharArray );


	std::string values = "'" + federate + "', " + timeString + ", '', '" + info + "', '', '" + level + "'";
	std::cout << values;
}

int C2WConsoleLogger::getLogLevel( const std::string &loglevel ) {

	int level = 5;

	if ( loglevel == "HIGHLY_IMPORTANT" ) {
		level = 0;
	} else if ( loglevel == "IMPORTANT" ) {
		level = 1;
	} else if ( loglevel == "NORMAL" ) {
		level = 2;
	} else if ( loglevel == "DETAILED" ) {
		level = 3;
	} else if ( loglevel == "HIGHLY_DETAILED" ) {
		level = 4;
	}

	return level;
}
