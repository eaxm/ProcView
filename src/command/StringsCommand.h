#ifndef PROCVIEW_STRINGSCOMMAND_H
#define PROCVIEW_STRINGSCOMMAND_H

#include "Command.h"
#include "../os/Process.h"
#include <stdexcept>

/**
 * Scans memory of process for strings and prints them to stdout
 */
class StringsCommand : public Command {

public:
    StringsCommand();

private:
    void execute() override;
    static const int DEFAULT_MIN_LENGTH = 20;
};


#endif //PROCVIEW_STRINGSCOMMAND_H
