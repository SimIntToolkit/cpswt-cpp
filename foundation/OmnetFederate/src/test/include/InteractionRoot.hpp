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
