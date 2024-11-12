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

    void get_lexemes();

    Lexeme get_lexeme();

    friend bool is_reserved(std::string &a);

private:
    std::vector<Lexeme> lexemes_;

    int curr_lex_ = 0;

    static void removeBetweenHashes(char *str) {
        char *readPtr = str;
        char *writePtr = str;
        bool insideHash = false;

        while (*readPtr != '\0') {
            if (*readPtr == '#') {
                insideHash = !insideHash;
            } else if (!insideHash) {
                *writePtr++ = *readPtr;
            }
            ++readPtr;
        }
        *writePtr = '\0';
    }
};
