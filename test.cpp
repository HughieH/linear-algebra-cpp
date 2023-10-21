#include <iostream>
#include "linear_algebra.hpp"

int main() {
   LinearAlgebra::Matrix<int, 3, 3> mat;  // Create a 3x3 matrix of integers
   mat[0][0] = 5;  // Assign a value to the top-left element
   std::cout << mat[0][0] << std::endl;  // Print the top-left element
   return 0;
}