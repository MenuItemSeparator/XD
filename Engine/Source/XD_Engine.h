#pragma once
#include "XDEngine_Minimal.h"
#include "Common/XD_Library.h"

namespace XD
{

    class XD_ENGINE_API XD_Engine
    {
    public:
        XD_Engine();
        X fInitializeX();

    private:
        std::vector<SPtr<XD_Library>> m_libraries;
    };

}
