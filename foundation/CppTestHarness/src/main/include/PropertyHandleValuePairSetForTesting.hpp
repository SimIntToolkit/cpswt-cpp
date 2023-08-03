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
#ifndef PROPERTYHANDLEVALUEPAIRSET_HPP_
#define PROPERTYHANDLEVALUEPAIRSET_HPP_

#include <map>
#include "GenericHandleValuePairForTesting.hpp"
#include <boost/shared_ptr.hpp>

#if __cplusplus >= 201703L
#define MultiArgTuple17
#define Tuple17 noexcept
#define throw(...) __VA_OPT__(MultiArg)##Tuple17
#endif

class PropertyHandleValuePairSetForTesting :
  public RTI::ParameterHandleValuePairSet, public RTI::AttributeHandleValuePairSet {
	//----------------------------------------------------------
	//                    STATIC VARIABLES
	//----------------------------------------------------------

	//----------------------------------------------------------
	//                   INSTANCE VARIABLES
	//----------------------------------------------------------
	private:
		std::map<RTI::Handle, GenericHandleValuePairSP> pairs;

	//----------------------------------------------------------
	//                      CONSTRUCTORS
	//----------------------------------------------------------
	public:
		PropertyHandleValuePairSetForTesting();
		PropertyHandleValuePairSetForTesting( RTI::ULong size );

		template<typename T> PropertyHandleValuePairSetForTesting(const T &propertyHandleValuePairSet) {
		    RTI::ULong maxValueLength = 0;
		    for(int ix = 0 ; ix < propertyHandleValuePairSet.size() ; ++ix) {
                RTI::ULong valueLength = propertyHandleValuePairSet.getValueLength(ix);
                if (valueLength > maxValueLength) {
                    maxValueLength = valueLength;
                }
            }
            char *buffer = new char[maxValueLength];
		    for(int ix = 0 ; ix < propertyHandleValuePairSet.size() ; ++ix) {
                RTI::Handle handle = propertyHandleValuePairSet.getHandle(ix);
                RTI::ULong valueLength = propertyHandleValuePairSet.getValueLength(ix);
                propertyHandleValuePairSet.getValue(ix, buffer, valueLength);
                add(handle, buffer, valueLength);
            }
            delete[] buffer;
        }
		virtual ~PropertyHandleValuePairSetForTesting();

	//----------------------------------------------------------
	//                    INSTANCE METHODS
	//----------------------------------------------------------
	private:
		GenericHandleValuePairSP getPairAt( RTI::ULong i ) const;
		void checkIndex( RTI::ULong index ) const throw( RTI::ArrayIndexOutOfBounds );

	public:
		RTI::ULong size() const override;

		RTI::Handle getHandle( RTI::ULong index ) const
			throw( RTI::ArrayIndexOutOfBounds ) override;

		RTI::ULong getValueLength( RTI::ULong index ) const
			throw( RTI::ArrayIndexOutOfBounds ) override;

		void getValue( RTI::ULong index, char* buffer, RTI::ULong& valueLength ) const
			throw( RTI::ArrayIndexOutOfBounds ) override;

		char* getValuePointer( RTI::ULong index, RTI::ULong& valueLength ) const
			throw( RTI::ArrayIndexOutOfBounds ) override;

		RTI::TransportType getTransportType() const
			throw( RTI::InvalidHandleValuePairSetContext ) override;

		RTI::TransportType getTransportType( RTI::ULong index ) const
			throw( RTI::ArrayIndexOutOfBounds, RTI::InvalidHandleValuePairSetContext ) override;

		RTI::OrderType getOrderType() const
			throw( RTI::InvalidHandleValuePairSetContext ) override;

		RTI::OrderType getOrderType( RTI::ULong index ) const
			throw( RTI::ArrayIndexOutOfBounds, RTI::InvalidHandleValuePairSetContext ) override;

		RTI::Region* getRegion() const
			throw( RTI::InvalidHandleValuePairSetContext ) override;

		RTI::Region* getRegion( RTI::ULong index ) const
			throw( RTI::ArrayIndexOutOfBounds, RTI::InvalidHandleValuePairSetContext ) override;

		void add( RTI::Handle handle, const char* buffer, RTI::ULong valueLength )
			throw( RTI::ValueLengthExceeded, RTI::ValueCountExceeded ) override;

		void remove( RTI::Handle handle ) throw( RTI::ArrayIndexOutOfBounds ) override;

		void moveFrom( const RTI::ParameterHandleValuePairSet& ahvps, RTI::ULong& index )
			throw( RTI::ValueCountExceeded, RTI::ArrayIndexOutOfBounds ) override;

		void moveFrom( const RTI::AttributeHandleValuePairSet& ahvps, RTI::ULong& index )
			throw( RTI::ValueCountExceeded, RTI::ArrayIndexOutOfBounds ) override;

		void empty() override; // Empty the Set without deallocating space.

		RTI::ULong start() const override;

		RTI::ULong valid( RTI::ULong index ) const override;

		RTI::ULong next( RTI::ULong index ) const override;

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

#if __cplusplus >= 201703L
#undef MultiArgTuple17
#undef Tuple17
#undef throw
#endif

#endif /* ATTRIBUTEHANDLEVALUEPAIRSET_H_ */
