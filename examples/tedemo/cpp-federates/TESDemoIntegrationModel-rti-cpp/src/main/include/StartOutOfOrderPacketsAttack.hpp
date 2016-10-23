
/*
 * Copyright (c) 2008, Institute for Software Integrated Systems, Vanderbilt University
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice, the following
 * two paragraphs and the author appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE VANDERBILT UNIVERSITY BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE VANDERBILT
 * UNIVERSITY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE VANDERBILT UNIVERSITY SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE VANDERBILT UNIVERSITY HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 * @author Himanshu Neema
 * @author Harmon Nine
 */

// This code has been generated by the C2W code generator.
// Do not edit manually!

/*
 * 	NOTE:  ALL "if" STATEMENTS IN THIS CODE THAT HAD THE FORM:
 *
 *  if (condition) statement;
 *
 *	OR
 *
 *  if (condition) statement1;
 *  else           statement2;
 *
 *  HAVE BEEN CONVERTED TO THE FORMS:
 *
 *  if (condition) {
 *		statement;
 *	}
 *
 *	AND
 *
 *  if (condition) {
 *		statement1;
 *	} else {
 *		statement2;
 *	}
 *
 *	RESPECTIVELY.  THIS IS BECAUSE THE OMNET DEBUGGER APPEARS TO HAVE A PROBLEM
 *  WITH THE NON-BRACED FORMS OF THE IF STATEMENT.  *PLEASE* DO NOT CHANGE IT BACK.
 *  -- H.S.N.
 *
 */

#ifndef _StartOutOfOrderPacketsAttack_CLASS
#define _StartOutOfOrderPacketsAttack_CLASS

#include "OmnetCommand.hpp"
#include "C2WException.hpp"


class StartOutOfOrderPacketsAttack : public OmnetCommand {

public:
	typedef OmnetCommand Super;
	typedef boost::shared_ptr< StartOutOfOrderPacketsAttack > SP;

	static StringVector get_parameter_names() {
		return getDatamemberNames();
	}

	static StringVector get_all_parameter_names() {
		return getAllDatamemberNames();
	}

	StartOutOfOrderPacketsAttack( void ) { }
	
	static SP create( void ) { return SP( new StartOutOfOrderPacketsAttack ); }

private:
	
	
	static int &get_dstNetworkAddress_handle_var( void ) {
		static int dstNetworkAddress_handle;
		return dstNetworkAddress_handle;
	}
	static int &get_recordDurationInSecs_handle_var( void ) {
		static int recordDurationInSecs_handle;
		return recordDurationInSecs_handle;
	}
	static int &get_srcNetworkAddress_handle_var( void ) {
		static int srcNetworkAddress_handle;
		return srcNetworkAddress_handle;
	}
	static int &get_recordingNodeFullPath_handle_var( void ) {
		static int recordingNodeFullPath_handle;
		return recordingNodeFullPath_handle;
	}
	
public:
	
	
	static int get_dstNetworkAddress_handle( void ) { return get_dstNetworkAddress_handle_var(); }
	static int get_recordDurationInSecs_handle( void ) { return get_recordDurationInSecs_handle_var(); }
	static int get_srcNetworkAddress_handle( void ) { return get_srcNetworkAddress_handle_var(); }
	static int get_recordingNodeFullPath_handle( void ) { return get_recordingNodeFullPath_handle_var(); }
	


private:
	static int &getHandle( void ) {
		static int handle;
		return handle;
	}

public:
	static int get_handle( void ) { return getHandle(); }
	static std::string get_class_name( void ) { return "StartOutOfOrderPacketsAttack"; }

private:
	static StringVector &getDatamemberNames( void ) {
		static StringVector datamemberNames;
		return datamemberNames;
	}

	static StringVector &getAllDatamemberNames( void ) {
		static StringVector allDatamemberNames;
		return allDatamemberNames;
	}



private:

	static InteractionRoot::SP factory( void ) {
		return InteractionRoot::SP( new StartOutOfOrderPacketsAttack() );
	}


