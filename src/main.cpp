#include "core/Board.hpp"

#include <iostream>

using namespace std;
using namespace ms;

Board gb;

int main(int argc, char **argv)
{
    gb.restart();
    gb.setSize(20, 20);
    // gb.putBomb(Pos(5, 1));
    gb.putBomb(Pos(5, 3));
    gb.putBomb(Pos(5, 5));
    gb.putBomb(Pos(5, 6));
    gb.putBomb(Pos(2, 6));
    gb.putBomb(Pos(1, 6));
    gb.putBomb(Pos(10, 5));
    gb.putBomb(Pos(5, 10));
    gb.calcMines();

    gb.uncover(Pos(0, 0));

    Board_t board = gb.get();

    for ( const auto &i : board )
    {
        for ( const auto &j : i )
        {
            cout << j.getChar() << ' ';
        }
        cout << endl;
    }

    return 0;
}