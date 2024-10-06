#pragma once
#include "XD_Application_Minimal.h"
#include "Application/Platform/XD_Application_PlatformSelector.h"
#include "Graphics/XD_GraphicsSystem.h"
#include "Common/XD_TimerManager.h"
#include "Common/XD_TimeClock.h"

namespace XD
{
    class XD_ENGINE_API XD_ApplicationConfig final
    {
    public:
        std::string m_displayName;

        XD_ApplicationConfig();
    };

    class XD_ENGINE_API XD_Application_Interface
    {
    public:
        virtual X fvInitializeX() = 0;
        virtual X fvTerminateX() = 0;

        virtual ~XD_Application_Interface() = default;
    };

    class XD_ENGINE_API XD_Application : public XD_Application_Interface
    {
    public:
        XD_Application(const XD_ApplicationConfig& _config);
        ~XD_Application();
        XD_Application(const XD_Application&) = delete;
        XD_Application& operator=(const XD_Application&) = delete;

        virtual X fvInitializeX() override;
        virtual X fvTerminateX() override;

        XD_GraphicsSystem* fGetGraphicsSystem() { return &m_graphicsSystem; }
        XD_TimerManager* fGetTimerManager() { return &m_timerManager; }

        X fLoopX();

        XD::VertexBufferObjectHandle m_vboHandle;
        XD::IndexBufferObjectHandle m_iboHandle;
        XD::ShaderProgramHandle m_programHandle;

    protected:
        XD_Window* m_window;
        XD_GraphicsSystem m_graphicsSystem;
        XD_TimerManager m_timerManager;
        XD_TimeClock m_timeClock;

        XD_ApplicationConfig m_config;
        bl m_requestedTermination;

        virtual X fvLoopX_Internal(f8 _deltaTime);

        bl fWantsToTerminate() const;
        X fTerminateSubsystemsX();
        X fTerminateApplicationX();
        X fTerminateWindowX(XD_Window* _widget);
    };

}
