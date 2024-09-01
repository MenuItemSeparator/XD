#pragma once
#include "XD_Engine.h"

namespace XD
{

    enum class eRendererType
    {
        None,
        OpenGL
    };

    struct XD_ENGINE_API XD_GraphicsConfig
    {
        eRendererType m_rendererType;
        void* m_hwnd;

        XD_GraphicsConfig() = default;
    };

}
