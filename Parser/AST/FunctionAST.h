#ifndef COMPILERJS_FUNCTIONAST_H
#define COMPILERJS_FUNCTIONAST_H

#include "PrototypeAST.h"
#include "ExprAST.h"
#include "ArrayExprAST.h"
#include "BodyAST.h"
#include <memory>

using namespace std;

class FunctionAST {
private:
    unique_ptr<PrototypeAST> Proto;
    unique_ptr<BodyAST> Body;

public:
    FunctionAST(unique_ptr<PrototypeAST> proto, unique_ptr<BodyAST> body)
        : Proto(move(proto)), Body(move(body)) {}
    unique_ptr<BodyAST> getBody() {
        return move(Body);
    }
    //vector<unique_ptr<ExprAST>> getBody() {
    //    return Body->get();
    //}
};


#endif
