#include "src/parser/parser.h"

#include <string>

#include "src/expression/expression.h"

Parser::Parser(Lexer &lexer) : m_lexer(lexer) {}

Expr::Expr *Parser::parse() { return literal(); }

Expr::Expr *Parser::literal() {
    Token token = m_lexer.read();

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
