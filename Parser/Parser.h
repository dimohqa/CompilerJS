#ifndef COMPILATOR_PARSER_H
#define COMPILATOR_PARSER_H

#include <iostream>
#include <memory>
#include <map>
#include "stdlib.h"
#include "../Lexer/Token.h"
#include "../Lexer/Lexer.h"
#include "AST/ExprAST.h"
#include "AST/VariableExprAST.h"
#include "AST/NumberExprAST.h"
#include "AST/BinaryExprAST.h"
#include "AST/ArrayExprAST.h"
#include "AST/PrototypeAST.h"
#include "AST/CallExprAST.h"
#include "AST/FunctionAST.h"
#include "AST/BodyAST.h"

using namespace std;

static std::map<char, int> BinopPrecedence;

class Parser {
private:
    Lexer lexer;
    static std::map<char, int> BinopPrecedence;
    Token currentToken;
public:
    Parser(Lexer lexer): lexer(lexer) {}
    Token getNextToken() {
        return currentToken = lexer.getNextToken();
    }
    unique_ptr<FunctionAST> parse(unique_ptr<bool> &fatalError);
    unique_ptr<ExprAST> parseVariable(unique_ptr<bool> &fatalError);
    unique_ptr<ExprAST> ParsePrimary(unique_ptr<bool> &fatalError);
    unique_ptr<ExprAST> parseExpression(unique_ptr<bool> &fatalError);
    unique_ptr<ExprAST> parseNumberExpression(unique_ptr<bool> &fatalError);
    unique_ptr<ExprAST> parseBinOpRHS(int exprPrec, unique_ptr<ExprAST> LHS, unique_ptr<bool> &fatalError);
    unique_ptr<ExprAST> parseParenExpr(unique_ptr<bool> &fatalError);
    unique_ptr<ExprAST> parseBraceExpr(unique_ptr<bool> &fatalError);
    unique_ptr<ExprAST> parseTopLevel(unique_ptr<bool> &fatalError);
    void parseUnary(Token token, bool ****fatalError);
};

#endif
