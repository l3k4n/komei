#ifndef VISITOR_H
#define VISITOR_H

#include "src/expression/expression.h"

class Visitor {
public:
    virtual void visitStringLiteral(Expr::StringLiteral &l) = 0;
    virtual void visitNumberLiteral(Expr::NumberLiteral &l) = 0;
    virtual void visitBoolLiteral(Expr::BoolLiteral &l) = 0;
    virtual void visitUnary(Expr::Unary &u) = 0;
    virtual void visitBinary(Expr::Binary &b) = 0;
};

#endif
