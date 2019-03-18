//
// Created by Jakub Plona PL on 16.03.2019.
//

#ifndef SDIZO_P1_DOUBLYLINKEDLIST_H
#define SDIZO_P1_DOUBLYLINKEDLIST_H

#include <climits>
#include <string>
#include <iostream>
#include <exception>

class Node {
public:
    Node *next;
    Node *prev;
    int data;
    bool isSentry;
    Node() : next(this), prev(this), data(INT_MAX), isSentry(true) {}
    explicit Node(int data) : next(nullptr), prev(nullptr), data(data), isSentry(false) {}
    Node(Node *next, Node *prev, int data) : next(next), prev(prev), data(data), isSentry(false) {}
};

class DoublyLinkedList {
public:
    DoublyLinkedList() noexcept;
    ~DoublyLinkedList() noexcept;
    void insert(int index, int value);
    void insertAtStart(int value);
    void insertAtEnd(int value);
    void insertAfterValue(int searchValue, int insertValue);
    void remove(int index);
    void removeAtStart();
    void removeAtEnd();
    void removeByValue(int value);
    int search(int value) const;
    std::string asString() const;

private:
    Node *sentry;
    int size;

    friend class DoublyLinkedListTest;
};

std::ostream& operator<<(std::ostream &ostr, const DoublyLinkedList &dll);


#endif //SDIZO_P1_DOUBLYLINKEDLIST_H
