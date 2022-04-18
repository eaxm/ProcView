#include "ListProcessesCommand.h"



void ListProcessesCommand::execute() {

    std::vector<Process> procList = Process::getProcessList();

    auto argUser = argMap.at("--user");
    if(argUser.hasValue()){
        std::string user = argUser.getValue();
        procList.erase(std::remove_if(procList.begin(), procList.end(), [&user]( Process& p){
            return p.getUser() != user;
        }), procList.end());
    }

    auto argProcName = argMap.at("--proc-name");
    if(argProcName.hasValue()){
        std::string procName = argProcName.getValue();
        procList.erase(std::remove_if(procList.begin(), procList.end(), [&procName]( Process& p){
            return p.getProcessName() != procName;
        }), procList.end());
    }


    // TODO: Make table size dynamic or cut off string at a defined length -> Table class
    std::cout << "PROCESS LIST" << std::endl;
    std::printf("%s\n", std::string(63, '_').c_str());
    std::printf("| %-6s| %-30s| %-20s|\n", "PID", "PROCESS NAME", "USER");
    for (Process item: procList) {
        std::printf("| %-6d| %-30s| %-20s|\n", item.getPid(), item.getProcessName().c_str(), item.getUser().c_str());
    }
    std::printf("%s\n", std::string(63, '-').c_str());
}

ListProcessesCommand::ListProcessesCommand() {
    description = "List processes";

    registerArg(Argument("--user", false));
    registerArg(Argument("--proc-name", false));
}
