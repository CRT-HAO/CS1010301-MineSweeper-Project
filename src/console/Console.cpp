#include "console/Console.hpp"

#include <string>

using namespace minesweeper;

Console::Console(Board *board) : _board(board) {}

Console::Console(Board *board, int argc, char *argv[]) : _board(board) {}

void Console::update()
{
    std::string command;
    std::cin >> command;

    if ( command == "restart" )
    {
        this->_board->restart();
    }
    else if ( command == "setSize" )
    {
        size_t width, height;
        std::cin >> width >> height;
        this->_board->setSize(width, height);
    }
    else if ( command == "putMine" )
    {
        int x, y;
        std::cin >> x >> y;
        this->_board->putMine(Pos(x, y));
    }
    else if ( command == "calcMines" )
    {
        this->_board->calcMines();
    }
    else if ( command == "uncover" )
    {
        Pos pos;
        std::cin >> pos.x >> pos.y;
        this->_board->uncover(pos);
    }
    else
        std::cout << "Unknown command " << command << std::endl;
}