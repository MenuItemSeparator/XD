#include "Game.h"

XD::X Game::fRunX()
{
    return XD::A_A;
}

int Game::EntryPoint()
{
    Game game{};
    X_Call(game.fRunX(), "Error while running game");
    return XD::X::fSuccess();
}

int EntryPoint(int argc, char** argv)
{
    return 0;
}
