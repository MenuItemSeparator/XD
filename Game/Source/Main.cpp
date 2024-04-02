#include <cstdlib>
#include "XDEngine_Minimal.h"
#include "FrameworkDummy.h"
#include "Source/XD_Engine.h"
#include "Application/XD_Application.h"
#include "Application/XD_Window_Widget.h"

int main()
{
    XD::XD_Engine engine{};
    engine.Initialize();
    XD::FrameworkDummy dummy{};

    XD::SPtr<XD::XD_Window_Widget> window = XD::XD_Window_Widget::fCreatePlatformWindow();
    window->fInitialize();

    while(!window->fWindowShouldClose())
    {
        window->fUpdate();
    }

    system("pause");

    return 0;
}
