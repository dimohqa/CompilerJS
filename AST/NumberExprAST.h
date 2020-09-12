#ifndef COMPILATOR_NUMBEREXPRAST_H
#define COMPILATOR_NUMBEREXPRAST_H

#include "ExprAST.h"


class NumberExprAST : public ExprAST {
private:
    double Value;

public:
    NumberExprAST(double value) : Value(value) {}
};


#endif
