#include "lexical_analyzer.h"

#include <iostream>

int main() {

    std::ifstream code("../src/code.txt");
    code.seekg(0, std::ios::end);
    const size_t size = code.tellg();
    code.seekg(0, std::ios::beg);
    const auto text = new char[size];
    code.read(text, size);


    Lexical_analyzer analyzer;
    auto b = analyzer.get_lexemes(text, size);
    for (const auto & i : b) {
        std::cout << i << "\n";
    }
}
