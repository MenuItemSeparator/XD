#include "XD_OpenGLRenderer.h"
#include "Platform/XD_OpenGL_PlatformSelector.h"

//delete me
void* NullLoaderProcPtr(const char *name)
{
    return nullptr;
}

namespace XD
{
    XD_OpenGLRenderer::XD_OpenGLRenderer() :
        m_library()
    {}

    X
    XD_OpenGLRenderer::fvInitializeX()
    {

        X_Call(m_library.fLoadLibraryX("opengl32.dll"), "Error while loading openGL lib");
        tWGLCreateContextProcPtr* contextCreationProc = m_library.fvGetProcAddress("wglCreateContext");

        mLOG("OpenGL renderer initialized successfully");
        return A_A;
    }

    X
    XD_OpenGLRenderer::fvShutdownX()
    {
        return A_A;
    }

    UPtr<XD_OpenGLRenderer> XD_OpenGLRenderer::CreateRenderer()
    {
        return std::make_unique<XD_OpenGLRenderer>();
    }
}
