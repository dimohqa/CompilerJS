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
    virtual void print() {
        std::cout << "lel" << std::endl;
    };
};


#endif
