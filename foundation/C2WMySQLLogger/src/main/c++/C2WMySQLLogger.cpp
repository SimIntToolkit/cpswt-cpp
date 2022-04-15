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

#include <boost/thread/thread.hpp>
#include <boost/lexical_cast.hpp>

#include "C2WMySQLLogger.hpp"
#include "TypeMedley.hpp"

#include <iostream>
#include <stdio.h>

#if __cplusplus <= 199711L
#define TIME_LOG_FORMAT "%.3f"
#else
#define TIME_LOG_FORMAT "%.3lf"
#endif


void C2WMySQLLogger::ExecuteUpdate::operator()( void ) {

	if ( C2WMySQLLogger::get_singleton().getSqlStatement() == 0 ) {
		return;
	}

	try {

		C2WMySQLLogger::get_singleton().getSqlStatement()->executeUpdate( _command );

	} catch (sql::SQLException &e) {

		std::cout << "# ERR: " << e.what();
		std::cout << "( MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

	}

}

void C2WMySQLLogger::createDB( const std::string &dbName ) {
	std::string updatedDbName = dbName;
	if( updatedDbName.length() > 64 ) {
		updatedDbName = dbName.substr(64);
		std::cout << "Limited database name to 64 characters, dbName updated to: " << updatedDbName << std::endl;
	}

	try {

		std::string dbURL = "jdbc:mysql://localhost:3306/";

		// CREATE DATABASE
		_sqlConnection = _sqlDriver->connect( dbURL, _username, _password );
		ExecuteUpdate( "CREATE DATABASE " + updatedDbName )();
		_sqlConnection->close();

		// CREATE TABLES
		dbURL += updatedDbName;

		_sqlConnection = _sqlDriver->connect( dbURL, _username, _password );
		ExecuteUpdate(
		 std::string( "CREATE TABLE ExperimentInfo " ) +
		 "(id VARCHAR(100), interaction VARCHAR(60), object VARCHAR(60), attribute VARCHAR(60), Publisher VARCHAR(60), Subscriber VARCHAR(60))"
		)();
		ExecuteUpdate(
		 std::string( "CREATE TABLE SimulationData " ) +
		 "(id VARCHAR(100), time VARCHAR(60), parameter VARCHAR(60), value VARCHAR(1024), type VARCHAR(60), level VARCHAR(60), logId VARCHAR(60))"
		)();

	} catch ( sql::SQLException &sqlException ) {

		if ( _sqlConnection != 0 ) {
			try {
				_sqlConnection->close();
			} catch ( sql::SQLException &sqlException ) { /* ignore close errors */ }
			_sqlConnection = 0;
		}

	}
}

//void C2WMySQLLogger::init( const std::string &db_name, const std::string &dbURL ) {
void C2WMySQLLogger::init( const ArgVector &argVector ) {

	std::string db_name = "";
	std::string dbURL = "localhost";

	if ( argVector.size() == 1 ) {
			db_name = argVector[ 0 ] ;
	} 
	if ( argVector.size() > 1 ) {
			dbURL = argVector[ 1 ];
	}

	if ( _sqlConnection != 0 ) {
		return;
	}

	std::string updatedDbName = db_name;
	if( updatedDbName.length() > 64 ) {
		updatedDbName = db_name.substr(64);
		std::cout << "Limited database name to 64 characters, dbName updated to: " << updatedDbName << std::endl;
	}

	try {

		/* Using the Driver to create a connection */
		_sqlConnection = _sqlDriver->connect(  std::string( "tcp://" ) + dbURL, "root", "c2wt"  );
		_sqlConnection->setSchema( updatedDbName );
		_sqlStatement = _sqlConnection->createStatement();

	} catch ( sql::SQLException &sqlException ) {

		std::cout << "# ERR: " << sqlException.what();
		std::cout << " ( MySQL error code: " << sqlException.getErrorCode();
		std::cout << ", SQLState: " << sqlException.getSQLState() << " )" << std::endl;

	}

}

void C2WMySQLLogger::addLog( const std::string &interaction, const std::string &fed, bool publish ) {

	std::string values;

	if ( publish ) {
		values = "'" + fed+"_pub_"+interaction + "', '" + interaction + "', '', '', '" + fed + "', ''";
	} else {
		values = "'" + interaction+"_sub_"+fed + "', '" + interaction + "', '', '', '', '" + fed + "'";
	}

	boost::thread thread(  ExecuteUpdate( "INSERT INTO ExperimentInfo VALUES(" + values + ")" )  );
	thread.join();
}

void C2WMySQLLogger::addLog( const std::string &object, const std::string &attribute, const std::string &fed, bool publish ) {

	std::string values;

	if ( publish ) {
		values = "'" + fed+"_pub_"+object+"_"+attribute + "', '', '" + object + "', '" + attribute + "', '" + fed + "', ''";
	} else {
		values = "'" + object+"_"+attribute+"_sub_"+fed + "', '', '" + object + "', '" + attribute + "', '', '" + fed + "'";
	}

	boost::thread thread(  ExecuteUpdate( "INSERT INTO ExperimentInfo VALUES(" + values + ")" )  );
	thread.join();
}

