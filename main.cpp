#include "tests/TableTest.h"
#include "tests/DoublyLinkedListTest.h"
#include "tests/HeapTest.h"
#include "tests/RedBlackTreeTest.h"

int main() {
    TableTest tabTest;
    tabTest.run();

    DoublyLinkedListTest dllTest;
    dllTest.run();

    HeapTest heapTest;
    heapTest.run();

    RedBlackTreeTest rbtTest;
    rbtTest.run();

    return 0;
}