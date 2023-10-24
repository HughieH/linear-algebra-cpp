#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <iostream>
#include <vector>
#include <initializer_list>
#include <stdexcept>

namespace LinearAlgebra {

template<typename Scalar> 
class Matrix 
{
   protected:
      
      Scalar* matrix_data;
      int rows;
      int cols;

   public:
      // Default Constructor
      Matrix(int input_rows, int input_cols) 
         : matrix_data(new Scalar[input_rows * input_cols]), rows(input_rows), cols(input_cols) {}

      // Constructor for taking in vector representation, e.g. 
      Matrix(int input_rows, int input_cols, std::initializer_list<std::initializer_list<Scalar>> init_list) 
         : matrix_data(new Scalar[input_rows * input_cols]), rows(input_rows), cols(input_cols) {
         
         int row = 0;
         for (const auto& curr_row : init_list) {
            int col = 0;
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

      // Copy constructor
      Matrix(const Matrix<Scalar>& other) 
         : matrix_data(new Scalar[other.rows * other.cols]), rows(other.rows), cols(other.cols) {
         
         std::copy(other.matrix_data, other.matrix_data + rows * cols, matrix_data);
      }
      
      // Destructor
      ~Matrix(){ delete [] matrix_data; }

      // Getters for rows & cols
      int getRows() const { return rows; }
      int getCols() const { return cols; }

      // Getter for element in the Matrix
      Scalar get(int row, int col) const {
         if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw std::out_of_range("Specified index is out of bounds");
         }
         return matrix_data[row * cols + col];
      }

      // Setter for specified index in the Matrix
      template<typename ValueType>
      void set(int row, int col, ValueType value) {
         static_assert(std::is_same<Scalar, ValueType>::value, "Provided value is of a different type than the matrix's Scalar type.");

         if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw std::out_of_range("Specified index is out of bounds");
         }

         matrix_data[row * cols + col] = value;
   }

      // Overloaded insertion "<<" operator for output
      friend std::ostream& operator<< (std::ostream& os, const Matrix<Scalar>& matrix) {
         for (int i = 0; i < matrix.rows; ++i) {
               for (int j = 0; j < matrix.cols; ++j) {
                  os << matrix.matrix_data[i * matrix.cols + j] << " ";
               }
               os << std::endl;
         }
         return os;
      }

      Matrix<Scalar>& operator=(const Matrix<Scalar>& other) {
         if (this != &other) {
            delete[] matrix_data;

            rows = other.rows;
            cols = other.cols;
            matrix_data = new Scalar[rows * cols];
            std::copy(other.matrix_data, other.matrix_data + rows * cols, matrix_data);
         }
         return *this;
      }

      // Overloaded multiplication operator for matrix multiplication
      template<typename OtherScalar>
      Matrix<Scalar> operator*(const Matrix<OtherScalar>& other_matrix) const {
         
         static_assert(std::is_same<Scalar, OtherScalar>::value, "Second matrix is of a different type than the first matrix's type.");
         int other_cols = other_matrix.getCols();
         
         // Check if matrices are conformant.
         if (rows != other_cols) { 
            throw std::invalid_argument("Matrices are not conformant for multiplication");
         }
         
         Matrix<Scalar> result(rows, other_cols);  // Resultant matrix
         
         for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other_cols; ++j) {
               result.matrix_data[i * other_cols + j] = 0; // Initialize result cell to 0
               for (int k = 0; k < cols; ++k) {
                     result.matrix_data[i * other_cols + j] += matrix_data[i * cols + k] * other_matrix.get(k, j);
               }
            }
         }
         
         return result;
      }

      // Transpose our matrix
      void transpose() {
         Scalar* transposed_data = new Scalar[rows * cols];

         for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
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