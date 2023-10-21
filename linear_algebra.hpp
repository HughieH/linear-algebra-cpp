#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <memory>

namespace LinearAlgebra {

template<typename T, size_t R, size_t C>

class Matrix {
   T* data; 

public:
   Matrix() : data(new T[R*C]) {}

   ~Matrix(){ delete [] data; }

   inline T* operator[](int row) {
      return &data[row * C];
   }

   inline const T* operator[](int row) const {
      return &data[row * C];
   }
};

}  // End of namespace LinearAlgebra

#endif // LINEAR_ALGEBRA_H