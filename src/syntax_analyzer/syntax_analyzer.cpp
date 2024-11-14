//
// Created by Роман Балдин on 12.11.2024.
//
#include "syntax_analyzer.h"

Syntax_analyzer::Syntax_analyzer() {
    analyzer_.get_lexemes();
    get_lex();
    program();
}

bool isType(Lexeme& lex) {
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
        throw lex_;
    }
}

void Syntax_analyzer::global_definition() {

}

void Syntax_analyzer::main() {
    if (lex_.getName() == "{") {
        get_lex();
        block();
        get_lex();
        if (lex_.getName() != "}") {
            throw lex_;
        }
    } else {
        throw lex_;
    }
}

void Syntax_analyzer::function_definition() {
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

void Syntax_analyzer::type() {
    if (!isType(lex_)) {
        throw lex_;
    }
}

void Syntax_analyzer::func_name() {
    name();
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
        get_lex();
    }
}

void Syntax_analyzer::block() {
    expression_list();
}

void Syntax_analyzer::expression_list() {
    bool hui = false;
    while (peek().getName() != "}") {
        if (hui) get_lex();
        all_operators();
        if (peek().getName() == "," || peek().getName() == ";") {
            get_lex();
            hui = true;
//            get_lex();
//            if (peek().getName() != "}") {
//                throw lex_;
//            }
        } else if (peek().getName() != "}") {
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

    } else {
        expression();
    }
}

void Syntax_analyzer::expression() {
    if (lex_.getType() == identifier) {
        if (peek().getName() == "(") {
            get_lex();
            get_lex();
            function_call();
            get_lex();
            if (lex_.getName() != ")") {
                throw lex_;
            }
        } else if (peek().getName() == "[") {
            get_lex();
            get_lex();
            array_access();
        } else {
//            get_lex();
            name();
        }
//        get_lex();
//        ass_func();
    } else if (lex_.getName() == "(") {
        get_lex();
        get_lex();
        expression();
        get_lex();
        if (lex_.getName() != ")") {
            throw lex_;
        }
    } else if (lex_.getType() == lexemeType::literal) {
//        get_lex();
        simple_expression();
    } else if (isType(lex_)) {
//        get_lex();
        initialization();
    }
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
    element_list();
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
    get_lex();
    if (lex_.getName() != "}") {
        throw lex_;
    }
}

void Syntax_analyzer::simple_expression() {
    logical_or_expression();
}


void Syntax_analyzer::comma_expression() {
    logical_or_expression();
    get_lex();
    while (lex_.getName() == ",") {
        get_lex();
        logical_or_expression();
        get_lex();
    }
}


void Syntax_analyzer::logical_or_expression() {
    logical_and_expression();
//    get_lex();
    while (peek().getName() == "or") {
        get_lex();
        logical_and_expression();
        get_lex();
    }
}

void Syntax_analyzer::logical_and_expression() {
    relational_expression();
//    get_lex();
    while (peek().getName() == "and") {
        get_lex();
        relational_expression();
        get_lex();
    }
}

void Syntax_analyzer::relational_expression() {
    additive_expression();
//    get_lex();
    while (peek().getName() == "==" || peek().getName() == "!=" || peek().getName() == "<" || peek().getName() == ">" ||
           peek().getName() == "<=" || peek().getName() == ">=") {
        get_lex();
        additive_expression();
        get_lex();
    }
}

void Syntax_analyzer::additive_expression() {
    multiplicative_expression();
//    get_lex();
    while (peek().getName() == "+" || peek().getName() == "-") {
        get_lex();
        multiplicative_expression();
        get_lex();
    }
}

void Syntax_analyzer::multiplicative_expression() {
    unary_expression();
//    get_lex();
    while (peek().getName() == "*" || peek().getName() == "/") {
        get_lex();
        unary_expression();
        get_lex();
    }
}

void Syntax_analyzer::unary_expression() {
    primary_expression();
//    get_lex();
    while (peek().getName() == "++" || peek().getName() == "--") {
        get_lex();
        primary_expression();
        get_lex();
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
//        get_lex(); // need peek
        if (peek().getName() == "[") {
            array_access();
        } else if (peek().getName() == "(") {
            ass_func();
        }
    } else if (lex_.getType() != lexemeType::literal) {
        throw lex_;
    }
}

void Syntax_analyzer::array_access() {
}

void Syntax_analyzer::special_expression() {
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
    } else {
        type();
        get_lex();
        if (lex_.getType() != identifier) {
            throw lex_;
        }
        get_lex();
        if (lex_.getName() != "=") {
            throw lex_;
        }
        get_lex();
    }
    expression();
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
    get_lex();
    if (lex_.getName() != "}") {
        throw lex_;
    }

    if (peek().getName() == "else") {
        get_lex();
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
}

void Syntax_analyzer::switch_conditional_statement() {
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
    get_lex();
    if (lex_.getName() != "}") {
        throw lex_;
    }
}

void Syntax_analyzer::case_block() {
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
    get_lex();
    if (lex_.getName() != "}") {
        throw lex_;
    }
}


void Syntax_analyzer::element_list() {
    literal();
    while (peek().getName() == ",") {
        get_lex();
        get_lex();
        literal();
    }
}

void Syntax_analyzer::expression_operator() {
    if (lex_.getName() == "print") {
        get_lex();
        output_operator();

    } else if (lex_.getName() == "return") {
        get_lex();
        expression();
    } else if (lex_.getName() == "while") {
        get_lex();
        while_operator();
    } else if (lex_.getName() == "for") {
        get_lex();
        for_operator();
    } else if (lex_.getName() == "switch") {
        get_lex();
        switch_conditional_statement();
    } else if (lex_.getName() == "if") {
        get_lex();
        if_conditional_statement();
    }
}

void Syntax_analyzer::function_call() {
    if (lex_.getName() != "(") {
        throw lex_;
    }
    get_lex();
    parameter_list();
    get_lex();
    if (lex_.getName() != ")") {
        throw lex_;
    }
}

void Syntax_analyzer::relation_operations() {

}

void Syntax_analyzer::assignment_operator() {

}
