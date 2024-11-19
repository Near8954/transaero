//
// Created by near on 23.10.24.
//

#ifndef LEXEME_H
#define LEXEME_H
#include <string>
#include <utility>

enum lexemeType {
    reservedWord,
    literal,
    string,
    openingRoundBracket,
    closingRoundBracket,
    openingSquareBracket,
    closingSquareBracket,
    openingCurlyBracket,
    closingCurlyBracket,
    binaryPlus,
    unaryPlus,
    binaryMinus,
    unaryMinus,
    binaryMultiplication,
    division,
    identifier,
    dot,
    comma,
    semicolon,
    increment,
    decrement,
    logicalOperations,
    assignmentOperators,
    other,
};

class Lexeme {
public:
    Lexeme() = default;

    Lexeme(std::string name, lexemeType type) : _type(type),
                                                _name(std::move(name)) {
    }

    Lexeme(std::string name, lexemeType type, int pos) : _type(type), _name(std::move(name)), _pos(pos) {
    };

    lexemeType getType() const;

    std::string getName() const;

    int getPos() const;

    bool operator==(const Lexeme &other) const;

    void set_pos(const int pos) {
        _pos = pos;
    }

private:
    lexemeType _type;
    std::string _name;
    int _pos;
};

std::ostream &operator<<(std::ostream &os, const Lexeme &lex);
#endif //LEXEME_H
