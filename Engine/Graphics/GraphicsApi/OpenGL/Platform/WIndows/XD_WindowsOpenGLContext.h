#pragma once
#include <Windows.h>
#include "glad.h"
#include "../../XD_OpenGLContext.h"

namespace XD
{
    class XD_OpenGLSwapChain : public XD_OpenGLSwapChain_Base
    {
    public:
        XD_OpenGLSwapChain(void* _nwh);
        ~XD_OpenGLSwapChain();

        //@TODO: make openGl error check wrappers
        X fMakeCurrentX();
        X fSwapBuffersX();

        HWND  m_hwnd;
        HDC   m_hdc;
        HGLRC m_context;
    };

    class XD_OpenGLContext : public XD_OpenGLContext_Base
    {
    public:
        XD_OpenGLContext();

        X fCreateX(u4 _width, u4 _height, u4 _flags) { mXD_NOT_IMPLEMENTED(); return X_X; }
        X fDestroyX() { mXD_NOT_IMPLEMENTED(); return X_X; }

        XD_OpenGLSwapChain* fCreateSwapChain(void* _nwnd) { mXD_NOT_IMPLEMENTED(); return nullptr; }
        X fDestroySwapChainX(XD_OpenGLSwapChain*  _swapChain) { mXD_NOT_IMPLEMENTED(); return X_X; }
        X fSwapX(XD_OpenGLSwapChain* _swapChain = nullptr) { mXD_NOT_IMPLEMENTED(); return X_X; }
        X fMakeCurrentX(XD_OpenGLSwapChain* _swapChain = nullptr) { mXD_NOT_IMPLEMENTED(); return X_X; }

    private:
        PIXELFORMATDESCRIPTOR m_pfd;
        XD_OpenGLSwapChain* m_currentSwapChain;
        XD_Library m_openGLDll;
        HGLRC m_context;
        HDC m_hdc;
        i4 m_contextAttrs[9];
        i4 m_pixelFormat;
    };
}
