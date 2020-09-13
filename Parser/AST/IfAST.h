#ifndef COMPILERJS_IFAST_H
#define COMPILERJS_IFAST_H

#include <memory>
#include <iostream>
#include "ExprAST.h"
#include "BodyAST.h"

using namespace std;

class IfAST: public ExprAST {
private:
    unique_ptr<ExprAST> Condition;
    unique_ptr<ExprAST> Body;

public:
    IfAST(unique_ptr<ExprAST> condition, unique_ptr<ExprAST> body)
        : Condition(move(condition)), Body(move(body)) {}
    void print() override {

    }
};


#endif
