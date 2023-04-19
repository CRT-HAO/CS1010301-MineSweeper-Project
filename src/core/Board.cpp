#include "core/Board.hpp"

#include <random>
#include <set>

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
    this->_state = TGameState::Standby;
    this->_win = TWin::None;
}

void Board::start()
{
    this->coverAll();
    this->calcMines();
    this->_state = TGameState::Playing;
    this->_win = TWin::None;
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
            (*this)(pos).setVal(0);
        }
    }

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

bool Board::coverAll()
{
    Pos pos;
    for ( pos.x = 0; pos.x < this->_width; pos.x++ )
    {
        for ( pos.y = 0; pos.y < this->_height; pos.y++ )
        {
            (*this)(pos).setCovered(true);
            (*this)(pos).setFlag(false);
            (*this)(pos).setQuestionMark(false);
        }
    }

    return true;
}

bool Board::action(const Pos &pos, bool right_click)
{
    if ( right_click )
    {
        if ( !(*this)(pos).isCovered() )
            return false;

        if ( !(*this)(pos).isFlag() && !(*this)(pos).isQuestionMark() )
            (*this)(pos).setFlag(true);

        if ( (*this)(pos).isFlag() )
            return false;
    }
    else
    {
        if ( (*this)(pos).isFlag() )
            return false;

        if ( (*this)(pos).isMine() )
        {
            this->_state = TGameState::GameOver;
            this->_win = TWin::Loose;
        }

        return Board::uncover(pos);
    }
}

const TGameState &Board::updateGameState()
{
    if ( this->_state != TGameState::Playing )
        return this->_state;

    Pos pos;
    for ( pos.x = 0; pos.x < this->_width; pos.x++ )
    {
        for ( pos.y = 0; pos.y < this->_height; pos.y++ )
        {
            if ( (*this)(pos).isMine() && (*this)(pos).isFlag() )
                continue;

            if ( !(*this)(pos).isMine() && !(*this)(pos).isFlag() )
                continue;

            return this->_state;
        }
    }

    this->_win = TWin::Won;
    this->_state == TGameState::GameOver;
    return this->_state;
}