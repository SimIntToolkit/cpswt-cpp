#include "RTITest.hh"

RTI::ParameterHandleValuePairSet *RTI::ParameterSetFactory::create(ULong count) throw (
  MemoryExhausted, ValueCountExceeded, HandleValuePairMaximumExceeded
) {
    return nullptr;
}

RTI::AttributeHandleValuePairSet *RTI::AttributeSetFactory::create(ULong count) throw (
  MemoryExhausted, ValueCountExceeded, HandleValuePairMaximumExceeded
) {
    return nullptr;
}

RTI::AttributeHandleSet* RTI::AttributeHandleSetFactory::create(ULong count) throw (
  MemoryExhausted, ValueCountExceeded
) {
    return nullptr;
}
