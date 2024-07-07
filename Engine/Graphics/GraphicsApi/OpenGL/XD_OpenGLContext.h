#pragma once
#include "Graphics/XD_Graphics_Minimal.h"

namespace XD
{
    class XD_OpenGLSwapChain;

    class XD_ENGINE_API XD_OpenGLSwapChain_Base
    {
    public:
        virtual ~XD_OpenGLSwapChain_Base() = default;

        X fMakeCurrentX() { mXD_NOT_IMPLEMENTED(); return X_X; }
        X fSwapBuffersX() { mXD_NOT_IMPLEMENTED(); return X_X; }

    protected:
        XD_OpenGLSwapChain_Base() = default;
    };

    class XD_ENGINE_API XD_OpenGLContext_Base
    {
    public:
        virtual ~XD_OpenGLContext_Base() = default;

        X fCreateX(u4 _width, u4 _height, u4 _flags) { mXD_NOT_IMPLEMENTED(); return X_X; }
        X fDestroyX() { mXD_NOT_IMPLEMENTED(); return X_X; }

        XD_OpenGLSwapChain* fCreateSwapChain(void* _nwnd) { mXD_NOT_IMPLEMENTED(); return nullptr; }
        X fDestroySwapChainX(XD_OpenGLSwapChain*  _swapChain) { mXD_NOT_IMPLEMENTED(); return X_X; }
        X fSwapX(XD_OpenGLSwapChain* _swapChain = nullptr) { mXD_NOT_IMPLEMENTED(); return X_X; }
        X fMakeCurrentX(XD_OpenGLSwapChain* _swapChain = nullptr) { mXD_NOT_IMPLEMENTED(); return X_X; }

    protected:
        XD_OpenGLContext_Base() = default;
    };

} // namespace XD
