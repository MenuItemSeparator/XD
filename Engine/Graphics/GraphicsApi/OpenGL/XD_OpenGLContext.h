#pragma once
#include "Graphics/XD_Graphics_Minimal.h"

namespace XD
{
    class XD_OpenGLSwapChain;

    class XD_ENGINE_API XD_OpenGLSwapChain_Base
    {
    public:
        virtual ~XD_OpenGLSwapChain_Base() = default;

        virtual X fvMakeCurrentX() = 0;
        virtual X fvSwapBuffersX() = 0;

    protected:
        XD_OpenGLSwapChain_Base() = default;
    };

    class XD_ENGINE_API XD_OpenGLContext_Base
    {
    public:
        XD_OpenGLContext_Base(const XD_OpenGLContext_Base&) = delete;
        XD_OpenGLContext_Base& operator=(const XD_OpenGLContext_Base&) = delete;
        virtual ~XD_OpenGLContext_Base() = default;

        virtual X fvCreateX(XD_Library* _library, void* _hwnd) = 0;
        virtual X fvDestroyX(XD_Library* _library) = 0;

        virtual XD_OpenGLSwapChain* fvCreateSwapChain(void* _nwnd) = 0;
        virtual X fvDestroySwapChainX(XD_OpenGLSwapChain*  _swapChain) = 0;

    protected:
        XD_OpenGLContext_Base() = default;
    };

} // namespace XD
