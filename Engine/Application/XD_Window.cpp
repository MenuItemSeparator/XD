#include "XD_Window.h"

namespace XD
{

    XD_WindowConfig::XD_WindowConfig() :
        m_widgetName("Nameless window"),
        m_widgetStartSize({1280, 720})
    {}

    XD_Window_Base::XD_Window_Base(const XD_WindowConfig &_config) :
        m_config(_config),
        m_onWidgetResizedX(),
        m_onWidgetWantsToCloseX()
    {}
}
