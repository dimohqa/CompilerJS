#ifndef COMPILERJS_TABLE_H
#define COMPILERJS_TABLE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include "Identifier.h"

using namespace std;

class Table {
private:
    unordered_multimap<string, Identifier> table;

public:
    bool push(Identifier identifier) {
        pair<string, Identifier> pairId(identifier.getName(), identifier);

        auto rangeId = table.equal_range(identifier.getName());
        for (auto it = rangeId.first; it != rangeId.second; it++) {
            cout << it->first << endl;
            if (identifier.getLevel() == it->second.getLevel()) {
                return false;
            }
        }

        table.insert(pairId);
        return true;
    }
    void print() {
        for (auto& item: table) {
            cout << "Identifier: " << item.first << endl;
            item.second.print();
        }
    }
};


#endif
