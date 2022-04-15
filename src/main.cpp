#include <iostream>
#include "command/Command.h"
#include "command/ListProcessesCommand.h"
#include "command/ViewProcessInfoCommand.h"
#include "command/DumpProcessMemoryCommand.h"
#include "command/ListUsersWithProcessesCommand.h"

int main() {

    // TODO: Check for root privileges and print info if not granted

    std::vector<std::unique_ptr<Command>> commands;
    commands.push_back(std::make_unique<ListProcessesCommand>());
    commands.push_back(std::make_unique<ListUsersWithProcessesCommand>());
    commands.push_back(std::make_unique<ViewProcessInfoCommand>());
    commands.push_back(std::make_unique<DumpProcessMemoryCommand>());


    bool proceed = true;

    while (proceed) {
        for (int i = 0; i < commands.size(); i++) {
            int commandNumber = i + 1;
            std::cout << "[" << commandNumber << "]\t" << commands.at(i)->getDescription() << std::endl;
            std::cout << "\tUsage: " << std::endl;

        }
        std::cout << "[0] Exit" << std::endl;
        std::cout << "Option: ";

        std::string input = "";
        std::getline(std::cin, input);

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
