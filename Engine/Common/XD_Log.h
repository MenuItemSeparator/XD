#pragma once

#include <iostream>

namespace XD
{

    class XD_Log
    {
    public:
        XD_Log* operator << (char* ) {return nullptr;}

    };

    #define mLOG(text) std::cout<<text

}
