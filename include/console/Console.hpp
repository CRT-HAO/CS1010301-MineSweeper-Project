#pragma once

#include "core/Board.hpp"

#include <iostream>

namespace minesweeper
{

    class Console
    {
    private:
        Board *_board;
        std::ifstream _ifs;
        std::ofstream _ofs;
        bool _fileMode{false};
        bool _running{true};

    public:
        Console(Board *board);
        Console(Board *board, const std::string &inputFile,
                const std::string &outputFile);

        inline bool isRunning() const { return this->_running; }

        void update();
        bool proccessCommand(const std::string &command, std::string &result);

    private:
        static std::istream &_safeGetline(std::istream &is, std::string &t);
    };

}