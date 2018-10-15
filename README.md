# parallel_matrix_multiply
Develop a parallel implementation of matrix multiplication as a group

This project will cover three different implementations of matrix multiplication:
* A sequential solution
* A pthread solution
* An OpenMP solution

It will also include an implementation of the Neighbor problem which is defined as follows:
Add up values for all neighbors (and self)

Adjust self based on these rules( top to bottom priority ):

% 10 == 0                        0

Under 50                         Add 3

Over 50 under 150         Subtract 3 Can't go negative(0)

over 150                          1

////////////////////////////////////////////////////////////////////////
To build this project, call 'make' from the root directory of the 
project. The executables will appear in the root directory. Calling
'make clean' will remove the executables
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
sequential matrix multiplication
////////////////////////////////////////////////////////////////////////

usage:
./mmult_sequential SIZE_OF_MATRIX
ex: ./mmult_sequential 200

Saves results from results matrix to a file: results.txt (THIS FILE IS OVERWRITTEN EVERYTIME exe is run).

Displaying to stdout is time consuming, this speeds up the process.
comment out the displayMatrix() function call to turn off displaying to the console.

build:
	gcc mmult_sequential.c -o sequential 
	or
	make

Built with Codeblocks on Windows. Tested on DSU's server with gcc.

////////////////////////////////////////////////////////////////////////
pthread matrix multiplication
////////////////////////////////////////////////////////////////////////

usage:
./mmult_pthread M N P

Creates an M by N matrix, A, and an N by P matrix, B, multiplies them 
together, and outputs the result to the screen.

build:
    gcc -o mmult_pthread test_mmult_pthread.c matrix.c multiply_pthread.c -lpthread
    or
    make
    or
    make mmult_pthread
