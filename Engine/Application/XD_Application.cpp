#include "XD_Application.h"
#include "Common/Allocator/XD_MallocWrapper.h"

namespace XD
{

    XD_ApplicationConfig::XD_ApplicationConfig() :
        m_displayName("Nameless application")
    {}

    XD_Application::XD_Application(const XD_ApplicationConfig& _config) :
        m_window(nullptr),
        m_graphicsSystem(),
        m_timerManager(),
        m_timeClock(),
        m_config(_config),
        m_requestedTermination(false)
    {}

    XD_Application::~XD_Application()
    {
    }

    X
    XD_Application::fvInitializeX()
    {
        gGlobalAllocator = new XD_MallocWrapper();

        XD_WindowConfig windowConfig{};
        windowConfig.m_windowName = m_config.m_displayName;
        m_window = XD_MemoryUtils::fAlloc<XD_Window>(gGlobalAllocator, windowConfig);
        X_Call(m_window->fvInitializeX(), "Can't initialize window");
        m_window->fOnWindowWantsToClose().fBind(this, &XD_Application::fTerminateWindowX);

        XD::XD_GraphicsConfig graphicsConfig{};
        graphicsConfig.m_rendererType = XD::eRendererType::OpenGL;
        graphicsConfig.m_hwnd = m_window->fvGetWindowRawPtr();

        X_Call(m_graphicsSystem.fInitializeX(graphicsConfig), "Failed when initializing graphics system");

        return A_A;
    }

    X
    XD_Application::fvTerminateX()
    {
        m_requestedTermination = true;
        return A_A;
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
            const f8 deltaTime = m_timeClock.Restart();
            X_Call(m_window->fUpdateX(), "Window update error");
            X_Call(m_timerManager.fUpdateX(deltaTime), "Some error while updating main timer manager");

            X_Call(fvLoopX_Internal(deltaTime), "Internal loop caused error");
            X_Call(m_graphicsSystem.fStageFrameX(), "Error while swapping render frames.");
        }

        X_Call(fTerminateApplicationX(), "Can't terminate application properly");
        return X::fSuccess();
    }

    X
    XD_Application::fvLoopX_Internal(f8 _deltaTime)
    {
        return A_A;
    }

    X
    XD_Application::fTerminateSubsystemsX()
    {
        mLOG("Starting subsystems termination");

        X_Call(m_graphicsSystem.fShutdownX(), "Error while terminating graphics system");

        mLOG("Application subsystems was terminated successfully");
        return X::fSuccess();
    }

    X 
    XD_Application::fTerminateApplicationX()
    {
        mLOG("Requested application termination");

        X_Call(fTerminateSubsystemsX(), "Error while terminating application subsystems");
        X_Call(m_window->fvTerminateX(), "Can't terminate window with title " << m_window->fGetWidgetTitleName());
        mLOG("Window " << m_window->fGetWidgetTitleName() << " was terminated");

        XD_MemoryUtils::fFree(gGlobalAllocator, m_window);        
        delete gGlobalAllocator;

        return A_A;
    }

    X
    XD_Application::fTerminateWindowX(XD_Window* _window)
    {
        mLOG("Received window termination callback");

        X_Call(fvTerminateX(), "Can't terminate application after receiving window termination callback");
        return A_A;
    }


}
