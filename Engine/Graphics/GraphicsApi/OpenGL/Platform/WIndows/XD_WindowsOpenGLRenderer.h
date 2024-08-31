#pragma once
#include "XD_WindowsOpenGLFuncPtr.h"
#include "Graphics/XD_Renderer.h"
#include "Graphics/GraphicsApi/OpenGL/XD_OpenGLContext.h"
#include "Common/Platform/XD_Common_PlatformSelector.h"

namespace XD
{
    class XD_OpenGLContext : public XD_OpenGLContext_Base
    {
    public:
        XD_OpenGLContext();
        ~XD_OpenGLContext();

        X fCreateX(HWND _hwnd, const int *_attribList);
        virtual X fvDestroyX() override;

        virtual X fvBindX() override;
        virtual X fvUnbindX() override;

    private:
        HWND m_hwnd;
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

        X fLoadExtensionsFuncPtrX();
    };
}