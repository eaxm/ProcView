#ifndef PROCVIEW_WRITEMEMORYCOMMAND_H
#define PROCVIEW_WRITEMEMORYCOMMAND_H

#include "Command.h"
#include "../os/Process.h"

// TODO: Create memory access class from which read/write memory inherit to avoid duplicate code
class WriteMemoryCommand : public Command {

public:
    WriteMemoryCommand();

private:
    void execute() override;
};


#endif //PROCVIEW_WRITEMEMORYCOMMAND_H
