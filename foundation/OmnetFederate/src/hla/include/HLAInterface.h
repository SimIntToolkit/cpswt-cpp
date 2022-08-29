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

#ifndef HLAINTERFACE_H
#define HLAINTERFACE_H

#include <string>
#include <set>
#include <vector>
#include <list>

#include <omnetpp.h>

#include <SynchronizedFederate.hpp>
#include <AttackCoordinator.h>

#include <messages/InteractionMsg_m.h>

#include <messages/ObjectMsg_m.h>

#include <inet/common/INETDefs.h>

#include <jsoncpp/json/json.h>


class HLAInterface : public omnetpp::cSimpleModule, public SynchronizedFederate {

using ObjectRoot = ::org::cpswt::hla::ObjectRoot;
using C2WInteractionRoot = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot;

public:
	typedef SynchronizedFederate Super;
	enum MessageType { INTERACTION, OBJECT };

	typedef std::set<std::string> StringSet;
	//
	// HLAInterface CAN ACCESS IP MODULES OF HOSTS USING THE FOLLOWING CODE */
	//

public:
	static const std::string &getInteractionMessageLabel(void) {
	    static std::string interactionMessageLabel("Interaction+Msg");
	    return interactionMessageLabel;
	}

private:
	std::string _logLevel;

	inet::cMessage *_keepAliveMsg;
	inet::cMessage *_readyToRunMsg;
	inet::cMessage *_interactionArrivalMsg;
	bool _noInteractionArrivalFlag;

    struct FederateHostConfig {
        std::string host;
        std::string hostApp;
        int appIndex;
        std::string appInterface;

        void assignFromJson(const Json::Value &jsonValue);

        FederateHostConfig() :
            host(""), hostApp(""), appIndex(0), appInterface("") {}

        FederateHostConfig(const Json::Value &jsonValue) {
            assignFromJson(jsonValue);
        }
    };

    typedef std::map<std::string, FederateHostConfig> FederateNameToHostConfigMap;

    FederateNameToHostConfigMap _federateNameToHostConfigMap;

    void initializeFederateHostConfigMap(const std::string &federateHostConfigJsonFileName);

	struct MessagingInfo {
	    std::string _publishFederateName;
	    int _payloadSize;

	    MessagingInfo(const std::string &publishFederateName, int payloadSize) {
	        _publishFederateName = publishFederateName;
	        _payloadSize = payloadSize;
	    }

	    const std::string &getPublishFederateName() const {
	        return _publishFederateName;
	    }

	    int getPayloadSize() const {
	        return _payloadSize;
	    }
	};

	typedef C2WInteractionRoot::StringList StringList;
	typedef std::vector<MessagingInfo> MessagingInfoVector;
	typedef std::map< StringList, MessagingInfoVector > FederateSequenceMessagingInfoVectorMap;

	typedef std::map< std::string, FederateSequenceMessagingInfoVectorMap> MessagingFederateSequenceMessagingInfoVectorMap;

	StringSet _dynamicPublishFullHlaClassNameSet;
    StringSet _dynamicSubscribeFullHlaClassNameSet;

	MessagingFederateSequenceMessagingInfoVectorMap _messagingFederateSequenceMessagingInfoVectorMap;

    void initializeFederateSequenceToMessagingInfoMap(const std::string &federateSequenceToMessagingInfoJsonFileName);

	static HLAInterface *&getHLAInterfacePtr( void ) {
		static HLAInterface *hlaInterfacePtr = 0;
		return hlaInterfacePtr;
	}

	static void setInstancePtr( HLAInterface *hlaInterfacePtr ) {
		if ( getHLAInterfacePtr() != 0 ) {
			std::cerr << "WARNING!  MULTIPLE INSTANCES OF THE HLAInterface CLASS DETECTED.  ALL BUT THE FIRST ARE IGNORED." << std::endl;
			return;
		}
		getHLAInterfacePtr() = hlaInterfacePtr;
	}


public:
	static HLAInterface *get_InstancePtr( void ) { return getHLAInterfacePtr(); }

	HLAInterface( void );
	virtual ~HLAInterface( void ) throw();

	//
	// SYNCHRONIZED-FEDERATE METHODS
	//
	void populateInteractionMsg(InteractionMsg &interactionMsg, const std::string &sendingFederateName, const std::string &receivingFederateName);

    void processInteractions( void );
    
    void interactionArrival( void );

	virtual void receiveInteraction(
	 RTI::InteractionClassHandle theInteraction,
	 const RTI::ParameterHandleValuePairSet& theParameters,
	 const RTI::FedTime& theTime,
     const char *theTag,
	 RTI::EventRetractionHandle theHandle
	)
	 throw ( RTI::InteractionClassNotKnown, RTI::InteractionParameterNotKnown, RTI::InvalidFederationTime, RTI::FederateInternalError ) override;

