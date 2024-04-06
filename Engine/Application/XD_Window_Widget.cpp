#include "XD_Window_Widget.h"

#ifdef dXD_PLATFORM_WINDOWS
#include "Platform/Windows/XD_WindowsWindow_Widget.h"
#endif


namespace XD
{

    XD_WindowConfig::XD_WindowConfig() :
        m_windowName("Nameless window")
    {

    }

    XD_Window_Widget::XD_Window_Widget(const XD_WindowConfig &_config) :
        m_config(_config),
        m_onWindowResized(),
        m_onWindowWantsToClose()
    {}

    SPtr<XD_Window_Widget> XD_Window_Widget::fCreatePlatformWindow(const XD_WindowConfig& _config)
    {
#ifdef dXD_PLATFORM_WINDOWS
        return std::make_shared<XD_WindowsWindow_Widget>(_config);
#endif

        mXD_ASSERTM(false, "Unknown platform while creating window widget");
        return nullptr;
    }


}
