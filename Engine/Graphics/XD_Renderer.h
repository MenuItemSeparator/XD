#pragma once
#include "XDEngine_Minimal.h"
#include "Common/Platform/XDCommon_PlatformSelector.h"
#include "XD_Library.h"

namespace XD
{
    enum class eGraphicsApiType
    {
        None,
        OpenGL
    };

    class XD_ENGINE_API XD_Renderer
    {
    public:
        XD_Renderer() = default;
        X fSwitchGraphicsApi(eGraphicsApiType _apiType);

    private:
        XD_Library m_library;
        eGraphicsApiType m_apiType;
    };
}
