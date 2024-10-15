#ifndef CUSTOM_VECTOR_H
#define CUSTOM_VECTOR_H

#include <stdexcept>
#include <algorithm>

class CustomVector {
private:
    int* data;
    size_t size;
    size_t capacity;

    void resize(size_t newCapacity) {
        int* newData = new int[newCapacity];
        std::copy(data, data + size, newData);
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    // Default constructor
    CustomVector() : data(nullptr), size(0), capacity(0) {}

    // Parameterized constructor
    CustomVector(size_t initialCapacity) : size(0), capacity(initialCapacity) {
        data = new int[capacity];
    }

    // Copy constructor
    CustomVector(const CustomVector& other) : size(other.size), capacity(other.capacity) {
        data = new int[capacity];
        std::copy(other.data, other.data + size, data);
    }

    // Destructor
    ~CustomVector() {
        delete[] data;
    }

    // Overloaded [] operator
    int& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // Const version of [] operator
    const int& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // Add element at the end
    void push_back(int value) {
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = value;
    }

    // Remove element from the end
    void pop_back() {
        if (size > 0) {
            --size;
        }
    }

    // Get current size
    size_t getSize() const {
        return size;
    }

    // Get current capacity
    size_t getCapacity() const {
        return capacity;
    }
};

#endif // CUSTOM_VECTOR_H