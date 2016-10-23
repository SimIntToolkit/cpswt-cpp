
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

#ifndef _StopDataInjectionAttack_CLASS
#define _StopDataInjectionAttack_CLASS

#include "AttacksNotYetImplemented.hpp"
#include "C2WException.hpp"


class StopDataInjectionAttack : public AttacksNotYetImplemented {

public:
	typedef AttacksNotYetImplemented Super;
	typedef boost::shared_ptr< StopDataInjectionAttack > SP;

	static StringVector get_parameter_names() {
		return getDatamemberNames();
	}

	static StringVector get_all_parameter_names() {
		return getAllDatamemberNames();
	}

	StopDataInjectionAttack( void ) { }
	
	static SP create( void ) { return SP( new StopDataInjectionAttack ); }

private:
	
	
	static int &get_packet_handle_var( void ) {
		static int packet_handle;
		return packet_handle;
	}
	static int &get_toNode_handle_var( void ) {
		static int toNode_handle;
		return toNode_handle;
	}
	static int &get_fromNode_handle_var( void ) {
		static int fromNode_handle;
		return fromNode_handle;
	}
	
public:
	
	
	static int get_packet_handle( void ) { return get_packet_handle_var(); }
	static int get_toNode_handle( void ) { return get_toNode_handle_var(); }
	static int get_fromNode_handle( void ) { return get_fromNode_handle_var(); }
	


private:
	static int &getHandle( void ) {
		static int handle;
		return handle;
	}

public:
	static int get_handle( void ) { return getHandle(); }
	static std::string get_class_name( void ) { return "StopDataInjectionAttack"; }

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
		return InteractionRoot::SP( new StopDataInjectionAttack() );
	}


	static std::string &getInitErrorMessage( void ) {
		static std::string initErrorMessage( "Error:  StopDataInjectionAttack:  could not initialize:  " );
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
		static std::string publishErrorMessage = "Error:  StopDataInjectionAttack:  could not publish:  ";
		return publishErrorMessage;
	}
	
public:
	static void publish( RTI::RTIambassador *rti );
	
private:
	static std::string &getUnpublishErrorMessage( void ) {
		static std::string unpublishErrorMessage = "Error:  StopDataInjectionAttack:  could not unpublish:  ";
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
		static std::string subscribedErrorMessage = "Error:  StopDataInjectionAttack:  could not subscribe:  ";
		return subscribedErrorMessage;
	}

public:
	static void subscribe( RTI::RTIambassador *rti );
		
private:
	static std::string getUnsubscribeErrorMessage( void ) {
		static std::string unsubscribeErrorMessage = "Error:  StopDataInjectionAttack:  could not unsubscribe:  ";
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
		return InteractionRoot::SP(  new StopDataInjectionAttack( *this )  );
	}







private:
	
	
	std::string _packet;
	
	std::string _toNode;
	
	std::string _fromNode;
	
public:
		
	void set_packet( const std::string & packet ) { _packet = packet; }
	const std::string & get_packet( void ) const { return _packet; }
	
	void set_toNode( const std::string & toNode ) { _toNode = toNode; }
	const std::string & get_toNode( void ) const { return _toNode; }
	
	void set_fromNode( const std::string & fromNode ) { _fromNode = fromNode; }
	const std::string & get_fromNode( void ) const { return _fromNode; }
	


	StopDataInjectionAttack( const RTI::ParameterHandleValuePairSet &datamemberMap ) : Super( datamemberMap ) { }
	
	StopDataInjectionAttack( const RTI::ParameterHandleValuePairSet &datamemberMap, const RTIfedTime &logicalTime ) : Super( datamemberMap, logicalTime ) { }
	
	
public:
	TypeMedley getParameter( const std::string &datamemberName ) const {
		
		
		if ( "packet" == datamemberName ) {
			return TypeMedley( get_packet() );
		}
		else if ( "toNode" == datamemberName ) {
			return TypeMedley( get_toNode() );
		}
		else if ( "fromNode" == datamemberName ) {
			return TypeMedley( get_fromNode() );
		} else {
			return Super::getParameter( datamemberName );
		}
	}
	
	TypeMedley getParameter( int datamemberHandle ) const {
		
		
		if ( get_packet_handle() == datamemberHandle ) {
			return TypeMedley( get_packet() );
		}
		else if ( get_toNode_handle() == datamemberHandle ) {
			return TypeMedley( get_toNode() );
		}
		else if ( get_fromNode_handle() == datamemberHandle ) {
			return TypeMedley( get_fromNode() );
		} else {
			return Super::getParameter( datamemberHandle );
		}
	}

protected:
	virtual bool setParameterAux( int param_handle, const std::string &val ) {
		bool retval = true;		
		
		
		if ( param_handle == get_packet_handle() ) {
			set_packet(  TypeMedley( val )  );
		}
		else if ( param_handle == get_toNode_handle() ) {
			set_toNode(  TypeMedley( val )  );
		}
		else if ( param_handle == get_fromNode_handle() ) {
			set_fromNode(  TypeMedley( val )  );
		} else {
			retval = Super::setParameterAux( param_handle, val );
		}
		return retval;
	}
	
	virtual bool setParameterAux( const std::string &datamemberName, const std::string &val ) {
		bool retval = true;
		
		
		if ( "packet" == datamemberName ) {
			set_packet(  TypeMedley( val )  );
		}
		else if ( "toNode" == datamemberName ) {
			set_toNode(  TypeMedley( val )  );
		}
		else if ( "fromNode" == datamemberName ) {
			set_fromNode(  TypeMedley( val )  );
		} else {
			retval = Super::setParameterAux( datamemberName, val );
		}
		
		return retval;
	}
	
	virtual bool setParameterAux( const std::string &datamemberName, const TypeMedley &val ) {
		bool retval = true;
		
		
		if ( "packet" == datamemberName ) {\
			set_packet( val );
		}
		else if ( "toNode" == datamemberName ) {\
			set_toNode( val );
		}
		else if ( "fromNode" == datamemberName ) {\
			set_fromNode( val );
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

typedef StopDataInjectionAttack::SP StopDataInjectionAttackSP;

static bool call_StopDataInjectionAttack_static_init = StopDataInjectionAttack::static_init();

std::ostream &operator<<( std::ostream &os, StopDataInjectionAttack::SP entitySP );
std::ostream &operator<<( std::ostream &os, const StopDataInjectionAttack &entity );
#endif
