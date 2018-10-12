/************************************************************************
 * A pthreads implementation of matrix multiplication
 ***********************************************************************/

// includes
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "multiply_pthread.h"


/********************************************************************
 * Runs the startup code for a newly created thread.
 *******************************************************************/
void * matrixMultiplyThreadStart( void * param)
{
    // typecast the parameter pointer so we can access elements of it
    MatrixMultiplyStruct* mStruct = (MatrixMultiplyStruct*) param;

    // create pointers with local scope pointing to "global" variables
    Matrix* A = mStruct->A;
    Matrix* B = mStruct->B;
    Matrix* C = mStruct->C;
    unsigned* index = mStruct->index;
    pthread_mutex_t* mutex = mStruct->mutex;
#ifdef DEBUG
    unsigned tid = mStruct->tid;
#endif

    // A variable to keep track of which element this thread is calculating
    unsigned myIndex = 0; 

    //printf("Thread %d with pointer %u started\n", tid, (unsigned long)param);

    // Keep grabbing a new task until all the tasks are done
    while(1)
    {
        // get the next available index for the output array and increment
        pthread_mutex_lock( mutex );
        myIndex = *index;
        (*index)++;
        pthread_mutex_unlock( mutex );


        // exit if the result array has been filled
        if( myIndex >= C->rows * C->cols )
            break;

        // determine the corresponding indices in matrix C
        unsigned i = myIndex / C->cols;
        unsigned j = myIndex % C->cols;

        // multiply and add the appropriate elements for this position
        double sum = 0;
        for( unsigned k = 0; k < A->cols; k++)
        {
            double temp = A->data[i*A->cols+k] * B->data[k*B->cols+j];
            //printf("Subposition: %d product: %f\n", k, temp);
            sum += temp;
        }
        C->data[i*C->cols+j] = sum;

#ifdef DEBUG
        printf("Thread %d evaluated C[%d,%d] as %f \n", tid, i, j, sum);
#endif

    }

    return (void*) 0;
}

/********************************************************************
 * Multiply two rectangular matrices and return a pointer to the
 * resulting matrix
 *******************************************************************/
Matrix* matrixMultiply( Matrix* A, Matrix* B)
{
    // check to make sure the matrices are compatible
    if( A->cols != B->rows)
    {
        printf("Error: Incompatible matrix sizes\n");
        return (void*) 0;
    }
    
    // create a matrix to hold the result
    Matrix* C = matrixCreate(A->rows, B->cols);

    // synchronization variables for the threads
    unsigned index = 0; // the next position to be filled in the result
    pthread_mutex_t mutex; // a mutex to protect the global index

    // initialize the mutex
    int retval = pthread_mutex_init( &mutex, NULL);
    if( retval != 0)
    {
        printf("Error: Couldn't initialize mutex\n");
        return (void*)0;
    }

    // create an array of thread parameter structs
    MatrixMultiplyStruct mStructs[T];
    
    // create an array of thread ids
    pthread_t tids[T];

    // initialize the thread parameters and create the threads
    for(unsigned i = 0; i < T; i++ )
    {
        mStructs[i].A = A;
        mStructs[i].B = B;
        mStructs[i].C = C;
        mStructs[i].index = &index;
        mStructs[i].mutex = &mutex;
        mStructs[i].tid = i;
        //printf("Creating thread %u\n", i);
        pthread_create( &(tids[i]), NULL, matrixMultiplyThreadStart, (void*)&(mStructs[i]));
    }

    // join all the threads back in
    for(unsigned i = 0; i < T; i++)
    {
        //printf("Joining thread %u\n", i);
        pthread_join(tids[i], NULL);
    }

#ifdef DEBUG
    printf("\n");
#endif

    return C;
}
