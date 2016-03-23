
// This code has been generated by the C2W code generator.
// Do not edit manually!

#include "SimulationControl.hpp"




void SimulationControl::init( RTI::RTIambassador *rti ) {
	static bool isInitialized = false;
	if ( isInitialized ) {
		return;
	}
	isInitialized = true;

	C2WInteractionRoot::init( rti );

	bool isNotInitialized = true;
	while( isNotInitialized ) {
		try {
			getHandle() = rti->getInteractionClassHandle( "InteractionRoot.C2WInteractionRoot.SimulationControl" );
			isNotInitialized = false;
		} catch ( RTI::FederateNotExecutionMember & ) {
			std::cerr << getInitErrorMessage() << "Federate Not Execution Member" << std::endl;
			return;				
		} catch ( RTI::NameNotFound & ) {
			std::cerr << getInitErrorMessage() << "Name Not Found" << std::endl;
			return;				
		} catch ( ... ) {
			std::cerr << getInitErrorMessage() << "Exception caught ... retry" << std::endl;
		}
	}

	getClassNameHandleMap().insert(  std::make_pair( "SimulationControl", get_handle() )  );
	getClassHandleNameMap().insert(  std::make_pair( get_handle(), "SimulationControl" )  );


	isNotInitialized = true;
	while( isNotInitialized ) {
		try {		
			
			
			get_sourceFed_handle_var() = rti->getParameterHandle( "sourceFed", get_handle() );
			get_originFed_handle_var() = rti->getParameterHandle( "originFed", get_handle() );
			get_actualLogicalGenerationTime_handle_var() = rti->getParameterHandle( "actualLogicalGenerationTime", get_handle() );
			get_federateFilter_handle_var() = rti->getParameterHandle( "federateFilter", get_handle() );
			isNotInitialized = false;
		} catch ( RTI::FederateNotExecutionMember & ) {
			std::cerr << getInitErrorMessage() << "Federate Not Execution Member" << std::endl;
			return;				
		} catch ( RTI::InteractionClassNotDefined & ) {
			std::cerr << getInitErrorMessage() << "Interaction Class Not Defined" << std::endl;
			return;				
		} catch ( RTI::NameNotFound & ) {
			std::cerr << getInitErrorMessage() << "Name Not Found" << std::endl;
			return;				
		} catch ( ... ) {
			std::cerr << getInitErrorMessage() << "Exception caught ... retry" << std::endl;
		}
	}
	
	
	getDatamemberNameHandleMap().insert(  std::make_pair( "SimulationControl,sourceFed", get_sourceFed_handle() )  );
	
	getDatamemberHandleNameMap().insert(  std::make_pair( get_sourceFed_handle(), "sourceFed" )  );
	
	getDatamemberTypeMap().insert( std::make_pair("sourceFed", "String") );
	
	
	getDatamemberNameHandleMap().insert(  std::make_pair( "SimulationControl,originFed", get_originFed_handle() )  );
	
	getDatamemberHandleNameMap().insert(  std::make_pair( get_originFed_handle(), "originFed" )  );
	
	getDatamemberTypeMap().insert( std::make_pair("originFed", "String") );
	
	
	getDatamemberNameHandleMap().insert(  std::make_pair( "SimulationControl,actualLogicalGenerationTime", get_actualLogicalGenerationTime_handle() )  );
	
	getDatamemberHandleNameMap().insert(  std::make_pair( get_actualLogicalGenerationTime_handle(), "actualLogicalGenerationTime" )  );
	
	getDatamemberTypeMap().insert( std::make_pair("actualLogicalGenerationTime", "double") );
	
	
	getDatamemberNameHandleMap().insert(  std::make_pair( "SimulationControl,federateFilter", get_federateFilter_handle() )  );
	
	getDatamemberHandleNameMap().insert(  std::make_pair( get_federateFilter_handle(), "federateFilter" )  );
	
	getDatamemberTypeMap().insert( std::make_pair("federateFilter", "String") );
	

}

void SimulationControl::publish( RTI::RTIambassador *rti ) {
	if ( getIsPublished() ) {
		return;
	}

	init( rti );



	bool isNotPublished = true;
	while( isNotPublished ) {
		try {
			rti->publishInteractionClass( get_handle() );
			isNotPublished = false;
		} catch ( RTI::FederateNotExecutionMember & ) {
			std::cerr << getPublishErrorMessage() << "Federate Not Execution Member" << std::endl;
			return;
		} catch ( RTI::InteractionClassNotDefined & ) {
			std::cerr << getPublishErrorMessage() << "Interaction Class Not Defined" << std::endl;
			return;
		} catch ( ... ) {
			std::cerr << getPublishErrorMessage() << "Exception caught ... retry" << std::endl;
		}
	}

	getIsPublished() = true;
}

void SimulationControl::unpublish( RTI::RTIambassador *rti ) {
	if ( !getIsPublished() ) {
		return;
	}

	init( rti );

	bool isNotUnpublished = true;
	while( isNotUnpublished ) {
		try {
			rti->unpublishInteractionClass( get_handle() );
			isNotUnpublished = false;
		} catch ( RTI::FederateNotExecutionMember & ) {
			std::cerr << getUnpublishErrorMessage() + "Federate Not Execution Member" << std::endl;
			return;
		} catch ( RTI::InteractionClassNotDefined & ) {
			std::cerr << getUnpublishErrorMessage() + "Interaction Class Not Defined" << std::endl;
			return;
		} catch ( RTI::InteractionClassNotPublished & ) {
			std::cerr << getUnpublishErrorMessage() + "Interaction Class Not Published" << std::endl;
			return;
		} catch ( ... ) {
			std::cerr << getUnpublishErrorMessage() << "Exception caught ... retry" << std::endl;
		}
	}

	getIsPublished() = false;
}

