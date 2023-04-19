#include "game/Game.hpp"

#include <iostream>

using namespace minesweeper;

Game::Game(int argc, char *argv[])
{
    this->_board = new Board();

    if ( argc > 1 )
    {
        std::string command = argv[1];
        if ( command == "CommandInput" )
        {
            this->_enableConsole = true;
            this->_console = new Console(this->_board);
        }
        else if ( command == "CommandFile" )
        {
            if ( argc >= 3 )
            {
                std::string inputFilePath = argv[2];
                std::string outputFilePath = argv[3];
                this->_enableConsole = true;
                this->_console = new Console(this->_board,
                                             inputFilePath, outputFilePath);
            }
        }
        else if ( command == "GUI" )
        {
            this->_enableGUI = true;
            this->_gui = new GUI();
        }
    }
}

Game::~Game()
{
    delete this->_board;
    if ( this->_enableConsole )
        delete this->_console;
}

bool Game::isRunning() const
{
    bool running = false;
    if ( this->_enableConsole )
        running |= this->_console->isRunning();
    return running;
}

void Game::initialize()
{
    if ( this->_enableGUI )
        this->_gui->Run();
}

void Game::update()
{
    if ( this->_enableConsole )
        this->_console->update();
}