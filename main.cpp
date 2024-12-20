#include <iostream>
#include "../syntax_analyzer/syntax_analyzer.h"
#include "../error/error.h"

int main() {
//    throw Error("f");
    try {
        Syntax_analyzer a;
        std::cout << "=========== OK! ===========\n\n";
    } catch (Lexeme& lex) {
        std::cerr << "Error in " << lex.getName() << " in string " << lex.getPos() << "\n";
        std::cerr << "Lexem type is " << to_string(lex.getType());
    } catch (Error& err) {
        std::cerr << err.what() << '\n';
    }
}
