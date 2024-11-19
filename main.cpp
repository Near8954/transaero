#include <iostream>
#include "../syntax_analyzer/syntax_analyzer.h"

int main() {
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     try {
        Syntax_analyzer a;
        std::cout << "OK";
     } catch (Lexeme lex) {
         std::cout << lex.getType();
         std::cout << "Error " << lex.getName() << " in string " << lex.getPos();
     }

//     for (int i = 0; int z = 5; ++i)
}
