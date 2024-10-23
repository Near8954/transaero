//
// Created by near on 23.10.24.
//

#ifndef LEXEME_H
#define LEXEME_H
#include <string>

enum lexemeType {
    reservedWord,
};

class Lexeme {
public:
    Lexeme();

    lexemeType getType() const;

    std::string getName() const;

private:
    lexemeType _type;
    std::string _name;
};


#endif //LEXEME_H
