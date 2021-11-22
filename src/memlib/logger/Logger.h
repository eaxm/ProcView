#include <iostream>
#include <string>

class Logger
{
public:
    inline static void logInfo(std::string msg)
    {
        std::cout << "[i] " << msg << std::endl;
        
    }


    inline static void logWarn(std::string msg)
    {
        std::cout << "[!] " << msg << std::endl;
    }
};