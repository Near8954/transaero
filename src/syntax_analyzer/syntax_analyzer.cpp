//
// Created by Роман Балдин on 12.11.2024.
//
#include "syntax_analyzer.h"

Syntax_analyzer::Syntax_analyzer() {
    analyzer_.get_lexemes();
    lex_ = analyzer_.get_lexeme();
}

inline void Syntax_analyzer::program() {


    if (lex_.getName() == "main") {
        lex_ = analyzer_.get_lexeme();
        main();
    }

}

inline void Syntax_analyzer::global_definition() {

}

inline void Syntax_analyzer::main() {
    if (lex_.getName() == "{") {
        lex_ = analyzer_.get_lexeme();
        block();

    } else {
        throw lex_;
    }

}

inline void Syntax_analyzer::function_definition() {
}

inline void Syntax_analyzer::type() {
}

inline void Syntax_analyzer::func_name() {
}

inline void Syntax_analyzer::name() {
}

inline void Syntax_analyzer::letter() {
}

inline void Syntax_analyzer::digit() {
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