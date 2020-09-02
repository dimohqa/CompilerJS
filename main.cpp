#include <iostream>
#include <gtest/gtest.h>
#include "Lexer/Lexer.h"

int main() {
    string filepath = "/home/nitro/university/CompilerJS/js/min.js";
    Lexer lexer(filepath);

    while (true) {
        Token token = lexer.getNextToken();
        token.print();
    }
    return 0;
}
