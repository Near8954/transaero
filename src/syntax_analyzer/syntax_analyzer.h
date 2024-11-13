//
// Created by Роман Балдин on 12.11.2024.
//

#ifndef SYNTAX_ANALYZER_H
#define SYNTAX_ANALYZER_H
#include <string>
#include "../lexical_analyzer/lexical_analyzer.h"

class Syntax_analyzer {
public:
    Syntax_analyzer();

private:

    Lexical_analyzer analyzer_;

    Lexeme lex_;

    int curr_lex = 0;

    void get_lex();

    void program();

    void global_definition();

    void main();

    void function_definition();

    void type();

    void func_name();

    void name();

    void ass_func();

    void parameter_list();

    void parameter();

    void block();

    void expression_list();

    void expression();

    void output_operator();

    void element_list();

    void assignment();

    void assignment_operator();

    void relation_operations();

    void simple_expression();

    void logical_or_expression();

    void logical_and_expression();

    void relational_expression();

    void additive_expression();

    void multiplicative_expression();

    void unary_expression();

    void primary_expression();

    void array_access();

    void special_expression();

    void lexeme();

    void string_literal();

    void character();

    void special_character();

    void number_literal();

    void function_call();

    void argument_list();

    void while_operator();

    void for_operator();

    void initialization();

    void if_conditional_statement();

    void switch_conditional_statement();

    void case_block();

};


#endif //SYNTAX_ANALYZER_H
