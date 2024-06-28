#pragma once
#include "XD_Graphics_Minimal.h"
#include "Common/Platform/XD_Common_PlatformSelector.h"

namespace XD
{
    //Пока виртуальные, потом девиртуализирую самые часто используемые функции
    class XD_ENGINE_API XD_Renderer
    {
    public:
        virtual ~XD_Renderer() = default;
        eRendererType GetRendererType() const { return m_rendererType; }

        virtual X fvInitializeX() = 0;
        virtual X fvShutdownX() = 0;

    protected:
        XD_Renderer() = default;

    private:
        eRendererType m_rendererType;
    };
}
