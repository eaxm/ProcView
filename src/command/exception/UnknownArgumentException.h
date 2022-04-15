#ifndef PROCVIEW_UNKNOWNARGUMENTEXCEPTION_H
#define PROCVIEW_UNKNOWNARGUMENTEXCEPTION_H

#include <exception>

class UnknownArgumentException : public std::exception {
private:
    std::string msg = "Unknown argument";

public:
    inline UnknownArgumentException(std::string msg){
        this->msg = msg;
    }

    inline UnknownArgumentException(){
    }

    const char* what() const noexcept override
    {
        return msg.c_str();
    }
};


#endif //PROCVIEW_UNKNOWNARGUMENTEXCEPTION_H
