#pragma once

#include "console/Console.hpp"
#include "core/Board.hpp"

namespace ms
{

    class Game
    {
    private:
        Board *_board;
        Console *_console;
        bool _enableConsole;
        bool _enableGUI;

    public:
        Game(int argc, char *argv[]);
        ~Game();

        void update();
    };

}