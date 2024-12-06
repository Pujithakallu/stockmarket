#include <iostream>
#include "CustomVector.h"

void printVector(const CustomVector& vec) {
    std::cout << "Vector contents: ";
    for (size_t i = 0; i < vec.getSize(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Size: " << vec.getSize() << ", Capacity: " << vec.getCapacity() << std::endl;
}

int main() {
    // Test default constructor
    CustomVector v1;
    std::cout << "Default constructor:" << std::endl;
    printVector(v1);

    // Test parameterized constructor
    CustomVector v2(5);
    std::cout << "\nParameterized constructor (capacity 5):" << std::endl;
    printVector(v2);

    // Test push_back
    std::cout << "\nAdding elements to v2:" << std::endl;
    for (int i = 0; i < 7; ++i) {
        v2.push_back(i * 10);
        printVector(v2);
    }

    // Test copy constructor
    CustomVector v3 = v2;
    std::cout << "\nCopy constructor (v3 = v2):" << std::endl;
    printVector(v3);

    // Test pop_back
    std::cout << "\nRemoving elements from v2:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        v2.pop_back();
        printVector(v2);
    }

    // Test [] operator
    std::cout << "\nAccessing elements of v2 using []:" << std::endl;
    for (size_t i = 0; i < v2.getSize(); ++i) {
        std::cout << "v2[" << i << "] = " << v2[i] << std::endl;
    }

    // Test exception handling
    try {
        std::cout << "\nTrying to access out-of-bounds element:" << std::endl;
        std::cout << v2[10] << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    return 0;
}