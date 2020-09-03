#include <iostream>

#ifndef COMPILATOR_NUMBEREXPRESSION_H
#define COMPILATOR_NUMBEREXPRESSION_H

class NumberExpression {
private:
    std::string Value;

public:
    NumberExpression(std::string Value): Value(Value) {}

    void print();
};


#endif
