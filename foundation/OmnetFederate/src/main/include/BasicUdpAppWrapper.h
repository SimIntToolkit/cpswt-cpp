//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

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
