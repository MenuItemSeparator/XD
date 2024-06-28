#include "Game.h"
#include "Graphics/XD_GraphicsSystem.h"

int Game::fStartup(int argc, const char **argv)
{
    XD::XD_GraphicsConfig graphicsConfig{};
    graphicsConfig.m_rendererType = XD::eRendererType::OpenGL;

    XD::XD_GraphicsSystem graphicsSystem{};
    X_Call(graphicsSystem.fInitializeX(graphicsConfig),"");
    X_Call(graphicsSystem.fShutdownX(), "");

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

