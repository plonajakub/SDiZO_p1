#ifndef SDIZO_P1_HEAP_H
#define SDIZO_P1_HEAP_H

#include <string>
#include <iostream>

#include "Table.h"


class Heap {
public:
    // Inserts key into heap
    void insert(int key);

    // Removes key from heap
    void remove(int key);

    // Searches for key in heap and returns key's index
    // If key does not exists search() returns KEY_NOT_FOUND
    int search(int key) const;

    // Draws heap in the console
    void print(const std::ostream &ostr, int index, int indent) const;

private:
    // Index returned by search() if key was not found
    static const int KEY_NOT_FOUND = -1;

    // This heap is implemented as a table
    Table table;

    // Parent node's index
    inline int parent(int index) const;

    // Left child node's index
    inline int left(int index) const;

    // Right child node's index
    inline int right(int index) const;

    // Standard algorithm for restoring heap order in node
    void heapify(int index);

    // Exchange values of two ints
    void swap(int &x, int &y) const;

    // Performs a recursive search
    void findKey(int &key, int currIdx, int &keyIndex) const;

    // For test purposes only
    friend class HeapTest;
};

// Declared for convenience
std::ostream &operator<<(std::ostream &ostr, const Heap &heap);

#endif //SDIZO_P1_HEAP_H
