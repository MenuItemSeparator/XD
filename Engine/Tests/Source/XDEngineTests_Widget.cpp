#include "XD_Engine_Minimal.h"
#include "XD_Test_Minimal.h"
#include "Application/Platform/XD_Application_PlatformSelector.h"
#include "Application/XD_Widget.h"

namespace XD
{
    X
    Test_WidgetCreation(XD_WidgetConfig& _config)
    {
        SPtr<XD_Widget> widget = std::make_shared<XD_Widget>(_config);

        mXD_IS_TRUE(widget != nullptr, "Invalid creation of xd widget");

        return A_A;
    }

    X
    Test_WidgetInitialization(XD_WidgetConfig& _config)
    {
        SPtr<XD_Widget> widget = std::make_shared<XD_Widget>(_config);
        X_Call(widget->fvInitializeX(), "Invalid initialization of widget");

        mXD_IS_TRUE(widget != nullptr, "Invalid creation of xd widget");
        mXD_IS_TRUE(widget->fIsValid(), "Invalid initialization of xd widget");

        X_Call(widget->fvTerminateX(), "Invalid termination of xd widget");

        mXD_IS_FALSE(widget->fIsValid(), "Invalid termination of xd widget");

        return A_A;
    }
}

int
main(int argc, char** argv)
{
    XD::XD_WidgetConfig config{};
    config.m_widgetName = "TestConfig";
    config.m_widgetStartSize = {1920, 1080};

    X_Call(XD::Test_WidgetCreation(config), "Widget creation test failed");
    X_Call(XD::Test_WidgetInitialization(config), "Widget initialization test failed");

    return 0;
}
