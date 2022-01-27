#ifndef _ATTRIBUTE_HANDLE_SET_TEST
#define _ATTRIBUTE_HANDLE_SET_TEST

#include <set>
#include "RTITest.hh"


class AttributeHandleSetTest: public RTI::AttributeHandleSet {

public:
    typedef std::set<RTI::AttributeHandle> StdAttributeHandleSet;
private:
    StdAttributeHandleSet attributeHandleSet;

public:
    RTI::ULong size() const override {
        return attributeHandleSet.size();
    }

    RTI::AttributeHandle getHandle(RTI::ULong index) const throw (RTI::ArrayIndexOutOfBounds) override {
        if (index >= size()) {
            return static_cast<RTI::AttributeHandle>(0);
        }

        int ix = 0;
        StdAttributeHandleSet::const_iterator sasCit = attributeHandleSet.begin();
        while(ix <= index) {
            ++sasCit;
            ++ix;
        }

        return static_cast<RTI::AttributeHandle>(*sasCit);
    }

    void add(RTI::AttributeHandle attributeHandle) throw (
      RTI::ArrayIndexOutOfBounds, RTI::AttributeNotDefined
    ) override {
        attributeHandleSet.insert(attributeHandle);
    }

    void remove(RTI::AttributeHandle attributeHandle) throw (RTI::AttributeNotDefined) override {
        attributeHandleSet.erase(attributeHandle);
    }

    void empty() override {
        attributeHandleSet.clear();
    }

    RTI::Boolean isEmpty() const override {
        return attributeHandleSet.empty() ? RTI::RTI_TRUE : RTI::RTI_FALSE;
    }

    RTI::Boolean isMember(RTI::AttributeHandle attributeHandle) const override {
        StdAttributeHandleSet::const_iterator sasCit = attributeHandleSet.find(attributeHandle);
        return sasCit == attributeHandleSet.end() ? RTI::RTI_FALSE : RTI::RTI_TRUE;
    }
};

#endif // _ATTRIBUTE_HANDLE_SET_TEST
