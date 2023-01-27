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

#ifndef INCLUDE_ATTACKCOORDINATOR_H_
#define INCLUDE_ATTACKCOORDINATOR_H_

#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

#include <omnetpp/cmodule.h>
#include <inet/networklayer/ipv4/Ipv4Route.h>

class AttackCoordinator {

public:
    static int getUniqueNo( void ) {
        static int uniqueNo = -1;
        return ++uniqueNo;
    }

    static AttackCoordinator &getSingleton(void) {
        static AttackCoordinator attackCoordinator;
        return attackCoordinator;
    }

    AttackCoordinator(void) { }

    //
    // NetworkAddress CLASS -- FOR MANAGING NETWORK ADDRESSES
    // THIS CLASS IS USED FOR:
    //   NETWORK ATTACKS
    //   REPLAY ATTACKS
    //   OUT-OF-ORDER-PACKET ATTACKS
    //
    class NetworkAddress {
    private:
        unsigned int _networkIPAddress;
        unsigned int _netMask;

        void truncateIPAddress( void ) {
            _networkIPAddress &= _netMask;
        }

    public:
        static int countBits( unsigned int number ) {
            int count = 0;
            while( number ) {
                if ( number & 1U ) ++count;
                number >>= 1;
            }
            return count;
        }

        NetworkAddress( void ) : _networkIPAddress( 0 ), _netMask( 2 ) { }
        NetworkAddress( unsigned int networkIPAddress, unsigned int netMask ) : _networkIPAddress( networkIPAddress ), _netMask( netMask ) {
            truncateIPAddress();
        }

    private:
        void initFromString( std::string networkAddressSpec );

    public:
        NetworkAddress( const char *networkAddressSpec ) : _networkIPAddress( 0 ), _netMask( 2 ) {
            initFromString(  std::string( networkAddressSpec )  );
        }
        NetworkAddress( const std::string &networkAddressSpec ) : _networkIPAddress( 0 ), _netMask( 2 ) {
            initFromString( networkAddressSpec );
        }

        NetworkAddress( const inet::Ipv4Address &ipAddress ) : _networkIPAddress( ipAddress.getInt() ), _netMask( ipAddress.getNetworkMask().getInt() ) {
            truncateIPAddress();
        }
        NetworkAddress( const inet::Ipv4Address *ipAddress ) : _networkIPAddress( ipAddress->getInt() ), _netMask( ipAddress->getNetworkMask().getInt() ) {
            truncateIPAddress();
        }
        NetworkAddress( const inet::Ipv4Address &hostIPAddress, const inet::Ipv4Address &netmaskIPAddress) :
         _networkIPAddress( hostIPAddress.getInt() ), _netMask( netmaskIPAddress.getInt() ) {
            truncateIPAddress();
        }
        NetworkAddress( const inet::Ipv4Address *hostIPAddress, const inet::Ipv4Address *netmaskIPAddress) :
         _networkIPAddress( hostIPAddress->getInt() ), _netMask( netmaskIPAddress->getInt() ) {
            truncateIPAddress();
        }

        NetworkAddress( const inet::Ipv4Route *ipRoute ) : _networkIPAddress( ipRoute->getDestination().getInt() ), _netMask( ipRoute->getNetmask().getInt() ) {
            truncateIPAddress();
        }

        void setNetworkIPAddress( unsigned int networkIPAddress ) { _networkIPAddress = networkIPAddress; }
        void setNetMask( unsigned int netMask ) { _netMask = netMask; }

        unsigned int getNetworkIPAddress( void ) const { return _networkIPAddress; }
        unsigned int getNetMask( void ) const { return _netMask; }

        bool isValid( void ) const {
            unsigned long bit = ~getNetMask() + 1;
            return countBits( bit ) == 1;
        }

        bool matches( unsigned int ipAddress ) const {
            ipAddress &= _netMask;
            return ipAddress == _networkIPAddress;
        }

        bool matches( const inet::Ipv4Address &ipAddress ) const {
            return matches( ipAddress.getInt() );
        }

    };


    struct NetworkAddressComparator {
        bool operator()( const NetworkAddress &networkAddress1, const NetworkAddress &networkAddress2 );
    };


    typedef std::set< NetworkAddress, NetworkAddressComparator > NetworkAddressSet;

