//
// Created by near on 22.10.24.
//

#include "lexical_analyzer.h"

Lexical_analyzer::Lexical_analyzer() = default;

bool is_reserved(const std::string &a, const Trie &tr) {
    return tr.search(a);
}

std::vector<Lexeme> Lexical_analyzer::get_lexemes(const char *text, size_t length) {
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
                    default: ;
                }
            }
        } else if (conditional == 1) {
            // индентификатор
            if (symbol == ' ') {
                conditional = 0;
                if (is_reserved(lex, tr)) {
                    ans.emplace_back(lex, reservedWord);
                } else {
                    ans.emplace_back(lex, identifier);
                }
                lex.clear();
            } else if (isalpha(symbol) || symbol == '_' || isdigit(symbol)) {
                lex += symbol;
            } else {
                switch (symbol) {
                    case '{':
                        conditional = 0;
                        ans.emplace_back(lex, identifier);
                        lex.clear();
                        ans.emplace_back("{", openingCurlyBracket);
                        continue;
                    case '}':
                        conditional = 0;
                        ans.emplace_back(lex, identifier);
                        lex.clear();
                        ans.emplace_back("}", closingCurlyBracket);
                        continue;
                    case '(':
                        conditional = 0;
                        ans.emplace_back(lex, identifier);
                        lex.clear();
                        ans.emplace_back("(", openingRoundBracket);
                        continue;
                    case ')':
                        conditional = 0;
                        ans.emplace_back(lex, identifier);
                        lex.clear();
                        ans.emplace_back(")", closingRoundBracket);
                        continue;
                    case '[':
                        conditional = 0;
                        ans.emplace_back(lex, identifier);
                        lex.clear();
                        ans.emplace_back("[", openingSquareBracket);
                        continue;
                    case ']':
                        conditional = 0;
                        ans.emplace_back(lex, identifier);
                        lex.clear();
                        ans.emplace_back("]", closingSquareBracket);
                        continue;
                    default: ;
                }
            }
        } else if (conditional == 2) {
            // int
            if (symbol == ' ') {
                conditional = 0;
                ans.emplace_back(lex, literal);
                lex.clear();
            } else if (symbol == '.') {
                conditional = 3;
                lex += symbol;
            } else if (isdigit(symbol)) {
                lex += symbol;
            }
        } else if (conditional == 3) {
            // float
            if (symbol == ' ') {
                conditional = 0;
                ans.emplace_back(lex, literal);
                lex.clear();
            } else if (isdigit(symbol)) {
                lex += symbol;
            } else {
                lex += symbol;
                conditional = 6;
            }
        } else if (conditional == 4) {
            // string
            if (symbol == '"') {
                conditional = 0;
                lex += symbol;
                ans.emplace_back(lex, string);
                lex.clear();
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
            } else {
                lex += symbol;
            }
        }
    }
    return ans;
}
