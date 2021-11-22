#include <iostream>
#include <iterator>
#include <memory>
#include "memlib/Process.h"
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





/*
    const std::string OPTIONS = "[1] List processes\n"
                                "[2] View process info of pid\n"
                                "\t<pid>\n"
                                "[3] Read memory\n"
                                "\t<address> <amount of bytes>\n"
                                "\t<module name> <address> <amount of bytes>\n"
                                "[4] Write memory\n"
                                "\t<address> <byte>\n"
                                "\t<module name> <address> <byte>\n"
                                "[0] Exit";

*/
    bool proceed = true;

    while (proceed) {
        for(int i = 0; i < commands.size(); i++){
            int commandNumber = i+1;
            std::cout << "[" << commandNumber << "] " << commands.at(i)->getDescription() << std::endl;
        }
        std::cout << "[0] Exit" << std::endl;

        std::string input = "";
        //std::cin >> input;
        std::getline(std::cin, input);

        char firstChar = input.front();

        int number = std::atoi(&firstChar); // TODO: No error check atm
        if(number == 0){
            proceed = false;
        }
        else if(number <= commands.size() && number > 0){
            commands.at(--number)->start(input);
        }else{
            std::cout << "Invalid input" << std::endl;
        }
/*
        switch (firstChar) {
            case '0':
                proceed = false;
                break;
            case '1': {

                ListProcessesCommand lpc;
                std::cout << lpc.getDescription() << std::endl;
                lpc.start(input);

                std::cout << "[i] PROCESS LIST" << std::endl;
                std::vector<Process> procListt = Process::getProcessList();
                for (const auto &item: procListt) {
                    std::cout << item << std::endl;
                }

            }
                break;
            case '2':
                std::cout << "2" << std::endl;
                break;
            case '3': {


                long pid;
                std::istringstream iss(input);
                std::vector<std::string> args(std::istream_iterator<std::string>{iss},
                                              std::istream_iterator<std::string>());

                std::cout << "args:" << std::endl;
                for (const auto &item : args){
                    std::cout << item << std::endl;
                }

                //Process p(pid);
            }

                break;
            default:
                std::cout << "Invalid input" << std::endl;
        }

        std::cout << std::endl;
*/
    }

    //Process::getProcessList();


    return 0;
}
