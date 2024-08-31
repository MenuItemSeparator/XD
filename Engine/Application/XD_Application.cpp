#include "XD_Application.h"

namespace XD
{

    XD_ApplicationConfig::XD_ApplicationConfig() :
        m_displayName("Nameless application")
    {}


    XD_Application::XD_Application(const XD_ApplicationConfig& _config) :
        m_window(nullptr),
        m_graphicsSystem(nullptr),
        m_config(_config),
        m_requestedTermination(false)
    {}

    X
    XD_Application::fvInitializeX()
    {
        XD::XD_GraphicsConfig graphicsConfig{};
        graphicsConfig.m_rendererType = XD::eRendererType::OpenGL;

        m_graphicsSystem = std::make_shared<XD_GraphicsSystem>();
        X_Call(m_graphicsSystem->fInitializeX(graphicsConfig), "Failed when initializing graphics system");

        XD_WindowConfig windowConfig{};
        windowConfig.m_windowName = m_config.m_displayName;

        mXD_ASSERT(m_graphicsSystem->fGetRenderer())
        m_window = m_graphicsSystem->fGetRenderer()->fvCreateWindow(windowConfig);
        m_window->fOnWindowWantsToCloseX().fBind(*this, &XD_Application::fTerminateWindowX);

        return X::fSuccess();
    }

    X
    XD_Application::fvTerminateX()
    {
        m_requestedTermination = true;
        return X::fSuccess();
    }

    bl
    XD_Application::fWantsToTerminate() const
    {
        return m_requestedTermination;
    }

    X
    XD_Application::fLoopX()
    {
        mXD_ASSERT(m_window);

        mLOG("Game loop start");

        while(!fWantsToTerminate())
        {
            X_Call(m_graphicsSystem->fBeginFrameX(), "Error while begin frame in graphics subsystem");
            X_Call(m_graphicsSystem->fEndFrameX(), "Error while end frame in graphics subsystem");

            X_Call(m_window->fUpdateX(), "Window update error");
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
    XD_Application::fTerminateWindowX(XD_Window* _window)
    {
        mLOG("Window " << _window->fGetWidgetTitleName() << " was terminated");

        X_Call(m_graphicsSystem->fGetRenderer()->fvTerminateWindowX(_window), "Can't terminate widget with title " << _window->fGetWidgetTitleName());
        m_requestedTermination = true;
        return X::fSuccess();
    }

}
