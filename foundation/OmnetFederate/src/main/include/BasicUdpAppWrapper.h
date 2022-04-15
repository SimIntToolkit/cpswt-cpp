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

#ifndef BASICUDPAPPWRAPPER_H
#define BASICUDPAPPWRAPPER_H

#include <omnetpp.h>
#include "BasicUdpApp.h"
#include "AttackCoordinator.h"
#include <InteractionRoot_p/C2WInteractionRoot_p/ActionBase_p/NetworkPacket.hpp>

/**
 * TODO - Generated class
 */
class BasicUdpAppWrapper : public BasicUdpApp {
public:
    using InteractionRoot = ::org::cpswt::hla::InteractionRoot;
    using NetworkPacket = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::ActionBase_p::NetworkPacket;

	typedef BasicUdpApp Super;

private:
	class MessageTracker {
	public:
		typedef std::set< int > IntSet;

	private:
		IntSet _intSet;
		unsigned int _maxNums;

	public:
		MessageTracker( void ) : _maxNums( 1024 ) { }
		MessageTracker( int maxNums ) : _maxNums( maxNums ) { }

		bool addInt( int num ) {
			if ( _intSet.find( num ) != _intSet.end() ) {
				return false;
			}
			_intSet.insert( num );
			while ( _intSet.size() > _maxNums ) {
				_intSet.erase( _intSet.begin() );
			}
			return true;
		}
	};

	const std::string _appName;
	MessageTracker _messageTracker;
	omnetpp::cModule *_hlaModulePtr;

public:
	BasicUdpAppWrapper( void ) : _appName( "BasicUdpAppWrapper" ) { }

	const std::string &getAppName( void ) {
		return _appName;
	}

protected:
	void recordInterfaceIPAddresses( void );
	virtual int numInitStages( void ) const override;
	virtual void initialize( int stage ) override;
	virtual void handleMessage(omnetpp::cMessage *msg) override;
	virtual void sendToUDP( inet::Packet *msg, const inet::Ipv4Address& destAddr, int destPort ) override;
	void setToDefaultValues( InteractionRoot &interactionRoot );
    void setToDefaultValues( InteractionRoot::SP interactionRootSP ) {
        setToDefaultValues( *interactionRootSP );
    }
	virtual void tweakIncoming(InteractionRoot &interactionRoot, AttackCoordinator::IntegrityAttackParams &iap);
};

#endif
