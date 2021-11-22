#ifndef PROCVIEW_LISTPROCESSESCOMMAND_H
#define PROCVIEW_LISTPROCESSESCOMMAND_H

#include "Command.h"


class ListProcessesCommand : public Command {
public:
    std::string getDescription() override;
private:
    void execute(std::vector<std::string> args) override;
    std::string description = "List processes";
};


#endif //PROCVIEW_LISTPROCESSESCOMMAND_H
