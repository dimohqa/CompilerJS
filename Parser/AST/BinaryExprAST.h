#ifndef COMPILATOR_BINARYEXPRAST_H
#define COMPILATOR_BINARYEXPRAST_H

#include "ExprAST.h"
#include <memory>
#include <iostream>
using namespace std;

class BinaryExprAST : public ExprAST {
private:
    char Op;
    unique_ptr<ExprAST> LHS, RHS;

public:
    BinaryExprAST(char op, unique_ptr<ExprAST> lhs, unique_ptr<ExprAST> rhs)
        : Op(op), LHS(move(lhs)), RHS(move(rhs)) {}
    void print(int level) override {
        printLevel(level);
        cout << "Operation: " << Op << endl;
        LHS.get()->print(level + 1);
        RHS.get()->print(level + 1);
        cout << endl;
    }
};


#endif
