//
// Created by Роман Балдин on 12.11.2024.
//
#include "syntax_analyzer.h"

Syntax_analyzer::Syntax_analyzer() {
    analyzer_.get_lexemes();
    get_lex();
    program();
}

bool isType(Lexeme &lex) {
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


Lexeme Syntax_analyzer::peek() {
    return analyzer_.peek();
}


void Syntax_analyzer::program() {
    if (lex_.getName() == "main") {
        get_lex();
        main();
    } else {
        while (lex_.getName() != "main") {
            function_definition();
            get_lex();
        }
        get_lex();
        main();
    }
}

void Syntax_analyzer::main() {
    if (lex_.getName() == "{") {
        get_lex();
        block();
    } else {
        throw lex_;
    }
}

void Syntax_analyzer::function_definition() {
    if (lex_.getName() != "function") {
        throw lex_;
    }
    get_lex();
    type();
    get_lex();
    name();
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
}

void Syntax_analyzer::type() {
    if (!isType(lex_)) {
        throw lex_;
    }
}

void Syntax_analyzer::name() {
    if (lex_.getType() != identifier) {
        throw lex_;
    }
}

void Syntax_analyzer::parameter_list() {
    parameter();
    while (peek().getName() == ",") {
        get_lex();
        get_lex();
        parameter();
    }
}

void Syntax_analyzer::parameter() {
    if (lex_.getName() != "empty") {
        type();
        get_lex();
        name();
        //        get_lex();
    }
}

void Syntax_analyzer::block() {
    expression_list();
    get_lex();
    if (lex_.getName() != "}") {
        throw lex_;
    }
}

void Syntax_analyzer::expression_list() {
    all_operators();
    get_lex();
    if (lex_.getName() != ";") {
        throw lex_;
    }
    while (peek().getName() != "}") {
        get_lex();
        all_operators();
        get_lex();
        if (lex_.getName() != ";") {
            throw lex_;
        }
    }
}

void Syntax_analyzer::all_operators() {
    if (lex_.getName() == "for") {
        get_lex();
        for_operator();
    } else if (lex_.getName() == "while") {
        get_lex();
        while_operator();
    } else if (lex_.getName() == "if") {
        get_lex();
        if_conditional_statement();
    } else if (lex_.getName() == "switch") {
        get_lex();
        switch_conditional_statement();
    } else if (lex_.getName() == "return") {
        get_lex();
        expression();
    } else if (lex_.getName() == "print") {
        get_lex();
        output_operator();
    } else if (lex_.getName() == "break") {
        get_lex();
    } else if (lex_.getName() == "continue") {
        get_lex();
    } else if (lex_.getName() == "empty") {
    } else if (isType(lex_)) {
        initialization();
    } else {
        expression();
    }
}

void Syntax_analyzer::expression() {
    simple_expression();
}

void Syntax_analyzer::ass_func() {
    if (lex_.getName() == "(") {
        get_lex();
        argument_list();
        get_lex();
        if (lex_.getName() != ")") {
            throw lex_;
        }
    } else {
        assignment_operator();
        get_lex();
        expression();
    }
}

void Syntax_analyzer::output_operator() {
    if (lex_.getName() != "(") {
        throw lex_;
    }
    get_lex();
    function_args();
    get_lex();
    if (lex_.getName() != ")") {
        throw lex_;
    }
}

void Syntax_analyzer::while_operator() {
    if (lex_.getName() != "(") {
        throw lex_;
    }
    get_lex();
    expression();
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
}

void Syntax_analyzer::simple_expression() {
    comma_expression();
}


void Syntax_analyzer::comma_expression() {
    assignment_operator();
    while (peek().getName() == ",") {
        get_lex();
        get_lex();
        assignment_operator();
    }
}


void Syntax_analyzer::assignment_operator() {
    logical_or_expression();
    while (peek().getName() == "=") {
        get_lex();
        get_lex();
        logical_or_expression();
    }
}


void Syntax_analyzer::logical_or_expression() {
    logical_and_expression();
    while (peek().getName() == "or" || peek().getName() == "||") {
        get_lex();
        get_lex();
        logical_and_expression();
    }
}

void Syntax_analyzer::logical_and_expression() {
    relational_expression();
    while (peek().getName() == "and" || peek().getName() == "&&") {
        get_lex();
        get_lex();
        relational_expression();
    }
}

void Syntax_analyzer::relational_expression() {
    additive_expression();
    while (peek().getName() == "==" || peek().getName() == "!=" || peek().getName() == "<" || peek().getName() == ">" ||
           peek().getName() == "<=" || peek().getName() == ">=") {
        get_lex();
        get_lex();
        additive_expression();
    }
}

void Syntax_analyzer::additive_expression() {
    multiplicative_expression();
    while (peek().getName() == "+" || peek().getName() == "-") {
        get_lex();
        get_lex();
        multiplicative_expression();
    }
}

void Syntax_analyzer::multiplicative_expression() {
    unary_expression();
    while (peek().getName() == "*" || peek().getName() == "/") {
        get_lex();
        get_lex();
        unary_expression();
    }
}

void Syntax_analyzer::unary_expression() {
    primary_expression();
    while (peek().getName() == "++" || peek().getName() == "--") {
        get_lex();
        get_lex();
        primary_expression();
    }
}

void Syntax_analyzer::primary_expression() {
    if (lex_.getName() == "(") {
        get_lex();
        expression();
        get_lex();
        if (lex_.getName() != ")") {
            throw lex_;
        }
    } else if (lex_.getType() == identifier) {
        if (peek().getName() == "[") {
            get_lex();
            array_access();
        } else if (peek().getName() == "(") {
            get_lex();
            function_call();
        }
    } else if (lex_.getType() == string) {
//        get_lex();
    } else if (lex_.getType() != lexemeType::literal) {
        throw lex_;
    }
}

void Syntax_analyzer::array_access() {
    if (lex_.getName() != "[") {
        throw lex_;
    }
    get_lex();
    expression();
    get_lex();
    if (lex_.getName() != "]") {
        throw lex_;
    }
}

void Syntax_analyzer::literal() {
    if (lex_.getType() != lexemeType::literal) {
        throw lex_;
    }
}


void Syntax_analyzer::argument_list() {
}

void Syntax_analyzer::initialization() {
    if (lex_.getType() == identifier) {
        get_lex();
        if (lex_.getType() != assignmentOperators) {
            throw lex_;
        }
        expression();
    } else {
        type();
        if (lex_.getName() == "array") {
            get_lex();
            if (lex_.getType() != identifier) {
                throw lex_;
            }
            get_lex();
            if (lex_.getName() != "[") {
                throw lex_;
            }
            get_lex();
            if (lex_.getType() != identifier && lex_.getType() != lexemeType::literal) {
                throw lex_;
            }
            get_lex();
            if (lex_.getName() != "]") {
                throw lex_;
            }
        } else {
            get_lex();
            if (lex_.getType() != identifier) {
                throw lex_;
            }
            get_lex();
            if (lex_.getName() != "=") {
                throw lex_;
            }
            get_lex();
            expression();
        }
    }
}

void Syntax_analyzer::if_conditional_statement() {
    if (lex_.getName() != "(") {
        throw lex_;
    }
    get_lex();
    expression();
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

    if (peek().getName() == "else") {
        get_lex();
        get_lex();
        if (lex_.getName() != "{") {
            throw lex_;
        }
        get_lex();
        block();
    }
}

void Syntax_analyzer::switch_conditional_statement() {
    if (lex_.getName() != "(") {
        throw lex_;
    }
    get_lex();
    if (lex_.getType() != identifier && lex_.getType() != lexemeType::literal) {
        throw lex_;
    }
    get_lex();
    if (lex_.getName() != ")") {
        throw lex_;
    }
    get_lex();
    if (lex_.getName() != "{") {
        throw lex_;
    }
    get_lex();
    if (lex_.getName() != "case") {
        throw lex_;
    }
    get_lex();
    case_block();
    get_lex();
    while (lex_.getName() == "case") {
        get_lex();
        case_block();
        get_lex();
    }
}

void Syntax_analyzer::case_block() {
    if (lex_.getName() != "(") {
        throw lex_;
    }
    get_lex();
    simple_expression();
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
//    get_lex();
//    if (lex_.getName() != "}") {
//        throw lex_;
//    }
}

void Syntax_analyzer::for_operator() {
    if (lex_.getName() != "(") {
        throw lex_;
    }
    get_lex();
    expression();
    get_lex();
    if (lex_.getName() != ";") {
        throw lex_;
    }
    get_lex();
    expression();
    get_lex();
    if (lex_.getName() != ";") {
        throw lex_;
    }
    get_lex();
    expression();
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

}

void Syntax_analyzer::function_call() {
    if (lex_.getName() != "(") {
        throw lex_;
    }
    get_lex();
    function_args();
    get_lex();
    if (lex_.getName() != ")") {
        throw lex_;
    }
}

void Syntax_analyzer::function_args() {
    while (peek().getName() != ")") {
        if (lex_.getType() != lexemeType::literal && lex_.getType() != identifier && lex_.getName() != "empty") {
            throw lex_;
        }
        get_lex();
        if (lex_.getType() != comma) {
            throw lex_;
        }
        get_lex();
    }
}