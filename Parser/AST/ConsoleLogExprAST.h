#ifndef COMPILERJS_CONSOLELOGEXPRAST_H
#define COMPILERJS_CONSOLELOGEXPRAST_H

#include "ExprAST.h"

class ConsoleLogExprAST: public ExprAST  {
private:
    unique_ptr<ExprAST> Args;
public:
    ConsoleLogExprAST(unique_ptr<ExprAST> args): Args(move(args)) {}
};


#endif
