cmake_minimum_required(VERSION 3.13)
project(SDiZO_p1)

set(CMAKE_CXX_STANDARD 11)

add_executable(SDiZO_p1 main.cpp data_structures/Table.cpp data_structures/Table.h tests/TableTest.cpp tests/TableTest.h data_structures/DoublyLinkedList.cpp data_structures/DoublyLinkedList.h tests/DoublyLinkedListTest.cpp tests/DoublyLinkedListTest.h data_structures/Heap.cpp data_structures/Heap.h tests/HeapTest.cpp tests/HeapTest.h data_structures/RedBlackTree.cpp data_structures/RedBlackTree.h tests/RedBlackTreeTest.cpp tests/RedBlackTreeTest.h)