void C2WMySQLLogger::addLog( const std::string &federate ) {

	std::string values = "'" + federate + "', '', '', '', '', ''";
	boost::thread thread(  ExecuteUpdate( "INSERT INTO ExperimentInfo VALUES(" + values + ")" )  );
	thread.join();
}

void C2WMySQLLogger::addLog(
 const std::string &id, const std::string &parameter, const std::string &value, const std::string &ptype, double time, const std::string &level
) {

	std::string logIdString = boost::lexical_cast< std::string >( ++_logId );
	std::string levelString = level.empty() ? "''" : "'" + level + "'";

	char timeCharArray[60];
	snprintf( timeCharArray, 60, TIME_LOG_FORMAT, time );
	std::string timeString( timeCharArray );

	std::string values = "'" + id + "', " + timeString + ", '" + parameter + "', '" + value + "', '" + ptype +
	 "', " + levelString + ", '" + logIdString + "'";

	boost::thread thread(  ExecuteUpdate( "INSERT INTO SimulationData VALUES(" + values + ")" )  );
	thread.join();
}

void C2WMySQLLogger::addLog( const std::string &id, const InteractionIf &interactionRoot, double time, const std::string &level ) {

	std::string logIdString = boost::lexical_cast< std::string >( ++_logId );
	std::string levelString = level.empty() ? "''" : "'" + level + "'";

	char timeCharArray[60];
	snprintf( timeCharArray, 60, TIME_LOG_FORMAT, time );
	std::string timeString( timeCharArray );

	StringVector stringVector = interactionRoot.getParameterNames();
	if ( stringVector.empty() ) {
		std::string values = "'" + id + "', " + timeString + ", '', '', '', " + levelString +", '" + logIdString + "'";

		boost::thread thread(  ExecuteUpdate( "INSERT INTO SimulationData VALUES(" + values + ")" )  );
		thread.join();
	}
	for( StringVector::iterator issItr = stringVector.begin() ; issItr != stringVector.end() ; ++issItr ) {

		std::string parameterName( *issItr );

		TypeMedley parameterValue = interactionRoot.getParameter( parameterName );
		std::string parameterValueString( parameterValue );
		std::string parameterTypeString( parameterValue.getTypeName() );

		if ( parameterTypeString == "std::string" ) {
			parameterTypeString = "String";
		}

		std::string values = "'" + id + "', " + timeString + ", '" + parameterName + "', '" + parameterValueString + "', '" + parameterTypeString +
		 "', " + levelString +", '" + logIdString + "'";

		boost::thread thread(  ExecuteUpdate( "INSERT INTO SimulationData VALUES(" + values + ")" )  );
		thread.join();
	}

}

void C2WMySQLLogger::addLog( const std::string &id, const ObjectIf &objectRoot, double time, const std::string &level ) {

	std::string logIdString = boost::lexical_cast< std::string >( ++_logId );

	char timeCharArray[60];
	snprintf( timeCharArray, 60, TIME_LOG_FORMAT, time );
	std::string timeString( timeCharArray );
	std::string levelString = level.empty() ? "''" : "'" + level + "'";

	StringVector stringVector = objectRoot.getAttributeNames();
	if ( stringVector.empty() ) {
		std::string values = "'" + id + "', " + timeString + ", '', '', '', " + levelString +", '" + logIdString + "'";

		boost::thread thread(  ExecuteUpdate( "INSERT INTO SimulationData VALUES(" + values + ")" )  );
		thread.join();
	}
	for( StringVector::iterator ossItr = stringVector.begin() ; ossItr != stringVector.end() ; ++ossItr ) {

		std::string attributeName( *ossItr );

		TypeMedley attributeValue = objectRoot.getAttribute( attributeName );
		std::string attributeValueString( attributeValue );
		std::string attributeTypeString( attributeValue.getTypeName() );

		if ( attributeTypeString == "std::string" ) {
			attributeTypeString = "String";
		}

		std::string values = "'" + id + "', " + timeString + ", '" + attributeName + "', '" + attributeValueString + "', '" + attributeTypeString +
		 "', " + levelString +", '" + logIdString + "'";

		boost::thread thread(  ExecuteUpdate( "INSERT INTO SimulationData VALUES(" + values + ")" )  );
		thread.join();
	}

}

void C2WMySQLLogger::addLog( const std::string &federate, const std::string &info, const std::string &level, double time ) {
	char timeCharArray[60];
	snprintf( timeCharArray, 60, TIME_LOG_FORMAT, time );
	std::string timeString( timeCharArray );


	std::string values = "'" + federate + "', " + timeString + ", '', '" + info + "', '', '" + level + "'";
	boost::thread thread(  ExecuteUpdate( "INSERT INTO SimulationData VALUES(" + values + ")" )  );
	thread.join();
}

int C2WMySQLLogger::getLogLevel( const std::string &loglevel ) {

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
