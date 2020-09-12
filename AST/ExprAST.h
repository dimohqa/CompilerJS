#ifndef COMPILATOR_EXPRAST_H
#define COMPILATOR_EXPRAST_H

#include <iostream>

class ExprAST {
public:
    virtual ~ExprAST() {}
    virtual void print() {
       std::cout << 'kek';
    };
};


#endif
