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

    using tOnRenderLoopCallback = XD_Delegate<X(void)>;

    class XD_ENGINE_API XD_Application : public XD_Application_Interface
    {
    public:
        XD_Application(const XD_ApplicationConfig& _config);
        XD_Application(const XD_Application&) = delete;
        XD_Application& operator=(const XD_Application&) = delete;

        virtual X fvInitializeX() override;
        virtual X fvTerminateX() override;

        tOnRenderLoopCallback& fOnRenderLoopCallback() { return m_onRenderLoopCallback; }
        XD_GraphicsSystem* fGetGraphicsSystem() { return &m_graphicsSystem; }
        XD_TimerManager* fGetTimerManager() { return &m_timerManager; }

        X fLoopX();

    private:
        tSptr<XD_Window> m_window;
        XD_GraphicsSystem m_graphicsSystem;
        XD_TimerManager m_timerManager;
        XD_TimeClock m_timeClock;

        tOnRenderLoopCallback m_onRenderLoopCallback;
        
        XD_ApplicationConfig m_config;
        bl m_requestedTermination;

        bl fWantsToTerminate() const;
        X fTerminateSubsystemsX();
        X fTerminateWindowX(XD_Window* _widget);
    };

}
