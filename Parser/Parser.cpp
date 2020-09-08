#include "Parser.h"
#include <memory>

void Parser::parse() {
    Token temp_token = lexer.getNextToken();

    temp_token.print();

    switch (temp_token.type) {
        case KW_VAR:
        case KW_CONST:
            idSemantics(temp_token);
    }

    return;
}

void Parser::idSemantics(Token token) {
    bool comma = false;
    Token temp_token = lexer.getNextToken();
    if (temp_token.type != ID) {
        printf("error 2");
    }
    temp_token = lexer.getNextToken();
    cout << TokenOfEnum(temp_token.type) << endl;
    switch (temp_token.type) {
        case EQUAL:
            temp_token = lexer.getNextToken();
            if (temp_token.type != NUMBER) {
                cout << TokenOfEnum(temp_token.type) << endl;
                printf("error 1");
            }
            break;
        case SEMICOLON:
            break;
    }
}