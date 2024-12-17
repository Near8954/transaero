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
            throw std::runtime_error("Unsupported operation for string");
        }
        stack.emplace_back("string", string);
    } else if (lhs.getType() == floatt || lhs.getType() == intt) {
        if (rhs.getType() != floatt && rhs.getType() != intt &&
            rhs.getType() != identifier) {
            throw std::runtime_error("Invalid operand types for numeric operation");
        }
        if ((rhs.getType() == floatt || lhs.getType() == floatt ||
             rhs.getType() == identifier &&
             (chc_->getType(rhs.getName()) == floatt ||
              chc_->getType(rhs.getName()) == intt))) {
            if ((op.getName() == "+" || op.getName() == "-" || op.getName() == "*" ||
                 op.getName() == "/")) {
                stack.emplace_back("result", floatt);
            } else if (op.getName() == "==" || op.getName() == ">" || op.getName() == "<" || op.getName() == "!=" || op.
                       getName() == ">=" || op.getName() == "<=") {
                stack.emplace_back("result", booll);
            } else {
                throw std::runtime_error("Unsupported operation for numeric types");
            }
        } else if (lhs.getType() == intt && rhs.getType() == intt) {
            if (op.getName() == "+" || op.getName() == "-" ||
                op.getName() == "*" || op.getName() == "/") {
                stack.emplace_back("result", intt);
            } else if (op.getName() == "==" || op.getName() == "!=" || op.getName() == ">" || op.getName() == "<" || op.
                       getName() == ">=" || op.getName() == "<=") {
                stack.emplace_back("result", booll);
            } else {
                throw std::runtime_error("Unsupported operation for numeric types");
            }
        } else {
            throw std::runtime_error("Unsupported operation for numeric types");
        }
    } else if (lhs.getType() == identifier) {
        lexemeType lhs_type = chc_->getType(lhs.getName());
        if (rhs.getType() == identifier) {
            lexemeType rhs_type = chc_->getType(rhs.getName());
            if (lhs_type == rhs_type && op.getName() == "=") {
                stack.emplace_back("result", lhs_type);
                return;
            }
            if (lhs_type == intt && rhs_type == intt) {
                if (!(op.getName() == "+" || op.getName() == "-" ||
                      op.getName() == "/" || op.getName() == "*") ||
                    op.getName() == "=") {
                    throw std::runtime_error("Unsupported operation for numeric types");
                }
                stack.emplace_back("result", intt);
            } else if (lhs_type == intt && rhs_type == floatt ||
                       lhs_type == floatt && rhs_type == intt) {
                if (!(op.getName() == "+" || op.getName() == "-" ||
                      op.getName() == "/" || op.getName() == "*") ||
                    op.getName() == "=") {
                    throw std::runtime_error("Unsupported operation for numeric types");
                }
                stack.emplace_back("result", floatt);
            } else if (lhs_type == booll & rhs_type == booll) {
                if (!(op.getName() == "=" || op.getName() == "!=" || op.getName() == "==" || op.getName() == "&&" || op.
                      getName() == "||" || op.
                      getName() == "and" || op.getName() == "or")) {
                    throw std::runtime_error("Unsupported operation for bool types");
                }
                stack.emplace_back("result", booll);
            } else if (lhs_type == string && rhs_type == string) {
                if (op.getName() == "+") {
                    stack.emplace_back("result", string);
                } else if (op.getName() == "==") {
                    stack.emplace_back("result", booll);
                } else {
                    throw std::runtime_error("Unsupported operation for strings");
                }
            } else {
                throw std::runtime_error("Unsupported operands");
            }
        } else if (rhs.getType() == intt || rhs.getType() == floatt) {
            lexemeType rhs_type = rhs.getType();
            if (lhs_type == intt && rhs_type == intt) {
                if (!(op.getName() == "+" || op.getName() == "-" ||
                      op.getName() == "/" || op.getName() == "*" ||
                      op.getName() == "=")) {
                    throw std::runtime_error("Unsupported operation for numeric types");
                }
                stack.emplace_back("result", intt);
            } else if (lhs_type == intt && rhs_type == floatt ||
                       lhs_type == floatt && rhs_type == intt) {
                if (!(op.getName() == "+" || op.getName() == "-" ||
                      op.getName() == "/" || op.getName() == "*" ||
                      op.getName() == "=")) {
                    throw std::runtime_error("Unsupported operation for numeric types");
                }
                stack.emplace_back("result", floatt);
            } else {
                throw std::runtime_error("Unsupported operands for that operation");
            }
        } else if (lhs_type == string && rhs.getType() == string) {
            if (!(op.getName() == "=" || op.getName() == "+")) {
                throw std::runtime_error("Unsupported operation for string");
            }
            stack.emplace_back("result", string);
        } else if (lhs_type == booll && rhs.getType() == booll) {
            if (!(op.getName() == "=" || op.getName() == "==" || op.getName() == ">" || op.getName() == "<" || op.
                  getName() == "!=" || op.getName() == ">=" || op.getName() == "<=")) {
                throw std::runtime_error("Unsupported operation for bool");
            }
            stack.emplace_back("result", booll);
        } else {
            throw std::runtime_error(
                "Unsupported operand types for binary operation");
        }
    } else if (lhs.getType() == string && rhs.getType() == identifier && chc_->getType(rhs.getName()) == string) {
        if (op.getName() == "+") {
            stack.emplace_back("result", string);
        } else if (op.getName() == "==") {
            stack.emplace_back("result", booll);
        } else {
            throw std::runtime_error("Unsupported operation for boolean types");
        }
    } else if (lhs.getType() == booll && rhs.getType() == booll) {
        if (op.getName() == "&&" || op.getName() == "||") {
            stack.emplace_back("result", booll);
        } else if (op.getName() == "==" || op.getName() == "!=") {
            stack.emplace_back("result", booll);
        } else {
            throw std::runtime_error("Unsupported operation for boolean types");
        }
    } else {
        throw std::runtime_error("Unsupported operands");
    }
}

void semstack::clear() {
    stack.clear();
}
