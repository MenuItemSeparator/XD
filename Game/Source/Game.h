#pragma once
#include "Application/Platform/XD_Application_PlatformSelector.h"
#include "Common/Platform/XD_Common_PlatformSelector.h"

class Game
{
public:
    Game() = default;
    int fStartup(int argc, const char** argv);
private:
    XD::X fRunX();
};
