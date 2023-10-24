# linear-algebra-cpp
Build instructions:
Im using the make build automation tool. Make sure the Makefile is in the same directory as the header and source file. 
Please run the below commands to compile and run my code:
1) make all
2) ./test_program

Some notes about my code:
Currently the library has a Matrix class, with two primary methods, a multiply and transpose methods.
The multiplication method between two matrices takes O(n^3) time with O(n^2) data. I wasn't really able to implement a more effecient solution in 2-3 hours as 
this would have required either an attempt at implementing Strassen's algotithm, which has only marginal performance benefits in a real world situation. Another idea 
I had would've been to implement some clever use of how existing BLAS libraries ultilize the cache with techniques like block matrix multiplication but that wasn't possible with the time I had.

If I had more time, I would have liked to add type casting for multiplication between matrices of different data types. Right now my multiplcation
method only allows for operations between two matrix objects of the same Scalar type, but in real-world solutions multiplication between matrices of type int and double for example should be allowed. 


 