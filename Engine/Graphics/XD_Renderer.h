#pragma once
#include "XD_Graphics_Minimal.h"
#include "Application/XD_Window.h"
#include "Common/Platform/XD_Common_PlatformSelector.h"
#include "Application/Platform/XD_Application_PlatformSelector.h"

namespace XD
{
    //Пока виртуальные, потом девиртуализирую самые часто используемые функции
    class XD_ENGINE_API XD_Renderer
    {
    public:
        virtual ~XD_Renderer() = default;
        eRendererType GetRendererType() const { return m_rendererType; }

        virtual X fvInitializeX() = 0;
        virtual SPtr<XD_Window> fvCreateWindow(const XD_WindowConfig& _config) = 0;
        virtual X fvTerminateWindowX(XD_Window* _window) = 0;
        virtual X fvShutdownX() = 0;

    protected:
        XD_Renderer() = default;

        SPtr<XD_Window> fCreateWindow_Internal(const XD_WindowConfig& _config);
        X fTerminateWindow_Internal(XD_Window* _window);

    private:
        eRendererType m_rendererType;
    };
}
