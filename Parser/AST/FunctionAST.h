#ifndef COMPILERJS_FUNCTIONAST_H
#define COMPILERJS_FUNCTIONAST_H

#include "PrototypeAST.h"
#include "ExprAST.h"
#include "ArrayExprAST.h"
#include "BodyAST.h"
#include <memory>

using namespace std;

class FunctionAST: public ExprAST {
private:
    unique_ptr<PrototypeAST> Proto;
    unique_ptr<BodyAST> Body;

public:
    FunctionAST(unique_ptr<PrototypeAST> proto, unique_ptr<BodyAST> body)
        : Proto(move(proto)), Body(move(body)) {}
    unique_ptr<BodyAST> getBody() {
        return move(Body);
    }
    void print(int level) {
        printLevel(level);
        cout << "Proto" << endl;
        Body.get()->print(level + 1);
    }
};


#endif
