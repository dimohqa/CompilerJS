#include "Parser.h"
#include <memory>

bool isId(TokenType type) {
    if (type != NUMBER && type != STRING &&
        type != HEX_NUMBER && type != REAL_NUMBER &&
        type != OCT_NUMBER && type != ID) {
        return false;
    }
    return true;
}

void Parser::parseUnary(Token token, bool ****fatalError) {
    Token nextToken = lexer.getNextToken();
    if (token.row + 1 == nextToken.row && nextToken.type == NUMBER) {
        
    }
}

void printError(string error, Token token) {
    cout << error << endl << '[' << token.col << ',' << token.row << "]: " << token.lexeme << endl;
}

void Parser::parseTopExpression(Token token, bool ***fatalError) {
    Token temp_token = token;
    switch (temp_token.type) {
        case PLUS:
        case MINUS: {
            temp_token = lexer.getNextToken();
            if (temp_token.type == MINUS || temp_token.type == PLUS)
                parseTopExpression(temp_token);
            if (temp_token.type != ID && temp_token.type != OCT_NUMBER &&
                temp_token.type != HEX_NUMBER && temp_token.type != REAL_NUMBER) {
                printError("Нераспознанный идентификатор", temp_token);
                ***fatalError = true;
                break;
            }

            Token nextToken = lexer.getNextToken();
            if (nextToken.col == temp_token.col || temp_token.type == SEMICOLON) {
                printError("Укажите ';' или передвиньте каретку на новую строку: ", temp_token);
                ***fatalError = true;
            }
            break;
        }
        case NUMBER:
            break;
    }
}

void Parser::parse(bool *fatalError) {
    Token temp_token = lexer.getNextToken();

    switch (temp_token.type) {
        case KW_VAR:
        case KW_CONST:
            idSemantics(temp_token, &fatalError);
        default:
            break;
    }

    return;
}

void Parser::idSemantics(Token token, bool **fatalError) {
    Token temp_token = lexer.getNextToken();

    if (temp_token.type != ID) {
        **fatalError = true;
        printError("Ошибка: некорректное имя переменной: ", temp_token);
    }

    temp_token = lexer.getNextToken();
    switch (temp_token.type) {
        case EQUAL:
            temp_token = lexer.getNextToken();

            switch (temp_token.type) {
                case NUMBER:
                case STRING:
                case HEX_NUMBER:
                case REAL_NUMBER:
                case OCT_NUMBER:
                case ID:
                    break;
                case LBRACE: {
                    bool first = true;
                    while (true) {
                        temp_token = lexer.getNextToken();

                        if (first && temp_token.type == COMMA) {
                            **fatalError = true;
                            printError("Ошибка: массив не может начинаться с: ", temp_token);
                            break;
                        }
                        first = false;

                        if (temp_token.type == COMMA)
                            continue;

                        if (temp_token.type == RBRACE)
                            break;

                        parseTopExpression(temp_token, &fatalError);
                    }
                    break;
                }
                default:
                    **fatalError = true;
                    printError("В массиве не может быть такого значения: ", temp_token);

            }
            break;
        case SEMICOLON:
            break;
        default:
            break;
    }
}