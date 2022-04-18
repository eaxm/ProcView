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


// TODO: Create extra argument class to differentiate between required and optional arguments and to add bool args
/**
 * Class from which commands should inherit
 */
class Command {
public:
    void start(std::string input);
    virtual std::string getDescription();

protected:
    bool registerArg(std::string argName);
    std::map<std::string, std::string> argMap; // contains the values of the parsed arguments
    std::set<std::string> argSet; // registered arguments are in here
    std::string description;

private:
    std::vector<std::string> splitInput(std::string input);
    void parseArgs(std::vector<std::string> args);
    virtual void execute() = 0;

};


#endif //PROCVIEW_COMMAND_H
