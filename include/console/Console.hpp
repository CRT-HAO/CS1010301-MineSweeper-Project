#pragma once

#include "core/Board.hpp"

namespace ms
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