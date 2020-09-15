#include <iostream>
#include <memory>
#include <ctype.h>
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

int main() {
    string filepath = "/home/nitro/university/CompilerJS/js/main.js";
    ifstream file = ifstream(filepath);
    Lexer lexer(file);

    while (true) {
        Token token = lexer.getNextToken();
        token.print();

        if (token.type == E0F) {
            break;
        }
    }
    /*Parser parser(lexer);

    unique_ptr<bool> fatalError(new bool(false));

    unique_ptr<ExprAST> main = parser.parse(fatalError);
    cout << "TREE: " << endl;
    auto b = main.get();
    b->print();
    if (*fatalError) {
        cout << endl << "Fix error plz" << endl;
        return 0;
    }*/

    return 0;
}
