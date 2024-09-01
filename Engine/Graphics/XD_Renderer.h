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

        virtual X fvInitializeX(void* _hwnd) = 0;
        virtual X fvShutdownX() = 0;

        virtual X fvBeginFrameX() = 0;
        virtual X fvEndFrameX() = 0;

    protected:
        XD_Renderer() = default;

    private:
        eRendererType m_rendererType;
    };
}