void SimulationControl::subscribe( RTI::RTIambassador *rti ) {
	if ( getIsSubscribed() ) {
		return;
	}

	init( rti );

	
	bool isNotSubscribed = true;
	while( isNotSubscribed ) {
		try {
			rti->subscribeInteractionClass( get_handle() );
			isNotSubscribed = false;
		} catch ( RTI::FederateNotExecutionMember & ) {
			std::cerr << getSubscribeErrorMessage() << "Federate Not Execution Member" << std::endl;
			return;
		} catch ( RTI::InteractionClassNotDefined & ) {
			std::cerr << getSubscribeErrorMessage() << "Interaction Class Not Defined" << std::endl;
			return;
		} catch ( ... ) {
			std::cerr << getSubscribeErrorMessage() << "Exception caught ... retry" << std::endl;
		}
	}

	getIsSubscribed() = true;
}
	
void SimulationControl::unsubscribe( RTI::RTIambassador *rti ) {
	if ( !getIsSubscribed() ) {
		return;
	}

	init( rti );
	
	bool isNotUnsubscribed = true;
	while( isNotUnsubscribed ) {
		try {
			rti->unsubscribeInteractionClass( get_handle() );
			isNotUnsubscribed = false;
		} catch ( RTI::FederateNotExecutionMember & ) {
			std::cerr << getUnsubscribeErrorMessage() << "Federate Not Execution Member" << std::endl;
			return;
		} catch ( RTI::InteractionClassNotDefined & ) {
			std::cerr << getUnsubscribeErrorMessage() << "Interaction Class Not Defined" << std::endl;
			return;
		} catch ( RTI::InteractionClassNotSubscribed & ) {
			std::cerr << getUnsubscribeErrorMessage() << "Interaction Class Not Subscribed" << std::endl;
			return;
		} catch ( ... ) {
			std::cerr << getUnsubscribeErrorMessage() << "Exception caught ... retry" << std::endl;
		}
	}

	getIsSubscribed() = false;
}

bool SimulationControl::static_init( void ) {
	static bool isInitialized = false;
	if ( isInitialized ) {
		return true;
	}
	isInitialized = true;
	
	getClassNameSet().insert( "SimulationControl" );
	
	getClassNameFactoryMap().insert(  std::make_pair( "SimulationControl", &SimulationControl::factory )  );
	getClassNamePublishMap().insert(   std::make_pair(  "SimulationControl", (PubsubFunctionPtr)( &SimulationControl::publish )  )   );
	getClassNameUnpublishMap().insert(   std::make_pair(  "SimulationControl", (PubsubFunctionPtr)( &SimulationControl::unpublish )  )   );
	getClassNameSubscribeMap().insert(   std::make_pair(  "SimulationControl", (PubsubFunctionPtr)( &SimulationControl::subscribe )  )   );
	getClassNameUnsubscribeMap().insert(   std::make_pair(  "SimulationControl", (PubsubFunctionPtr)( &SimulationControl::unsubscribe )  )   );

	getDatamemberClassNameVectorPtrMap().insert(  std::make_pair( "SimulationControl", &getDatamemberNames() )  );
	getAllDatamemberClassNameVectorPtrMap().insert(  std::make_pair( "SimulationControl", &getAllDatamemberNames() )  );
	
	
	
	getDatamemberNames().push_back( "sourceFed" );
	getDatamemberNames().push_back( "originFed" );
	getDatamemberNames().push_back( "actualLogicalGenerationTime" );
	getDatamemberNames().push_back( "federateFilter" );
	
	
	getAllDatamemberNames().push_back( "sourceFed" );
	getAllDatamemberNames().push_back( "originFed" );
	getAllDatamemberNames().push_back( "actualLogicalGenerationTime" );
	getAllDatamemberNames().push_back( "federateFilter" );



	return true;
}

std::ostream &operator<<( std::ostream &os, SimulationControl::SP entitySP ) {
	return os << *entitySP;
}
std::ostream &operator<<( std::ostream &os, const SimulationControl &entity ) {
	return os << "SimulationControl("  << "sourceFed:" << entity.get_sourceFed() << ", " << "originFed:" << entity.get_originFed() << ", " << "actualLogicalGenerationTime:" << entity.get_actualLogicalGenerationTime() << ", " << "federateFilter:" << entity.get_federateFilter()	<< ")";
}





SimulationControl::ParameterHandleValuePairSetSP SimulationControl::createDatamemberHandleValuePairSet( RTI::ULong count ) {
	ParameterHandleValuePairSetSP datamembers = Super::createDatamemberHandleValuePairSet( count + 4 );

	std::string stringConversion;
		

	
	
	stringConversion = static_cast< std::string >(  TypeMedley( get_sourceFed() )  );
	datamembers->add( get_sourceFed_handle(), stringConversion.c_str(), stringConversion.size() );
	
	stringConversion = static_cast< std::string >(  TypeMedley( get_originFed() )  );
	datamembers->add( get_originFed_handle(), stringConversion.c_str(), stringConversion.size() );
	
	stringConversion = static_cast< std::string >(  TypeMedley( get_actualLogicalGenerationTime() )  );
	datamembers->add( get_actualLogicalGenerationTime_handle(), stringConversion.c_str(), stringConversion.size() );
	
	stringConversion = static_cast< std::string >(  TypeMedley( get_federateFilter() )  );
	datamembers->add( get_federateFilter_handle(), stringConversion.c_str(), stringConversion.size() );
	

	return datamembers;
}

