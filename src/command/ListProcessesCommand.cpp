#include "ListProcessesCommand.h"

std::string ListProcessesCommand::getDescription() {

    return description;
}


void ListProcessesCommand::execute(std::vector<std::string> args) {
    std::cout << "[i] PROCESS LIST" << std::endl;
    std::vector<Process> procList = Process::getProcessList();

    std::printf("%s\n", std::string(60, '_').c_str());
    std::printf("|%-6s|%-30s|%-20s|\n", "PID", "PROCESS NAME", "USER");
    for (Process item: procList) {
        //std::cout << item << std::endl;
        // TODO: printf
        std::printf("|%-6d|%-30s|%-20s|\n", item.getPid(), item.getProcessName().c_str(), item.getUser().c_str());
    }
    std::printf("%s\n", std::string(60, '-').c_str());
}