//
// Created by Роман Балдин on 15.12.2024.
//

#ifndef SEMSTACK_H
#define SEMSTACK_H

#include "../lexeme/lexeme.h"
#include <vector>
class semstack {
public:
  void push(const Lexeme& lex) {
    stack.push_back(lex);
  }
  void checkBin() {
    Lexeme rhs = stack.back();
    stack.pop_back();
    Lexeme op = stack.back();
    stack.pop_back();
    Lexeme lhs = stack.back();
    stack.pop_back();
    if (lhs.getType() == string && rhs.getType() == string) {
      if (!(op.getName() == "=" || op.getName() == "+")) {
        throw "Wrong operation for string";
      }
      stack.emplace_back("string", string);
    }

  }
private:
  std::vector<Lexeme> stack;
};

#endif // SEMSTACK_H
