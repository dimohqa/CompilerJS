#ifndef COMPILATOR_TOKEN_H
#define COMPILATOR_TOKEN_H

#include <iostream>
#include <string>

using namespace std;

enum TokenType {
    KW_THIS, KW_NEW, KW_FUNCTION, KW_VAR, KW_FOR, KW_IF, KW_ELSE, KW_TRUE, KW_FALSE, KW_RETURN, KW_UNDEFINED, KW_NULL,
    KW_INSTANCEOF, KW_IN, KW_DO, KW_DEFAULT, KW_VOID, KW_WHILE, KW_BREAK, KW_CASE, KW_TYPEOF, KW_CONTINUE, KW_INFINITY, KW_NAN,
    KW_DELETE, KW_SWITCH, KW_TRY, KW_CATCH, KW_THROW, KW_FINALLY, KW_WITH, KW_DEBUGGER, KW_CONST, KW_LET,

    LBRACKET, RBRACKET, DOT, GEQT, PLUS, LSHIFT, NEGATION, EQUAL, GGEQT, SEMICOLON, DIVISION, EEQUAL, MINUS, RSHIFT, CEDILLA, PLUSEQ, DIVISIONEQ,
    GGGEQT, LPAREN, COMMA, NOTEQUAL, STAR, GGGT, AND, MINUSEQ, ANDEQ, RPAREN, LT, EEEQUAL, PERCENTAGE, BW_AND, OR, TIMESEQ, OREQ, LBRACE,
    GT, NOTEEQUAL, INCREMENT, BW_OR, QUESTION, PERCENTAGEEQUAL, EXPEQUAL, ESCAPE, DECREMENT, EXP, COLON, LLEQT, RBRACE, LEQT,

    ID, UNKNOWN, STRING, NUMBER, OCT_NUMBER, HEX_NUMBER, REAL_NUMBER, E0F
};

class Token {
public:
    TokenType type;
    string lexeme;
    int row;
    int col;

    Token() {}
    void set(string lex, int r, int c, TokenType typeToken);
    virtual void print();
};

#endif //COMPILATOR_TOKEN_H
