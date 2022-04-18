#ifndef PROCVIEW_VIEWPROCESSINFOCOMMAND_H
#define PROCVIEW_VIEWPROCESSINFOCOMMAND_H

#include "Command.h"
#include "../os/Process.h"
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>

class ViewProcessInfoCommand : public Command {
public:
    ViewProcessInfoCommand();

private:
    void execute() override;
};


#endif //PROCVIEW_VIEWPROCESSINFOCOMMAND_H
