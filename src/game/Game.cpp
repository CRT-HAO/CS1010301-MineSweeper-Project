#include "game/Game.hpp"

#include <iostream>

using namespace ms;

Game::Game(int argc, char *argv[])
{
    this->_board = new Board();

    if ( argc > 1 )
    {
        std::string command = argv[1];
        if ( command == "CommandInput" )
        {
            this->_enableConsole = true;
            this->_console = new Console(this->_board, argc, argv);
        }
        else if ( command == "GUI" )
        {
            this->_enableGUI = true;
        }
    }
}

Game::~Game()
{
    delete this->_board;
    if ( this->_enableConsole )
        delete this->_console;
}

void Game::update()
{
    if ( this->_enableConsole )
        this->_console->update();

    for ( const auto &i : this->_board->get() )
    {
        for ( const auto &j : i )
        {
            std::cout << j.getChar() << ' ';
        }
        std::cout << std::endl;
    }
}