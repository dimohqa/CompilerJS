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

        auto rangeId = table.equal_range(pairId.first);
        for (auto it = rangeId.first; it != rangeId.second; it++) {
            if (identifier.getLevel() == it->second.getLevel()) {
                cout << "Ошибка: Повторное объявление переменной, удалите переменную: " << identifier.getName() << endl;
                return false;
            }
        }

        table.insert(pairId);
        return true;
    }
    bool find(Identifier identifier) {
        pair<string, Identifier> pairId(identifier.getName(), identifier);

        table.find(pairId.first);
    }
    void print() {
        for (auto& item: table) {
            cout << "Identifier: " << item.first << endl;
            item.second.print();
        }
    }
};


#endif
