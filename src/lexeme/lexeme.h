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
    Lexeme() = default;

    Lexeme(std::string name, lexemeType type) : _type(type), _name(std::move(name)) {
    };

    lexemeType getType() const;

    std::string getName() const;

private:
    lexemeType _type;
    std::string _name;
};


#endif //LEXEME_H
