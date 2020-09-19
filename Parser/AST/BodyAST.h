#ifndef COMPILERJS_BODYAST_H
#define COMPILERJS_BODYAST_H

#include <iostream>
#include <memory>
#include <vector>
#include "ExprAST.h"

using namespace std;

class BodyAST: public ExprAST {
private:
    vector<unique_ptr<ExprAST>> Child;

public:
    BodyAST() {}
    void push(unique_ptr<ExprAST> child) {
        Child.push_back(move(child));
    }
    void print(int level) override {
        printLevel(level);
        cout << "Body" << endl;
        for (int i = 0; i < Child.size(); ++i) {
            Child[i].get()->print(level + 1);
        }
    }

    void table(Table &table, int level, unique_ptr<bool> &fatalError) override {
        for (int i = 0; i < Child.size(); i++) {
            Child[i].get()->table(table, level + 1, fatalError);
        }
    }

    void codegen(ofstream &out, Table table) override {
        for (int i = 0; i < Child.size(); i++) {
            Child[i].get()->codegen(out, table);
        }
    }
};


#endif
