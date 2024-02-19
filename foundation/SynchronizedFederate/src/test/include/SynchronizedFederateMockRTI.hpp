#ifndef _SYNCHRONIZED_FEDERATE_MOCK_RTI_HPP
#define _SYNCHRONIZED_FEDERATE_MOCK_RTI_HPP

#include "RTIAmbassadorTest2.hpp"

typedef RTI::FederateAmbassador NullFederateAmbassador;
#include "SynchronizedFederate.hpp"

class SynchronizedFederateMockRTI: public SynchronizedFederate {
public:

    virtual ~SynchronizedFederateMockRTI() {
        RTIAmbassadorTest2::remove_federate_ptr(this);
    }

    typedef SynchronizedFederate Super;
    SynchronizedFederateMockRTI(FederateConfig *federateConfig) : Super(federateConfig) {}

    void createRTI() {
        _rti = RTIAmbassadorTest2::get_instance_ptr();
        _currentTime = getCurrentTime();
    }
};

#endif // _SYNCHRONIZED_FEDERATE_MOCK_RTI_HPP
