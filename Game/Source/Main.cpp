#include <cstdlib>
#include "FrameworkDummy.h"
#include "Source/XD_Engine.h"
#include "Application/XD_PlatformApplication.h"

int main()
{
    XD::XD_Engine engine{};
    engine.Initialize();
    XD::FrameworkDummy dummy{};
    XD::App App;

    App.fLoop();


    system("pause");

    return 0;
}