    typedef std::set< omnetpp::cModule * > CModuleSet;

    typedef std::map< NetworkAddress, CModuleSet, NetworkAddressComparator > NetworkAddressCModuleSetMap;

    typedef std::map< std::string, inet::Ipv4Address > InterfaceIPAddressMap;


    class IPModuleProperties {
    public:

    private:
        omnetpp::cModule *_cModule;
        InterfaceIPAddressMap _interfaceIPAddressMap;

    public:
        IPModuleProperties( void ) : _cModule( nullptr ) { }
        IPModuleProperties( omnetpp::cModule *cModule_var ) : _cModule( cModule_var ) { }

        omnetpp::cModule *getCModule( void ) {
            return _cModule;
        }
        inet::Ipv4Address getIPAddress( const std::string &interfaceName ) {
            InterfaceIPAddressMap::iterator iimItr = _interfaceIPAddressMap.find( interfaceName );
            return iimItr == _interfaceIPAddressMap.end() ? inet::Ipv4Address(  static_cast< uint32_t >( 0 )  ) : iimItr->second;
        }
        InterfaceIPAddressMap &getInterfaceIPAddressMap( void ) {
            return _interfaceIPAddressMap;
        }

        void setCModule( omnetpp::cModule *cModule_var ) {
            _cModule = cModule_var;
        }
        void setInterfaceIPAddress( const std::string &interfaceName, const inet::Ipv4Address &ipAddress ) {
            _interfaceIPAddressMap[ interfaceName ] = ipAddress;
        }
    };


    typedef std::string HostName;

    typedef std::map< HostName, IPModuleProperties > HostNameIPModulePropertiesMap;


private:
    HostNameIPModulePropertiesMap _hostNameIPModulePropertiesMap;
    NetworkAddressCModuleSetMap _networkAddressCModuleSetMap;
    NetworkAddressSet _attackedNetworkAddressSet;


public:
    void registerIPModule( const HostName &hostName, omnetpp::cModule *module ) {
        _hostNameIPModulePropertiesMap.insert(   std::make_pair(  hostName, IPModuleProperties( module )  )   );
    }

    omnetpp::cModule *getIPModule( const HostName &hostName ) {
        HostNameIPModulePropertiesMap::iterator himItr = _hostNameIPModulePropertiesMap.find( hostName );
        return himItr == _hostNameIPModulePropertiesMap.end() ? (omnetpp::cModule *)0 : himItr->second.getCModule();
    }

    inet::Ipv4Address getIPAddress( const HostName &hostName, const std::string &interfaceName ) {
        HostNameIPModulePropertiesMap::iterator himItr = _hostNameIPModulePropertiesMap.find( hostName );
        return himItr->second.getIPAddress( interfaceName );
    }

    InterfaceIPAddressMap &getIPModuleInterfaceIPAddressMap( const HostName &hostName ) {
        return _hostNameIPModulePropertiesMap[ hostName ].getInterfaceIPAddressMap();
    }

    std::string listIPModuleProperties( void );

    void registerIPModuleNetworks( omnetpp::cModule *module, const NetworkAddressSet &networkAddressSet ) {
        for( NetworkAddressSet::const_iterator nasCit = networkAddressSet.begin() ; nasCit != networkAddressSet.end() ; ++nasCit ) {
            _networkAddressCModuleSetMap[ *nasCit ].insert( module );
        }
    }

    void unregisterIPModuleNetworks( omnetpp::cModule *module, const NetworkAddressSet &networkAddressSet ) {
        for( NetworkAddressSet::const_iterator nasCit = networkAddressSet.begin() ; nasCit != networkAddressSet.end() ; ++nasCit ) {
            _networkAddressCModuleSetMap[ *nasCit ].erase( module );
        }
    }

    const CModuleSet &getCModuleSet(const NetworkAddress networkAddress) {

        static CModuleSet emptyCModuleSet;

        NetworkAddressCModuleSetMap::iterator ncmItr = _networkAddressCModuleSetMap.find( networkAddress );
        return ncmItr == _networkAddressCModuleSetMap.end() ? emptyCModuleSet : ncmItr->second;
    }

    std::string listIPModuleNetworks( void );


    class AppSpec {
    private:
        std::string _hostName;
        std::string _appName;
        int _appIndex;

