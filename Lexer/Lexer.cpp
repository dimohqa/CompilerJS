#include "Lexer.h"

int operLength = 49;
int reservLength = 36;

Token Lexer::getNextToken() {
    int colStart;
    TokenType int_tok;
    Token token;
    bool check;
    string buffer;

    if (!file.is_open()) {
        cout << "Not read file";

        exit(0);
    }
    while (true) {
        char symb = file.peek();
        if (file.eof()) {
            token.set(TokenOfEnum(E0F), row, colStart, E0F);
            return token;
        }
            switch (symb) {
                case '_':
                case '$':
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                case 'E':
                case 'F':
                case 'G':
                case 'H':
                case 'I':
                case 'J':
                case 'K':
                case 'L':
                case 'M':
                case 'N':
                case 'O':
                case 'P':
                case 'Q':
                case 'R':
                case 'S':
                case 'T':
                case 'U':
                case 'V':
                case 'W':
                case 'X':
                case 'Y':
                case 'Z':
                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'e':
                case 'f':
                case 'g':
                case 'h':
                case 'i':
                case 'j':
                case 'k':
                case 'l':
                case 'm':
                case 'n':
                case 'o':
                case 'p':
                case 'q':
                case 'r':
                case 's':
                case 't':
                case 'v':
                case 'w':
                case 'x':
                case 'y':
                case 'z':
                    colStart = col;
                    int_tok = identificator(file, buffer);
                    token.set(buffer, row, colStart, int_tok);
                    return token;
                case '/':
                    colStart = col;
                    check = singleLineComment(file);
                    if (!check) {
                        int_tok = op(file, buffer);
                        token.set(buffer, row, colStart, int_tok);
                        return token;
                    }
                    break;
                case '"':
                case '`':
                case '\'':
                    colStart = col;
                    int_tok = stroka(file, buffer);
                    token.set(buffer, row, colStart, int_tok);
                    return token;
                case '{':
                case '}':
                case '(':
                case ')':
                case '.':
                case '>':
                case '<':
                case '=':
                case '+':
                case '!':
                case ';':
                case '-':
                case '~':
                case '*':
                case '|':
                case '&':
                case '%':
                case '^':
                case ':':
                case ']':
                case '[':
                case '?':
                case '\\':
                case ',':
                    colStart = col;
                    int_tok = op(file, buffer);
                    token.set(buffer, row, colStart, int_tok);
                    return token;
                case ' ':
                    file.get();
                    col++;
                    break;
                case '\n':
                    file.get();
                    row++;
                    col = 1;
                    break;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    colStart = col;
                    int_tok = number(file, buffer);
                    token.set(buffer, row, colStart, int_tok);
                    return token;
                default:
                    file.get();
                    //token.set(buffer, row, colStart, int_tok);
                    //return token;
                    break;
            }
        }
}

TokenType Lexer::number(ifstream &file, string &buffer) {
    buffer = "";
    int pos = 0;
    while (true) {
        char symb = file.peek();
        if (symb == '.') {
            return realNumber(file, buffer);
        }
        if (!(isdigit(symb) || (symb == 'x' && pos == 1) || (symb == 'o' && pos == 1) || (symb == '.' && pos != 0))) {
            break;
        }
        if (symb == '0' && pos == 0) {
            symb = file.get();
            col++;
            buffer += symb;
            if (file.peek() == '.') {
                return realNumber(file, buffer);
            }
            return NUMBER;
        }
        symb = file.get();
        col++;
        buffer += symb;
        pos++;
    }
    if (buffer[1] == 'o') {
        return OCT_NUMBER;
    }
    if (buffer[1] == 'x') {
        return HEX_NUMBER;
    }
    return NUMBER;
}

TokenType Lexer::realNumber(ifstream &file, string &buffer) {
    char symb = file.get();
    buffer += symb;
    while (true) {
        col++;
        symb = file.peek();
        if (!isdigit(symb)) {
            break;
        }
        buffer += symb;
        file.get();
    }
    return REAL_NUMBER;
}

TokenType Lexer::identificator(ifstream &file, string &buffer) {
    buffer = "";
    char symb;
    int pos = 0;
    while (true) {
        symb = file.peek();
        if (!(isalpha(symb) || (symb == '$') || (isdigit(symb) && pos != 0))) {
            break;
        }
        symb = file.get();
        col++;
        buffer += symb;
        pos++;
    }

    for (int i = 0; i < reservLength; i++) {
        if (buffer == reserved_words[i]) {
            return static_cast<TokenType>(i);
        }
    }
    return ID;
}

TokenType Lexer::op(ifstream &file, string &buffer) {
    buffer = "";
    while (true) {
        char symb = file.peek();
        if (symb == EOF) {
            break;
        }
        if (!ispunct(symb)) {
            break;
        }
        symb = file.get();
        col++;
        buffer += symb;
    }
metka:
    for (int i = 0; i < operLength; i++) {
        if (oper[i] == buffer) {
            return static_cast<TokenType>(i + reservLength);
        }
    }
    buffer.pop_back();
    file.unget();
    col--;
    if (buffer.length() != 0) {
        goto metka;
    }
    return UNKNOWN;
}

bool Lexer::singleLineComment(ifstream &file) {
    char symb = file.get();
    col++;
    if (file.peek() == '*') {
        return multiLineComment(file);
    }
    if (file.peek() != '/') {
        file.unget();
        col--;
        return false;
    }
    while(symb != '\n') {
        if (file.peek() == EOF) {
            break;
        }
        symb = file.get();
        col++;
        if (symb == '\n') {
            row++;
            col = 1;
        }
    }
    return true;
}

bool Lexer::multiLineComment(ifstream &file) {
    char symb = file.get();
    col++;
    while (true) {
        if (file.peek() == EOF) {
            break;
        }
        symb = file.get();
        col++;
        if (symb == '\n') {
            col = 1;
            row++;
        }
        if (symb == '*' && (char)file.peek() == '/') {
            file.get();
            col++;
            return true;
        }
    }
}

TokenType Lexer::stroka(ifstream &file, string &buffer) {
    buffer = "";
    char strSymb, symb;
    symb = strSymb = file.get();
    col++;
    while (symb != '\n') {
        buffer += symb;
        col++;
        if ((symb = file.get()) == strSymb) {
            buffer += symb;
            return STRING;
        }
    }
    return UNKNOWN;
}