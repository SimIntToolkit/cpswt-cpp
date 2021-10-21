/*
 * HLAScheduler.cpp
 *
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
