#include "ArrayExprAST.h"

void ArrayExprAST::pushExpression(unique_ptr<ExprAST> element) {
    Elements.push_back(move(element));
}
