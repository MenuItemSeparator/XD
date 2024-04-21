#include "Main.h"
#include "Application/Platform/XDApplication_PlatformSelector.h"
#include "Common/Platform/XDCommon_PlatformSelector.h"
#include "glad.h"

//delete me
void* NullLoaderProcPtr(const char *name)
{
    return nullptr;
}

int
main(int argc, char** argv)
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

    XD::XD_ApplicationConfig applicationConfig{};
    applicationConfig.m_displayName = "XD";

    XD::XD_Application application{applicationConfig};
    X_Call(application.fvInitializeX(), "Application initialization error");

    mLOG("Main loop started");
    X_Call(application.fLoopX(), "Application loop error");

    return 0;
}
