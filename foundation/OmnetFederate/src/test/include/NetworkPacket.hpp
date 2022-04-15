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

#ifndef _NetworkPacket_CLASS
#define _NetworkPacket_CLASS

#include "InteractionRoot.hpp"


class NetworkPacket : public InteractionRoot {

private:
    static int get_handle(void) {
        return 1;
    }

    static StringVector &getDatamemberNames(void) {
        static StringVector stringVector;
        return stringVector;
    }

public:
    static std::string get_class_name( void ) { return "InteractionRoot"; }

    static StringVector get_parameter_names(void) {
        return getDatamemberNames();
    }

    static bool static_init(void) {

        getDatamemberNames().push_back( "packetType" );
        getDatamemberNames().push_back( "receiverHost" );
        getDatamemberNames().push_back( "data" );
        getDatamemberNames().push_back( "receiverAppIndex" );
        getDatamemberNames().push_back( "receiverHostApp" );
        getDatamemberNames().push_back( "senderHostApp" );
        getDatamemberNames().push_back( "numBytes" );
        getDatamemberNames().push_back( "senderHost" );
        getDatamemberNames().push_back( "receiverAppInterface" );
        getDatamemberNames().push_back( "senderAppIndex" );

        return true;
    }

	typedef InteractionRoot Super;
	typedef boost::shared_ptr< NetworkPacket > SP;

	NetworkPacket( void ) { }
	virtual ~NetworkPacket(void) { }
	
	static bool match( int handle ) { return handle == get_handle(); }

	virtual int getClassHandle( void ) const override { return get_handle(); }
    virtual std::string getClassName( void ) const override { return get_class_name(); }

	virtual StringVector getParameterNames( void ) const override { return get_parameter_names(); }

private:
	
	std::string _packetType;
	std::string _receiverHost;
	std::string _data;
	int _receiverAppIndex;
	std::string _receiverHostApp;
	std::string _senderHostApp;
	int _numBytes;
	std::string _senderHost;
	std::string _receiverAppInterface;
	int _senderAppIndex;
	
public:
		
	void set_packetType( const std::string & packetType ) { _packetType = packetType; }
	const std::string & get_packetType( void ) const { return _packetType; }
	
	void set_receiverHost( const std::string & receiverHost ) { _receiverHost = receiverHost; }
	const std::string & get_receiverHost( void ) const { return _receiverHost; }
	
	void set_data( const std::string & data ) { _data = data; }
	const std::string & get_data( void ) const { return _data; }
	
	void set_receiverAppIndex( int receiverAppIndex ) { _receiverAppIndex = receiverAppIndex; }
	int get_receiverAppIndex( void ) const { return _receiverAppIndex; }
	
	void set_receiverHostApp( const std::string & receiverHostApp ) { _receiverHostApp = receiverHostApp; }
	const std::string & get_receiverHostApp( void ) const { return _receiverHostApp; }
	
	void set_senderHostApp( const std::string & senderHostApp ) { _senderHostApp = senderHostApp; }
	const std::string & get_senderHostApp( void ) const { return _senderHostApp; }
	
	void set_numBytes( int numBytes ) { _numBytes = numBytes; }
	int get_numBytes( void ) const { return _numBytes; }
	
	void set_senderHost( const std::string & senderHost ) { _senderHost = senderHost; }
	const std::string & get_senderHost( void ) const { return _senderHost; }
	
	void set_receiverAppInterface( const std::string & receiverAppInterface ) { _receiverAppInterface = receiverAppInterface; }
	const std::string & get_receiverAppInterface( void ) const { return _receiverAppInterface; }
	
	void set_senderAppIndex( int senderAppIndex ) { _senderAppIndex = senderAppIndex; }
	int get_senderAppIndex( void ) const { return _senderAppIndex; }
	
    TypeMedley getParameter( const std::string &datamemberName ) const override {

        if ( "packetType" == datamemberName ) {
            return TypeMedley( get_packetType() );
        }
        else if ( "receiverHost" == datamemberName ) {
            return TypeMedley( get_receiverHost() );
        }
        else if ( "data" == datamemberName ) {
            return TypeMedley( get_data() );
        }
        else if ( "receiverAppIndex" == datamemberName ) {
            return TypeMedley( get_receiverAppIndex() );
        }
        else if ( "receiverHostApp" == datamemberName ) {
            return TypeMedley( get_receiverHostApp() );
        }
        else if ( "senderHostApp" == datamemberName ) {
            return TypeMedley( get_senderHostApp() );
        }
        else if ( "numBytes" == datamemberName ) {
            return TypeMedley( get_numBytes() );
        }
        else if ( "senderHost" == datamemberName ) {
            return TypeMedley( get_senderHost() );
        }
        else if ( "receiverAppInterface" == datamemberName ) {
            return TypeMedley( get_receiverAppInterface() );
        }
        else if ( "senderAppIndex" == datamemberName ) {
            return TypeMedley( get_senderAppIndex() );
        } else {
            return Super::getParameter( datamemberName );
        }
    }

};

typedef NetworkPacket::SP NetworkPacketSP;

static bool call_NetworkPacket_static_init = NetworkPacket::static_init();

//std::ostream &operator<<( std::ostream &os, NetworkPacket::SP entitySP );
//std::ostream &operator<<( std::ostream &os, const NetworkPacket &entity );

#endif
