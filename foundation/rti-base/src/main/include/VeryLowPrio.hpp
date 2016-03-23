
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

#ifndef _VeryLowPrio_CLASS
#define _VeryLowPrio_CLASS

#include "SimLog.hpp"
#include "C2WException.hpp"


class VeryLowPrio : public SimLog {

public:
	typedef SimLog Super;
	typedef boost::shared_ptr< VeryLowPrio > SP;

	static StringVector get_parameter_names() {
		return getDatamemberNames();
	}

	static StringVector get_all_parameter_names() {
		return getAllDatamemberNames();
	}

	VeryLowPrio( void ) { }
	
	static SP create( void ) { return SP( new VeryLowPrio ); }

private:
	
	
	static int &get_Time_handle_var( void ) {
		static int Time_handle;
		return Time_handle;
	}
	static int &get_sourceFed_handle_var( void ) {
		static int sourceFed_handle;
		return sourceFed_handle;
	}
	static int &get_FedName_handle_var( void ) {
		static int FedName_handle;
		return FedName_handle;
	}
	static int &get_originFed_handle_var( void ) {
		static int originFed_handle;
		return originFed_handle;
	}
	static int &get_Comment_handle_var( void ) {
		static int Comment_handle;
		return Comment_handle;
	}
	static int &get_actualLogicalGenerationTime_handle_var( void ) {
		static int actualLogicalGenerationTime_handle;
		return actualLogicalGenerationTime_handle;
	}
	static int &get_federateFilter_handle_var( void ) {
		static int federateFilter_handle;
		return federateFilter_handle;
	}
	
public:
	
	
	static int get_Time_handle( void ) { return get_Time_handle_var(); }
	static int get_sourceFed_handle( void ) { return get_sourceFed_handle_var(); }
	static int get_FedName_handle( void ) { return get_FedName_handle_var(); }
	static int get_originFed_handle( void ) { return get_originFed_handle_var(); }
	static int get_Comment_handle( void ) { return get_Comment_handle_var(); }
	static int get_actualLogicalGenerationTime_handle( void ) { return get_actualLogicalGenerationTime_handle_var(); }
	static int get_federateFilter_handle( void ) { return get_federateFilter_handle_var(); }
	


private:
	static int &getHandle( void ) {
		static int handle;
		return handle;
	}

public:
	static int get_handle( void ) { return getHandle(); }
	static std::string get_class_name( void ) { return "VeryLowPrio"; }

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
		return InteractionRoot::SP( new VeryLowPrio() );
	}


	static std::string &getInitErrorMessage( void ) {
		static std::string initErrorMessage( "Error:  VeryLowPrio:  could not initialize:  " );
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
		static std::string publishErrorMessage = "Error:  VeryLowPrio:  could not publish:  ";
		return publishErrorMessage;
	}
	
public:
	static void publish( RTI::RTIambassador *rti );
	
private:
	static std::string &getUnpublishErrorMessage( void ) {
		static std::string unpublishErrorMessage = "Error:  VeryLowPrio:  could not unpublish:  ";
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
		static std::string subscribedErrorMessage = "Error:  VeryLowPrio:  could not subscribe:  ";
		return subscribedErrorMessage;
	}

public:
	static void subscribe( RTI::RTIambassador *rti );
		
private:
	static std::string getUnsubscribeErrorMessage( void ) {
		static std::string unsubscribeErrorMessage = "Error:  VeryLowPrio:  could not unsubscribe:  ";
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
		return InteractionRoot::SP(  new VeryLowPrio( *this )  );
	}







private:
	
	
	double _Time;
	
	std::string _sourceFed;
	
	std::string _FedName;
	
	std::string _originFed;
	
	std::string _Comment;
	
	double _actualLogicalGenerationTime;
	
	std::string _federateFilter;
	
public:
		
	void set_Time( double Time ) { _Time = Time; }
	double get_Time( void ) const { return _Time; }
	
	void set_sourceFed( const std::string & sourceFed ) { _sourceFed = sourceFed; }
	const std::string & get_sourceFed( void ) const { return _sourceFed; }
	
	void set_FedName( const std::string & FedName ) { _FedName = FedName; }
	const std::string & get_FedName( void ) const { return _FedName; }
	
	void set_originFed( const std::string & originFed ) { _originFed = originFed; }
	const std::string & get_originFed( void ) const { return _originFed; }
	
	void set_Comment( const std::string & Comment ) { _Comment = Comment; }
	const std::string & get_Comment( void ) const { return _Comment; }
	
	void set_actualLogicalGenerationTime( double actualLogicalGenerationTime ) { _actualLogicalGenerationTime = actualLogicalGenerationTime; }
	double get_actualLogicalGenerationTime( void ) const { return _actualLogicalGenerationTime; }
	
	void set_federateFilter( const std::string & federateFilter ) { _federateFilter = federateFilter; }
	const std::string & get_federateFilter( void ) const { return _federateFilter; }
	


	VeryLowPrio( const RTI::ParameterHandleValuePairSet &datamemberMap ) : Super( datamemberMap ) { }
	
	VeryLowPrio( const RTI::ParameterHandleValuePairSet &datamemberMap, const RTIfedTime &logicalTime ) : Super( datamemberMap, logicalTime ) { }
	
	
