#ifndef PARSER_H
#define PARSER_H

#include "src/expression/expression.h"
#include "src/lexer/lexer.h"

class Parser {
    class ParseError {};

    Lexer& m_lexer;

    Expr::Expr* literal();
    Expr::Expr* unary();
    Expr::Expr* factor();

public:
    Parser(Lexer& lexer);
    Expr::Expr* parse();
};

#endif
