#include <iostream>
#include <cassert>
#include "linear_algebra.hpp"

using namespace LinearAlgebra;

int main() {
    // Test default constructor
    Matrix<int> matrix1(3, 3);
    assert(matrix1.getRows() == 3 && matrix1.getCols() == 3);

    // Test initializer list constructor
    Matrix<int> matrix2(2, 2, {{1, 2}, {3, 4}});
    assert(matrix2.get(0, 0) == 1 && matrix2.get(0, 1) == 2 && matrix2.get(1, 0) == 3 && matrix2.get(1, 1) == 4);

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
