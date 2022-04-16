#ifndef PROCVIEW_PROCESS_H
#define PROCVIEW_PROCESS_H


#include <string>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <fstream>
#include <sys/uio.h>
#include <exception>
#include <vector>
#include <pwd.h>
#include <sys/stat.h>
#include "exception/ProcessNotFound.h"
#include "MemoryRegion.h"
#include <iterator>


// TODO: Current name is limited to a small amount of chars
/**
 * Class to interact with a process
 */
class Process {

private:
    inline static const std::string PROC_PATH = "/proc/";
    inline static const std::string COMM_NAME = "/comm";

    std::string processName;
    int pid;
    std::string user;

    std::string getModulePath(std::string line);

    friend std::ostream &operator<<(std::ostream &, const Process &);
    int min = 10;
    int max = 1;
public:

    Process(int pid);

    Process(int pid, std::string processName, std::string user);

    static Process getFirstProcessByName(std::string processName);

    //static Process getProcessByPid(int pid);

    static std::vector<Process> getProcessesByName(std::string processName);

    static std::vector<Process> getProcessList();

    void read(unsigned long address, size_t length, void *buffer);


    std::stringstream getMaps();

    void printModules();

    // TODO: unsigned long
    long getModuleBaseAddr(std::string moduleName);

    std::vector<MemoryRegion> getMemoryRegions();

    unsigned long getSpace();

    const inline long getPid() {
        return pid;
    }

    const inline std::string getProcessName() {
        return processName;
    }

    const inline std::string getUser() {
        return user;
    }
};


#endif //PROCVIEW_PROCESS_H