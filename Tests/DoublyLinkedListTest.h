//
// Created by Jakub Plona PL on 17.03.2019.
//

#ifndef SDIZO_P1_DOUBLYLINKEDLISTTEST_H
#define SDIZO_P1_DOUBLYLINKEDLISTTEST_H

#include "../data_structures/DoublyLinkedList.h"
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

class DoublyLinkedListTest {

public:
    void run();

private:
    void testInsert();
    void testInsertAtEnd();
    void testInsertAtStart();
    void testInsertAfterValue();
    void testRemove();
    void testRemoveAtStart();
    void testRemoveAtEnd();
    void testRemoveByValue();
    void testSearch();
};


#endif //SDIZO_P1_DOUBLYLINKEDLISTTEST_H
