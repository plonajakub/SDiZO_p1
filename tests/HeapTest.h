#ifndef SDIZO_P1_HEAPTEST_H
#define SDIZO_P1_HEAPTEST_H

#include <iostream>
#include <cassert>

#include "../data_structures/Heap.h"

using std::cout;
using std::endl;


class HeapTest {
public:
    void run();

private:
    void insertTest();

    void removeTest();

    void searchTest();

    void printTest();
};


#endif //SDIZO_P1_HEAPTEST_H
