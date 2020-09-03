#include <iostream>
#include <gtest/gtest.h>
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

static std::unique_ptr<NumberExpression> parseNumberExpr(Token token) {
    switch (token.type) {
        case NUMBER: {
            auto result = std::make_unique<NumberExpression>(token.lexeme);
            cout << token.type << token.lexeme;
            return std::move(result);
        }
        default:
            auto result = std::make_unique<NumberExpression>("");
            return std::move(result);
    }
}

int main() {
    string filepath = "/home/nitro/university/CompilerJS/js/nod.js";
    Lexer lexer(filepath);

    while (true) {
        Token token = lexer.getNextToken();
        token.print();
        auto res = parseNumberExpr(token);

        res->print();
    }
    return 0;
}
