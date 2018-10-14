/************************************************************************
 * A pthreads implementation of matrix multiplication
 ***********************************************************************/

// includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include "matrix.h"
#include "neighbor_pthread.h"

int main()
{
    srand(time(0)); //Seed the random number generator
    // create a matrix, A, mxn
    const unsigned int m = 4;
    const unsigned int n = 3;

    Matrix* A = matrixCreate(m,n);
    Matrix* B;

    // initialize the matrix A
    matrixRandomizeInt(A, 11);

    // print the operands
    printf("A:\n");
    matrixPrint(A);

    // run the neighbor algorithm on A
    B = neighbor(A);

    // print the result
    printf("B = neighbor(A) = \n");
    matrixPrint(B);

    // free the matrices
    matrixFree(A);
    matrixFree(B);

    return 0;
}
