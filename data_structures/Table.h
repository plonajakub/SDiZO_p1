#ifndef SDIZO_P1_TABLE_H
#define SDIZO_P1_TABLE_H

#include <iostream>
#include <exception>
#include <string>


class Table {

public:
    Table() noexcept;

    ~Table() noexcept;

    // Inserts value into table on place described by index
    void insert(int index, int value);

    // Inserts value into table at end
    void insertAtEnd(int value);

    // Inserts value into table at start
    void insertAtStart(int value);

    // Remove value described by index from table
    void remove(int index);

    // Remove value from table from start
    void removeFromStart();

    // Remove value from table from end
    void removeFromEnd();

    // Linear search for value in the table
    // Returns VALUE_NOT_FOUND if value is not in the table
    // Otherwise returns value's index
    int search(int value) const;

    // Table's string representation
    std::string asString() const;

    // For accessing table's elements
    int &operator[](int index);

    // For accessing table's elements
    int &operator[](int index) const;

    int getSize() const;

    int getCapacity() const;

    // Returned by search() if value was not found
    static const int VALUE_NOT_FOUND = -1;

private:

    // Used to determine if the table should be enlarged
    static const int ENLARGEMENT_COEFFICIENT = 2;

    // Used to determine if the table should be reduced
    static constexpr double REDUCTION_COEFFICIENT = 0.25;

    // Numbers of elements in the table
    int size;

    // Numbers of possible elements to bo hold without enlarging the table
    int capacity;

    // First element's pointer
    int *table;

    // Calculates full factor (see implementation)
    double getFullFactor() const;

    // For test purposes
    friend class TableTest;
};

// Declared for convenience
std::ostream &operator<<(std::ostream &ostr, const Table &table);

#endif //SDIZO_P1_TABLE_H
