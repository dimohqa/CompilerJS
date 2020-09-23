#ifndef COMPILATOR_VARIABLEEXPRAST_H
#define COMPILATOR_VARIABLEEXPRAST_H

#include "ExprAST.h"
#include "../../../EnumSwitch/TokenTypeSwitch.h"
#include "../../Lexer/Token.h"
#include <memory>
#include <string>
#include <map>

using namespace std;

class VariableExprAST : public ExprAST {
private:
    string Name;
    TokenType Type;
    unique_ptr<ExprAST> Expr;
public:
    VariableExprAST(const string &name, const TokenType &type, unique_ptr<ExprAST> expr) : Name(name), Type(type), Expr(move(expr)) {}
    void setExpr(unique_ptr<ExprAST> expr) {
        Expr = move(expr);
    }
    ExprAST* get() override {
        return Expr.get();
    }
    void print(int level) override {
        printLevel(level);
        cout << "Variable name: " << Name << endl;
        if (Expr.get())
            Expr.get()->print(level + 1);
    }

    string getName() override {
        return Name;
    }

    string getNameClass() override {
        return "Variable";
    }

    void table(Table &table, int level, unique_ptr<bool> &fatalError) override {
        if (Type == UNKNOWN) {
            return;
        }
        if (Type == KW_CONST && !Expr.get()) {
            cout << "Ошибка: const обязательно нужно инициализировать" << endl;
        }
        IdentifierType type = Expr.get() ? Expr.get()->getType(fatalError) : UND;
        bool binary = Expr.get()->isBinary();
        int length;
        if (type == STR || type == ARR)
            length = Expr.get()->getLength(fatalError);
        else
            length = 1;

        Identifier identifier(Name, level, Type == KW_CONST, type, length, binary);
        table.push(identifier);
    }

    void codegen(ofstream &out, Table table) override {
        auto id = table.table.find(Name);

        if (id != table.table.end()) {
            if (id->second.getType() == NUM) {
                if (!id->second.getBinary()) {
                    if (Type != UNKNOWN || id->second.getType() && Expr.get()) {
                        Expr.get()->codegen(out, table);
                        out << '\t' << "popl " << Name << endl;
                    } else {
                        out << '\t' << "pushl " << Name << endl;
                    }
                } else {
                    Expr.get()->codegen(out, table);
                    out << '\t' << "popl " << Name << endl;
                }
            }
            if (id->second.getType() == STR) {
                Expr.get()->codegenString(out, Name);
            }
        }
    }
};


#endif
