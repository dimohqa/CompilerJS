#ifndef COMPILERJS_CONSOLELOGEXPRAST_H
#define COMPILERJS_CONSOLELOGEXPRAST_H

#include "ExprAST.h"

class ConsoleLogExprAST: public ExprAST  {
private:
    unique_ptr<ExprAST> Arg;
public:
    ConsoleLogExprAST(unique_ptr<ExprAST> arg): Arg(move(arg)) {}
    void print(int level) {

        printLevel(level);
        cout << "Console.log: " << endl;

        printLevel(level + 1);
        cout << "Arg:" << endl;

        Arg.get()->print(level + 2);
    }
    void codegen(ofstream &out, Table table) {
        if (Arg.get()->getNameClass() == "Variable") {
            auto id = table.table.find(Arg.get()->getName());
            if (id->second.getType() == NUM) {
                out << '\t' << "pushl ";
                out << Arg.get()->getName() << endl;
                out << '\t' << "pushl $printf_format" << endl;
                out << '\t' << "call printf" << endl;
            }
            if (id->second.getType() == STR) {
                out << '\t' << "pushl $" << id->first << endl;
                out << '\t' << "pushl $printfStringFormat" << endl;
                out << '\t' << "call printf" << endl;
            }
        }
        if (Arg.get()->isBinary()) {
            Arg.get()->codegen(out, table);
            out << '\t' << "pushl $printf_format" << endl;
            out << '\t' << "call printf" << endl;
        }
        if (Arg.get()->getNameClass() == "Number") {
            Arg.get()->codegen(out, table);
            out << '\t' << "pushl $printf_format" << endl;
            out << '\t' << "call printf" << endl;
        }
        if (Arg.get()->getNameClass() == "String") {
            Arg.get()->codegen(out, table);
        }
    }
};


#endif
