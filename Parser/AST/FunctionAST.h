#ifndef COMPILERJS_FUNCTIONAST_H
#define COMPILERJS_FUNCTIONAST_H

#include "PrototypeAST.h"
#include "ExprAST.h"
#include "ArrayExprAST.h"
#include "BodyAST.h"
#include <memory>

using namespace std;

class FunctionAST: public ExprAST {
private:
    unique_ptr<PrototypeAST> Proto;
    unique_ptr<BodyAST> Body;

public:
    FunctionAST(unique_ptr<PrototypeAST> proto, unique_ptr<BodyAST> body)
        : Proto(move(proto)), Body(move(body)) {}
    unique_ptr<BodyAST> getBody() {
        return move(Body);
    }
    void print(int level) {
        //printLevel(level);
        //cout << "Proto" << endl;
        Proto.get()->print(level + 1);
        Body.get()->print(level + 1);
    }

    Table createTable(unique_ptr<bool> &fatalError) override {
        Table table;
        if (Body.get())
            Body.get()->table(table, 0, fatalError);

        return table;
    }

    void codegenInit(Table table) override {
        ofstream out("../codegen.s");
        for (auto id = table.table.begin(); id != table.table.end(); id++) {
            out << ".bss" << endl;
            out << id->first << ":" << endl;
            out << '\t' << ".space " << id->second.getSizeByte() << endl;
        }
        out << ".data" << endl;
        out << "printf_format:" << endl;
        out << '\t' << ".string \"%d\\n\"" << endl;
        out << "printfStringFormat:" << endl;
        out << '\t' << ".string \"%s\\n\"" << endl;
        out << "printfCharFormat:" << endl;
        out << '\t' << ".string \"%c\"" << endl;
        out << ".text" << endl;
        out << ".globl main" << endl;
        out << ".type main, @function" << endl;
        out << endl << "main:" << endl;
        out << '\t' << "pushl %ebp" << endl;
        out << '\t' << "movl %esp, %ebp" << endl << endl;

        if (Body.get())
            Body.get()->codegen(out, table);

        out << endl << '\t' << "movl $0, %eax" << endl;
        out << '\t' << "leave" << endl;
        out << '\t' << "ret" << endl;
    }
};


#endif
