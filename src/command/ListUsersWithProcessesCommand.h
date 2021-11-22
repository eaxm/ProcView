#ifndef PROCVIEW_LISTUSERSWITHPROCESSESCOMMAND_H
#define PROCVIEW_LISTUSERSWITHPROCESSESCOMMAND_H


#include "Command.h"
#include <string>
#include <map>

class ListUsersWithProcessesCommand : public Command {
public:
    std::string getDescription() override;

private:
    void execute(std::vector<std::string> args) override;
    std::string description = "List users with processes";
};


#endif //PROCVIEW_LISTUSERSWITHPROCESSESCOMMAND_H
