//
// Created by Jakub Plona PL on 22.03.2019.
//

#include <iomanip>
#include "Heap.h"

void Heap::insert(int key) {
    table.insertAtEnd(0);
    int keyIndex = table.getSize() - 1;
    while (keyIndex > 0 && table[parent(keyIndex)] < key) {
        table[keyIndex] = table[parent(keyIndex)];
        keyIndex = parent(keyIndex);
    }
    table[keyIndex] = key;
}

void Heap::remove(int key) {
    int rmIdx = search(key);
    if (rmIdx == KEY_NOT_FOUND) {
        throw std::invalid_argument("Key does not exist");
    }
    table[rmIdx] = table[table.getSize() - 1];
    table.removeAtEnd();
    if (rmIdx > 0 && rmIdx != table.getSize() && table[rmIdx] > table[parent(rmIdx)]) {
        int movedValueIdx = rmIdx;
        while (movedValueIdx > 0 && table[parent(movedValueIdx)] < table[movedValueIdx]) {
            swap(table[movedValueIdx], table[parent(movedValueIdx)]);
            movedValueIdx = parent(movedValueIdx);
        }
    }
    else {
        heapify(rmIdx);
    }

}

int Heap::search(int key) const {
    int keyIndex = KEY_NOT_FOUND;
    findKey(key, 0, keyIndex);
    return keyIndex;
}

void Heap::findKey(int &key, int currIdx, int &keyIndex) const {
    if (currIdx >= table.getSize() || keyIndex != KEY_NOT_FOUND) {
        return;
    }
    if (table[currIdx] == key) {
        keyIndex = currIdx;
    }
    else if (table[currIdx] > key) {
        findKey(key, this->right(currIdx), keyIndex);
        findKey(key, this->left(currIdx), keyIndex);
    }
}

void Heap::print(const std::ostream &ostr, int index = 0, int space = 0) const {
    const int COUNT = 8;

    if (index >= table.getSize())
        return;

    space += COUNT;

    print(ostr, this->right(index), space);

    std::cout << std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout << " ";
    std::cout << table[index] << std::endl;

    print(ostr, this->left(index), space);
}

int Heap::parent(int index) const {
    return ((index + 1) >> 1) - 1;
}

int Heap::left(int index) const {
    return ((index + 1) << 1) - 1;
}

int Heap::right(int index) const {
    return (index + 1) << 1;
}

void Heap::heapify(int index) {
    int l = this->left(index);
    int r = this->right(index);
    int heapSize = table.getSize();
    int largest = index;
    if (l < heapSize && table[l] > table[largest]) {
        largest = l;
    }
    if (r < heapSize && table[r] > table[largest]) {
        largest = r;
    }
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

std::ostream& operator<<(std::ostream &ostr, const Heap &heap) {
    ostr << std::string(40, '-') << std::endl;
    heap.print(ostr);
    ostr << std::string(40, '#') << std::endl;
    return ostr;
}
