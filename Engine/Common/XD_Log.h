#pragma once

#include <iostream>

namespace XD{

class Log
{
public:
    Log* operator << (char* ) {return nullptr;}
}Log;

#define mLOG(text) std::cout<<text

}
