#ifndef PROCVIEW_MODULENOTFOUNDEXCEPTION_H
#define PROCVIEW_MODULENOTFOUNDEXCEPTION_H

#include <exception>
#include <string>

/**
 * Thrown when memory region with given module file path was not found
 */
class ModuleNotFoundException : public std::exception {

private:
    std::string msg = "Module not found";

public:
    inline ModuleNotFoundException(std::string msg) {
        this->msg = msg;
    }

    inline ModuleNotFoundException() {
    }

    const char *what() const noexcept override {
        return msg.c_str();
    }
};

#endif //PROCVIEW_MODULENOTFOUNDEXCEPTION_H
