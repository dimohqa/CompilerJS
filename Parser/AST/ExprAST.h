#ifndef COMPILATOR_EXPRAST_H
#define COMPILATOR_EXPRAST_H

#include <iostream>

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
