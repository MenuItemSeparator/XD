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
        XD_Renderer* fGetRenderer() { return m_renderer.get(); }
        X fShutdownX();

    private:
        UPtr<class XD_Renderer> m_renderer;
    };

}
