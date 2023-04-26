/**
 *  File: main.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/04/22 20:39:44
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/04/26 11:55:05
 *  Description: MineSweeper Game Main Entry Point
 */

#include "game/Game.hpp"

#include <iostream>

using namespace std;
using namespace minesweeper;

int main(int argc, char *argv[])
{
    Game game(argc, argv);

    game.initialize();

    for ( ; game.isRunning(); )
        game.update();

    return 0;
}