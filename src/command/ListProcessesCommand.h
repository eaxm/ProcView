#ifndef PROCVIEW_LISTPROCESSESCOMMAND_H
#define PROCVIEW_LISTPROCESSESCOMMAND_H

#include "Command.h"
#include "../os/Process.h"

/**
 * Lists all Processes
 * Possible filters: pid and process name
 */
class ListProcessesCommand : public Command {
public:
    ListProcessesCommand();

private:
    void execute() override;
};


#endif //PROCVIEW_LISTPROCESSESCOMMAND_H
