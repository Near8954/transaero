//
// Created by near on 22.10.24.
//

#pragma once
#include <cctype>
#include <clocale>
#include <string>
#include <vector>
#include "../lexeme/lexeme.h"

class Lexical_analyzer {
public:
    Lexical_analyzer();

    std::vector<Lexeme> get_lexemes(const char *text);

    friend bool is_reserved(std::string &a);
};

