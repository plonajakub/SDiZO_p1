#include "RedBlackTreeTest.h"

void RedBlackTreeTest::run() {
    printTreeTest();
}

void RedBlackTreeTest::printTreeTest() {
    cout << " *** RedBlackTreeTest::printTreeTest() start *** " << endl;

    RedBlackTree rbt;
    rbt.insert(15);
    rbt.insert(27);
    rbt.insert(-14);
    rbt.insert(0);
    rbt.insert(87);
    rbt.insert(-147);
    rbt.insert(19);
    rbt.insert(200);
    rbt.insert(5);
    cout << rbt << endl;

    cout << " *** RedBlackTreeTest::printTreeTest() end *** " << endl;
}

void RedBlackTreeTest::searchTest() {

}

void RedBlackTreeTest::insertTest() {

}

void RedBlackTreeTest::removeTest() {

}
