#ifndef PROCVIEW_READMEMORYCOMMAND_H
#define PROCVIEW_READMEMORYCOMMAND_H

#include "Command.h"
#include "../os/Process.h"

class ReadMemoryCommand : public Command {

public:
    ReadMemoryCommand();

private:
    void execute() override;
};


#endif //PROCVIEW_READMEMORYCOMMAND_H
