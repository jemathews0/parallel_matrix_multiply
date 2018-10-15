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

int main( int argc, char* argv[])
{
    srand(time(0)); //Seed the random number generator
    // create a matrix, A, mxn

    if( argc != 4 )
    {
        printf("Multiplies an M by N matrix, A, by an N by P matrix B.\
                usage: mmult_pthread M N P\n");
        return 1;
    }
    const unsigned int m = atoi(argv[1]);
    const unsigned int n = atoi(argv[2]);
    const unsigned int p = atoi(argv[3]);


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
