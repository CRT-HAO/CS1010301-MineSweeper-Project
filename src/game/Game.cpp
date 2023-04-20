#include "game/Game.hpp"

#include <iostream>

using namespace minesweeper;

Game::Game(int argc, char *argv[])
{
    if ( argc > 1 )
    {
        std::string command = argv[1];
        if ( command == "CommandInput" )
        {
            this->_enableConsole = true;
            this->_console = new Console();
        }
        else if ( command == "CommandFile" || command == "GUI" )
        {
            if ( argc >= 3 )
            {
                std::string inputFilePath = argv[2];
                std::string outputFilePath = argv[3];
                this->_enableConsole = true;
                this->_console = new Console(inputFilePath, outputFilePath);
            }
        }

        if ( command == "GUI" )
        {
            this->_enableGUI = true;
            this->_gui = new GUI();
        }
    }
}

Game::~Game()
{
    if ( this->_enableConsole )
        delete this->_console;

    if ( this->_enableGUI )
        delete this->_gui;
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