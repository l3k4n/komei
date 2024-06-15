#ifndef TOKENS_H
#define TOKENS_H

#include <string>
class Token {
public:
    enum class Kind {
        // clang-format off
        Unknown = 0,
	Comment, EndOfFile,

        Plus, Minus, Asterisk, Slash,
	Equal, EqualEqual, Bang, BangEqual,
	LessThan, GreaterThan, LessThanOrEqual, GreaterThanOrEqual,
        Semicolon, Colon, Comma, Dot,
        ParenLeft, ParenRight, BraceLeft, BraceRight,

        If, Else, Return, For,
        Identifier, Number, String,
        // clang-format on
    };

    Token(Token::Kind kind);
    Token(Token::Kind kind, char literal);
    Token(Token::Kind kind, std::string&& literal);

    const Kind kind() const;
    const std::string& literal() const;

private:
    const Kind m_kind;
    const std::string m_literal;
};

#endif
