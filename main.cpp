#include <iostream>


int main() {


    Lexical_analyzer analyzer;
    auto b = analyzer.get_lexemes(text, size);
    for (const auto &lexeme: b) {
        std::cout << lexeme << "\n";
    }
}
