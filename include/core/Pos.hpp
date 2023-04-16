#pragma once

#include <iostream>

namespace minesweeper
{

    class Pos
    {
    public:
        int x, y;

        Pos() : x(0), y(0) {}
        Pos(int x, int y) : x(x), y(y) {}

        inline Pos operator+(const Pos &pos) const
        {
            return Pos(this->x + pos.x, this->y + pos.y);
        }

        inline Pos operator-(const Pos &pos) const
        {
            return Pos(this->x - pos.x, this->y - pos.y);
        }
    };

}