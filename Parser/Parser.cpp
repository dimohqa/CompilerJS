#include "Parser.h"
#include <memory>

void printError(string error, Token token) {
    cout << error << endl
         << '[' << token.row << ',' << token.col << "]: " << token.lexeme << endl;
}

int GetTokPrecedence(Token token) {
    BinopPrecedence["=="] = 10;
    BinopPrecedence["<"] = 10;
    BinopPrecedence[">"] = 10;
    BinopPrecedence["!="] = 10;
    BinopPrecedence[">="] = 10;
    BinopPrecedence["<="] = 10;
    BinopPrecedence["+"] = 50;
    BinopPrecedence["-"] = 50;
    BinopPrecedence["*"] = 60;
    BinopPrecedence["/"] = 60;
    BinopPrecedence["%"] = 60;

    const char op = token.lexeme[0];
    if (!isascii(op))
        return -1;

    const int TokPrec = BinopPrecedence[token.lexeme];
    if (TokPrec <= 0) return -1;
    return TokPrec;
}

unique_ptr<ExprAST> Parser::parse(unique_ptr<bool> &fatalError) {
    auto body = make_unique<BodyAST>();

    getNextToken();

    while (true) {
        switch (currentToken.type) {
            case KW_VAR:
            case KW_LET:
            case KW_CONST: {
                auto type = currentToken.type;
                getNextToken();
                body->push(parseVariable(type, fatalError));
                break;
            }
            case KW_RETURN:
                body->push(parseReturn(fatalError));
                break;
            case KW_IF:
                body->push(parseIF(fatalError));
                break;
            case KW_WHILE:
                body->push(parseWhile(fatalError));
                break;
            case ID:
                body->push(parseVariable(UNKNOWN, fatalError));
                break;
            case KW_CONSOLE:
                body->push(parseOutput(fatalError));
            case SEMICOLON:
                getNextToken();
                break;
            case RBRACKET:
                return body;
            case E0F: {
                auto proto = make_unique<PrototypeAST>("main", vector<string>());
                return make_unique<FunctionAST>(move(proto), move(body));
            }
            default:
                fatalError.reset(new bool(true));
                printError("Неподдерживаемый токен: ", currentToken);
                getNextToken();
                break;
        }
    }
}


unique_ptr<ExprAST> Parser::parseExpression(unique_ptr<bool> &fatalError) {
    auto LHS = ParsePrimary(fatalError);

    if (!LHS)
        return nullptr;

    //getNextToken();
    //currentToken.print();
    return parseBinOpRHS(0, move(LHS), fatalError);
}

unique_ptr<ExprAST> Parser::ParsePrimary(unique_ptr<bool> &fatalError) {
    switch (currentToken.type) {
        case NUMBER:
        case HEX_NUMBER:
        case REAL_NUMBER:
        case OCT_NUMBER:
            return parseNumberExpression(fatalError);
        case STRING:
            return parseStringExpression(fatalError);
        case ID:
            return parseID(UNKNOWN, fatalError);
        case LPAREN:
            return parseParenExpr(fatalError);
        case LBRACE: {
            auto ptr = parseBraceExpr(fatalError);
            return ptr;
        }
        default:
            fatalError.reset(new bool(true));
            printError("Неизвестное выражение: ", currentToken);
    }
    return nullptr;
}

unique_ptr<ExprAST> Parser::parseParenExpr(unique_ptr<bool> &fatalError) {
    getNextToken();

    if (currentToken.type == RPAREN) {
        fatalError.reset(new bool(true));
        printError("Ожидалось выражение внутри скобок: ", currentToken);

        return nullptr;
    }

    auto expr = parseExpression(fatalError);

    if (!expr)
        return nullptr;

    if (currentToken.type != RPAREN) {
        printError("Ожидалось закрытая скобка: ", currentToken);
        fatalError.reset(new bool(true));
    }
    getNextToken();
    return expr;
}

unique_ptr<ExprAST> Parser::parseBraceExpr(unique_ptr<bool> &fatalError) {
    auto arrayExpression = make_unique<ArrayExprAST>(ArrayExprAST());

    getNextToken();

    while (true) {
        if (currentToken.type == RBRACE)
            break;
        if (currentToken.type == COMMA) {
            getNextToken();
            continue;
        }

        auto expr = parseExpression(fatalError);
        //currentToken.print();
        if (!expr)
            return nullptr;

        arrayExpression->pushExpression(move(expr));
    }
    //currentToken.print();
    getNextToken();
    return arrayExpression;
}

