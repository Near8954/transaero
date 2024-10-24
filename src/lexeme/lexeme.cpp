//
// Created by near on 23.10.24.
//

#include "lexeme.h"
#include <iostream>

lexemeType Lexeme::getType() const {
//    1 - служебное слово
//    2 - идентификатор
//    3 - литерал
//    4 - .
//    5 - ,
//    6 - (
//    7 - )
//    8 - [
//    9 - ]
//    10 - {
//    11 - }
//    12 - ;
//    13 - + (bin)
//    14 - + (uno)
//    15 - - (bin)
//    16 - - (uno)
//    17 - * (bin)
//    18 - * (link)
//    19 - /
//    20 - increment
//    21 - decrement



    return _type;
}

std::string Lexeme::getName() const {
    return _name;
}


bool Lexeme::operator==(const Lexeme &other) const {
    return _type == other._type;
}

//typenameemplate<typename T>
//std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e) {
//    return stream << static_cast<typename std::underlying_type<T>::type>(e);
//}

std::ostream& operator<<(std::ostream &os, const Lexeme& lex) {
    os << lex.getName() << " ";
    os << lex.getType();
    return os;
}
