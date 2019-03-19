//
// Created by Jakub Plona PL on 16.03.2019.
//

#include "DoublyLinkedList.h"

DoublyLinkedList::DoublyLinkedList() noexcept {
    sentry = new Node();
    size = 0;
}

DoublyLinkedList::~DoublyLinkedList() noexcept {
    auto *it = sentry->next;
    while (!it->isSentry) {
        it = it->next;
        delete it->prev;
    }
    delete sentry;
}

void DoublyLinkedList::insert(int index, int value) {
    if (index < 0 || index > size) {
        throw std::out_of_range("Index out of bounds");
    }
    auto *newNode = new Node(value);
    auto *it = sentry->next;
    for (int i = 0; i != index; ++i) {
        it = it->next;
    }
    newNode->prev = it->prev;
    it->prev->next = newNode;
    it->prev = newNode;
    newNode->next = it;
    ++size;
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
    for (auto *it = sentry->next; !it->isSentry; it = it->next) {
        if (it->data == searchValue) {
            auto *newNode = new Node(insertValue);
            newNode->next = it->next;
            it->next->prev = newNode;
            it->next = newNode;
            newNode->prev = it;
            ++size;
            return;
        }
    }
    this->insertAtStart(insertValue);
}

void DoublyLinkedList::remove(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    Node *it = sentry->next;
    for (int i = 0; i != index; ++i) {
        it = it->next;
    }
    it->prev->next = it->next;
    it->next->prev = it->prev;
    delete it;
    --size;
}

void DoublyLinkedList::removeAtStart() {
    if (size == 0) {
        throw std::out_of_range("List is empty");
    }
    auto *head = sentry->next;
    sentry->next = head->next;
    head->next->prev = sentry;
    delete head;
    --size;
}

void DoublyLinkedList::removeAtEnd() {
    if (size == 0) {
        throw std::out_of_range("List is empty");
    }
    auto *tail = sentry->prev;
    sentry->prev = tail->prev;
    tail->prev->next = sentry;
    delete tail;
    --size;
}

void DoublyLinkedList::removeByValue(int value) {
    try {
        this->remove(this->search(value));
    } catch (const std::out_of_range &e) {
        // No action if value does not exist
    }
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
