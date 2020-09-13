#ifndef COMPILERJS_ARRAYAST_H
#define COMPILERJS_ARRAYAST_H

#include <iostream>
#include <memory>
#include <vector>
#include "ExprAST.h"

using namespace std;

class ArrayExprAST: public ExprAST {
private:
    vector<unique_ptr<ExprAST>> Elements;

public:
    ArrayExprAST() {
    }
    void pushExpression(unique_ptr<ExprAST> element);
    void print() override {
        cout << "array, size = " << Elements.size() << endl;
        for (int i = 0; i < Elements.size(); i++) {
            Elements[i].get()->print();
        }
        cout << endl;
    }
};


#endif
