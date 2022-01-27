#include "RTITest.hh"
#include <cstring>


char *__copyForExceptionString(const char *original) {
    char *retval = new char[strlen(original) + 1];
    strcpy(retval, original);
    return retval;
}

RTI::Exception::Exception(const char *reason) : _name(nullptr) {
    _serial = static_cast<ULong>(0);
    _reason = ::__copyForExceptionString(reason);
}

RTI::Exception::Exception(ULong serial, const char *reason) : _name(nullptr) {
    _serial = serial;
    _reason = ::__copyForExceptionString(reason);
}

RTI::Exception::Exception(const Exception &toCopy) : _name(::__copyForExceptionString(toCopy._name)) {
    _serial = toCopy._serial;
    _reason = __copyForExceptionString(toCopy._reason);
}

RTI::Exception::~Exception() {
    delete[] _reason;
    _reason = nullptr;

    delete[] _name;
    _name = nullptr;
}

RTI::Exception &RTI::Exception::operator=(const Exception &toCopy) {
    _serial = toCopy._serial;
    _reason = ::__copyForExceptionString(toCopy._reason);
    return *this;
}


