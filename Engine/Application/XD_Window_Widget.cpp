#include "XD_Window_Widget.h"

#ifdef dXD_PLATFORM_WINDOWS
#include "Platform/Windows/XD_WindowsWindow_Widget.h"
#endif


namespace XD
{

    SPtr<XD_Window_Widget> XD_Window_Widget::fCreatePlatformWindow()
    {

#ifdef dXD_PLATFORM_WINDOWS
        return std::make_shared<XD_WindowsWindow_Widget>();
#endif

        mLOG("Unknown platform while creating window widget");
        return nullptr;
    }

}
