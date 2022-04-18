#ifndef PROCVIEW_LISTUSERSWITHPROCESSESCOMMAND_H
#define PROCVIEW_LISTUSERSWITHPROCESSESCOMMAND_H


#include "Command.h"
#include <string>
#include <map>
#include "../os/Process.h"

/**
 * Lists users with their number of processes
 */
class ListUsersWithProcessesCommand : public Command {
public:
    ListUsersWithProcessesCommand();

private:
    void execute() override;
    std::string description = "List users with processes";
};


#endif //PROCVIEW_LISTUSERSWITHPROCESSESCOMMAND_H
