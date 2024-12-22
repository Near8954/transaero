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
        if (!(op.getName() == "+" || op.getName() == "!=" || op.getName() == "==")) {
            throw Error(
                "Unsupported operation '" + op.getName() + "' for string type" + " in line " + std::to_string(
                    op.getPos()));
        }
        if (op.getName() == "==" || op.getName() == "!=") {
            stack.emplace_back("result", booll);
        } else {
            stack.emplace_back("result", string);
        }
    } else if (lhs.getType() == floatt || lhs.getType() == intt) {
        if (rhs.getType() != floatt && rhs.getType() != intt && rhs.getType() != identifier) {
            throw Error(
                "Invalid operand types for numeric operation: " + to_string(lhs.getType()) + " and " +
                to_string(rhs.getType()) + " in line " + std::to_string(op.getPos()));
        }
        if ((rhs.getType() == floatt || lhs.getType() == floatt || (rhs.getType() == identifier &&
                                                                    (chc_->getType(rhs.getName()) == floatt || chc_->
                                                                     getType(rhs.getName()) == intt)))) {
            if ((op.getName() == "+" || op.getName() == "-" || op.getName() == "*" || op.getName() == "/")) {
                stack.emplace_back("result", floatt);
            } else if (op.getName() == "==" || op.getName() == ">" || op.getName() == "<" || op.getName() == "!=" || op.
                       getName() == ">=" || op.getName() == "<=") {
                stack.emplace_back("result", booll);
            } else {
                throw Error(
                    "Unsupported operation '" + op.getName() + "' for numeric types" + " in line " + std::to_string(
                        op.getPos()));
            }
        } else if (lhs.getType() == intt && rhs.getType() == intt) {
            if (op.getName() == "+" || op.getName() == "-" || op.getName() == "*" || op.getName() == "/") {
                stack.emplace_back("result", intt);
            } else if (op.getName() == "==" || op.getName() == "!=" || op.getName() == ">" || op.getName() == "<" || op.
                       getName() == ">=" || op.getName() == "<=") {
                stack.emplace_back("result", booll);
            } else {
                throw Error(
                    "Unsupported operation '" + op.getName() + "' for numeric types" + " in line " + std::to_string(
                        op.getPos()));
            }
        } else {
            throw Error(
                "Unsupported operation for numeric types: " + to_string(lhs.getType()) + " and " +
                to_string(rhs.getType()) + " in line " + std::to_string(op.getPos()));
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
                if (op.getName() == "==" || op.getName() == "!=" || op.getName() == ">" || op.getName() == "<" || op.
                    getName() == ">=" || op.getName() == "<=") {
                    stack.emplace_back("result", booll);
                    return;
                }
                if (!((op.getName() == "+" || op.getName() == "-" || op.getName() == "/" || op.getName() == "*") || op.
                      getName() == "=")) {
                    throw Error(
                        "Unsupported operation '" + op.getName() + "' for numeric types" + " in line " + std::to_string(
                            op.getPos()));
                }
                stack.emplace_back("result", intt);
            } else if (lhs_type == intt && rhs_type == floatt || lhs_type == floatt && rhs_type == intt) {
                if (op.getName() == "==" || op.getName() == "!=" || op.getName() == ">" || op.getName() == "<" || op.
                    getName() == ">=" || op.getName() == "<=") {
                    stack.emplace_back("result", booll);
                    return;
                }
                if (!((op.getName() == "+" || op.getName() == "-" || op.getName() == "/" || op.getName() == "*") || op.
                      getName() == "=")) {
                    throw Error(
                        "Unsupported operation '" + op.getName() + "' for numeric types" + " in line " + std::to_string(
                            op.getPos()));
                }
                stack.emplace_back("result", floatt);
            } else if (lhs_type == booll && rhs_type == booll) {
                if (!(op.getName() == "=" || op.getName() == "!=" || op.getName() == "==" || op.getName() == "&&" || op.
                      getName() == "||" || op.getName() == "and" || op.getName() == "or")) {
                    throw Error(
                        "Unsupported operation '" + op.getName() + "' for bool types" + " in line " + std::to_string(
                            op.getPos()));
                }
                stack.emplace_back("result", booll);
            } else if (lhs_type == string && rhs_type == string) {
                if (op.getName() == "+") {
                    stack.emplace_back("result", string);
                } else if (op.getName() == "==" || op.getName() == "!=") {
                    stack.emplace_back("result", booll);
                } else {
                    throw Error(
                        "Unsupported operation '" + op.getName() + "' for strings" + " in line " + std::to_string(
                            op.getPos()));
                }
            } else {
                throw Error(
                    "Unsupported operands: " + to_string(lhs_type) + " and " + to_string(rhs_type) + " in line " +
                    std::to_string(op.getPos()));
            }
        } else if (rhs.getType() == intt || rhs.getType() == floatt) {
            lexemeType rhs_type = rhs.getType();
            if (lhs_type == intt && rhs_type == intt) {
                if (op.getName() == "==" || op.getName() == "!=" || op.getName() == ">" || op.getName() == "<" || op.
                    getName() == ">=" || op.getName() == "<=") {
                    stack.emplace_back("result", booll);
                    return;
                }
                if (!((op.getName() == "+" || op.getName() == "-" || op.getName() == "/" || op.getName() == "*" ||
                       op.
                       getName() == "="))) {
                    throw Error(
                        "Unsupported operation '" + op.getName() + "' for numeric types" + " in line " +
                        std::to_string(
                            op.getPos()));
                }
                stack.emplace_back("result", intt);
            } else if (lhs_type == intt && rhs_type == floatt || lhs_type == floatt && rhs_type == intt) {
                if (!((op.getName() == "+" || op.getName() == "-" || op.getName() == "/" || op.getName() == "*") || op.
                      getName() == "=")) {
                    throw Error(
                        "Unsupported operation '" + op.getName() + "' for numeric types" + " in line " + std::to_string(
                            op.getPos()));
                }
                stack.emplace_back("result", floatt);
            } else {
                throw Error(
                    "Unsupported operands for that operation: " + to_string(lhs_type) + " and " + to_string(rhs_type) +
                    " in line " + std::to_string(op.getPos()));
            }
        } else if (lhs_type == string && rhs.getType() == string) {
            if (!(op.getName() == "=" || op.getName() == "+")) {
                throw Error(
                    "Unsupported operation '" + op.getName() + "' for string" + " in line " + std::to_string(
                        op.getPos()));
            }
            stack.emplace_back("result", string);
        } else if (lhs_type == booll && rhs.getType() == booll) {
            if (!(op.getName() == "=" || op.getName() == "==" || op.getName() == ">" || op.getName() == "<" || op.
                  getName() == "!=" || op.getName() == ">=" || op.getName() == "<=")) {
                throw Error(
                    "Unsupported operation '" + op.getName() + "' for bool" + " in line " + std::to_string(
                        op.getPos()));
            }
            stack.emplace_back("result", booll);
        } else {
            throw Error(
                "Unsupported operand types for binary operation: " + to_string(lhs.getType()) + " and " +
                to_string(rhs.getType()) + " in line " + std::to_string(op.getPos()));
        }
    } else if (lhs.getType() == string && rhs.getType() == identifier && chc_->getType(rhs.getName()) == string) {
        if (op.getName() == "+") {
            stack.emplace_back("result", string);
        } else if (op.getName() == "==") {
            stack.emplace_back("result", booll);
        } else {
            throw Error(
                "Unsupported operation '" + op.getName() + "' for boolean types" + " in line " + std::to_string(
                    op.getPos()));
        }
    } else if (lhs.getType() == booll && rhs.getType() == booll) {
        if (op.getName() == "&&" || op.getName() == "||") {
            stack.emplace_back("result", booll);
        } else if (op.getName() == "==" || op.getName() == "!=") {
            stack.emplace_back("result", booll);
        } else {
            throw Error(
                "Unsupported operation '" + op.getName() + "' for boolean types" + " in line " + std::to_string(
                    op.getPos()));
        }
    } else {
        throw Error(
            "Unsupported operands: " + to_string(lhs.getType()) + " and " + to_string(rhs.getType()) + " in line " +
            std::to_string(op.getPos()));
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
            throw Error(
                "Unsupported operation '" + op.getName() + "' for boolean type" + " in line " + std::to_string(
                    op.getPos()));
        }
        stack.emplace_back("result", booll);
    } else if (rhs_type == identifier) {
        auto rhst = chc_->getType(rhs.getName());
        if (rhst == booll) {
            if (op.getName() == "not") {
                stack.emplace_back("result", booll);
            } else {
                throw Error(
                    "Unsupported operation '" + op.getName() + "' for boolean type" + " in line " + std::to_string(
                        op.getPos()));
            }
        } else if (rhst == intt || rhst == floatt) {
            if (op.getName() == "-" || op.getName() == "+" || op.getName() == "++" || op.getName() == "--") {
                stack.emplace_back(rhs);
            } else {
                throw Error(
                    "Unsupported operation '" + op.getName() + "' for numeric type" + " in line " + std::to_string(
                        op.getPos()));
            }
        } else {
            throw Error(
                "Unsupported operation '" + op.getName() + "' for type: " + to_string(rhst) + " in line " +
                std::to_string(op.getPos()));
        }
    } else {
        throw Error(
            "Wrong type " + rhs.getName() + " for " + op.getName() + " operation in line " +
            std::to_string(op.getPos()));
    }
}

void semstack::checkBool() {
    if (stack.back().getType() == identifier) {
        if (chc_->getType(stack.back().getName()) != booll) {
            throw Error("Expected boolean expression in line " + std::to_string(stack.back().getPos()));
        }
    } else if (stack.back().getType() != booll) {
        throw Error("Expected boolean expression in line " + std::to_string(stack.back().getPos()));
    }
    stack.pop_back();
}

Lexeme semstack::back() {
    return stack.back();
}

void semstack::pop() {
    stack.pop_back();
}

void semstack::clear() {
    stack.clear();
}
