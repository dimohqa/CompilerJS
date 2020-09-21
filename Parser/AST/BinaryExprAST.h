#ifndef COMPILATOR_BINARYEXPRAST_H
#define COMPILATOR_BINARYEXPRAST_H

#include "ExprAST.h"
#include <memory>
#include <iostream>
using namespace std;

class BinaryExprAST : public ExprAST {
private:
    string Op;
    unique_ptr<ExprAST> LHS, RHS;

public:
    BinaryExprAST(string op, unique_ptr<ExprAST> lhs, unique_ptr<ExprAST> rhs)
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

        /*if (typeLHS != typeRHS) {
            cout << "Ошибка: нельзя производить операции над разными типами данных" << endl;
            return UND;
        }*/

        return typeLHS < typeRHS ? typeLHS : typeRHS;
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

        if (Op == "+") {
            out << '\t' << "popl " << "%eax" << endl;
            out << '\t' << "addl " << "%eax, " << "(%esp)" << endl;
            return;
        }
        if (Op == "-") {
            out << '\t' << "popl " << "%ebx" << endl;
            out << '\t' << "popl " << "%eax" << endl;
            out << '\t' << "subl " << "%ebx, %eax" << endl;
            out << '\t' << "pushl " << "%eax" << endl;
            return;
        }
        if (Op == "*") {
            out << '\t' << "popl " << "%eax" << endl;
            out << '\t' << "popl " << "%ebx" << endl;
            out << '\t' << "imull " << "%ebx" << endl;
            out << '\t' << "pushl " << "%eax" << endl;
            return;
        }
        if (Op == "/") {
            out << '\t' << "popl " << "%ebx" << endl;
            out << '\t' << "popl " << "%eax" << endl;
            out << '\t' << "pushl %eax" << endl;
            out << '\t' << "movl $0, %edx" << endl;
            out << '\t' << "idivl " << "%ebx" << endl;
            out << '\t' << "pushl " << "%eax" << endl;
            return;
        }
        if (Op == "==") {
            out << '\t' << "popl " << "%eax" << endl;
            out << '\t' << "popl " << "%ebx" << endl;
            out << '\t' << "cmpl %eax, %ebx" << endl;
            out << '\t' << "je equal" << metks["equal"] << endl;
            out << "jmp next" << metks["next"] << endl;
            out << "equal" << metks["equal"] << ":" << endl;
            metks["equal"]++;
            return;
        }
        if (Op == "<") {
            out << '\t' << "popl " << "%eax" << endl;
            out << '\t' << "popl " << "%ebx" << endl;
            out << '\t' << "cmpl %eax, %ebx" << endl;
            out << '\t' << "jl less" << metks["less"] << endl;
            out << "jmp next" << metks["next"] << endl;
            out << "less" << metks["less"] << ":" << endl;
            metks["less"]++;
            return;
        }
        if (Op == ">") {
            out << '\t' << "popl " << "%eax" << endl;
            out << '\t' << "popl " << "%ebx" << endl;
            out << '\t' << "cmpl %eax, %ebx" << endl;
            out << '\t' << "jg greater" << metks["greater"] << endl;
            out << "jmp next" << metks["next"] << endl;
            out << "greater" << metks["greater"] << ":"  << endl;
            metks["greater"]++;
            return;
        }
        if (Op == "!=") {
            out << '\t' << "popl " << "%eax" << endl;
            out << '\t' << "popl " << "%ebx" << endl;
            out << '\t' << "cmpl %eax, %ebx" << endl;
            out << '\t' << "jne notEqual" << metks["notEqual"] << endl;
            out << "jmp next" << metks["next"] << endl;
            out << "notEqual" << metks["notEqual"] << ":"  << endl;
            metks["notEqual"]++;
            return;
        }
        if (Op == "<=") {
            out << '\t' << "popl " << "%eax" << endl;
            out << '\t' << "popl " << "%ebx" << endl;
            out << '\t' << "cmpl %eax, %ebx" << endl;
            out << '\t' << "jle lessEqual" << metks["lessEqual"] << endl;
            out << "jmp next" << metks["next"] << endl;
            out << "lessEqual" << metks["lessEqual"] << ":" << endl;
            metks["lessEqual"]++;
            return;
        }
        if (Op == ">=") {
            out << '\t' << "popl " << "%eax" << endl;
            out << '\t' << "popl " << "%ebx" << endl;
            out << '\t' << "cmpl %eax, %ebx" << endl;
            out << '\t' << "jge greaterEqual" << metks["greaterEqual"] << endl;
            out << "jmp next" << metks["next"] << endl;
            out << "greaterEqual" << metks["greaterEqual"] << ":"  << endl;
            metks["greaterEqual"]++;
            return;
        }
    }

    void codegenWhile(ofstream &out, Table table) override {
        LHS.get()->codegen(out, table);
        RHS.get()->codegen(out, table);

        if (Op == "+") {
            out << '\t' << "popl " << "%eax" << endl;
            out << '\t' << "addl " << "%eax, " << "(%esp)" << endl;
            return;
        }
        if (Op == "-") {
            out << '\t' << "popl " << "%ebx" << endl;
            out << '\t' << "popl " << "%eax" << endl;
            out << '\t' << "subl " << "%ebx, %eax" << endl;
            out << '\t' << "pushl " << "%eax" << endl;
            return;
        }
        if (Op == "*") {
            out << '\t' << "popl " << "%eax" << endl;
            out << '\t' << "popl " << "%ebx" << endl;
            out << '\t' << "imull " << "%ebx" << endl;
            out << '\t' << "pushl " << "%eax" << endl;
            return;
        }
        if (Op == "/") {
            out << '\t' << "popl " << "%ebx" << endl;
            out << '\t' << "popl " << "%eax" << endl;
            out << '\t' << "pushl %eax" << endl;
            out << '\t' << "movl $0, %edx" << endl;
            out << '\t' << "idivl " << "%ebx" << endl;
            out << '\t' << "pushl " << "%eax" << endl;
            return;
        }
        if (Op == "==") {
            out << '\t' << "popl " << "%eax" << endl;
            out << '\t' << "popl " << "%ebx" << endl;
            out << '\t' << "cmpl %eax, %ebx" << endl;
            out << '\t' << "je loopStart" << metks["loopStart"] << endl;
            metks["loopStart"]++;
            return;
        }
        if (Op == "<") {
            out << '\t' << "popl " << "%eax" << endl;
            out << '\t' << "popl " << "%ebx" << endl;
            out << '\t' << "cmpl %eax, %ebx" << endl;
            out << '\t' << "jl loopStart" << metks["loopStart"] << endl;
            metks["loopStart"]++;
            return;
        }
        if (Op == ">") {
            out << '\t' << "popl " << "%eax" << endl;
            out << '\t' << "popl " << "%ebx" << endl;
            out << '\t' << "cmpl %eax, %ebx" << endl;
            out << '\t' << "jg loopStart" << metks["loopStart"] << endl;
            metks["loopStart"]++;
            return;
        }
        if (Op == "!=") {
            out << '\t' << "popl " << "%eax" << endl;
            out << '\t' << "popl " << "%ebx" << endl;
            out << '\t' << "cmpl %eax, %ebx" << endl;
            out << '\t' << "jne loopStart" << metks["loopStart"] << endl;
            metks["loopStart"]++;
            return;
        }
        if (Op == "<=") {
            out << '\t' << "popl " << "%eax" << endl;
            out << '\t' << "popl " << "%ebx" << endl;
            out << '\t' << "cmpl %eax, %ebx" << endl;
            out << '\t' << "jle loopStart" << metks["loopStart"] << endl;
            metks["loopStart"]++;
            return;
        }
        if (Op == ">=") {
            out << '\t' << "popl " << "%eax" << endl;
            out << '\t' << "popl " << "%ebx" << endl;
            out << '\t' << "cmpl %eax, %ebx" << endl;
            out << '\t' << "jge loopStart" << metks["loopStart"] << endl;
            metks["loopStart"]++;
            return;
        }
    }
};


#endif
