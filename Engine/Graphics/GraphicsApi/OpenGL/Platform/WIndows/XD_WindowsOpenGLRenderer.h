#pragma once
#include "XD_WindowsOpenGLFuncPtr.h"
#include "Graphics/XD_Renderer.h"
#include "Graphics/XD_Context.h"
#include "Common/Platform/XD_Common_PlatformSelector.h"

namespace XD
{
    class XD_ENGINE_API XD_OpenGLContext : public XD_Context_Base
    {
    public:
        XD_OpenGLContext();
        ~XD_OpenGLContext();

        X fCreateX(HWND _hwnd, const int *_attribList);
        virtual X fvDestroyX() override;

        virtual X fvBindX() override;
        virtual X fvUnbindX() override;

        virtual X fvSwapBuffersX() override;

    private:
        HWND m_hwnd;
        HDC m_hdc;
        HGLRC m_context;
    };

    class XD_ENGINE_API XD_OpenGLRenderer : public XD_Renderer
    {
    public:
        XD_OpenGLRenderer();
        
        virtual X fvInitializeX(void* _hwnd) override;
        virtual X fvShutdownX() override;

        virtual X fvBeginFrameX() override;
        virtual X fvEndFrameX() override;

    private:
        SPtr<XD_OpenGLContext> m_context;
        XD_Library m_openGLDll;
        PIXELFORMATDESCRIPTOR m_pfd;

        X fExtractInitialProcsFromDummyContextX();
        X fCreateValidPixelFormatX(HWND _hwnd);
    };
}