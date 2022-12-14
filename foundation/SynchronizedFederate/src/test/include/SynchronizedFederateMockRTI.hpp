#ifndef _SYNCHRONIZED_FEDERATE_MOCK_RTI_HPP
#define _SYNCHRONIZED_FEDERATE_MOCK_RTI_HPP

#include "RTIAmbassadorTest2.hpp"

typedef RTI::FederateAmbassador NullFederateAmbassador;
#include "SynchronizedFederate.hpp"

class SynchronizedFederateMockRTI: public SynchronizedFederate {
public:
    typedef SynchronizedFederate Super;
    SynchronizedFederateMockRTI(FederateConfig *federateConfig) : Super(federateConfig) {}

    void createRTI() {
        _rti = RTIAmbassadorTest2::get_rti_ambassador_2_ptr();
    }
};

#endif // _SYNCHRONIZED_FEDERATE_MOCK_RTI_HPP