unique_ptr<ExprAST> Parser::parseBinOpRHS(int exprPrec, unique_ptr<ExprAST> LHS, unique_ptr<bool> &fatalError) {
    while (true) {
        int tokPrec = GetTokPrecedence(currentToken);

        if (tokPrec < exprPrec)
            return LHS;

        string binOp = currentToken.lexeme;

        getNextToken();
        unique_ptr<ExprAST> RHS = ParsePrimary(fatalError);

        if (!RHS)
            return 0;

        //getNextToken();

        int nextPrec = GetTokPrecedence(currentToken);
        if (tokPrec < nextPrec) {
            RHS = parseBinOpRHS(tokPrec + 1, move(RHS), fatalError);
            if (RHS == 0)
                return 0;
        }

        LHS = make_unique<BinaryExprAST>(binOp, move(LHS), move(RHS));
    }
}

unique_ptr<ExprAST> Parser::parseNumberExpression(unique_ptr<bool> &fatalError) {
    const double number = stod(currentToken.lexeme);
    getNextToken();
    return make_unique<NumberExprAST>(number);
}

unique_ptr<ExprAST> Parser::parseStringExpression(unique_ptr<bool> &fatalError) {
    const string str = currentToken.lexeme;
    getNextToken();
    return make_unique<StringExprAST>(str);
}

unique_ptr<ExprAST> Parser::parseOutput(unique_ptr<bool> &fatalError) {
    getNextToken();

    if (currentToken.type != DOT) {
        fatalError.reset(new bool(true));

        printError("Ошибка: ожидалась точка: ", currentToken);

        return nullptr;
    }

    getNextToken();

    if (currentToken.type != KW_LOG) {
        fatalError.reset(new bool(true));

        printError("Ошибка: ожидалось log: ", currentToken);

        return nullptr;
    }
    getNextToken();
    if (auto parenExpr = parseParenExpr(fatalError))
        return make_unique<ConsoleLogExprAST>(move(parenExpr));

    return nullptr;
}

unique_ptr<ExprAST> Parser::parseID(TokenType type, unique_ptr<bool> &fatalError) {
    if (currentToken.type != ID) {
        fatalError.reset(new bool(true));

        printError("Ошибка: некорректное имя переменной: ", currentToken);

        return nullptr;
    }
    const string name = currentToken.lexeme;

    getNextToken();

    auto id = make_unique<VariableExprAST>(name, type, nullptr);

    //Дописывал позднее
    if (currentToken.type == LBRACE) {
        getNextToken();

        if (currentToken.type != NUMBER) {
            fatalError.reset(new bool(true));
            printError("Ошибка: Неккоретный индекс обращения к массиву: ", currentToken);
            return nullptr;
        }

        auto index = parseNumberExpression(fatalError);

        if (currentToken.type != RBRACE) {
            fatalError.reset(new bool(true));
            printError("Ошибка: ожидалась ']': ", currentToken);
            return nullptr;
        }

        getNextToken();

        return make_unique<VariableArrayExprAST>(move(id), move(index));
    }

    return id;
}

unique_ptr<ExprAST> Parser::parseReturn(unique_ptr<bool> &fatalError) {
    getNextToken();
    if (auto ret = parseExpression(fatalError)) {
        return make_unique<ReturnExprAST>(move(ret));
    }
    return nullptr;
}

unique_ptr<ExprAST> Parser::parseIF(unique_ptr<bool> &fatalError) {
    getNextToken(); // '('
    auto parenExpr = parseParenExpr(fatalError);
    if (!parenExpr)
        return nullptr;

    auto body = parse(fatalError);
    if (!body)
        return nullptr;

    getNextToken();

    return make_unique<IfAST>(move(parenExpr), move(body));
}

unique_ptr<ExprAST> Parser::parseWhile(unique_ptr<bool> &fatalError) {
    getNextToken(); // '('
    auto parenExpr = parseParenExpr(fatalError);
    if (!parenExpr)
        return nullptr;

    auto body = parse(fatalError);
    if (!body)
        return nullptr;

    getNextToken();

    return make_unique<WhileAST>(move(parenExpr), move(body));
}

unique_ptr<ExprAST> Parser::parseVariable(TokenType type, unique_ptr<bool> &fatalError) {
    auto variable = parseID(type, fatalError);;

    //getNextToken();

    if (currentToken.type == EQUAL) {
        getNextToken();

        variable->setExpr(parseExpression(fatalError));
        return variable;
    }

    if (currentToken.type == SEMICOLON) {
        return variable;
    }

    return nullptr;
}