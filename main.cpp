#include <iostream>
#include <gtest/gtest.h>
#include "Lexer.h"

int main() {
    string filepath = "/home/dima/compilator/js/min.js";
    Lexer lex;
    lex.getNextToken(filepath);
    return 0;
}
