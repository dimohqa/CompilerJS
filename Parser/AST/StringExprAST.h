#ifndef COMPILERJS_STRINGEXPRAST_H
#define COMPILERJS_STRINGEXPRAST_H

#include "ExprAST.h"

class StringExprAST: public ExprAST {
private:
    string Value;

public:
    StringExprAST(string value): Value(value) {}

};


#endif
