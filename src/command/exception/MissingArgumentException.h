#ifndef PROCVIEW_MISSINGARGUMENTEXCEPTION_H
#define PROCVIEW_MISSINGARGUMENTEXCEPTION_H

#include <exception>
#include <string>

class MissingArgumentException : public std::exception {
private:
    std::string msg = "Unknown argument";

public:
    inline MissingArgumentException(std::string msg){
        this->msg = msg;
    }

    inline MissingArgumentException(){
    }

    const char* what() const noexcept override
    {
        return msg.c_str();
    }
};


#endif //PROCVIEW_MISSINGARGUMENTEXCEPTION_H
