//
// Created by Jakub Plona PL on 17.03.2019.
//

#include "DoublyLinkedListTest.h"

void DoublyLinkedListTest::run() {
    testInsert();
    testInsertAtStart();
    testInsertAtEnd();
    testInsertAfterValue();
    testSearch();
}

void DoublyLinkedListTest::testInsert() {
    cout << "*** DoublyLinkedListTest::testInsert start ***" << endl;
    DoublyLinkedList dll;

    assert(dll.sentry != nullptr);
    assert(dll.sentry->next == dll.sentry);
    assert(dll.sentry->prev == dll.sentry);
    assert(dll.sentry->data == INT_MAX);
    assert(dll.sentry->isSentry);
    cout << dll << endl;

    dll.insert(0, 5);
    assert(dll.sentry->next == dll.sentry->prev);
    assert(!dll.sentry->next->isSentry);
    assert(dll.sentry->next->next->isSentry);
    assert(dll.size == 1);
    cout << dll << endl;

    dll.insert(1, 10);
    assert(dll.sentry->next == dll.sentry->prev->prev);
    assert(dll.sentry->next->next->next->isSentry);
    assert(dll.sentry->prev->prev->prev->isSentry);
    assert(dll.size == 2);
    cout << dll << endl;

    dll.insert(1, -5);
    assert(dll.sentry->next == dll.sentry->prev->prev->prev);
    assert(dll.sentry->next->next->next->next->isSentry);
    assert(dll.sentry->prev->prev->prev->prev->isSentry);
    assert(dll.size == 3);
    cout << dll << endl;

    dll.insert(2, -147);
    assert(dll.search(-147) == 2);
    cout << dll << endl;

    dll.insert(4, 28);
    assert(dll.search(28) == 4);
    cout << dll << endl;
    cout << "*** DoublyLinkedListTest::testInsert end ***" << endl;
}

void DoublyLinkedListTest::testInsertAtEnd() {
    cout << "*** DoublyLinkedListTest::testInsertAtEnd start ***" << endl;
    DoublyLinkedList dll;

    assert(dll.sentry != nullptr);
    assert(dll.sentry->next == dll.sentry);
    assert(dll.sentry->prev == dll.sentry);
    assert(dll.sentry->data == INT_MAX);
    assert(dll.sentry->isSentry);
    cout << dll << endl;

    dll.insertAtEnd(5);
    assert(dll.sentry->prev == dll.sentry->next);
    assert(!dll.sentry->prev->isSentry);
    assert(dll.sentry->prev->prev->isSentry);
    assert(dll.size == 1);
    cout << dll << endl;

    dll.insertAtEnd(10);
    assert(dll.sentry->prev == dll.sentry->next->next);
    assert(dll.sentry->prev->prev->prev->isSentry);
    assert(dll.sentry->next->next->next->isSentry);
    assert(dll.size == 2);
    cout << dll << endl;

    dll.insertAtEnd(15);
    assert(dll.sentry->prev == dll.sentry->next->next->next);
    assert(dll.sentry->prev->prev->prev->prev->isSentry);
    assert(dll.sentry->next->next->next->next->isSentry);
    assert(dll.size == 3);
    cout << dll << endl;
    cout << "*** DoublyLinkedListTest::testInsertAtEnd end ***" << endl;
}

void DoublyLinkedListTest::testInsertAtStart() {
    cout << "*** DoublyLinkedListTest::testInsertAtStart start ***" << endl;
    DoublyLinkedList dll;

    assert(dll.sentry != nullptr);
    assert(dll.sentry->next == dll.sentry);
    assert(dll.sentry->prev == dll.sentry);
    assert(dll.sentry->data == INT_MAX);
    assert(dll.sentry->isSentry);
    cout << dll << endl;

    dll.insertAtStart(5);
    assert(dll.sentry->next == dll.sentry->prev);
    assert(!dll.sentry->next->isSentry);
    assert(dll.sentry->next->next->isSentry);
    assert(dll.size == 1);
    cout << dll << endl;

    dll.insertAtStart(10);
    assert(dll.sentry->next == dll.sentry->prev->prev);
    assert(dll.sentry->next->next->next->isSentry);
    assert(dll.sentry->prev->prev->prev->isSentry);
    assert(dll.size == 2);
    cout << dll << endl;

    dll.insertAtStart(15);
    assert(dll.sentry->next == dll.sentry->prev->prev->prev);
    assert(dll.sentry->next->next->next->next->isSentry);
    assert(dll.sentry->prev->prev->prev->prev->isSentry);
    assert(dll.size == 3);
    cout << dll << endl;
    cout << "*** DoublyLinkedListTest::testInsertAtStart end ***" << endl;
}

void DoublyLinkedListTest::testInsertAfterValue() {
    cout << "*** DoublyLinkedListTest::testInsertAfterValue start ***" << endl;
    DoublyLinkedList dll;

    assert(dll.sentry != nullptr);
    assert(dll.sentry->next == dll.sentry);
    assert(dll.sentry->prev == dll.sentry);
    assert(dll.sentry->data == INT_MAX);
    assert(dll.sentry->isSentry);
    cout << dll << endl;

    dll.insertAfterValue(0, 5);
    assert(dll.sentry->next == dll.sentry->prev);
    assert(!dll.sentry->next->isSentry);
    assert(dll.sentry->next->next->isSentry);
    assert(dll.size == 1);
    cout << dll << endl;

    dll.insertAfterValue(5, 10);
    assert(dll.sentry->next == dll.sentry->prev->prev);
    assert(dll.sentry->next->next->next->isSentry);
    assert(dll.sentry->prev->prev->prev->isSentry);
    assert(dll.size == 2);
    cout << dll << endl;

    dll.insertAfterValue(5, -5);
    assert(dll.sentry->next == dll.sentry->prev->prev->prev);
    assert(dll.sentry->next->next->next->next->isSentry);
    assert(dll.sentry->prev->prev->prev->prev->isSentry);
    assert(dll.size == 3);
    cout << dll << endl;

    dll.insertAfterValue(10, -147);
    assert(dll.search(-147) == 3);
    cout << dll << endl;

    dll.insertAfterValue(4, 28);
    assert(dll.search(28) == 0);
    cout << dll << endl;
    cout << "*** DoublyLinkedListTest::testInsertAfterValue end ***" << endl;
}

void DoublyLinkedListTest::testRemove() {

}

void DoublyLinkedListTest::testRemoveAtStart() {

}

void DoublyLinkedListTest::testRemoveAtEnd() {

}

void DoublyLinkedListTest::testSearch() {
    cout << "*** DoublyLinkedListTest::testSearch start ***" << endl;

    DoublyLinkedList dll;

    assert(dll.search(-5) == -1);

    dll.insertAtEnd(5);
    dll.insertAtEnd(-15);
    dll.insertAtEnd(0);
    dll.insertAtEnd(456);
    dll.insertAtEnd(-147);
    cout << dll << endl;

    assert(dll.search(-5) == -1);
    assert(dll.search(5) == 0);
    assert(dll.search(-147) == 4);
    assert(dll.search(0) == 2);
    cout << "*** DoublyLinkedListTest::testSearch end ***" << endl;
}
