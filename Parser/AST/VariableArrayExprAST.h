#ifndef COMPILERJS_VARIABLEARRAYEXPRAST_H
#define COMPILERJS_VARIABLEARRAYEXPRAST_H

#include "ExprAST.h"
#include "VariableExprAST.h"
#include "NumberExprAST.h"

class VariableArrayExprAST: public ExprAST {
private:
    unique_ptr<ExprAST> Variable;
    unique_ptr<ExprAST> Index;
public:
    VariableArrayExprAST(unique_ptr<ExprAST> variable, unique_ptr<ExprAST> index)
        : Variable(move(variable)), Index(move(index)) {}

    void print(int level) override {
        printLevel(level);
        cout << "CallArray: " << endl;

        if (Variable.get())
            Variable.get()->print(level + 1);

        if (Index.get())
            Index.get()->print(level + 1);
    }
};


#endif
