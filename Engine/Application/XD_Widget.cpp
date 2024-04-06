#include "XD_Widget.h"

#ifdef dXD_PLATFORM_WINDOWS
#include "Platform/Windows/XD_WindowsWidget.h"
#endif


namespace XD
{

    XD_WidgetConfig::XD_WidgetConfig() :
        m_widgetName("Nameless window")
    {

    }

    XD_Widget::XD_Widget(const XD_WidgetConfig &_config) :
        m_config(_config),
        m_onWidgetResized(),
        m_onWidgetWantsToClose()
    {}

    SPtr<XD_Widget>
    XD_Widget::fCreatePlatformWidget(const XD_WidgetConfig& _config)
    {
    #ifdef dXD_PLATFORM_WINDOWS
        return std::make_shared<XD_WindowsWidget>(_config);
    #endif

        mXD_ASSERTM(false, "Unknown platform while creating widget");
        return nullptr;
    }

}
