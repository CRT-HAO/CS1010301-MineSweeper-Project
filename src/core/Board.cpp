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

bool Board::start()
{
    if ( this->_width <= 0 || this->_height <= 0 )
        return false;

    if ( this->_state != TGameState::Standby )
        return false;

    this->coverAll();
    this->calcMines();
    this->_state = TGameState::Playing;
    this->_win = TWin::None;

    return true;
}

bool Board::loadBoardFile(const BoardFile &file)
{
    if ( this->_state != TGameState::Standby )
        return false;

    if ( !file.isParsed() )
        return false;

    this->clear();

    this->setSize(file.getBoardWidth(), file.getBoardHeight());

    for ( const Pos &p : file.getBoardMinesPos() )
        this->putMine(p);

    return true;
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

    if ( (*this)(pos).isMine() )
        return true;

    if ( (*this)(pos).val() > 0 )
        return true;

    bool success = false;
    for ( size_t i = 0; i < Board::_AROUND.size(); i++ )
    {
        Pos p = (Pos)pos + (Pos)Board::_AROUND[i];
        if ( this->inside(p) )
            success |= this->uncover(p);
    }

    return true;
}

bool Board::uncoverAll()
{
    Pos pos;
    for ( pos.x = 0; pos.x < this->_width; pos.x++ )
    {
        for ( pos.y = 0; pos.y < this->_height; pos.y++ )
        {
            (*this)(pos).setCovered(false);
        }
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

bool Board::randomMinesCount(int count)
{
    /// Rand a position of mines on the board.

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_x(0, this->_width);
    std::uniform_int_distribution<> dis_y(0, this->_height);
    int mines_count = 0;
    while ( mines_count < count )
    {
        Pos p = {dis_x(gen), dis_y(gen)};
        if ( this->putMine(p) )
            mines_count++;
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

bool Board::action(const Pos &pos, bool right_click)
{
    if ( this->_state != TGameState::Playing )
        return false;

    bool success = false;
    if ( right_click )
    {
        if ( !(*this)(pos).isCovered() )
        {
            this->updateGameState();
            return false;
        }

        if ( !(*this)(pos).isFlag() && !(*this)(pos).isQuestionMark() )
        {
            (*this)(pos).putFlag();
            this->updateGameState();
            return true;
        }

        if ( (*this)(pos).isFlag() )
        {
            (*this)(pos).putQuestionMark();
            this->updateGameState();
            return true;
        }

        if ( (*this)(pos).isQuestionMark() )
        {
            (*this)(pos).removeFlags();
            this->updateGameState();
            return true;
        }
    }
    else
    {
        if ( !this->inside(pos) )
            return false;

        if ( (*this)(pos).isFlag() || (*this)(pos).isQuestionMark() )
        {
            this->updateGameState();
            return false;
        }

        if ( (*this)(pos).isMine() )
        {
            this->uncoverAll();
            this->_state = TGameState::GameOver;
            this->_win = TWin::Loose;
            return true;
        }

        bool success = this->uncover(pos);
        this->updateGameState();
        return success;
    }

    return success;
}

const TGameState &Board::updateGameState()
{
    if ( this->_state != TGameState::Playing )
        return this->_state;

    if ( this->getRemainBlankCount() == 0 )
    {
        this->_win = TWin::Won;
        this->_state = TGameState::GameOver;
    }

    return this->_state;
}

// 取得目前炸彈數量
int Board::getMineCount()
{
    Pos pos;
    int mineCount = 0;
    for ( pos.x = 0; pos.x < this->_width; pos.x++ )
    {
        for ( pos.y = 0; pos.y < this->_height; pos.y++ )
        {
            if ( (*this)(pos).isMine() )
                mineCount++;
        }
    }
    return mineCount;
}

// 取得目前旗幟數量
int Board::getFlagCount()
{
    Pos pos;
    int flagCount = 0;
    for ( pos.x = 0; pos.x < this->_width; pos.x++ )
    {
        for ( pos.y = 0; pos.y < this->_height; pos.y++ )
        {
            if ( (*this)(pos).isFlag() )
                flagCount++;
        }
    }
    return flagCount;
}

// 取得目前空白格子數量
int Board::getOpenBlankCount()
{
    Pos pos;
    int openBlankCount = 0;
    for ( pos.x = 0; pos.x < this->_width; pos.x++ )
    {
        for ( pos.y = 0; pos.y < this->_height; pos.y++ )
        {
            if ( !(*this)(pos).isCovered() && (*this)(pos).isEmpty() )
                openBlankCount++;
        }
    }
    return openBlankCount;
}

// 取得尚未打開的空白格子數量
int Board::getRemainBlankCount()
{
    Pos pos;
    int remainBlankCount = 0;
    for ( pos.x = 0; pos.x < this->_width; pos.x++ )
    {
        for ( pos.y = 0; pos.y < this->_height; pos.y++ )
        {
            if ( (*this)(pos).isCovered() && (*this)(pos).isEmpty() )
                remainBlankCount++;
        }
    }
    return remainBlankCount;
}

std::string Board::getBoardInString() const
{
    std::string board;
    size_t ii = 0;

    for ( const auto &i : this->_board )
    {
        for ( const auto &j : i )
        {
            board += j.getChar();
            board += " ";
        }
        if ( ii < this->_board.size() - 1 )
            board += "\n";
        ii += 1;
    }

    return board;
}

std::string Board::getBoardWithoutCoverInString() const
{
    std::string board;
    size_t ii = 0;

    for ( const auto &i : this->_board )
    {
        for ( const auto &j : i )
        {
            board += j.getFieldChar();
            board += " ";
        }
        if ( ii < this->_board.size() - 1 )
            board += "\n";
        ii += 1;
    }

    return board;
}
