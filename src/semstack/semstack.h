//
// Created by Роман Балдин on 15.12.2024.
//

#ifndef SEMSTACK_H
#define SEMSTACK_H

#include "../checker/checker.h"
#include "../lexeme/lexeme.h"
#include "../tid/tid.h"
#include <vector>
class semstack {
public:
  void push(const Lexeme &lex) { stack.push_back(lex); }
  void clear();
  void checkBin();
  void checkUno();
  void checkBool();
  void set_checker(checker *chc) { chc_ = chc; }

private:
  std::vector<Lexeme> stack;
  checker *chc_;
};

#endif // SEMSTACK_H
