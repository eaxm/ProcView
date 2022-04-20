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
#include "exception/ProcessNotFoundException.h"
#include "MemoryRegion.h"
#include <iterator>


/**
 * Class to interact with a process
 */
class Process {

private:
    inline static const std::string PROC_PATH = "/proc/";
    inline static const std::string COMM_NAME = "/comm";
    inline static const std::string STATM_NAME = "/statm";

    std::string processName;
    int pid;
    std::string user;

    friend std::ostream &operator<<(std::ostream &, const Process &);
    std::stringstream getMaps();

public:

    Process(int pid);

    static Process getFirstProcessByName(std::string processName);

    static std::vector<Process> getProcessesByName(std::string processName);

    static std::vector<Process> getProcessList();

    bool read(unsigned long address, size_t length, void *buffer);

    bool write(unsigned long address, size_t length, void *buffer);

    unsigned long getModuleBaseAddress(std::string moduleName);

    std::vector<MemoryRegion> getMemoryRegions();

    unsigned long getVirtualMemorySpace();

    unsigned long getResidentSpace();

    const std::string &getProcessName() const;

    int getPid() const;

    const std::string &getUser() const;
};


#endif //PROCVIEW_PROCESS_H