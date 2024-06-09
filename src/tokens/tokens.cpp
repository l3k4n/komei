#include "src/tokens/tokens.h"

#include <string>

Token::Token(Token::Kind kind) : m_kind(kind) {}

Token::Token(Token::Kind kind, std::string&& literal)
    : m_kind(kind), m_literal(std::move(literal)) {}

Token::Token(Token::Kind kind, char literal) : m_kind(kind), m_literal(1, literal) {}

const Token::Kind Token::kind() const { return m_kind; }

const std::string& Token::literal() const { return m_literal; }
