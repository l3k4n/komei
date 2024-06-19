#include "src/expression/expression.h"

#include <string>

#include "src/expression/visitor.h"

using Expr::Binary;
using Expr::BoolLiteral;
using Expr::NumberLiteral;
using Expr::StringLiteral;
using Expr::Unary;

StringLiteral::StringLiteral(std::string val) : m_value(val) {}

NumberLiteral::NumberLiteral(int val) : m_value(val) {}

BoolLiteral::BoolLiteral(bool val) : m_value(val) {}

Unary::Unary(Token op, Expr *right) : m_operator(op), m_right(right) {}

Binary::Binary(Expr *left, Token op, Expr *right) : m_left(left), m_operator(op), m_right(right) {}

void StringLiteral::accept(Visitor &v) { v.visitStringLiteral(*this); }

void NumberLiteral::accept(Visitor &v) { v.visitNumberLiteral(*this); }

void BoolLiteral::accept(Visitor &v) { v.visitBoolLiteral(*this); }

void Unary::accept(Visitor &v) { v.visitUnary(*this); }

void Binary::accept(Visitor &v) { v.visitBinary(*this); }
