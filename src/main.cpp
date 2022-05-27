#include "Defs.hpp"
#include "Game.hpp"

int main()
{
    Daft::Game game(SCREEN_WIDTH, SCREEN_HEIGHT, "daft-engine");

    return game.run();
}
