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
    for( unsigned i = 0; i < m; i++ )
    {
        for( unsigned j = 0; j < n; j++ )
        {
            // get a random number on interval [0,10)
            A->data[i*A->cols+j] = (int)(rand()*10.0/RAND_MAX);
        }
    }

    // initialize the matrix B
    for( unsigned i = 0; i < n; i++ )
    {
        for( unsigned j = 0; j < p; j++ )
        {
            // get a random number on interval [0,10)
            B->data[i*B->cols+j] = (int)(rand()*10.0/RAND_MAX);
        }
    }

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
