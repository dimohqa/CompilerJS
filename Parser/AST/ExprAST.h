#ifndef COMPILATOR_EXPRAST_H
#define COMPILATOR_EXPRAST_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "../../Table/Table.h"

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

    virtual void print(int level) {};

    virtual void table(Table &table, int level, unique_ptr<bool> &fatalError) {}

    virtual Table createTable(unique_ptr<bool> &fatalError) {}

    virtual IdentifierType getType(unique_ptr<bool> &fatalError) {
        return UND;
    }
    virtual int getLength(unique_ptr<bool> &fatalError) {}
};


#endif
