#ifndef COMPILERJS_IDENTIFIER_H
#define COMPILERJS_IDENTIFIER_H

#include <iostream>
#include <string>

using namespace std;

enum IdentifierType {
    NUM = 1,
    STR = 2,
    ARR = 3,
    UND = 4,
};

class Identifier {
    string Name; // +
    bool Volatile; // +
    int SizeByte; // +
    int SizeBite; // +
    int Level; // +
    IdentifierType Type; // +
    int AmountOfElements; // +
    string Register; // ???
    int Offset; // +- array not working

public:
    Identifier(string name, int level, bool vol, IdentifierType type, int length)
        : Name(name), Level(level), Volatile(vol), Type(type), AmountOfElements(length) {
        switch (type) {
            case NUM:
                SizeByte = 4;
                SizeBite = SizeByte * 8;
                Offset = 0;
                break;
            case STR:
                SizeByte = 4 * AmountOfElements;
                SizeBite = SizeByte * 8;
                Offset = 0;
                break;
            default:
                SizeByte = 4;
                SizeBite = SizeByte * 8;
                Offset = 0;
                break;
        }
    }
    string getName() {
        return Name;
    }
    int getLevel() {
        return Level;
    }
    void printIdentifier() {
        switch (Type) {
            case NUM:
                cout << "NUMBER";
                break;
            case STR:
                cout << "STRING";
                break;
            case ARR:
                cout << "ARRAY";
                break;
            case UND:
                cout << "UNDEFINED";
                break;
            default:
                cout << "UNKNOWN";
                break;
        }
    }

    void changeType(IdentifierType type) {
        Type = type;
    }

    IdentifierType getType() {
        return Type;
    }

    bool getVolatile() {
        return Volatile;
    }

    void print() {
        cout << '\t' << "Volatile: " << Volatile << endl;
        cout << '\t' << "Level: " << Level << endl;
        cout << '\t' << "IdentifierType: "; printIdentifier(); cout << endl;
        cout << '\t' << "AmountOfElements: " << AmountOfElements << endl;
        cout << '\t' << "SizeByte: " << SizeByte << endl;
        cout << '\t' << "SizeBite: " << SizeBite << endl;
    }
};


#endif
