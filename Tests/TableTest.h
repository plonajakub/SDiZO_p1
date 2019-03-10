//
// Created by Jakub Plona PL on 10.03.2019.
//

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
    void testInsertAtEnd();
    void testSearch();
};


#endif //SDIZO_P1_TABLETEST_H
