#include "XD_Widget.h"

namespace XD
{

    XD_WidgetConfig::XD_WidgetConfig() :
        m_widgetName("Nameless window"),
        m_widgetStartSize({1280, 720})
    {}

    XD_Widget_Base::XD_Widget_Base(const XD_WidgetConfig &_config) :
        m_config(_config),
        m_onWidgetResizedX(),
        m_onWidgetWantsToCloseX()
    {}
}