    public:
        AppSpec( void ) { }
        AppSpec( const std::string &hostName, const std::string &appName, int appIndex ) :
         _hostName( hostName ), _appName( appName ), _appIndex( appIndex ) { }

        const std::string &getHostName( void ) const {
            return _hostName;
        }
        const std::string &getAppName( void ) const {
            return _appName;
        }
        int getAppIndex( void ) const {
            return _appIndex;
        }

        void setHostName( const std::string &hostName ) {
            _hostName = hostName;
        }
        void setAppName( const std::string &appName ) {
            _appName = appName;
        }
        void setAppIndex( int appIndex ) {
            _appIndex = appIndex;
        }

        std::string getSpec( void ) const {
            return _hostName + "." + _appName + "[" + boost::lexical_cast< std::string >( _appIndex ) + "]";
        }
    };


    struct AppSpecComparator {
        bool operator()( const AppSpec &appSpec1, const AppSpec &appSpec2 ) {
            return appSpec1.getSpec() < appSpec2.getSpec();
        }
    };


    class AppProperties {
    private:
        omnetpp::cModule *_cModule;
        InterfaceIPAddressMap _interfaceIPAddressMap;
        int _port;

    public:
        AppProperties( void ) : _cModule( 0 ), _port( -1 ) { }
        AppProperties( omnetpp::cModule *cModule_var, int port ) : _cModule( cModule_var ), _port( port ) { }

        omnetpp::cModule *getCModule( void ) {
            return _cModule;
        }
        inet::Ipv4Address getIPAddress( const std::string &interfaceName ) {
            InterfaceIPAddressMap::iterator iimItr = _interfaceIPAddressMap.find( interfaceName );
            return iimItr == _interfaceIPAddressMap.end() ? inet::Ipv4Address(  static_cast< uint32_t >( 0 )  ) : iimItr->second;
        }
        InterfaceIPAddressMap &getInterfaceIPAddressMap( void ) {
            return _interfaceIPAddressMap;
        }
        int getPort( void ) {
            return _port;
        }

        void setCModule( omnetpp::cModule *cModule_var ) {
            _cModule = cModule_var;
        }
        void setInterfaceIPAddress( const std::string &interfaceName, const inet::Ipv4Address &ipAddress ) {
            _interfaceIPAddressMap[ interfaceName ] = ipAddress;
        }
        void setPort( int port ) {
            _port = port;
        }
    };


    typedef std::map< AppSpec, AppProperties, AppSpecComparator > AppSpecPropertiesMap;


private:
    AppSpecPropertiesMap _appSpecPropertiesMap;


public:
    void registerAppSpecProperties( const HostName &hostName, const std::string &appName, int appIndex, omnetpp::cModule *cModule_var, int port ) {
        _appSpecPropertiesMap.insert(   std::make_pair(  AppSpec( hostName, appName, appIndex ), AppProperties( cModule_var, port )  )   );
    }

    omnetpp::cModule *getAppSpecModule( const AppSpec &appSpec  ) {
        AppSpecPropertiesMap::iterator apmItr = _appSpecPropertiesMap.find( appSpec );
        return apmItr == _appSpecPropertiesMap.end() ? (omnetpp::cModule *)0 : apmItr->second.getCModule();
    }
    omnetpp::cModule *getAppSpecModule( const HostName &hostName, const std::string &appName, int appIndex ) {
        return getAppSpecModule(  AppSpec( hostName, appName, appIndex )  );
    }

    InterfaceIPAddressMap &getAppInterfaceIPAddressMap( const AppSpec &appSpec ) {
        return _appSpecPropertiesMap[ appSpec ].getInterfaceIPAddressMap();
    }
    InterfaceIPAddressMap &getAppInterfaceIPAddressMap( const HostName &hostName, const std::string &appName, int appIndex ) {
        return getAppInterfaceIPAddressMap(  AppSpec( hostName, appName, appIndex )  );
    }

    inet::Ipv4Address getAppSpecIPAddress( const AppSpec &appSpec, const std::string &interfaceName ) {
        AppSpecPropertiesMap::iterator apmItr = _appSpecPropertiesMap.find( appSpec );
        return apmItr == _appSpecPropertiesMap.end() ? inet::Ipv4Address(  static_cast< uint32_t >( 0 )  ) : apmItr->second.getIPAddress( interfaceName );
    }
    inet::Ipv4Address getAppSpecIPAddress( const HostName &hostName, const std::string &appName, int appIndex, const std::string &interfaceName ) {
        return getAppSpecIPAddress(  AppSpec( hostName, appName, appIndex ), interfaceName  );
    }

