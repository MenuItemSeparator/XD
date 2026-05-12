#pragma once
#include "App/App.h"

namespace nXD
{
    class Solution : public App
    {
    public:
        nXD::Result fn_Init();
        nXD::Result fn_Run();
    };
}