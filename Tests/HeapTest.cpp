//
// Created by Jakub Plona PL on 22.03.2019.
//

#include "HeapTest.h"

void HeapTest::run() {
    printTest();
}

void HeapTest::insertTest() {

}

void HeapTest::removeTest() {

}

void HeapTest::searchTest() {

}

void HeapTest::printTest() {
    cout << "*** HeapTest::printTest() start ***" << endl;

    Heap heap;
    heap.insert(0);
    heap.insert(1);
    heap.insert(2);
    heap.insert(3);
    heap.insert(4);
    heap.insert(5);
    heap.insert(6);
    heap.insert(7);

    cout << heap.table << endl;
    cout << heap << endl;
    cout << "*** HeapT1est::printTest() end ***" << endl;
}
