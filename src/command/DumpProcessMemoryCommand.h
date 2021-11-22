#ifndef PROCVIEW_DUMPPROCESSMEMORYCOMMAND_H
#define PROCVIEW_DUMPPROCESSMEMORYCOMMAND_H


#include "Command.h"

class DumpProcessMemoryCommand : public Command{
public:
    std::string getDescription() override;
private:
    void execute(std::vector<std::string> args) override;
    std::string description = "Dump process memory";
};


#endif //PROCVIEW_DUMPPROCESSMEMORYCOMMAND_H
