/*
 * ObjectRoot.hpp
 *
 *  Created on: Aug 7, 2021
 *      Author: hnine999
 */

#ifndef OBJECTROOT_HPP_
#define OBJECTROOT_HPP_

#include <iostream>
#include <boost/shared_ptr.hpp>

class ObjectRoot {
public:
    typedef boost::shared_ptr<ObjectRoot> SP;
};

typedef ObjectRoot::SP ObjectRootSP;

inline std::ostream &operator<<( std::ostream &os, const ObjectRoot &entity ) {
        return os << "ObjectRoot(" << ")";
}
inline std::ostream &operator<<( std::ostream &os, ObjectRoot::SP entitySP ) {
        return os << *entitySP;
}

#endif /* OBJECTROOT_HPP_ */
