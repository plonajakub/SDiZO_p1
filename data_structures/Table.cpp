//
// Created by Jakub Plona PL on 09.03.2019.
//

#include "Table.h"

Table::Table() noexcept : size(0), capacity(0), table(nullptr) {
}

Table::~Table() noexcept {
    delete [] table;
}

void Table::insertAtEnd(int value) {
    if (capacity == 0) {
        table = new int[1];
        capacity = 1;
    } else if (capacity == size) {
        auto *tmpTable = new int[ENLARGEMENT_COEFFICIENT * capacity];
        for (int i = 0; i < size; ++i) {
            tmpTable[i] = table[i];
        }
        delete [] table;
        table = tmpTable;
        capacity *= ENLARGEMENT_COEFFICIENT;
    }
    table[size] = value;
    ++size;
}

int Table::remove(int index) {
    return 0;
}

int Table::search(int value) const {
    int index = -1;
    for (int i = 0; i < size; ++i) {
        if (table[i] == value) {
            index = i;
            break;
        }
    }
    return index;
}

std::string Table::asString() const {
    std::string strTable;
    strTable.append("[");
    for (int i = 0; i < size - 1; ++i) {
        strTable.append(std::to_string(table[i]));
        strTable.append(", ");
    }
    strTable.append(std::to_string(table[size - 1]));
    strTable.append("]");
    return strTable;
}

int Table::getSize() const {
    return size;
}


int Table::getCapacity() const {
    return capacity;
}

double Table::getFullFactor() const {
    return 0;
}

std::ostream &operator<<(std::ostream &ostr, const Table &table) {
    ostr << table.asString();
    return ostr;
}
