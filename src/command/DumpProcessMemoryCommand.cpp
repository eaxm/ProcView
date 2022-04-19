#include "DumpProcessMemoryCommand.h"

void DumpProcessMemoryCommand::execute() {
    int pid = argMap.at("--pid").getValueAsInt();


    Process p(pid);
    std::vector<MemoryRegion> memoryRegions = p.getMemoryRegions();


    std::time_t time = std::time(nullptr);

    std::string dumpName = "proc_dump_" + std::to_string(time) + "_" + std::to_string(pid);
    std::cout << "dump name: " << dumpName << std::endl;


    std::ofstream of;
    of.open(dumpName, std::ios_base::app);

    unsigned long writeCounter = 0;

    for(auto m : memoryRegions){
        if (m.isShared() || m.getModulePath().empty() || !m.isRead())
            continue;

        unsigned long size = m.getSpace();
        char *buffer = (char *) std::malloc(size);

        if(p.read(m.getStartAddress(), size, buffer)){
            writeCounter += size;
            if(writeCounter >= MAX_WRITE){
                std::cout << "Process dump exceeded MAX_WRITE size" << std::endl;
                std::free(buffer);
                return;
            }

            of.write(buffer, size);
        }



        std::free(buffer);
    }



}

DumpProcessMemoryCommand::DumpProcessMemoryCommand() {
    description = "Dump process memory";

    registerArg(Argument("--pid", true));
}
