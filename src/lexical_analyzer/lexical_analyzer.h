//
// Created by near on 22.10.24.
//

#pragma once
#include <cctype>
#include <clocale>
#include <string>
#include <vector>
#include "../lexeme/lexeme.h"
#include "../trie/Trie.h"
#include <fstream>

class Lexical_analyzer {
public:
    Lexical_analyzer();

    static std::vector<Lexeme> get_lexemes(const char *text, size_t length);

    friend bool is_reserved(std::string &a);
};

