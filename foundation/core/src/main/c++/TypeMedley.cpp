//
// Created by vagrant on 12/23/21.
//

#include "TypeMedley.hpp"

bool TypeMedley::string_to_bool(const std::string &value) {
    if (value.empty()) {
        return false;
    }
    if (hasDoubleFormat(value)) {
        return static_cast<bool>(boost::lexical_cast<double>(value));
    }

    std::string valueCopy(value);
    boost::algorithm::to_lower(valueCopy);
    if (valueCopy == "false") {
        return false;
    }
    return true;
}


bool TypeMedley::setValue(const std::string &value) {
    try {
        switch(_dataType) {
            case BOOLEAN:
                _value = boost::lexical_cast<std::string>(string_to_bool(value));
                break;
            case CHARACTER: {
                char localChar = value.empty() ? '\0' : _value[0];
                _value = std::string(&localChar, 1);
                break;
            }
            case SHORT: {
                _value = convert_to_string<short>(value);
                break;
            }
            case INTEGER:
                _value = convert_to_string<int>(value);
                break;
            case LONG:
                _value = convert_to_string<long>(value);
                break;
            case FLOAT:
                _value = convert_to_string<float>(value);
                break;
            case DOUBLE:
                _value = convert_to_string<double>(value);
                break;
            case STRING:
                _value = value;
                break;
        }
        return true;
    } catch(...) { }
    return false;
}

