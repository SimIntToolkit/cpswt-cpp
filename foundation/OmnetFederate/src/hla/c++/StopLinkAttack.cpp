
// This code has been generated by the C2W code generator.
// Do not edit manually!

#include "StopLinkAttack.hpp"




void StopLinkAttack::init( RTI::RTIambassador *rti ) {
	static bool isInitialized = false;
	if ( isInitialized ) {
		return;
	}
	isInitialized = true;

	AttacksNotYetImplemented::init( rti );

	bool isNotInitialized = true;
	while( isNotInitialized ) {
		try {
			getHandle() = rti->getInteractionClassHandle( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StopLinkAttack" );
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

	getClassNameHandleMap().insert(  std::make_pair( "StopLinkAttack", get_handle() )  );
	getClassHandleNameMap().insert(  std::make_pair( get_handle(), "StopLinkAttack" )  );


	isNotInitialized = true;
	while( isNotInitialized ) {
		try {		
			
			
			get_toHost_handle_var() = rti->getParameterHandle( "toHost", get_handle() );
			get_fromHost_handle_var() = rti->getParameterHandle( "fromHost", get_handle() );
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
	
	
	getDatamemberNameHandleMap().insert(  std::make_pair( "StopLinkAttack,toHost", get_toHost_handle() )  );
	
	getDatamemberHandleNameMap().insert(  std::make_pair( get_toHost_handle(), "toHost" )  );
	
	getDatamemberTypeMap().insert( std::make_pair("toHost", "String") );
	
	
	getDatamemberNameHandleMap().insert(  std::make_pair( "StopLinkAttack,fromHost", get_fromHost_handle() )  );
	
	getDatamemberHandleNameMap().insert(  std::make_pair( get_fromHost_handle(), "fromHost" )  );
	
	getDatamemberTypeMap().insert( std::make_pair("fromHost", "String") );
	

}

void StopLinkAttack::publish( RTI::RTIambassador *rti ) {
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

void StopLinkAttack::unpublish( RTI::RTIambassador *rti ) {
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

void StopLinkAttack::subscribe( RTI::RTIambassador *rti ) {
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
	
void StopLinkAttack::unsubscribe( RTI::RTIambassador *rti ) {
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

bool StopLinkAttack::static_init( void ) {
	static bool isInitialized = false;
	if ( isInitialized ) {
		return true;
	}
	isInitialized = true;
	
	getClassNameSet().insert( "StopLinkAttack" );
	
	getClassNameFactoryMap().insert(  std::make_pair( "StopLinkAttack", &StopLinkAttack::factory )  );
	getClassNamePublishMap().insert(   std::make_pair(  "StopLinkAttack", (PubsubFunctionPtr)( &StopLinkAttack::publish )  )   );
	getClassNameUnpublishMap().insert(   std::make_pair(  "StopLinkAttack", (PubsubFunctionPtr)( &StopLinkAttack::unpublish )  )   );
	getClassNameSubscribeMap().insert(   std::make_pair(  "StopLinkAttack", (PubsubFunctionPtr)( &StopLinkAttack::subscribe )  )   );
	getClassNameUnsubscribeMap().insert(   std::make_pair(  "StopLinkAttack", (PubsubFunctionPtr)( &StopLinkAttack::unsubscribe )  )   );

	getDatamemberClassNameVectorPtrMap().insert(  std::make_pair( "StopLinkAttack", &getDatamemberNames() )  );
	getAllDatamemberClassNameVectorPtrMap().insert(  std::make_pair( "StopLinkAttack", &getAllDatamemberNames() )  );
	
	
	
	getDatamemberNames().push_back( "toHost" );
	getDatamemberNames().push_back( "fromHost" );
	
	
	getAllDatamemberNames().push_back( "toHost" );
	getAllDatamemberNames().push_back( "fromHost" );



	return true;
}

std::ostream &operator<<( std::ostream &os, StopLinkAttack::SP entitySP ) {
	return os << *entitySP;
}
std::ostream &operator<<( std::ostream &os, const StopLinkAttack &entity ) {
	return os << "StopLinkAttack("  << "toHost:" << entity.get_toHost() << ", " << "sourceFed:" << entity.get_sourceFed() << ", " << "uniqueCommandID:" << entity.get_uniqueCommandID() << ", " << "fromHost:" << entity.get_fromHost() << ", " << "originFed:" << entity.get_originFed() << ", " << "federateFilter:" << entity.get_federateFilter() << ", " << "actualLogicalGenerationTime:" << entity.get_actualLogicalGenerationTime()	<< ")";
}





StopLinkAttack::ParameterHandleValuePairSetSP StopLinkAttack::createDatamemberHandleValuePairSet( RTI::ULong count ) {
	ParameterHandleValuePairSetSP datamembers = Super::createDatamemberHandleValuePairSet( count + 2 );

	std::string stringConversion;
		

	
	
	stringConversion = static_cast< std::string >(  TypeMedley( get_toHost() )  );
	datamembers->add( get_toHost_handle(), stringConversion.c_str(), stringConversion.size() );
	
	stringConversion = static_cast< std::string >(  TypeMedley( get_fromHost() )  );
	datamembers->add( get_fromHost_handle(), stringConversion.c_str(), stringConversion.size() );
	

	return datamembers;
}

