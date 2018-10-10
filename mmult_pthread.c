/************************************************************************
 * A pthreads implementation of matrix multiplication
 ***********************************************************************/

// includes
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>


/********************************************************************
 * Global Constants
 *******************************************************************/

/********************************************************************
 * Global Variables
 *******************************************************************/

/********************************************************************
 * Synchronization variables
 *******************************************************************/


void printMatrix( double *A, unsigned int rows, unsigned int cols)
{
    for( unsigned i = 0; i < rows; i++ )
    {
        for( unsigned j = 0; j < cols; j++ )
        {
            printf("%.3f\t", *(A + i*cols + j));
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    srand(1); //Seed the random number generator
    // create a matrix, A, mxn
    const unsigned int m = 7;
    const unsigned int n = 3;
    const unsigned int p = 5;
    double A[m][n];
    double B[n][p];

    for( unsigned i = 0; i < m; i++ )
    {
        for( unsigned j = 0; j < n; j++ )
        {
            A[i][j] = rand()*100.0/RAND_MAX;
        }
    }

    printMatrix((double*)A, m, n);
    
    // create a matrix, B, nxp
    // create a matrix for the result, C, mxp
    // check that the sizes alow multiplication
    // for each column in A
        // for each row in B
            // multiply the elements and add their products to the sum
            // assign the result to the result matrix
    // print the result

    return 0;
}
