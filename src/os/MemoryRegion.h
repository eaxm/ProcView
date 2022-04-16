#ifndef PROCVIEW_MEMORYREGION_H
#define PROCVIEW_MEMORYREGION_H

#include <string>
#include <stdexcept>

class MemoryRegion {
public:
    MemoryRegion(unsigned long startAddress, unsigned long endAddress, bool readable, bool writable, bool executable,
                 const std::string &path);

    MemoryRegion();

    unsigned long getStartAddress() const;

    void setStartAddress(unsigned long startAddress);

    unsigned long getEndAddress() const;

    void setEndAddress(unsigned long endAddress);

    void setPermissions(std::string permissions);

    bool isRead() const;

    void setRead(bool read);

    bool isWrite() const;

    void setWrite(bool write);

    bool isExecute() const;

    void setExecute(bool execute);

    bool isShared() const;

    void setShared(bool shared);

    bool isPrivatePerm() const;

    void setPrivatePerm(bool privatePerm);

    const std::string &getPath() const;

    void setPath(const std::string &path);

private:
    unsigned long startAddress;
    unsigned long endAddress;

    bool read;
    bool write;
    bool execute;
    bool shared;
    bool privatePerm;

    std::string path;


};


#endif //PROCVIEW_MEMORYREGION_H
