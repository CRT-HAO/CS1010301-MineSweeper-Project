/**
 *  File: Pos.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/04/20 01:36:48
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/04/26 12:55:30
 *  Description: Game Board Position
 */

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