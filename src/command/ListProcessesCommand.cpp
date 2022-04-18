#include "ListProcessesCommand.h"



void ListProcessesCommand::execute() {

    std::vector<Process> procList = Process::getProcessList();

    std::string argUser = argMap["--user"];
    std::string argProcName = argMap["--proc-name"];


    if(!argUser.empty()){
        procList.erase(std::remove_if(procList.begin(), procList.end(), [&argUser]( Process& p){
            return p.getUser() != argUser;
        }), procList.end());
    }
    if(!argProcName.empty()){
        procList.erase(std::remove_if(procList.begin(), procList.end(), [&argProcName]( Process& p){
            return p.getProcessName() != argProcName;
        }), procList.end());
    }

    std::cout << "PROCESS LIST" << std::endl;
    std::printf("%s\n", std::string(63, '_').c_str());
    std::printf("| %-6s| %-30s| %-20s|\n", "PID", "PROCESS NAME", "USER");
    for (Process item: procList) {
        std::printf("| %-6d| %-30s| %-20s|\n", item.getPid(), item.getProcessName().c_str(), item.getUser().c_str());
    }
    std::printf("%s\n", std::string(63, '-').c_str());
}

ListProcessesCommand::ListProcessesCommand() {
    Command::description = "List processes";

    Command::registerArg("--user");
    Command::registerArg("--proc-name");
}
