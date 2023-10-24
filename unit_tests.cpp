// Unit tests for Matrix class in Linear Algebra library
// Completed by Hou Wai Wan for Brain Corp assesment 

#include "linear_algebra.h"
#include <iostream>
#include <cassert>

void testDefaultConstructor() {
   std::cout << "Testing Default Constructor...\n";
   LinearAlgebra::Matrix<int> matrix(3, 3);
   assert(matrix1.getRows() == 3 && matrix1.getCols() == 3);
   std::cout << "Expected Output: A 3x3 matrix with uninitialized values\n";
   std::cout << "Actual Output: \n" << matrix << "\n";
}

void testListConstructor() {
    std::cout << "Testing List Constructor...\n";
    LinearAlgebra::Matrix<int> matrix(2, 2, {{1, 2}, {3, 4}});
    assert(matrix2.get(0, 0) == 1 && matrix2.get(0, 1) == 2 && matrix2.get(1, 0) == 3 && matrix2.get(1, 1) == 4);
    std::cout << "Expected Output:\n1 2 \n3 4 \n";
    std::cout << "Actual Output: \n" << matrix << "\n";
}

void testListConstructorException() {
    std::cout << "Testing List Constructor Exception...\n";
    try {
        LinearAlgebra::Matrix<int> matrix(2, 2, {{1, 2, 3}, {4, 5, 6}});
    } catch (const std::out_of_range& e) {
        std::cout << "Expected Output: Initializer list exceeds matrix dimensions\n";
        std::cout << "Actual Output: " << e.what() << "\n";
    }
}

void testGetAndSet() {
    std::cout << "Testing Get and Set...\n";
    LinearAlgebra::Matrix<int> matrix(3, 3);
    matrix.set(1, 1, 5);
    std::cout << "Expected Output: 5\n";
    std::cout << "Actual Output: " << matrix.get(1, 1) << "\n";
    assert(matrix2.get(1, 1) == 5);
}

void testTranspose() {
    std::cout << "Testing Transpose...\n";
    LinearAlgebra::Matrix<int> matrix(2, 3, {{1, 2, 3}, {4, 5, 6}});
    matrix.transpose();
    std::cout << "Expected Output:\n1 4 \n2 5 \n3 6 \n";
    std::cout << "Actual Output: \n" << matrix << "\n";
}

void testMultiplication() {
    std::cout << "Testing Multiplication...\n";
    LinearAlgebra::Matrix<int> matrixA(2, 3, {{1, 2, 3}, {4, 5, 6}});
    LinearAlgebra::Matrix<int> matrixB(3, 2, {{7, 8}, {9, 10}, {11, 12}});
    L
}

int main() {

    // Test set & get functions
    matrix2.set(0, 0, 100);
    assert(matrix2.get(0, 0) == 100);

    // Test copy constructor
    Matrix<int> matrix3(matrix2);
    assert(matrix3.get(0, 0) == 100);

    // Test multiplication operator
    Matrix<int> matrix4(2, 3, {{1, 2, 3}, {4, 5, 6}});
    Matrix<int> matrix5(3, 2, {{1, 2}, {3, 4}, {5, 6}});
    Matrix<int> result = matrix4 * matrix5;
    assert(result.get(0, 0) == 22 && result.get(0, 1) == 28);
    assert(result.get(1, 0) == 49 && result.get(1, 1) == 64);

    // Test transpose
    matrix4.transpose();
    assert(matrix4.getRows() == 3 && matrix4.getCols() == 2);
    assert(matrix4.get(0, 0) == 1 && matrix4.get(0, 1) == 4);
    
    // Test for exceptions:
    try {
        Matrix<int> m(2, 2, {{1, 2, 3}, {4, 5, 6}});
        assert(false); // should not reach here
    } catch (std::out_of_range& e) {
        assert(true); // expected exception
    }

    try {
        matrix2.get(3, 3);
        assert(false); // should not reach here
    } catch (std::out_of_range& e) {
        assert(true); // expected exception
    }

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
