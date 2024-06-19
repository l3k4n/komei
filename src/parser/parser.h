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
    Expr::Expr* term();
    Expr::Expr* comparison();
    Expr::Expr* equality();

public:
    Parser(Lexer& lexer);
    Expr::Expr* parse();
};

#endif
