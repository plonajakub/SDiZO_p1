//
// Created by Jakub Plona PL on 09.03.2019.
//

#ifndef SDIZO_P1_TABLE_H
#define SDIZO_P1_TABLE_H

#include <iostream>
#include "../Tests/TableTest.h"

class Table {

public:
    Table() noexcept;
    ~Table() noexcept;
    void insert(int index, int value);
    void insertAtEnd(int value);
    void insertAtStart(int value);
    void remove(int index);
    int search(int value) const;
    std::string asString() const;

    int getCapacity() const;
    int getSize() const;

private:
    const int ENLARGEMENT_COEFFICIENT = 2;
    const double REDUCTION_COEFFICIENT = 0.25;

    int size;
    int capacity;
    int *table;

    double getFullFactor() const;

    friend class TableTest;
};

std::ostream& operator<<(std::ostream &ostr, const Table &table);

#endif //SDIZO_P1_TABLE_H
