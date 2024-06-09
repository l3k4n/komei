#include "src/lexer/lexer.h"

#include <fstream>
#include <string>
#include <utility>

#include "src/tokens/tokens.h"

#define char_fn static inline bool

char_fn is_alpha(unsigned char ch) { return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'); }
char_fn is_int(unsigned char ch) { return ch >= '0' && ch <= '9'; }
char_fn is_identifier_char(unsigned char ch) { return is_alpha(ch) || ch == '_' || is_int(ch); }
char_fn is_whitespace(unsigned char ch) {
    return ch == ' ' || ch == '\r' || ch == '\n' || ch == '\t';
}

Lexer::Lexer(std::ifstream &fin) : m_fin(fin) {}

Token Lexer::read() {
    unsigned char ch = m_fin.peek();

    if (is_whitespace(ch)) {
        consume_whitespace();
        return read();
    }

    switch (ch) {
        case ' ':
        case '\r':
        case '\t':
        case '\n':
            consume_whitespace();
            return read();
        case '(':
            return Token(Token::Kind::ParenLeft, m_fin.get());
        case ')':
            return Token(Token::Kind::ParenRight, m_fin.get());
        case '{':
            return Token(Token::Kind::BraceLeft, m_fin.get());
        case '}':
            return Token(Token::Kind::BraceRight, m_fin.get());
        case ';':
            return Token(Token::Kind::Semicolon, m_fin.get());
        case ':':
            return Token(Token::Kind::Colon, m_fin.get());
        case '=':
            return Token(Token::Kind::Equal, m_fin.get());
        case '+':
            return Token(Token::Kind::Plus, m_fin.get());
        case ',':
            return Token(Token::Kind::Comma, m_fin.get());
        case '"':
            return Token(Token::Kind::DoubleQuote, m_fin.get());
        default: {
            if (is_alpha(ch)) return read_identifier();
            if (is_int(ch)) return read_number();

            return Token(Token::Kind::Unknown, ch);
        }
    }
}

Token Lexer::read_identifier() {
    unsigned char ch = m_fin.peek();
    std::string str;

    while (!m_fin.eof() && is_identifier_char(ch)) {
        str.push_back(m_fin.get());
        ch = m_fin.peek();
    }

    return Token(Token::Kind::Identifier, std::move(str));
}

Token Lexer::read_number() {
    unsigned char ch = m_fin.peek();
    std::string str;

    while (!m_fin.eof() && is_int(ch)) {
        str.push_back(m_fin.get());
        ch = m_fin.peek();
    }

    return Token(Token::Kind::Number, std::move(str));
}

void Lexer::consume_whitespace() {
    while (!m_fin.eof() && is_whitespace(m_fin.peek())) m_fin.get();
}

bool Lexer::eof() { return m_fin.eof(); }
