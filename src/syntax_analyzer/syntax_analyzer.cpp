//
// Created by Роман Балдин on 12.11.2024.
//
#include "syntax_analyzer.h"

Syntax_analyzer::Syntax_analyzer() {
    analyzer_.get_lexemes();
    get_lex();
}

bool isType(Lexeme lex) {
    std::string name = lex.getName();
    if (name == "int" || name == "float" || name == "array" || name == "bool" || name == "float" || name == "char" ||
        name == "void") {
        return true;
    }
    return false;
}

void Syntax_analyzer::get_lex() {
    lex_ = analyzer_.get_lexeme();
}

inline void Syntax_analyzer::program() {
    if (lex_.getName() == "main") {
        get_lex();
        main();
    }
}

inline void Syntax_analyzer::global_definition() {
}

inline void Syntax_analyzer::main() {
    if (lex_.getName() == "{") {
        get_lex();
        block();
        get_lex();
        if (lex_.getName() != "{") {
            throw lex_;
        }
    } else {
        throw lex_;
    }
}

inline void Syntax_analyzer::function_definition() {
    get_lex();
    type();
    get_lex();
    func_name();
    get_lex();
    if (lex_.getName() != "(") {
        throw lex_;
    }
    get_lex();
    parameter_list();
    get_lex();
    if (lex_.getName() != ")") {
        throw lex_;
    }
    get_lex();
    if (lex_.getName() != "{") {
        throw lex_;
    }
    get_lex();
    block();
    get_lex();
    if (lex_.getName() != "}") {
        throw lex_;
    }
}

inline void Syntax_analyzer::type() {
    if (!isType(lex_)) {
        throw lex_;
    }
}

inline void Syntax_analyzer::func_name() {
    name();
}

inline void Syntax_analyzer::name() {
    if (lex_.getType() != identifier) {
        throw lex_;
    }
}

inline void Syntax_analyzer::parameter_list() {
}

inline void Syntax_analyzer::parameter() {
}

inline void Syntax_analyzer::block() {
}

inline void Syntax_analyzer::expression_list() {
}

inline void Syntax_analyzer::expression() {
}

inline void Syntax_analyzer::output_operator() {
}

inline void Syntax_analyzer::element_list() {
}

inline void Syntax_analyzer::assignment() {
}

inline void Syntax_analyzer::assignment_operator() {
}

inline void Syntax_analyzer::relation_operations() {
}

inline void Syntax_analyzer::simple_expression() {
}

inline void Syntax_analyzer::logical_or_expression() {
}

inline void Syntax_analyzer::logical_and_expression() {
}

inline void Syntax_analyzer::relational_expression() {
}

inline void Syntax_analyzer::additive_expression() {
}

inline void Syntax_analyzer::multiplicative_expression() {
}

inline void Syntax_analyzer::unary_expression() {
}

inline void Syntax_analyzer::primary_expression() {
}

inline void Syntax_analyzer::array_access() {
}

inline void Syntax_analyzer::special_expression() {
}

inline void Syntax_analyzer::lexeme() {
}

inline void Syntax_analyzer::string_literal() {
}

inline void Syntax_analyzer::character() {
}

inline void Syntax_analyzer::special_character() {
}

inline void Syntax_analyzer::number_literal() {
}

inline void Syntax_analyzer::function_call() {
}

inline void Syntax_analyzer::argument_list() {
}

inline void Syntax_analyzer::loop_operator() {
}

inline void Syntax_analyzer::initialization() {
}

inline void Syntax_analyzer::conditional_statement() {
}

inline void Syntax_analyzer::case_block() {
}
