#include <iostream>
#include "NumberExpression.h"
#include "stdlib.h"
#include "../Lexer/Token.h"
#include "../Lexer/Lexer.h"

#ifndef COMPILATOR_PARSER_H
#define COMPILATOR_PARSER_H

using namespace std;

class Parser {
private:
    Lexer lexer;
public:
    Parser(Lexer lexer): lexer(lexer) {}
    void parse(bool *fatalError);
    void idSemantics(Token token, bool **fatalError);
    void parseTopExpression(Token token, bool ***fatalError);
};

#endif
