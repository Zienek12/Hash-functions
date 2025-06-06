#pragma once
#include "DynamicArray.h"
#include "DoublyLinkedList.h"
#include <functional>
#include <stdexcept>

template<typename T>
class HashTable {
private:
    DynamicArray<LinkedList<T>*> buckets;
    int bucketCount;
    std::function<size_t(const T&)> hashFunc;

public:
    HashTable(int numBuckets, std::function<size_t(const T&)> func)
        : buckets(numBuckets), bucketCount(numBuckets), hashFunc(func)
    {
        for (int i = 0; i < bucketCount; ++i) {
            buckets.addBack(new LinkedList<T>());
        }
    }

    ~HashTable() {
        for (int i = 0; i < bucketCount; ++i) {
            delete buckets[i];
        }
    }

    void insert(const T& value) {
        size_t idx = hashFunc(value) % bucketCount;
        buckets[idx]->addBack(value);
    }

    bool remove(const T& value) {
        size_t idx = hashFunc(value) % bucketCount;
        int pos = buckets[idx]->search(value);
        if (pos != -1) {
            buckets[idx]->removeIndex(pos);
            return true;
        }
        return false;
    }

    bool contains(const T& value) const {
        size_t idx = hashFunc(value) % bucketCount;
        return buckets[idx]->search(value) != -1;
    }

    void print() const {
        for (int i = 0; i < bucketCount; ++i) {
            std::cout << "Bucket " << i << ": ";
            buckets[i]->print();
        }
    }
};
