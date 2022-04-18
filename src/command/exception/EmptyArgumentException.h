#ifndef PROCVIEW_EMPTYARGUMENTEXCEPTION_H
#define PROCVIEW_EMPTYARGUMENTEXCEPTION_H

#include <exception>
#include <string>

/**
 * Thrown when an argument is empty
 */
class EmptyArgumentException : public std::exception {
private:
    std::string msg = "Empty argument";

public:
    inline EmptyArgumentException(std::string msg) {
        this->msg = msg;
    }

    inline EmptyArgumentException() {
    }

    const char *what() const noexcept override {
        return msg.c_str();
    }
};

#endif //PROCVIEW_EMPTYARGUMENTEXCEPTION_H
