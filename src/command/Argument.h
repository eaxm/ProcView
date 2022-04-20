#ifndef PROCVIEW_ARGUMENT_H
#define PROCVIEW_ARGUMENT_H

#include <string>
#include "exception/MissingArgumentException.h"
#include "exception/EmptyArgumentException.h"

class Argument {
public:
    Argument(const std::string &name, bool aRequired);

    Argument(const std::string &name, bool aRequired, bool boolArg);

    Argument(const std::string &name, bool aRequired, bool boolArg, const std::string &additionalInfo);

    Argument(const std::string &name, bool aRequired, const std::string &additionalInfo);

    const std::string &getName() const;

    void setName(const std::string &name);

    bool isRequired() const;

    void setARequired(bool aRequired);

    bool isBoolArg() const;

    void setBoolArg(bool boolArg);

    const std::string &getValue() const;

    void setValue(const std::string &value);

    int getValueAsInt();

    unsigned long getValueAsUnsignedLong();

    unsigned long getValueAsUnsignedLong(int base);

    bool hasValue();

    const std::string &getAdditionalInfo() const;

    bool hasAdditionalInfo();

private:
    std::string name;
    bool required = false;
    bool boolArg = false;
    std::string value;
    std::string additionalInfo;
};


#endif //PROCVIEW_ARGUMENT_H
