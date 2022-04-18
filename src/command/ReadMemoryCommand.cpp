#include "ReadMemoryCommand.h"

ReadMemoryCommand::ReadMemoryCommand() {
    description = "Read from process memory";

    registerArg(Argument("--pid", true));
    registerArg(Argument("--address", true));       // address is relative to module if module is specified
    registerArg(Argument("--amount", false));       // amount of bytes to read
    registerArg(Argument("--file-path", false));    // path name
}

void ReadMemoryCommand::execute() {
    int pid = argMap.at("--pid").getValueAsInt();
    unsigned long address = argMap.at("--address").getValueAsUnsignedLong(16);

    int amount = DEFAULT_AMOUNT_BYTES;
    auto argAmount = argMap.at("--amount");
    if(argAmount.hasValue())
        amount = argAmount.getValueAsInt();


    Process p(pid);

    std::byte *buffer = (std::byte *) std::malloc(amount);

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
    std::cout << std::endl;

    std::free(buffer);
}
