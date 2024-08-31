#pragma once
#include "Graphics/XD_Graphics_Minimal.h"

namespace XD
{
    class XD_ENGINE_API XD_Context_Base
    {
    public:
        XD_Context_Base(const XD_Context_Base&) = delete;
        XD_Context_Base& operator=(const XD_Context_Base&) = delete;
        virtual ~XD_Context_Base() = default;

        virtual X fvDestroyX() = 0;

        virtual X fvBindX() = 0;
        virtual X fvUnbindX() = 0;

        virtual X fvSwapBuffersX() = 0;

    protected:
        XD_Context_Base() = default;
    };

}
