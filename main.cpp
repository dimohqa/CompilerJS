#include <iostream>
#include <gtest/gtest.h>
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

int main() {
    string filepath = "/home/nitro/university/CompilerJS/js/chisl.js";
    ifstream file = ifstream(filepath);
    Lexer lexer(file);

    /*while (true) {
        Token token = lexer.getNextToken();
        token.print();

        if (token.type == E0F) {
            break;
        }
    }*/

    Parser parser(lexer);

    parser.parse();

    return 0;
}
