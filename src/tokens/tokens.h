#include <string>

#ifndef TOKENS_H
#define TOKENS_H

#define IGNORE_TOKEN_KIND(name, string)

#define TOKEN_KIND_LIST(T, K) \
    T(Add, "+")               \
    T(Mul, "*")               \
    T(Div, "/")               \
    T(Rem, "%")               \
    T(Sub, "-")               \
    T(Not, "!")               \
                              \
    T(Eq, "==")               \
    T(NotEq, "!=")            \
    T(LessThan, "<")          \
    T(LessThanEq, "<=")       \
    T(GreaterThan, ">")       \
    T(GreaterThanEq, ">=")    \
    T(And, "&&")              \
    T(Or, "||")               \
                              \
    T(ParenLeft, "(")         \
    T(ParenRight, ")")        \
    T(BraceLeft, "{")         \
    T(BraceRight, "}")        \
                              \
    T(Dot, ".")               \
    T(Comma, ",")             \
    T(Semicolon, ";")         \
    T(Colon, ":")             \
    T(Assign, "=")            \
                              \
    K(If, "if")               \
    K(Else, "else")           \
    K(Return, "return")       \
    K(For, "for")             \
    K(Fn, "fn")               \
                              \
    K(True, "true")           \
    K(False, "false")         \
    T(Number, nullptr)        \
    T(String, nullptr)        \
                              \
    T(Identifier, nullptr)    \
    T(Comment, nullptr)       \
    T(EndOfFile, nullptr)     \
    T(Illegal, nullptr)

class Token {
public:
#define T(name, string) name,
    enum class Kind { TOKEN_KIND_LIST(T, T) };
#undef T

    Token(Token::Kind kind);
    Token(Token::Kind kind, char literal);
    Token(Token::Kind kind, std::string literal);

    const Kind kind() const;
    const std::string& literal() const;

private:
    const Kind m_kind;
    const std::string m_literal;
};

#endif
