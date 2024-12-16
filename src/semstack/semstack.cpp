//
// Created by Роман Балдин on 15.12.2024.
//

#include "semstack.h"

void semstack::checkBin() {
  Lexeme rhs = stack.back();
  stack.pop_back();
  Lexeme op = stack.back();
  stack.pop_back();
  Lexeme lhs = stack.back();
  stack.pop_back();
  if (lhs.getType() == string && rhs.getType() == string) {
    if (!(op.getName() == "+")) {
      throw "Wrong operation for string";
    }
    stack.emplace_back("string", string);
  } else if (lhs.getType() == floatt || lhs.getType() == intt) {
    if (rhs.getType() != floatt && rhs.getType() != intt) {
      throw std::runtime_error("Invalid operand types for numeric operation");
    }
    if ((rhs.getType() == floatt || lhs.getType() == floatt) &&
        (op.getName() == "+" || op.getName() == "-" || op.getName() == "*" ||
         op.getName() == "/")) {
      stack.emplace_back("result", floatt);
    } else if (lhs.getType() == intt && rhs.getType() == intt &&
               (op.getName() == "+" || op.getName() == "-" ||
                op.getName() == "*" || op.getName() == "/")) {
      stack.emplace_back("result", intt);
    } else {
      throw std::runtime_error("Unsupported operation for numeric types");
    }
  } else {
    throw std::runtime_error("Unsupported operand types for binary operation");
  }
}
