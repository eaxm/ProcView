#include "StringsCommand.h"

StringsCommand::StringsCommand() {
    description = "Scan process for strings";

    registerArg(Argument("--pid", true));
    registerArg(Argument("--min-length", false));
    registerArg(Argument("--module", false));
}

void StringsCommand::execute() {
    int pid = argMap.at("--pid").getValueAsInt();

    int currentMinLength = DEFAULT_MIN_LENGTH;
    auto argMinLength = argMap.at("--min-length");
    if(argMinLength.hasValue()){
        currentMinLength = argMap.at("--min-length").getValueAsInt();
        if(currentMinLength <= 0)
            throw std::invalid_argument("minLength is below 1");
    }


    Process p(pid);
    std::vector<MemoryRegion> memoryRegions = p.getMemoryRegions();

    auto argModule = argMap.at("--module");
    if(argModule.hasValue()){
        std::string module = argModule.getValue();
        memoryRegions.erase(std::remove_if(memoryRegions.begin(), memoryRegions.end(), [module] (MemoryRegion m) {
            return m.getModulePath() != module;
        }), memoryRegions.end());
    }

    for (auto m: memoryRegions) {
        if (m.isShared() || m.getModulePath().empty() || !m.isRead())
            continue;

        unsigned long size = m.getSpace();
        char *buffer = (char *) std::malloc(size);
        if(!p.read(m.getStartAddress(), size, buffer)){
            std::free(buffer);
            continue;
        }

        std::string temp;
        for (int i = 0; i < size; i++) {
            char c = buffer[i];

            if(!std::isprint(c) && c != '\0'){
                temp.clear();
            } else if(c != '\0'){
                temp += c;
            }else{
                if (temp.length() >= currentMinLength) {
                    std::cout << "found string: " << temp << std::endl;
                    std::cout << "location: " << m.getModulePath() << " + 0x" << std::hex << i << std::dec << std::endl << std::endl;
                }
                temp.clear();
            }

        }

        std::free(buffer);
    }

}


