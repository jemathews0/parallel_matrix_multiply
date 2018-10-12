#ifndef _MULTIPLY_PTHREAD_H
#define _MULTIPLY_PTHREAD_H

#include <pthread.h>
#include "matrix.h"

/********************************************************************
 * Global Constants
 *******************************************************************/

#define T 8

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

void * matrixMultiplyThreadStart( void * param);
Matrix* matrixMultiply( Matrix* A, Matrix* B);

#endif
