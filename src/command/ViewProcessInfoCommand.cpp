#include "ViewProcessInfoCommand.h"


void ViewProcessInfoCommand::execute() {
    int pid = argMap.at("--pid").getValueAsInt();

    Process p(pid);

    std::cout << "Process name: " << p.getProcessName() << std::endl;
    std::cout << "Process id: " << p.getPid() << std::endl;
    std::cout << "User: " << p.getUser() << std::endl;

    std::vector<MemoryRegion> memoryRegions = p.getMemoryRegions();
    std::cout << "Amount of memory regions: " << memoryRegions.size() << std::endl;

    unsigned long space = p.getVirtualMemorySpace();
    std::cout << "virtual memory: " << space << " bytes" << std::endl;
    std::cout << "virtual memory: " << (space / 1e6f) << " megabytes" << std::endl;


    space = p.getResidentSpace();
    std::cout << "resident space: " << space << " bytes" << std::endl;
    std::cout << "resident space: " << (space / 1e6f) << " megabytes" << std::endl << std::endl;

    // TODO: Stack and heap size; Amount of modules loaded

}

ViewProcessInfoCommand::ViewProcessInfoCommand() {
    description = "View process info";

    registerArg(Argument("--pid", true));
}
