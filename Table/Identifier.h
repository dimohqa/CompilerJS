#ifndef COMPILERJS_IDENTIFIER_H
#define COMPILERJS_IDENTIFIER_H

#include <iostream>
#include <string>

using namespace std;

enum IdentifierType {
    NUMBER,
    STRING,
    ARRAY,
};

class Identifier {
    string Name;
    bool Volatile;
    int SizeByte;
    int SizeBite;
    int Level;
    //int AlignmentBytes;
    //int AlignmentBites;
    IdentifierType Type;
    int AmountOfElements;
    //bool RegisterVariable;
    string Register;
    //string BaseRegister;
    int Offset;

public:
    Identifier() {}
    string getName() {
        return Name;
    }
    int getLevel() {
        return Level;
    }
    void printIdentifier() {
        switch (Type) {
            case NUMBER:
                cout << "NUMBER";
                break;
            case STRING:
                cout << "STRING";
                break;
            case ARRAY:
                cout << "ARRAY";
                break;
            default:
                cout << "UNKNOWN";
                break;
        }
    }
    void print() {
        cout << '\t' << "Volatile: " << Volatile << endl;
        cout << '\t' << "Level: " << Level << endl;
        cout << '\t' << "SizeByte: " << SizeBite << endl;
        cout << '\t' << "IdentifierType: "; printIdentifier(); cout << endl;
    }
};


#endif
