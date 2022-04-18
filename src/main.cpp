#include <iostream>
#include "command/Command.h"
#include "command/ListProcessesCommand.h"
#include "command/ViewProcessInfoCommand.h"
#include "command/DumpProcessMemoryCommand.h"
#include "command/ListUsersWithProcessesCommand.h"
#include "command/SystemCallLoggerCommand.h"
#include "command/StringsCommand.h"
#include "command/ReadMemoryCommand.h"
#include "command/WriteMemoryCommand.h"

int main() {

    // TODO: Check for root privileges and print info if not granted

    std::vector<std::unique_ptr<Command>> commands;
    commands.push_back(std::make_unique<ListProcessesCommand>());
    commands.push_back(std::make_unique<ListUsersWithProcessesCommand>());
    commands.push_back(std::make_unique<ViewProcessInfoCommand>());
    commands.push_back(std::make_unique<DumpProcessMemoryCommand>());
    commands.push_back(std::make_unique<SystemCallLoggerCommand>());
    commands.push_back(std::make_unique<StringsCommand>());
    commands.push_back(std::make_unique<DumpProcessMemoryCommand>());
    commands.push_back(std::make_unique<ReadMemoryCommand>());
    commands.push_back(std::make_unique<WriteMemoryCommand>());

    bool proceed = true;

    std::cout << "ProcView" << std::endl;
    std::cout << "Commands can be selected via the [number]" << std::endl;
    std::cout << "Usage of a command can be viewed via the --help flag. Example: 1 --help" << std::endl << std::endl;

    while (proceed) {
        for (int i = 0; i < commands.size(); i++) {
            int commandNumber = i + 1;
            std::cout << "[" << commandNumber << "]\t" << commands.at(i)->getDescription() << std::endl;
        }
        std::cout << "[0]\tExit" << std::endl;
        std::cout << "Option: ";

        std::string input = "";
        std::getline(std::cin, input);

        if(input.empty()){
            std::cout << "Empty input" << std::endl;
            continue;
        }

        std::string optionNumber = input.substr(0, input.find(' '));

        int number;
        try {
            number = std::stoi(optionNumber);
        } catch (std::invalid_argument &e) {
            std::cout << "Invalid input" << std::endl;
            continue;
        }

        if (number == 0) {
            std::cout << "Exiting..." << std::endl;
            proceed = false;
        } else if (number <= commands.size() && number > 0) {
            try {
                commands.at(--number)->start(input);
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }

        }else {
            std::cout << "Invalid option" << std::endl;
        }


    }


    return 0;
}
