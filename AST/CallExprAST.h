#ifndef COMPILATOR_CALLEXPRAST_H
#define COMPILATOR_CALLEXPRAST_H

#include "ExprAST.h"
#include <string>
#include <vector>

using namespace std;

class CallExprAST : public ExprAST {
private:
    string Callee;
    vector<ExprAST *> Args;

public:
    CallExprAST(const string &callee, vector<ExprAST *> &args)
        : Callee(callee), Args(args) {}
};


#endif
