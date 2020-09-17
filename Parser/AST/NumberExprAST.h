#ifndef COMPILATOR_NUMBEREXPRAST_H
#define COMPILATOR_NUMBEREXPRAST_H

#include <iostream>
#include "ExprAST.h"

using namespace std;

class NumberExprAST : public ExprAST {
private:
    double Value;

public:
    NumberExprAST(double value) : Value(value) {}
    void print(int level) override {
        printLevel(level);
        cout << "Number: " << Value << endl;
    }
    IdentifierType getType(unique_ptr<bool> &fatalError) override {
        return NUM;
    }
};


#endif
