#pragma once
#include "XDEngine_Minimal.h"

namespace XD
{

    class XD_Renderer_Base
    {
    public:
        XD_Renderer_Base() = default;
        virtual ~XD_Renderer_Base() = default;
        virtual X fInitializeX() = 0;
        virtual X fShutdownX() = 0;
    };

}

