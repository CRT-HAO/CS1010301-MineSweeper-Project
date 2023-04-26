/**
 *  File: BoardFile.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/04/20 01:36:48
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/04/26 12:54:32
 *  Description: Game Board File
 */

#pragma once

#include "Field.hpp"
#include "Pos.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace minesweeper
{

    class BoardFile
    {
    private:
        std::ifstream _ifs;
        bool _parsed{false};
        size_t _boardWidth{0}, _boardHeight{0};
        std::vector<std::vector<TField>> _board;

    public:
        BoardFile(){};
        BoardFile(const std::string &filepath)
        {
            this->open(filepath);
        };

        inline void open(const std::string &filepath)
        {
            this->_ifs.open(filepath);
            this->_parse();
        }

        inline bool isOpen() const
        {
            return this->_ifs.is_open();
        }

        inline bool isParsed() const
        {
            return this->_parsed;
        }

        inline size_t getBoardWidth() const
        {
            return this->_parsed ? this->_boardWidth : 0;
        };

        inline size_t getBoardHeight() const
        {
            return this->_parsed ? this->_boardHeight : 0;
        };

        std::vector<Pos> getBoardMinesPos() const;

    private:
        void _parse();
    };

}
