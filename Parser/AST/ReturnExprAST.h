#ifndef COMPILERJS_RETURNEXPRAST_H
#define COMPILERJS_RETURNEXPRAST_H

#include <iostream>
#include <memory>
#include "ExprAST.h"

using namespace std;

class ReturnExprAST: public ExprAST {
private:
    unique_ptr<ExprAST> ReturnValue;

public:
    ReturnExprAST(unique_ptr<ExprAST> returnValue)
        : ReturnValue(move(returnValue)) {}
};


#endif
