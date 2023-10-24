// Unit tests for Matrix class in Linear Algebra library
// Completed by Hou Wai Wan for Brain Corp assesment 

#include "linear_algebra.h"
#include <iostream>
#include <cassert>
#include <vector>

void testDefaultConstructor() {
   std::cout << "Testing Default Constructor...\n";
   LinearAlgebra::Matrix<int> matrix(3, 3);
   std::cout << "Expected Output: A 3x3 matrix with uninitialized values\n";
   assert(matrix.getRows() == 3 && matrix.getCols() == 3);
   std::cout << "Actual Output: \n" << matrix << "\n";
}

void testListConstructor() {
    std::cout << "Testing List Constructor...\n";
    LinearAlgebra::Matrix<int> matrix(2, 2, {{1, 2}, {3, 4}});
    std::cout << "Expected Output:\n1 2 \n3 4 \n";
    assert(matrix.get(0, 0) == 1 && matrix.get(0, 1) == 2 && matrix.get(1, 0) == 3 && matrix.get(1, 1) == 4);
    std::cout << "Actual Output: \n" << matrix << "\n";
}

void testVectorConstructor() {
    std::cout << "Testing Vector Constructor...\n";
    std::vector<std::vector<int>> vector_example = {
        {1, 2},
        {3, 4}
    };
    LinearAlgebra::Matrix<int> matrix(2, 2, vector_example);
    std::cout << "Expected Output:\n1 2 \n3 4 \n";
    assert(matrix.get(0, 0) == 1 && matrix.get(0, 1) == 2 && matrix.get(1, 0) == 3 && matrix.get(1, 1) == 4);
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
    std::cout << "\nTesting Get and Set...\n";
    LinearAlgebra::Matrix<int> matrix(3, 3);
    matrix.set(1, 1, 5);
    std::cout << "Expected Output: 5\n";
    assert(matrix.get(1, 1) == 5);
    std::cout << "Actual Output: " << matrix.get(1, 1) << "\n";
}

void testTranspose() {
    std::cout << "\nTesting Transpose...\n";
    LinearAlgebra::Matrix<int> matrix(2, 3, {{1, 2, 3}, {4, 5, 6}});
    matrix.transpose();
    std::cout << "Expected Output:\n1 4 \n2 5 \n3 6 \n";
    assert(matrix.getRows() == 3 && matrix.getCols() == 2);
    assert(matrix.get(0, 0) == 1 && matrix.get(0, 1) == 4);
    assert(matrix.get(1, 0) == 2 && matrix.get(1, 1) == 5);
    assert(matrix.get(2, 0) == 3 && matrix.get(2, 1) == 6);
    std::cout << "Actual Output: \n" << matrix << "\n";
}

void testMultiplication() {
    std::cout << "Testing Multiplication...\n";
    LinearAlgebra::Matrix<int> matrixA(2, 3, {{1, 2, 3}, {4, 5, 6}});
    LinearAlgebra::Matrix<int> matrixB(3, 2, {{7, 8}, {9, 10}, {11, 12}});
    LinearAlgebra::Matrix<int> result = matrixA * matrixB;
    assert(result.get(0, 0) == 58 && result.get(0, 1) == 64);
    assert(result.get(1, 0) == 139 && result.get(1, 1) == 154);
    std::cout << "Expected Output:\n58 64 \n139 154 \n";
    std::cout << "Actual Output: \n" << result << "\n";
}

void testMultiplicationException() {
    std::cout << "Testing Multiplication Exception...\n";
    LinearAlgebra::Matrix<int> matrixA(2, 3, {{1, 2, 3}, {4, 5, 6}});
    LinearAlgebra::Matrix<int> matrixB(2, 2, {{7, 8}, {9, 10}});
    try {
        LinearAlgebra::Matrix<int> result = matrixA * matrixB;
    } catch (const std::invalid_argument& e) {
        std::cout << "Expected Output: Matrices are not conformant for multiplication\n";
        std::cout << "Actual Output: " << e.what() << "\n";
    }
}

void testLargeMultiplication() {
    std::cout << "\nTesting Large Multiplication...\n";
    
    // Create matrices A (20x30) and B (30x40)
    LinearAlgebra::Matrix<int> matrixA(10, 30, {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30}
    });

    LinearAlgebra::Matrix<int> matrixB(30, 20, {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}
    });

    std::cout << "20x30 Matrix:\n" << matrixA << "\n";
    std::cout << "30x40 Matrix:\n" << matrixB << "\n";
    // Multiplication
    LinearAlgebra::Matrix<int> result = matrixA * matrixB;
    assert(result.getRows() == matrixA.getRows() && result.getCols() == matrixB.getCols());
    std::cout << "Result of 20x30 multiplied by 30x40:\n" << result << "\n";
}

void testLargeTranspose() {
    std::cout << "\nTesting Large Transpose...\n";
    
    // Create matrix (10x30)
    LinearAlgebra::Matrix<int> matrix(10, 30, {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30}
    });

    // Transpose
    matrix.transpose();
    assert(matrix.getRows() == 30 && matrix.getCols() == 10);
    std::cout << "Transposed 20x30 matrix:\n" << matrix << "\n";
}

int main() {

    // All test cases
    testDefaultConstructor();
    testListConstructor();
    testVectorConstructor();
    testListConstructorException();
    testGetAndSet();
    testTranspose();
    testMultiplication();
    testMultiplicationException();
    testLargeMultiplication();
    testLargeTranspose();

    std::cout << "\nAll tests passed!" << std::endl;
    return 0;
}
