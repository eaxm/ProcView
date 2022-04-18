#ifndef PROCVIEW_DUMPPROCESSMEMORYCOMMAND_H
#define PROCVIEW_DUMPPROCESSMEMORYCOMMAND_H

#include "Command.h"
#include "../os/Process.h"


/**
 * Dumps processes memory to file
 * Only includes certain memory regions
 */
class DumpProcessMemoryCommand : public Command{
public:
    DumpProcessMemoryCommand();

private:
    static const unsigned long MAX_WRITE = 1e9; // 1 GB
    void execute() override;
};


#endif //PROCVIEW_DUMPPROCESSMEMORYCOMMAND_H
