//
// Created by near on 23.10.24.
//

#ifndef LEXEME_H
#define LEXEME_H
#include <string>

enum lexemeType {
    reservedWord,
    literal,
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
    linkMultiplication,
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

    Lexeme(std::string name, lexemeType type) :
            _type(type),
            _name(std::move(name)) {};

    lexemeType getType() const;

    std::string getName() const;

    bool operator==(const Lexeme &other) const;



private:
    lexemeType _type;
    std::string _name;
};

std::ostream &operator<<(std::ostream &os, const Lexeme& lex);
#endif //LEXEME_H
