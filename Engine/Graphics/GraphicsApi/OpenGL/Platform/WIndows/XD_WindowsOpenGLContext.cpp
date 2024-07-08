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
   
    XD_OpenGLContext::XD_OpenGLContext() :
        m_currentSwapChain(),
        m_context()
    {
    }

    XD_OpenGLContext::~XD_OpenGLContext()
    {
    }

    X 
    XD_OpenGLContext::fvCreateX(XD_Library* _library, void* _hwnd)
    {
        mXD_ASSERT(!m_context);

        tWGLCreateContextProcPtr* contextCreationProc = _library->fvGetProcAddress("wglCreateContext");

        HWND* hwnd = static_cast<HWND*>(_hwnd);
        mXD_ASSERT(hwnd);

        HDC hdc = GetDC(*hwnd);
        mXD_ASSERT(hdc);

        //PIXELFORMATDESCRIPTOR m_pfd;

        m_context = contextCreationProc(hdc);
        mXD_ASSERT(m_context);
        return A_A;
    }

    X
    XD_OpenGLContext::fvDestroyX(XD_Library* _library)
    {
        mXD_ASSERT(m_context);

        tWGLDeleteContext* contextDeleteProc = _library->fvGetProcAddress("wglDeleteContext");
        mXD_ASSERT(contextDeleteProc);

        contextDeleteProc(m_context);
        return A_A;
    }

    XD_OpenGLSwapChain*
    XD_OpenGLContext::fvCreateSwapChain(void *_nwnd)
    {
        return nullptr;
    }

    X 
    XD_OpenGLContext::fvDestroySwapChainX(XD_OpenGLSwapChain *_swapChain)
    {
        delete _swapChain;
        return A_A;
    }
}
