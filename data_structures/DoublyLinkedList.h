#ifndef SDIZO_P1_DOUBLYLINKEDLIST_H
#define SDIZO_P1_DOUBLYLINKEDLIST_H

#include <climits>
#include <string>
#include <iostream>
#include <exception>


// Represents single node of the list
class Node {
public:
    // Next node's pointer
    Node *next;

    // Previous node's pointer
    Node *prev;

    int data;

    // Sentry marker
    bool isSentry;

    // This constructor is used to create sentry node
    Node() : next(this), prev(this), data(INT_MAX), isSentry(true) {}

    // Mainly used constructor for new nodes creation
    explicit Node(int data) : next(nullptr), prev(nullptr), data(data), isSentry(false) {}
};


class DoublyLinkedList {
public:
    DoublyLinkedList() noexcept;

    ~DoublyLinkedList() noexcept;

    // Inserts new node with data equal to value into the place described by index
    void insert(int index, int value);

    // Inserts new node with data equal to value at beginning of the list
    void insertAtStart(int value);

    // Inserts new node with data equal to value at end of the list
    void insertAtEnd(int value);

    // Inserts new node with data equal to insertValue after the node described by data equal to searchValue
    // If searchValue does not exist this method inserts new node at the beginning of the list
    void insertAfterValue(int searchValue, int insertValue);

    // Removes node from place described by index
    void remove(int index);

    // Removes node from beginning of the list
    void removeFromStart();

    // Removes node from end of the list
    void removeFromEnd();

    // Removes node with data equal to value
    void removeByValue(int value);

    // Performs linear search on the list and returns value's index
    // If value does not exist VALUE_NOT_FOUND is returned
    int search(int value) const;

    // Returns list's size
    int getSize() const;

    // Makes list's string representation
    std::string asString() const;

    // Returned by search() if value was not found in the list
    static const int VALUE_NOT_FOUND = -1;
private:

    // Sentry's pointer
    Node *sentry;

    // Number of elements in the list
    int size;

    // For test purposes only
    friend class DoublyLinkedListTest;
};

// Declared for convenience
std::ostream &operator<<(std::ostream &ostr, const DoublyLinkedList &dll);


#endif //SDIZO_P1_DOUBLYLINKEDLIST_H
