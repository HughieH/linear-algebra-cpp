#include <iostream>
#include "linear_algebra.hpp"
#include "../eigen/Eigen/Dense"

using Eigen::MatrixXd;
using LinearAlgebra::Matrix;
 
int main()
{
   Matrix<int> a(2, 3, {
      {1, 2, 3},
      {3, 4, 3}
   });
   std::cout << a << std::endl; 
   //a[1][2] = 5;
   //std::cout << a[1][2] << std::endl; 
   Matrix<int> b(3, 2, {
      {1, 2},
      {3, 4}, 
      {5, 6}
   });
      
   Matrix c = a * b;
   std::cout << c << std::endl;  // Print the top-left element
   return 0;
}
   


   /*
   
   */
