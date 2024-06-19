#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>

#include "src/tokens/tokens.h"

class Visitor;

namespace Expr {

class Expr {
public:
    virtual void accept(Visitor &v) = 0;
};

class StringLiteral : public Expr {
public:
    std::string m_value;

    StringLiteral(std::string value);
    void accept(Visitor &v);
};

class NumberLiteral : public Expr {
public:
    int m_value;

    NumberLiteral(int value);
    void accept(Visitor &v);
};

class BoolLiteral : public Expr {
public:
    bool m_value;

    BoolLiteral(bool value);
    void accept(Visitor &v);
};

class Unary : public Expr {
public:
    Token m_operator;
    Expr *m_right;

    Unary(Token op, Expr *right);
    void accept(Visitor &v) override;
};

class Binary : public Expr {
public:
    Token m_operator;
    Expr *m_right;
    Expr *m_left;

    Binary(Expr *left, Token operatior, Expr *right);
    void accept(Visitor &v) override;
};

}  // namespace Expr

#endif
