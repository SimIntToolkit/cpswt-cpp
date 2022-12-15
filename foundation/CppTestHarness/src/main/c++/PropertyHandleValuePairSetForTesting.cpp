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
 */
#include "PropertyHandleValuePairSetForTesting.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// Constructors ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
PropertyHandleValuePairSetForTesting::PropertyHandleValuePairSetForTesting()
{
}

PropertyHandleValuePairSetForTesting::PropertyHandleValuePairSetForTesting( RTI::ULong size )
{
	// we ignore the size for now because we're using a map which will resize itself
}

PropertyHandleValuePairSetForTesting::~PropertyHandleValuePairSetForTesting()
{
	empty();
}

//////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// Instance Methods //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
GenericHandleValuePairSP PropertyHandleValuePairSetForTesting::getPairAt( RTI::ULong index ) const
{
	std::map<RTI::Handle,GenericHandleValuePairSP>::const_iterator mapIterator = pairs.begin();
	RTI::ULong counter = 0;

	while( mapIterator != pairs.end() )
	{
		if( counter == index )
		{
			return mapIterator->second;
		}
		counter++;
		mapIterator++;
	}

	return GenericHandleValuePairSP();
}

void PropertyHandleValuePairSetForTesting::checkIndex( RTI::ULong index ) const
	throw( RTI::ArrayIndexOutOfBounds )
{
	if( pairs.empty() || index >= pairs.size() )
	{
		char message[32];
		sprintf( message, "Index [%lo] out of bounds", index );
		throw RTI::ArrayIndexOutOfBounds( message ); // leaky leaky!
	}
}

RTI::ULong PropertyHandleValuePairSetForTesting::size() const
{
	return (RTI::ULong)pairs.size();
}

RTI::Handle PropertyHandleValuePairSetForTesting::getHandle( RTI::ULong index ) const
	throw( RTI::ArrayIndexOutOfBounds )
{
	checkIndex( index );
	GenericHandleValuePairSP thePair = getPairAt(index);
	return thePair->getHandle();
}

RTI::ULong PropertyHandleValuePairSetForTesting::getValueLength( RTI::ULong index ) const
	throw( RTI::ArrayIndexOutOfBounds )
{
	checkIndex( index );
	GenericHandleValuePairSP thePair = getPairAt(index);
	return thePair->getValueLength();
}

void PropertyHandleValuePairSetForTesting::getValue( RTI::ULong index,
                                            char* buffer,
                                            RTI::ULong& valueLength ) const 
	throw( RTI::ArrayIndexOutOfBounds )
{
	// note: the 1.3 spec says that we should assume that the given buffer is big
	//       enough to hold all the handle information, so we should just try and
	//       write it all, putting the written amount into the given valueLength
	//       reference on the way out

	checkIndex( index );

	// fetch the pair that contains the information
	GenericHandleValuePairSP thePair = getPairAt(index);
	// attempt to copy the entire value into the given buffer
	memcpy( buffer, thePair->getValue(), thePair->getValueLength() );
	// store the amount of bytes that were written
	valueLength = thePair->getValueLength();
}

char* PropertyHandleValuePairSetForTesting::getValuePointer( RTI::ULong index,
                                                    RTI::ULong& valueLength ) const
	throw( RTI::ArrayIndexOutOfBounds )
{
	checkIndex( index );

	GenericHandleValuePairSP thePair = getPairAt(index);
	valueLength = thePair->getValueLength();
	return thePair->getValue();
}

RTI::TransportType PropertyHandleValuePairSetForTesting::getTransportType() const
	throw( RTI::InvalidHandleValuePairSetContext )
{
	return 0;
}

RTI::TransportType PropertyHandleValuePairSetForTesting::getTransportType( RTI::ULong index ) const
	throw( RTI::ArrayIndexOutOfBounds, RTI::InvalidHandleValuePairSetContext )
{
	return 0;
}

RTI::OrderType PropertyHandleValuePairSetForTesting::getOrderType() const
	throw( RTI::InvalidHandleValuePairSetContext )
{
	return 0;
}

RTI::OrderType PropertyHandleValuePairSetForTesting::getOrderType( RTI::ULong index ) const
	throw( RTI::ArrayIndexOutOfBounds, RTI::InvalidHandleValuePairSetContext )
{
	return 0;
}

RTI::Region* PropertyHandleValuePairSetForTesting::getRegion() const
	throw( RTI::InvalidHandleValuePairSetContext )
{
	return 0;
}

RTI::Region* PropertyHandleValuePairSetForTesting::getRegion( RTI::ULong index ) const
	throw( RTI::ArrayIndexOutOfBounds, RTI::InvalidHandleValuePairSetContext )
{
	return 0;
}

void PropertyHandleValuePairSetForTesting::add(RTI::Handle handle, const char* buffer, RTI::ULong valueLength)
	throw( RTI::ValueLengthExceeded, RTI::ValueCountExceeded )
{
	GenericHandleValuePairSP thePair(new GenericHandleValuePair());

	thePair->setHandle( handle );
	thePair->setValue( buffer, valueLength ); // will make a copy

	pairs[handle] = thePair;
}

void PropertyHandleValuePairSetForTesting::remove( RTI::Handle handle ) throw( RTI::ArrayIndexOutOfBounds )
{
	pairs.erase( handle ); // remove the key from the map
}

void PropertyHandleValuePairSetForTesting::moveFrom(const RTI::AttributeHandleValuePairSet& ahvps, RTI::ULong& index )
	throw( RTI::ValueCountExceeded, RTI::ArrayIndexOutOfBounds )
{
	
}

void PropertyHandleValuePairSetForTesting::moveFrom(const RTI::ParameterHandleValuePairSet& ahvps, RTI::ULong& index )
	throw( RTI::ValueCountExceeded, RTI::ArrayIndexOutOfBounds )
{

}

void PropertyHandleValuePairSetForTesting::empty() // Empty the Set without deallocating space.
{
	// empty the set
	pairs.clear();
}

RTI::ULong PropertyHandleValuePairSetForTesting::start() const
{
	return 0;
}

RTI::ULong PropertyHandleValuePairSetForTesting::valid( RTI::ULong index ) const
{
	return 0;	
}

RTI::ULong PropertyHandleValuePairSetForTesting::next( RTI::ULong index ) const
{
	return 0;	
}

////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// Non-Standard Methods /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
// this method should NOT copy the given data, but rather, should just
// store the pointer and take ownership for the maangement of the data.
// this is designed to allow data coming in from the JNI to only be copied
// once, rather than being copied from the JNI, and then copied again when
// it is put in the set.
void PropertyHandleValuePairSetForTesting::addButDontCopy( RTI::Handle handle,
                                                  char *buffer,
                                                  RTI::ULong size )
{
	GenericHandleValuePairSP thePair(new GenericHandleValuePair());

	thePair->setHandle( handle );
	thePair->setValueButDontCopy( buffer, size );
	// store the pair
	pairs[handle] = thePair;
}

//////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// Static Methods ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
