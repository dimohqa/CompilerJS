#include "Parser.h"
#include <memory>

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

    getNextToken();
    //currentToken.print();
    return parseBinOpRHS(0, move(LHS), fatalError);
}

unique_ptr<ExprAST> Parser::ParsePrimary(unique_ptr<bool> &fatalError) {
    switch (currentToken.type) {
        case NUMBER:
        case HEX_NUMBER:
        case REAL_NUMBER:
        case OCT_NUMBER:
        case ID:
            return parseNumberExpression(fatalError);
        case STRING:
            return parseStringExpression(fatalError);
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
    auto expr = parseExpression(fatalError);

    if (!expr)
        return nullptr;

    if (currentToken.type != RPAREN) {
        printError("Ожидалось закрытая скобка: ", currentToken);
        fatalError.reset(new bool(true));
    }

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
        if (!expr)
            return nullptr;

        arrayExpression->pushExpression(move(expr));
    }
    return arrayExpression;
}

unique_ptr<ExprAST> Parser::parseBinOpRHS(int exprPrec, unique_ptr<ExprAST> LHS, unique_ptr<bool> &fatalError) {
    while (true) {
        int tokPrec = GetTokPrecedence(currentToken);

        if (tokPrec < exprPrec)
            return LHS;

        char binOp = currentToken.lexeme[0];

        getNextToken();
        unique_ptr<ExprAST> RHS = ParsePrimary(fatalError);

        if (!RHS)
            return 0;

        getNextToken();

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

    return make_unique<NumberExprAST>(number);
}

unique_ptr<ExprAST> Parser::parseStringExpression(unique_ptr<bool> &fatalError) {
        return make_unique<StringExprAST>(currentToken.lexeme);
}

unique_ptr<ExprAST> Parser::parse(unique_ptr<bool> &fatalError) {
    auto body = make_unique<BodyAST>();
    getNextToken();
    while (true) {
        switch (currentToken.type) {
            case KW_VAR:
            case KW_LET:
            case KW_CONST:
                body->push(parseVariable(fatalError));
                break;
            case KW_RETURN:
                body->push(parseReturn(fatalError));
                break;
            case KW_IF:
                body->push(parseIF(fatalError));
                break;
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

    getNextToken(); // '{'
    auto body = parse(fatalError);
    if (!body)
        return nullptr;

    return make_unique<IfAST>(move(parenExpr), move(body));
}

unique_ptr<ExprAST> Parser::parseVariable(unique_ptr<bool> &fatalError) {
    getNextToken();

    if (currentToken.type != ID) {
        fatalError.reset(new bool(true));

        printError("Ошибка: некорректное имя переменной: ", currentToken);

        return nullptr;
    }

    auto variable = make_unique<VariableExprAST>(currentToken.lexeme, nullptr);

    getNextToken();

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