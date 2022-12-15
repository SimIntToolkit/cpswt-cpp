/*
 *   Copyright 2007 The Portico Project
 *
 *   This file is part of portico.
 *
 *   portico is free software; you can redistribute it and/or modify
 *   it under the terms of the Common Developer and Distribution License (CDDL)
 *   as published by Sun Microsystems. For more information see the LICENSE file.
 *
 *   Use of this software is strictly AT YOUR OWN RISK!!!
 *   If something bad happens you do not have permission to come crying to me.
 *   (that goes for your lawyer as well)
 *
 */
#ifndef GENERIC_HANDLE_VALUE_PAIR_HPP
#define GENERIC_HANDLE_VALUE_PAIR_HPP

#include "RTIForTesting.hpp"
#include <boost/shared_ptr.hpp>

class GenericHandleValuePair {
public:
    typedef boost::shared_ptr<char[]> CharStringSP;

	//----------------------------------------------------------
	//                    STATIC VARIABLES
	//----------------------------------------------------------

	//----------------------------------------------------------
	//                   INSTANCE VARIABLES
	//----------------------------------------------------------
private:
    RTI::Handle _theHandle;
    CharStringSP _buffer;
    RTI::ULong _valueLength;

	//----------------------------------------------------------
	//                      CONSTRUCTORS
	//----------------------------------------------------------
public:
    GenericHandleValuePair();
    ~GenericHandleValuePair() {}

	//----------------------------------------------------------
	//                    INSTANCE METHODS
	//----------------------------------------------------------
public:
    RTI::Handle getHandle();
    void setHandle( RTI::Handle newHandle );
    void setValue( const char *newData, RTI::ULong newDataLength );
    char* getValue();
    RTI::ULong getValueLength();

    // sets the value to the given data, but DOESN'T COPY IT. this means that
    // when call this method, it is passing responsibility for deleting it over
    // to us and making the guarantee that the caller won't delete the data.
    void setValueButDontCopy( char *newData, RTI::ULong newDataLength );

	//----------------------------------------------------------
	//                     STATIC METHODS
	//----------------------------------------------------------

};

typedef boost::shared_ptr<GenericHandleValuePair> GenericHandleValuePairSP;

#endif

