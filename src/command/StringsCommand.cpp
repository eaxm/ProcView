#include "StringsCommand.h"

StringsCommand::StringsCommand() {
    description = "Scan process for strings";

    registerArg("--pid");
    registerArg("--min-length");
}

void StringsCommand::execute() {

    std::string strPid = argMap["--pid"]; // TODO: Handle empty arg
    int pid = std::stoi(strPid);

    std::string strMinLength = argMap["--min-length"];
    int currentMinLength = DEFAULT_MIN_LENGTH;
    if(!strMinLength.empty()){
        currentMinLength = std::stoi(strMinLength);
        if(currentMinLength <= 0)
            throw std::invalid_argument("minLength is below 1");
    }

    // TODO: Add argument to print module and address


    Process p(pid);

    std::vector<MemoryRegion> memoryRegions = p.getMemoryRegions();


    for (auto m: memoryRegions) {
        if (m.isShared() || m.getPath().empty() || !m.isRead())
            continue;

        unsigned long size = m.getSpace();
        char *buffer = (char *) std::malloc(size);
        p.read(m.getStartAddress(), size, buffer);

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
                }
                temp.clear();
            }

        }

        std::free(buffer);
    }

}


