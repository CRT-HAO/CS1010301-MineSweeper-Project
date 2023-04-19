#pragma once

#include "core/Board.hpp"

#include <iostream>

namespace minesweeper
{

    class Console
    {
    private:
        Board *_board;

    public:
        Console(Board *board);
        Console(Board *board, int argc, char *argv[]);

        void update();
        bool proccessCommand(const std::string &command, std::string &result);
    };

}