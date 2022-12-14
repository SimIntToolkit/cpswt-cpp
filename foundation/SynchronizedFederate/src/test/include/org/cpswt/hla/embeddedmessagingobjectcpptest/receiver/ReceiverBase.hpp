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

#ifndef ORG_CPSWT_HLA_EMBEDDEDMESSAGINGOBJECTCPPTEST_RECEIVER_CLASS_BASE_CLASS
#define ORG_CPSWT_HLA_EMBEDDEDMESSAGINGOBJECTCPPTEST_RECEIVER_CLASS_BASE_CLASS

#define BOOST_LOG_DYN_LINK

#include <fstream>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/expressions.hpp>

#include "SynchronizedFederateMockRTI.hpp"
#include "SubscribedInteractionFilter.hpp"
#include "FederateConfigParser.h"


#include "InteractionRoot_p/C2WInteractionRoot_p/EmbeddedMessaging_p/Receiver.hpp"
#include "ObjectRoot_p/TestObject.hpp"


namespace org {
 namespace cpswt {
  namespace hla {
   namespace embeddedmessagingobjectcpptest {
    namespace receiver {

BOOST_LOG_ATTRIBUTE_KEYWORD(federateName, "FederateName", std::string);
BOOST_LOG_ATTRIBUTE_KEYWORD(messagingClassName, "MessagingClassName", std::string);
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", logging::trivial::severity_level);
BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime);

namespace logging = boost::log;
namespace logging_source = boost::log::sources;
namespace attrs = boost::log::attributes;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;

using namespace logging::trivial;

class ReceiverBase: public SynchronizedFederateMockRTI {

using InteractionRoot = ::org::cpswt::hla::InteractionRoot;
using C2WInteractionRoot = ::org::cpswt::hla::InteractionRoot_p::C2WInteractionRoot;

public:
    typedef logging_source::severity_logger< severity_level > severity_logger;
    typedef sinks::synchronous_sink< sinks::text_ostream_backend > text_sink;

private:
    static severity_logger &get_logger_aux() {

        logging::add_common_attributes();

        // ADD FEDERATE NAME ATTRIBUTE TO ALL LOG MESSAGES
        logging::core::get()->add_global_attribute("FederateName", attrs::constant< std::string >(
          "Receiver"
        ));

        // ADD SINK TO LOG FILE NAMED AFTER FEDERATE
        // NEEDS TO BE STATIC SO THAT THE SINK PERSIST AFTER THIS FUNCION RETURNS
        static boost::shared_ptr< text_sink > fileSink = boost::make_shared< text_sink >();

        fileSink->locked_backend()->add_stream(
          boost::make_shared< std::ofstream >("Receiver.log")
        );

        fileSink->set_formatter(
            expr::stream << federateName << " "
              << expr::if_(expr::has_attr(messagingClassName)) [
                expr::stream << "{" << messagingClassName << "} "
              ]
              << "<" << timestamp << "> [" << severity << "]: " << expr::smessage
        ); 
        logging::core::get()->add_sink(fileSink);

        static severity_logger logger;
        return logger;
    }

public:
    static severity_logger &get_logger() {
        static severity_logger &logger = get_logger_aux();
        return logger;
    }

    typedef SynchronizedFederateMockRTI Super;

    typedef std::vector<std::string> ArgVector;

    virtual ~ReceiverBase() { }

private:
    SubscribedInteractionFilter _subscribedInteractionFilter;

protected:
    void init();

public:
    ReceiverBase(FederateConfig *federateConfig);

    virtual void receiveInteraction(
      RTI::InteractionClassHandle interactionClassHandle,
      const RTI::ParameterHandleValuePairSet &parameterHandleValuePairSet,
      const char *userSuppliedTag
    ) throw (
      RTI::InteractionClassNotKnown,
      RTI::InteractionParameterNotKnown,
      RTI::FederateInternalError
    );

    virtual void receiveInteraction(
      RTI::InteractionClassHandle interactionClassHandle,
      const RTI::ParameterHandleValuePairSet &parameterHandleValuePairSet,
      const RTI::FedTime &fedTime,
      const char *userSuppliedTag,
      RTI::EventRetractionHandle theHandle
    ) throw (
      RTI::InteractionClassNotKnown,
      RTI::InteractionParameterNotKnown,
      RTI::InvalidFederationTime,
      RTI::FederateInternalError
    );
};
    } // NAMESPACE "receiver"
   } // NAMESPACE "embeddedmessagingobjectcpptest"
  } // NAMESPACE "hla"
 } // NAMESPACE "cpswt"
} // NAMESPACE "org"

#endif // ORG_CPSWT_HLA_EMBEDDEDMESSAGINGOBJECTCPPTEST_RECEIVER_CLASS_BASE_CLASS
