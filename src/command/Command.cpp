#include "Command.h"


void Command::start(std::string input) {
    std::vector<std::string> args = splitInput(input);
    args.erase(args.begin()); // erase menu selection number
    parseArgs(args);

    // fixme: Don't use string literals for common argument names
    if (argMap.at("--help").hasValue()) {
        std::cout << "Arguments" << std::endl;
        for (auto arg: argMap) {
            auto val = arg.second;
            // TODO: Format string -> spacing
            std::cout << val.getName() << std::boolalpha << ": required=" <<  val.isRequired() << ", boolFlag=" << val.isBoolArg()
                      << std::endl;
            if(val.hasAdditionalInfo()){
                std::cout << "\t" << val.getAdditionalInfo() << std::endl;
            }
        }
        std::cout << std::endl;
    } else {
        execute();
    }

    // clear values
    for (auto &arg: argMap) {
        arg.second.setValue("");
    }

}

std::vector<std::string> Command::splitInput(std::string input) {

    std::istringstream iss(input);
    std::vector<std::string> args(std::istream_iterator<std::string>{iss},
                                  std::istream_iterator<std::string>());

    return args;
}

// TODO: Rename all these arg variables. At the moment it's confusing.
void Command::parseArgs(std::vector<std::string> args) {
    for (int i = 0; i < args.size(); i++) {
        std::string argName = args.at(i);

        if (!argMap.contains(argName))
            throw UnknownArgumentException("Unknown argument: " + argName);

        auto argEntryValue = argMap.at(argName); // Not sure if the extra var that actually helps the readability

        std::string arg;
        if (argEntryValue.isBoolArg()) {
            arg = "1"; // Just set the value of the argument to something that's not empty, so that we know the bool flag was set. fixme: bad design -> need to change Argument class
        } else {
            if (i + 1 >= args.size())
                throw MissingArgumentException("Missing argument for: " + argName);
            i++;
            arg = args.at(i);
        }

        argMap.at(argName).setValue(arg);
    }
}

bool Command::registerArg(Argument arg) {

    if (argMap.contains(arg.getName()))
        return false;
    return argMap.insert(std::make_pair(arg.getName(),
                                        arg)).second; // second value contains bool that is true if the element was inserted

}


std::string Command::getDescription() {
    return description;
}

Command::Command() {
    registerArg(Argument("--help", false, true));
}
