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
            throw Error("Unsupported operation for string");
        }
        stack.emplace_back("string", string);
    } else if (lhs.getType() == floatt || lhs.getType() == intt) {
        if (rhs.getType() != floatt && rhs.getType() != intt &&
            rhs.getType() != identifier) {
            throw Error("Invalid operand types for numeric operation");
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
                throw Error("Unsupported operation for numeric types");
            }
        } else if (lhs.getType() == intt && rhs.getType() == intt) {
            if (op.getName() == "+" || op.getName() == "-" ||
                op.getName() == "*" || op.getName() == "/") {
                stack.emplace_back("result", intt);
            } else if (op.getName() == "==" || op.getName() == "!=" || op.getName() == ">" || op.getName() == "<" || op.
                       getName() == ">=" || op.getName() == "<=") {
                stack.emplace_back("result", booll);
            } else {
                throw Error("Unsupported operation for numeric types");
            }
        } else {
            throw Error("Unsupported operation for numeric types");
        }
    } else if (lhs.getType() == identifier) {
        // left operand is variable
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
                    throw Error("Unsupported operation for numeric types");
                }
                stack.emplace_back("result", intt);
            } else if (lhs_type == intt && rhs_type == floatt ||
                       lhs_type == floatt && rhs_type == intt) {
                if (!(op.getName() == "+" || op.getName() == "-" ||
                      op.getName() == "/" || op.getName() == "*") ||
                    op.getName() == "=") {
                    throw Error("Unsupported operation for numeric types");
                }
                stack.emplace_back("result", floatt);
            } else if (lhs_type == booll & rhs_type == booll) {
                if (!(op.getName() == "=" || op.getName() == "!=" || op.getName() == "==" || op.getName() == "&&" || op.
                      getName() == "||" || op.
                      getName() == "and" || op.getName() == "or")) {
                    throw Error("Unsupported operation for bool types");
                }
                stack.emplace_back("result", booll);
            } else if (lhs_type == string && rhs_type == string) {
                if (op.getName() == "+") {
                    stack.emplace_back("result", string);
                } else if (op.getName() == "==") {
                    stack.emplace_back("result", booll);
                } else {
                    throw Error("Unsupported operation for strings");
                }
            } else {
                throw Error("Unsupported operands");
            }
        } else if (rhs.getType() == intt || rhs.getType() == floatt) {
            lexemeType rhs_type = rhs.getType();
            if (lhs_type == intt && rhs_type == intt) {
                if (!(op.getName() == "+" || op.getName() == "-" ||
                      op.getName() == "/" || op.getName() == "*" ||
                      op.getName() == "=")) {
                    throw Error("Unsupported operation for numeric types");
                }
                stack.emplace_back("result", intt);
            } else if (lhs_type == intt && rhs_type == floatt ||
                       lhs_type == floatt && rhs_type == intt) {
                if (!(op.getName() == "+" || op.getName() == "-" ||
                      op.getName() == "/" || op.getName() == "*" ||
                      op.getName() == "=")) {
                    throw Error("Unsupported operation for numeric types");
                }
                stack.emplace_back("result", floatt);
            } else {
                throw Error("Unsupported operands for that operation");
            }
        } else if (lhs_type == string && rhs.getType() == string) {
            if (!(op.getName() == "=" || op.getName() == "+")) {
                throw Error("Unsupported operation for string");
            }
            stack.emplace_back("result", string);
        } else if (lhs_type == booll && rhs.getType() == booll) {
            if (!(op.getName() == "=" || op.getName() == "==" || op.getName() == ">" || op.getName() == "<" || op.
                  getName() == "!=" || op.getName() == ">=" || op.getName() == "<=")) {
                throw Error("Unsupported operation for bool");
            }
            stack.emplace_back("result", booll);
        } else {
            throw Error(
                "Unsupported operand types for binary operation");
        }
    } else if (lhs.getType() == string && rhs.getType() == identifier && chc_->getType(rhs.getName()) == string) {
        if (op.getName() == "+") {
            stack.emplace_back("result", string);
        } else if (op.getName() == "==") {
            stack.emplace_back("result", booll);
        } else {
            throw Error("Unsupported operation for boolean types");
        }
    } else if (lhs.getType() == booll && rhs.getType() == booll) {
        if (op.getName() == "&&" || op.getName() == "||") {
            stack.emplace_back("result", booll);
        } else if (op.getName() == "==" || op.getName() == "!=") {
            stack.emplace_back("result", booll);
        } else {
            throw Error("Unsupported operation for boolean types");
        }
    } else {
        throw Error("Unsupported operands");
    }
}

void semstack::checkUno() {
    auto rhs = stack.back();
    stack.pop_back();
    auto op = stack.back();
    stack.pop_back();
    auto rhs_type = rhs.getType();
    if (rhs_type == booll) {
        if (op.getName() != "not") {
            throw Error("Unsupported operation");
        }
        stack.emplace_back("result", booll);
    } else if (rhs_type == identifier) {
        auto rhst = chc_->getType(rhs.getName());
        if (rhst == booll) {
            if (op.getName() == "not") {
                stack.emplace_back("result", booll);
            } else {
                throw Error("Unsupported operation");
            }
        } else if (rhst == intt || rhst == floatt) {
            if (op.getName() == "-" || op.getName() == "+" || op.getName() == "++" || op.getName() == "--") {
                stack.emplace_back(rhs);
            } else {
                throw Error("Unsupported operation");
            }
        } else {
            throw Error("Unsupported operation");
        }
    }
}


void semstack::clear() {
    stack.clear();
}
