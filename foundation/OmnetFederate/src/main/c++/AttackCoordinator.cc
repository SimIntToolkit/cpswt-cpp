/*
 * AttackCoordinator.cc
 *
 *  Created on: Aug 4, 2021
 *      Author: ninehs (hnine999)
 */

#include <boost/regex.hpp>

#include "AttackCoordinator.h"


void AttackCoordinator::NetworkAddress::initFromString( std::string networkAddressSpec ) {

    // PATTERN FOR MATCHING A NETWORK ADDRESS
    static boost::regex networkIdPattern( "(\\d{1,3})\\.(\\d{1,3}).(\\d{1,3}).(\\d{1,3})/(\\d{1,2})" );
    static boost::regex whitespacePattern( "\\s" );
    //
    networkAddressSpec = boost::regex_replace( networkAddressSpec, whitespacePattern, "" );
    const std::string &constNetworkAddressSpec = networkAddressSpec;

    boost::match_results< std::string::const_iterator > results;
    if (  !regex_match( constNetworkAddressSpec.begin(), constNetworkAddressSpec.end(), results, networkIdPattern )  ) {
        return;
    }

    _networkIPAddress = 0;
    for( int ix = 1 ; ix <= 4 ; ++ix ) {
        _networkIPAddress <<= 8;
        int byte = boost::lexical_cast< unsigned int >(  std::string( results[ ix ].first, results[ ix ].second )  );
        _networkIPAddress |= byte;
    }

    int bits = boost::lexical_cast< unsigned int >(  std::string( results[ 5 ].first, results[ 5 ].second )  );
    _netMask = bits == 0 ? 0 : ~(  ( 1UL << (32 - bits) ) - 1  );

    truncateIPAddress();

}

bool AttackCoordinator::NetworkAddressComparator::operator()( const NetworkAddress &networkAddress1, const NetworkAddress &networkAddress2 ) {
    if ( networkAddress1.getNetworkIPAddress() < networkAddress2.getNetworkIPAddress() ) {
        return true;
    }
    if ( networkAddress1.getNetworkIPAddress() > networkAddress2.getNetworkIPAddress() ) {
        return false;
    }

    if ( networkAddress1.getNetMask() < networkAddress2.getNetMask() ) {
        return true;
    }
    return false;
}

std::string AttackCoordinator::listIPModuleProperties( void ) {
    std::string retval;
    for(
     HostNameIPModulePropertiesMap::iterator himItr = _hostNameIPModulePropertiesMap.begin() ; himItr != _hostNameIPModulePropertiesMap.end() ; ++himItr
    ) {
        retval += himItr->first + ":\n";
        IPModuleProperties &ipModuleProperties = himItr->second;
        retval += "\tModule address: " + boost::lexical_cast< std::string >( ipModuleProperties.getCModule() ) + "\n";
        retval += "\tIPAddresses:\n";
        InterfaceIPAddressMap interfaceIPAddressMap = ipModuleProperties.getInterfaceIPAddressMap();
        for( InterfaceIPAddressMap::iterator iimItr = interfaceIPAddressMap.begin() ; iimItr != interfaceIPAddressMap.end() ; ++iimItr ) {
            retval += "\t\t" + iimItr->first + ":\t" + iimItr->second.str() + "\n";
        }
    }
    return retval;
}

std::string AttackCoordinator::listIPModuleNetworks( void ) {
    std::string retval;

    for( NetworkAddressCModuleSetMap::iterator ncmItr = _networkAddressCModuleSetMap.begin() ; ncmItr != _networkAddressCModuleSetMap.end() ; ++ncmItr ) {
        retval += "Hosts in network " + boost::lexical_cast< std::string >( ncmItr->first ) + ":\n";
        CModuleSet &cModuleSet = ncmItr->second;
        for( CModuleSet::const_iterator cmsCit = cModuleSet.begin() ; cmsCit != cModuleSet.end() ; ++cmsCit ) {
            CPSWTIpv4 *c2wipv4 = static_cast< CPSWTIpv4 * >( *cmsCit );
            retval += "\t" + c2wipv4->getHostFullName() + "\n";
        }
        retval += "\n";
    }

    return retval;
}

std::string AttackCoordinator::listAppSpecProperties( void ) {
    std::string retval;
    for( AppSpecPropertiesMap::iterator apmItr = _appSpecPropertiesMap.begin() ; apmItr != _appSpecPropertiesMap.end() ; ++apmItr ) {
        retval += apmItr->first.getSpec() + ":\n";
        retval += "\tIPAddresses:\n";
        AppProperties &appProperties = apmItr->second;
        InterfaceIPAddressMap interfaceIPAddressMap = appProperties.getInterfaceIPAddressMap();
        for( InterfaceIPAddressMap::iterator iimItr = interfaceIPAddressMap.begin() ; iimItr != interfaceIPAddressMap.end() ; ++iimItr ) {
            retval += "\t\t" + iimItr->first + ":\t" + iimItr->second.str() + "\n";
        }
        retval += "\tPort: " + boost::lexical_cast< std::string >( appProperties.getPort() ) + "\n\n";
    }
    return retval;
}

std::ostream &operator<<( std::ostream &os, const AttackCoordinator::NetworkAddress &networkAddress ) {
    std::string output;

    unsigned int networkIPAddress = networkAddress.getNetworkIPAddress();
    bool first = true;
    for( int ix = 0 ; ix < 4 ; ++ix ) {
        if ( first ) {
            first = false;
        } else {
            output = "." + output;
        }
        unsigned int byte = networkIPAddress & 0xFF;
        output = boost::lexical_cast< std::string >( byte ) + output;
        networkIPAddress >>= 8;
    }

    unsigned int netMask = networkAddress.getNetMask();
    int bits = AttackCoordinator::NetworkAddress::countBits( netMask );
    if ( bits != 32 ) {
        output += "/" + boost::lexical_cast< std::string >( bits );
    }

    os << output;
    return os;
}

std::ostream &operator<<( std::ostream &os, const AttackCoordinator::AppSpec &appSpec ) {
    os << appSpec.getSpec();
    return os;
}

std::ostream &operator<<( std::ostream &os, const AttackCoordinator::RouteEntry &routeEntry ) {
    os << "RouteEntry( nodeName:" << routeEntry.get_nodeName() << ", interfaceEntry:" << routeEntry.get_interfaceEntry() <<
     ", networkAddress:" << routeEntry.get_networkAddress() << ", gateway:" << routeEntry.get_gatewayAddress() << ")";
    return os;
}

std::ostream &operator<<( std::ostream &os, const AttackCoordinator::RouteEntrySP &routeEntrySP ) {
    return os << *routeEntrySP;
}
