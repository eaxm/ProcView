#ifndef PROCVIEW_VIEWPROCESSINFOCOMMAND_H
#define PROCVIEW_VIEWPROCESSINFOCOMMAND_H

#include "Command.h"
#include "../os/Process.h"

class ViewProcessInfoCommand : public Command {
public:
    ViewProcessInfoCommand();

private:
    void execute() override;
};


#endif //PROCVIEW_VIEWPROCESSINFOCOMMAND_H
