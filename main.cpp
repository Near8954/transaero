#include <iostream>
#include "../syntax_analyzer/syntax_analyzer.h"

int main() {
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     try {
        Syntax_analyzer a;
        std::cout << "=========== OK! ===========\n\n";
     } catch (Lexeme lex) {

         std::cerr << "Error " << lex.getName() << " in string " << lex.getPos() << "\n";
         std::cerr << "Lexem type is " << lex.getType();


     }

//
//     int a;
//     for (int i = 0; i < 5; ++i) {
//         int a = 5;
//         std::cout << a;
//     }


}
