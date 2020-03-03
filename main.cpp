#include <iostream>
#include "Lexer.h"

int main() {
    string filepath = "/home/dima/compilator/js/nod.js";
    Lexer lex;
    lex.getNextToken(filepath);
    return 0;
}
