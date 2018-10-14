/************************************************************************
 * A pthreads implementation of matrix multiplication
 ***********************************************************************/

// includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include "matrix.h"
#include "multiply_pthread.h"

int main()
{
    srand(time(0)); //Seed the random number generator
    // create a matrix, A, mxn
    const unsigned int m = 4;
    const unsigned int n = 3;
    const unsigned int p = 2;

    Matrix* A = matrixCreate(m,n);
    Matrix* B = matrixCreate(n,p);
    Matrix* C;

    // initialize the matrix A
    matrixRandomizeInt(A, 10);

    // initialize the matrix B
    matrixRandomizeInt(B, 10);

    // print the operands
    printf("A:\n");
    matrixPrint(A);
    printf("B:\n");
    matrixPrint(B);

    // multiply the operands
    C = matrixMultiply(A,B);

    // print the result
    printf("C = A*B =\n");
    matrixPrint(C);

    // free the matrices
    matrixFree(A);
    matrixFree(B);
    matrixFree(C);

    return 0;
}
