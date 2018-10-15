/************************************************************************
 * A general purpose matrix class
 ***********************************************************************/

// includes
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "matrix.h"

/********************************************************************
 * Initialize all values in a matrix to val
 *******************************************************************/
void matrixInit( Matrix * mat, double val)
{
    // initialize the matrix A
    for( unsigned i = 0; i < mat->rows; i++ )
    {
        for( unsigned j = 0; j < mat->cols; j++ )
        {
            mat->data[i*mat->cols+j] = val;
        }
    }
}

/********************************************************************
 * Initialize all values in a matrix to an integer between 0 and max
 *******************************************************************/
void matrixRandomizeInt( Matrix * mat, unsigned max)
{
    // initialize the matrix A
    for( unsigned i = 0; i < mat->rows; i++ )
    {
        for( unsigned j = 0; j < mat->cols; j++ )
        {
            // get a random integer on interval [0,max)
            mat->data[i*mat->cols+j] = (int)(rand()*(double)(max+1)/RAND_MAX);
        }
    }
}
/********************************************************************
 * Initialize all values in a matrix to an integer between 0 and max
 *******************************************************************/
void matrixRandomize( Matrix * mat, unsigned max)
{
    // initialize the matrix A
    for( unsigned i = 0; i < mat->rows; i++ )
    {
        for( unsigned j = 0; j < mat->cols; j++ )
        {
            // get a random double on interval [0,max)
            mat->data[i*mat->cols+j] = (rand()*(double)(max)/RAND_MAX);
        }
    }
}

/********************************************************************
 * Multiply mat by scalar
 *******************************************************************/
int matrixScale( Matrix * mat, double scalar)
{
    // check to see if the matrix is initialized
    if( mat==(void*)0 || mat->cols == 0 || mat->rows == 0)
    {
        printf("Error: Matrix is empty\n");
        return 0;
    }
    // initialize the matrix A
    for( unsigned i = 0; i < mat->rows; i++ )
    {
        for( unsigned j = 0; j < mat->cols; j++ )
        {
            mat->data[i*mat->cols+j] *= scalar;
        }
    }
    return 1;
}


/********************************************************************
 * Allocate the memory for a rectangular matrix
 *******************************************************************/
Matrix * matrixCreate( unsigned rows, unsigned cols)
{
    // grab a block of memory big enough to hold the Matrix struct with
    // the matrix values in a one-dimensional array starting immediately
    // afterwards
    Matrix* mat = malloc(sizeof(Matrix)+rows*cols*sizeof(double));
    if(!mat)
    {
        printf("Error: Couldn't allocate memory for matrix\n");
        return (void *)0;
    }

    // store the size of the matrix in the struct
    mat->rows = rows;
    mat->cols = cols;

    return mat;
}

/********************************************************************
 * Free up the memory associated with a matrix
 *******************************************************************/
void matrixFree( Matrix * mat )
{
    free( mat );
}

/********************************************************************
 * Print an m by n matrix to the screen 
 *******************************************************************/
void matrixPrint( Matrix* mat)
{
    // if the matrix is empty, don't try to print it
    if( mat==(void*)0 || mat->cols == 0 || mat->rows == 0)
    {
        printf("Error: Matrix is empty\n");
        return;
    }
    // print each row, one element at a time
    for( unsigned i = 0; i < mat->rows; i++ )
    {
        for( unsigned j = 0; j < mat->cols; j++ )
        {
            printf("%5.3f\t", mat->data[i*mat->cols + j]);
        }
        printf("\n");
    }
    printf("\n");

    return;
}
