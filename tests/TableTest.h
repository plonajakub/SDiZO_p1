#ifndef SDIZO_P1_TABLETEST_H
#define SDIZO_P1_TABLETEST_H

#include <iostream>
#include <cassert>

#include "../data_structures/Table.h"

using std::cout;
using std::endl;


class TableTest {

public:
    void run();

private:
    void testInsert();

    void testInsertAtEnd();

    void testInsertAtStart();

    void testRemove();

    void testRemoveAtStart();

    void testRemoveAtEnd();

    void testSearch();
};


#endif //SDIZO_P1_TABLETEST_H
