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

#ifndef MAIN_HPP
#define MAIN_HPP

#include "GridlabDFederateBase.hpp"

// Needed for Fork/exec/kill
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

// Needed for communicating with GLD
#include <boost/network/protocol/http/client.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

struct gld_obj
{
  bool has_data;
  std::string type;
  std::string object;
  std::string name;
  std::string value;
};

class GridlabDFederate : public GridlabDFederateBase 
{
private:
  double _currentTime;
  std::string _gld_ip;
  std::string _gld_port;
public:
  typedef GridlabDFederateBase Super;
  GridlabDFederate( int argc, char *argv[] ) 
    : Super( argc, argv ), _currentTime( 0 ), _gld_ip("localhost"), _gld_port("6267") { }
  virtual ~ GridlabDFederate( void )
    throw (RTI::FederateInternalError) { }

  class GridlabDFederateATRCallback : public ATRCallback 
  {
  private:
    GridlabDFederate &_gldfed;
  public:
    GridlabDFederateATRCallback( GridlabDFederate &gldfed ) : _gldfed( gldfed ) { }
    virtual void execute( void ) { _gldfed.execute(); }
    virtual SP clone( void ) { return SP( new GridlabDFederateATRCallback( *this ) ); }
  };

  void initialize( void );
  void execute( void );
  
  bool call_gld( std::string gld_url, gld_obj& ret_obj );
};

#endif
