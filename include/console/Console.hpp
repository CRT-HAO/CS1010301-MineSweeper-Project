#pragma once

#include "core/Board.hpp"

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
    };

}