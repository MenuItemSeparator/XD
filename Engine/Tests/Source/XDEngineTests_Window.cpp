#include "XD_Engine_Minimal.h"
#include "XD_Test_Minimal.h"
#include "Application/Platform/XD_Application_PlatformSelector.h"
#include "Application/XD_Window.h"

namespace XD
{
    X
    Test_WidgetCreation(XD_WindowConfig& _config)
    {
        SPtr<XD_Window> window = std::make_shared<XD_Window>(_config);

        mXD_IS_TRUE(window != nullptr, "Invalid creation of xd window");

        return A_A;
    }

    X
    Test_WidgetInitialization(XD_WindowConfig& _config)
    {
        SPtr<XD_Window> window = std::make_shared<XD_Window>(_config);
        X_Call(window->fvInitializeX(), "Invalid initialization of window");

        mXD_IS_TRUE(window != nullptr, "Invalid creation of xd window");
        mXD_IS_TRUE(window->fIsValid(), "Invalid initialization of xd window");

        X_Call(window->fvTerminateX(), "Invalid termination of xd window");

        mXD_IS_FALSE(window->fIsValid(), "Invalid termination of xd window");

        return A_A;
    }
}

int
main(int argc, char** argv)
{
    XD::XD_WindowConfig config{};
    config.m_widgetName = "TestConfig";
    config.m_widgetStartSize = {1920, 1080};

    X_Call(XD::Test_WidgetCreation(config), "Widget creation test failed");
    X_Call(XD::Test_WidgetInitialization(config), "Widget initialization test failed");

    return 0;
}
