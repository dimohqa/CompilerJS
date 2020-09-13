#ifndef COMPILERJS_BODYAST_H
#define COMPILERJS_BODYAST_H

#include <iostream>
#include <memory>
#include <vector>
#include "ExprAST.h"

using namespace std;

class BodyAST {
private:
    vector<unique_ptr<ExprAST>> Child;

public:
    BodyAST() {}
    void push(unique_ptr<ExprAST> child) {
        Child.push_back(move(child));
    }
    void print() {
        for (int i = 0; i < Child.size(); ++i) {
            Child[i].get()->print();
            cout << '\t';
            Child[i]->get()->print();
        }
    }
};


#endif
