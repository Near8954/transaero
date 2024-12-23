//
// Created by Роман Балдин on 12.11.2024.
//
#include "syntax_analyzer.h"

checker *chc = new checker();

Syntax_analyzer::Syntax_analyzer() {
    analyzer_.get_lexemes();
    semstack_.set_checker(chc);
    get_lex();
    program();
}

bool isType(Lexeme &lex) {
    std::string name = lex.getName();
    if (name == "int" || name == "array" || name == "bool" ||
        name == "float" || name == "char" || name == "void" || name == "string") {
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

Lexeme Syntax_analyzer::prev_lex() {
    return analyzer_.prev_lexeme();
}

lexemeType func_type;

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
    func_type = from_string(lex_.getName());
    lexemeType type = from_string(lex_.getName());
    get_lex();
    name();
    std::string name = lex_.getName();
    lex_.setType(func_call);
    get_lex();
    if (lex_.getName() != "(") {
        throw lex_;
    }
    get_lex();

    chc->createScope();

    std::vector<lexemeType> args = parameter_list();
    get_lex();
    if (lex_.getName() != ")") {
        throw lex_;
    }
    get_lex();
    if (lex_.getName() != "{") {
        throw lex_;
    }
    get_lex();

    table_.push(name, type, args);

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

std::vector<lexemeType> Syntax_analyzer::parameter_list() {
    std::vector<lexemeType> args;
    if (lex_.getName() != "empty") {
        args.push_back(parameter());
        while (peek().getName() == ",") {
            get_lex();
            get_lex();
            args.push_back(parameter());
        }
    }
    return args;
}

lexemeType Syntax_analyzer::parameter() {
    type();
    Lexeme lex = lex_;
    get_lex();
    name();
    chc->pushId(from_string(prev_lex().getName()), lex_.getName());
    return from_string(lex.getName());
}

void Syntax_analyzer::block() {
    chc->createScope();
    expression_list();
    chc->exitScope();
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
        if (semstack_.back().getType() != func_type) {
            throw Error("Return type mismatch");
        }
        semstack_.pop();
        func_type = other;
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
    semstack_.checkBool();
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
        semstack_.push(lex_);
        get_lex();
        assignment_operator();
        semstack_.checkBin();
    }
}

void Syntax_analyzer::assignment_operator() {
    logical_or_expression();
    while (peek().getName() == "=") {
        get_lex();
        semstack_.push(lex_);
        get_lex();
        logical_or_expression();
        semstack_.checkBin();
    }
}

void Syntax_analyzer::logical_or_expression() {
    logical_and_expression();
    while (peek().getName() == "or" || peek().getName() == "||") {
        get_lex();
        semstack_.push(lex_);
        get_lex();
        logical_and_expression();
        semstack_.checkBin();
    }
}

void Syntax_analyzer::logical_and_expression() {
    relational_expression();
    while (peek().getName() == "and" || peek().getName() == "&&") {
        get_lex();
        semstack_.push(lex_);
        get_lex();
        relational_expression();
        semstack_.checkBin();
    }
}

void Syntax_analyzer::relational_expression() {
    additive_expression();
    while (peek().getName() == "==" || peek().getName() == "!=" ||
           peek().getName() == "<" || peek().getName() == ">" ||
           peek().getName() == "<=" || peek().getName() == ">=") {
        get_lex();
        semstack_.push(lex_);
        get_lex();
        additive_expression();
        semstack_.checkBin();
    }
}

void Syntax_analyzer::additive_expression() {
    multiplicative_expression();
    while (peek().getName() == "+" || peek().getName() == "-") {
        get_lex();
        semstack_.push(lex_);
        get_lex();
        multiplicative_expression();
        semstack_.checkBin();
    }
}

void Syntax_analyzer::multiplicative_expression() {
    unary_expression();
    while (peek().getName() == "*" || peek().getName() == "/") {
        get_lex();
        semstack_.push(lex_);
        get_lex();
        unary_expression();
        semstack_.checkBin();
    }
}

void Syntax_analyzer::unary_expression() {
    if (lex_.getName() == "+" || lex_.getName() == "-" ||
        (lex_.getName() == "++" && peek().getType() == identifier || peek().getName() == "++" || peek().getName() ==
                                                                                                 "--") ||
        lex_.getName() == "--" && (peek().getType() == identifier || peek().getName() == "++" || peek().
                getName() ==
                                                                                                 "--") ||
        lex_.getName() == "not") {
        semstack_.push(lex_);
        get_lex();
        unary_expression();
        semstack_.checkUno();
    } else {
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
        } else {
            semstack_.push(lex_);
        }
    } else if (lex_.getType() == string) {
        Lexeme lex("string", string);
        semstack_.push(lex);
    } else if (lex_.getName() == "true" || lex_.getName() == "false") {
        Lexeme lex("bool", booll);
        semstack_.push(lex);
    } else if (lex_.getType() == intt) {
        Lexeme lex("intt", intt);
        semstack_.push(lex);
    } else if (lex_.getType() == floatt) {
        Lexeme lex("floatt", floatt);
        semstack_.push(lex);
    } else if (lex_.getType() == lexemeType::literal) {
        Lexeme lex("literal", lexemeType::literal);
        semstack_.push(lex);
    } else {
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

void Syntax_analyzer::initialization(bool f) {
    if (lex_.getType() == identifier && f) {
        semstack_.push(lex_);
        get_lex();
        if (lex_.getType() != assignmentOperators) {
            throw lex_;
        }
        semstack_.push(Lexeme("=", assignmentOperators));
        expression();
        semstack_.checkBin();
    } else {
        type();
        if (lex_.getName() == "array" && f) {
            get_lex();
            if (lex_.getType() != identifier) {
                throw lex_;
            }
            chc->pushId(array, lex_.getName());
            get_lex();
            if (lex_.getName() != "[") {
                throw lex_;
            }
            get_lex();
            if (lex_.getType() != intt) {
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
            lexemeType tmp = other;
            std::string tmp_name = lex_.getName();
            int pos = lex_.getPos();
            if (prev_lex().getName() == "int") {
                tmp = intt;
                // chc->pushId(intt, lex_.getName());
            } else if (prev_lex().getName() == "float") {
                tmp = floatt;
                // chc->pushId(floatt, lex_.getName());
            } else if (prev_lex().getName() == "string") {
                tmp = string;
                // chc->pushId(string, lex_.getName());
            } else if (prev_lex().getName() == "bool") {
                tmp = booll;
                // chc->pushId(booll, lex_.getName());
            } else if (prev_lex().getName() == "char") {
                tmp = charr;
                // chc->pushId(charr, lex_.getName());
            }
            semstack_.push(lex_);
            get_lex();
            if (lex_.getName() != "=") {
                throw lex_;
            }
            semstack_.push(Lexeme("=", assignmentOperators, pos));
            get_lex();
            expression();
            chc->pushId(tmp, tmp_name);
            semstack_.checkBin();
            semstack_.clear();
        }
    }
}

void Syntax_analyzer::if_conditional_statement() {
    if (lex_.getName() != "(") {
        throw lex_;
    }
    get_lex();
    expression();
    semstack_.checkBool();
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
    if (lex_.getType() != identifier && lex_.getType() != lexemeType::literal && lex_.getType() != intt && lex_.
            getType() != floatt && lex_.getType() != charr || lex_.getType() != string) {
        throw lex_;
    }
    lexemeType type;
    if (lex_.getType() == identifier) {
        type = chc->getType(lex_.getName());
    } else {
        type = lex_.getType();
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
    case_block(type);
    get_lex();
    while (lex_.getName() == "case") {
        get_lex();
        case_block(type);
        get_lex();
    }
}

void Syntax_analyzer::case_block(lexemeType type) {
    if (lex_.getName() != "(") {
        throw lex_;
    }
    get_lex();
    expression();
    if (semstack_.back().getType() != type) {
        throw Error("Wrong type in case block");
    }
    semstack_.pop();
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

void Syntax_analyzer::for_operator() {
    if (lex_.getName() != "(") {
        throw lex_;
    }
    get_lex();
    chc->createScope();
    initialization(false);
    semstack_.clear();
    get_lex();
    if (lex_.getName() != ";") {
        throw lex_;
    }
    get_lex();
    expression();
    semstack_.checkBool();
    get_lex();
    if (lex_.getName() != ";") {
        throw lex_;
    }
    get_lex();
    expression();
    semstack_.clear();
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
    Lexeme prev = prev_lex();
    if (lex_.getName() != "(") {
        throw lex_;
    }
    get_lex();
    auto args = function_args();
    get_lex();
    if (lex_.getName() != ")") {
        throw lex_;
    }
    semstack_.push({"result", table_.getType(prev.getName(), args)});
}

std::vector<lexemeType> Syntax_analyzer::function_args() {
    if (lex_.getName() == "empty") {
        return {};
    }
    std::vector<lexemeType> args;
    while (peek().getName() != ")") {
        assignment_operator();
        auto lex = semstack_.back();
        if (lex_.getType() == identifier) {
            args.push_back(chc->getType(lex.getName()));
        } else {
            args.push_back(lex.getType());
        }
        semstack_.pop();
        get_lex();
        if (lex_.getType() != comma) {
            throw lex_;
        }
        get_lex();
    }
    assignment_operator();
    auto lex = semstack_.back();
    if (lex_.getType() == identifier) {
        args.push_back(chc->getType(lex.getName()));
    } else {
        args.push_back(lex.getType());
    }
    semstack_.pop();
    return args;
}
