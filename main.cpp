#include <iostream>
#include "../syntax_analyzer/syntax_analyzer.h"

int main() {
    try {
        Syntax_analyzer a;
        std::cout << "OK";
    } catch (Lexeme lex) {
        std::cout << "Error " << lex.getName();
    }
}
