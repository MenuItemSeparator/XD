//"LICENSE"
#pragma once

#include "Common/XD_Log.h"

namespace XD {

class App_Interface
{
public:
    virtual void* fCreateWidget() { return nullptr; }
};

class App
{
public:
    App() {}

    void fLoop() {
        mLOG("Loop is here!");
    }
};


}
