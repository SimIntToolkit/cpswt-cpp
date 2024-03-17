#ifndef _SYNCHRONIZED_FEDERATE_MOCK_RTI_HPP
#define _SYNCHRONIZED_FEDERATE_MOCK_RTI_HPP

#include "RTIAmbassadorTest2.hpp"

typedef RTI::FederateAmbassador NullFederateAmbassador;
#include "SynchronizedFederate.hpp"

class SynchronizedFederateMockRTI: public SynchronizedFederate {

private:
    RTIAmbassadorTest2 rtiAmbassadorTest2;

public:
    typedef SynchronizedFederate Super;

    SynchronizedFederateMockRTI(FederateConfig *federateConfig) :
      Super(federateConfig), rtiAmbassadorTest2(*this) {}

    virtual ~SynchronizedFederateMockRTI() {}

    void createRTI() {
        _rti = &rtiAmbassadorTest2.getRTIAmbassador();
        _currentTime = getCurrentTime();
    }

    RTIAmbassadorTest2 &getRTIAmbassadorTest2() {
        return rtiAmbassadorTest2;
    }
};

#endif // _SYNCHRONIZED_FEDERATE_MOCK_RTI_HPP
