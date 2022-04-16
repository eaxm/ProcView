#include "Process.h"

Process Process::getFirstProcessByName(std::string processName) {
    std::vector<Process> procList = Process::getProcessList();

    throw ProcessNotFoundException("Process " + processName + " not found");
    // TODO: Throw exception
}


Process::Process(int pid) {
    this->pid = pid;
}

Process::Process(int pid, std::string processName, std::string user) {
    this->pid = pid;
    this->processName = processName;
    this->user = user;
}

/**
 * Get list of currently running processes
 * @return Processes in a vector
 */
std::vector<Process> Process::getProcessList() {
    std::vector<Process> procList = {};

    for (const auto &entry: std::filesystem::directory_iterator(PROC_PATH)) {

        if (!entry.is_directory())
            continue;

        std::string dirName = entry.path().filename().string();

        if (!std::all_of(dirName.begin(), dirName.end(), ::isdigit))
            continue;

        std::string commPath = entry.path().string().append(COMM_NAME);

        if (std::filesystem::is_regular_file(commPath)) {

            std::ifstream t(commPath);
            if (!t.good())
                continue;

            std::string commProcessName;
            getline(t, commProcessName);

            struct stat info;
            stat(entry.path().c_str(), &info);
            struct passwd *pw = getpwuid(info.st_uid);

            std::string dirUser = pw->pw_name;
            //std::cout << "pid: " << dirName << std::endl;
            //std::cout << "process name: " << commProcessName << std::endl;
            procList.push_back(Process(std::stol(dirName), commProcessName, dirUser));
            // TODO: ? free(pw);


            //t.close();
        }
    }

    return procList;
}

void Process::read(unsigned long address, size_t length, void *buffer) {

    struct iovec local[1];
    local[0].iov_base = buffer;
    local[0].iov_len = length;

    struct iovec remote[1];
    remote[0].iov_base = (void *) address;
    remote[0].iov_len = length;

    ssize_t read = process_vm_readv(pid, local, 1, remote, 1, 0);
    std::cout << "bytes read: " << read << std::endl;
}

std::stringstream Process::getMaps() {
    std::string mapFilePath = PROC_PATH + std::to_string(pid) + "/maps";
    std::ifstream t(mapFilePath);
    if (!t.is_open()) {
        std::cout << mapFilePath << " not open" << std::endl;
        throw std::exception();
    }
    std::stringstream buffer;
    buffer << t.rdbuf();
    //std::cout << buffer.str();

    return buffer;
    /*
    std::vector<std::string> result;
    std::string item;

    while (getline(buffer, item, '\n'))
    {
        result.push_back(item);
        std::cout << "DBG: " << item << std::endl;
    }
*/

    // TODO: Close?
}

void Process::printModules() {

    std::cout << getMaps().str();

    /*
    std::string mapFilePath = PROC_PATH + std::to_string(pid) + "/maps";
    std::ifstream t(mapFilePath);
    if (!t.is_open())
    {
        std::cout << mapFilePath << " not open" << std::endl;
        return;
    }
    std::stringstream buffer;
    buffer << t.rdbuf();
    //std::cout << buffer.str();

    std::vector<std::string> result;
    std::string item;

    while (getline(buffer, item, '\n'))
    {
        result.push_back(item);
        std::cout << "DBG: " << item << std::endl;
    }

    */

    // TODO: Close?
}

long Process::getModuleBaseAddr(std::string moduleName) {

    std::string item;
    std::stringstream buffer = getMaps();
    while (getline(buffer, item, '\n')) {
        std::string modulePath = getModulePath(item);
        //std::cout << "DBG: " << modulePath << std::endl;

        std::string s = modulePath;
        std::string delimiter = "/";

        size_t pos = 0;
        std::string token;

        size_t last = 0;
        size_t next = 0;
        while ((next = s.find(delimiter, last)) != std::string::npos) {
            std::cout << s.substr(last, next - last) << std::endl;
            last = next + 1;
        }
        //std::cout << s.substr(last) << std::endl;
        std::string lastPart = s.substr(last);

        if (lastPart == moduleName) {
            std::string baseAddrStr = item.substr(0, item.find("-", 0));
            std::cout << "length: " << baseAddrStr.length() << std::endl;
            std::cout << "FOUND Module: " << lastPart << " at 0x" << baseAddrStr << std::endl;

            return std::stol(baseAddrStr, NULL, 16);
        }
    }

    // TODO: Throw an exception
    return -1;
}

