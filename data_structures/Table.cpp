#include "Table.h"

Table::Table() noexcept : size(0), capacity(0), table(nullptr) {
}

Table::~Table() noexcept {
    delete[] table;
}

void Table::insert(int index, int value) {
    // Check if index is valid
    if (index > size || index < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    if (capacity == 0) {
        // First elements is being inserted
        table = new int[1];
        capacity = 1;
    } else if (capacity > size) {
        // Insert element without enlarging table
        for (int i = size - 1; i >= index; --i) {
            table[i + 1] = table[i];
        }
    } else if (capacity == size) {
        // Table must be enlarged before insertion
        auto *tmpTable = new int[ENLARGEMENT_COEFFICIENT * capacity];
        int i;
        for (i = 0; i < index; ++i) {
            tmpTable[i] = table[i];
        }
        for (int j = index + 1; i < size; ++i, ++j) {
            tmpTable[j] = table[i];
        }
        delete[] table;
        table = tmpTable;
        capacity *= ENLARGEMENT_COEFFICIENT;
    }
    table[index] = value;
    ++size;
}

void Table::insertAtStart(int value) {
    if (capacity == 0) {
        // First elements is being inserted
        table = new int[1];
        capacity = 1;
    } else if (capacity > size) {
        // Insert element without enlarging table
        for (int i = size - 1; i >= 0; --i) {
            table[i + 1] = table[i];
        }
    } else if (capacity == size) {
        // Table must be enlarged before insertion
        auto *tmpTable = new int[ENLARGEMENT_COEFFICIENT * capacity];
        for (int i = size - 1; i >= 0; --i) {
            tmpTable[i + 1] = table[i];
        }
        delete[] table;
        table = tmpTable;
        capacity *= ENLARGEMENT_COEFFICIENT;
    }
    table[0] = value;
    ++size;
}

void Table::insertAtEnd(int value) {
    if (capacity == 0) {
        // First elements is being inserted
        table = new int[1];
        capacity = 1;
    } else if (capacity == size) {
        // Table must be enlarged before insertion
        auto *tmpTable = new int[ENLARGEMENT_COEFFICIENT * capacity];
        for (int i = 0; i < size; ++i) {
            tmpTable[i] = table[i];
        }
        delete[] table;
        table = tmpTable;
        capacity *= ENLARGEMENT_COEFFICIENT;
    }
    table[size] = value;
    ++size;
}

void Table::remove(int index) {
    // Check if index is valid
    if (index >= size || index < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    if (size == 1) {
        // Remove last element
        delete[] table;
        table = nullptr;
        capacity = 0;
    } else if (getFullFactor() > REDUCTION_COEFFICIENT) {
        // Table doesn't have to be reduced after removal
        for (int i = index; i < size - 1; ++i) {
            table[i] = table[i + 1];
        }
    } else {
        // Table has to be reduced after removal
        auto *tmpTable = new int[capacity / ENLARGEMENT_COEFFICIENT];
        int i;
        for (i = 0; i < index; ++i) {
            tmpTable[i] = table[i];
        }
        ++i;
        for (int j = index; i < size; ++i, ++j) {
            tmpTable[j] = table[i];
        }
        delete[] table;
        table = tmpTable;
        capacity /= ENLARGEMENT_COEFFICIENT;
    }
    --size;
}

void Table::removeFromStart() {
    // Check if table is not empty
    if (size < 1) {
        throw std::out_of_range("Table is empty");
    }
    if (size == 1) {
        // Remove last element
        delete[] table;
        table = nullptr;
        capacity = 0;
    } else if (getFullFactor() > REDUCTION_COEFFICIENT) {
        // Table doesn't have to be reduced after removal
        for (int i = 0; i < size - 1; ++i) {
            table[i] = table[i + 1];
        }
    } else {
        // Table has to be reduced after removal
        auto *tmpTable = new int[capacity / ENLARGEMENT_COEFFICIENT];
        for (int i = 0; i < size - 1; ++i) {
            tmpTable[i] = table[i + 1];
        }
        delete[] table;
        table = tmpTable;
        capacity /= ENLARGEMENT_COEFFICIENT;
    }
    --size;
}


void Table::removeFromEnd() {
    // Check if table is not empty
    if (size < 1) {
        throw std::out_of_range("Table is empty");
    }
    if (size == 1) {
        // Remove last element
        delete[] table;
        table = nullptr;
        capacity = 0;
    } else if (getFullFactor() == REDUCTION_COEFFICIENT) {
        // Table has to be reduced after removal
        auto *tmpTable = new int[capacity / ENLARGEMENT_COEFFICIENT];
        for (int i = 0; i < size - 1; ++i) {
            tmpTable[i] = table[i];
        }
        delete[] table;
        table = tmpTable;
        capacity /= ENLARGEMENT_COEFFICIENT;
    }
    --size;
}

int Table::search(int value) const {
    int index = VALUE_NOT_FOUND;

    // Perform linear search on the table
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

int &Table::operator[](int index) {
    if (index >= size || index < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    return table[index];
}

int &Table::operator[](int index) const {
    if (index >= size || index < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    return table[index];
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
        return static_cast<double>(size) / capacity;
    }
}

std::ostream &operator<<(std::ostream &ostr, const Table &table) {
    ostr << table.asString();
    return ostr;
}
