#include "Token.h"
#include "../EnumSwitch/TokenTypeSwitch.h"

void Token::set(string lexemeToken, int rowToken, int columnToken, TokenType typeToken ) {
    lexeme = lexemeToken;
    row = rowToken;
    col = columnToken;
    type = typeToken;
}

void Token::print() {
    cout << "Loc=<" << row << ':' << col << ">\t" << TokenOfEnum(type) << " \'" << lexeme << '\'' << '\n';
}