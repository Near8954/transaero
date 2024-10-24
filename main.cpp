#include "lexical_analyzer.h"

#include <iostream>

int main() {



    const char *text = "int gcd(int ABCd, int b) { int __r123 & !=b; {} ~ for (; b!= 0; r = a % b, a = b, b = r);return a;}";




    Lexical_analyzer a;
    auto b = a.get_lexemes(text);
    for (int i = 0; i < b.size(); ++i) {
        std::cout << b[i] << "\n";
    }
}
