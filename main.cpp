#include <iostream>
#include <gtest/gtest.h>
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

int main() {
    string filepath = "/home/nitro/university/CompilerJS/js/chisl.js";
    ifstream file = ifstream(filepath);
    Lexer lexer(file);

    bool fatalError = false;


    /*while (true) {
        Token token = lexer.getNextToken();
        token.print();

        if (token.type == E0F) {
            break;
        }
    }*/

    Parser parser(lexer);

    parser.parse(&fatalError);

    if (fatalError) {
        cout << "Fix error plz" << endl;
        return 0;
    }

    return 0;
}
