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

    using tOnWidgetResizedDelegate = XD_MulticastDelegate<X(u4, u4)>;
    using tOnWidgetWantsToClose = XD_MulticastDelegate<void(class XD_Widget*)>;

    class XD_ENGINE_API XD_Widget_Interface
    {
    public:
        XD_Widget_Interface() = default;
        virtual ~XD_Widget_Interface() = default;
    };

    class XD_ENGINE_API XD_Widget : public XD_Widget_Interface
    {
    public:
        XD_Widget(const XD_WidgetConfig& _config);
        XD_Widget(const XD_Widget&) = delete;
        XD_Widget& operator=(const XD_Widget&) = delete;

        virtual X fInitializeX() = 0;
        virtual X fTerminateX() = 0;

        virtual X fUpdateX() = 0;
        virtual void* fGetWidgetRawPtr() = 0;
        virtual bool fIsValid() = 0;

        const std::string& fGetWidgetTitleName() const { return m_config.m_widgetName; }

        tOnWidgetResizedDelegate& fOnWidgetResized() { return m_onWidgetResized; }
        tOnWidgetWantsToClose& fOnWidgetWantsToClose() { return m_onWidgetWantsToClose; }

        static SPtr<XD_Widget> fCreatePlatformWidget(const XD_WidgetConfig& _config);

    protected:
        tOnWidgetResizedDelegate m_onWidgetResized;
        tOnWidgetWantsToClose m_onWidgetWantsToClose;

        XD_WidgetConfig m_config;
    };

}
