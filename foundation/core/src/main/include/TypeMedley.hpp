/*
 * Copyright (c) 2008, Institute for Software Integrated Systems, Vanderbilt University
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice, the following
 * two paragraphs and the author appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE VANDERBILT UNIVERSITY BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE VANDERBILT
 * UNIVERSITY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE VANDERBILT UNIVERSITY SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE VANDERBILT UNIVERSITY HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 */

#ifndef _TYPEMEDLEY_HPP
#define _TYPEMEDLEY_HPP

#include <boost/lexical_cast.hpp>
#include <iostream>
#include <regex>
#include <utility>
#include <boost/algorithm/string.hpp>
#include <map>

class TypeMedley {
public:
    enum DataType { BOOLEAN, CHARACTER, SHORT, INTEGER, LONG, FLOAT, DOUBLE, STRING };

private:
    static std::regex &get_double_regex() {
        static std::regex doubleRegex("^(?:\\.[0-9]+|[0-9]+(?:\\.[0-9]*)?)(?:e[+-][0-9]{1,3})?");
        return doubleRegex;
    }

    static bool hasDoubleFormat(const std::string &value) {
        return std::regex_match(value, get_double_regex());
    }

    static bool string_to_bool(const std::string &value);

    template<typename T>
    static std::string convert_to_string(const std::string &value) {
        T tValue = hasDoubleFormat(value)
                   ? static_cast<T>(boost::lexical_cast<double>(value))
                   : static_cast<T>(value.empty());
        return boost::lexical_cast<std::string>(tValue);
    }

    static const std::map<DataType, std::string> &get_enum_to_string_type_map_aux() {
        static std::map<DataType, std::string> enumToStringTypeMap;

        enumToStringTypeMap[BOOLEAN] = "bool";
        enumToStringTypeMap[CHARACTER] = "char";
        enumToStringTypeMap[SHORT] = "short";
        enumToStringTypeMap[INTEGER] = "int";
        enumToStringTypeMap[LONG] = "long";
        enumToStringTypeMap[FLOAT] = "float";
        enumToStringTypeMap[DOUBLE] = "double";
        enumToStringTypeMap[STRING] = "std::string";

        return enumToStringTypeMap;
    }

    static const std::map<DataType, std::string> &get_enum_to_string_type_map() {
        static const std::map<DataType, std::string> &enumToStringTypeMap = get_enum_to_string_type_map_aux();

        return enumToStringTypeMap;
    }


protected:
    DataType _dataType;
    std::string _value;

public:
    explicit TypeMedley(bool value):
      _dataType(BOOLEAN), _value(boost::lexical_cast<std::string>(value)) { }

    explicit TypeMedley(char value):
      _dataType(CHARACTER), _value(boost::lexical_cast<std::string>(static_cast<int>(value))) { }

    explicit TypeMedley(short value):
      _dataType(SHORT), _value(boost::lexical_cast<std::string>(value)) { }

    explicit TypeMedley(int value):
      _dataType(INTEGER), _value(boost::lexical_cast<std::string>(value)) { }

    explicit TypeMedley(long value):
      _dataType(LONG), _value(boost::lexical_cast<std::string>(value)) { }

    explicit TypeMedley(float value):
      _dataType(FLOAT), _value(boost::lexical_cast<std::string>(value)) { }

    explicit TypeMedley(double value):
      _dataType(DOUBLE), _value(boost::lexical_cast<std::string>(value)) { }

    explicit TypeMedley(std::string value):
      _dataType(STRING), _value(std::move(value)) { }

public:
    DataType getDataType() const {
        return _dataType;
    }

    const std::string &getTypeName() const {
        return get_enum_to_string_type_map().find(_dataType)->second;
    }

    template<typename T>
    bool setValue(T value) {
        switch(_dataType) {
            case BOOLEAN:
                _value = boost::lexical_cast<std::string>(static_cast<bool>(value));
                break;
            case CHARACTER:
                _value = boost::lexical_cast<std::string>(static_cast<char>(value));
                break;
            case SHORT:
                _value = boost::lexical_cast<std::string>(static_cast<short>(value));
                break;
            case INTEGER:
                _value = boost::lexical_cast<std::string>(static_cast<int>(value));
                break;
            case LONG:
                _value = boost::lexical_cast<std::string>(static_cast<long>(value));
                break;
            case FLOAT:
                _value = boost::lexical_cast<std::string>(static_cast<float>(value));
                break;
            case DOUBLE:
                _value = boost::lexical_cast<std::string>(static_cast<double>(value));
                break;
            case STRING:
                _value = boost::lexical_cast<std::string>(value);
                break;
        }
        return true;
    }

    bool setValue(const std::string &value);

    bool asBool() const {
        switch(_dataType) {
            case CHARACTER:
                return _value[0] != '0' && static_cast<char>(boost::lexical_cast<int>(_value)) != '0';
            case STRING:
                return string_to_bool(_value);
            default:
                return static_cast<bool>(boost::lexical_cast<double>(_value));
        }
    }

    operator bool() const {
        return asBool();
    }

    char asChar() const {
        if (_dataType == STRING) {
            return _value.empty() ? '\0' : _value[0];
        }
        return static_cast<char>(boost::lexical_cast<double>(_value));
    }

    operator char() const {
         return asChar();
    }

    short asShort() const {
        if (_dataType == STRING && !hasDoubleFormat(_value)) {
            return static_cast<short>(_value.empty());
        }
        return static_cast<short>(boost::lexical_cast<double>(_value));
    }

    operator short() const {
        return asShort();
    }

    int asInt() const {
        if (_dataType == STRING && !hasDoubleFormat(_value)) {
            return static_cast<int>(_value.empty());
        }
        return static_cast<int>(boost::lexical_cast<double>(_value));
    }

    operator int() const {
        return asInt();
    }

    long asLong() const {
        if (_dataType == STRING && !hasDoubleFormat(_value)) {
            return static_cast<long>(_value.empty());
        }
        return static_cast<long>(boost::lexical_cast<double>(_value));
    }

    operator long() const {
        return asLong();
    }

    float asFloat() const {
        if (_dataType == STRING && !hasDoubleFormat(_value)) {
            return static_cast<float>(_value.empty());
        }
        return static_cast<float>(boost::lexical_cast<double>(_value));
    }

    operator float() const {
        return asFloat();
    }

    double asDouble() const {
        if (_dataType == STRING && !hasDoubleFormat(_value)) {
            return static_cast<double>(_value.empty());
        }
        return boost::lexical_cast<double>(_value);
    }

    operator double() const {
        return asDouble();
    }

    std::string asString() const {
        switch(_dataType) {
            case BOOLEAN:
                return boost::lexical_cast<int>(_value) ? "true" : "false";
            case CHARACTER: {
                char localChar = static_cast<char>(boost::lexical_cast<int>(_value));
                return { &localChar, 1 };
            }
            default:
                return _value;
        }
    }

    operator std::string() const {
        return asString();
    }
};

#endif // _TYPEMEDLEY_HPP
