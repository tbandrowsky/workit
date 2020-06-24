
#pragma once

#include <string>

class command 
{

    int run();
    std::string commandText;

public:

    command();

    std::string to_string(std::string val)
    {
        return val;
    }

    std::string to_string(long val)
    {
        return std::to_string(val);
    }

    std::string to_string(double val)
    {
        return std::to_string(val);
    }

    template <typename T, typename... Types>
    int run(T var1, Types... var2)
    {
        std::string t = to_string( var1 );
        commandText += t;
        int r = run(var2...);
        return r;
    }
};

