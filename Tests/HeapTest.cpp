//
// Created by Jakub Plona PL on 22.03.2019.
//

#include "HeapTest.h"

void HeapTest::run() {
    insertTest();
    removeTest();
    searchTest();
    printTest();
}

void HeapTest::insertTest() {
    cout << "*** HeapTest::insertTest() start ***" << endl;
    Heap heap;
    cout << heap << endl;

    heap.insert(0);
    cout << heap << endl;
    assert(heap.table.getSize() == 1);
    assert(heap.table[0] == 0);

    heap.insert(1);
    cout << heap << endl;
    assert(heap.table.getSize() == 2);
    assert(heap.table[0] == 1);
    assert(heap.table[1] == 0);

    heap.insert(2);
    cout << heap << endl;
    assert(heap.table.getSize() == 3);
    assert(heap.table[0] == 2);
    assert(heap.table[1] == 0);
    assert(heap.table[2] == 1);

    heap.insert(3);
    cout << heap << endl;
    assert(heap.table.getSize() == 4);
    assert(heap.table[0] == 3);
    assert(heap.table[1] == 2);
    assert(heap.table[2] == 1);
    assert(heap.table[3] == 0);
    cout << "*** HeapTest::insertTest() end ***" << endl;
}

void HeapTest::removeTest() {
    cout << "*** HeapTest::removeTest() start ***" << endl;

    auto *heap = new Heap;
    heap->insert(0);
    heap->insert(1);
    heap->insert(2);
    heap->insert(3);
    heap->insert(4);
    heap->insert(5);
    heap->insert(6);
    heap->insert(7);
    cout << "Heap No. 1" << endl;
    cout << *heap << endl;

    heap->remove(0);
    cout << *heap << endl;
    assert(heap->table.getSize() == 7);

    heap->remove(7);
    cout << *heap << endl;
    assert(heap->table.getSize() == 6);
    assert(heap->table[0] == 6);
    assert(heap->table[1] == 4);

    heap->remove(4);
    cout << *heap << endl;
    assert(heap->table.getSize() == 5);
    assert(heap->table[0] == 6);
    assert(heap->table[1] == 3);
    assert(heap->table[2] == 5);
    assert(heap->table[3] == 1);
    assert(heap->table[4] == 2);

    delete heap;

    heap = new Heap;
    heap->insert(100);
    heap->insert(70);
    heap->insert(90);
    heap->insert(20);
    heap->insert(19);
    heap->insert(89);
    heap->insert(88);
    heap->insert(16);
    heap->insert(15);
    heap->insert(14);
    heap->insert(13);
    heap->insert(79);
    heap->insert(78);
    heap->insert(76);
    heap->insert(75);
    cout << "Heap No. 2" << endl;
    cout << *heap << endl;

    heap->remove(20);
    assert(heap->table.getSize() == 14);
    assert(heap->table[1] == 75);
    cout << *heap << endl;
    cout << "*** HeapTest::removeTest() end ***" << endl;
}

void HeapTest::searchTest() {
    cout << "*** HeapTest::searchTest() start ***" << endl;

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

    assert(heap.search(7) == 0);
    assert(heap.search(6) == 1);
    assert(heap.search(5) == 2);
    assert(heap.search(3) == 3);
    assert(heap.search(2) == 4);
    assert(heap.search(1) == 5);
    assert(heap.search(4) == 6);
    assert(heap.search(0) == 7);
    assert(heap.search(-5) == -1);
    assert(heap.search(125) == -1);

    cout << "*** HeapTest::searchTest() end ***" << endl;
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
