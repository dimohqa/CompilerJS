#include <iostream>
#include <memory>
#include <ctype.h>
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

int main() {
    string filepath = "/home/nitro/university/CompilerJS/js/main.js";
    ifstream file = ifstream(filepath);
    Lexer lexer(file);

    BinopPrecedence['<'] = 10;
    BinopPrecedence['+'] = 20;
    BinopPrecedence['-'] = 20;
    BinopPrecedence['*'] = 40;

    /*while (true) {
        Token token = lexer.getNextToken();
        token.print();

        if (token.type == E0F) {
            break;
        }
    }*/
    Parser parser(lexer);

    unique_ptr<bool> fatalError(new bool(false));

    parser.parse(fatalError);

    if (*fatalError) {
        cout << "Fix error plz" << endl;
        return 0;
    }

    return 0;
}
