#include "XD_WindowsApplication.h"

namespace XD
{

    XD_Application::XD_Application(const XD_ApplicationConfig& _config) :
        XD_Application_Base(_config),
        m_window()
    {

    }

    X
    XD_Application::fvInitializeX()
    {
        XD_WidgetConfig windowConfig{};
        windowConfig.m_widgetName = m_config.m_displayName;

        m_window = std::make_shared<XD_Widget>(windowConfig);
        m_window->fOnWidgetWantsToCloseX().fBind(*this, &XD_Application::fTerminateWidgetX);

        X_Call(m_window->fvInitializeX(), "Can't initialize window");
        return X::fSuccess();
    }

    X
    XD_Application::fvTerminateX()
    {
        m_context.m_requestedTermination = true;
        return X::fSuccess();
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

        return X::fSuccess();
    }

    X
    XD_Application::fTerminateSubsystemsX()
    {
        return X::fSuccess();
    }

    X
    XD_Application::fTerminateWidgetX(XD_Widget* _widget)
    {
        mLOG("Window " << _widget->fGetWidgetTitleName() << " was terminated");

        X_Call(_widget->fvTerminateX(), "Can't terminate widget with title " << _widget->fGetWidgetTitleName());
        m_context.m_requestedTermination = true;
        return X::fSuccess();
    }

}
