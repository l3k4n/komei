#include "src/parser/parser.h"

#include <string>

#include "src/expression/expression.h"

Parser::Parser(Lexer &lexer) : m_lexer(lexer) {}

Expr::Expr *Parser::parse() { return factor(); }

Expr::Expr *Parser::literal() {
    Token token = m_lexer.next();

    switch (token.kind()) {
        case Token::Kind::Number:
            return new Expr::NumberLiteral(std::stoi(token.literal()));

        case Token::Kind::String:
            return new Expr::StringLiteral(token.literal());

        case Token::Kind::True:
            return new Expr::BoolLiteral(true);

        case Token::Kind::False:
            return new Expr::BoolLiteral(false);

        default:
            throw Parser::ParseError();
    }
}

Expr::Expr *Parser::unary() {
    Token token = m_lexer.peek();

    switch (token.kind()) {
        case Token::Kind::Not:
        case Token::Kind::Sub:
            return new Expr::Unary(m_lexer.next(), unary());

        default:
            return literal();
    }
}

Expr::Expr *Parser::factor() {
    auto left = unary();
    Token token = m_lexer.peek();

    switch (token.kind()) {
        case Token::Kind::Mul:
        case Token::Kind::Div:
            return new Expr::Binary(left, m_lexer.next(), unary());

        default:
            return left;
    }
}

Expr::Expr *Parser::term() {
    auto left = factor();
    Token token = m_lexer.peek();

    switch (token.kind()) {
        case Token::Kind::Add:
        case Token::Kind::Sub:
            return new Expr::Binary(left, m_lexer.next(), factor());

        default:
            return left;
    }
}

Expr::Expr *Parser::comparison() {
    auto left = term();
    Token token = m_lexer.peek();

    switch (token.kind()) {
        case Token::Kind::LessThan:
        case Token::Kind::LessThanEq:
        case Token::Kind::GreaterThan:
        case Token::Kind::GreaterThanEq:
            return new Expr::Binary(left, m_lexer.next(), term());

        default:
            return left;
    }
}

Expr::Expr *Parser::equality() {
    auto left = comparison();
    Token token = m_lexer.peek();

    switch (token.kind()) {
        case Token::Kind::NotEq:
        case Token::Kind::Eq:
            return new Expr::Binary(left, m_lexer.next(), comparison());

        default:
            return left;
    }
}