	static std::string &getInitErrorMessage( void ) {
		static std::string initErrorMessage( "Error:  StartOutOfOrderPacketsAttack:  could not initialize:  " );
		return initErrorMessage;
	}

protected:
	static void init( RTI::RTIambassador *rti );
	
private:
	static bool &getIsPublished( void ) {
		static bool isPublished = false;
		return isPublished;
	}
	
	static std::string &getPublishErrorMessage( void ) {
		static std::string publishErrorMessage = "Error:  StartOutOfOrderPacketsAttack:  could not publish:  ";
		return publishErrorMessage;
	}
	
public:
	static void publish( RTI::RTIambassador *rti );
	
private:
	static std::string &getUnpublishErrorMessage( void ) {
		static std::string unpublishErrorMessage = "Error:  StartOutOfOrderPacketsAttack:  could not unpublish:  ";
		return unpublishErrorMessage;
	}

public:
	static void unpublish( RTI::RTIambassador *rti );

private:
	static bool &getIsSubscribed( void ) {
		static bool isSubscribed = false;
		return isSubscribed;
	}
	static std::string &getSubscribeErrorMessage( void ) {
		static std::string subscribedErrorMessage = "Error:  StartOutOfOrderPacketsAttack:  could not subscribe:  ";
		return subscribedErrorMessage;
	}

public:
	static void subscribe( RTI::RTIambassador *rti );
		
private:
	static std::string getUnsubscribeErrorMessage( void ) {
		static std::string unsubscribeErrorMessage = "Error:  StartOutOfOrderPacketsAttack:  could not unsubscribe:  ";
		return unsubscribeErrorMessage;
	}
	
public:
	static void unsubscribe( RTI::RTIambassador *rti );
	
	static bool static_init( void );
	
	static bool match( int handle ) { return handle == get_handle(); }

	virtual int getClassHandle( void ) const { return get_handle(); }
	virtual std::string getClassName( void ) const { return get_class_name(); }
	virtual StringVector getParameterNames( void ) const { return get_parameter_names(); }
	virtual StringVector getAllParameterNames( void ) const { return get_all_parameter_names(); }

	virtual void publishInteraction( RTI::RTIambassador *rti ) { publish( rti ); }
	virtual void subscribeInteraction( RTI::RTIambassador *rti ) { subscribe( rti ); }

	virtual InteractionRoot::SP clone( void ) {
		return InteractionRoot::SP(  new StartOutOfOrderPacketsAttack( *this )  );
	}







private:
	
	
	std::string _dstNetworkAddress;
	
	double _recordDurationInSecs;
	
	std::string _srcNetworkAddress;
	
	std::string _recordingNodeFullPath;
	
public:
		
	void set_dstNetworkAddress( const std::string & dstNetworkAddress ) { _dstNetworkAddress = dstNetworkAddress; }
	const std::string & get_dstNetworkAddress( void ) const { return _dstNetworkAddress; }
	
	void set_recordDurationInSecs( double recordDurationInSecs ) { _recordDurationInSecs = recordDurationInSecs; }
	double get_recordDurationInSecs( void ) const { return _recordDurationInSecs; }
	
	void set_srcNetworkAddress( const std::string & srcNetworkAddress ) { _srcNetworkAddress = srcNetworkAddress; }
	const std::string & get_srcNetworkAddress( void ) const { return _srcNetworkAddress; }
	
	void set_recordingNodeFullPath( const std::string & recordingNodeFullPath ) { _recordingNodeFullPath = recordingNodeFullPath; }
	const std::string & get_recordingNodeFullPath( void ) const { return _recordingNodeFullPath; }
	


	StartOutOfOrderPacketsAttack( const RTI::ParameterHandleValuePairSet &datamemberMap ) : Super( datamemberMap ) { }
	
	StartOutOfOrderPacketsAttack( const RTI::ParameterHandleValuePairSet &datamemberMap, const RTIfedTime &logicalTime ) : Super( datamemberMap, logicalTime ) { }
	
	
public:
	TypeMedley getParameter( const std::string &datamemberName ) const {
		
		
		if ( "dstNetworkAddress" == datamemberName ) {
			return TypeMedley( get_dstNetworkAddress() );
		}
		else if ( "recordDurationInSecs" == datamemberName ) {
			return TypeMedley( get_recordDurationInSecs() );
		}
		else if ( "srcNetworkAddress" == datamemberName ) {
			return TypeMedley( get_srcNetworkAddress() );
		}
		else if ( "recordingNodeFullPath" == datamemberName ) {
			return TypeMedley( get_recordingNodeFullPath() );
		} else {
			return Super::getParameter( datamemberName );
		}
	}
	