	virtual void receiveInteraction(
	 RTI::InteractionClassHandle theInteraction,
	 const RTI::ParameterHandleValuePairSet& theParameters,
     const char *theTag
	)
	 throw ( RTI::InteractionClassNotKnown, RTI::InteractionParameterNotKnown, RTI::FederateInternalError ) override;


    void processObjectReflectors( void );
    
    void reflectAttributeValues(
     RTI::ObjectHandle theObject, 
     const RTI::AttributeHandleValuePairSet& theAttributes,
     const RTI::FedTime& theTime,
     const char *theTag,
     RTI::EventRetractionHandle theHandle
    ) throw ( RTI::ObjectNotKnown, RTI::AttributeNotKnown, RTI::FederateOwnsAttributes, RTI::InvalidFederationTime, RTI::FederateInternalError ) override {
        SynchronizedFederate::reflectAttributeValues( theObject, theAttributes, theTime, theTag, theHandle );
        processObjectReflectors();
    }

    void reflectAttributeValues ( RTI::ObjectHandle theObject, const RTI::AttributeHandleValuePairSet& theAttributes, const char *theTag )
     throw ( RTI::ObjectNotKnown, RTI::AttributeNotKnown, RTI::FederateOwnsAttributes, RTI::FederateInternalError ) override {
        SynchronizedFederate::reflectAttributeValues( theObject, theAttributes, theTag );
        processObjectReflectors();
    }


    //
    // OMNET CMODULE METHODS
    //
    
    virtual int numInitStages() const override { return inet::NUM_INIT_STAGES; }
	virtual void initialize( int stage ) override;
	virtual void handleMessage( inet::cMessage *msg ) override;
	virtual void finish() override {
	    SynchronizedFederate::finalizeAndTerminate();
	}

	ObjectMsg *wrapObject( ObjectRoot::SP objectRootSP, const std::string &name, inet::simtime_t timestamp ) {
	
		Enter_Method( "wrapObject" );

		ObjectMsg *objectMsgPtr = new ObjectMsg( name.c_str() );
		objectMsgPtr->setObjectRootSP( objectRootSP );
		objectMsgPtr->setKind( OBJECT );
		objectMsgPtr->setTimestamp( timestamp );
		
		return objectMsgPtr;
	}
	
	ObjectMsg *wrapObject( ObjectRoot::SP objectRootSP, const std::string &name ) {
		return wrapObject( objectRootSP, name, inet::simTime() );
	}
	
	ObjectMsg *wrapObject( ObjectRoot &objectRoot, const std::string &name, inet::simtime_t timestamp ) {
		return wrapObject( objectRoot.cloneObject(), name, timestamp );
	}

	ObjectMsg *wrapObject( ObjectRoot &objectRoot, const std::string &name ) {
		return wrapObject( objectRoot.cloneObject(), name );
	}

	void updateObject( ObjectMsg *objectMsgPtr ) {
		Enter_Method( "updateObject" );
		take( objectMsgPtr );
		scheduleAt( inet::simTime(), objectMsgPtr );
	}
	
	void updateObject( ObjectRoot::SP objectRootSP, const std::string &name, inet::simtime_t timestamp ) {		
		ObjectMsg *objectMsgPtr = wrapObject( objectRootSP, name, timestamp );
		updateObject( objectMsgPtr );
	}
	
	void updateObject( ObjectRoot::SP objectRootSP, const std::string &name, double timestamp ) {
		updateObject(  objectRootSP, name, inet::SimTime( timestamp )  );
	}

	void updateObject( ObjectRoot::SP objectRootSP, const std::string &name ) {
		updateObject( objectRootSP, name, inet::simTime() );
	}

	void updateObject( ObjectRoot &objectRoot, const std::string &name, inet::simtime_t timestamp ) {
		updateObject( objectRoot.cloneObject(), name, timestamp );
	}
	
	void updateObject( ObjectRoot &objectRoot, const std::string &name, double timestamp ) {
		updateObject(  objectRoot, name, inet::SimTime( timestamp )  );
	}
	
	void updateObject( ObjectRoot &objectRoot, const std::string &name ) {
		updateObject( objectRoot, name, inet::simTime() );
	}

	static ObjectRoot::SP unwrapObject( inet::cMessage *msg ) {
		if ( msg->getKind() != OBJECT ) return ObjectRoot::SP(  static_cast< ObjectRoot * >( 0 )  );
		return static_cast< ObjectMsg * >( msg )->getObjectRootSP();
	}	

private:
    void setup( void );
	void sendKeepAliveMsg( void );

};

#endif /* HLAINTERFACE_H */
