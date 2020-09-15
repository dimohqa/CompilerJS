#ifndef COMPILATOR_CALLEXPRAST_H
#define COMPILATOR_CALLEXPRAST_H

#include "ExprAST.h"
#include <string>
#include <vector>

using namespace std;

class CallExprAST : public ExprAST {
private:
    string Callee;
    vector<unique_ptr<ExprAST>> Args;

public:
    CallExprAST(const string &callee, vector<unique_ptr<ExprAST>> args)
        : Callee(callee), Args(move(args)) {}
    void print(int level) override {
        printLevel(level);
        cout << "Call: " << Callee << endl;
    }
};


#endif
