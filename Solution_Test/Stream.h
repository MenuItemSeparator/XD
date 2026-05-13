#pragma once
#include <iostream>
#include <ostream>
#include <sstream>

#include "Log/Log.h"

class StreamChecker
{   
    std::ostringstream oss;
public:
    StreamChecker()
    {
        fn_CheckStream();
    }
    ~StreamChecker() {}

    bool fn_CheckStream()
    {
        fn_Log() << "Data received in StreamChecker." << std::endl;
        fn_Update();
        fn_Log() << "StreamChecker processed the data." << std::endl;
        fn_Update();
        fn_Log() << "Third message." << std::endl;
        fn_Update();

        nXD::Log Log;
        Log.fn_Log() << "Log check in module Log." << std::endl;
        Log.fn_Update();
        Log.fn_Log() << "Log check in module Log 2." << std::endl;
        Log.fn_Update();

        return true;   
    }

    void fn_Update()
    {
        if(oss.str().length() > 0)
        {
            std::cout << "XD MESSAGE: " << oss.str();
            oss.str("");
        }
    }

    std::ostream& fn_Log()
    {
        return oss;
    }
};