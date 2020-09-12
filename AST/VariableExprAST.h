#ifndef COMPILATOR_VARIABLEEXPRAST_H
#define COMPILATOR_VARIABLEEXPRAST_H

#include "ExprAST.h"
#include <string>

using namespace std;

class VariableExprAST : public ExprAST {
private:
    string Name;

public:
    VariableExprAST(const string &name) : Name(name) {}
};


#endif
