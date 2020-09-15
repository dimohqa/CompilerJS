#ifndef COMPILATOR_EXPRAST_H
#define COMPILATOR_EXPRAST_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class ExprAST {
public:
    virtual ~ExprAST() {}
    virtual ExprAST* get() {
        return nullptr;
    }
    virtual void setExpr(unique_ptr<ExprAST> expr) {
        cout << "prov" << endl;
    }
    void printLevel(int level) {
        for (int i = 0; i < level; i++) {
            cout << ' ';
        }
    }
    virtual void print(int level) {
        cout << "Base class" << std::endl;
    };
};


#endif
