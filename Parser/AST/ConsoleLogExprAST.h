#ifndef COMPILERJS_CONSOLELOGEXPRAST_H
#define COMPILERJS_CONSOLELOGEXPRAST_H

#include "ExprAST.h"

class ConsoleLogExprAST: public ExprAST  {
private:
    unique_ptr<ExprAST> Arg;
public:
    ConsoleLogExprAST(unique_ptr<ExprAST> arg): Arg(move(arg)) {}
    void print(int level) {
        printLevel(level);
        cout << "Arg = ";
        Arg.get()->print(level);
        cout << endl;
    }
};


#endif
