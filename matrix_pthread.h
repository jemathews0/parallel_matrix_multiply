#ifndef _MATRIX_PTHREAD_H
#define _MATRIX_PTHREAD_H

#include <pthread.h>

/********************************************************************
 * A struct to hold a rectangular matrix of doubles. Must be 
 * initialized by calling matrixCreate( rows, cols);
 *******************************************************************/
typedef struct 
{
    unsigned int rows;
    unsigned int cols;
    double data[];
} Matrix;

/********************************************************************
 * A struct to pass all information a matrix multiplication thread 
 * needs to the thread
 *******************************************************************/
typedef struct
{
    unsigned tid; // An id so the thread knows who it is
    Matrix* A;    // A pointer to the first operand
    Matrix* B;    // A pointer to the second operand
    Matrix* C;    // A pointer to the resulting matrix
    unsigned* index; // A pointer to an index for thread synchronization
    pthread_mutex_t* mutex; // A mutex to protect the index
} MatrixMultiplyStruct;

Matrix * matrixCreate( unsigned rows, unsigned cols);
void matrixFree( Matrix * mat );
void matrixPrint( Matrix* mat);
void * matrixThreadStart( void * param);
Matrix* matrixMultiply( Matrix* A, Matrix* B);

#endif
