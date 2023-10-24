#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <iostream>
#include <vector>
#include <initializer_list>
#include <stdexcept>

namespace LinearAlgebra {

template<typename Scalar> 
class Matrix {

protected:
   
   Scalar* matrix_data;
   size_t rows;
   size_t cols;

public:

   // Default Constructor
   Matrix(size_t input_rows, size_t input_cols) 
      : matrix_data(new Scalar[input_rows * input_cols]), rows(input_rows), cols(input_cols) {}

   // Constructor for taking in vector representation, e.g. 
   Matrix(size_t input_rows, size_t input_cols, std::initializer_list<std::initializer_list<Scalar>> init_list) 
      : matrix_data(new Scalar[input_rows * input_cols]), rows(input_rows), cols(input_cols) {
      
      size_t row = 0;
      for (const auto& curr_row : init_list) {
         size_t col = 0;
         for (const auto& elem : curr_row) {
            if (row >= input_rows || col >= input_cols) {
                throw std::out_of_range("Initializer list exceeds matrix dimensions");
            }
            matrix_data[row * cols + col] = elem;
            ++col;
         }
         ++row;
      }
   }
   
   // Destructor
   ~Matrix(){ delete [] matrix_data; }

   // Getters for rows & cols
   size_t getRows() const { return rows; }
   size_t getCols() const { return cols; }

   // Operator overload [][] 
   inline Scalar* operator[](int row) {
      if (row < 0 || static_cast<size_t>(row) >= rows) {
         throw std::out_of_range("Row index out of bounds");
      }
      return &matrix_data[row * cols];
}

   inline const Scalar* operator[](int row) const {
      return &matrix_data[row * cols];
   }

   // Overloaded insertion operator for output
   friend std::ostream& operator<< (std::ostream& os, const Matrix<Scalar>& matrix) {
        for (size_t i = 0; i < matrix.rows; ++i) {
            for (size_t j = 0; j < matrix.cols; ++j) {
                os << matrix.matrix_data[i * matrix.cols + j] << " ";
            }
            os << std::endl;
        }
        return os;
    }

   // Overloaded multiplication operator for matrix multiplication
   Matrix<Scalar> operator*(const Matrix<Scalar>& other_matrix) const {
      
      size_t other_cols = other_matrix.getCols();
      
      // Check if matrices are conformant.
      if (rows != other_cols) { 
         throw std::invalid_argument("Matrices are not conformant for multiplication");
      }
      
      Matrix<Scalar> result(rows, other_cols);  // Resultant matrix
      
      for (size_t i = 0; i < rows; ++i) {
         for (size_t j = 0; j < other_cols; ++j) {
            result.matrix_data[i * other_cols + j] = 0; // Initialize result cell to 0
            for (size_t k = 0; k < cols; ++k) {
                  result.matrix_data[i * other_cols + j] += matrix_data[i * cols + k] * other_matrix.matrix_data[k * other_cols + j];
            }
         }
      }
      
      return result;
   }

   // Transpose our matrix
   void transpose() {
      Scalar* transposed_data = new Scalar[rows * cols];

      for (size_t i = 0; i < rows; ++i) {
         for (size_t j = 0; j < cols; ++j) {
            transposed_data[j * rows + i] = matrix_data[i * cols + j];
         }
      }

      // Swap the rows and columns values
      std::swap(rows, cols);

      // Cleanup old matrix_data and update pointer
      delete[] matrix_data;
      matrix_data = transposed_data;
}

};

}  // End of namespace LinearAlgebra

#endif // LINEAR_ALGEBRA_H