#ifndef PROCVIEW_SYSTEMCALLLOGGERCOMMAND_H
#define PROCVIEW_SYSTEMCALLLOGGERCOMMAND_H

#include "Command.h"
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/wait.h>
#include <thread>
#include <atomic>

/**
 * Attaches to the given process and logs system calls
 */
class SystemCallLoggerCommand : public Command {

public:
    SystemCallLoggerCommand();
    inline static int gPid;

private:
    void execute() override;
    void systemCallLogger(int pid);
    std::atomic<bool> proceed;
};


#endif //PROCVIEW_SYSTEMCALLLOGGERCOMMAND_H
