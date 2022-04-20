#include "SystemCallLoggerCommand.h"

SystemCallLoggerCommand::SystemCallLoggerCommand() {
    description = "Log system calls";
    registerArg(Argument("--pid", true));
}


void SystemCallLoggerCommand::systemCallLogger(int pid) {

    long ret = ptrace(PTRACE_ATTACH, pid, NULL, NULL);
    if (ret == -1) {
        if (errno == 1) {
            std::cout << "Insufficient permissions" << std::endl;
        }
        std::cout << "error: " << errno << std::endl;
        return;
    }

    waitpid(pid, NULL, 0);


    while (proceed) {
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

    ret = ptrace(PTRACE_DETACH, pid, NULL, NULL);
    if (ret == -1) {
        std::cout << "error: " << errno << std::endl;
        return;
    }

}

void SystemCallLoggerCommand::execute() {
    int pid = argMap.at("--pid").getValueAsInt();

    proceed = true;

    std::thread t(&SystemCallLoggerCommand::systemCallLogger, this, pid);

    std::cout << "Press any key to exit the system call logger" << std::endl;
    getchar();

    proceed = false;
    std::cout << "Exiting on next system call" << std::endl; // TODO: Not optimal

    t.join();
}
