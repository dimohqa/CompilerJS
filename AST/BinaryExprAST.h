#ifndef COMPILATOR_BINARYEXPRAST_H
#define COMPILATOR_BINARYEXPRAST_H

#include "ExprAST.h"
#include <memory>

using namespace std;

class BinaryExprAST : public ExprAST {
private:
    char Op;
    unique_ptr<ExprAST> LHS, RHS;

public:
    BinaryExprAST(char op, unique_ptr<ExprAST> lhs, unique_ptr<ExprAST> rhs)
        : Op(op), LHS(move(lhs)), RHS(move(rhs)) {}
};


#endif
