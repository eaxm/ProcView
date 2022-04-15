#include "Command.h"


void Command::start(std::string input){
    std::vector<std::string> args = splitInput(input);
    args.erase(args.begin()); // erase menu selection number
    parseArgs(args);
    execute();
    argMap.clear();

}

std::vector<std::string> Command::splitInput(std::string input) {

    std::istringstream iss(input);
    std::vector<std::string> args(std::istream_iterator<std::string>{iss},
                                  std::istream_iterator<std::string>());

    return args;
}

void Command::parseArgs(std::vector<std::string> args) {
    for(int i = 0; i < args.size(); i++){
        std::string argName = args.at(i);

        if(!argSet.contains(argName))
            throw UnknownArgumentException("Unknown argument: " + argName);
        if(i+1 >= args.size())
            throw MissingArgumentException("Missing argument for: " + argName);

        i++;
        std::string arg = args.at(i);
        argMap[argName] = arg;

        std::cout << "argMap[" << argName << "] = " << arg << std::endl;
    }
}

bool Command::registerArg(std::string argName) {
    if(argSet.contains(argName))
        return false;
    argSet.insert(argName);
    return true;
}


std::string Command::getDescription() {
    return description;
}
