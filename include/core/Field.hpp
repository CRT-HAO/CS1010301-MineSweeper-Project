/**
 *  File: Field.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/04/20 01:36:48
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/04/26 12:55:04
 *  Description: Game Board Field
 */

#pragma once

#include "TField.hpp"

#include <iostream>
#include <vector>

namespace minesweeper
{

    class Field
    {
    private:
        TField _field{TField::None};
        int _val{0};
        bool _covered{true};
        bool _flag{false};
        bool _question_mark{false};

    public:
        Field() {}
        Field(TField field) : _field(field) {}

        inline void set(TField field) { this->_field = field; }
        inline void setVal(int val) { this->_val = val; }
        inline void setCovered(bool covered) { this->_covered = covered; }
        inline void setFlag(bool flag) { this->_flag = flag; }
        inline void setQuestionMark(bool question) { this->_question_mark = question; }
        inline void removeFlags()
        {
            this->_flag = false, this->_question_mark = false;
        }
        inline void putFlag()
        {
            this->_flag = true, this->_question_mark = false;
        }
        inline void putQuestionMark()
        {
            this->_flag = false, this->_question_mark = true;
        }

        inline TField get() const { return this->_field; }
        inline int val() const { return this->_val; }
        inline bool isMine() const { return this->_field == TField::Mine; }
        inline bool isEmpty() const { return this->_field == TField::None; }
        inline bool isCovered() const { return this->_covered; }
        inline bool isFlag() const { return this->_flag; }
        inline bool isQuestionMark() const { return this->_question_mark; }

        char getChar() const
        {
            if ( this->_flag )
                return 'f';

            if ( this->_question_mark )
                return '?';

            if ( this->_covered )
                return '#';

            switch ( this->_field )
            {
            case TField::None:
                return this->_val + '0';
            case TField::Mine:
                return 'X';
            }

            return ' ';
        }

        char getFieldChar() const
        {
            switch ( this->_field )
            {
            case TField::None:
                return this->_val + '0';
            case TField::Mine:
                return 'X';
            }

            return ' ';
        }
    };

}