#pragma once
#include "XDApplication_Minimal.h"

namespace XD
{
    class XD_ENGINE_API XD_WidgetConfig final
    {
    public:
        std::string m_widgetName;

        XD_WidgetConfig();
    };

    using tOnWidgetResizedDelegate = XD_Delegate<X(u4, u4)>;
    using tOnWidgetWantsToClose = XD_Delegate<X(class XD_Widget*)>;
}
