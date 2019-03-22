cmake_minimum_required(VERSION 3.13)
project(SDiZO_p1)

set(CMAKE_CXX_STANDARD 11)

add_executable(SDiZO_p1 main.cpp data_structures/Table.cpp data_structures/Table.h Tests/TableTest.cpp Tests/TableTest.h data_structures/DoublyLinkedList.cpp data_structures/DoublyLinkedList.h Tests/DoublyLinkedListTest.cpp Tests/DoublyLinkedListTest.h data_structures/Heap.cpp data_structures/Heap.h Tests/HeapTest.cpp Tests/HeapTest.h)