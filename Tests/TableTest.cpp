//
// Created by Jakub Plona PL on 10.03.2019.
//

#include "TableTest.h"

void TableTest::run() {
    testInsertAtEnd();
    testSearch();
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
