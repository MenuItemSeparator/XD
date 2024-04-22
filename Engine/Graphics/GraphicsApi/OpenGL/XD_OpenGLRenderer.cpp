#include "XD_OpenGLRenderer.h"
#include "glad.h"

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

        //delete me as soon as possible
        if(false)
        {
            mLOG("Start");
            if (!gladLoadGLLoader((GLADloadproc)NullLoaderProcPtr))
            {
                mLOG("Fail");
                std::cout << "Failed to initialize GLAD" << std::endl;
                return -1;
            }

            typedef HGLRC (tWGLCreateContextProcPtr)(HDC);

            XD::XD_Library lib{};
            X_Call(lib.fLoadLibraryX("opengl32.dll"), "");

            tWGLCreateContextProcPtr* f = lib.fGetProcAddress("wglCreateContext");
            mLOG(f);
        }

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
