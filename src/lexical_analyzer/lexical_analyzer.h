//
// Created by near on 22.10.24.
//

#ifndef LEXEMES_H
#define LEXEMES_H

#include <string>
#include <vector>
#include "../lexeme/lexeme.h"

class Lexical_analyzer {
public:
    Lexical_analyzer();

    std::vector<Lexeme> get_lexemes(char *text);
};


#endif //LEXEMES_H
