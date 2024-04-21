#include "glad.h"
#include "Game.h"

//delete me
void* NullLoaderProcPtr(const char *name)
{
    return nullptr;
}

int Game::fStartup(int argc, const char **argv)
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

XD::X
Game::fRunX()
{
    return XD::A_A;
}

XD_IMPLEMENT_ENTRY_POINT(Game, fStartup);

