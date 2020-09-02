#include <iostream>
#include <vector>
#include "Expression.h"

#ifndef COMPILATOR_CALLEXPRESSION_H
#define COMPILATOR_CALLEXPRESSION_H

using namespace std;

class CallExpression {
private:
    string Callee;
    vector<Expression> Args;

public:
    CallExpression(const string &Callee, vector<Expression> Args): Callee(Callee), Args(Args) {}
};


#endif
