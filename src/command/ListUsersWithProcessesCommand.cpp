#include "ListUsersWithProcessesCommand.h"


void ListUsersWithProcessesCommand::execute() {

    std::vector<Process> procList = Process::getProcessList();
    std::map<std::string, int> userProcessAmountMap;

    for (auto &item: procList) {
        userProcessAmountMap[item.getUser()]++;
    }


    std::cout << "USERS WITH PROCESSES" << std::endl;
    std::printf("%s\n", std::string(45, '_').c_str());
    std::printf("| %-30s| %-10s|\n", "USER", "AMOUNT");
    for (const auto &[key, value]: userProcessAmountMap) {
        std::printf("| %-30s| %-10d|\n", key.c_str(), value);
    }
    std::printf("%s\n", std::string(45, '-').c_str());

}

ListUsersWithProcessesCommand::ListUsersWithProcessesCommand() {
    description = "List users with processes";
}
