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
    inline static const std::string DATA_FORMAT_INFO = "A byte needs to consist of two characters in hex. No spaces between bytes. Example: 0A0B0C";
};


#endif //PROCVIEW_WRITEMEMORYCOMMAND_H
