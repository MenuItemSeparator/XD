#pragma once
#include "XDApplication_Minimal.h"
#include "XD_Widget.h"

namespace XD
{

    class XD_ENGINE_API XD_WindowConfig final
    {
    public:
        std::string m_windowName;

        XD_WindowConfig();
    };

    using tOnWindowResizedDelegate = XD_MulticastDelegate<void(u4, u4)>;
    using tOnWindowWantsToClose = XD_MulticastDelegate<void(class XD_Window_Widget*)>;

    class XD_ENGINE_API XD_Window_Widget : public XD_Widget
    {
    public:
        XD_Window_Widget(const XD_WindowConfig& _config);
        XD_Window_Widget(const XD_Window_Widget&) = delete;
        XD_Window_Widget& operator=(const XD_Window_Widget&) = delete;

        virtual XD_Result fInitialize() = 0;
        virtual XD_Result fTerminate() = 0;

        virtual void fUpdate() = 0;
        virtual void* fGetWindowRawPtr() = 0;
        virtual bool fIsValid() = 0;

        const std::string& fGetWindowTitleName() const { return m_config.m_windowName; }

        tOnWindowResizedDelegate& fOnWindowResized() { return m_onWindowResized; }
        tOnWindowWantsToClose& fOnWindowWantsToClose() { return m_onWindowWantsToClose; }

        static SPtr<XD_Window_Widget> fCreatePlatformWindow(const XD_WindowConfig& _config);

    protected:
        tOnWindowResizedDelegate m_onWindowResized;
        tOnWindowWantsToClose m_onWindowWantsToClose;

        XD_WindowConfig m_config;
    };

}
