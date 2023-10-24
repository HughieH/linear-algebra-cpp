/**
 * Portable & High-performance Linear Algebra Library 
 * Created by Hou Wai Wan for Brain Corp intern assesment.
 * 
*/

#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <iostream>
#include <vector>
#include <initializer_list>
#include <stdexcept>

/**
 * The Linear Algebra library currently contains a Matrix class with its associated constructors, some overloaded operators,
 * getters & setters, and two primary methods:
 * 
 * 1) A multiplication method, implemented via the overloaded "*" operator
 * 2) A transpose method
 * 
 * The primary implementation of the Matrix itself is via the use of a C style contiguos array, instead of the more
 * straightforward nested vector implementation. This allows for slightly better access times and performance. 
 * This "flattened" matrix is accessed and manipulated with the member methods of the Matrix class. The Matrix is also
 * 0-indexed based with a getter and setter for accessing elements.
*/
namespace LinearAlgebra {

// Class for representing a matrix with generic Scalar type, this can include int, double, float etc.
template<typename Scalar> 
class Matrix 
{
   protected:
      
      Scalar* matrix_data; // Pointer to the flattened matrix data.
      int rows; // Number of rows in the matrix.
      int cols; // Number of columns in the matrix.

      /**
       * Helper function to initialize matrix_data from a 2D range (like 2D vector or initializer list).
       * 
       * @param input_list: Either a 2D vector or nested initializer list
       * @throws Throws an exception if the provided range exceeds matrix dimensions 
       *    or if the number of elements in a data row is incorrect.
      */ 
      template<typename RangeType>
      void initializeFrom2DRange(const RangeType& input_list) {
         int row = 0;
         for (const auto& curr_row : input_list) {
            int col = 0;
            for (const auto& elem : curr_row) {
               if (row >= rows || col >= cols) {
                  throw std::out_of_range("Data exceeds matrix dimensions");
               }
               matrix_data[row * cols + col] = elem;
               col++;
            }
            if (col != cols) {
               throw std::invalid_argument("Incorrect number of elements in data row");
            }
            row++;
         }
      }

   public:
      /**
       * Default Constructor: Initialize an empty matrix with specified dimensions.
       * @param input_rows: Number of rows for the new matrix.
       * @param input_cols: Number of columns for the new matrix.
       */
      Matrix(int input_rows, int input_cols) 
         : matrix_data(new Scalar[input_rows * input_cols]), rows(input_rows), cols(input_cols) {}

       /**
       * Constructor to initialize matrix using an initializer list.
       * 
       * Example: LinearAlgebra::Matrix<int> matrix(2, 2, {{1, 2}, {3, 4}});
       * 
       * @param input_rows: Number of rows for the new matrix.
       * @param input_cols: Number of columns for the new matrix.
       * @param init_list: Initializer list to populate the matrix.
       */
      Matrix(int input_rows, int input_cols, std::initializer_list<std::initializer_list<Scalar>> init_list) 
         : matrix_data(new Scalar[input_rows * input_cols]), rows(input_rows), cols(input_cols) {
         initializeFrom2DRange(init_list);
      }

      /**
       * Constructor to initialize matrix using a 2D vector.
       * @param input_rows: Number of rows for the matrix.
       * @param input_cols: Number of columns for the matrix.
       * @param input_vector: 2D vector to populate the matrix.
       */
      Matrix(int input_rows, int input_cols, const std::vector<std::vector<Scalar>>& input_vector) 
         : matrix_data(new Scalar[input_rows * input_cols]), rows(input_rows), cols(input_cols) {
         initializeFrom2DRange(input_vector);
      }

      /**
       * Copy constructor.
       * @param other: Another matrix object to be copied.
       */
      Matrix(const Matrix<Scalar>& other) 
         : matrix_data(new Scalar[other.rows * other.cols]), rows(other.rows), cols(other.cols) {
         std::copy(other.matrix_data, other.matrix_data + rows * cols, matrix_data);
      }

      /**
       * Move constructor for efficient matrix creation by moving data.
       * @param other: Another matrix object.
       */
      Matrix(Matrix<Scalar>&& other) noexcept
         : matrix_data(std::move(other.matrix_data)), rows(std::move(other.rows)), cols(std::move(other.cols)) {}
      
