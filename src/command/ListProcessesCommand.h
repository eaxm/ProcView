#ifndef PROCVIEW_LISTPROCESSESCOMMAND_H
#define PROCVIEW_LISTPROCESSESCOMMAND_H

#include "Command.h"
#include "../os/Process.h"

class ListProcessesCommand : public Command {
public:
    ListProcessesCommand();

private:
    void execute() override;
    std::string description = "List processes";
};


#endif //PROCVIEW_LISTPROCESSESCOMMAND_H
