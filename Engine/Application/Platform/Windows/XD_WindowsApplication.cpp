#include "./XD_WindowsApplication.h"

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
        XD_WindowConfig windowConfig{};
        windowConfig.m_widgetName = m_config.m_displayName;

        m_window = std::make_shared<XD_Window>(windowConfig);
        m_window->fOnWidgetWantsToCloseX().fBind(*this, &XD_Application::fTerminateWidgetX);

        X_Call(m_window->fvInitializeX(), "Can't initialize window");

        m_graphicsSystem = std::make_shared<XD_GraphicsSystem>();

        XD::XD_GraphicsConfig graphicsConfig{};
        graphicsConfig.m_rendererType = XD::eRendererType::OpenGL;

        X_Call(m_graphicsSystem->fInitializeX(graphicsConfig), "Failed when initializing graphics system");
        X_Call(m_graphicsSystem->fSetCurrentContextX(m_window), "Failed when setting current context");

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
        X_Call(m_graphicsSystem->fShutdownX(), "Error while terminating graphics system");
        return X::fSuccess();
    }

    X
    XD_Application::fTerminateWidgetX(XD_Window* _window)
    {
        mLOG("Window " << _window->fGetWidgetTitleName() << " was terminated");

        X_Call(_window->fvTerminateX(), "Can't terminate widget with title " << _window->fGetWidgetTitleName());
        m_context.m_requestedTermination = true;
        return X::fSuccess();
    }

}
