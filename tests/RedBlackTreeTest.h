#ifndef SDIZO_P1_REDBLACKTREETEST_H
#define SDIZO_P1_REDBLACKTREETEST_H

#include <iostream>
#include <cassert>

#include "../data_structures/RedBlackTree.h"

using std::cout;
using std::endl;


class RedBlackTreeTest {
public:
    void run();

private:
    void printTreeTest();

    void searchTest();

    void insertTest();

    void removeTest();
};


#endif //SDIZO_P1_REDBLACKTREETEST_H
