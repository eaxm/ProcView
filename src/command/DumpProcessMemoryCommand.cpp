#include "DumpProcessMemoryCommand.h"

void DumpProcessMemoryCommand::execute() {
    std::string strPid = argMap["--pid"];
    int pid = std::stoi(strPid);


    Process p(pid);
    std::vector<MemoryRegion> memoryRegions = p.getMemoryRegions();


    std::time_t time = std::time(nullptr);

    std::string dumpName = "proc_dump_" + std::to_string(time) + "_" + strPid;
    std::cout << "dump name: " << dumpName << std::endl;


    std::ofstream of;
    of.open(dumpName, std::ios_base::app);


    for(auto m : memoryRegions){
        if (m.isShared() || m.getPath().empty() || !m.isRead())
            continue;

        unsigned long size = m.getSpace();
        char *buffer = (char *) std::malloc(size);
        p.read(m.getStartAddress(), size, buffer);

        of.write(buffer, size);


        std::free(buffer);
    }



}

DumpProcessMemoryCommand::DumpProcessMemoryCommand() {
    description = "Dump process memory";

    registerArg("--pid");
}
