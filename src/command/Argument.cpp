#include "Argument.h"

Argument::Argument(const std::string &name, bool aRequired, bool boolArg) : name(name), required(aRequired),
                                                                            boolArg(boolArg) {}

Argument::Argument(const std::string &name, bool aRequired) : name(name), required(aRequired) {}

const std::string &Argument::getName() const {
    return name;
}

void Argument::setName(const std::string &name) {
    Argument::name = name;
}

bool Argument::isRequired() const {
    return required;
}

void Argument::setARequired(bool aRequired) {
    required = aRequired;
}

bool Argument::isBoolArg() const {
    return boolArg;
}

void Argument::setBoolArg(bool boolArg) {
    Argument::boolArg = boolArg;
}

const std::string &Argument::getValue() const {
    if (value.empty())
        if (required)
            throw MissingArgumentException("Required value is not defined for: " + name); // TODO: Create another exception
        else
            throw EmptyArgumentException();
    return value;
}

void Argument::setValue(const std::string &value) {
    Argument::value = value;
}


int Argument::getValueAsInt() {
    return std::stoi(getValue());
}

unsigned long Argument::getValueAsUnsignedLong() {
    return std::stoul(getValue());
}

unsigned long Argument::getValueAsUnsignedLong(int base) {
    return std::stoul(getValue(), 0, base);
}

bool Argument::hasValue() {
    return !value.empty();
}
