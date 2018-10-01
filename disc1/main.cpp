#include <iostream>

#include "matrix.hxx"
#include "vector.hh"

int main(void) {
    std::cout << "Hello World!" << std::endl;

    std::cout << "This is an example Vector: " << Vector(3, 5.0) << std::endl;
    std::cout << "This is another example Vector: " << Vector({0.707, 0.707})
              << std::endl;

    // Try to get this code to work:

    Matrix A = {{1.0, 2.0, 3.0},
                {4.0, 5.0, 6.0},
                {7.0, 8.0, 9.0}};
    Matrix B = {{3.0, 2.0, 1.0},
                {6.0, 5.0, 4.0},
                {9.0, 8.0, 7.0}};
    std::cout << "This is matrix A: " << std::endl << A << std::endl;
    std::cout << "This is matrix B: " << std::endl << B << std::endl;
    std::cout << "A * B = " << std::endl
              << Matrix::matrix_multiply(A, B) << std::endl;

    return 0;
}