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

inline lexemeType from_string(const std::string &type) {
    if (type == "def") return lexemeType::def;
    if (type == "reservedWord") return lexemeType::reservedWord;
    if (type == "literal") return lexemeType::literal;
    if (type == "string") return lexemeType::string;
    if (type == "openingRoundBracket") return lexemeType::openingRoundBracket;
    if (type == "closingRoundBracket") return lexemeType::closingRoundBracket;
    if (type == "openingSquareBracket") return lexemeType::openingSquareBracket;
    if (type == "closingSquareBracket") return lexemeType::closingSquareBracket;
    if (type == "openingCurlyBracket") return lexemeType::openingCurlyBracket;
    if (type == "closingCurlyBracket") return lexemeType::closingCurlyBracket;
    if (type == "binaryPlus") return lexemeType::binaryPlus;
    if (type == "unaryPlus") return lexemeType::unaryPlus;
    if (type == "binaryMinus") return lexemeType::binaryMinus;
    if (type == "unaryMinus") return lexemeType::unaryMinus;
    if (type == "binaryMultiplication") return lexemeType::binaryMultiplication;
    if (type == "division") return lexemeType::division;
    if (type == "identifier") return lexemeType::identifier;
    if (type == "dot") return lexemeType::dot;
    if (type == "comma") return lexemeType::comma;
    if (type == "semicolon") return lexemeType::semicolon;
    if (type == "increment") return lexemeType::increment;
    if (type == "decrement") return lexemeType::decrement;
    if (type == "logicalOperations") return lexemeType::logicalOperations;
    if (type == "assignmentOperators") return lexemeType::assignmentOperators;
    if (type == "array") return lexemeType::array;
    if (type == "float") return lexemeType::floatt;
    if (type == "int") return lexemeType::intt;
    if (type == "bool") return lexemeType::booll;
    if (type == "char") return lexemeType::charr;
    if (type == "other") return lexemeType::other;
    return lexemeType::other; // Default case if no match is found
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
