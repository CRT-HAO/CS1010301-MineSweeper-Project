#include "console/Console.hpp"

#include "core/BoardFile.hpp"

#include <fstream>
#include <sstream>
#include <string>

using namespace minesweeper;

Console::Console() {}

Console::Console(const std::string &inputFile, const std::string &outputFile)
    : _fileMode(true)
{
    this->_ifs.open(inputFile, std::ifstream::in);
    if ( !this->_ifs.is_open() )
    {
        std::cout << "Open input command file error!" << std::endl;
        this->_running = false;
        return;
    }

    this->_ofs.open(outputFile);
    if ( !this->_ofs.is_open() )
    {
        std::cout << "Open output file error!" << std::endl;
        this->_running = false;
        return;
    }
}

void Console::update()
{
    if ( !this->_running )
        return;

    std::string command_line, result;
    if ( this->_fileMode )
    {
        this->_running = bool(Console::_safeGetline(this->_ifs, command_line));

        if ( !this->_running )
            return;

        if ( command_line.length() <= 0 )
            return;

        bool success = this->proccessCommand(command_line, result);
        this->_ofs << "<" << command_line << "> : " << result << std::endl;
    }
    else
    {
        getline(std::cin, command_line);

        if ( command_line.length() <= 0 )
            return;

        bool success = this->proccessCommand(command_line, result);
        std::cout << "<" << command_line << "> : " << result << std::endl;
    }
}

bool Console::proccessCommand(const std::string &command_line,
                              std::string &result)
{
    std::stringstream ss(command_line);

    std::string command;
    ss >> command;

    if ( command == "Load" )
    {
        std::string loadMode;
        ss >> loadMode;
        if ( loadMode == "BoardFile" )
        {
            if ( this->_board.getState() != TGameState::Standby )
            {
                result = "Failed";
                return false;
            }
            std::string inputFileName;
            ss >> inputFileName;
            BoardFile file(inputFileName);
            bool success = this->_board.loadBoardFile(file);
            result = success ? "Success" : "Failed";
            return true;
        }
        else if ( loadMode == "RandomCount" )
        {
            if ( this->_board.getState() != TGameState::Standby )
            {
                result = "Failed";
                return false;
            }
            int width, height, count;
            ss >> height >> width >> count;
            this->_board.setSize(width, height);
            bool success = this->_board.randomMinesCount(count);
            result = success ? "Success" : "Failed";
            return true;
        }
        else if ( loadMode == "RandomRate" )
        {
            if ( this->_board.getState() != TGameState::Standby )
            {
                result = "Failed";
                return false;
            }
            int width, height;
            double rate;
            ss >> height >> width >> rate;
            this->_board.setSize(width, height);
            bool success = this->_board.randomMinesRate(rate);
            result = success ? "Success" : "Failed";
            return true;
        }
        else
        {
            result = "Failed";
            return false;
        }
        return true;
    }
    else if ( command == "StartGame" )
    {
        if ( this->_board.getState() != TGameState::Standby )
        {
            result = "Failed";
            return false;
        }
        bool success = this->_board.start();
        result = success ? "Success" : "Failed";
        return true;
    }
    else if ( command == "Print" )
    {
        std::string printMode;
        ss >> printMode;
        if ( printMode == "GameBoard" )
        {
            result = '\n' + this->_board.getBoardInString();
            return true;
        }
        else if ( printMode == "GameAnswer" )
        {
            result = '\n' + this->_board.getBoardWithoutCoverInString();
            return true;
        }
        else if ( printMode == "GameState" )
        {
            result = this->_board.getStateInString();
            return true;
        }
        else if ( printMode == "BombCount" )
        {
            result = std::to_string(this->_board.getMineCount());
            return true;
        }
        else if ( printMode == "FlagCount" )
        {
            result = std::to_string(this->_board.getFlagCount());
            return true;
        }
        else if ( printMode == "OpenBlankCount" )
        {
            result = std::to_string(this->_board.getOpenBlankCount());
            return true;
        }
        else if ( printMode == "RemainBlankCount" )
        {
            result = std::to_string(this->_board.getRemainBlankCount());
            return true;
        }
        else
        {
            result = "Failed";
            return false;
        }
    }
    else if ( command == "LeftClick" )
    {
        if ( this->_board.getState() != TGameState::Playing )
        {
            result = "Failed";
            return false;
        }
        Pos pos;
        ss >> pos.y >> pos.x;
        bool success = this->_board.action(pos, false);
        result = success ? "Success" : "Failed";
        if ( success && this->_board.getState() == TGameState::GameOver )
        {
            result += "\n";
            result += (this->_board.getWin() == TWin::Won)
                          ? "You win the game"
                          : "You lose the game";
        }
        return true;
    }
    else if ( command == "RightClick" )
    {
        if ( this->_board.getState() != TGameState::Playing )
        {
            result = "Failed";
            return false;
        }
        Pos pos;
        ss >> pos.y >> pos.x;
        bool success = this->_board.action(pos, true);
        result = success ? "Success" : "Failed";
        return true;
    }
    else if ( command == "Replay" )
    {
        if ( this->_board.getState() != TGameState::GameOver )
        {
            result = "Failed";
            return false;
        }
        this->_board.clear();
        result = "Success";
        return true;
    }
    else if ( command == "Quit" )
    {
        if ( this->_board.getState() != TGameState::GameOver )
        {
            result = "Failed";
            return false;
        }
        this->_running = false;
        result = "Success";
        return true;
    }
    else
    {
        result = "Failed";
        return false;
    }

    //     if ( command == "clear" )
    //     {
    //         this->_board.clear();
    //         return true;
    //     }
    //     else if ( command == "setSize" )
    //     {
    //         size_t width, height;
    //         ss >> width >> height;
    //         this->_board.setSize(width, height);
    //         return true;
    //     }
    //     else if ( command == "putMine" )
    //     {
    //         int x, y;
    //         ss >> x >> y;
    //         this->_board.putMine(Pos(x, y));
    //         return true;
    //     }
    //     else if ( command == "calcMines" )
    //     {
    //         this->_board.calcMines();
    //         return true;
    //     }
    //     else if ( command == "uncover" )
    //     {
    //         Pos pos;
    //         ss >> pos.x >> pos.y;
    //         this->_board.uncover(pos);
    //         return true;
    //     }
    //     else
    //     {
    //         result = "Unknown command " + command;
    //         return false;
    //     }
}

std::istream &Console::_safeGetline(std::istream &is, std::string &t)
{
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf *sb = is.rdbuf();

    for ( ;; )
    {
        int c = sb->sbumpc();
        switch ( c )
        {
        case '\n':
            return is;
        case '\r':
            if ( sb->sgetc() == '\n' )
                sb->sbumpc();
            return is;
        case std::streambuf::traits_type::eof():
            // Also handle the case when the last line has no line ending
            if ( t.empty() )
                is.setstate(std::ios::eofbit);
            return is;
        default:
            t += (char)c;
        }
    }
}