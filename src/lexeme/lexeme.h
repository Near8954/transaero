//
// Created by near on 23.10.24.
//
#pragma once
#ifndef LEXEME_H
#define LEXEME_H
#include <string>
#include <utility>

enum lexemeType {
    def,
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
    array,
    floatt,
    intt,
    booll,
    charr,
    other,
};
inline std::string to_string(lexemeType type) {
    switch (type) {
        case lexemeType::def: return "def";
        case lexemeType::reservedWord: return "reservedWord";
        case lexemeType::literal: return "literal";
        case lexemeType::string: return "string";
        case lexemeType::openingRoundBracket: return "openingRoundBracket";
        case lexemeType::closingRoundBracket: return "closingRoundBracket";
        case lexemeType::openingSquareBracket: return "openingSquareBracket";
        case lexemeType::closingSquareBracket: return "closingSquareBracket";
        case lexemeType::openingCurlyBracket: return "openingCurlyBracket";
        case lexemeType::closingCurlyBracket: return "closingCurlyBracket";
        case lexemeType::binaryPlus: return "binaryPlus";
        case lexemeType::unaryPlus: return "unaryPlus";
        case lexemeType::binaryMinus: return "binaryMinus";
        case lexemeType::unaryMinus: return "unaryMinus";
        case lexemeType::binaryMultiplication: return "binaryMultiplication";
        case lexemeType::division: return "division";
        case lexemeType::identifier: return "identifier";
        case lexemeType::dot: return "dot";
        case lexemeType::comma: return "comma";
        case lexemeType::semicolon: return "semicolon";
        case lexemeType::increment: return "increment";
        case lexemeType::decrement: return "decrement";
        case lexemeType::logicalOperations: return "logicalOperations";
        case lexemeType::assignmentOperators: return "assignmentOperators";
        case lexemeType::array: return "array";
        case lexemeType::floatt: return "float";
        case lexemeType::intt: return "int";
        case lexemeType::booll: return "bool";
        case lexemeType::charr: return "char";
        case lexemeType::other: return "other";
        default: return "Unknown";
    }
}
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
