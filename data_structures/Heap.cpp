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

}

int Heap::search(int key) const {
    return 0;
}

void Heap::print(int index, int indent = 0) const {
    int heapSize = table.getSize();
    if (index < heapSize) {
        if(this->left(index) < heapSize) {
            print(this->left(index), indent + 4);
        }
        if(this->right(index) < heapSize) {
            print(this->right(index), indent + 4);
        }
        if (indent != 0) {
            std::cout << std::setw(indent) << ' ';
        }
        std::cout<< table[index] << std::endl;
    }
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
    int largest = table[index];
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
    heap.print(0);
    return ostr;
}
