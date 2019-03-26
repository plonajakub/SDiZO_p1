//
// Created by Jakub Plona PL on 10.03.2019.
//

#include "TableTest.h"

void TableTest::run() {
    testInsert();
    testInsertAtStart();
    testInsertAtEnd();
    testRemove();
    testRemoveAtStart();
    testRemoveAtEnd();
    testSearch();
}

void TableTest::testInsert() {
    cout << "*** TableTest::testInsert() start ***" << endl;

    Table table;
    assert(table.table == nullptr);
    assert(table.getSize() == 0);
    assert(table.getCapacity() == 0);

    table.insert(0, 1);
    assert(table.table != nullptr);
    assert(table.getSize() == 1);
    assert(table.getCapacity() == 1);
    assert(table.table[0] == 1);
    cout << table << endl;

    table.insert(0, 2);
    assert(table.table != nullptr);
    assert(table.getSize() == 2);
    assert(table.getCapacity() == 2);
    assert(table.table[1] == 1);
    cout << table << endl;

    table.insert(1, 3);
    assert(table.table != nullptr);
    assert(table.getSize() == 3);
    assert(table.getCapacity() == 4);
    assert(table.table[1] == 3);
    cout << table << endl;

    table.insert(3, -46);
    assert(table.table != nullptr);
    assert(table.getSize() == 4);
    assert(table.getCapacity() == 4);
    assert(table.table[3] == -46);
    cout << table << endl;

    table.insert(3, 100);
    assert(table.table != nullptr);
    assert(table.getSize() == 5);
    assert(table.getCapacity() == 8);
    assert(table.table[4] == -46);
    cout << table << endl;

    table.insert(2, 15);
    assert(table.table != nullptr);
    assert(table.getSize() == 6);
    assert(table.getCapacity() == 8);
    assert(table.table[3] == 1);
    cout << table << endl;

    table.insert(2, -15);
    assert(table.table != nullptr);
    assert(table.getSize() == 7);
    assert(table.getCapacity() == 8);
    assert(table.table[6] == -46);
    cout << table << endl;

    table.insert(0, 27);
    assert(table.table != nullptr);
    assert(table.getSize() == 8);
    assert(table.getCapacity() == 8);
    assert(table.table[1] == 2);
    cout << table << endl;

    table.insert(8, 79);
    assert(table.table != nullptr);
    assert(table.getSize() == 9);
    assert(table.getCapacity() == 16);
    assert(table.table[8] == 79);
    cout << table << endl;

    cout << "*** TableTest::testInsert() end ***" << endl;
}

void TableTest::testInsertAtStart() {
    cout << "*** TableTest::testInsertAtStart() start ***" << endl;

    Table table;
    assert(table.table == nullptr);
    assert(table.getSize() == 0);
    assert(table.getCapacity() == 0);

    table.insertAtStart(5);
    assert(table.table != nullptr);
    assert(table.getSize() == 1);
    assert(table.getCapacity() == 1);
    assert(table.table[0] == 5);
    cout << table << endl;

    table.insertAtStart(10);
    assert(table.table != nullptr);
    assert(table.getSize() == 2);
    assert(table.getCapacity() == 2);
    assert(table.table[1] == 5);
    cout << table << endl;

    table.insertAtStart(7);
    assert(table.table != nullptr);
    assert(table.getSize() == 3);
    assert(table.getCapacity() == 4);
    assert(table.table[1] == 10);
    cout << table << endl;

    table.insertAtStart(-46);
    assert(table.table != nullptr);
    assert(table.getSize() == 4);
    assert(table.getCapacity() == 4);
    assert(table.table[3] == 5);
    cout << table << endl;

    table.insertAtStart(0);
    assert(table.table != nullptr);
    assert(table.getSize() == 5);
    assert(table.getCapacity() == 8);
    assert(table.table[2] == 7);
    cout << table << endl;

    cout << "*** TableTest::testInsertAtStart() end ***" << endl;
}

void TableTest::testInsertAtEnd() {
    cout << "*** TableTest::testInsertAtEnd() start ***" << endl;

    Table table;
    assert(table.table == nullptr);
    assert(table.getSize() == 0);
    assert(table.getCapacity() == 0);

    table.insertAtEnd(5);
    assert(table.table != nullptr);
    assert(table.getSize() == 1);
    assert(table.getCapacity() == 1);
    assert(table.table[0] == 5);
    cout << table << endl;

    table.insertAtEnd(10);
    assert(table.table != nullptr);
    assert(table.getSize() == 2);
    assert(table.getCapacity() == 2);
    assert(table.table[1] == 10);
    cout << table << endl;

    table.insertAtEnd(7);
    assert(table.table != nullptr);
    assert(table.getSize() == 3);
    assert(table.getCapacity() == 4);
    assert(table.table[2] == 7);
    cout << table << endl;

    table.insertAtEnd(-46);
    assert(table.table != nullptr);
    assert(table.getSize() == 4);
    assert(table.getCapacity() == 4);
    assert(table.table[3] == -46);
    cout << table << endl;

    table.insertAtEnd(0);
    assert(table.table != nullptr);
    assert(table.getSize() == 5);
    assert(table.getCapacity() == 8);
    assert(table.table[4] == 0);
    cout << table << endl;

    cout << "*** TableTest::testInsertAtEnd() end ***" << endl;
}

