#include "ListProcessesCommand.h"

std::string ListProcessesCommand::getDescription() {

    return description;
}

bool getArg(std::string optionName, int *counter, std::vector<std::string> args, std::string *option){
    if(args.at(*counter) == optionName ){
        if(*option != ""){
            std::cout << "user already set!" << std::endl;
            return false;
        }
        if((*counter)+1 < args.size()){
            *option = args.at(++*counter);
        }else{
            std::cout << "Missing an argument" << std::endl;
            return false;
        }
    }
}

void ListProcessesCommand::execute(std::vector<std::string> args) {

    std::vector<Process> procList = Process::getProcessList();

    std::string argUser = "";
    std::string argProcName = "";

    for(int i = 0; i < args.size(); i++){
        /*
        if(args.at(i) == "--user" ){
            if(argUser != ""){
                std::cout << "user already set!" << std::endl;
                return;
            }
            if(i+1 < args.size()){
                argUser = args.at(++i);
            }else{
                std::cout << "Missing an argument" << std::endl;
                return;
            }
        }
         */

        getArg("--user", &i, args, &argUser);
        getArg("--procName", &i, args, &argProcName);
    }

    if(argUser != ""){
        procList.erase(std::remove_if(procList.begin(), procList.end(), [&argUser]( Process& p){
            return p.getUser() != argUser;
        }), procList.end());
    }
    if(argProcName != ""){
        procList.erase(std::remove_if(procList.begin(), procList.end(), [&argProcName]( Process& p){
            return p.getProcessName() != argProcName;
        }), procList.end());
    }

    std::cout << "PROCESS LIST" << std::endl;
    std::printf("%s\n", std::string(63, '_').c_str());
    std::printf("| %-6s| %-30s| %-20s|\n", "PID", "PROCESS NAME", "USER"); // TODO: Process name not large enough
    for (Process item: procList) {
        //std::cout << item << std::endl;
        // TODO: printf
        std::printf("| %-6d| %-30s| %-20s|\n", item.getPid(), item.getProcessName().c_str(), item.getUser().c_str());
    }
    std::printf("%s\n", std::string(63, '-').c_str());
}