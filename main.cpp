#include <iostream>
#include <gtest/gtest.h>
#include "Lexer/Lexer.h"

int main() {
    string filepath = "/home/nitro/university/CompilerJS/js/mi2n.js";
    Lexer lex;
    lex.getNextToken(filepath);
    return 0;
}
