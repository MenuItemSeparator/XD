#pragma once
#include "XD_WindowsOpenGLFuncPtr.h"
#include "Graphics/XD_Renderer.h"
#include "Graphics/GraphicsApi/OpenGL/XD_OpenGLContext.h"
#include "Common/Platform/XD_Common_PlatformSelector.h"

namespace XD
{
    class XD_OpenGLSwapChain : public XD_OpenGLSwapChain_Base
    {
    public:
        XD_OpenGLSwapChain(void* _hwnd);
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
        ~XD_OpenGLContext();

        virtual X fvCreateX(XD_Library* _library, void* _hwnd) override;
        virtual X fvDestroyX(XD_Library* _library) override;

        virtual XD_OpenGLSwapChain* fvCreateSwapChain(void* _nwnd) override;
        virtual X fvDestroySwapChainX(XD_OpenGLSwapChain*  _swapChain) override;

    private:
        XD_OpenGLSwapChain* m_swapChain;
        HGLRC m_context;
    };

    class XD_OpenGLRenderer : public XD_Renderer
    {
    public:
        XD_OpenGLRenderer();
        
        virtual X fvInitializeX() override;
        virtual SPtr<XD_Window> fvCreateWindow(const XD_WindowConfig& _config) override;
        virtual X fvTerminateWindowX(XD_Window* _window) override;
        virtual X fvShutdownX() override;

    private:
        SPtr<XD_OpenGLContext> m_context;
        XD_WGL_Library m_openGLDll;

        X fLoadExtensionsFuncPtr();
    };
}