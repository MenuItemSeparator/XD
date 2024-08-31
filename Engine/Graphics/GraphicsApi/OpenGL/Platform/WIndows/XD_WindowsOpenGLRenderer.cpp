#include "XD_WindowsOpenGLRenderer.h"
#include "glad/glad.h"

namespace
{
    #define WGL_CONTEXT_MAJOR_VERSION_ARB             0x2091
    #define WGL_CONTEXT_MINOR_VERSION_ARB             0x2092
    #define WGL_CONTEXT_PROFILE_MASK_ARB              0x9126

    #define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001

    #define WGL_DRAW_TO_WINDOW_ARB                    0x2001
    #define WGL_ACCELERATION_ARB                      0x2003
    #define WGL_SUPPORT_OPENGL_ARB                    0x2010
    #define WGL_DOUBLE_BUFFER_ARB                     0x2011
    #define WGL_PIXEL_TYPE_ARB                        0x2013
    #define WGL_COLOR_BITS_ARB                        0x2014
    #define WGL_DEPTH_BITS_ARB                        0x2022
    #define WGL_STENCIL_BITS_ARB                      0x2023

    #define WGL_FULL_ACCELERATION_ARB                 0x2027
    #define WGL_TYPE_RGBA_ARB                         0x202B

    XD::i4 gPixelFormatAttribs[] = 
    {
        WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
        WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB,         32,
        WGL_DEPTH_BITS_ARB,         24,
        WGL_STENCIL_BITS_ARB,       8,
        0
    };

    XD::i4 gGLAttribList[] = 
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0,
    };
}

namespace XD
{
    static tWGLCreateContextAttribsARB* gWGLCreateContextAttribsARBProc;
    static tWGLChoosePixelFormatARB* gWGLChoosePixelFormatARBProc;

    
    XD_OpenGLContext::XD_OpenGLContext() : 
        m_hwnd(NULL),
        m_context(NULL)
    {

    }

    XD_OpenGLContext::~XD_OpenGLContext()
    {
        fvDestroyX().fCheck();
    }

    X 
    XD_OpenGLContext::fCreateX(HWND _hwnd, const int *_attribList)
    {
        if(!_hwnd) return X_X;

        m_hwnd = _hwnd;

        HDC dc = GetDC(m_hwnd);

        m_context = gWGLCreateContextAttribsARBProc(dc, NULL, _attribList);

        if(!m_context) return X_X;

        ReleaseDC(m_hwnd, dc);
        return A_A;
    }

    X 
    XD_OpenGLContext::fvDestroyX()
    {
        HGLRC currentContext = wglGetCurrentContext();
        if(currentContext == m_context)
        {
            fvUnbindX();
        }

        wglDeleteContext(m_context);
        return A_A;
    }

    X 
    XD_OpenGLContext::fvBindX()
    {
        if(!m_hwnd) return X_X;
        
        HDC dc = GetDC(m_hwnd);
        wglMakeCurrent(dc, m_context);
        ReleaseDC(m_hwnd, dc);
        
        return A_A;
    }

    X 
    XD_OpenGLContext::fvUnbindX()
    {
        if(!m_hwnd) return X_X;

        HDC dc = GetDC(m_hwnd);
        wglMakeCurrent(dc, m_context);
        ReleaseDC(m_hwnd, dc);

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
        X_Call(fLoadExtensionsFuncPtrX(), "Error while loading OpenGL extensions");

        mLOG("OpenGL renderer initialized successfully");
        return A_A;
    }

    SPtr<XD_Window> 
    XD_OpenGLRenderer::fvCreateWindow(const XD_WindowConfig &_config)
    {
        SPtr<XD_Window> realWindow = fCreateWindow_Internal(_config);
        realWindow->fvInitializeX().fCheck();

        i4 pixelFormat = 0;
        u4 numFormats = 0;

        HDC hdc = GetDC(realWindow->fGetHWND());
        gWGLChoosePixelFormatARBProc(hdc, gPixelFormatAttribs, NULL, 1, &pixelFormat, &numFormats);

        if(!numFormats)
        {
            mXD_ASSERTM(false, "Failed to choose opengl pixel format");
            return nullptr;
        }


        PIXELFORMATDESCRIPTOR pfd{};
        DescribePixelFormat(hdc, pixelFormat, sizeof(pfd), &pfd);

        if(!SetPixelFormat(hdc, pixelFormat, &pfd))
        {
            mXD_ASSERTM(false, "Failed to set opengl pixel format");
            return nullptr;
        }

        m_context = std::make_shared<XD_OpenGLContext>();
        m_context->fCreateX(realWindow->fGetHWND(), gGLAttribList).fCheck();

        ReleaseDC(realWindow->fGetHWND(), hdc);
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
    XD_OpenGLRenderer::fLoadExtensionsFuncPtrX()
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

        if(!dummyWindow->fSetPixelFormatToWindow(dummyPFD))
        {
            mXD_ASSERTM(false, "Can't set pixel format to dummy window");
            return X_X;
        }

        HDC dummyDC = GetDC(dummyWindow->fGetHWND());
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
        mXD_ASSERT(gWGLCreateContextAttribsARBProc);

        gWGLChoosePixelFormatARBProc = m_openGLDll.fvGetProcAddress("wglChoosePixelFormatARB");
        mXD_ASSERT(gWGLChoosePixelFormatARBProc);

        wglMakeCurrent(dummyDC, NULL);
        wglDeleteContext(dummyContext);
        ReleaseDC(dummyWindow->fGetHWND(), dummyDC);
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
