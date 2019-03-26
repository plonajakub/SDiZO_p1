#include "DoublyLinkedList.h"


DoublyLinkedList::DoublyLinkedList() noexcept {
    sentry = new Node();
    size = 0;
}

DoublyLinkedList::~DoublyLinkedList() noexcept {
    // Free memory
    auto *it = sentry->next;
    while (!it->isSentry) {
        it = it->next;
        delete it->prev;
    }
    delete sentry;
}

void DoublyLinkedList::insert(int index, int value) {
    // Check if index is valid
    if (index < 0 || index > size) {
        throw std::out_of_range("Index out of bounds");
    }

    auto *newNode = new Node(value);
    auto *it = sentry->next;

    // Find proper place for the node based on index
    for (int i = 0; i != index; ++i) {
        it = it->next;
    }

    // Insert the new node into the list
    newNode->prev = it->prev;
    it->prev->next = newNode;
    it->prev = newNode;
    newNode->next = it;
    ++size;
}

void DoublyLinkedList::insertAtStart(int value) {
    auto *newNode = new Node(value);

    // Insert the new node into the list
    newNode->next = sentry->next;
    sentry->next->prev = newNode;
    sentry->next = newNode;
    newNode->prev = sentry;
    ++size;
}

void DoublyLinkedList::insertAtEnd(int value) {
    auto *newNode = new Node(value);

    // Insert the new node into the list
    newNode->prev = sentry->prev;
    sentry->prev->next = newNode;
    sentry->prev = newNode;
    newNode->next = sentry;
    ++size;
}

void DoublyLinkedList::insertAfterValue(int searchValue, int insertValue) {
    // Find proper place for a new node based on searchValue
    for (auto *it = sentry->next; !it->isSentry; it = it->next) {
        if (it->data == searchValue) {
            // searchValue found -> insert the new node
            auto *newNode = new Node(insertValue);
            newNode->next = it->next;
            it->next->prev = newNode;
            it->next = newNode;
            newNode->prev = it;
            ++size;
            return;
        }
    }
    // searchValue not found -> insert the new node at beginning of the list
    this->insertAtStart(insertValue);
}

void DoublyLinkedList::remove(int index) {
    // Check if index is valid
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }

    // Find a node to be deleted
    Node *it = sentry->next;
    for (int i = 0; i != index; ++i) {
        it = it->next;
    }

    // Delete the node
    it->prev->next = it->next;
    it->next->prev = it->prev;
    delete it;
    --size;
}

void DoublyLinkedList::removeAtStart() {
    // Check if list is empty
    if (size == 0) {
        throw std::out_of_range("List is empty");
    }

    // Remove the node at start of the list
    auto *head = sentry->next;
    sentry->next = head->next;
    head->next->prev = sentry;
    delete head;
    --size;
}

void DoublyLinkedList::removeAtEnd() {
    // Check if list is empty
    if (size == 0) {
        throw std::out_of_range("List is empty");
    }

    // Remove the node at end of the list
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
    int returnIdx = VALUE_NOT_FOUND;
    int currentIdx = 0;
    Node *it = sentry->next;

    // Perform linear search
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

std::ostream &operator<<(std::ostream &ostr, const DoublyLinkedList &dll) {
    ostr << dll.asString();
    return ostr;
}
