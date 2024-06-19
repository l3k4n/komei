#include "src/lexer/lexer.h"

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>

#include "src/tokens/tokens.h"

#define CHAR_UTIL(name) static inline bool name(unsigned char ch)

CHAR_UTIL(is_alpha) { return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'); }
CHAR_UTIL(is_int) { return ch >= '0' && ch <= '9'; }
CHAR_UTIL(is_identifier_char) { return is_alpha(ch) || ch == '_' || is_int(ch); }
CHAR_UTIL(is_whitespace) { return ch == ' ' || ch == '\r' || ch == '\n' || ch == '\t'; }

#define T(name, str_val) {str_val, Token::Kind::name},
std::map<std::string, Token::Kind> keywords = {TOKEN_KIND_LIST(IGNORE_TOKEN_KIND, T)};
#undef T

#define HANDLE_TRAILING_EQUAL(kind, kind_with_eq)         \
    {                                                     \
        std::string str;                                  \
        str.push_back(m_fin.get());                       \
        if (m_fin.peek() != '=') return Token(kind, str); \
        str.push_back(m_fin.get());                       \
        return Token(kind_with_eq, str);                  \
    }

Lexer::Lexer(std::ifstream &fin) : m_fin(fin), m_peeked(nullptr) {}

Token Lexer::read() {
    unsigned char ch = m_fin.peek();

    switch (ch) {
        case ' ':
        case '\r':
        case '\t':
        case '\n':
            consume_whitespace();
            return next();
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
        case '+':
            return Token(Token::Kind::Add, m_fin.get());
        case '-':
            return Token(Token::Kind::Sub, m_fin.get());
        case '*':
            return Token(Token::Kind::Mul, m_fin.get());
        case '/':
            return Token(Token::Kind::Div, m_fin.get());
        case ',':
            return Token(Token::Kind::Comma, m_fin.get());
        case '=':
            HANDLE_TRAILING_EQUAL(Token::Kind::Assign, Token::Kind::Eq)
        case '!':
            HANDLE_TRAILING_EQUAL(Token::Kind::Not, Token::Kind::NotEq)
        case '<':
            HANDLE_TRAILING_EQUAL(Token::Kind::LessThan, Token::Kind::LessThanEq)
        case '>':
            HANDLE_TRAILING_EQUAL(Token::Kind::GreaterThan, Token::Kind::GreaterThanEq)
        case '"':
            return scan_string();
        default: {
            if (is_alpha(ch)) return scan_identifier_or_keyword();
            if (is_int(ch)) return scan_number();

            return Token(Token::Kind::Illegal, ch);
        }
    }
}

Token &Lexer::peek() {
    if (m_peeked == nullptr) {
        auto tok = new Token(std::move(read()));
        m_peeked.reset(tok);
    }

    return *m_peeked;
}

Token Lexer::next() {
    if (m_peeked) {
        Token token = std::move(*m_peeked);
        m_peeked.reset();
        return token;
    };

    return read();
}

Token Lexer::scan_identifier_or_keyword() {
    unsigned char ch = m_fin.peek();
    std::string str;

    while (!m_fin.eof() && is_identifier_char(ch)) {
        str.push_back(m_fin.get());
        ch = m_fin.peek();
    }

    if (str.length() > 1) {
        auto found = keywords.find(str);
        if (found != keywords.end()) return Token(found->second, std::move(str));
    }

    return Token(Token::Kind::Identifier, std::move(str));
}

Token Lexer::scan_number() {
    unsigned char ch = m_fin.peek();
    std::string str;

    while (!m_fin.eof() && is_int(ch)) {
        str.push_back(m_fin.get());
        ch = m_fin.peek();
    }

    return Token(Token::Kind::Number, std::move(str));
}

Token Lexer::scan_string() {
    m_fin.get();  // consume initial quote

    unsigned char ch = m_fin.peek();
    std::string str;

    while (!m_fin.eof() && ch != '"' && ch != '\n') {
        str.push_back(m_fin.get());
        ch = m_fin.peek();
    }

    if (ch != '"') {
        std::cout << "unterminated string literal\n";
    }

    return Token(Token::Kind::String, std::move(str));
}

void Lexer::consume_whitespace() {
    while (!m_fin.eof() && is_whitespace(m_fin.peek())) m_fin.get();
}

bool Lexer::eof() { return m_fin.eof(); }
