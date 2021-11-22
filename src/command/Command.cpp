#include "Command.h"


void Command::start(std::string input){
    std::vector<std::string> args = splitInput(input);
    execute(args);
}

std::vector<std::string> Command::splitInput(std::string input) {

    std::istringstream iss(input);
    std::vector<std::string> args(std::istream_iterator<std::string>{iss},
                                  std::istream_iterator<std::string>());

    // TODO: Debug -> Remove
    std::cout << "args:" << std::endl;
    for (const auto &item: args) {
        std::cout << item << std::endl;
    }


    return args;
}

