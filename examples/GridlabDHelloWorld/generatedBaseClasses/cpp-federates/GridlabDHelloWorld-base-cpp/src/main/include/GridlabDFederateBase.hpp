#ifndef _GridlabDFederateBase_
#define _GridlabDFederateBase_

// This code has been generated by the C2W code generator.
// Do not edit manually!

#include <vector>

#include "SynchronizedFederate.hpp"
#include "SubscribedInteractionFilter.hpp"


#include "GridlabDOutput.hpp"
#include "GridlabDInput.hpp"
#include "GridlabDControl.hpp"

#include "C2WLogger.hpp"

class GridlabDFederateBase : public SynchronizedFederate {

public:
	typedef SynchronizedFederate Super;
	

	typedef std::vector< std::string > ArgVector;
	
	static double getLookAhead( void ) {
		static double lookAhead = 0.2;
		return lookAhead;
	}

	virtual ~GridlabDFederateBase( void )
	 throw (RTI::FederateInternalError) { }

private:
	SubscribedInteractionFilter _subscribedInteractionFilter;

protected:
	void init( ArgVector argVector ) {

		createRTI();
		joinFederation( argVector[ 0 ], argVector[ 1 ] );
		
		std::string loglevel="";
		ArgVector loggerArgVector;
		if ( argVector.size() == 3 ) {
			loggerArgVector.push_back( argVector[ 2 ] );
		} else if ( argVector.size() > 3 ) {
			loggerArgVector.push_back( argVector[ 3 ] );
		}
		_logger->init(loggerArgVector);
		
		if ( argVector.size() == 5 ) {
			loglevel = argVector[ 4 ];
		}
			

		enableTimeConstrained();



		enableTimeRegulation( getLookAhead() );



		enableAsynchronousDelivery();



        // interaction pubsub
        
        
        GridlabDOutput::publish( getRTI() );
          
          
        GridlabDInput::subscribe( getRTI() );
		_subscribedInteractionFilter.setFedFilters( GridlabDInput::get_handle(), SubscribedInteractionFilter::ORIGIN_FILTER_DISABLED, SubscribedInteractionFilter::SOURCE_FILTER_DISABLED );  
        GridlabDControl::subscribe( getRTI() );
		_subscribedInteractionFilter.setFedFilters( GridlabDControl::get_handle(), SubscribedInteractionFilter::ORIGIN_FILTER_DISABLED, SubscribedInteractionFilter::SOURCE_FILTER_DISABLED );  
		
		// object pubsub
        
          

         
          
   
        
         // enable pubsub log
         if( argVector.size() > 2 ){
			
			
			GridlabDOutput::enablePublishLog("GridlabDOutput", "GridlabDFederate", "NORMAL", loglevel);  
			
			
			GridlabDInput::enableSubscribeLog("GridlabDInput", "GridlabDFederate", "NORMAL", loglevel);
			GridlabDControl::enableSubscribeLog("GridlabDControl", "GridlabDFederate", "NORMAL", loglevel);  
			
			  
			
			  
		}

	}

	void init( int argc, char *argv[] ) {
		ArgVector argVector;
		for( int ix = 1 ; ix < argc ; ++ix ) argVector.push_back( argv[ ix ] );
		init( argVector );
	}
	
	void init( const std::string &federation_id, const std::string &federate_id ) {
		ArgVector argVector;
		argVector.push_back( federation_id );
		argVector.push_back( federate_id );
		init( argVector );
	}
	
public:	
	// default constructor
	GridlabDFederateBase( void ) { }
	
	// constructor
	GridlabDFederateBase( const std::string &federation_id, const std::string &federate_id ) { init( federation_id, federate_id ); }

	// constructor	
	GridlabDFederateBase( int argc, char *argv[] ) { init( argc, argv ); }

	
	
	GridlabDOutputSP create_GridlabDOutput( void ) {
	   GridlabDOutputSP interactionSP = GridlabDOutput::create();
	   interactionSP->set_sourceFed( getFederateId() );
	   interactionSP->set_originFed( getFederateId() );
	   return interactionSP;
	}  

    
    virtual void receiveInteraction(
	 RTI::InteractionClassHandle theInteraction,
	 const RTI::ParameterHandleValuePairSet& theParameters,
	 const RTI::FedTime& theTime,
	 const char *theTag,
	 RTI::EventRetractionHandle theHandle
	)
	 throw ( RTI::InteractionClassNotKnown, RTI::InteractionParameterNotKnown, RTI::InvalidFederationTime, RTI::FederateInternalError) {

		if ( getMoreATRs() ) {
			InteractionRoot::SP interactionRootSP = InteractionRoot::create_interaction( theInteraction, theParameters, theTime );
			C2WInteractionRootSP c2wInteractionRootSP = boost::dynamic_pointer_cast< C2WInteractionRoot >( interactionRootSP );
			if ( c2wInteractionRootSP != 0 ) {

	            // Filter interaction if src/origin fed requirements (if any) are not met
	            if (  _subscribedInteractionFilter.filterC2WInteraction( getFederateId(), c2wInteractionRootSP )  ) {
	            	return;
	            }
	        }

	        Super::receiveInteraction( theInteraction, theParameters, theTime, theTag, theHandle );
	    }
	}

	virtual void receiveInteraction(
	 RTI::InteractionClassHandle theInteraction,
	 const RTI::ParameterHandleValuePairSet& theParameters,
	 const char *theTag
	)
	 throw ( RTI::InteractionClassNotKnown, RTI::InteractionParameterNotKnown, RTI::FederateInternalError) {
		if ( getMoreATRs() ) {
			InteractionRoot::SP interactionRootSP = InteractionRoot::create_interaction( theInteraction, theParameters );
			C2WInteractionRootSP c2wInteractionRootSP = boost::dynamic_pointer_cast< C2WInteractionRoot >( interactionRootSP );
			if ( c2wInteractionRootSP != 0 ) {

	            // Filter interaction if src/origin fed requirements (if any) are not met
	            if (  _subscribedInteractionFilter.filterC2WInteraction( getFederateId(), c2wInteractionRootSP )  ) {
	            	return;
	            }
	        }

			Super::receiveInteraction( theInteraction, theParameters, theTag );
		}
	}
};

#endif

