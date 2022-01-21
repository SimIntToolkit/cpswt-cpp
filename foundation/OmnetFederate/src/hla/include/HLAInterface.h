/*
 * THIS IS GENERATED CODE -- DO NOT MODIFY
 * HLAInterface.h
 *
 */

#ifndef HLAINTERFACE_H
#define HLAINTERFACE_H

#include <string>
#include <set>

#include <omnetpp.h>

#include <SynchronizedFederate.hpp>
#include <AttackCoordinator.h>

#include <messages/ObjectMsg_m.h>

#include <inet/common/INETDefs.h>


class HLAInterface : public omnetpp::cSimpleModule, public SynchronizedFederate {

using ObjectRoot = ::org::cpswt::hla::ObjectRoot;

public:
	typedef SynchronizedFederate Super;
	enum MessageType { INTERACTION, OBJECT };
	

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
