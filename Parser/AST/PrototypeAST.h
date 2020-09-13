#ifndef COMPILERJS_PROTOTYPEAST_H
#define COMPILERJS_PROTOTYPEAST_H

#include <string>
#include <vector>
#include "ExprAST.h"

using namespace std;

class PrototypeAST: public ExprAST {
private:
    string Name;
    vector<string> Args;

public:
    PrototypeAST(const string &name, const vector<string> &args)
        : Name(name), Args(move(args)) {}
};


#endif
