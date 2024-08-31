#pragma once
#include "Graphics/XD_Graphics_Minimal.h"

namespace XD
{
    class XD_ENGINE_API XD_OpenGLContext_Base
    {
    public:
        XD_OpenGLContext_Base(const XD_OpenGLContext_Base&) = delete;
        XD_OpenGLContext_Base& operator=(const XD_OpenGLContext_Base&) = delete;
        virtual ~XD_OpenGLContext_Base() = default;

        virtual X fvDestroyX() = 0;

        virtual X fvBindX() = 0;
        virtual X fvUnbindX() = 0;

    protected:
        XD_OpenGLContext_Base() = default;
    };

} // namespace XD
