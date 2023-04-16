#include "game/Game.hpp"

#include <iostream>

using namespace minesweeper;

Game::Game(int argc, char *argv[])
{
    this->_board = new Board();

    this->_enableGUI = true;
    this->_gui = new GUI();

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
        }
    }
}

Game::~Game()
{
    delete this->_board;
    if ( this->_enableConsole )
        delete this->_console;
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

    for ( const auto &i : this->_board->get() )
    {
        for ( const auto &j : i )
        {
            std::cout << j.getChar() << ' ';
        }
        std::cout << std::endl;
    }
}