public:
	TypeMedley getParameter( const std::string &datamemberName ) const {
		
		
		if ( "Time" == datamemberName ) {
			return TypeMedley( get_Time() );
		}
		else if ( "sourceFed" == datamemberName ) {
			return TypeMedley( get_sourceFed() );
		}
		else if ( "FedName" == datamemberName ) {
			return TypeMedley( get_FedName() );
		}
		else if ( "originFed" == datamemberName ) {
			return TypeMedley( get_originFed() );
		}
		else if ( "Comment" == datamemberName ) {
			return TypeMedley( get_Comment() );
		}
		else if ( "actualLogicalGenerationTime" == datamemberName ) {
			return TypeMedley( get_actualLogicalGenerationTime() );
		}
		else if ( "federateFilter" == datamemberName ) {
			return TypeMedley( get_federateFilter() );
		} else {
			return Super::getParameter( datamemberName );
		}
	}
	
	TypeMedley getParameter( int datamemberHandle ) const {
		
		
		if ( get_Time_handle() == datamemberHandle ) {
			return TypeMedley( get_Time() );
		}
		else if ( get_sourceFed_handle() == datamemberHandle ) {
			return TypeMedley( get_sourceFed() );
		}
		else if ( get_FedName_handle() == datamemberHandle ) {
			return TypeMedley( get_FedName() );
		}
		else if ( get_originFed_handle() == datamemberHandle ) {
			return TypeMedley( get_originFed() );
		}
		else if ( get_Comment_handle() == datamemberHandle ) {
			return TypeMedley( get_Comment() );
		}
		else if ( get_actualLogicalGenerationTime_handle() == datamemberHandle ) {
			return TypeMedley( get_actualLogicalGenerationTime() );
		}
		else if ( get_federateFilter_handle() == datamemberHandle ) {
			return TypeMedley( get_federateFilter() );
		} else {
			return Super::getParameter( datamemberHandle );
		}
	}

protected:
	virtual bool setParameterAux( int param_handle, const std::string &val ) {
		bool retval = true;		
		
		
		if ( param_handle == get_Time_handle() ) {
			set_Time(  TypeMedley( val )  );
		}
		else if ( param_handle == get_sourceFed_handle() ) {
			set_sourceFed(  TypeMedley( val )  );
		}
		else if ( param_handle == get_FedName_handle() ) {
			set_FedName(  TypeMedley( val )  );
		}
		else if ( param_handle == get_originFed_handle() ) {
			set_originFed(  TypeMedley( val )  );
		}
		else if ( param_handle == get_Comment_handle() ) {
			set_Comment(  TypeMedley( val )  );
		}
		else if ( param_handle == get_actualLogicalGenerationTime_handle() ) {
			set_actualLogicalGenerationTime(  TypeMedley( val )  );
		}
		else if ( param_handle == get_federateFilter_handle() ) {
			set_federateFilter(  TypeMedley( val )  );
		} else {
			retval = Super::setParameterAux( param_handle, val );
		}
		return retval;
	}
	
	virtual bool setParameterAux( const std::string &datamemberName, const std::string &val ) {
		bool retval = true;
		
		
		if ( "Time" == datamemberName ) {
			set_Time(  TypeMedley( val )  );
		}
		else if ( "sourceFed" == datamemberName ) {
			set_sourceFed(  TypeMedley( val )  );
		}
		else if ( "FedName" == datamemberName ) {
			set_FedName(  TypeMedley( val )  );
		}
		else if ( "originFed" == datamemberName ) {
			set_originFed(  TypeMedley( val )  );
		}
		else if ( "Comment" == datamemberName ) {
			set_Comment(  TypeMedley( val )  );
		}
		else if ( "actualLogicalGenerationTime" == datamemberName ) {
			set_actualLogicalGenerationTime(  TypeMedley( val )  );
		}
		else if ( "federateFilter" == datamemberName ) {
			set_federateFilter(  TypeMedley( val )  );
		} else {
			retval = Super::setParameterAux( datamemberName, val );
		}
		
		return retval;
	}
	
	virtual bool setParameterAux( const std::string &datamemberName, const TypeMedley &val ) {
		bool retval = true;
		
		
		if ( "Time" == datamemberName ) {\
			set_Time( val );
		}
		else if ( "sourceFed" == datamemberName ) {\
			set_sourceFed( val );
		}
		else if ( "FedName" == datamemberName ) {\
			set_FedName( val );
		}
		else if ( "originFed" == datamemberName ) {\
			set_originFed( val );
		}
		else if ( "Comment" == datamemberName ) {\
			set_Comment( val );
		}
		else if ( "actualLogicalGenerationTime" == datamemberName ) {\
			set_actualLogicalGenerationTime( val );
		}
		else if ( "federateFilter" == datamemberName ) {\
			set_federateFilter( val );
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

typedef VeryLowPrio::SP VeryLowPrioSP;

static bool call_VeryLowPrio_static_init = VeryLowPrio::static_init();

std::ostream &operator<<( std::ostream &os, VeryLowPrio::SP entitySP );
std::ostream &operator<<( std::ostream &os, const VeryLowPrio &entity );
#endif
