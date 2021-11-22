#ifndef PROCVIEW_VIEWPROCESSINFOCOMMAND_H
#define PROCVIEW_VIEWPROCESSINFOCOMMAND_H

#include "Command.h"

class ViewProcessInfoCommand : public Command {
public:
    std::string getDescription() override;
private:
    void execute(std::vector<std::string> args) override;
    std::string description = "View process info";
};


#endif //PROCVIEW_VIEWPROCESSINFOCOMMAND_H
