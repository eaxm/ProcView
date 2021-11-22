#ifndef PROCVIEW_PROCESSNOTFOUNDEXCEPTION_H
#define PROCVIEW_PROCESSNOTFOUNDEXCEPTION_H

#include <exception>

class ProcessNotFoundException : public std::exception
{

private:
    std::string msg = "Process not found";

public:
    inline ProcessNotFoundException(std::string msg)
    {
        this->msg = msg;
    }
    inline ProcessNotFoundException()
    {
    }

    const char* what() const noexcept override
    {
        return msg.c_str();
    }
};

#endif //PROCVIEW_PROCESSNOTFOUNDEXCEPTION_H