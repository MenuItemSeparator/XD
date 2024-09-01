#pragma once
#include "XD_Graphics_Minimal.h"
#include "XD_Renderer.h"

namespace XD
{
    class XD_ENGINE_API XD_GraphicsSystem final
    {
    public:
        XD_GraphicsSystem();
        XD_GraphicsSystem(const XD_GraphicsSystem&) = delete;
        XD_GraphicsSystem& operator=(const XD_GraphicsSystem&) = delete;

        X fInitializeX(const XD_GraphicsConfig& _config);
        X fShutdownX();

        X fBeginFrameX();
        X fEndFrameX();

    private:
        UPtr<class XD_Renderer> m_renderer;
    };

}