std::string Process::getModulePath(std::string line) {
    std::string path = "";

    int startPosition = 73;
    if (line.length() > startPosition) {
        for (int i = startPosition; i < line.length(); i++) {
            path += line.at(i);
        }
    }
    return path;
}

std::vector<MemoryRegion> Process::getMemoryRegions() {

    std::vector<MemoryRegion> memoryRegions;

    std::string item;
    std::stringstream buffer = getMaps();
    while (getline(buffer, item, '\n')) {


        std::istringstream iss(item);
        std::vector<std::string> values(std::istream_iterator<std::string>{iss},
                                        std::istream_iterator<std::string>());


        //std::cout << "values amount: " << values.size() << std::endl;
        if (values.size() > max)
            max = values.size();
        if (values.size() < min)
            min = values.size();

        if (values.size() == 7)
            for (auto val: values) {
                std::cout << val << std::endl;
            }

        MemoryRegion memoryRegion;
        // fixme: unreliable parsing
        if (values.size() >= 5) {
            std::string addressRange = values[0];
            //std::cout << "address range: " << addressRange << std::endl;
            std::string startAddress = addressRange.substr(0, addressRange.find('-'));
            std::string endAddress = addressRange.substr(addressRange.find('-') + 1,
                                                         addressRange.length() - 1); // TODO: Check length

            //std::cout << "start: " << startAddress << "; end: " << endAddress << std::endl;


            memoryRegion.setStartAddress(std::stoul(startAddress, nullptr, 16));
            memoryRegion.setEndAddress(std::stoul(endAddress, nullptr, 16));
            //std::cout << "start: " << memoryRegion.getStartAddress() << "; end: " << memoryRegion.getEndAddress() << std::endl;


            std::string permissions = values[1];
            memoryRegion.setPermissions(permissions);
        }
        if (values.size() >= 6) {
            std::string path = values[5];
            memoryRegion.setPath(path);
        }

        memoryRegions.push_back(memoryRegion);


/*
        std::string modulePath = getModulePath(item);
        //std::cout << "DBG: " << modulePath << std::endl;

        std::string s = modulePath;
        std::string delimiter = "/";

        size_t pos = 0;
        std::string token;

        size_t last = 0;
        size_t next = 0;
        while ((next = s.find(delimiter, last)) != std::string::npos)
        {
            std::cout << s.substr(last, next - last) << std::endl;
            last = next + 1;
        }
        //std::cout << s.substr(last) << std::endl;
        std::string lastPart = s.substr(last);

        if (lastPart == moduleName)
        {
            std::string baseAddrStr = item.substr(0, item.find("-", 0));
            std::cout << "length: " << baseAddrStr.length() << std::endl;
            std::cout << "FOUND Module: " << lastPart << " at 0x" << baseAddrStr << std::endl;

            return std::stol(baseAddrStr, NULL, 16);
        }
*/

    }

    //std::cout << "min: " << min << "; max: " << max << std::endl;
    return memoryRegions;
}

std::ostream &operator<<(std::ostream &strm, const Process &p) {
    return strm << "Process(name: " << p.processName << "; pid: " << p.pid << ")";
}

unsigned long Process::getSpace() {
    std::vector<MemoryRegion> memoryRegions = getMemoryRegions();

    unsigned long space = 0;

    for(auto memoryRegion : memoryRegions){
        space += memoryRegion.getEndAddress()-memoryRegion.getStartAddress();
    }

    return space;
}
