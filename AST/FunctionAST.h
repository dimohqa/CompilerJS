#ifndef COMPILERJS_FUNCTIONAST_H
#define COMPILERJS_FUNCTIONAST_H

#include "PrototypeAST.h"
#include "ExprAST.h"
#include <memory>

using namespace std;

class FunctionAST {
private:
    unique_ptr<PrototypeAST> Proto;
    unique_ptr<ExprAST> Body;

public:
    FunctionAST(unique_ptr<PrototypeAST> proto, unique_ptr<ExprAST> body)
        : Proto(move(proto)), Body(move(body)) {}
};


#endif