	TypeMedley getParameter( int datamemberHandle ) const {
		
		
		if ( get_dstNetworkAddress_handle() == datamemberHandle ) {
			return TypeMedley( get_dstNetworkAddress() );
		}
		else if ( get_recordDurationInSecs_handle() == datamemberHandle ) {
			return TypeMedley( get_recordDurationInSecs() );
		}
		else if ( get_srcNetworkAddress_handle() == datamemberHandle ) {
			return TypeMedley( get_srcNetworkAddress() );
		}
		else if ( get_recordingNodeFullPath_handle() == datamemberHandle ) {
			return TypeMedley( get_recordingNodeFullPath() );
		} else {
			return Super::getParameter( datamemberHandle );
		}
	}

protected:
	virtual bool setParameterAux( int param_handle, const std::string &val ) {
		bool retval = true;		
		
		
		if ( param_handle == get_dstNetworkAddress_handle() ) {
			set_dstNetworkAddress(  TypeMedley( val )  );
		}
		else if ( param_handle == get_recordDurationInSecs_handle() ) {
			set_recordDurationInSecs(  TypeMedley( val )  );
		}
		else if ( param_handle == get_srcNetworkAddress_handle() ) {
			set_srcNetworkAddress(  TypeMedley( val )  );
		}
		else if ( param_handle == get_recordingNodeFullPath_handle() ) {
			set_recordingNodeFullPath(  TypeMedley( val )  );
		} else {
			retval = Super::setParameterAux( param_handle, val );
		}
		return retval;
	}
	
	virtual bool setParameterAux( const std::string &datamemberName, const std::string &val ) {
		bool retval = true;
		
		
		if ( "dstNetworkAddress" == datamemberName ) {
			set_dstNetworkAddress(  TypeMedley( val )  );
		}
		else if ( "recordDurationInSecs" == datamemberName ) {
			set_recordDurationInSecs(  TypeMedley( val )  );
		}
		else if ( "srcNetworkAddress" == datamemberName ) {
			set_srcNetworkAddress(  TypeMedley( val )  );
		}
		else if ( "recordingNodeFullPath" == datamemberName ) {
			set_recordingNodeFullPath(  TypeMedley( val )  );
		} else {
			retval = Super::setParameterAux( datamemberName, val );
		}
		
		return retval;
	}
	
	virtual bool setParameterAux( const std::string &datamemberName, const TypeMedley &val ) {
		bool retval = true;
		
		
		if ( "dstNetworkAddress" == datamemberName ) {\
			set_dstNetworkAddress( val );
		}
		else if ( "recordDurationInSecs" == datamemberName ) {\
			set_recordDurationInSecs( val );
		}
		else if ( "srcNetworkAddress" == datamemberName ) {\
			set_srcNetworkAddress( val );
		}
		else if ( "recordingNodeFullPath" == datamemberName ) {\
			set_recordingNodeFullPath( val );
		} else {
			retval = Super::setParameterAux( datamemberName, val );
		}
		
		return retval;
	}

	virtual ParameterHandleValuePairSetSP createDatamemberHandleValuePairSet( RTI::ULong count );

	virtual ParameterHandleValuePairSetSP createDatamemberHandleValuePairSet( ) {
		return createDatamemberHandleValuePairSet( 0 );
	}
	
	
};

typedef StartOutOfOrderPacketsAttack::SP StartOutOfOrderPacketsAttackSP;

static bool call_StartOutOfOrderPacketsAttack_static_init = StartOutOfOrderPacketsAttack::static_init();

std::ostream &operator<<( std::ostream &os, StartOutOfOrderPacketsAttack::SP entitySP );
std::ostream &operator<<( std::ostream &os, const StartOutOfOrderPacketsAttack &entity );
#endif
