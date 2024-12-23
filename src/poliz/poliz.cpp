//
// Created by Иванов Кирилл on 23.12.2024.
//

#include "poliz.h"



int getPriority(Lexeme lex) {
    if (lex.getPriority() != -1) {
        return lex.getPriority();
    }
    if (lex.getName() == "(") return 0;
    if (lex.getName() == ")") return 0;
    if (lex.getName() == ",") return 0;
    if (lex.getName() == "\n") return 0;
    std::string name = lex.getName();
    if (name == "=") {
        return 0;
    } else if (name == "or" || name == "||") {
        return 1;
    } else if (name == "and" || name == "&&") {
        return 2;
    } else if (name == "==" || name == "!=" || name == ">" || name == "<" || name == "<=" || name == ">=") {
        return 3;
    } else if (name == "+" || name == "-") {
        return 4;
    } else if (name == "*" || name == "/") {
        return 5;
    } else if (name == "--" || name == "++" || name == "not") {
        return 6;
    } else if (name == "[" || name == "]") {
        return 7;
    } else if (lex.getType() == func_call) {
        return 8;
    }
    throw Error("Unknown operator");

}

void poliz::pushPoliz(Lexeme lex) {
    poliz_.push_back(lex);
    types_.push_back(lex.getType());
    ++cur_;
}

void poliz::pushStack(Lexeme lex) {
    int pr = getPriority(lex);
    if (lex.getName() == "(") {
        stack_.push_back(lex);
        return;
    }
    if (lex.getType() == comma) {
        while (!stack_.empty() && stack_.back().getType() != openingRoundBracket) {
            pushPoliz(stack_.back());
            stack_.pop_back();
        }
        return;
    }
    if (lex.getName() == "\n") {
        clearStack();
        pushPoliz(lex);
        return;
    }
    if (lex.getType() == closingRoundBracket) {
        while (stack_.back().getType() != openingRoundBracket) {
            pushPoliz(stack_.back());
            stack_.pop_back();
        }
        stack_.pop_back();
        return;
    }
    while (!stack_.empty() && getPriority(stack_.back()) >= pr) {
        pushPoliz(stack_.back());
        stack_.pop_back();
    }
    lex.setPriority(pr);
    stack_.push_back(lex);
}

void poliz::clearStack() {
    stack_.clear();
}

int poliz::getPos() {
    return cur_;
}

void poliz::setPos(int i, int x) {
    poliz_[i].setFieldId(x);
}

std::vector<Lexeme> poliz::getPoliz() {
    return poliz_;
}