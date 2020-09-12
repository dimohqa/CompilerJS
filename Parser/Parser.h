#ifndef COMPILATOR_PARSER_H
#define COMPILATOR_PARSER_H

#include <iostream>
#include <memory>
#include "stdlib.h"
#include "../Lexer/Token.h"
#include "../Lexer/Lexer.h"

using namespace std;

class Parser {
private:
    Lexer lexer;
public:
    Parser(Lexer lexer): lexer(lexer) {}
    void parse(unique_ptr<bool> &fatalError);
    void parseVariable(unique_ptr<bool> &fatalError);
    void parseTopExpression(Token token, unique_ptr<bool> &fatalError);
    void parseUnary(Token token, bool ****fatalError);
};

#endif
