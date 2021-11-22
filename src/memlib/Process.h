#ifndef PROCVIEW_PROCESS_H
#define PROCVIEW_PROCESS_H


#include <string>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <fstream>
#include <sys/uio.h>
#include <exception>
//#include <stdexcept>
#include <vector>
#include <pwd.h>
#include <sys/stat.h>
#include "exception/ProcessNotFound.h"


// TODO: Current name is limited to a small amount of chars
/**
 * Class to interact with a process
 */
class Process {

private:
    inline static const std::string PROC_PATH = "/proc/";
    inline static const std::string COMM_NAME = "/comm";

    std::string processName;
    long pid;
    std::string user;

    std::string getModulePath(std::string line);

    friend std::ostream &operator<<(std::ostream &, const Process &);

public:

    Process(long pid);

    Process(long pid, std::string processName, std::string user);

    static Process getFirstProcessByName(std::string processName);

    static std::vector<Process> getProcessesByName(std::string processName);

    static std::vector<Process> getProcessList();

    void read(unsigned long address, size_t length, void *buffer);

    /**
     * Check if process still exists
     * @return true when process still exists
     */
    bool check();

    std::stringstream getMaps();

    void printModules();

    long getModuleBaseAddr(std::string moduleName);

    // TODO: dumpMemory
    // TODO: findSignature
    // TODO: hook -> log args to file & std out
    // packet
    // write/read
    // TODO: inject
    // TODO: getLoadedLibraries
    // TODO: scan
    // choose section

    const inline long getPid() {
        return pid;
    }

    const inline std::string getProcessName() {
        return processName;
    }

    const inline std::string getUser(){
        return user;
    }
};


#endif //PROCVIEW_PROCESS_H