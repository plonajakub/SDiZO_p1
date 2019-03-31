#include "RedBlackTreeTest.h"

void RedBlackTreeTest::run() {
    printTreeTest();
    searchTest();
    insertTest();
    removeTest();
}

void RedBlackTreeTest::printTreeTest() {
    cout << "*** RedBlackTreeTest::printTreeTest() start ***" << endl;

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
    rbt.insert(87);
    rbt.insert(-23);
    rbt.insert(-87);
    rbt.insert(1456);
    cout << rbt << endl;

    cout << "*** RedBlackTreeTest::printTreeTest() end ***" << endl;
}

void RedBlackTreeTest::searchTest() {
    cout << "*** RedBlackTreeTest::searchTest() start ***" << endl;

    RedBlackTree rbt;

    rbt.insert(15);
    assert(rbt.search(15) == rbt.root);
    cout << rbt << endl;

    rbt.insert(27);
    assert(rbt.search(27) == rbt.root->right);
    cout << rbt << endl;

    rbt.insert(-14);
    assert(rbt.search(-14) == rbt.root->left);
    cout << rbt << endl;

    rbt.insert(0);
    assert(rbt.search(0) == rbt.root->left->right);
    cout << rbt << endl;

    cout << "*** RedBlackTreeTest::searchTest() end ***" << endl;
}

void RedBlackTreeTest::insertTest() {
    cout << "*** RedBlackTreeTest::insertTest() start ***" << endl;

    RedBlackTree rbt;
    assert(rbt.root == &(rbt.sentry));
    assert(rbt.root->left == &(rbt.sentry));
    assert(rbt.root->right == &(rbt.sentry));
    assert(rbt.root->parent == &(rbt.sentry));
    assert(rbt.root->color == 'B');
    cout << rbt << endl;

    rbt.insert(15);
    assert(rbt.root->key == 15);
    assert(rbt.root->left == &(rbt.sentry));
    assert(rbt.root->right == &(rbt.sentry));
    assert(rbt.root->parent == &(rbt.sentry));
    assert(rbt.root->color == 'B');
    cout << rbt << endl;

    rbt.insert(27);
    assert(rbt.root->key == 15);
    assert(rbt.root->left == &(rbt.sentry));
    assert(rbt.root->right->key == 27);
    assert(rbt.root->right->color == 'R');
    assert(rbt.root->parent == &(rbt.sentry));
    cout << rbt << endl;

    rbt.insert(-14);
    assert(rbt.root->key == 15);
    assert(rbt.root->left->key == -14);
    assert(rbt.root->left->color == 'R');
    assert(rbt.root->right->key == 27);
    assert(rbt.root->parent == &(rbt.sentry));
    cout << rbt << endl;

    rbt.insert(16);
    assert(rbt.root->key == 15);
    assert(rbt.root->right->left->key == 16);
    assert(rbt.root->right->left->color == 'R');
    cout << rbt << endl;

    cout << "*** RedBlackTreeTest::insertTest() end ***" << endl;
}

void RedBlackTreeTest::removeTest() {
    cout << "*** RedBlackTreeTest::printTreeTest() start ***" << endl;

    RedBlackTree rbt;
    rbt.insert(15);
    rbt.insert(27);
    rbt.insert(-14);
    rbt.insert(16);
    cout << rbt << endl;

    rbt.remove(15);
    assert(rbt.root->key == 16);
    assert(rbt.root->color == 'B');
    assert(rbt.root->left->key == -14);
    assert(rbt.root->left->color == 'B');
    assert(rbt.root->right->key == 27);
    assert(rbt.root->right->color == 'B');
    cout << rbt << endl;

    rbt.remove(16);
    assert(rbt.root->key == 27);
    assert(rbt.root->color == 'B');
    assert(rbt.root->left->key == -14);
    assert(rbt.root->left->color == 'R');
    cout << rbt << endl;

    rbt.remove(-14);
    assert(rbt.root->key == 27);
    assert(rbt.root->color == 'B');
    cout << rbt << endl;

    rbt.remove(27);
    assert(rbt.root == &(rbt.sentry));
    assert(rbt.root->left == &(rbt.sentry));
    assert(rbt.root->right == &(rbt.sentry));
    assert(rbt.root->parent == &(rbt.sentry));
    assert(rbt.root->color == 'B');
    cout << rbt << endl;

    cout << "*** RedBlackTreeTest::printTreeTest() end ***" << endl;
}
