#include <iostream>
#include "Matrix.h"

void printMatrix(const Matrix& m) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            std::cout << m.get(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    // Test default constructor
    Matrix m1;
    std::cout << "Default constructor (m1):" << std::endl;
    printMatrix(m1);

    // Test parameterized constructor
    Matrix m2(1, 2, 3, 4);
    std::cout << "Parameterized constructor (m2):" << std::endl;
    printMatrix(m2);

    // Test copy constructor
    Matrix m3 = m2;
    std::cout << "Copy constructor (m3 = m2):" << std::endl;
    printMatrix(m3);

    // Test addition
    Matrix m4 = m2 + m3;
    std::cout << "Addition (m4 = m2 + m3):" << std::endl;
    printMatrix(m4);

    // Test multiplication
    Matrix m5 = m2 * m3;
    std::cout << "Multiplication (m5 = m2 * m3):" << std::endl;
    printMatrix(m5);

    // Test transpose
    Matrix m6 = m2.transpose();
    std::cout << "Transpose of m2:" << std::endl;
    printMatrix(m6);

    return 0;
}