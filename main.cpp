#include "tests/TableTest.h"
#include "tests/DoublyLinkedListTest.h"
#include "tests/HeapTest.h"

int main() {
    TableTest tabTest;
    tabTest.run();

    DoublyLinkedListTest dllTest;
    dllTest.run();

    HeapTest heapTest;
    heapTest.run();
    return 0;
}