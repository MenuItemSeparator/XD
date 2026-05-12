#pragma once

#include "Result.h"

namespace nXD{
class App
{
public:
    App();
    ~App();

    nXD::Result fn_Init();
    nXD::Result fn_Run();
    nXD::Result fn_Stop();

private:
    bool Var_IsInitialized;
    bool Var_IsRunning;
};
}