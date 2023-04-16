#pragma once

#include "console/Console.hpp"
#include "core/Board.hpp"
#include "gui/GUI.h"

namespace minesweeper
{

    class Game
    {
    private:
        Board *_board;
        Console *_console;
        GUI *_gui;
        bool _enableConsole{false};
        bool _enableGUI{false};

    public:
        Game(int argc, char *argv[]);
        ~Game();

        void initialize();
        void update();
    };

}