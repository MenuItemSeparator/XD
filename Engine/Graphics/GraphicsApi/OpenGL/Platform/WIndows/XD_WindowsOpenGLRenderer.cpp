#include "XD_WindowsOpenGLRenderer.h"
#include "glad/glad.h"

namespace XD
{
    XD_OpenGLRenderer::XD_OpenGLRenderer() :
        m_context(nullptr),
        m_openGLDll()
    {
    }

    X 
    XD_OpenGLRenderer::fvInitializeX()
    {
        X_Call(m_openGLDll.fLoadLibraryX("opengl32.dll"), "Error while loading openGL lib");

        m_context = std::make_shared<XD_OpenGLContext>();

        mLOG("OpenGL renderer initialized successfully");
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvSetCurrentContextX(SPtr<XD_Window> _window)
    {
        X_Call(m_context->fvCreateX(&m_openGLDll, _window->fvGetWindowRawPtr()), "Fail when creating openGL context");
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvShutdownX()
    {
        X_Call(m_openGLDll.fUnloadLibraryX(), "Can't unload open gl library");
        return A_A;
    }
}

