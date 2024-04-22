#pragma once
#include "XDGraphics_Minimal.h"

namespace XD
{
    class XD_ENGINE_API XD_GraphicsContext final
    {
    public:
        XD_GraphicsContext();
        XD_GraphicsContext(const XD_GraphicsContext&) = delete;
        XD_GraphicsContext& operator=(const XD_GraphicsContext&) = delete;

        X fInitializeX(const XD_GraphicsConfig& _config);
        X fShutdownX();

    private:
        UPtr<class XD_Renderer> m_renderer;
    };

}
