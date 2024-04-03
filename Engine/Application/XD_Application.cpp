#include "XD_Application.h"

namespace XD
{

    XD_ApplicationConfig::XD_ApplicationConfig() :
        m_displayName("Nameless application")
    {

    }

    XD_Application::XD_Application() :
        XD_Application(XD_ApplicationConfig{})
    {

    }

    XD_Application::XD_Application(const XD_ApplicationConfig& _config) :
        m_config(_config),
        m_context(),
        m_window()
    {
        XD_WindowConfig windowConfig{};
        windowConfig.m_windowName = m_config.m_displayName;

        m_window = XD_Window_Widget::fCreatePlatformWindow(windowConfig);
    }

    XD_Result XD_Application::fInitialize()
    {
        return m_window->fInitialize();
    }

    void XD_Application::fForceTerminate()
    {
        m_context.m_requestedTermination = true;
    }

    bool XD_Application::fWantsToTerminate() const
    {
        bool shouldTerminate = false;

        shouldTerminate |= m_window->fWindowShouldClose();
        shouldTerminate |= m_context.m_requestedTermination;

        return shouldTerminate;
    }

    XD_ApplicationTerminationReason_Enum XD_Application::fLoop()
    {
        while(!fWantsToTerminate())
        {
            m_window->fUpdate();
        }

        fDeinitialize();

        return XD_ApplicationTerminationReason_Enum::ClosedByUser;
    }

    XD_Result XD_Application::fDeinitialize()
    {
        return m_window->fDeinitialize();
    }
}
