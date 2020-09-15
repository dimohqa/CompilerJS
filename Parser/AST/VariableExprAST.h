#ifndef COMPILATOR_VARIABLEEXPRAST_H
#define COMPILATOR_VARIABLEEXPRAST_H

#include "ExprAST.h"
#include "../../Lexer/Token.h"
#include <memory>
#include <string>

using namespace std;

class VariableExprAST : public ExprAST {
private:
    string Name;
    TokenType Type;
    unique_ptr<ExprAST> Expr;
public:
    VariableExprAST(const string &name, const TokenType &type, unique_ptr<ExprAST> expr) : Name(name), Type(type), Expr(move(expr)) {}
    void setExpr(unique_ptr<ExprAST> expr) {
        Expr = move(expr);
    }
    ExprAST* get() override {
        return Expr.get();
    }
    void print(int level) override {
        printLevel(level);
        cout << "Variable name: " << Name << endl;
        if (Expr.get())
            Expr.get()->print(level + 1);
    }
};


#endif
