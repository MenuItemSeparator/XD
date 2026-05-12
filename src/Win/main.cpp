#include "Solution.h"

int main()
{
    nXD::App app;
    if (app.fn_Init() != (int)nXD::ResultStatus::Success)
        return -1;
    if (app.fn_Run() != (int)nXD::ResultStatus::Success)
        return -1; 
    return (int)nXD::ResultStatus::Success;
}
