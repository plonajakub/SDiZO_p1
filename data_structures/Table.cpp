//
// Created by Jakub Plona PL on 09.03.2019.
//

#include "Table.h"

Table::Table() noexcept : size(0), capacity(0), table(nullptr) {
}

Table::~Table() noexcept {
    delete [] table;
}

void Table::insert(int index, int value) {
    if (index > size || index < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    if (capacity == 0) {
        table = new int[1];
        capacity = 1;
    } else if (capacity > size) {
        for (int i = size - 1; i >= index; --i) {
            table[i + 1] = table[i];
        }
    } else if (capacity == size) {
        auto *tmpTable = new int[ENLARGEMENT_COEFFICIENT * capacity];
        int i;
        for (i = 0; i < index; ++i) {
            tmpTable[i] = table[i];
        }
        for (int j = index + 1; i < size; ++i, ++j) {
            tmpTable[j] = table[i];
        }
        delete [] table;
        table = tmpTable;
        capacity *= ENLARGEMENT_COEFFICIENT;
    }
    table[index] = value;
    ++size;
}

void Table::insertAtStart(int value) {
    if (capacity == 0) {
        table = new int[1];
        capacity = 1;
    } else if (capacity > size) {
        for (int i = size - 1; i >= 0; --i) {
            table[i + 1] = table[i];
        }
    } else if (capacity == size) {
        auto *tmpTable = new int[ENLARGEMENT_COEFFICIENT * capacity];
        for (int i = size - 1; i >= 0; --i) {
            tmpTable[i + 1] = table[i];
        }
        delete [] table;
        table = tmpTable;
        capacity *= ENLARGEMENT_COEFFICIENT;
    }
    table[0] = value;
    ++size;
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

void Table::remove(int index) {
    if (index >= size || index < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    if (size == 1) {
        delete [] table;
        table = nullptr;
        capacity = 0;
    }
    else if (getFullFactor() > REDUCTION_COEFFICIENT) {
        for (int i = index; i < size - 1; ++i) {
            table[i] = table[i + 1];
        }
    } else {
        auto *tmpTable = new int [capacity / ENLARGEMENT_COEFFICIENT];
        int i;
        for (i = 0; i < index; ++i) {
            tmpTable[i] = table[i];
        }
        ++i;
        for (int j = index; i < size; ++i, ++j) {
            tmpTable[j] = table[i];
        }
        delete [] table;
        table = tmpTable;
        capacity /= ENLARGEMENT_COEFFICIENT;
    }
    --size;
}

void Table::removeAtStart() {
    if (size == 1) {
        delete [] table;
        table = nullptr;
        capacity = 0;
    }
    else if (getFullFactor() > REDUCTION_COEFFICIENT) {
        for (int i = 0; i < size - 1; ++i) {
            table[i] = table[i + 1];
        }
    } else {
        auto *tmpTable = new int [capacity / ENLARGEMENT_COEFFICIENT];
        for (int i = 0; i < size - 1; ++i) {
            tmpTable[i] = table[i + 1];
        }
        delete [] table;
        table = tmpTable;
        capacity /= ENLARGEMENT_COEFFICIENT;
    }
    --size;
}


void Table::removeAtEnd() {
    if (size == 1) {
        delete [] table;
        table = nullptr;
        capacity = 0;
    } else if (getFullFactor() == REDUCTION_COEFFICIENT) {
        auto *tmpTable = new int [capacity / ENLARGEMENT_COEFFICIENT];
        for (int i = 0; i < size - 1; ++i) {
            tmpTable[i] = table[i];
        }
        delete [] table;
        table = tmpTable;
        capacity /= ENLARGEMENT_COEFFICIENT;
    }
    --size;
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
    if (size != 0) {
        strTable.append(std::to_string(table[size - 1]));
    }
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
    if (capacity == 0) {
        return 1;
    } else {
        return static_cast<double>(size)/capacity;
    }
}

std::ostream& operator<<(std::ostream &ostr, const Table &table) {
    ostr << table.asString();
    return ostr;
}
