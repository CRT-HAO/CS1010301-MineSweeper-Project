#include "game/Game.hpp"

#include <iostream>

using namespace std;
using namespace minesweeper;

int main(int argc, char *argv[])
{
    Game game(argc, argv);

    game.initialize();

    for ( ;; )
        game.update();

    return 0;
}