#ifndef COMPILATOR_BINARYEXPRAST_H
#define COMPILATOR_BINARYEXPRAST_H

#include "ExprAST.h"
#include <memory>
#include <iostream>
using namespace std;

class BinaryExprAST : public ExprAST {
private:
    char Op;
    unique_ptr<ExprAST> LHS, RHS;

public:
    BinaryExprAST(char op, unique_ptr<ExprAST> lhs, unique_ptr<ExprAST> rhs)
        : Op(op), LHS(move(lhs)), RHS(move(rhs)) {}

    void print(int level) override {
        printLevel(level);
        cout << "Operation: " << Op << endl;
        LHS.get()->print(level + 1);
        RHS.get()->print(level + 1);
    }

    IdentifierType getType(unique_ptr<bool> &fatalError) override {
        IdentifierType typeLHS = LHS.get()->getType(fatalError);;
        IdentifierType typeRHS = RHS.get()->getType(fatalError);;

        if (typeLHS != typeRHS) {
            cout << "Ошибка: нельзя производить операции над разными типами данных" << endl;
            return UND;
        }

        return typeLHS;
    }

    bool isBinary() override {
        return true;
    }

    int getLength(unique_ptr<bool> &fatalError) override {
        if (LHS.get()->getType(fatalError) == STR && RHS.get()->getType(fatalError) == STR) {
            return LHS.get()->getLength(fatalError) + LHS.get()->getLength(fatalError);
        }

        if (LHS.get()->getType(fatalError) == NUM && RHS.get()->getType(fatalError) == NUM) {
            return 1;
        }

        //array
    }

    void codegen(ofstream &out, Table table) override {
        LHS.get()->codegen(out, table);
        RHS.get()->codegen(out, table);

        switch (Op) {
            case '+': {
                out << '\t' << "popl " << "%eax" << endl;
                out << '\t' << "addl " << "%eax, " << "(%esp)" << endl;
            }
        }
    }
};


#endif
