#include <unistd.h>
#include "Process.h"

/**
 * Constructor for Process.
 * Reads process data for the given pid from the proc directory.
 * @param pid process id
 */
Process::Process(int pid) {
    this->pid = pid;

    std::string pidProcPath = PROC_PATH + std::to_string(pid);

    if (!std::filesystem::is_directory(pidProcPath))
        throw ProcessNotFoundException("Could not find directory: " + pidProcPath);

    std::string commPath = pidProcPath.append(COMM_NAME);
    if (!std::filesystem::is_regular_file(commPath))
        throw ProcessNotFoundException("Could not find file: " + commPath);

    std::ifstream t(commPath);
    if (!t.good())
        throw ProcessNotFoundException();

    std::string commProcessName;
    getline(t, commProcessName);
    this->processName = commProcessName;

    struct stat info;
    if (stat(pidProcPath.c_str(), &info) == -1)
        throw ProcessNotFoundException();

    struct passwd *pw = getpwuid(info.st_uid);

    if (pw == nullptr)
        throw ProcessNotFoundException();

    this->user = pw->pw_name;

}


/**
 * Get list of currently running processes
 * @return Processes in a vector
 */
std::vector<Process> Process::getProcessList() {
    std::vector<Process> procList;

    for (const auto &entry: std::filesystem::directory_iterator(PROC_PATH)) {

        if (!entry.is_directory())
            continue;

        std::string dirName = entry.path().filename().string();

        if (!std::all_of(dirName.begin(), dirName.end(), ::isdigit))
            continue;

        Process p(std::stoi(dirName));
        procList.push_back(p);

    }

    return procList;
}

// TODO: Implementation
Process Process::getFirstProcessByName(std::string processName) {
    std::vector<Process> procList = Process::getProcessList();

    throw ProcessNotFoundException("Not implemented yet");
    //throw ProcessNotFoundException("Process " + processName + " not found");

}

/**
 * Returns maps of process from the maps file
 * @return maps in a stringstream
 */
std::stringstream Process::getMaps() {
    std::string mapFilePath = PROC_PATH + std::to_string(pid) + "/maps";
    std::ifstream t(mapFilePath);
    if (!t.is_open()) {
        std::cout << mapFilePath << " not open" << std::endl;
        throw std::exception();
    }
    std::stringstream buffer;
    buffer << t.rdbuf();

    return buffer;
}

/**
 * Returns the starting address of the first memory region whose module name is equal to the given module name.
 * @param moduleName file path of the loaded module
 * @return memory address
 */
unsigned long Process::getModuleBaseAddress(std::string moduleName) {

    std::vector<MemoryRegion> memoryRegions = getMemoryRegions();

    std::vector<MemoryRegion>::iterator it = std::find_if(memoryRegions.begin(), memoryRegions.end(),
                                                          [moduleName](MemoryRegion m) {
                                                              return m.getModulePath() == moduleName;
                                                          });

    if (it != memoryRegions.end()) {
        std::cout << "memory region found: " << std::hex << it->getStartAddress() << std::dec << std::endl;
        return it->getStartAddress();
    } else {
        std::cout << "memory region not found." << std::endl;
        throw ProcessNotFoundException();
    }
}

/**
 * Returns all memory regions of the process.
 * Data is retrieved from the maps file.
 * @return memory regions within a vector
 */
std::vector<MemoryRegion> Process::getMemoryRegions() {

    std::vector<MemoryRegion> memoryRegions;

    std::string item;
    std::stringstream buffer = getMaps();
    while (getline(buffer, item, '\n')) {


        std::istringstream iss(item);
        std::vector<std::string> values(std::istream_iterator<std::string>{iss},
                                        std::istream_iterator<std::string>());


        MemoryRegion memoryRegion;
        // fixme: unreliable parsing
        if (values.size() >= 5) {
            std::string addressRange = values[0];
            //std::cout << "address range: " << addressRange << std::endl;
            std::string startAddress = addressRange.substr(0, addressRange.find('-'));
            std::string endAddress = addressRange.substr(addressRange.find('-') + 1,
                                                         addressRange.length() - 1); // TODO: Check length

            memoryRegion.setStartAddress(std::stoul(startAddress, nullptr, 16));
            memoryRegion.setEndAddress(std::stoul(endAddress, nullptr, 16));

            std::string permissions = values[1];
            memoryRegion.setPermissions(permissions);
        }
        if (values.size() >= 6) {
            std::string path = values[5];
            memoryRegion.setPath(path);
        }

        memoryRegions.push_back(memoryRegion);
    }
    return memoryRegions;
}

std::ostream &operator<<(std::ostream &strm, const Process &p) {
    return strm << "Process(name: " << p.processName << "; pid: " << p.pid << ")";
}

/**
 * Adds up memory space of every memory region
 * @return memory size
 */
unsigned long Process::getVirtualMemorySpace() {
    // TODO: Read value from statm instead
    std::vector<MemoryRegion> memoryRegions = getMemoryRegions();

    unsigned long space = 0;

    for (auto memoryRegion: memoryRegions) {
        space += memoryRegion.getSpace();
    }

    return space;
}

/**
 * Get resident space from statm file
 * @return resident memory size
 */
unsigned long Process::getResidentSpace() {

    std::string statmPath = PROC_PATH + std::to_string(pid) + STATM_NAME;
    if (!std::filesystem::is_regular_file(statmPath))
        throw std::exception(); // TODO: Create an extra exception

    std::ifstream t(statmPath);
    if (!t.good())
        throw std::exception();


    std::string statmContent;
    getline(t, statmContent);


    std::istringstream iss(statmContent);
    std::vector<std::string> statmValues(std::istream_iterator<std::string>{iss},
                                  std::istream_iterator<std::string>());

    if(statmValues.size() < 2)
        throw std::exception();

    long resMemoryPageAmount = std::stoul(statmValues.at(1));

    long pageSize = sysconf(_SC_PAGESIZE);

    unsigned long resMemorySize = resMemoryPageAmount * pageSize;

    return resMemorySize;
}

// TODO: Change method signature for read and write. Return return-value of system calls and throw an exception on failed read/write.
/**
 * Read memory from given address. Data will be written into buffer.
 * @param address Memory address
 * @param length Amount of bytes to read
 * @param buffer Buffer for read data
 * @return If read has succeeded
 */
bool Process::read(unsigned long address, size_t length, void *buffer) {

    struct iovec local[1];
    local[0].iov_base = buffer;
    local[0].iov_len = length;

    struct iovec remote[1];
    remote[0].iov_base = (void *) address;
    remote[0].iov_len = length;

    ssize_t read = process_vm_readv(pid, local, 1, remote, 1, 0);
    return (read != -1);
}

/**
 * Write memory from buffer to given address.
 * @param address Memory address
 * @param length Amount of bytes to write
 * @param buffer Data that will be written to the given address
 * @return If write has succeeded
 */
bool Process::write(unsigned long address, size_t length, void *buffer) {

    struct iovec local[1];
    local[0].iov_base = buffer;
    local[0].iov_len = length;

    struct iovec remote[1];
    remote[0].iov_base = (void *) address;
    remote[0].iov_len = length;

    ssize_t write = process_vm_writev(pid, local, 1, remote, 1, 0);
    return (write != -1);
}

/**
 * Returns process name retrieved from the comm file
 * @return
 */
const std::string &Process::getProcessName() const {
    return processName;
}

/**
 * Returns pid
 * @return
 */
int Process::getPid() const {
    return pid;
}

/**
 * Returns user name retrieved from the file owner of the process directory
 * @return
 */
const std::string &Process::getUser() const {
    return user;
}
