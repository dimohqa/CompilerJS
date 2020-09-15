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
        cout << "Console.log: " << endl;

        printLevel(level + 1);
        cout << "Arg:" << endl;

        Arg.get()->print(level + 2);
    }
};


#endif
