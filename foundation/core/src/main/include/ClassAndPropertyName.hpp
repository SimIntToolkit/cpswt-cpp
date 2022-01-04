#ifndef _CLASS_AND_PROPERTY_NAME_HPP
#define _CLASS_AND_PROPERTY_NAME_HPP

#include <string>
#include <utility>
#include <boost/shared_ptr.hpp>
#include <unordered_set>
#include <list>

class ClassAndPropertyName {

private:
    static const std::string &getSeparatorChar() {
        static const std::string separatorChar(">");
        return separatorChar;
    }

    std::string _className;
    std::string _propertyName;

public:
    ClassAndPropertyName(std::string className, std::string propertyName):
            _className(std::move(className)), _propertyName(std::move(propertyName)) { }

    explicit ClassAndPropertyName(const std::string &classAndPropertyNameString) {
        size_t separatorCharPosition = classAndPropertyNameString.find(getSeparatorChar());
        if (separatorCharPosition == std::string::npos) {
            _className = classAndPropertyNameString;
            _propertyName = classAndPropertyNameString;
        } else {
            _className = classAndPropertyNameString.substr(0, separatorCharPosition);
            _propertyName = classAndPropertyNameString.substr(separatorCharPosition + 1);
        }
    }

    const std::string &getClassName() const {
        return _className;
    }

    const std::string &getPropertyName() const {
        return _propertyName;
    }

    explicit operator std::string() const {
        static std::string stringValue(_className + getSeparatorChar() + _propertyName);
        return stringValue;
    }

    size_t hashCode() const {
        static std::hash<std::string> localHash;
        return localHash(static_cast<std::string>(*this));
    }

    bool operator==(const ClassAndPropertyName &other) const {
        return _className == other._className && _propertyName == other._propertyName;
    }

    bool operator<(const ClassAndPropertyName &other) const {
        if (_className < other._className) {
            return true;
        }
        if (_className > other._className) {
            return false;
        }
        return _propertyName < other._propertyName;
    }

    bool operator>(const ClassAndPropertyName &other) const {
        if (_className > other._className) {
            return true;
        }
        if (_className < other._className) {
            return false;
        }
        return _propertyName > other._propertyName;
    }
};

template<>
struct std::hash<ClassAndPropertyName> {
    size_t operator()(const ClassAndPropertyName &classAndPropertyName) {
        return classAndPropertyName.hashCode();
    }
};

typedef boost::shared_ptr<ClassAndPropertyName> ClassAndPropertyNameSP;
typedef std::unordered_set<ClassAndPropertyName> ClassAndPropertyNameSet;
typedef std::list<ClassAndPropertyName> ClassAndPropertyNameList;

#endif // _CLASS_AND_PROPERTY_NAME_HPP
