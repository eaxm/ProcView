#ifndef PROCVIEW_COMMAND_H
#define PROCVIEW_COMMAND_H

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include "../memlib/Process.h"

class Command {
public:
    void start(std::string input);
    virtual std::string getDescription() = 0;
private:
    std::vector<std::string> splitInput(std::string input);
    virtual void execute(std::vector<std::string> args) = 0; // TODO: Generic

};


#endif //PROCVIEW_COMMAND_H
