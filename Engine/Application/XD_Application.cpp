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
        XD_WindowConfig windowConfig{};
        windowConfig.m_windowName = m_config.m_displayName;
        m_window = std::make_shared<XD_Window>(windowConfig);
        X_Call(m_window->fvInitializeX(), "Can't initialize window");
        m_window->fOnWindowWantsToCloseX().fBind(*this, &XD_Application::fTerminateWindowX);

        XD::XD_GraphicsConfig graphicsConfig{};
        graphicsConfig.m_rendererType = XD::eRendererType::OpenGL;
        graphicsConfig.m_hwnd = m_window->fvGetWindowRawPtr();

        m_graphicsSystem = std::make_shared<XD_GraphicsSystem>();
        X_Call(m_graphicsSystem->fInitializeX(graphicsConfig), "Failed when initializing graphics system");

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
        mLOG("Starting subsystems termination");

        X_Call(m_graphicsSystem->fShutdownX(), "Error while terminating graphics system");

        mLOG("Application subsystems was terminated successfully");
        return X::fSuccess();
    }

    X
    XD_Application::fTerminateWindowX(XD_Window* _window)
    {
        mLOG("Starting window termination");

        X_Call(m_window->fvTerminateX(), "Can't terminate window with title " << _window->fGetWidgetTitleName());
        m_requestedTermination = true;

        mLOG("Window " << _window->fGetWidgetTitleName() << " was terminated");
        return X::fSuccess();
    }

}
