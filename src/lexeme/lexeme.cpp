//
// Created by near on 23.10.24.
//

#include "lexeme.h"
#include <iostream>

lexemeType Lexeme::getType() const {
    return _type;
}

std::string Lexeme::getName() const {
    return _name;
}

int Lexeme::getPos() const {
    return _pos;
}


bool Lexeme::operator==(const Lexeme &other) const {
    return _type == other._type;
}

std::ostream &operator<<(std::ostream &os, const Lexeme &lex) {
    os << lex.getName() << " ";
    os << "type: " << lex.getType() << " " << "pos: " << std::to_string(lex.getPos());
    return os;
}
