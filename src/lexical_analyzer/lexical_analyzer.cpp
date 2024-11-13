//
// Created by near on 22.10.24.
//

#include "lexical_analyzer.h"

Lexical_analyzer::Lexical_analyzer() = default;

bool is_reserved(const std::string &a, const Trie &tr) {
    return tr.search(a);
}

void Lexical_analyzer::get_lexemes() {
    std::ifstream code("../src/code.txt");
    code.seekg(0, std::ios::end);
    size_t size = code.tellg();
    code.seekg(0, std::ios::beg);
    const auto text = new char[size];
    code.read(text, size);
    removeBetweenHashes(text);
    auto it = text;
    size_t i = 0;
    while (*it != '\0') {
        ++it;
        ++i;
    }
    size = i;
    int length = size;
    std::vector<Lexeme> ans;
    int conditional = 0;
    std::string lex;
    Trie tr;
    std::ifstream fin("../src/reserved_words.txt");
    while (std::getline(fin, lex)) {
        tr.insert(lex);
    }
    lex.clear();
    // 0 - default
    // 1 - идентификатор
    // 2 - int
    // 3 - float
    // 4 - string
    // 5 - char
    // 6 - other
    int cnt = 1;

    for (int i = 0; i < length; ++i) {
        char symbol = text[i];
        if (conditional == 0) {
            // default
            if (std::isalpha(symbol) || symbol == '_') {
                lex += symbol;
                conditional = 1;
            } else if (std::isdigit(symbol)) {
                lex += symbol;
                conditional = 2;
            } else if (symbol == '"') {
                lex += symbol;
                conditional = 4;
            } else if (symbol == '\'') {
                lex += symbol;
                conditional = 5;
            } else if (symbol == '+') {
                if (ans.back() == Lexeme("", literal)
                    || ans.back() == Lexeme("", identifier)) {
                    ans.emplace_back("+", binaryPlus);
                } else if (ans.back() == Lexeme("", binaryPlus)
                           || ans.back() == Lexeme("", unaryPlus)) {
                    ans.back() = Lexeme("++", increment);
                } else {
                    ans.emplace_back("+", unaryPlus);
                }
            } else if (symbol == '-') {
                if (ans.back() == Lexeme("", literal)
                    || ans.back() == Lexeme("", identifier)) {
                    ans.emplace_back("-", binaryMinus);
                } else if (ans.back() == Lexeme("", binaryMinus)
                           || ans.back() == Lexeme("", unaryMinus)) {
                    ans.back() = Lexeme("--", decrement);
                } else {
                    ans.emplace_back("-", unaryMinus);
                }
            } else if (symbol == '/') {
                ans.emplace_back("/", division);
            } else if (symbol == '*') {
                ans.emplace_back("*", binaryMultiplication);
            } else if (symbol == '.') {
                conditional = 6;
                lex += symbol;
            } else if (symbol == ',') {
                ans.emplace_back(",", comma);
            } else if (symbol == ' ' || symbol == '\n') {
                continue;
            } else if (symbol == '=') {
                if (ans.back() == Lexeme("", binaryMinus) ||
                    ans.back() == Lexeme("", unaryMinus)) {
                    ans.back() = Lexeme("-=", assignmentOperators);
                } else if (ans.back() == Lexeme("", binaryPlus) ||
                           ans.back() == Lexeme("", unaryPlus)) {
                    ans.back() = Lexeme("+=", assignmentOperators);
                } else if (ans.back() == Lexeme("", division)) {
                    ans.back() = Lexeme("/=", assignmentOperators);
                } else if (ans.back() == Lexeme("", binaryMultiplication)) {
                    ans.back() = Lexeme("*=", assignmentOperators);
                } else if (ans.back() == Lexeme("", binaryMultiplication)) {
                    ans.back() = Lexeme("*=", assignmentOperators);
                } else if (ans.back().getName() == "=") {
                    ans.back() = Lexeme("==", logicalOperations);
                } else if (ans.back().getName() == "!") {
                    ans.back() = Lexeme("!=", logicalOperations);
                } else {
                    ans.emplace_back("=", assignmentOperators);
                }
            } else {
                switch (symbol) {
                    case '{':
                        ans.emplace_back("{", openingCurlyBracket);
                        continue;
                    case '}':
                        ans.emplace_back("}", closingCurlyBracket);
                        continue;
                    case '(':
                        ans.emplace_back("(", openingRoundBracket);
                        continue;
                    case ')':
                        ans.emplace_back(")", closingRoundBracket);
                        continue;
                    case '[':
                        ans.emplace_back("[", openingSquareBracket);
                        continue;
                    case ']':
                        ans.emplace_back("]", closingSquareBracket);
                        continue;
                    default:
                        conditional = 6;
                        lex += symbol;
                }
            }
        } else if (conditional == 1) {
            // индентификатор
            if (symbol == ' ' ||
                symbol == ';' ||
                symbol == ',') {
                conditional = 0;
                ans.emplace_back(lex, is_reserved(lex, tr) ? reservedWord : identifier);
                lex.clear();
                if (symbol == ';') {
                    ans.emplace_back(";", semicolon);
                } else if (symbol == ',') {
                    ans.emplace_back(",", comma);
                }
            } else if (isalpha(symbol) || symbol == '_' || isdigit(symbol)) {
                lex += symbol;
            } else if (symbol == '+') {
                conditional = 0;
                if (is_reserved(lex, tr)) {
                    ans.emplace_back(lex, reservedWord);
                } else {
                    ans.emplace_back(lex, identifier);
                }
                lex.clear();
                if (ans.back() == Lexeme("", literal)
                    || ans.back() == Lexeme("", identifier)) {
                    ans.emplace_back("+", binaryPlus);
                } else if (ans.back() == Lexeme("", binaryPlus)
                           || ans.back() == Lexeme("", unaryPlus)) {
                    ans.back() = Lexeme("++", increment);
                } else {
                    ans.emplace_back("+", unaryPlus);
                }
            } else if (symbol == '-') {
                conditional = 0;
                if (is_reserved(lex, tr)) {
                    ans.emplace_back(lex, reservedWord);
                } else {
                    ans.emplace_back(lex, identifier);
                }
                lex.clear();
                if (ans.back() == Lexeme("", literal)
                    || ans.back() == Lexeme("", identifier)) {
                    ans.emplace_back("-", binaryMinus);
                } else if (ans.back() == Lexeme("", binaryMinus)
                           || ans.back() == Lexeme("", unaryMinus)) {
                    ans.back() = Lexeme("--", decrement);
                } else {
                    ans.emplace_back("-", unaryMinus);
                }
            } else if (symbol == '/') {
                conditional = 0;
                if (is_reserved(lex, tr)) {
                    ans.emplace_back(lex, reservedWord);
                } else {
                    ans.emplace_back(lex, identifier);
                }
                lex.clear();
                ans.emplace_back("/", division);
            } else if (symbol == '*') {
                conditional = 0;
                if (is_reserved(lex, tr)) {
                    ans.emplace_back(lex, reservedWord);
                } else {
                    ans.emplace_back(lex, identifier);
                }
                lex.clear();
                ans.emplace_back("*", binaryMultiplication);
            } else if (symbol == '=') {
                conditional = 0;
                if (is_reserved(lex, tr)) {
                    ans.emplace_back(lex, reservedWord);
                } else {
                    ans.emplace_back(lex, identifier);
                }
                lex.clear();
                ans.emplace_back("=", assignmentOperators);
            } else {
                switch (symbol) {
                    case '{':
                        conditional = 0;
                        ans.emplace_back(lex, is_reserved(lex, tr) ? reservedWord : identifier);
                        lex.clear();
                        ans.emplace_back("{", openingCurlyBracket);
                        continue;
                    case '}':
                        conditional = 0;
                        ans.emplace_back(lex, is_reserved(lex, tr) ? reservedWord : identifier);
                        lex.clear();
                        ans.emplace_back("}", closingCurlyBracket);
                        continue;
                    case '(':
                        conditional = 0;
                        ans.emplace_back(lex, is_reserved(lex, tr) ? reservedWord : identifier);
                        lex.clear();
                        ans.emplace_back("(", openingRoundBracket);
                        continue;
                    case ')':
                        conditional = 0;
                        ans.emplace_back(lex, is_reserved(lex, tr) ? reservedWord : identifier);
                        lex.clear();
                        ans.emplace_back(")", closingRoundBracket);
                        continue;
                    case '[':
                        conditional = 0;
                        ans.emplace_back(lex, is_reserved(lex, tr) ? reservedWord : identifier);
                        lex.clear();
                        ans.emplace_back("[", openingSquareBracket);
                        continue;
                    case ']':
                        conditional = 0;
                        ans.emplace_back(lex, is_reserved(lex, tr) ? reservedWord : identifier);
                        lex.clear();
                        ans.emplace_back("]", closingSquareBracket);
                        continue;
                    default:
                        conditional = 6;
                        if (is_reserved(lex, tr)) {
                            ans.emplace_back(lex, reservedWord);
                        } else {
                            ans.emplace_back(lex, identifier);
                        }
                        lex.clear();;
                }
            }
        } else if (conditional == 2) {
            // int
            if (symbol == ' ' ||
                symbol == '+' ||
                symbol == '-' ||
                symbol == '*' ||
                symbol == '/' ||
                symbol == ';' ||
                symbol == '=' ||
                symbol == ',') {
                conditional = 0;
                ans.emplace_back(lex, literal);
                lex.clear();
                if (symbol == '+') {
                    ans.emplace_back("+", binaryPlus);
                } else if (symbol == '-') {
                    ans.emplace_back("-", binaryMinus);
                } else if (symbol == '*') {
                    ans.emplace_back("*", binaryMultiplication);
                } else if (symbol == '/') {
                    ans.emplace_back("/", division);
                } else if (symbol == ';') {
                    ans.emplace_back(";", semicolon);
                } else if (symbol == '=') {
                    ans.emplace_back("=", assignmentOperators);
                } else if (symbol == ',') {
                    ans.emplace_back(",", comma);
                }
            } else if (symbol == '.') {
                conditional = 3;
                lex += symbol;
            } else if (isdigit(symbol)) {
                lex += symbol;
            } else {
                conditional = 0;
                ans.emplace_back(lex, literal);
                ans.emplace_back("" + symbol, other);
                lex.clear();
            }
        } else if (conditional == 3) {
            // float
            if (symbol == ' ' ||
                symbol == '+' ||
                symbol == '-' ||
                symbol == '*' ||
                symbol == '/' ||
                symbol == ';' ||
                symbol == '=' ||
                symbol == ',') {
                conditional = 0;
                ans.emplace_back(lex, literal);
                lex.clear();
                if (symbol == '+') {
                    ans.emplace_back("+", binaryPlus);
                } else if (symbol == '-') {
                    ans.emplace_back("-", binaryMinus);
                } else if (symbol == '*') {
                    ans.emplace_back("*", binaryMultiplication);
                } else if (symbol == '/') {
                    ans.emplace_back("/", division);
                } else if (symbol == ';') {
                    ans.emplace_back(";", semicolon);
                } else if (symbol == '=') {
                    ans.emplace_back("=", assignmentOperators);
                } else if (symbol == ',') {
                    ans.emplace_back(",", comma);
                }
            } else if (isdigit(symbol)) {
                lex += symbol;
            } else {
                conditional = 0;
                ans.emplace_back(lex, literal);
                ans.emplace_back("" + symbol, other);
                lex.clear();
            }
        } else if (conditional == 4) {
            // string
            if (symbol == '"') {
                conditional = 0;
                lex += symbol;
                ans.emplace_back(lex, string);
                lex.clear();
            } else {
                lex += symbol;
            }
        } else if (conditional == 5) {
            // char
            if (symbol == '\'') {
                conditional = 0;
                lex += symbol;
                if (lex.size() == 3) {
                    ans.emplace_back(lex, literal);
                } else {
                    ans.emplace_back(lex, other);
                }
                lex.clear();
            } else {
                lex += symbol;
            }
        } else if (conditional == 6) {
            if (symbol == ' ') {
                conditional = 0;
                ans.emplace_back(lex, other);
                lex.clear();
            } else if (symbol == '+') {
                conditional = 0;
                ans.emplace_back(lex, other);
                ans.emplace_back("+", binaryPlus);
                lex.clear();
            } else if (symbol == '-') {
                conditional = 0;
                ans.emplace_back(lex, other);
                ans.emplace_back("-", binaryMinus);
                lex.clear();
            } else if (symbol == '/') {
                conditional = 0;
                ans.emplace_back(lex, other);
                ans.emplace_back("/", division);
                lex.clear();
            } else if (symbol == '*') {
                conditional = 0;
                ans.emplace_back(lex, other);
                ans.emplace_back("*", binaryMultiplication);
                lex.clear();
            } else if (symbol == ';') {
                conditional = 0;
                ans.emplace_back(lex, other);
                ans.emplace_back(";", semicolon);
                lex.clear();
            } else if (symbol == '\n') {
                conditional = 0;
                ans.emplace_back(lex, other);
                lex.clear();
            } else if (symbol == '=') {
                conditional = 0;
                if (lex == "!") {
                    ans.emplace_back("!=", logicalOperations);
                } else if (lex == "=") {
                    ans.emplace_back("==", logicalOperations);
                } else {
                    ans.emplace_back("=", assignmentOperators);
                }
                lex.clear();
            } else if (symbol == '&') {
                if (ans.back().getName() == "&" || lex == "&") {
                    ans.back() = Lexeme("&&", logicalOperations);
                    lex.clear();
                    conditional = 0;
                } else {
                    lex += symbol;
                }
            } else if (symbol == '|') {
                if (ans.back().getName() == "|" || lex == "|") {
                    ans.back() = Lexeme("||", logicalOperations);
                    lex.clear();
                    conditional = 0;
                } else {
                    lex += symbol;
                }
            } else {
                switch (symbol) {
                    case '{':
                        conditional = 0;
                        ans.emplace_back(lex, other);
                        lex.clear();
                        ans.emplace_back("{", openingCurlyBracket);
                        continue;
                    case '}':
                        conditional = 0;
                        ans.emplace_back(lex, other);
                        lex.clear();
                        ans.emplace_back("}", closingCurlyBracket);
                        continue;
                    case '(':
                        conditional = 0;
                        ans.emplace_back(lex, other);
                        lex.clear();
                        ans.emplace_back("(", openingRoundBracket);
                        continue;
                    case ')':
                        conditional = 0;
                        ans.emplace_back(lex, other);
                        lex.clear();
                        ans.emplace_back(")", closingRoundBracket);
                        continue;
                    case '[':
                        conditional = 0;
                        ans.emplace_back(lex, other);
                        lex.clear();
                        ans.emplace_back("[", openingSquareBracket);
                        continue;
                    case ']':
                        conditional = 0;
                        ans.emplace_back(lex, other);
                        lex.clear();
                        ans.emplace_back("]", closingSquareBracket);
                        continue;
                    default:
                        lex += symbol;
                }
            }
        }
    }
    lexemes_ = ans;
}


Lexeme Lexical_analyzer::get_lexeme() {
    return lexemes_[curr_lex_++];
}

Lexeme Lexical_analyzer::peek() {
    return lexemes_[curr_lex_+ 1];
}

