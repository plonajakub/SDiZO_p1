//
// Created by Jakub Plona PL on 22.03.2019.
//

#ifndef SDIZO_P1_HEAP_H
#define SDIZO_P1_HEAP_H

#include <string>
#include <iostream>
#include "Table.h"


class Heap {
public:
    void insert(int key);
    void remove(int key);
    int search(int key) const;
    void print(int index, int indent) const;

private:
    Table table;

    inline int parent(int index) const;
    inline int left(int index) const;
    inline int right(int index) const;
    void heapify(int index);
    void swap(int &x, int &y) const;

    friend class HeapTest;
};

std::ostream& operator<<(std::ostream &ostr, const Heap &heap);

#endif //SDIZO_P1_HEAP_H
