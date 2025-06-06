#pragma once
#include <iostream>

template<typename T>
class DynamicArray
{
private:
    T* arr;
    int size;
    int capacity;
    void resize() {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        T* newArr = new T[newCapacity];

        int elementsToCopy = (size > newCapacity) ? newCapacity : size;
        for (int i = 0; i < elementsToCopy; i++) {
            newArr[i] = arr[i];
        }

        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
    }

public:

    DynamicArray(int initialCapacity = 2) : capacity(initialCapacity), size(0) {
        arr = new T[capacity];
    }

    ~DynamicArray() {
        delete[] arr;
    }

    void addFront(const T& value) {
        if (size == capacity) {
            resize();
        }
        for (int i = size; i > 0; i--) {
            arr[i] = arr[i - 1];
        }
        arr[0] = value;
        size++;
    }
    void addBack(const T& value) {
        if (size == capacity)
        {
            resize();
        }
        arr[size] = value;
        size++;
    }
    void addIndex(int index, const T& value) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of range");
        }
        if (size == capacity) {
            resize();
        }
        for (int i = size; i > index; i--) {
            arr[i] = arr[i - 1];
        }
        arr[index] = value;
        size++;
    }
    void removeFront() {
        if (size == 0) {
            throw std::out_of_range("Array is empty");
        }
        for (int i = 0; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
    }
    void removeBack() {
        if (size == 0) {
            throw std::out_of_range("Array is empty");
        }
        size--;
    }
    void removeIndex(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
    }
    int search(const T& value) {
        for (int i = 0; i < size; i++) {
            if (arr[i] == value) {
                return i;
            }
        }
        return -1;
    }
    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    int getSize() const {
        return size;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }
};
