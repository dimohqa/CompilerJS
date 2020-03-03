#include "Lexer.h"

int operLength = 49;
int reservLength = 34;

void Lexer::getNextToken(string filepath) {
    int row = 0, col = 0;
    int int_tok;
    bool check;
    string buffer;

    ifstream in(filepath);
    if (!in.is_open()) {
        cout << "Not read file";
    }
    while (true) {
        char symb = in.peek();
        if (in.eof()) {
            print_EOF();
            return;
        }
        switch (symb) {
            case '_': case '$':
            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
            case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
            case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
            case 'V': case 'W': case 'X': case 'Y': case 'Z':
            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
            case 'g': case 'h': case 'i': case 'j': case 'k': case 'l':
            case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
            case 's': case 't': case 'v': case 'w': case 'x': case 'y':
            case 'z':
                int_tok = identificator(in, buffer);
                cout << TokenOfEnum(int_tok) << "\t" << buffer << "\n";
                break;
            case '/':
                check = singleLineComment(in);
                if (!check) {
                    int_tok = op(in, buffer);
                    if (int_tok == - 1) {
                        break;
                    }
                    cout << TokenOfEnum(int_tok) << "\t" << buffer << "\n";
                }
                break;
            case '"': case '`': case '\'':
                int_tok = stroka(in, buffer);
                cout << TokenOfEnum(int_tok) << "\t" << buffer << "\n";
                break;
            case '{': case '}': case '(': case ')': case '.': case '>':
            case '<': case '=': case '+': case '!': case ';': case '-':
            case '~': case '*': case '|': case '&': case '%': case '^':
            case ':': case ']': case '[': case '?': case '\\': case ',':
                int_tok = op(in, buffer);
                cout << TokenOfEnum(int_tok) << "\t" << buffer << "\n";
                break;
            case ' ':
                in.get();
                break;
            case '\n':
                in.get();
                row++;
                break;
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                int_tok = number(in, buffer);
                cout << TokenOfEnum(int_tok) << "\t" << buffer << "\n";
                break;
            default:
                cout << TokenOfEnum(999) << '\t' << symb << '\n';
                in.get();
        }
        col++;
    }
}

int Lexer::number(ifstream &file, string &buffer) {
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
            buffer += symb;
            if (file.peek() == '.') {
                return realNumber(file, buffer);
            }
            return NUMBER;
        }
        symb = file.get();
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

int Lexer::realNumber(ifstream &file, string &buffer) {
    char symb = file.get();
    buffer += symb;
    while (true) {
        symb = file.peek();
        if (!isdigit(symb)) {
            break;
        }
        buffer += symb;
        file.get();
    }
    return REAL_NUMBER;
}

int Lexer::identificator(ifstream &file, string &buffer) {
    buffer = "";
    char symb;
    int pos = 0;
    while (true) {
        symb = file.peek();
        if (!(isalpha(symb) || (symb == '$') || (isdigit(symb) && pos != 0))) {
            break;
        }
        symb = file.get();
        buffer += symb;
        pos++;
    }

    for (int i = 0; i < reservLength; i++) {
        if (buffer == reserved_words[i]) {
            return i;
        }
    }
    return ID;
}

int Lexer::op(ifstream &file, string &buffer) {
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
        buffer += symb;
    }
metka:
    for (int i = 0; i < operLength; i++) {
        if (oper[i] == buffer) {
            return i + reservLength;
        }
    }
    buffer.pop_back();
    file.unget();
    if (buffer.length() != 0) {
        goto metka;
    }
    return 999;
}

int Lexer::singleLineComment(ifstream &file) {
    char symb = file.get();
    if (file.peek() == '*') {
        return multiLineComment(file);
    }
    if (file.peek() != '/') {
        file.unget();
        return false;
    }
    while(symb != '\n') {
        if (file.peek() == EOF) {
            return false;
        }
        symb = file.get();
    }
    return true;
}

bool Lexer::multiLineComment(ifstream &file) {
    char symb = file.get();
    while (true) {
        symb = file.get();
        if (file.eof()) {

            return false;
        }
        if (symb == '*' && (char)file.peek() == '/') {
            file.get();
            return true;
        }
    }
}

int Lexer::stroka(ifstream &file, string &buffer) {
    buffer = "";
    char strSymb, symb;
    symb = strSymb = file.get();
    while (symb != '\n') {
        buffer += symb;
        if ((symb = file.get()) == strSymb) {
            buffer += symb;
            return STRING;
        }
    }
    return UNKNOWN;
}

void Lexer::print_EOF() {
    cout << TokenOfEnum(E0F) << "\t" << "''" << "\n";
}