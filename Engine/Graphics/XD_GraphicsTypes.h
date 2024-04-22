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

        XD_GraphicsConfig() = default;
    };

}
