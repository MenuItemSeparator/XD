#include "Game.h"

XD::X
Game::fRunX()
{
    return XD::A_A;
}

XD::i4
Game::EntryPoint()
{
    Game game{};
    X_Call(game.fRunX(), "Error while running game");
    return XD::X::fSuccess();
}
