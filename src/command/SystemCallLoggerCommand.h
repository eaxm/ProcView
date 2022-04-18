#ifndef PROCVIEW_SYSTEMCALLLOGGERCOMMAND_H
#define PROCVIEW_SYSTEMCALLLOGGERCOMMAND_H

#include "Command.h"
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/wait.h>

/*
 * Attaches to the given process and logs system calls
 */
class SystemCallLoggerCommand : public Command {

public:
    SystemCallLoggerCommand();

private:
    void execute() override;
};


#endif //PROCVIEW_SYSTEMCALLLOGGERCOMMAND_H
