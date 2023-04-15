#pragma once

#include "TField.hpp"

#include <iostream>
#include <vector>

namespace ms
{

    class Field
    {
    private:
        TField _field{TField::None};
        int _val{0};
        bool _covered{true};
        bool _flag{false};

    public:
        Field() {}
        Field(TField field) : _field(field) {}

        inline void set(TField field) { this->_field = field; }
        inline void setVal(int val) { this->_val = val; }
        inline void setCovered(bool covered) { this->_covered = covered; }
        inline void setFlag(bool flag) { this->_flag = flag; }

        inline TField get() const { return this->_field; }
        inline int val() const { return this->_val; }
        inline bool isMine() const { return this->_field == TField::Mine; }
        inline bool isEmpty() const { return this->_field == TField::None; }
        inline bool isCovered() const { return this->_covered; }
        inline bool isFlag() const { return this->_flag; }

        char getChar() const
        {
            if ( this->_flag )
                return 'F';

            if ( this->_covered )
                return '#';

            switch ( this->_field )
            {
            case TField::None:
                if ( this->_val > 0 )
                    return this->_val + '0';
                else
                    return ' ';
            case TField::Mine:
                return '*';
            }

            return '?';
        }
    };

}