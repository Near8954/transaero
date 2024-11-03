#include "lexical_analyzer.h"

#include <iostream>

void removeBetweenHashes(char *str) {
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

int main() {
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

    Lexical_analyzer analyzer;
    auto b = analyzer.get_lexemes(text, size);
    for (const auto &lexeme: b) {
        std::cout << lexeme << "\n";
    }
}