    void setAppSpecIPAddress( const AppSpec &appSpec, const std::string &interfaceName, const inet::Ipv4Address &ipAddress ) {
        _appSpecPropertiesMap[ appSpec ].setInterfaceIPAddress( interfaceName, ipAddress );
    }
    void setAppSpecIPAddress( const HostName &hostName, const std::string &appName, int appIndex, const std::string &interfaceName, const inet::Ipv4Address &ipAddress ) {
        setAppSpecIPAddress(  AppSpec( hostName, appName, appIndex ), interfaceName, ipAddress  );
    }

    int getAppSpecPort( const AppSpec &appSpec ) {
        AppSpecPropertiesMap::iterator apmItr = _appSpecPropertiesMap.find( appSpec );
        return apmItr == _appSpecPropertiesMap.end() ? -1 : apmItr->second.getPort();
    }
    int getAppSpecPort( const HostName &hostName, const std::string &appName, int appIndex ) {
        return getAppSpecPort(  AppSpec( hostName, appName, appIndex )  );
    }

    AppProperties &getAppSpecProperties( const AppSpec &appSpec ) {
        return _appSpecPropertiesMap[ appSpec ];
    }
    AppProperties &getAppSpecProperties( const HostName &hostName, const std::string &appName, int appIndex  ) {
        return getAppSpecProperties(  AppSpec( hostName, appName, appIndex )  );
    }

    std::string listAppSpecProperties( void );


    class RouteEntry {

    private:
        std::string _nodeName;
        std::string _interfaceEntry;
        NetworkAddress _networkAddress;
        NetworkAddress _gatewayAddress;
        RouteEntry( void ) { };

    public:
        RouteEntry( const std::string& nodeName,
                    const std::string& interfaceEntry,
                    const NetworkAddress& networkAddressSpec,
                    const NetworkAddress& gatewayAddressSpec
                  ) : _nodeName( nodeName), _interfaceEntry( interfaceEntry ),
                      _networkAddress(  NetworkAddress( networkAddressSpec )  ),
                      _gatewayAddress(  NetworkAddress( gatewayAddressSpec )  ) { }

        std::string get_nodeName( void ) const { return _nodeName; }
        std::string get_interfaceEntry( void ) const { return _interfaceEntry; }
        NetworkAddress get_networkAddress( void ) const { return _networkAddress; }
        NetworkAddress get_gatewayAddress( void ) const { return _gatewayAddress; }
    };

    typedef boost::shared_ptr< RouteEntry > RouteEntrySP;

    RouteEntrySP createRouteEntrySP(
     const std::string &nodeName, const std::string &interfaceEntry, const NetworkAddress &networkAddress, const NetworkAddress &gatewayAddress
    ) {
        return RouteEntrySP(  new RouteEntry( nodeName, interfaceEntry, networkAddress, gatewayAddress )  );
    }


    class IntegrityAttackParams {
    private:
        int _intMultiplier;
        int _intAdder;
        long _longMultiplier;
        long _longAdder;
        double _doubleMultiplier;
        double _doubleAdder;
        bool _booleanEnableFlip;
        std::string _stringReplacement;

    public:
        IntegrityAttackParams( void ) : _intMultiplier(1), _intAdder(0), _longMultiplier(1), _longAdder(0), _doubleMultiplier(1.0), _doubleAdder(0.0), _booleanEnableFlip(false), _stringReplacement("") { }
        IntegrityAttackParams( int intMultiplier, int intAdder, long longMultiplier, long longAdder, double doubleMultiplier, double doubleAdder, bool booleanEnableFlip, const std::string &stringReplacement ) : _intMultiplier(intMultiplier), _intAdder(intAdder), _longMultiplier(longMultiplier), _longAdder(longAdder), _doubleMultiplier(doubleMultiplier), _doubleAdder(doubleAdder), _booleanEnableFlip(booleanEnableFlip), _stringReplacement(stringReplacement) { }

