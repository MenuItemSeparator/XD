#include "XD_WindowsOpenGLContext.h"


namespace XD
{

    XD_OpenGLSwapChain::XD_OpenGLSwapChain(void* _hwnd) :
        m_hwnd((HWND)_hwnd)
    {
        m_hdc = GetDC(m_hwnd);
    }

    XD_OpenGLSwapChain::~XD_OpenGLSwapChain()
    {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(m_context);
        ReleaseDC(m_hwnd, m_hdc);
    }

    X
    XD_OpenGLSwapChain::fMakeCurrentX()
    {
        wglMakeCurrent(m_hdc, m_context);
        //GLenum err = glGetError();
        //mXD_ASSERTM(0 != err, "wglMakeCurrent failed with GL error: 0x%04x. " << err);
        return A_A;
    }

    X
    XD_OpenGLSwapChain::fSwapBuffersX()
    {
        SwapBuffers(m_hdc);
        return A_A;
    }
   
    XD_OpenGLContext::XD_OpenGLContext()
    {
    }
}

