#include <iostream>

#ifndef COMPILATOR_VARIABLEEXPRESSION_H
#define COMPILATOR_VARIABLEEXPRESSION_H

using namespace std;

class VariableExpression {
private:
    string Name;

public:
    VariableExpression(const string &Name): Name(Name) {}

};


#endif
