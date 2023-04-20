#pragma once

#include "console/Console.hpp"
#include "gui/GUI.h"

namespace minesweeper
{

    class Game
    {
    private:
        Console *_console;
        GUI *_gui;
        bool _enableConsole{false};
        bool _enableGUI{false};

    public:
        Game(int argc, char *argv[]);
        ~Game();

        bool isRunning() const;

        void initialize();
        void update();
    };

}