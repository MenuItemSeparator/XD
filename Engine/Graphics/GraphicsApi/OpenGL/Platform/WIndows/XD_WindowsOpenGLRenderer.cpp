#include "XD_WindowsOpenGLRenderer.h"
#include "glad/glad.h"

namespace XD
{
    tWGLCreateContextAttribsARB* gWGLCreateContextAttribsARBProc;
    tWGLChoosePixelFormatARB* gWGLChoosePixelFormatARBProc;

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
        m_swapChain(),
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


    XD_OpenGLRenderer::XD_OpenGLRenderer() :
        m_context(nullptr),
        m_openGLDll()
    {
    }

    X 
    XD_OpenGLRenderer::fvInitializeX()
    {
        X_Call(m_openGLDll.fLoadLibraryX("opengl32.dll"), "Error while loading openGL lib");
        X_Call(fLoadExtensionsFuncPtr(), "Error while loading OpenGL extensions");

        mLOG("OpenGL renderer initialized successfully");
        return A_A;
    }

    SPtr<XD_Window> 
    XD_OpenGLRenderer::fvCreateWindow(const XD_WindowConfig &_config)
    {
        SPtr<XD_Window> realWindow = fCreateWindow_Internal(_config);
        return realWindow;
    }

    X 
    XD_OpenGLRenderer::fvTerminateWindowX(XD_Window* _window)
    {
        mXD_ASSERT(_window);
        X_Call(fTerminateWindow_Internal(_window), "Can't terminate window");
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fLoadExtensionsFuncPtr()
    {
        XD_WindowConfig dummyConfig{};
        dummyConfig.m_windowName = "DummyWindow";

        SPtr<XD_Window> dummyWindow = fCreateWindow_Internal(dummyConfig);
        X_Call(dummyWindow->fvInitializeX(), "Can't initialize dummy window");

        PIXELFORMATDESCRIPTOR dummyPFD = {
            .nSize = sizeof(dummyPFD),
            .nVersion = 1,
            .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            .iPixelType = PFD_TYPE_RGBA,
            .cColorBits = 32,
            .cAlphaBits = 8,
            .cDepthBits = 24,
            .cStencilBits = 8,
            .iLayerType = PFD_MAIN_PLANE,
        };

        if(!dummyWindow->SetPixelFormatToWindow(dummyPFD))
        {
            mXD_ASSERTM(false, "Can't set pixel format to dummy window");
            return X_X;
        }

        HDC dummyDC = GetDC(dummyWindow->GetHWND());
        HGLRC dummyContext = wglCreateContext(dummyDC);

        if (!dummyContext) 
        {
            mXD_ASSERTM(false, "Failed to create a dummy OpenGL rendering context.");
            return X_X;
        }

        if (!wglMakeCurrent(dummyDC, dummyContext)) 
        {
            mXD_ASSERTM(false, "Failed to activate dummy OpenGL rendering context.");
            return X_X;
        }

        gWGLCreateContextAttribsARBProc = m_openGLDll.fvGetProcAddress("wglCreateContextAttribsARB");
        gWGLChoosePixelFormatARBProc = m_openGLDll.fvGetProcAddress("wglChoosePixelFormatARB");

        wglMakeCurrent(dummyDC, NULL);
        wglDeleteContext(dummyContext);
        ReleaseDC(dummyWindow->GetHWND(), dummyDC);
        X_Call(fTerminateWindow_Internal(dummyWindow.get()), "Can't terminate dummy window.");
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvShutdownX()
    {
        X_Call(m_openGLDll.fUnloadLibraryX(), "Can't unload open gl library");
        return A_A;
    }

}
