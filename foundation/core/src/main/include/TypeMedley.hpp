/*
 * Certain portions of this software are Copyright (C) 2006-present
 * Vanderbilt University, Institute for Software Integrated Systems.
 *
 * Certain portions of this software are contributed as a public service by
 * The National Institute of Standards and Technology (NIST) and are not
 * subject to U.S. Copyright.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above Vanderbilt University copyright notice, NIST contribution
 * notice and this permission and disclaimer notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE. THE AUTHORS OR COPYRIGHT HOLDERS SHALL NOT HAVE
 * ANY OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS,
 * OR MODIFICATIONS.
 */

#ifndef _TYPEMEDLEY_HPP
#define _TYPEMEDLEY_HPP

#include <boost/lexical_cast.hpp>
#include <iostream>
#include <regex>
#include <utility>
#include <boost/algorithm/string.hpp>
#include <boost/shared_ptr.hpp>
#include <jsoncpp/json/json.h>
#include <list>
#include <map>


class TypeMedley {
public:
    enum DataType { BOOLEAN, CHARACTER, SHORT, INTEGER, LONG, FLOAT, DOUBLE, STRING, JSON };
    typedef boost::shared_ptr<TypeMedley> SP;

private:
    static std::regex &get_double_regex() {
        static std::regex doubleRegex("^[+-]?(?:\\.[0-9]+|[0-9]+(?:\\.[0-9]*)?)(?:e[+-][0-9]{1,3})?");
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
        enumToStringTypeMap[JSON] = "Json::Value";

        return enumToStringTypeMap;
    }

    static const std::map<DataType, std::string> &get_enum_to_string_type_map() {
        static const std::map<DataType, std::string> &enumToStringTypeMap = get_enum_to_string_type_map_aux();

        return enumToStringTypeMap;
    }

    Json::Value jsonStringToJson() const {
        std::istringstream jsonInputStream(_value);

        Json::Value topLevelJSONObject;
        jsonInputStream >> topLevelJSONObject;

        return topLevelJSONObject;
    }

    std::string jsonToJsonString(const Json::Value &jsonValue) const {

        Json::StreamWriterBuilder streamWriterBuilder;
        streamWriterBuilder["commentStyle"] = "None";
        streamWriterBuilder["indentation"] = "    ";
        std::unique_ptr<Json::StreamWriter> streamWriterUPtr(streamWriterBuilder.newStreamWriter());
        std::ostringstream stringOutputStream;
        streamWriterUPtr->write(jsonValue, &stringOutputStream);
        return stringOutputStream.str();
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

    explicit TypeMedley(const Json::Value &value):
      _dataType(JSON), _value(jsonToJsonString(value)) { }

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
                _value = boost::lexical_cast<std::string>(static_cast<short>(value));
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
            case JSON:
                Json::Value jsonValue(value);
                _value = jsonToJsonString(jsonValue);
                break;
        }
        return true;
    }

    bool setValue(long value) {
        return setValue(static_cast<Json::Value::Int64>(value));
    }
    // SPECIALIZATION FOR std::string
    bool setValue(const std::string &value);

    bool setValue(const char *cString) {
        return setValue(std::string(cString));
    }

    // SPECIALIZATION FOR Json::Value
    bool setValue(const Json::Value &value) {
        switch(_dataType) {
            case BOOLEAN:
                _value = boost::lexical_cast<std::string>(static_cast<bool>(value.size()));
                break;
            case CHARACTER:
                _value = boost::lexical_cast<std::string>(static_cast<short>(value.size()));
                break;
            case SHORT:
                _value = boost::lexical_cast<std::string>(static_cast<short>(value.size()));
                break;
            case INTEGER:
                _value = boost::lexical_cast<std::string>(static_cast<int>(value.size()));
                break;
            case LONG:
                _value = boost::lexical_cast<std::string>(static_cast<long>(value.size()));
                break;
            case FLOAT:
                _value = boost::lexical_cast<std::string>(static_cast<float>(value.size()));
                break;
            case DOUBLE:
                _value = boost::lexical_cast<std::string>(static_cast<double>(value.size()));
                break;
            case STRING:
            case JSON:
                _value = jsonToJsonString(value);
                break;
        }
        return true;
    }

    bool setValue(const TypeMedley &other) {
        if (getDataType() == other.getDataType()) {
            _value = other._value;
            return true;
        }

        switch( other.getDataType() ) {
            case BOOLEAN:
                setValue( other.asBool() );
                break;
            case CHARACTER:
                setValue( other.asChar() );
                break;
            case SHORT:
                setValue( other.asShort() );
                break;
            case INTEGER:
                setValue( other.asInt() );
                break;
            case LONG:
                setValue( other.asLong() );
                break;
            case FLOAT:
                setValue( other.asFloat() );
                break;
            case DOUBLE:
                setValue( other.asDouble() );
                break;
            case STRING:
            case JSON:
                setValue( other.asString() );
                break;
        }
    }

private:

    template<typename T>
    T convertToType() const {
        switch(_dataType) {
            case JSON: {
                return static_cast<T>(jsonStringToJson().size());
            }
            case STRING: {
                if (!hasDoubleFormat(_value)) {
                    return static_cast<T>(_value.empty() ? 0 : _value[0]);
                }
            }
            default: {
                return static_cast<T>(boost::lexical_cast<double>(_value));
            }
        }
    }

public:
    bool asBool() const {
        switch(_dataType) {
            case JSON: {
                Json::Value value = jsonStringToJson();
                return static_cast<bool>(value.size());
            }
            case STRING: {
                return string_to_bool(_value);
            }
            default: {
                return static_cast<bool>(boost::lexical_cast<double>(_value));
            }
        }
    }

    operator bool() const {
        return asBool();
    }

    char asChar() const {
        return convertToType<char>();
    }

    operator char() const {
         return asChar();
    }

    short asShort() const {
        return convertToType<short>();
    }

    operator short() const {
        return asShort();
    }

    int asInt() const {
        return convertToType<int>();
    }

    operator int() const {
        return asInt();
    }

    long asLong() const {
        return convertToType<long>();
    }

    operator long() const {
        return asLong();
    }

    float asFloat() const {
        return convertToType<float>();
    }

    operator float() const {
        return asFloat();
    }

    double asDouble() const {
        return convertToType<double>();
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

    Json::Value asJson() const {
        switch(_dataType) {
            case BOOLEAN:
                return Json::Value(asBool());
            case CHARACTER:
                return Json::Value(asChar());
            case SHORT:
                return Json::Value(asShort());
            case INTEGER:
                return Json::Value(asInt());
            case LONG:
                return Json::Value(static_cast<Json::Value::Int64>(asLong()));
            case FLOAT:
                return Json::Value(asFloat());
            case DOUBLE:
                return Json::Value(asDouble());
            case STRING:
                return Json::Value(asString());
            case JSON:
                return jsonStringToJson();
                
        }
    }

    operator Json::Value() const {
        return asJson();
    }

    std::string getStringRepresentation() const {
        return _value;
    }
};

#endif // _TYPEMEDLEY_HPP
