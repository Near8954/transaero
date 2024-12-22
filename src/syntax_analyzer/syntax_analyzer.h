//
// Created by Роман Балдин on 12.11.2024.
//

#ifndef SYNTAX_ANALYZER_H
#define SYNTAX_ANALYZER_H
#include <string>
#include "../lexical_analyzer/lexical_analyzer.h"
#include "../semstack/semstack.h"
#include "../function_table/function_table.h"
#include "iostream"
#include "vector"
class Syntax_analyzer {
public:
    Syntax_analyzer();

private:

    Lexical_analyzer analyzer_;

    semstack semstack_;

    function_table table_;

    Lexeme lex_;

    int curr_lex = 0;

    Lexeme peek();

    void get_lex();

    Lexeme prev_lex();

    void program();

    void main();

    void function_definition();

    void type();

    void name();

    std::vector<lexemeType> parameter_list();

    lexemeType parameter();

    void block();

    void expression_list();

    void expression();

    void output_operator();

    void assignment_operator();

    void simple_expression();

    void comma_expression();

    void logical_or_expression();

    void logical_and_expression();

    void relational_expression();

    void additive_expression();

    void multiplicative_expression();

    void unary_expression();

    void primary_expression();

    void array_access();

    void literal();

    void function_call();

    std::vector<lexemeType> function_args();

    void while_operator();

    void for_operator();

    void initialization();

    void if_conditional_statement();

    void switch_conditional_statement();

    void case_block();

    void all_operators();

};


#endif //SYNTAX_ANALYZER_H
