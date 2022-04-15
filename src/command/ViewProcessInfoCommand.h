#ifndef PROCVIEW_VIEWPROCESSINFOCOMMAND_H
#define PROCVIEW_VIEWPROCESSINFOCOMMAND_H

#include "Command.h"

class ViewProcessInfoCommand : public Command {
public:
    ViewProcessInfoCommand();

private:
    void execute() override;
    std::string description = "View process info";
};


#endif //PROCVIEW_VIEWPROCESSINFOCOMMAND_H
