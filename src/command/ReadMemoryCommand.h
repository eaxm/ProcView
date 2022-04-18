#ifndef PROCVIEW_READMEMORYCOMMAND_H
#define PROCVIEW_READMEMORYCOMMAND_H

#include "Command.h"
#include "../os/Process.h"

class ReadMemoryCommand : public Command {

public:
    ReadMemoryCommand();

private:
    void execute() override;
    const int DEFAULT_AMOUNT_BYTES = 1;
};


#endif //PROCVIEW_READMEMORYCOMMAND_H
