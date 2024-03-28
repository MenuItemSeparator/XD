#include "FrameworkDummy.h"
#include "Application/XD_PlatformApplication.h"

int main()
{
    XD::FrameworkDummy dummy{};
    XD::App App;

    App.fLoop();
    return 0;
}
