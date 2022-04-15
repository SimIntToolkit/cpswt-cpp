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

#ifndef _ISIS_SUBSCRIBEDINTERACTION_FILTER_HPP_
#define _ISIS_SUBSCRIBEDINTERACTION_FILTER_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string.hpp>
#include "InteractionRoot_p/C2WInteractionRoot.hpp"

class SubscribedInteractionFilter {

using C2WInteractionRoot = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot;

public:
    enum OriginFedFilter { ORIGIN_FILTER_DISABLED, SELF, NON_SELF };
    enum SourceFedFilter { SOURCE_FILTER_DISABLED, MAPPER, NON_MAPPER };

    class Filter {
    private:
        OriginFedFilter _originFedFilter;
        SourceFedFilter _sourceFedFilter;

    public:
        Filter( void ) : _originFedFilter( ORIGIN_FILTER_DISABLED ), _sourceFedFilter( SOURCE_FILTER_DISABLED ) { }

        void setOriginFedFilter( OriginFedFilter originFedFilter ) {
            _originFedFilter = originFedFilter;
        }

        OriginFedFilter getOriginFedFilter( void ) { return _originFedFilter; }

        void setSourceFedFilter( SourceFedFilter sourceFedFilter ) {
            _sourceFedFilter = sourceFedFilter;
        }
        SourceFedFilter getSourceFedFilter( void ) { return _sourceFedFilter; }
    };

    typedef std::map< int, Filter > HandleFilterMap;

    struct FilterInit {
        typedef boost::shared_ptr< FilterInit > SP;

        virtual ~FilterInit( void ) { }

        static SP create( void ) {
            return SP( new FilterInit() );
        }

        virtual void execute( SubscribedInteractionFilter &subscribedInteractionFilter ) { }
    };

    typedef FilterInit::SP FilterInitSP;

private:
    HandleFilterMap _handleFilterMap;
    FilterInitSP _filterInitSP;

public:
    SubscribedInteractionFilter( void ) : _filterInitSP( FilterInit::create() ) { }

    void setOriginFedFilter( int handle, OriginFedFilter originFedFilter ) {
        HandleFilterMap::iterator hfmItr = _handleFilterMap.find( handle );
        if ( hfmItr == _handleFilterMap.end() ) {
            hfmItr = _handleFilterMap.insert(  std::make_pair( handle, Filter() )  ).first;
        }
        hfmItr->second.setOriginFedFilter( originFedFilter );
    }

    void setSourceFedFilter( int handle, SourceFedFilter sourceFedFilter ) {
        HandleFilterMap::iterator hfmItr = _handleFilterMap.find( handle );
        if ( hfmItr == _handleFilterMap.end() ) {
            hfmItr = _handleFilterMap.insert(  std::make_pair( handle, Filter() )  ).first;
        }
        hfmItr->second.setSourceFedFilter( sourceFedFilter );
    }

    void setFedFilters( int handle, OriginFedFilter originFedFilter, SourceFedFilter sourceFedFilter ) {
        HandleFilterMap::iterator hfmItr = _handleFilterMap.find( handle );
        if ( hfmItr == _handleFilterMap.end() ) {
            hfmItr = _handleFilterMap.insert(  std::make_pair( handle, Filter() )  ).first;
        }
        Filter &filter = hfmItr->second;
        filter.setOriginFedFilter( originFedFilter );
        filter.setSourceFedFilter( sourceFedFilter );
    }

    void setFilterInit( FilterInitSP filterInitSP ) {
        _filterInitSP = filterInitSP;
    }

    bool filterC2WInteraction( const std::string &federateId, C2WInteractionRoot::SP c2wInteractionRootSP );

    void initialize( void ) {
        _filterInitSP->execute( *this );
    }

    static SubscribedInteractionFilter &get_singleton( void ) {
        static SubscribedInteractionFilter subscribedInteractionFilter;
        return subscribedInteractionFilter;
    }

};

#endif
