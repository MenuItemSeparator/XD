#include "../_mod/_app/App.h"
#include "_app/Result.h"

int main()
{
    XD::App app;
    if (app.fn_Init() != (int)XD::ResultStatus::Success)
        return -1;
    if (app.fn_Run() != (int)XD::ResultStatus::Success)
        return -1; 
    return (int)XD::ResultStatus::Success;
}
