/*
 * HLAScheduler.hpp
 *
 */

#ifndef HLAScheduler_hpp
#define HLAScheduler_hpp

#include <omnetpp.h>

/**
 * Extends the basic OMNeT scheduler to step forward in
 * time based on the RTI's permission
 */
class HLAScheduler: public omnetpp::cScheduler
{
public:
    HLAScheduler();
    virtual ~HLAScheduler() {}

    virtual omnetpp::cEvent *takeNextEvent() override;
    virtual omnetpp::cEvent *guessNextEvent() override {
        return sim->getFES()->peekFirst();
    }
    virtual void putBackEvent(omnetpp::cEvent *event) override {
        sim->getFES()->putBackFirst(event);
    }
};

#endif /* HLAScheduler_hpp */
