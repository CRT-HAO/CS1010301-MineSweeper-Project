#include "console/Console.hpp"

#include <sstream>
#include <string>

using namespace minesweeper;

Console::Console(Board *board) : _board(board) {}

Console::Console(Board *board, int argc, char *argv[]) : _board(board) {}

void Console::update()
{
    std::string command_line, result;
    getline(std::cin, command_line);
    bool success = this->proccessCommand(command_line, result);
}

<<<<<<< HEAD
bool consoleCommand(const std::string &command, std::string &result)
{
    std::stringstream ss;
    if( command == "Load")
    {
=======
bool Console::proccessCommand(const std::string &command_line, std::string &result)
{
    std::stringstream ss(command_line);

    std::string command;
    ss >> command;
>>>>>>> 9d47ac8e5f41dc180bee5bf6888133d6f448d9b2

    }
    else if ( command == "StartGame" )
    {

    }
    else if ( command == "Print" )
    {
        
    }
    else if ( command == "LeftClick" )
    {
        
    }
    else if ( command == "RightClick")
    {
        
    }
    else if ( command == "Replay")
    {
<<<<<<< HEAD

    }
    else if ( command == Quit )
    {

    }
    result = "Unknown command " + command;
=======
        result = "Unknown command " + command_line;
>>>>>>> 9d47ac8e5f41dc180bee5bf6888133d6f448d9b2
        return false;
}


// bool Console::proccessCommand(const std::string &command, std::string &result)
// {
//     std::stringstream ss;

//     if ( command == "clear" )
//     {
//         this->_board->clear();
//         return true;
//     }
//     else if ( command == "setSize" )
//     {
//         size_t width, height;
//         ss >> width >> height;
//         this->_board->setSize(width, height);
//         return true;
//     }
//     else if ( command == "putMine" )
//     {
//         int x, y;
//         ss >> x >> y;
//         this->_board->putMine(Pos(x, y));
//         return true;
//     }
//     else if ( command == "calcMines" )
//     {
//         this->_board->calcMines();
//         return true;
//     }
//     else if ( command == "uncover" )
//     {
//         Pos pos;
//         ss >> pos.x >> pos.y;
//         this->_board->uncover(pos);
//         return true;
//     }
//     else
//     {
//         result = "Unknown command " + command;
//         return false;
//     }
// }