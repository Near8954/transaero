//
// Created by Иванов Кирилл on 23.12.2024.
//

#pragma once
#include "iostream"
#include "vector"
#include "../lexeme/lexeme.h"
#include "../error/error.h"

class poliz {
public:

    void pushStack(Lexeme lex);
    void pushPoliz(Lexeme lex);
    void clearStack();
    int getPos();
    void setPos(int i, int x);

    std::vector<Lexeme> getPoliz();

private:
    int cur_;
    std::vector <Lexeme> poliz_;
    std::vector <Lexeme> stack_;
    std::vector <lexemeType> types_;
};



