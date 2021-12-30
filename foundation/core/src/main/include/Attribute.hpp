//
// Created by vagrant on 12/23/21.
//

#ifndef CPSWT_CPP_ATTRIBUTE_HPP
#define CPSWT_CPP_ATTRIBUTE_HPP

#include "TypeMedley.hpp"

//-----------------------------------------------------
// Attribute CLASS -- USED BY ObjectRoot AND SUBCLASSES
//-----------------------------------------------------
class Attribute: public TypeMedley {
private:
    std::string _oldValue;
    bool _oldValueInit;
    double _time;

    explicit Attribute(bool value) : TypeMedley(value), _oldValueInit(false), _time(-1) { }
    explicit Attribute(char value) : TypeMedley(value), _oldValueInit(false), _time(-1) { }
    explicit Attribute(short value) : TypeMedley(value), _oldValueInit(false), _time(-1) { }
    explicit Attribute(int value) : TypeMedley(value), _oldValueInit(false), _time(-1) { }
    explicit Attribute(long value) : TypeMedley(value), _oldValueInit(false), _time(-1) { }
    explicit Attribute(float value) : TypeMedley(value), _oldValueInit(false), _time(-1) { }
    explicit Attribute(double value) : TypeMedley(value), _oldValueInit(false), _time(-1) { }
    explicit Attribute(const std::string &value) : TypeMedley(value), _oldValueInit(false), _time(-1) { }

public:
    double getTime() const {
        return _time;
    }
    void setTime(double time) {
        _time = time;
    }

    void setHasBeenUpdated() {
        _oldValue = _value;
        _oldValueInit = true;
    }

    bool shouldBeUpdated(bool force) const {
        return force || !_oldValueInit || _oldValue != _value;
    }
};

typedef boost::shared_ptr<Attribute> AttributeSP;

//--------------------
// END Attribute CLASS
//--------------------

#endif //CPSWT_CPP_ATTRIBUTE_HPP
