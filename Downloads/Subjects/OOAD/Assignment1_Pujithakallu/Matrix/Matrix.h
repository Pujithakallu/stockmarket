#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
private:
    double data[2][2];

public:
    // Default constructor
    Matrix();

    // Parameterized constructor
    Matrix(double a, double b, double c, double d);

    // Copy constructor
    Matrix(const Matrix& other);

    // Overloaded + operator
    Matrix operator+(const Matrix& other) const;

    // Overloaded * operator
    Matrix operator*(const Matrix& other) const;

    // Transpose function
    Matrix transpose() const;

    // Getter for accessing elements
    double get(int row, int col) const;

    // Setter for modifying elements
    void set(int row, int col, double value);
};

// Default constructor
Matrix::Matrix() {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            data[i][j] = 0.0;
        }
    }
}

// Parameterized constructor
Matrix::Matrix(double a, double b, double c, double d) {
    data[0][0] = a; data[0][1] = b;
    data[1][0] = c; data[1][1] = d;
}

// Copy constructor
Matrix::Matrix(const Matrix& other) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
}

// Overloaded + operator
Matrix Matrix::operator+(const Matrix& other) const {
    Matrix result;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

// Overloaded * operator
Matrix Matrix::operator*(const Matrix& other) const {
    Matrix result;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            result.data[i][j] = data[i][0] * other.data[0][j] + data[i][1] * other.data[1][j];
        }
    }
    return result;
}

// Transpose function
Matrix Matrix::transpose() const {
    return Matrix(data[0][0], data[1][0], data[0][1], data[1][1]);
}

// Getter
double Matrix::get(int row, int col) const {
    return data[row][col];
}

// Setter
void Matrix::set(int row, int col, double value) {
    data[row][col] = value;
}

#endif // MATRIX_H