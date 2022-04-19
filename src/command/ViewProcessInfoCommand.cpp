#include "ViewProcessInfoCommand.h"


void ViewProcessInfoCommand::execute() {
    int pid = argMap.at("--pid").getValueAsInt();

    Process p(pid);

    std::vector<MemoryRegion> memoryRegions = p.getMemoryRegions();
    std::cout << "mem region size: " << memoryRegions.size() << std::endl;

    std::cout << "Process name: " << p.getProcessName() << std::endl;

    unsigned long space = p.getVirtualMemorySpace();
    std::cout << "space: " << space << " bytes" << std::endl;
    std::cout << "space: " << (space / 1e6f) << " megabytes" << std::endl;

    space = p.getResidentSpace();
    std::cout << "res space: " << space << " bytes" << std::endl;
    std::cout << "res space: " << (space / 1e6f) << " megabytes" << std::endl;




}

ViewProcessInfoCommand::ViewProcessInfoCommand() {
    description = "View process info";

    registerArg(Argument("--pid", true));
}
