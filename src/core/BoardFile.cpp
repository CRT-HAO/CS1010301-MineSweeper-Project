#include "core/BoardFile.hpp"

#include <sstream>

using namespace minesweeper;

void BoardFile::_parse()
{
    if ( !this->isOpen() )
        return;

    if ( this->isParsed() )
        return;

    this->_board.clear();
    this->_ifs >> this->_boardHeight >> this->_boardWidth;
    this->_board.resize(this->_boardHeight,
                        std::vector<TField>(this->_boardWidth, TField::None));

    std::vector<std::string> readLine;
    readLine.resize(this->_boardHeight);
    for ( size_t i = 0; i < this->_boardHeight; i++ )
    {
        this->_ifs >> readLine[i];
        for ( size_t j = 0; j < this->_boardWidth; j++ )
        {
            this->_board[i][j] =
                (readLine[i][j] == 'X') ? TField::Mine : TField::None;
        }
    }

    this->_parsed = true;
}

std::vector<Pos> BoardFile::getBoardMinesPos() const
{
    std::vector<Pos> r;
    Pos pos;
    for ( pos.y = 0; pos.y < this->_boardHeight; pos.y++ )
    {
        for ( pos.x = 0; pos.x < this->_boardWidth; pos.x++ )
        {
            if ( this->_board[pos.y][pos.x] == TField::Mine )
                r.push_back(pos);
        }
    }
    return r;
}