#pragma once

#include "Result.h"

namespace XD{
class App
{
public:
    App();
    ~App();

    XD::Result fn_Init();
    XD::Result fn_Run();
    XD::Result fn_Stop();

private:
    bool Var_IsInitialized;
    bool Var_IsRunning;
};
}