#include "ListUsersWithProcessesCommand.h"

std::string ListUsersWithProcessesCommand::getDescription() {
    return description;
}

void ListUsersWithProcessesCommand::execute() {

    std::vector<Process> procList = Process::getProcessList();
    std::map<std::string, int> userProcessAmountMap;

    for (auto &item : procList){
        userProcessAmountMap[item.getUser()]++;
    }



    for (const auto& [key, value] : userProcessAmountMap) {
        std::cout << key << " = " << value << std::endl;
    }

}
