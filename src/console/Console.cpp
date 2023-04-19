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

bool Console::proccessCommand(const std::string &command_line, std::string &result)
{
    std::stringstream ss(command_line);

    std::string command;
    ss >> command;

    if ( command == "Load" )
    {
        std::string inputCommand;
        ss >> inputCommand;
        if( inputCommand == "BoardFile" )
        {
            string inputFileName;
            ss >> inputFileName;
            return true;
        }
        else if ( inputCommand == "RandomCount")
        {
            int count = 0;
            ss >> count;
            this->_board->randomMinesCount(count);
            return true;
        }
        else if ( inputCommand == "RandomRate")
        {
            int rate;
            ss >> rate;
            this->_board->randomMinesRate(rate);
            return true;
        }
        else
        {
            result = "Failed" + command_line;
            return false;
        }
        return true;
    }
    else if ( command == "StartGame" )
    {
        this->_board->start();
        return true;
    }
    else if ( command == "Print" )
    {
        this->_board->print();
        return true;
    }
    else if ( command == "LeftClick" )
    {
        Pos pos;
        ss >> pos.x >> pos.y;
        this->_board->action(pos, false);
        return true;
    }
    else if ( command == "RightClick" )
    {
        Pos pos;
        ss >> pos.x >> pos.y;
        this->_board->action(pos, true);
        return true;
    }
    else if ( command == "Replay" )
    {
        this->board->start();
        return true;
    }
    else
    {
        result = "Failed" + command_line;
        return false;
    }

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
}