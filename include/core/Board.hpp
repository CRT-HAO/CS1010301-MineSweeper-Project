/**
 *  File: Board.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/04/20 16:47:44
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/04/26 12:54:07
 *  Description: MineSweeper Game Board
 */

#pragma once

#include "BoardFile.hpp"
#include "Field.hpp"
#include "Pos.hpp"
#include "TGameState.hpp"
#include "TWin.hpp"

#include <iostream>
#include <vector>

namespace minesweeper
{

    typedef std::vector<std::vector<Field>> Board_t;

    class Board
    {
    private:
        Board_t _board;
        size_t _width;
        size_t _height;
        size_t _mines_count{0};
        TWin _win{TWin::None};
        TGameState _state{TGameState::Standby};

    public:
        Board() : _width(0), _height(0){};

        inline size_t w() const { return this->_width; }

        inline size_t h() const { return this->_height; }

        inline const Board_t &get() const { return this->_board; }

        inline const Field &getField(const Pos &pos) const
        {
            return this->_board[pos.y][pos.x];
        }

        inline bool inside(const Pos &pos) const
        {
            return (pos.x >= 0 && pos.y >= 0) &&
                   (pos.x < this->_width && pos.y < this->_height);
        }

        inline const TWin &getWin() const { return this->_win; }

        inline std::string getWinInString() const
        {
            switch ( this->_win )
            {
            case TWin::None:
                return "None";
            case TWin::Win:
                return "Win";
            case TWin::Lose:
                return "Lose";
            }
        }

        inline const TGameState &getState() const { return this->_state; }

        inline std::string getStateInString() const
        {
            switch ( this->_state )
            {
            case TGameState::Standby:
                return "Standby";
            case TGameState::Playing:
                return "Playing";
            case TGameState::GameOver:
                return "GameOver";
            default:
                return "Unknown state";
            }
        }

        void setSize(size_t width, size_t height);

        bool putMine(const Pos &pos);

        void calcMines();

        void clear();

        bool start();

        bool loadBoardFile(const BoardFile &file);

        bool randomMinesCount(int count);

        bool randomMinesRate(double rate);

        bool uncover(const Pos &pos);

        bool uncoverAll();

        bool coverAll();

        bool action(const Pos &pos, bool right_click);

        // 取得目前炸彈數量
        int getMineCount();

        // 取得目前旗幟數量
        int getFlagCount();

        // 取得目前空白格子數量
        int getOpenBlankCount();

        // 取得尚未打開的空白格子數量
        int getRemainBlankCount();

        std::string getBoardInString() const;

        std::string getBoardWithoutCoverInString() const;

        inline const Field &operator()(const Pos &pos) const
        {
            return this->_board[pos.y][pos.x];
        }

    private:
        inline Field &operator()(const Pos &pos)
        {
            return this->_board[pos.y][pos.x];
        }

        const TGameState &updateGameState();

        static const std::vector<Pos> _AROUND;
    };

}