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
#include "AttributeHandleValuePairSetForTesting.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// Constructors ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
AttributeHandleValuePairSetForTesting::AttributeHandleValuePairSetForTesting()
{
}

AttributeHandleValuePairSetForTesting::AttributeHandleValuePairSetForTesting( RTI::ULong size )
{
	// we ignore the size for now because we're using a map which will resize itself
}

AttributeHandleValuePairSetForTesting::~AttributeHandleValuePairSetForTesting()
{
	this->empty();
}

//////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// Instance Methods //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
GenericHandleValuePair* AttributeHandleValuePairSetForTesting::getPairAt( RTI::ULong index ) const
{
	std::map<RTI::Handle,GenericHandleValuePair*>::const_iterator mapIterator = pairs.begin();
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

	return 0;
}

void AttributeHandleValuePairSetForTesting::checkIndex( RTI::ULong index ) const
	throw( RTI::ArrayIndexOutOfBounds )
{
	if( pairs.empty() || index > pairs.size()-1 )
	{
		char message[32];
		sprintf( message, "Index [%lo] out of bounds", index );
		throw RTI::ArrayIndexOutOfBounds( message ); // leaky leaky!
	}
}

RTI::ULong AttributeHandleValuePairSetForTesting::size() const
{
	return (RTI::ULong)pairs.size();
}

RTI::Handle AttributeHandleValuePairSetForTesting::getHandle( RTI::ULong index ) const
	throw( RTI::ArrayIndexOutOfBounds )
{
	checkIndex( index );
	GenericHandleValuePair *thePair = this->getPairAt(index);
	return thePair->getHandle();
}

RTI::ULong AttributeHandleValuePairSetForTesting::getValueLength( RTI::ULong index ) const
	throw( RTI::ArrayIndexOutOfBounds )
{
	checkIndex( index );
	GenericHandleValuePair *thePair = this->getPairAt(index);
	return thePair->getValueLength();
}

void AttributeHandleValuePairSetForTesting::getValue( RTI::ULong index,
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
	GenericHandleValuePair *thePair = this->getPairAt(index);
	// attempt to copy the entire value into the given buffer
	memcpy( buffer, thePair->getValue(), thePair->getValueLength() );
	// store the amount of bytes that were written
	valueLength = thePair->getValueLength();
}

char* AttributeHandleValuePairSetForTesting::getValuePointer( RTI::ULong index,
                                                    RTI::ULong& valueLength ) const
	throw( RTI::ArrayIndexOutOfBounds )
{
	checkIndex( index );

	GenericHandleValuePair *thePair = this->getPairAt(index);
	valueLength = thePair->getValueLength();
	return thePair->getValue();
}

RTI::TransportType AttributeHandleValuePairSetForTesting::getTransportType( RTI::ULong index ) const
	throw( RTI::ArrayIndexOutOfBounds, RTI::InvalidHandleValuePairSetContext )
{
	return 0;
}

RTI::OrderType AttributeHandleValuePairSetForTesting::getOrderType( RTI::ULong index ) const
	throw( RTI::ArrayIndexOutOfBounds, RTI::InvalidHandleValuePairSetContext )
{
	return 0;
}

RTI::Region* AttributeHandleValuePairSetForTesting::getRegion( RTI::ULong index ) const
	throw( RTI::ArrayIndexOutOfBounds, RTI::InvalidHandleValuePairSetContext )
{
	return 0;
}

void AttributeHandleValuePairSetForTesting::add( RTI::Handle handle,
                                       const char* buffer,
                                       RTI::ULong valueLength )
	throw( RTI::ValueLengthExceeded, RTI::ValueCountExceeded )
{
	GenericHandleValuePair *thePair = new GenericHandleValuePair();

	thePair->setHandle( handle );
	thePair->setValue( buffer, valueLength ); // will make a copy

	pairs[handle] = thePair;
}

void AttributeHandleValuePairSetForTesting::remove( RTI::Handle handle ) throw( RTI::ArrayIndexOutOfBounds )
{
	delete pairs[handle];  // delete the GenericHandleValuePair, releasing the memory
	pairs.erase( handle ); // remove the key from the map
}

void AttributeHandleValuePairSetForTesting::moveFrom( const RTI::AttributeHandleValuePairSet& ahvps,
                                                  RTI::ULong& index ) 
	throw( RTI::ValueCountExceeded, RTI::ArrayIndexOutOfBounds )
{
	
}

void AttributeHandleValuePairSetForTesting::empty() // Empty the Set without deallocating space.
{
	// recoup any space for the contents of the map
	std::map<RTI::Handle,GenericHandleValuePair*>::iterator iterator;
	for( iterator = pairs.begin(); iterator != pairs.end(); iterator++ )
	{
		GenericHandleValuePair *current = (*iterator).second;
		delete current;
	}

	// empty the set
	pairs.clear();
}

RTI::ULong AttributeHandleValuePairSetForTesting::start() const
{
	return 0;
}

RTI::ULong AttributeHandleValuePairSetForTesting::valid( RTI::ULong index ) const
{
	return 0;	
}

RTI::ULong AttributeHandleValuePairSetForTesting::next( RTI::ULong index ) const
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
void AttributeHandleValuePairSetForTesting::addButDontCopy( RTI::Handle handle,
                                                  char *buffer,
                                                  RTI::ULong size )
{
	GenericHandleValuePair *thePair = new GenericHandleValuePair();

	thePair->setHandle( handle );
	thePair->setValueButDontCopy( buffer, size );
	// store the pair
	pairs[handle] = thePair;
}

//////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// Static Methods ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
