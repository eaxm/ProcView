#include "ReadMemoryCommand.h"

ReadMemoryCommand::ReadMemoryCommand() {
    description = "Read from process memory";

    registerArg(Argument("--pid", true));
    registerArg(Argument("--address", true));       // address is relative to module if module is specified
    registerArg(Argument("--amount", false));       // amount of bytes to read
    registerArg(Argument("--module", false));       // file path of module
}

void ReadMemoryCommand::execute() {
    int pid = argMap.at("--pid").getValueAsInt();
    unsigned long address = argMap.at("--address").getValueAsUnsignedLong(16);

    int amount = DEFAULT_AMOUNT_BYTES;
    auto argAmount = argMap.at("--amount");
    if(argAmount.hasValue()){
        amount = argAmount.getValueAsInt();
        if(amount <= 0)
            throw std::invalid_argument("amount is below 1");
    }


    Process p(pid);

    auto argModule = argMap.at("--module");
    if(argModule.hasValue()){
        // if file path to module has been given, treat address as a relative address.
        std::string moduleFilePath = argModule.getValue();
        unsigned long baseAddress = p.getModuleBaseAddress(moduleFilePath);
        address += baseAddress;
    }


    std::byte *buffer = (std::byte *) std::malloc(amount);

    // TODO: Check memory region permissions
    if (!p.read(address, amount, buffer)) {
        std::cout << "Could not read memory" << std::endl;
        std::free(buffer);
        return;
    }

    std::cout << "Read memory: " << std::hex;
    for(int i = 0; i < amount; i++){
        std::byte b = buffer[i];
        std::cout << (int)b << " ";
    }
    std::cout << std::dec << std::endl; // set cout back to dec and print a new line

    std::free(buffer);
}
