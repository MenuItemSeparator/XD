#pragma once
#include "XD_Application_Minimal.h"

namespace XD
{
    class XD_ENGINE_API XD_WidgetConfig final
    {
    public:
        std::string m_widgetName;
        Vector2u m_widgetStartSize;

        XD_WidgetConfig();
    };

    using tOnWidgetResizedDelegate = XD_Delegate<X(u4, u4)>;
    using tOnWidgetWantsToClose = XD_Delegate<X(class XD_Widget*)>;

    class XD_ENGINE_API XD_Widget_Interface
    {
    public:
        virtual X fvInitializeX() = 0;
        virtual X fvTerminateX() = 0;

        virtual void* fvGetWidgetRawPtr() = 0;

        virtual ~XD_Widget_Interface() = default;
    };

    class XD_ENGINE_API XD_Widget_Base : public XD_Widget_Interface
    {
    public:
        XD_Widget_Base(const XD_Widget_Base&) = delete;
        XD_Widget_Base& operator=(const XD_Widget_Base&) = delete;

        X fUpdateX() { mXD_NOT_IMPLEMENTED(); return X::fFail(); }
        bool fIsValid() { mXD_NOT_IMPLEMENTED(); return false; }

        const std::string& fGetWidgetTitleName() const { mXD_NOT_IMPLEMENTED(); return m_config.m_widgetName; }

        tOnWidgetResizedDelegate& fOnWidgetResized() { mXD_NOT_IMPLEMENTED(); return m_onWidgetResizedX; }
        tOnWidgetWantsToClose& fOnWidgetWantsToCloseX() { mXD_NOT_IMPLEMENTED(); return m_onWidgetWantsToCloseX; }

    protected:
        XD_WidgetConfig m_config;
        tOnWidgetResizedDelegate m_onWidgetResizedX;
        tOnWidgetWantsToClose m_onWidgetWantsToCloseX;

        XD_Widget_Base(const XD_WidgetConfig& _config);
    };
}
