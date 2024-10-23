//
// Created by near on 23.10.24.
//

#include "lexeme.h"

Lexeme::Lexeme() {

}

lexemeType Lexeme::getType() const {
    return _type;
}

std::string Lexeme::getName() const {
    return _name;
}
