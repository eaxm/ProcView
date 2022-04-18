#include "ReadMemoryCommand.h"

ReadMemoryCommand::ReadMemoryCommand() {
    description = "Read memory";

    registerArg("--pid");
    registerArg("--address");       // address is relative to module if module is specified
    registerArg("--amount");        // amount of bytes to read
    registerArg("--file-path");     // path name
}

void ReadMemoryCommand::execute() {

    std::string strPid = argMap["--pid"]; // in dec
    int pid = std::stoi(strPid);

    std::string strAddress = argMap["--address"]; // in hex
    unsigned long address = std::stoul(strAddress, 0, 16);

    std::string strAmount = argMap["--amount"]; // in dec
    int amount = std::stoi(strAmount);


    Process p(pid);

    std::byte *buffer = (std::byte *) std::malloc(amount);

    if (!p.read(address, amount, buffer)) {
        std::cout << "Could not read memory" << std::endl;
        free(buffer);
        return;
    }

    std::cout << "Read memory: " << std::hex;
    for(int i = 0; i < amount; i++){
        std::byte b = buffer[i];
        std::cout << (int)b << " ";
    }
    std::cout << std::endl;

    free(buffer);
}
