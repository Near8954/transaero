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
    size_t sz = 0;
    while (*it != '\0') {
        ++it;
        ++sz;
    }
    size = sz;
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
    // 7 - ++
    // 8 - --
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
                lex += symbol;
                conditional = 7;
            } else if (symbol == '-') {
                lex += symbol;
                conditional = 8;
            } else if (symbol == '/') {
                ans.emplace_back("/", division, cnt);
            } else if (symbol == '*') {
                ans.emplace_back("*", binaryMultiplication, cnt);
            } else if (symbol == '.') {
                conditional = 6;
                lex += symbol;
            } else if (symbol == ',') {
                ans.emplace_back(",", comma, cnt);
            } else if (symbol == '>') {
                ans.emplace_back(">", logicalOperations, cnt);
            } else if (symbol == '|') {
                if (ans.back().getName() == "|") {
                    ans.back() = Lexeme("||", logicalOperations, cnt);
                } else {
                    ans.emplace_back("|", other, cnt);
                }
            } else if (symbol == '&') {
                if (ans.back().getName() == "&") {
                    ans.back() = Lexeme("&&", logicalOperations, cnt);
                } else {
                    ans.emplace_back("&", other, cnt);
                }
            } else if (symbol == '<') {
                ans.emplace_back("<", logicalOperations, cnt);
            } else if (symbol == ' ' || symbol == '\n') {
                if (symbol == '\n') {
                    ++cnt;
                }
                continue;
            } else if (symbol == '=') {
                if (ans.back() == Lexeme("", binaryMinus) ||
                    ans.back() == Lexeme("", unaryMinus)) {
                    ans.back() = Lexeme("-=", assignmentOperators, cnt);
                } else if (ans.back() == Lexeme("", binaryPlus) ||
                           ans.back() == Lexeme("", unaryPlus)) {
                    ans.back() = Lexeme("+=", assignmentOperators, cnt);
                } else if (ans.back() == Lexeme("", division)) {
                    ans.back() = Lexeme("/=", assignmentOperators, cnt);
                } else if (ans.back() == Lexeme("", binaryMultiplication)) {
                    ans.back() = Lexeme("*=", assignmentOperators, cnt);
                } else if (ans.back() == Lexeme("", binaryMultiplication)) {
                    ans.back() = Lexeme("*=", assignmentOperators, cnt);
                } else if (ans.back().getName() == "=") {
                    ans.back() = Lexeme("==", logicalOperations, cnt);
                } else if (ans.back().getName() == "!") {
                    ans.back() = Lexeme("!=", logicalOperations, cnt);
                } else if (ans.back().getName() == "<") {
                    ans.back() = Lexeme("<=", logicalOperations, cnt);
                } else if (ans.back().getName() == ">") {
                    ans.back() = Lexeme(">=", logicalOperations, cnt);
                } else {
                    ans.emplace_back("=", assignmentOperators, cnt);
                }
            } else {
                switch (symbol) {
                    case '{':
                        ans.emplace_back("{", openingCurlyBracket, cnt);
                        continue;
                    case '}':
                        ans.emplace_back("}", closingCurlyBracket, cnt);
                        continue;
                    case '(':
                        ans.emplace_back("(", openingRoundBracket, cnt);
                        continue;
                    case ')':
                        ans.emplace_back(")", closingRoundBracket, cnt);
                        continue;
                    case '[':
                        ans.emplace_back("[", openingSquareBracket, cnt);
                        continue;
                    case ']':
                        ans.emplace_back("]", closingSquareBracket, cnt);
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
                symbol == ',' ||
                symbol == '>' ||
                symbol == '<' ||
                symbol == '|' ||
                symbol == '&') {
                conditional = 0;
                ans.emplace_back(lex, is_reserved(lex, tr) ? reservedWord : identifier, cnt);
                lex.clear();
                if (symbol == ';') {
                    ans.emplace_back(";", semicolon, cnt);
                } else if (symbol == ',') {
                    ans.emplace_back(",", comma, cnt);
                } else if (symbol == '<') {
                    ans.emplace_back("<", logicalOperations, cnt);
                } else if (symbol == '>') {
                    ans.emplace_back(">", logicalOperations, cnt);
                } else if (symbol == '|') {
                    ans.emplace_back("|", other, cnt);
                } else if (symbol == '&') {
                    ans.emplace_back("&", other, cnt);
                }
            } else if (isalpha(symbol) || symbol == '_' || isdigit(symbol)) {
                lex += symbol;
            } else if (symbol == '+') {
                conditional = 0;
                if (is_reserved(lex, tr)) {
                    ans.emplace_back(lex, reservedWord, cnt);
                } else {
                    ans.emplace_back(lex, identifier, cnt);
                }
                lex.clear();
                lex += symbol;
                conditional = 7;
            } else if (symbol == '-') {
                conditional = 0;
                if (is_reserved(lex, tr)) {
                    ans.emplace_back(lex, reservedWord, cnt);
                } else {
                    ans.emplace_back(lex, identifier, cnt);
                }
                lex.clear();
                lex += symbol;
                conditional = 8;
            } else if (symbol == '/') {
                conditional = 0;
                if (is_reserved(lex, tr)) {
                    ans.emplace_back(lex, reservedWord, cnt);
                } else {
                    ans.emplace_back(lex, identifier, cnt);
                }
                lex.clear();
                ans.emplace_back("/", division, cnt);
            } else if (symbol == '*') {
                conditional = 0;
                if (is_reserved(lex, tr)) {
                    ans.emplace_back(lex, reservedWord, cnt);
                } else {
                    ans.emplace_back(lex, identifier, cnt);
                }
                lex.clear();
                ans.emplace_back("*", binaryMultiplication, cnt);
            } else if (symbol == '=') {
                conditional = 0;
                if (is_reserved(lex, tr)) {
                    ans.emplace_back(lex, reservedWord, cnt);
                } else {
                    ans.emplace_back(lex, identifier, cnt);
                }
                lex.clear();
                ans.emplace_back("=", assignmentOperators, cnt);
            } else {
                switch (symbol) {
                    case '{':
                        conditional = 0;
                        ans.emplace_back(lex, is_reserved(lex, tr) ? reservedWord : identifier, cnt);
                        lex.clear();
                        ans.emplace_back("{", openingCurlyBracket, cnt);
                        continue;
                    case '}':
                        conditional = 0;
                        ans.emplace_back(lex, is_reserved(lex, tr) ? reservedWord : identifier, cnt);
                        lex.clear();
                        ans.emplace_back("}", closingCurlyBracket, cnt);
                        continue;
                    case '(':
                        conditional = 0;
                        ans.emplace_back(lex, is_reserved(lex, tr) ? reservedWord : identifier, cnt);
                        lex.clear();
                        ans.emplace_back("(", openingRoundBracket, cnt);
                        continue;
                    case ')':
                        conditional = 0;
                        ans.emplace_back(lex, is_reserved(lex, tr) ? reservedWord : identifier, cnt);
                        lex.clear();
                        ans.emplace_back(")", closingRoundBracket, cnt);
                        continue;
                    case '[':
                        conditional = 0;
                        ans.emplace_back(lex, is_reserved(lex, tr) ? reservedWord : identifier, cnt);
                        lex.clear();
                        ans.emplace_back("[", openingSquareBracket, cnt);
                        continue;
                    case ']':
                        conditional = 0;
                        ans.emplace_back(lex, is_reserved(lex, tr) ? reservedWord : identifier, cnt);
                        lex.clear();
                        ans.emplace_back("]", closingSquareBracket, cnt);
                        continue;
                    default:
                        conditional = 6;
                        if (is_reserved(lex, tr)) {
                            ans.emplace_back(lex, reservedWord, cnt);
                        } else {
                            ans.emplace_back(lex, identifier, cnt);
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
                symbol == ',' ||
                symbol == '|' ||
                symbol == '&' ||
                symbol == '\n') {
                conditional = 0;
                ans.emplace_back(lex, intt, cnt);
                if (symbol == '\n') {
                    ++cnt;
                }
                lex.clear();
                if (symbol == '+') {
                    lex += symbol;
                    conditional = 7;
                } else if (symbol == '-') {
                    lex += symbol;
                    conditional = 8;
                } else if (symbol == '*') {
                    ans.emplace_back("*", binaryMultiplication, cnt);
                } else if (symbol == '/') {
                    ans.emplace_back("/", division, cnt);
                } else if (symbol == ';') {
                    ans.emplace_back(";", semicolon, cnt);
                } else if (symbol == '=') {
                    ans.emplace_back("=", assignmentOperators, cnt);
                } else if (symbol == ',') {
                    ans.emplace_back(",", comma, cnt);
                } else if (symbol == '|') {
                    ans.emplace_back("|", other, cnt);
                } else if (symbol == '&') {
                    ans.emplace_back("&", other, cnt);
                }
            } else if (symbol == '.') {
                conditional = 3;
                lex += symbol;
            } else if (isdigit(symbol)) {
                lex += symbol;
            } else {
                switch (symbol) {
                    case '{':
                        conditional = 0;
                        ans.emplace_back(lex, intt, cnt);
                        lex.clear();
                        ans.emplace_back("{", openingCurlyBracket, cnt);
                        continue;
                    case '}':
                        conditional = 0;
                        ans.emplace_back(lex, intt, cnt);
                        lex.clear();
                        ans.emplace_back("}", closingCurlyBracket, cnt);
                        continue;
                    case '(':
                        conditional = 0;
                        ans.emplace_back(lex, intt, cnt);
                        lex.clear();
                        ans.emplace_back("(", openingRoundBracket, cnt);
                        continue;
                    case ')':
                        conditional = 0;
                        ans.emplace_back(lex, intt, cnt);
                        lex.clear();
                        ans.emplace_back(")", closingRoundBracket, cnt);
                        continue;
                    case '[':
                        conditional = 0;
                        ans.emplace_back(lex, intt, cnt);
                        lex.clear();
                        ans.emplace_back("[", openingSquareBracket, cnt);
                        continue;
                    case ']':
                        conditional = 0;
                        ans.emplace_back(lex, intt, cnt);
                        lex.clear();
                        ans.emplace_back("]", closingSquareBracket, cnt);
                        continue;
                    case '>':
                        conditional = 0;
                        ans.emplace_back(lex, intt, cnt);
                        lex.clear();
                        ans.emplace_back(">", logicalOperations, cnt);
                        continue;
                    case '<':
                        conditional = 0;
                        ans.emplace_back(lex, intt, cnt);
                        lex.clear();
                        ans.emplace_back("<", logicalOperations, cnt);
                        continue;
                    default:
                        conditional = 0;
                        ans.emplace_back(lex, intt, cnt);
                        ans.emplace_back("" + symbol, other, cnt);
                        lex.clear();
                }
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
                symbol == ',' ||
                symbol == '>' ||
                symbol == '<') {
                conditional = 0;
                ans.emplace_back(lex, floatt, cnt);
                lex.clear();
                if (symbol == '+') {
                    lex += symbol;
                    conditional = 7;
                } else if (symbol == '-') {
                    lex += symbol;
                    conditional = 8;
                } else if (symbol == '*') {
                    ans.emplace_back("*", binaryMultiplication, cnt);
                } else if (symbol == '/') {
                    ans.emplace_back("/", division, cnt);
                } else if (symbol == ';') {
                    ans.emplace_back(";", semicolon, cnt);
                } else if (symbol == '=') {
                    ans.emplace_back("=", assignmentOperators, cnt);
                } else if (symbol == ',') {
                    ans.emplace_back(",", comma, cnt);
                } else if (symbol == '<') {
                    ans.emplace_back("<", logicalOperations, cnt);
                } else if (symbol == '>') {
                    ans.emplace_back(">", logicalOperations, cnt);
                }
            } else if (isdigit(symbol)) {
                lex += symbol;
            } else {
                conditional = 0;
                ans.emplace_back(lex, floatt, cnt);
                ans.emplace_back("" + symbol, other, cnt);
                lex.clear();
            }
        } else if (conditional == 4) {
            // string
            if (symbol == '"') {
                conditional = 0;
                lex += symbol;
                ans.emplace_back(lex, string, cnt);
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
                    ans.emplace_back(lex, floatt, cnt);
                } else {
                    ans.emplace_back(lex, other, cnt);
                }
                lex.clear();
            } else {
                lex += symbol;
            }
        } else if (conditional == 6) {
            if (symbol == ' ') {
                conditional = 0;
                ans.emplace_back(lex, other, cnt);
                lex.clear();
            } else if (symbol == '+') {
                conditional = 0;
                ans.emplace_back(lex, other, cnt);
                lex.clear();
                lex += symbol;
                conditional = 7;
            } else if (symbol == '-') {
                conditional = 0;
                ans.emplace_back(lex, other, cnt);
                lex.clear();
                lex += symbol;
                conditional = 8;
            } else if (symbol == '/') {
                conditional = 0;
                ans.emplace_back(lex, other, cnt);
                ans.emplace_back("/", division, cnt);
                lex.clear();
            } else if (symbol == '*') {
                conditional = 0;
                ans.emplace_back(lex, other, cnt);
                ans.emplace_back("*", binaryMultiplication, cnt);
                lex.clear();
            } else if (symbol == ';') {
                conditional = 0;
                ans.emplace_back(lex, other, cnt);
                ans.emplace_back(";", semicolon, cnt);
                lex.clear();
            } else if (symbol == '\n') {
                conditional = 0;
                ans.emplace_back(lex, other, cnt);
                ++cnt;
                lex.clear();
            } else if (symbol == '=') {
                conditional = 0;
                if (lex == "!") {
                    ans.emplace_back("!=", logicalOperations, cnt);
                } else if (lex == "=") {
                    ans.emplace_back("==", logicalOperations, cnt);
                } else {
                    ans.emplace_back("=", assignmentOperators, cnt);
                }
                lex.clear();
            } else if (symbol == '&') {
                if (ans.back().getName() == "&" || lex == "&") {
                    ans.back() = Lexeme("&&", logicalOperations, cnt);
                    lex.clear();
                    conditional = 0;
                } else {
                    lex += symbol;
                }
            } else if (symbol == '|') {
                if (ans.back().getName() == "|" || lex == "|") {
                    ans.back() = Lexeme("||", logicalOperations, cnt);
                    lex.clear();
                    conditional = 0;
                } else {
                    lex += symbol;
                }
            } else {
                switch (symbol) {
                    case '{':
                        conditional = 0;
                        ans.emplace_back(lex, other, cnt);
                        lex.clear();
                        ans.emplace_back("{", openingCurlyBracket, cnt);
                        continue;
                    case '}':
                        conditional = 0;
                        ans.emplace_back(lex, other, cnt);
                        lex.clear();
                        ans.emplace_back("}", closingCurlyBracket, cnt);
                        continue;
                    case '(':
                        conditional = 0;
                        ans.emplace_back(lex, other, cnt);
                        lex.clear();
                        ans.emplace_back("(", openingRoundBracket, cnt);
                        continue;
                    case ')':
                        conditional = 0;
                        ans.emplace_back(lex, other, cnt);
                        lex.clear();
                        ans.emplace_back(")", closingRoundBracket, cnt);
                        continue;
                    case '[':
                        conditional = 0;
                        ans.emplace_back(lex, other, cnt);
                        lex.clear();
                        ans.emplace_back("[", openingSquareBracket, cnt);
                        continue;
                    case ']':
                        conditional = 0;
                        ans.emplace_back(lex, other, cnt);
                        lex.clear();
                        ans.emplace_back("]", closingSquareBracket, cnt);
                        continue;
                    case '>':
                        conditional = 0;
                        ans.emplace_back(lex, other, cnt);
                        lex.clear();
                        ans.emplace_back(">", logicalOperations, cnt);
                        continue;
                    case '<':
                        conditional = 0;
                        ans.emplace_back(lex, other, cnt);
                        lex.clear();
                        ans.emplace_back("<", logicalOperations, cnt);
                        continue;
                    default:
                        lex += symbol;
                }
            }
        } else if (conditional == 7) {
            if (symbol == '+') {
                ans.emplace_back("++", increment);
                lex.clear();
                conditional = 0;
            } else {
                ans.emplace_back("+", unaryPlus);
                lex.clear();
                lex += symbol;
                if (isdigit(symbol)) {
                    conditional = 2;
                } else if (symbol == '\"') {
                    conditional = 4;
                } else if (symbol == '\'') {
                    conditional = 5;
                } else if (symbol == ' ') {
                    lex.clear();
                    conditional = 0;
                } else if (isalpha(symbol)) {
                    conditional = 1;
                } else {
                    conditional = 6;
                }
            }
        } else if (conditional == 8) {
            if (symbol == '-') {
                ans.emplace_back("--", decrement);
                lex.clear();
                conditional = 0;
            } else {
                ans.emplace_back("-", unaryMinus);
                lex.clear();
                lex += symbol;
                if (isdigit(symbol)) {
                    conditional = 2;
                } else if (symbol == '\"') {
                    conditional = 4;
                } else if (symbol == '\'') {
                    conditional = 5;
                } else if (isalpha(symbol)) {
                    conditional = 1;
                } else if (symbol == ' ') {
                    lex.clear();
                    conditional = 0;
                } else {
                    conditional = 6;
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
    return lexemes_[curr_lex_];
}

Lexeme Lexical_analyzer::prev_lexeme() {
    return lexemes_[curr_lex_ - 2];
}