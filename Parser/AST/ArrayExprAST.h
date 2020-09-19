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
    void print(int level) override {
        printLevel(level);
        cout << "Array: " << endl;
        for (int i = 0; i < Elements.size(); i++) {
            Elements[i].get()->print(level + 1);
        }
    }

    IdentifierType getType(unique_ptr<bool> &fatalError) override {
        return ARR;
    }

    int getLength(unique_ptr<bool> &fatalError) override {
        return Elements.size();
    }
};


#endif
