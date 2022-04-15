
// This code has been generated by the C2W code generator.
// Do not edit manually!

#include "StartNetworkFilterAttack.hpp"




void StartNetworkFilterAttack::init( RTI::RTIambassador *rti ) {
	static bool isInitialized = false;
	if ( isInitialized ) {
		return;
	}
	isInitialized = true;

	OmnetCommand::init( rti );

	bool isNotInitialized = true;
	while( isNotInitialized ) {
		try {
			getHandle() = rti->getInteractionClassHandle( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartNetworkFilterAttack" );
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

	getClassNameHandleMap().insert(  std::make_pair( "StartNetworkFilterAttack", get_handle() )  );
	getClassHandleNameMap().insert(  std::make_pair( get_handle(), "StartNetworkFilterAttack" )  );


	isNotInitialized = true;
	while( isNotInitialized ) {
		try {		
			
			
			get_dstNetworkAddress_handle_var() = rti->getParameterHandle( "dstNetworkAddress", get_handle() );
			get_srcNetworkAddress_handle_var() = rti->getParameterHandle( "srcNetworkAddress", get_handle() );
			get_nodeFullPath_handle_var() = rti->getParameterHandle( "nodeFullPath", get_handle() );
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
	
	
	getDatamemberNameHandleMap().insert(  std::make_pair( "StartNetworkFilterAttack,dstNetworkAddress", get_dstNetworkAddress_handle() )  );
	
	getDatamemberHandleNameMap().insert(  std::make_pair( get_dstNetworkAddress_handle(), "dstNetworkAddress" )  );
	
	getDatamemberTypeMap().insert( std::make_pair("dstNetworkAddress", "String") );
	
	
	getDatamemberNameHandleMap().insert(  std::make_pair( "StartNetworkFilterAttack,srcNetworkAddress", get_srcNetworkAddress_handle() )  );
	
	getDatamemberHandleNameMap().insert(  std::make_pair( get_srcNetworkAddress_handle(), "srcNetworkAddress" )  );
	
	getDatamemberTypeMap().insert( std::make_pair("srcNetworkAddress", "String") );
	
	
	getDatamemberNameHandleMap().insert(  std::make_pair( "StartNetworkFilterAttack,nodeFullPath", get_nodeFullPath_handle() )  );
	
	getDatamemberHandleNameMap().insert(  std::make_pair( get_nodeFullPath_handle(), "nodeFullPath" )  );
	
	getDatamemberTypeMap().insert( std::make_pair("nodeFullPath", "String") );
	

}

void StartNetworkFilterAttack::publish( RTI::RTIambassador *rti ) {
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

void StartNetworkFilterAttack::unpublish( RTI::RTIambassador *rti ) {
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

void StartNetworkFilterAttack::subscribe( RTI::RTIambassador *rti ) {
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
	
void StartNetworkFilterAttack::unsubscribe( RTI::RTIambassador *rti ) {
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

bool StartNetworkFilterAttack::static_init( void ) {
	static bool isInitialized = false;
	if ( isInitialized ) {
		return true;
	}
	isInitialized = true;
	
	getClassNameSet().insert( "StartNetworkFilterAttack" );
	
	getClassNameFactoryMap().insert(  std::make_pair( "StartNetworkFilterAttack", &StartNetworkFilterAttack::factory )  );
	getClassNamePublishMap().insert(   std::make_pair(  "StartNetworkFilterAttack", (PubsubFunctionPtr)( &StartNetworkFilterAttack::publish )  )   );
	getClassNameUnpublishMap().insert(   std::make_pair(  "StartNetworkFilterAttack", (PubsubFunctionPtr)( &StartNetworkFilterAttack::unpublish )  )   );
	getClassNameSubscribeMap().insert(   std::make_pair(  "StartNetworkFilterAttack", (PubsubFunctionPtr)( &StartNetworkFilterAttack::subscribe )  )   );
	getClassNameUnsubscribeMap().insert(   std::make_pair(  "StartNetworkFilterAttack", (PubsubFunctionPtr)( &StartNetworkFilterAttack::unsubscribe )  )   );

	getDatamemberClassNameVectorPtrMap().insert(  std::make_pair( "StartNetworkFilterAttack", &getDatamemberNames() )  );
	getAllDatamemberClassNameVectorPtrMap().insert(  std::make_pair( "StartNetworkFilterAttack", &getAllDatamemberNames() )  );
	
	
	
	getDatamemberNames().push_back( "dstNetworkAddress" );
	getDatamemberNames().push_back( "srcNetworkAddress" );
	getDatamemberNames().push_back( "nodeFullPath" );
	
	
	getAllDatamemberNames().push_back( "dstNetworkAddress" );
	getAllDatamemberNames().push_back( "srcNetworkAddress" );
	getAllDatamemberNames().push_back( "nodeFullPath" );



	return true;
}

std::ostream &operator<<( std::ostream &os, StartNetworkFilterAttack::SP entitySP ) {
	return os << *entitySP;
}
std::ostream &operator<<( std::ostream &os, const StartNetworkFilterAttack &entity ) {
	return os << "StartNetworkFilterAttack("  << "dstNetworkAddress:" << entity.get_dstNetworkAddress() << ", " << "srcNetworkAddress:" << entity.get_srcNetworkAddress() << ", " << "sourceFed:" << entity.get_sourceFed() << ", " << "uniqueCommandID:" << entity.get_uniqueCommandID() << ", " << "nodeFullPath:" << entity.get_nodeFullPath() << ", " << "originFed:" << entity.get_originFed() << ", " << "federateFilter:" << entity.get_federateFilter() << ", " << "actualLogicalGenerationTime:" << entity.get_actualLogicalGenerationTime()	<< ")";
}





StartNetworkFilterAttack::ParameterHandleValuePairSetSP StartNetworkFilterAttack::createDatamemberHandleValuePairSet( RTI::ULong count ) {
	ParameterHandleValuePairSetSP datamembers = Super::createDatamemberHandleValuePairSet( count + 3 );

	std::string stringConversion;
		

	
	
	stringConversion = static_cast< std::string >(  TypeMedley( get_dstNetworkAddress() )  );
	datamembers->add( get_dstNetworkAddress_handle(), stringConversion.c_str(), stringConversion.size() );
	
	stringConversion = static_cast< std::string >(  TypeMedley( get_srcNetworkAddress() )  );
	datamembers->add( get_srcNetworkAddress_handle(), stringConversion.c_str(), stringConversion.size() );
	
	stringConversion = static_cast< std::string >(  TypeMedley( get_nodeFullPath() )  );
	datamembers->add( get_nodeFullPath_handle(), stringConversion.c_str(), stringConversion.size() );
	

	return datamembers;
}

