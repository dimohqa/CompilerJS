#ifndef COMPILATOR_LEXER_H
#define COMPILATOR_LEXER_H

#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include "Token.h"
#include "EnumSwitch/TokenTypeSwitch.h"

using namespace std;

const string reserved_words[] = {
        "this",         "new",      "function",  "var",
        "for",          "if",       "else",     "true",
        "false",        "return",   "undefined","null",
        "instanceof",   "in",       "do",       "default",
        "void",         "while",    "break",    "case",
        "typeof",       "continue", "Infinity", "NaN",
        "delete",       "switch",   "try",      "catch",
        "throw",        "finally",  "with",     "debugger",
        "const",        "let"
};

const string oper[] = {
        "{",    "}",    ".",    ">=",   "+",
        "<<",   "!",    "=",    ">>=",  ";", "/",
        "==",   "-",    ">>",   "~",    "+=", "/=",
        ">>>=", "(",    ",",    "!=",   "*",
        ">>>",  "&&",   "-=",   "&=",   ")",
        "<",    "===",  "%",    "&",    "||",
        "*=",   "|=",   "[",    ">",    "!==",
        "++",   "|",    "?",    "%=",   "^=", "\\",
        "--",   "^",    ":",    "<<=",  "]",    "<="
};

class Lexer {
private:
public:
    virtual void getNextToken(string filepath);
    static int identificator(ifstream &file, string &buffer);
    static int op(ifstream &file, string &buffer);
    static int number(ifstream &file, string &buffer);
    static int realNumber(ifstream &file, string &buffer);
    static int stroka(ifstream &file, string &buffer);
    static int singleLineComment(ifstream &file);
    static bool multiLineComment(ifstream &file);
    static void print_EOF();
};


#endif //COMPILATOR_LEXER_H
