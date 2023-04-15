#include "game/Game.hpp"

#include <iostream>

using namespace std;
using namespace ms;

int main(int argc, char *argv[])
{
    Game game(argc, argv);

    for ( ;; )
        game.update();

    return 0;
}