#pragma once
#include <iostream>
#include <stdexcept>

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& val) : data(val), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~LinkedList() {
        clear();
    }

    void clear() {
        while (head) {
            removeFront();
        }
    }

    void addBack(const T& val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void addFront(const T& val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
            tail = newNode;
        }
        else {
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    void addIndex(const T& val, int index) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of bounds");
        }

        if (index == 0) {
            addFront(val);
            return;
        }
        if (index == size) {
            addBack(val);
            return;
        }

        Node* newNode = new Node(val);
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
        size++;
    }

    void removeFront() {
        if (!head) {
            throw std::out_of_range("List is empty");
        }
        Node* temp = head;
        head = head->next;

        if (head) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }

        delete temp;
        size--;
    }

    void removeBack() {
        if (!tail) {
            throw std::out_of_range("List is empty");
        }
        Node* temp = tail;
        tail = tail->prev;

        if (tail) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }

        delete temp;
        size--;
    }

    void removeIndex(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }

        if (index == 0) {
            removeFront();
            return;
        }
        if (index == size - 1) {
            removeBack();
            return;
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        current->prev->next = current->next;
        current->next->prev = current->prev;

        delete current;
        size--;
    }

    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    int search(const T& value) const {
        Node* current = head;
        int index = 0;
        while (current) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            index++;
        }
        return -1;
    }

    int getSize() const {
        return size;
    }
};
