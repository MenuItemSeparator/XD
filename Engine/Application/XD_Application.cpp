#include "XD_Application.h"

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

    X
    XD_Application::fvInitializeX()
    {
        XD_WindowConfig windowConfig{};
        windowConfig.m_windowName = m_config.m_displayName;
        m_window = std::make_shared<XD_Window>(windowConfig);
        X_Call(m_window->fvInitializeX(), "Can't initialize window");
        m_window->fOnWindowWantsToClose().fBind(*this, &XD_Application::fTerminateWindowX);

        XD::XD_GraphicsConfig graphicsConfig{};
        graphicsConfig.m_rendererType = XD::eRendererType::OpenGL;
        graphicsConfig.m_hwnd = m_window->fvGetWindowRawPtr();

        X_Call(m_graphicsSystem.fInitializeX(graphicsConfig), "Failed when initializing graphics system");

        if(false)
        {
            XD::VertexBufferLayoutHandle layoutHandle;
            static std::vector<XD::eShaderDataType> shaderTypes{ XD::eShaderDataType::Float3 };
            X_Call(fGetGraphicsSystem()->fCreateVertexBufferLayoutX(layoutHandle, shaderTypes), "Can't create vb layout");

            static float vboRawData[] = {
                0.5f,  0.5f, 0.0f,  // top right
                0.5f, -0.5f, 0.0f,  // bottom right
                -0.5f, -0.5f, 0.0f,  // bottom left
                -0.5f,  0.5f, 0.0f   // top left 
            };
            static XD::Memory vboMem{vboRawData, sizeof(vboRawData)};
            X_Call(fGetGraphicsSystem()->fCreateVertexBufferObjectX(m_vboHandle, &vboMem, layoutHandle), "Can't create vbo");

            static int iboRawData[] = {
                0, 1, 3,   // first triangle
                1, 2, 3 
            };
            static XD::Memory iboMem{iboRawData, sizeof(iboRawData)};
            X_Call(fGetGraphicsSystem()->fCreateIndexBufferX(m_iboHandle, &iboMem), "Can't create ibo");

            XD::ShaderHandle vsHandle;
            static std::string vsFilePath = cXD_ENGINE_RESOURCE_FOLDER_PATH + "TestVS.vs";
            X_Call(fGetGraphicsSystem()->fCreateShaderX(vsHandle, vsFilePath), "Can't create vertex shader");
            XD::ShaderHandle fsHandle;
            static std::string fsFilePath = cXD_ENGINE_RESOURCE_FOLDER_PATH + "TestFS.fs";
            X_Call(fGetGraphicsSystem()->fCreateShaderX(fsHandle, fsFilePath), "Can't create fragment shader");

            X_Call(fGetGraphicsSystem()->fCreateShaderProgramX(m_programHandle, vsHandle, fsHandle), "Can't create shader program");

            XD_Color col{1.0f, 0.2f, 0.2f, 1.0f};
            X_Call(fGetGraphicsSystem()->fSetClearColorX(col), "");
        }

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

        mLOG("Requested application termination");
        X_Call(fTerminateSubsystemsX(), "Error while terminating application subsystems");
        X_Call(m_window->fvTerminateX(), "Can't terminate window with title " << m_window->fGetWidgetTitleName());
        mLOG("Window " << m_window->fGetWidgetTitleName() << " was terminated");

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
    XD_Application::fTerminateWindowX(XD_Window* _window)
    {
        mLOG("Received window termination callback");

        X_Call(fvTerminateX(), "Can't terminate application after receiving window termination callback");
        return A_A;
    }

}
