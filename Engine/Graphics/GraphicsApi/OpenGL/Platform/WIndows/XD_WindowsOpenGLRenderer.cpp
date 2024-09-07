#include "XD_WindowsOpenGLRenderer.h"

namespace XD
{
    static i4 gPixelFormatAttribs[] = 
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

    static i4 gGLAttribList[] = 
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 6,
        WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0,
    };

    
    XD_OpenGLContext::XD_OpenGLContext() : 
        m_hwnd(NULL),
        m_context(NULL)
    {
    }

    XD_OpenGLContext::~XD_OpenGLContext()
    {
        fDestroyX().fCheck();
    }

    X 
    XD_OpenGLContext::fCreateX(HWND _hwnd, const int *_attribList)
    {
        if(!_hwnd) return X_X;

        m_hwnd = _hwnd;
        m_hdc = GetDC(m_hwnd);
        m_context = gWGLCreateContextAttribsARBProc(m_hdc, NULL, _attribList);

        return m_context ? A_A : X_X;
    }

    X 
    XD_OpenGLContext::fDestroyX()
    {
        HGLRC currentContext = wglGetCurrentContext();
        if(currentContext == m_context)
        {
            X_Call(fUnbindX(), "Error while unbinding gl context");
        }

        wglDeleteContext(m_context);
        return A_A;
    }

    X 
    XD_OpenGLContext::fBindX()
    {
        if(!m_hwnd) return X_X;
        
        wglMakeCurrent(m_hdc, m_context);
        
        return A_A;
    }

    X 
    XD_OpenGLContext::fUnbindX()
    {
        if(!m_hwnd) return X_X;

        wglMakeCurrent(m_hdc, m_context);

        return A_A;
    }

    X 
    XD_OpenGLContext::fSwapBuffersX()
    {
        return SwapBuffers(m_hdc) ? A_A : X_X;
    }

    XD_OpenGLRenderer::XD_OpenGLRenderer() :
        m_context(nullptr),
        m_openGLDll(),
        m_pfd()
    {
    }

    X 
    XD_OpenGLRenderer::fvInitializeX(void* _hwnd)
    {
        HWND hwnd = reinterpret_cast<HWND>(_hwnd);

        X_Call(m_openGLDll.fLoadLibraryX("opengl32.dll"), "Error while loading openGL lib");
        X_Call(fExtractInitialProcsFromDummyContextX(), "Error while loading OpenGL initial proc ptrs");
        X_Call(fCreateValidPixelFormatX(hwnd), "Error while creating valid pixel format");
        X_Call(fLoadOpenGLExtensionProcPtrX(m_openGLDll), "Error while loading initial gl proc ptrs");

        mLOG("OpenGL renderer initialized successfully");
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fExtractInitialProcsFromDummyContextX()
    {
        WNDCLASSEX wc{};
        MSG msg{};
        HMODULE hInstance = GetModuleHandle(NULL);

        wc.cbSize        = sizeof(WNDCLASSEX);
        wc.style         = CS_OWNDC;
        wc.lpfnWndProc   = DefWindowProc;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = hInstance;
        wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
        wc.lpszMenuName  = NULL;
        wc.lpszClassName = "Dummy_WGL";
        wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

        if(!RegisterClassEx(&wc))
        {
            mLOG("Dummy window class registration failed!");
            MessageBoxA(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
            return X_X;
        }

        HWND dummyHwnd = CreateWindowEx
            (
                WS_EX_CLIENTEDGE,
                wc.lpszClassName,
                "Dummy openGL window",
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                640,
                360,
                NULL,
                NULL,
                hInstance,
                this
                );

        if(dummyHwnd == NULL)
        {
            mLOG("Window Creation Failed!");
            MessageBoxA(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
            return X::fFail();
        }

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

        HDC dummyDC = GetDC(dummyHwnd);
        i4 pixelFormat = ChoosePixelFormat(dummyDC, &dummyPFD);

        if(!pixelFormat)
        {
            mXD_ASSERTM(false, "Failed to find a suitable pixel format")
            return 0;
        }

        if(!SetPixelFormat(dummyDC, pixelFormat, &dummyPFD))
        {
            mXD_ASSERTM(false, "Failed to set pixel format")
            return 0;
        }

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

        X_Call(fLoadOpenGLInitialProcPtrX(), "Error while loading initial openGL proc ptrs");

        wglMakeCurrent(dummyDC, NULL);
        wglDeleteContext(dummyContext);
        ReleaseDC(dummyHwnd, dummyDC);
        DeleteDC(dummyDC);
        DestroyWindow(dummyHwnd);
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fCreateValidPixelFormatX(HWND _hwnd)
    {
        i4 pixelFormat = 0;
        u4 numFormats = 0;

        HDC hdc = GetDC(_hwnd);
        gWGLChoosePixelFormatARBProc(hdc, gPixelFormatAttribs, NULL, 1, &pixelFormat, &numFormats);

        if(!numFormats)
        {
            mXD_ASSERTM(false, "Failed to choose opengl pixel format");
            return X_X;
        }

        DescribePixelFormat(hdc, pixelFormat, sizeof(m_pfd), &m_pfd);

        if(!pixelFormat)
        {
            mXD_ASSERTM(false, "Failed to find a suitable pixel format")
            return 0;
        }

        if(!SetPixelFormat(hdc, pixelFormat, &m_pfd))
        {
            mXD_ASSERTM(false, "Failed to set pixel format")
            return 0;
        }

        m_context = std::make_shared<XD_OpenGLContext>();
        X_Call(m_context->fCreateX(_hwnd, gGLAttribList), "Can't create opengl context wrapper");
        X_Call(m_context->fBindX(), "Can't bind open gl context");

        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvShutdownX()
    {
        X_Call(m_openGLDll.fUnloadLibraryX(), "Can't unload open gl library");
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvBeginFrameX()
    {
        gSetClearColorProc(1.0f, 0.6f, 0.2f, 1.0f);
        gClearProc(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvEndFrameX()
    {
        X_Call(m_context->fSwapBuffersX(), "Error while swapping buffers");
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvCreateVertexBufferLayoutX(VertexBufferLayoutHandle _layoutHandle, const std::vector<eShaderDataType>& _elements)
    {
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvDestroyVertexBufferLayoutX(VertexBufferLayoutHandle _layoutHandle)
    {
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvCreateIBOX(IndexBufferHandle _iboHandle, Memory* _data)
    {
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvDestroyIBOX(IndexBufferHandle _iboHandle)
    {
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvCreateVBOX(VertexBufferHandle _vboHandle, Memory* _data, VertexBufferLayoutHandle _layoutHandle)
    {
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvDestroyVBOX(VertexBufferHandle _vboHandle)
    {
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvCreateShaderX(ShaderHandle _handle, const std::string& _filePath)
    {
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvDestroyShaderX(ShaderHandle _handle)
    {
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvCreateShaderProgramX(ShaderProgramHandle _programHandle, ShaderHandle _vsh, ShaderHandle _fsh)
    {
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvDestroyShaderProgramX(ShaderProgramHandle _programHandle)
    {
        return A_A;
    }
}
