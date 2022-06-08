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
 *   MODIFIED BY HARMON NINE FOR CppTestHarness
 */
#ifndef ATTRIBUTEHANDLEVALUEPAIRSET_HPP_
#define ATTRIBUTEHANDLEVALUEPAIRSET_HPP_

#include <map>
#include "GenericHandleValuePairForTesting.hpp"

class AttributeHandleValuePairSetForTesting : public RTI::AttributeHandleValuePairSet
{
	//----------------------------------------------------------
	//                    STATIC VARIABLES
	//----------------------------------------------------------

	//----------------------------------------------------------
	//                   INSTANCE VARIABLES
	//----------------------------------------------------------
	private:
		std::map<RTI::Handle,GenericHandleValuePair*> pairs;

	//----------------------------------------------------------
	//                      CONSTRUCTORS
	//----------------------------------------------------------
	public:
		AttributeHandleValuePairSetForTesting();
		AttributeHandleValuePairSetForTesting( RTI::ULong size );
		virtual ~AttributeHandleValuePairSetForTesting();

	//----------------------------------------------------------
	//                    INSTANCE METHODS
	//----------------------------------------------------------
	private:
		GenericHandleValuePair* getPairAt( RTI::ULong i ) const;
		void checkIndex( RTI::ULong index ) const throw( RTI::ArrayIndexOutOfBounds );

	public:
		virtual RTI::ULong size() const;

		virtual RTI::Handle getHandle( RTI::ULong index ) const
			throw( RTI::ArrayIndexOutOfBounds );

		virtual RTI::ULong getValueLength( RTI::ULong index ) const
			throw( RTI::ArrayIndexOutOfBounds );

		virtual void getValue( RTI::ULong index, char* buffer, RTI::ULong& valueLength ) const 
			throw( RTI::ArrayIndexOutOfBounds );

		virtual char* getValuePointer( RTI::ULong index, RTI::ULong& valueLength ) const
			throw( RTI::ArrayIndexOutOfBounds );

		virtual RTI::TransportType getTransportType( RTI::ULong index ) const
			throw( RTI::ArrayIndexOutOfBounds, RTI::InvalidHandleValuePairSetContext );

		virtual RTI::OrderType getOrderType( RTI::ULong index ) const
			throw( RTI::ArrayIndexOutOfBounds, RTI::InvalidHandleValuePairSetContext );

		virtual RTI::Region* getRegion( RTI::ULong index ) const
			throw( RTI::ArrayIndexOutOfBounds, RTI::InvalidHandleValuePairSetContext );

		virtual void add( RTI::Handle handle, const char* buffer, RTI::ULong valueLength )
			throw( RTI::ValueLengthExceeded, RTI::ValueCountExceeded );

		virtual void remove( RTI::Handle handle ) throw( RTI::ArrayIndexOutOfBounds );

		virtual void moveFrom( const RTI::AttributeHandleValuePairSet& ahvps, RTI::ULong& index ) 
			throw( RTI::ValueCountExceeded, RTI::ArrayIndexOutOfBounds );

		virtual void empty(); // Empty the Set without deallocating space.

		virtual RTI::ULong start() const;

		virtual RTI::ULong valid( RTI::ULong index ) const;

		virtual RTI::ULong next( RTI::ULong index ) const;

	public: // non-standard methods			
		// this method should NOT copy the given data, but rather, should just
		// store the pointer and take ownership for the maangement of the data.
		// this is designed to allow data coming in from the JNI to only be copied
		// once, rather than being copied from the JNI, and then copied again when
		// it is put in the set.
		virtual void addButDontCopy( RTI::Handle handle, char *buffer, RTI::ULong size );

	//----------------------------------------------------------
	//                     STATIC METHODS
	//----------------------------------------------------------

};

#endif /* ATTRIBUTEHANDLEVALUEPAIRSET_H_ */
