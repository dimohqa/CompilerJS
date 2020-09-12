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

void printError(string error, Token token) {
    cout << error << endl
         << '[' << token.row << ',' << token.col << "]: " << token.lexeme << endl;
}

int GetTokPrecedence(Token token) {
    BinopPrecedence['<'] = 10;
    BinopPrecedence['+'] = 20;
    BinopPrecedence['-'] = 20;
    BinopPrecedence['*'] = 40;

    const char op = token.lexeme[0];
    if (!isascii(op))
        return -1;

    const int TokPrec = BinopPrecedence[op];
    if (TokPrec <= 0) return -1;
    return TokPrec;
}

unique_ptr<ExprAST> Parser::parseExpression(unique_ptr<bool> &fatalError) {
    auto LHS = ParsePrimary(fatalError);

    if (!LHS)
        return nullptr;

    Token temp_token = lexer.getNextToken();

    return parseBinOpRHS(0, temp_token, move(LHS), fatalError);
}

unique_ptr<ExprAST> Parser::ParsePrimary(unique_ptr<bool> &fatalError) {
    Token temp_token = lexer.getNextToken();

    switch (temp_token.type) {
        case NUMBER:
        case STRING:
        case HEX_NUMBER:
        case REAL_NUMBER:
        case OCT_NUMBER:
        case ID:
            return parseNumberExpression(temp_token, fatalError);
        case LPAREN:
            return parseParenExpr(fatalError);
        case LBRACE: {
            auto ptr = parseBraceExpr(fatalError);
            ptr->print();
            return ptr;
        }
        default:
            fatalError.reset(new bool(true));
            printError("Неизвестное выражение: ", temp_token);
    }
    return nullptr;
}

unique_ptr<ExprAST> Parser::parseParenExpr(unique_ptr<bool> &fatalError) {
    auto expr = parseExpression(fatalError);

    if (!expr)
        return nullptr;

    if (lexer.currentToken.type != RPAREN) {
        printError("Ожидалось закрытая скобка: ", lexer.currentToken);
        fatalError.reset(new bool(true));
    }

    return expr;
}

unique_ptr<ExprAST> Parser::parseBraceExpr(unique_ptr<bool> &fatalError) {
    auto arrayExpression = make_unique<ArrayExprAST>(ArrayExprAST());
    Token temp_token = lexer.getNextToken();
    while (true) {
        if (lexer.currentToken.type == SEMICOLON)
            continue;

        if (temp_token.type == RBRACE) {
            break;
        }

        auto expr = parseExpression(fatalError);

        if (!expr)
            return nullptr;

        arrayExpression->pushExpression(move(expr));
    }
    return arrayExpression;
}

unique_ptr<ExprAST> Parser::parseBinOpRHS(int exprPrec, Token temp_token, unique_ptr<ExprAST> LHS, unique_ptr<bool> &fatalError) {
    while (true) {
        int tokPrec = GetTokPrecedence(temp_token);

        if (tokPrec < exprPrec)
            return LHS;

        char binOp = temp_token.lexeme[0];

        unique_ptr<ExprAST> RHS = ParsePrimary(fatalError);

        if (!RHS)
            return 0;

        temp_token = lexer.getNextToken();

        int nextPrec = GetTokPrecedence(temp_token);
        if (tokPrec < nextPrec) {
            RHS = parseBinOpRHS(tokPrec + 1, temp_token, move(RHS), fatalError);
            if (RHS == 0)
                return 0;
        }

        LHS = make_unique<BinaryExprAST>(binOp, move(LHS), move(RHS));
    }
}

unique_ptr<ExprAST> Parser::parseNumberExpression(Token token, unique_ptr<bool> &fatalError) {
    const double number = stod(token.lexeme);

    return make_unique<NumberExprAST>(number);
}

/*unique_ptr<ExprAST> Parser::parseTopLevelExpression(Token token, unique_ptr<bool> &fatalError) {
    Token temp_token = token;
    switch (temp_token.type) {
        case PLUS:
        case MINUS: {
            temp_token = lexer.getNextToken();
            if (temp_token.type == MINUS || temp_token.type == PLUS)
                //parseTopExpression(temp_token);
            if (temp_token.type != ID && temp_token.type != OCT_NUMBER &&
                temp_token.type != HEX_NUMBER && temp_token.type != REAL_NUMBER) {
                printError("Нераспознанный идентификатор", temp_token);
                fatalError.reset(new bool(true));
                break;
            }

            Token nextToken = lexer.getNextToken();
            if (nextToken.col == temp_token.col || temp_token.type == SEMICOLON) {
                printError("Укажите ';' или передвиньте каретку на новую строку: ", temp_token);
                fatalError.reset(new bool(true));
            }
            break;
        }
        case NUMBER: {
            const double number = stod(temp_token.lexeme);

            Token next_token = lexer.getNextToken();

            if (temp_token.type == SEMICOLON || next_token.row != temp_token.row)
                return make_unique<NumberExprAST>(number);

            return parseNumberExpression(next_token, fatalError);
        }
        default:
            fatalError.reset(new bool(true));
            printError("В массиве не может быть такого значения: ", temp_token);
    }
}*/

void Parser::parse(unique_ptr<bool> &fatalError) {
    Token temp_token = lexer.getNextToken();

    switch (temp_token.type) {
        case KW_VAR:
        case KW_CONST:
            parseVariable(fatalError);
        default:
            break;
    }

    return;
}

unique_ptr<ExprAST> Parser::parseVariable(unique_ptr<bool> &fatalError) {
    Token temp_token = lexer.getNextToken();

    if (temp_token.type != ID) {
        fatalError.reset(new bool(true));

        printError("Ошибка: некорректное имя переменной: ", temp_token);
    }

    temp_token = lexer.getNextToken();

    if (temp_token.type == EQUAL) {
        auto bin = parseExpression(fatalError);
        return nullptr;
    }

    /*switch (temp_token.type) {
        case EQUAL:
            temp_token = lexer.getNextToken();

            switch (temp_token.type) {
                case NUMBER:
                case STRING:
                case HEX_NUMBER:
                case REAL_NUMBER:
                case OCT_NUMBER:
                case ID: {
                    auto bin = parseExpression(temp_token, fatalError);
                    return nullptr;
                }
                case LBRACE: {
                    bool first = true;
                    while (true) {
                        temp_token = lexer.getNextToken();

                        if (first && temp_token.type == COMMA) {
                            fatalError.reset(new bool(true));
                            printError("Ошибка: массив не может начинаться с: ", temp_token);
                            break;
                        }
                        first = false;

                        if (temp_token.type == COMMA)
                            continue;

                        if (temp_token.type == RBRACE)
                            break;

                        //parseTopLevelExpression(temp_token, fatalError);
                    }
                    break;
                }
                default:
                    printError("В массиве не может быть такого значения: ", temp_token);
                    fatalError.reset(new bool(true));
            }
            break;
        case SEMICOLON:
            break;
        default:
            break;*/
}