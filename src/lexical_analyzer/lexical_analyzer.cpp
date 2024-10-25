//
// Created by near on 22.10.24.
//

#include "lexical_analyzer.h"

Lexical_analyzer::Lexical_analyzer() = default;

bool is_reserved(const std::string &a, const Trie &tr) {
    return tr.search(a);
}


void new_lex(std::vector<Lexeme> &ans, std::string &lex, int &conditional, const Trie &tr, int pos) {
    if (!lex.empty()) {
        if (lex == "-") {
            if (static_cast<Lexeme>(ans.back()) == Lexeme("-", binaryMinus)
                || static_cast<Lexeme>(ans.back()) == Lexeme("-", unaryMinus)) {
                ans.back() = Lexeme("--", decrement);
            } else if (static_cast<Lexeme>(ans.back()) == Lexeme("", literal)
                       || static_cast<Lexeme>(ans.back()) == Lexeme("", identifier)) {
                ans.emplace_back("-", binaryMinus);
            } else {
                ans.emplace_back("-", unaryMinus);
            }
        } else if (lex == "(") {
            ans.emplace_back("(", openingRoundBracket);
        } else if (lex == ")") {
            ans.emplace_back(")", closingRoundBracket);
        } else if (lex == "[") {
            ans.emplace_back("[", openingSquareBracket);
        } else if (lex == "]") {
            ans.emplace_back("]", closingSquareBracket);
        } else if (lex == "{") {
            ans.emplace_back("{", openingCurlyBracket);
        } else if (lex == "}") {
            ans.emplace_back("}", closingCurlyBracket);
        } else if (lex == ",") {
            ans.emplace_back(",", comma);
        } else if (lex == ".") {
            if (ans.back() == Lexeme("", literal)) {
                ans.back() = Lexeme(ans.back().getName() + lex, literal);
            } else if (ans.back().getName().back() == '.') {
                ans.back() = Lexeme(ans.back().getName() + lex, other);
            } else {
                ans.emplace_back(".", dot);
            }
        } else if (isdigit(lex[0])) {
            if (ans.back() == Lexeme("", literal)) {
                ans.back() = Lexeme(ans.back().getName() + lex, literal);
            } else {
                ans.emplace_back(lex, literal);
            }
        } else if (lex == "!") {
            ans.emplace_back("!", logicalOperations);
        } else if (lex == "=") {
            if (ans.back() == Lexeme("!", logicalOperations)) {
                ans.back() = Lexeme("!=", logicalOperations);
            } else if (ans.back() == Lexeme("-", binaryMinus)) {
                ans.back() = Lexeme("-=", assignmentOperators);
            } else if (ans.back() == Lexeme("+", binaryPlus)) {
                ans.back() = Lexeme("+=", assignmentOperators);
            } else if (ans.back() == Lexeme("/", division)) {
                ans.back() = Lexeme("/=", assignmentOperators);
            } else if (ans.back() == Lexeme("*", binaryMultiplication)) {
                ans.back() = Lexeme("*=", assignmentOperators);
            } else if (ans.back() == Lexeme("=", assignmentOperators)) {
                ans.back() = Lexeme("==", logicalOperations);
            } else {
                ans.emplace_back("=", assignmentOperators);
            }
        } else if (lex == "&") {
            if (ans.back() == Lexeme("&", other)) {
                ans.back() = Lexeme("&&", logicalOperations);
            } else {
                ans.emplace_back("&", other);
            }
        } else if (lex == "|") {
            if (ans.back() == Lexeme("|", other)) {
                ans.back() = Lexeme("||", logicalOperations);
            } else {
                ans.emplace_back("|", other);
            }
        } else if (lex == ";") {
            ans.emplace_back(";", semicolon);
        } else if (lex == "+") {
            if (static_cast<Lexeme>(ans.back()) == Lexeme("+", binaryPlus)
                || static_cast<Lexeme>(ans.back()) == Lexeme("+", unaryPlus)) {
                ans[ans.size() - 1] = Lexeme("++", increment);
            } else if (static_cast<Lexeme>(ans.back()) == Lexeme("", literal)
                       || static_cast<Lexeme>(ans.back()) == Lexeme("", identifier)) {
                ans.emplace_back("+", binaryPlus);
            } else {
                ans.emplace_back("+", unaryPlus);
            }
        } else if (lex == "*") {
            if (static_cast<Lexeme>(ans.back()) == Lexeme("", literal)
                || static_cast<Lexeme>(ans.back()) == Lexeme("", identifier)) {
                ans.emplace_back("*", binaryMultiplication);
            } else {
                ans.emplace_back("*", linkMultiplication);
            }
        } else if (lex == "/") {
            ans.emplace_back("/", division);
        } else if (is_reserved(lex, tr) && conditional == 1) {
            ans.emplace_back(lex, reservedWord);
        } else if (conditional == 1) {
            ans.emplace_back(lex, identifier);
        } else {
            ans.emplace_back(lex, literal);
        }
        lex.clear();
        conditional = 0;
        ans.back().set_pos(pos);
    }
}


std::vector<Lexeme> Lexical_analyzer::get_lexemes(const char *text, size_t length) {
    std::vector<Lexeme> ans;
    int conditional = 0;
    char symbol;
    std::string lex;
    Trie tr;
    std::ifstream fin("../src/reserved_words.txt");
    while (std::getline(fin, lex)) {
        tr.insert(lex);
    }
    // 0 - default
    // 1- сейчас буква
    // 2 - сейчас символ
    lex.clear();
    int cnt = 1;

    for (int i = 0; i < length; ++i) {
        symbol = text[i];

        if (conditional == 0) {
            if (std::isalpha(symbol) || symbol == '_') {
                conditional = 1;
                lex.push_back(symbol);
                continue;
            } else if (symbol == ' ' || symbol == '\n') {
                new_lex(ans, lex, conditional, tr, cnt);
                if (symbol == '\n') {
                    ++cnt;
                }
                conditional = 0;
            } else {
                lex.push_back(symbol);
                new_lex(ans, lex, conditional, tr, cnt);
            }
        } else if (conditional == 1) {
            if (std::isalpha(symbol) || symbol == '_' || symbol >= '0' && symbol <= '9') {
                lex.push_back(symbol);
                continue;
            } else if (symbol == ' ' || symbol == '\n') {
                new_lex(ans, lex, conditional, tr, cnt);
                if (symbol == '\n') {
                    ++cnt;
                }
                conditional = 0;
            } else {
                std::string b;
                b += symbol;
                new_lex(ans, lex, conditional, tr, cnt);
                new_lex(ans, b, conditional, tr, cnt);
                conditional = 0;
            }
        }

        new_lex(ans, lex, conditional, tr, cnt);
    }

    return ans;
}
