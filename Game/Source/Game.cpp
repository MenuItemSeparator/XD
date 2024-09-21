#include "Game.h"
#include "Application/XD_Application.h"

int Game::fStartup(int argc, const char **argv)
{
    XD::XD_ApplicationConfig applicationConfig{};
    applicationConfig.m_displayName = "XD";

    XD::tUptr<XD::XD_Application> application = std::make_unique<XD::XD_Application>(applicationConfig);
    X_Call(application->fvInitializeX(), "Application initialization error");

    mLOG("Main loop started");
    X_Call(application->fLoopX(), "Application loop error");

    return 0;
}

XD::X
Game::fRunX()
{
    return XD::A_A;
}

XD_IMPLEMENT_ENTRY_POINT(Game, fStartup);

