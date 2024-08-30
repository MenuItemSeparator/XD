#pragma once
#include "XD_WindowsOpenGLFuncPtr.h"
#include "Graphics/XD_Renderer.h"
#include "XD_WindowsOpenGLContext.h"
#include "Application/Platform/XD_Application_PlatformSelector.h"
#include "Common/Platform/XD_Common_PlatformSelector.h"
#include "Common/XD_Library.h"

namespace XD
{
    class XD_OpenGLRenderer : public XD_Renderer
    {
    public:
        XD_OpenGLRenderer();
        
        virtual X fvInitializeX() override;
        virtual X fvSetCurrentContextX(SPtr<XD_Window> _window) override;
        virtual X fvShutdownX() override;

    private:
        SPtr<XD_OpenGLContext> m_context;
        XD_Library m_openGLDll;
    };
}