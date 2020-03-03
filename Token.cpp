#include "Token.h"

Token* createToken(Token *tok, string Lexeme, TokenType type, int row, int col) {
    tok = new Token;
    tok->Lexeme = Lexeme;
    tok->type = type;
    tok->row = row;
    tok->col = col;

    return tok;
}

void printToken(Token *token) {
    cout << token->type << "\t" << token->Lexeme << "\n";
}