        int getIntMultiplier( void ) {
            return _intMultiplier;
        }
        int getIntAdder( void ) {
            return _intAdder;
        }
        long getLongMultiplier( void ) {
            return _longMultiplier;
        }
        long getLongAdder( void ) {
            return _longAdder;
        }
        double getDoubleMultiplier( void ) {
            return _doubleMultiplier;
        }
        double getDoubleAdder( void ) {
            return _doubleAdder;
        }
        bool getBooleanEnableFlip( void ) {
            return _booleanEnableFlip;
        }
        const std::string &getStringReplacement( void ) const {
            return _stringReplacement;
        }
    };

    typedef std::map< HostName, IntegrityAttackParams > IntegrityAttackParamsMap;

private:
    IntegrityAttackParamsMap _integrityAttackParamsMap;

public:
    void enableIntegrityAttack( const HostName &hostName, int intMultiplier, int intAdder, long longMultiplier, long longAdder, double doubleMultiplier, double doubleAdder, bool booleanEnableFlip, const std::string &stringReplacement ) {
        _integrityAttackParamsMap.insert(   std::make_pair(  hostName, IntegrityAttackParams( intMultiplier, intAdder, longMultiplier, longAdder, doubleMultiplier, doubleAdder, booleanEnableFlip, stringReplacement )  )   );
    }

    void disableIntegrityAttack( const HostName &hostName ) {
        _integrityAttackParamsMap.erase( hostName );
    }

    bool isIntegrityAttackEnabled( const HostName &hostName ) {
        return ( _integrityAttackParamsMap.find(hostName) != _integrityAttackParamsMap.end() );
    }

    IntegrityAttackParams &getIntegrityAttackParams( omnetpp::cModule* cModulePtr, const HostName &hostName ) {
        if( !isIntegrityAttackEnabled( hostName ) ) {
            throw inet::cRuntimeError(cModulePtr, "HLAInterface::getIntegrityAttackParams()::ERROR: Integrity attack not set for '%s'", hostName.c_str());
        }

        return _integrityAttackParamsMap[hostName];
    }


    typedef std::set< std::string > ModifyFromHLAPacketsSet;
    typedef std::set< std::string > ModifyToHLAPacketsSet;
    typedef std::set< std::string > NodeAttackSet;

private:
    ModifyFromHLAPacketsSet _modifyFromHLAPacketsSet;
    ModifyToHLAPacketsSet _modifyToHLAPacketsSet;
    NodeAttackSet _nodeAttackSet;

public:

    void setNodeAttack( const std::string nodeFullPath, bool attack ) {
        if ( attack ) {
            _nodeAttackSet.insert( nodeFullPath );
        } else {
            _nodeAttackSet.erase( nodeFullPath );
        }
    }

    bool nodeAttack( const std::string nodeFullPath ) {
        return _nodeAttackSet.find( nodeFullPath ) != _nodeAttackSet.end();
    }

    void setModifyFromHLAPackets( const std::string nodeFullPath, bool modify ) {
        if ( modify ) {
            _modifyFromHLAPacketsSet.insert( nodeFullPath );
        } else {
            _modifyFromHLAPacketsSet.erase( nodeFullPath );
        }
    }

    bool modifyFromHLAPackets( const std::string nodeFullPath ) {
        return _modifyFromHLAPacketsSet.find( nodeFullPath ) != _modifyFromHLAPacketsSet.end();
    }

    void setModifyToHLAPackets( const std::string nodeFullPath, bool modify ) {
        if ( modify ) {
            _modifyToHLAPacketsSet.insert( nodeFullPath );
        } else {
            _modifyToHLAPacketsSet.erase( nodeFullPath );
        }
    }

    bool modifyToHLAPackets( const std::string nodeFullPath ) {
        return _modifyToHLAPacketsSet.find( nodeFullPath ) != _modifyToHLAPacketsSet.end();
    }
};

std::ostream &operator<<( std::ostream &os, const AttackCoordinator::NetworkAddress &networkAddress );

std::ostream &operator<<( std::ostream &os, const AttackCoordinator::AppSpec &appSpec );

std::ostream &operator<<( std::ostream &os, const AttackCoordinator::RouteEntry &routeEntry );
std::ostream &operator<<( std::ostream &os, const AttackCoordinator::RouteEntrySP &routeEntrySP );


#endif /* INCLUDE_ATTACKCOORDINATOR_H_ */
