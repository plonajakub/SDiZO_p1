#include "Heap.h"


void Heap::insert(int key) {
    table.insertAtEnd(0);
    int keyIndex = table.getSize() - 1;

    // Get higher indexes for the new key until it the place meets the heap's condition
    while (keyIndex > 0 && table[parent(keyIndex)] < key) {
        table[keyIndex] = table[parent(keyIndex)];
        keyIndex = parent(keyIndex);
    }
    table[keyIndex] = key;
}

void Heap::remove(int key) {
    // Get key's index
    int rmIdx = search(key);
    if (rmIdx == KEY_NOT_FOUND) {
        throw std::invalid_argument("Key does not exist");
    }

    // Move last value in heap into the removed key's place
    table[rmIdx] = table[table.getSize() - 1];
    table.removeFromEnd();

    // Decide which algorithm to use in order to restore heap's order
    if (rmIdx > 0 && rmIdx != table.getSize() && table[rmIdx] > table[parent(rmIdx)]) {
        int movedValueIdx = rmIdx;

        // Move value up in the heap
        while (movedValueIdx > 0 && table[parent(movedValueIdx)] < table[movedValueIdx]) {
            swap(table[movedValueIdx], table[parent(movedValueIdx)]);
            movedValueIdx = parent(movedValueIdx);
        }
    } else {

        // Move value down in the heap
        heapify(rmIdx);
    }

}

int Heap::search(int key) const {
    int keyIndex = KEY_NOT_FOUND;

    // Call search algorithm
    findKey(key, 0, keyIndex);
    return keyIndex;
}

void Heap::findKey(int &key, int currIdx, int &keyIndex) const {
    // Base case
    if (currIdx >= table.getSize() || keyIndex != KEY_NOT_FOUND) {
        return;
    }
    if (table[currIdx] == key) {
        // key found
        keyIndex = currIdx;
    } else if (table[currIdx] > key) {
        // Key could be located deeper in the heap
        findKey(key, this->right(currIdx), keyIndex);
        findKey(key, this->left(currIdx), keyIndex);
    }
    // If key is greater than table[currIdx] stop looking deeper
}

void Heap::print(const std::ostream &ostr, int index = 0, int space = 0) const {
    // Gap between levels
    const int COUNT = 8;

    // Base case
    if (index >= table.getSize())
        return;

    // Space for new heap's level
    space += COUNT;

    // Process right subtree first
    print(ostr, this->right(index), space);

    // Process current node
    std::cout << std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout << " ";
    std::cout << table[index] << std::endl;

    // Process left subtree
    print(ostr, this->left(index), space);
}

int Heap::parent(int index) const {
    // floor(index / 2): index from 1
    return ((index + 1) >> 1) - 1;
}

int Heap::left(int index) const {
    // 2 * index: index from 1
    return ((index + 1) << 1) - 1;
}

int Heap::right(int index) const {
    // 2 * index + 1: index from 1
    return (index + 1) << 1;
}

void Heap::heapify(int index) {
    int l = this->left(index);
    int r = this->right(index);
    int heapSize = table.getSize();

    // Find the greatest node
    int largest = index;
    if (l < heapSize && table[l] > table[largest]) {
        largest = l;
    }
    if (r < heapSize && table[r] > table[largest]) {
        largest = r;
    }

    // Exchange nodes and continue
    if (largest != index) {
        this->swap(table[index], table[largest]);
        this->heapify(largest);
    }
}

void Heap::swap(int &x, int &y) const {
    int temp = x;
    x = y;
    y = temp;
}

std::ostream &operator<<(std::ostream &ostr, const Heap &heap) {
    ostr << std::string(40, '-') << std::endl;
    heap.print(ostr);
    ostr << std::string(40, '#') << std::endl;
    return ostr;
}