void TableTest::testRemove() {
    cout << "*** TableTest::testRemove() start ***" << endl;

    Table table;
    table.insertAtEnd(5);
    table.insertAtEnd(20);
    table.insertAtEnd(-5);
    table.insertAtEnd(0);
    table.insertAtEnd(-15);

    assert(table.table != nullptr);
    assert(table.getSize() == 5);
    assert(table.getCapacity() == 8);
    assert(table.table[0] == 5);
    cout << table << endl;

    table.remove(0);
    assert(table.table != nullptr);
    assert(table.getSize() == 4);
    assert(table.getCapacity() == 8);
    assert(table.table[0] == 20);
    cout << table << endl;

    table.remove(1);
    assert(table.table != nullptr);
    assert(table.getSize() == 3);
    assert(table.getCapacity() == 8);
    assert(table.table[1] == 0);
    cout << table << endl;

    table.remove(0);
    assert(table.table != nullptr);
    assert(table.getSize() == 2);
    assert(table.getCapacity() == 8);
    assert(table.table[0] == 0);
    cout << table << endl;

    table.remove(1);
    assert(table.table != nullptr);
    assert(table.getSize() == 1);
    assert(table.getCapacity() == 4);
    assert(table.table[0] == 0);
    cout << table << endl;

    table.remove(0);
    assert(table.table == nullptr);
    assert(table.getSize() == 0);
    assert(table.getCapacity() == 0);
    cout << table << endl;

    cout << "*** TableTest::testRemove() end ***" << endl;
}

void TableTest::testSearch() {
    cout << "*** TableTest::testSearch() start ***" << endl;

    Table table;
    table.insertAtEnd(5);
    table.insertAtEnd(20);
    table.insertAtEnd(-5);
    table.insertAtEnd(0);

    assert(table.search(-123) == -1);
    assert(table.search(20) == 1);
    assert(table.search(0) == 3);

    cout << "*** TableTest::testSearch() end ***" << endl;
}

void TableTest::testRemoveAtStart() {
    cout << "*** TableTest::testRemoveAtStart() start ***" << endl;

    Table table;
    table.insertAtEnd(5);
    table.insertAtEnd(20);
    table.insertAtEnd(-5);
    table.insertAtEnd(0);
    table.insertAtEnd(-15);

    assert(table.table != nullptr);
    assert(table.getSize() == 5);
    assert(table.getCapacity() == 8);
    assert(table.table[0] == 5);
    cout << table << endl;

    table.removeFromStart();
    assert(table.table != nullptr);
    assert(table.getSize() == 4);
    assert(table.getCapacity() == 8);
    assert(table.table[0] == 20);
    cout << table << endl;

    table.removeFromStart();
    assert(table.table != nullptr);
    assert(table.getSize() == 3);
    assert(table.getCapacity() == 8);
    assert(table.table[1] == 0);
    cout << table << endl;

    table.removeFromStart();
    assert(table.table != nullptr);
    assert(table.getSize() == 2);
    assert(table.getCapacity() == 8);
    assert(table.table[0] == 0);
    cout << table << endl;

    table.removeFromStart();
    assert(table.table != nullptr);
    assert(table.getSize() == 1);
    assert(table.getCapacity() == 4);
    assert(table.table[0] == -15);
    cout << table << endl;

    table.removeFromStart();
    assert(table.table == nullptr);
    assert(table.getSize() == 0);
    assert(table.getCapacity() == 0);
    cout << table << endl;
    cout << "*** TableTest::testRemoveAtStart() end ***" << endl;
}

void TableTest::testRemoveAtEnd() {
    cout << "*** TableTest::testRemoveAtEnd() start ***" << endl;

    Table table;
    table.insertAtEnd(5);
    table.insertAtEnd(20);
    table.insertAtEnd(-5);
    table.insertAtEnd(0);
    table.insertAtEnd(-15);

    assert(table.table != nullptr);
    assert(table.getSize() == 5);
    assert(table.getCapacity() == 8);
    assert(table.table[4] == -15);
    cout << table << endl;

    table.removeFromEnd();
    assert(table.table != nullptr);
    assert(table.getSize() == 4);
    assert(table.getCapacity() == 8);
    assert(table.table[3] == 0);
    cout << table << endl;

    table.removeFromEnd();
    assert(table.table != nullptr);
    assert(table.getSize() == 3);
    assert(table.getCapacity() == 8);
    assert(table.table[2] == -5);
    cout << table << endl;

    table.removeFromEnd();
    assert(table.table != nullptr);
    assert(table.getSize() == 2);
    assert(table.getCapacity() == 8);
    assert(table.table[1] == 20);
    cout << table << endl;

    table.removeFromEnd();
    assert(table.table != nullptr);
    assert(table.getSize() == 1);
    assert(table.getCapacity() == 4);
    assert(table.table[0] == 5);
    cout << table << endl;

    table.removeFromEnd();
    assert(table.table == nullptr);
    assert(table.getSize() == 0);
    assert(table.getCapacity() == 0);
    cout << table << endl;

    cout << "*** TableTest::testRemoveAtEnd() end ***" << endl;
}
