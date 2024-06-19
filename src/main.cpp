#include <cstdio>
#include <fstream>
#include <iostream>

#include "src/expression/expression.h"
#include "src/expression/visitor.h"
#include "src/lexer/lexer.h"
#include "src/parser/parser.h"

class ExprPrinter : public Visitor {
public:
    void visitStringLiteral(Expr::StringLiteral &expr) override {
        std::cout << "\"" << expr.m_value << "\"";
    }

    void visitNumberLiteral(Expr::NumberLiteral &expr) override { std::cout << expr.m_value; }

    void visitBoolLiteral(Expr::BoolLiteral &expr) override { std::cout << expr.m_value; }

    void visitUnary(Expr::Unary &expr) override { print(expr.m_right); }

    void visitBinary(Expr::Binary &expr) override {
        print(expr.m_left);
        print(expr.m_right);
    }

    void print(Expr::Expr *expr) { expr->accept(*this); }
};

int main() {
    std::ifstream fin("samples/expressions.komei");
    Lexer lexer(fin);
    Parser parser(lexer);

    ExprPrinter().print(parser.parse());
}
