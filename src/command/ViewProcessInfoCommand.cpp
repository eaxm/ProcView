#include "ViewProcessInfoCommand.h"


void ViewProcessInfoCommand::execute() {
    std::string strPid = argMap["--pid"]; // TODO: Handle empty entry

    int pid = std::stoi(strPid);

    Process p(pid);

   // std::cout << p.getMaps().str() << std::endl;
    std::vector<MemoryRegion> memoryRegions = p.getMemoryRegions();
    std::cout << "mem region size: " << memoryRegions.size() << std::endl;

    unsigned long space = p.getSpace();
    std::cout << "space: " << space << " bytes" << std::endl;
    std::cout << "space: " << (space/1e6f) << " megabytes" << std::endl;

}

ViewProcessInfoCommand::ViewProcessInfoCommand() {
    Command::description = "View process info";
    Command::registerArg("--pid");
}
