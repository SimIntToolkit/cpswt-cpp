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

#include <HLAScheduler.h>
#include <HLAInterface.h>


Register_Class(HLAScheduler);

HLAScheduler::HLAScheduler() : cScheduler() {}

// takeNextEvent - the main method of the scheduler
// THIS METHOD IS MODELED OFF OF THE takeNextEvent METHOD FROM "cscheculer.cc"
omnetpp::cEvent* HLAScheduler::takeNextEvent()
{
    // first try to see if an event is scheduled

    HLAInterface *hlaInterfacePtr = HLAInterface::get_InstancePtr();

    omnetpp::cEvent *event = sim->getFES()->removeFirst();
    if (!event)
    {
        throw new inet::cTerminationException(omnetpp::E_ENDEDOK);
    }


    // if no event is scheduled before the logical time,
    // request that the RTI advance the time
    double timeDifference = event->getArrivalTime().dbl() - hlaInterfacePtr->getCurrentTimeLocal();
    while( timeDifference > 0 ) {

        // move time ahead one step
        double step = std::min( timeDifference, hlaInterfacePtr->getStepSize() );
        hlaInterfacePtr->advanceTimeStep( step );

        if (event->isStale()) {
            delete event;
            event = sim->getFES()->removeFirst();
        }
        timeDifference = event->getArrivalTime().dbl() - hlaInterfacePtr->getCurrentTimeLocal();
    }

    return event;
}
