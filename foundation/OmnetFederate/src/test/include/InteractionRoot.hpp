/*
 * InteractionRoot.hpp
 *
 *  Created on: Aug 7, 2021
 *      Author: hnine999
 */

#ifndef INTERACTIONROOT_HPP_
#define INTERACTIONROOT_HPP_

#include <boost/shared_ptr.hpp>
#include <StringCollections.hpp>
#include <TypeMedley.hpp>

class InteractionRoot {

public:
    typedef boost::shared_ptr< InteractionRoot > SP;

    static SP create_interaction(const std::string &className);
    static std::string get_class_name( void ) { return "InteractionRoot"; }

private:
    static int get_handle(void) {
        return 0;
    }

public:
    static bool match( int handle ) { return handle == get_handle(); }

    virtual ~InteractionRoot(void) { }

    virtual int getClassHandle( void ) const { return get_handle(); }
    virtual std::string getClassName( void ) const { return get_class_name(); }

    virtual StringVector getParameterNames(void) const {
        return StringVector();
    }

    virtual TypeMedley getParameter( const std::string &datamemberName ) const {
        throw std::invalid_argument( getClassName() + " class has no parameter named \"" + datamemberName + "\"" );
    }

};

typedef InteractionRoot::SP InteractionRootSP;

inline std::ostream &operator<<( std::ostream &os, const InteractionRoot &entity ) {
        return os << "InteractionRoot(" << ")";
}
inline std::ostream &operator<<( std::ostream &os, InteractionRootSP entitySP ) {
        return os << *entitySP;
}

#endif /* INTERACTIONROOT_HPP_ */
