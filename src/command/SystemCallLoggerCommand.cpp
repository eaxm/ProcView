#include "SystemCallLoggerCommand.h"

SystemCallLoggerCommand::SystemCallLoggerCommand() {
    description = "Log system calls";
    registerArg(Argument("--pid", true));
}


void SystemCallLoggerCommand::execute() {
    int pid = argMap.at("--pid").getValueAsInt();

    long ret = ptrace(PTRACE_ATTACH, pid, NULL, NULL);
    if (ret == -1) {
        if (errno == 1) {
            std::cout << "Insufficient permissions" << std::endl;
        }
        std::cout << "error: " << errno << std::endl;
        return;
    }

    waitpid(pid, NULL, 0);

    // TODO: Exit on specified condition
    for (;;) {
        ret = ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
        if (ret == -1) {
            std::cout << "error: " << errno << std::endl;
            return;
        }

        waitpid(pid, NULL, 0);

        long syscall = ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * ORIG_RAX);
        std::cout << "syscall: " << syscall << std::endl; // TODO: Add time


        // Ignore
        ret = ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
        if (ret == -1) {
            std::cout << "error: " << errno << std::endl;
            return;
        }

        waitpid(pid, NULL, 0);

    }


}
