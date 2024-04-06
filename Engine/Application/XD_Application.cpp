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

    }

    XD_Result XD_Application::fInitialize()
    {
        XD_WindowConfig windowConfig{};
        windowConfig.m_windowName = m_config.m_displayName;

        m_window = XD_Window_Widget::fCreatePlatformWindow(windowConfig);

        return m_window->fInitialize();
    }

    void XD_Application::fForceTerminate()
    {
        m_context.m_requestedTermination = true;
    }

    bool XD_Application::fWantsToTerminate() const
    {
        bool shouldTerminate = false;

        shouldTerminate |= !m_window->fIsValid();
        shouldTerminate |= m_context.m_requestedTermination;

        return shouldTerminate;
    }

    XD_ApplicationTerminationReason_Enum XD_Application::fLoop()
    {
        mXD_ASSERT(m_window);

        while(!fWantsToTerminate())
        {
            m_window->fUpdate();
        }

        mLOG("Requested termination");

        fTerminateSubsystems();

        return XD_ApplicationTerminationReason_Enum::ClosedByUser;
    }

    XD_Result XD_Application::fTerminateSubsystems()
    {
        return m_window->fTerminate();
    }
}
