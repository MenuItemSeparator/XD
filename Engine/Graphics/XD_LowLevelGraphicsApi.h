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

    class XD_ENGINE_API XD_LowLevelGraphicsApi
    {
    public:
        XD_LowLevelGraphicsApi() = default;
        X fSwitchGraphicsApi(eGraphicsApiType _apiType);

    private:
        XD_Library m_library;
        eGraphicsApiType m_apiType;
    };
}
