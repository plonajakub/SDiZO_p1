//
// Created by Jakub Plona PL on 16.03.2019.
//

#include "DoublyLinkedList.h"

DoublyLinkedList::DoublyLinkedList() noexcept {
    sentry = new Node();
    size = 0;
}

DoublyLinkedList::~DoublyLinkedList() noexcept {

}

void DoublyLinkedList::insert(int index, int value) {

}

void DoublyLinkedList::insertAtStart(int value) {
    auto *newNode = new Node(value);
    newNode->next = sentry->next;
    sentry->next->prev = newNode;
    sentry->next = newNode;
    newNode->prev = sentry;
    ++size;
}

void DoublyLinkedList::insertAtEnd(int value) {
    auto *newNode = new Node(value);
    newNode->prev = sentry->prev;
    sentry->prev->next = newNode;
    sentry->prev = newNode;
    newNode->next = sentry;
    ++size;
}

void DoublyLinkedList::insertAfterValue(int searchValue, int insertValue) {

}

void DoublyLinkedList::remove(int index) {

}

void DoublyLinkedList::removeAtStart() {

}

void DoublyLinkedList::removeAtEnd() {

}

void DoublyLinkedList::removeByValue(int value) {

}

int DoublyLinkedList::search(int value) const {
    int returnIdx = -1;
    int currentIdx = 0;
    Node *it = sentry->next;
    while (!it->isSentry) {
        if (it->data == value) {
            returnIdx = currentIdx;
            break;
        }
        ++currentIdx;
        it = it->next;
    }
    return returnIdx;
}

std::string DoublyLinkedList::asString() const {
    std::string strDll;
    strDll.append("[");
    Node *it = sentry->next;
    while (!it->next->isSentry) {
        strDll.append(std::to_string(it->data));
        strDll.append(", ");
        it = it->next;
    }
    if (size != 0) {
        strDll.append(std::to_string(it->data));
    }
    strDll.append("]");
    return strDll;
}

std::ostream& operator<<(std::ostream &ostr, const DoublyLinkedList &dll) {
    ostr << dll.asString();
    return ostr;
}
