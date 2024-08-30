#pragma once
#include "XD_Application_Minimal.h"

namespace XD
{
    class XD_ENGINE_API XD_WindowConfig final
    {
    public:
        std::string m_widgetName;
        Vector2u m_widgetStartSize;

        XD_WindowConfig();
    };

    using tOnWindowResizedDelegate = XD_Delegate<X(u4, u4)>;
    using tOnWindowWantsToClose = XD_Delegate<X(class XD_Window*)>;

    class XD_ENGINE_API XD_Window_Interface
    {
    public:
        virtual X fvInitializeX() = 0;
        virtual X fvTerminateX() = 0;

        virtual void* fvGetWindowRawPtr() = 0;

        virtual ~XD_Window_Interface() = default;
    };

    class XD_ENGINE_API XD_Window_Base : public XD_Window_Interface
    {
    public:
        XD_Window_Base(const XD_Window_Base&) = delete;
        XD_Window_Base& operator=(const XD_Window_Base&) = delete;

        X fUpdateX() { mXD_NOT_IMPLEMENTED(); return X::fFail(); }
        bool fIsValid() { mXD_NOT_IMPLEMENTED(); return false; }

        const std::string& fGetWidgetTitleName() const { mXD_NOT_IMPLEMENTED(); return m_config.m_widgetName; }

        tOnWindowResizedDelegate& fOnWidgetResized() { mXD_NOT_IMPLEMENTED(); return m_onWidgetResizedX; }
        tOnWindowWantsToClose& fOnWidgetWantsToCloseX() { mXD_NOT_IMPLEMENTED(); return m_onWidgetWantsToCloseX; }

    protected:
        XD_WindowConfig m_config;
        tOnWindowResizedDelegate m_onWidgetResizedX;
        tOnWindowWantsToClose m_onWidgetWantsToCloseX;

        XD_Window_Base(const XD_WindowConfig& _config);
    };
}
