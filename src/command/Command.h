#ifndef PROCVIEW_COMMAND_H
#define PROCVIEW_COMMAND_H

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <map>
#include <set>
#include "exception/UnknownArgumentException.h"
#include "exception/MissingArgumentException.h"

class Command {
public:
    void start(std::string input);
    virtual std::string getDescription();

protected:
    bool registerArg(std::string argName);
    std::map<std::string, std::string> argMap;
    std::set<std::string> argSet;
    std::string description;

private:
    std::vector<std::string> splitInput(std::string input);
    void parseArgs(std::vector<std::string> args);
    virtual void execute() = 0;

};


#endif //PROCVIEW_COMMAND_H
