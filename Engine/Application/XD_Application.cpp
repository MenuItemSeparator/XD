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

    X
    XD_Application::fInitializeX()
    {
        XD_WidgetConfig windowConfig{};
        windowConfig.m_widgetName = m_config.m_displayName;

        m_window = XD_Widget::fCreatePlatformWidget(windowConfig);
        m_window->fOnWidgetWantsToClose().fBind(*this, &XD_Application::fTerminateWidget);

        X_Call(m_window->fInitializeX(), "Can't initialize window");
        return X::Success();
    }

    X
    XD_Application::fForceTerminateX()
    {
        m_context.m_requestedTermination = true;
        return X::Success();
    }

    bl
    XD_Application::fWantsToTerminate() const
    {
        return m_context.m_requestedTermination;
    }

    X
    XD_Application::fLoopX()
    {
        mXD_ASSERT(m_window);

        mLOG("Game loop start");

        while(!fWantsToTerminate())
        {
            X_Call(m_window->fUpdateX(), "Widget update error");
        }

        mLOG("Requested application termination");

        X_Call(fTerminateSubsystemsX(), "Error while terminating application subsystems");

        return X::Success();
    }

    X
    XD_Application::fTerminateSubsystemsX()
    {
        return X::Success();
    }


    void XD_Application::fTerminateWidget(XD_Widget* _widget)
    {
        mLOG("Window " << _widget->fGetWidgetTitleName() << " was terminated");

        X_Call_Void(_widget->fTerminateX(), "Can't terminate widget with title " << _widget->fGetWidgetTitleName());
        m_context.m_requestedTermination = true;
    }
}
