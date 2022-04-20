#include "MemoryRegion.h"

MemoryRegion::MemoryRegion(unsigned long startAddress, unsigned long endAddress, bool read, bool write, bool execute,
                           const std::string &path) : startAddress(startAddress), endAddress(endAddress),
                                                      read(read), write(write), execute(execute),
                                                      path(path) {}

MemoryRegion::MemoryRegion() {}

unsigned long MemoryRegion::getStartAddress() const {
    return startAddress;
}

void MemoryRegion::setStartAddress(unsigned long startAddress) {
    MemoryRegion::startAddress = startAddress;
}

unsigned long MemoryRegion::getEndAddress() const {
    return endAddress;
}

void MemoryRegion::setEndAddress(unsigned long endAddress) {
    MemoryRegion::endAddress = endAddress;
}

bool MemoryRegion::isRead() const {
    return read;
}

void MemoryRegion::setRead(bool read) {
    MemoryRegion::read = read;
}

bool MemoryRegion::isWrite() const {
    return write;
}

void MemoryRegion::setWrite(bool write) {
    MemoryRegion::write = write;
}

bool MemoryRegion::isExecute() const {
    return execute;
}

void MemoryRegion::setExecute(bool execute) {
    MemoryRegion::execute = execute;
}

bool MemoryRegion::isShared() const {
    return shared;
}

void MemoryRegion::setShared(bool shared) {
    MemoryRegion::shared = shared;
}

bool MemoryRegion::isPrivatePerm() const {
    return privatePerm;
}

void MemoryRegion::setPrivatePerm(bool privatePerm) {
    MemoryRegion::privatePerm = privatePerm;
}

const std::string &MemoryRegion::getModulePath() const {
    return path;
}

void MemoryRegion::setPath(const std::string &path) {
    MemoryRegion::path = path;
}

void MemoryRegion::setPermissions(std::string permissions) {
    if(permissions.length() != 4)
        throw std::invalid_argument("Invalid permission length");

    this->read = permissions[0] == 'r';
    this->write = permissions[1] == 'w';
    this->execute = permissions[2] == 'x';
    this->shared = permissions[3] == 's';
    this->privatePerm = permissions[3] == 'p';

}
/**
 * Subtracts startAddress from endAddress
 * @return memory size
 */
unsigned long MemoryRegion::getSpace() {
    return endAddress - startAddress;
}
