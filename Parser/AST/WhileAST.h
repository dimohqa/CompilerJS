#ifndef COMPILERJS_WHILEAST_H
#define COMPILERJS_WHILEAST_H

#include "ExprAST.h"

class WhileAST: public ExprAST {
private:
    unique_ptr<ExprAST> Condition;
    unique_ptr<ExprAST> Body;

public:
    WhileAST(unique_ptr<ExprAST> condition, unique_ptr<ExprAST> body)
        : Condition(move(condition)), Body(move(body))  {}
    void print(int level) override {
        printLevel(level);
        cout << "While" << endl;

        if (Condition.get())
            printLevel(level + 1);
            cout << "Condition:" << endl;
            Condition.get()->print(level + 2);
        if (Body.get())
            Body.get()->print(level + 1);
    }

    void table(Table &table, int level, unique_ptr<bool> &fatalError) override {
        if (Body.get()) {
            Body.get()->table(table, level, fatalError);
        }
    }

    void codegen(ofstream &out, Table table) override {
        metks["loopStart"]++;
        out << '\t' << "jmp check" << metks["check"] << endl;
        out << "loopStart" << metks["loopStart"] << ":" << endl;
        Body->codegen(out, table);
        out << "check" << metks["check"] << ":" << endl;
        metks["check"]++;
        Condition->codegenWhile(out, table);
    }
};


#endif
