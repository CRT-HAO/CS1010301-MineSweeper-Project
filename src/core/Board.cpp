#include "core/Board.hpp"

using namespace minesweeper;

const std::vector<Pos> Board::_AROUND = {
    {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

void Board::setSize(size_t width, size_t height)
{
    this->_width = width;
    this->_height = height;
    this->_board.resize(height, std::vector<Field>(width));
}

void Board::clear()
{
    this->_width = 0;
    this->_height = 0;
    this->_board.clear();
}

void Board::start()
{
    this->calcMines();
    this->_state = TGameState::Playing;
}

bool Board::putMine(const Pos &pos)
{
    if ( !this->inside(pos) )
        return false;

    if ( !(*this)(pos).isEmpty() )
        return false;

    (*this)(pos).set(TField::Mine);

    return true;
}

void Board::calcMines()
{
    Pos pos;
    for ( pos.x = 0; pos.x < this->_width; pos.x++ )
    {
        for ( pos.y = 0; pos.y < this->_height; pos.y++ )
        {
            if ( !(*this)(pos).isMine() )
                continue;

            int count = 0;
            for ( size_t i = 0; i < Board::_AROUND.size(); i++ )
            {
                Pos p = pos + Board::_AROUND[i];
                if ( this->inside(p) )
                    (*this)(p).setVal((*this)(p).val() + 1);
            }
        }
    }
}

bool Board::uncover(const Pos &pos)
{
    if ( !this->inside(pos) )
        return false;

    if ( !(*this)(pos).isCovered() )
        return false;

    (*this)(pos).setCovered(false);

    if ( (*this)(pos).val() > 0 )
        return false;

    for ( size_t i = 0; i < Board::_AROUND.size(); i++ )
    {
        Pos p = (Pos)pos + (Pos)Board::_AROUND[i];
        if ( this->inside(p) )
            this->uncover(p);
    }

    return true;
}

bool Board::randomMinesCount(int count)
{
    /// Rand a position of mines on the board.

    int num_mines = count;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_x(0, this->_width);
    std::uniform_int_distribution<> dis_y(0, this->_height);
    std::set<Pos> points;
    while ( points.size() < num_mines )
    {
        Pos p = {dis_x(gen), dis_y(gen)};
        points.insert(p);
    }

    for ( const auto &i : points )
    {
        this->putMine(i);
    }

    return true;
}

bool Board::randomMinesRate(double rate)
{
    int gameArea = this->_width * this->_height;
    int minesCount = int(gameArea * rate);
    Board::randomMinesCount(minesCount);
    return true;
}