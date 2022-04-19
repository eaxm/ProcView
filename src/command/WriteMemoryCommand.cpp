#include "WriteMemoryCommand.h"

WriteMemoryCommand::WriteMemoryCommand() {
    description = "Write to process memory";

    registerArg(Argument("--pid", true));
    registerArg(Argument("--address", true));       // address is relative to module if module is specified
    registerArg(Argument("--data", true));          // bytes to write
    registerArg(Argument("--module", false));       // file path of module
}


void WriteMemoryCommand::execute() {

    int pid = argMap.at("--pid").getValueAsInt();
    unsigned long address = argMap.at("--address").getValueAsUnsignedLong(16);

    std::string data = argMap.at("--data").getValue();

    Process p(pid);

    auto argModule = argMap.at("--module");
    if(argModule.hasValue()){
        // if file path to module has been given, treat address as a relative address.
        std::string moduleFilePath = argModule.getValue();
        unsigned long baseAddress = p.getModuleBaseAddress(moduleFilePath);
        address += baseAddress;
    }

    if (data.length() % 2)
        throw std::invalid_argument("The bytes in the argument always need to have two characters. Example: 0F");

    //std::vector<std::byte> bytes;

    size_t size = data.length() / 2;
    std::byte *byteBuffer = (std::byte *) malloc(size);

    try {
        for (int i = 0; i < data.length(); i += 2) {
            std::string strTmpByte = data.substr(i, 2); // Should be safe because of the modulo check?
            //std::cout << strTmpByte << std::endl;
            byteBuffer[i / 2] = (std::byte) std::stoi(strTmpByte, 0, 16);
        }
    } catch (std::invalid_argument &e) {
        std::free(byteBuffer);
        throw e;
    }


    // TODO: Check memory region permissions
    if (!p.write(address,size,byteBuffer)) {
        std::cout << "Could not read memory" << std::endl;
        std::free(byteBuffer);
        return;
    }


    std::free(byteBuffer);
}
