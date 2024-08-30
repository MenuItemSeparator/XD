#pragma once
#include "XD_Engine_Minimal.h"
#include "./XD_WindowsWindow.h"
#include "Graphics/XD_GraphicsSystem.h"
#include "../../XD_Application.h"

namespace XD
{
    class XD_ENGINE_API XD_Application : public XD_Application_Base
    {
    public:
        XD_Application(const XD_ApplicationConfig& _config);

        virtual X fvInitializeX() override;
        virtual X fvTerminateX() override;

        X fLoopX();

    private:
        SPtr<XD_Window> m_window;
        SPtr<XD_GraphicsSystem> m_graphicsSystem;

        bl fWantsToTerminate() const;
        X fTerminateSubsystemsX();
        X fTerminateWidgetX(XD_Window* _widget);
    };
}

