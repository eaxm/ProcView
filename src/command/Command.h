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
#include "Argument.h"

/**
 * Class from which commands should inherit
 */
class Command {
public:
    void start(std::string input);
    virtual std::string getDescription();

    Command();

protected:
    bool registerArg(Argument arg);
    std::map<std::string, Argument> argMap; // fixme: argument name is currently stored twice
    std::string description;

private:
    std::vector<std::string> splitInput(std::string input);
    void parseArgs(std::vector<std::string> args);
    virtual void execute() = 0;

};


#endif //PROCVIEW_COMMAND_H
