#pragma once
#include "Application/Platform/XDApplication_PlatformSelector.h"
#include "Common/Platform/XDCommon_PlatformSelector.h"

class Game
{
public:
    Game() = default;
    int fStartup(int argc, const char** argv);
private:
    XD::X fRunX();
};
