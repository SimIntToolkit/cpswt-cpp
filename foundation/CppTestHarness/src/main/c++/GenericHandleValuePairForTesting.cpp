/*
 *   Copyright 2009 The Portico Project
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
 *   MODIFIED BY HARMON HNINE FOR CppTestHarness, CPSWT PROEJECT
 */
#include "GenericHandleValuePairForTesting.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// Constructors ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
GenericHandleValuePair::GenericHandleValuePair()
{
	_theHandle = 0;
	_buffer = CharStringSP(new char[1]);
	*_buffer.get() = '\0';
	_valueLength = 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// Instance Methods //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

RTI::Handle GenericHandleValuePair::getHandle()
{
	return _theHandle;
}

void GenericHandleValuePair::setHandle( RTI::Handle newHandle )
{
	_theHandle = newHandle;
}

void GenericHandleValuePair::setValue( const char *newData, RTI::ULong newDataLength )
{
	_buffer = CharStringSP(new char[newDataLength]());
	memcpy( _buffer.get(), newData, newDataLength );
	_valueLength = newDataLength;
}

// sets the value to the given data, but DOESN'T COPY IT. this means that
// when call this method, it is passing responsibility for deleting it over
// to us and making the guarantee that the caller won't delete the data.
void GenericHandleValuePair::setValueButDontCopy( char *newData, RTI::ULong newDataLength )
{
	// don't copy! we're just going to use what's given to us
    _buffer = CharStringSP(newData);
	_valueLength = newDataLength;
}

char* GenericHandleValuePair::getValue()
{
	return _buffer.get();
}

RTI::ULong GenericHandleValuePair::getValueLength()
{
	return _valueLength;
}
//////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// Static Methods ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
