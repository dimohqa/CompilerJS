#include <iostream>
#include <memory>
#include <string.h>
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

int main(int argc, char *argv[]) {
    if (argc < 1) {
        cout << "Вы ввели невалидное количество аргументов!" << endl;
        return 0;
    }

    if (argc == 3) {
        string filepath = argv[2];
        ifstream file = ifstream(filepath);

        if (strcmp(argv[1], "--dump-tokens") == 0) {
            Lexer lexer(file);

            while (true) {
                Token token = lexer.getNextToken();
                token.print();

                if (token.type == E0F) {
                    break;
                }
            }
            return 0;
        }

        if (strcmp(argv[1], "--dump-ast") == 0) {
            Lexer lexer(file);

            Parser parser(lexer);

            unique_ptr<bool> fatalError(new bool(false));

            unique_ptr<ExprAST> main = parser.parse(fatalError);
            cout << "TREE: " << endl;
            main.get()->print(0);
        }

        if (strcmp(argv[1], "--dump-asm") == 0) {
            Lexer lexer(file);

            Parser parser(lexer);

            unique_ptr<bool> fatalError(new bool(false));

            unique_ptr<ExprAST> main = parser.parse(fatalError);

            auto table = main.get()->createTable(fatalError);

            if (*fatalError) {
                cout << endl << "Fix error plz" << endl;
                return 0;
            }

            main.get()->codegenInit(table);

            ifstream codegen("../codegen.s");
            while (codegen) {
                string strInput;
                getline(codegen, strInput);
                cout << strInput << endl;
            }
            codegen.close();
        }
    }

    if (argc == 2) {
        string filepath = argv[1];
        ifstream file = ifstream(filepath);

        Lexer lexer(file);

        Parser parser(lexer);

        unique_ptr<bool> fatalError(new bool(false));

        unique_ptr<ExprAST> main = parser.parse(fatalError);
        cout << "TREE: " << endl;
        main.get()->print(0);

        cout << "TABLE: " << endl;

        auto table = main.get()->createTable(fatalError);
        table.print();

        if (*fatalError) {
            cout << endl << "Fix error plz" << endl;
            return 0;
        }

        main.get()->codegenInit(table);
        cout << "RUN:" << endl;
        system("gcc -no-pie -g ../codegen.s -m32 -o ../codegen");
        system("../codegen");
    }

    return 0;
}