      /**
       * Copy assignment operator.
       * @param other: Another matrix object to be copied.
       * @returns: This matrix object after copying data from the provided matrix.
       */
      Matrix<Scalar>& operator=(Matrix<Scalar> other) {
         std::swap(matrix_data, other.matrix_data);
         std::swap(rows, other.rows);
         std::swap(cols, other.cols);
         return *this;
      }

      /**
       * Move assignment operator for efficient matrix assignment.
       * @param other: Another matrix object.
       * @returns: This matrix object after moving data from the provided matrix.
       */
      Matrix<Scalar>& operator=(Matrix<Scalar>&& other) noexcept {
         matrix_data = std::move(other.matrix_data);
         rows = std::move(other.rows);
         cols = std::move(other.cols);
         return *this;
      }

      // Destructor
      ~Matrix(){ delete [] matrix_data; }

      /**
       * GETTER
       * Get the number of rows in the matrix.
       * @returns: Number of rows in the matrix.
       */
      int getRows() const { return rows; }

      /**
       * GETTER
       * Get the number of columns in the matrix.
       * @returns: Number of columns in the matrix.
       */
      int getCols() const { return cols; }

      /**
       * GETTER
       * Get the value of a specific cell in the matrix.
       * @param row: Row index of the cell.
       * @param col: Column index of the cell.
       * @throws An out_of_range exception if the input indexes are out of bounds.
       * @returns: Value at the specified cell in the matrix.
       */
      Scalar get(int row, int col) const {
         if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw std::out_of_range("Specified index is out of bounds");
         }
         return matrix_data[row * cols + col];
      }

      /**
       * SETTER
       * Set the value of a specific cell in the matrix.
       * @param row: Row index of the cell.
       * @param col: Column index of the cell.
       * @param value: Value to set in the specified cell.
       * @throws An out_of_range exception if the input indexes are out of bounds.
       * @returns: Void. Updates the matrix cell with the provided value.
       */
      template<typename ValueType>
      void set(int row, int col, ValueType value) {
         static_assert(std::is_same<Scalar, ValueType>::value, "Provided value is of a different type than the matrix's Scalar type.");

         if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw std::out_of_range("Specified index is out of bounds");
         }

         matrix_data[row * cols + col] = value;
      }

      /**
       * Overloaded insertion operator for streaming out the matrix content.
       * Allows for easy printing of the matrix using standard output streams.
       * @param os: The output stream to write to.
       * @param matrix: The matrix object to be printed.
       * @returns: The output stream after inserting the matrix content.
       */
      friend std::ostream& operator<< (std::ostream& os, const Matrix<Scalar>& matrix) {
         for (int i = 0; i < matrix.rows; ++i) {
               for (int j = 0; j < matrix.cols; ++j) {
                  os << matrix.matrix_data[i * matrix.cols + j] << " ";
               }
               os << std::endl;
         }
         return os;
      }

      /**
       * Overloaded multiplication operator for matrix multiplication.
       * Performs matrix multiplication on two conformant matrices.
       * Note: Both matrices should have the same Scalar type.
       * @param other_matrix: The second matrix to multiply with.
       * @returns: Resultant matrix after multiplication.
       */
      template<typename OtherScalar>
      Matrix<Scalar> operator*(const Matrix<OtherScalar>& other_matrix) const {
         
         // Check if both matrices are of the same Scalar type
         static_assert(std::is_same<Scalar, OtherScalar>::value, "Second matrix is of a different type than the first matrix's type.");
         // Check if matrices are conformant.
         if (cols != other_matrix.getRows()) { 
            throw std::invalid_argument("Matrices are not conformant for multiplication");
         }
         
         int other_cols = other_matrix.getCols();
         Matrix<Scalar> result(rows, other_cols);  // Initialize resultant matrix
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

      /**
       * Transposes the current matrix by creating a new Matrix with swapped rows and cols.
       * The function then swaps the values, deletes old matrix_data, and updates our matrix_data pointer 
       * to the new transposed matrix.
       * @returns: Void. The matrix object is transposed with matrix_data pointer updated.
       */
      void transpose() {
      
         Scalar* transposed_data = new Scalar[rows * cols];
         for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
               transposed_data[j * rows + i] = matrix_data[i * cols + j];
            }
         }
         std::swap(rows, cols); // Swap the rows and columns values
         delete[] matrix_data; // Cleanup old matrix_data and update pointer
         matrix_data = transposed_data;
      }
};
}  // End of namespace LinearAlgebra

#endif // LINEAR_ALGEBRA_H