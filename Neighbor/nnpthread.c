/************************************************************************
 * A pthreads implementation of matrix multiplication
 ***********************************************************************/

// includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include "matrix.h"
#include <pthread.h>

/********************************************************************
 * Global Constants
 *******************************************************************/

#define T 8 // The number of threads to create

/********************************************************************
 * A struct to pass all information a matrix multiplication thread 
 * needs to the thread
 *******************************************************************/
typedef struct
{
    unsigned tid; // An id so the thread knows who it is
    Matrix* A;    // A pointer to the first operand
    Matrix* B;    // A pointer to the second operand
    unsigned* index; // A pointer to an index for thread synchronization
    pthread_mutex_t* mutex; // A mutex to protect the index
} NeighborStruct;
/********************************************************************
 * Runs the startup code for a newly created thread.
 *******************************************************************/
void * neighborThreadStart( void * param)
{
    // typecast the parameter pointer so we can access elements of it
    NeighborStruct* mStruct = (NeighborStruct*) param;

    // create pointers with local scope pointing to "global" variables
    Matrix* A = mStruct->A;
    Matrix* B = mStruct->B;
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
        if( myIndex >= B->rows * B->cols )
            break;

        // determine the corresponding indices in matrix B
        unsigned i = myIndex / B->cols;
        unsigned j = myIndex % B->cols;

        int sum = 0;
        // add up the neighbors and self
        for(int k = i-1; k < (int)i+2; k++)
        {
            for(int m = j-1; m < (int)j+2; m++)
            {
                if( k>=0 && k < (int)B->rows && m>=0 && m<(int)B->cols)
                {
                    sum += A->data[k*A->cols+m];
                }
            }
        }
#ifdef DEBUG
        printf("Thread %d evaluated sum[%d,%d] as %d \n", tid, i, j, sum);
#endif

        B->data[i*B->cols+j] = A->data[i*A->cols+j];
        if( sum % 10 == 0 )
        {
            B->data[i*B->cols+j] = 0;
        }
        else if( sum < 50)
        {
            B->data[i*B->cols+j] += 3;
        }
        else if( sum < 150)
        {
            B->data[i*B->cols+j] -= 3;
            if( B->data[i*B->cols+j] < 0 )
                B->data[i*B->cols+j] = 0;
        }
        else
        {
            B->data[i*B->cols+j] = 1;
        }

#ifdef DEBUG
        printf("Thread %d evaluated B[%d,%d] as %d \n", tid, i, j, B->data[i*B->cols+j]);
#endif

    }

    return (void*) 0;
}

/********************************************************************
 * Multiply two rectangular matrices and return a pointer to the
 * resulting matrix
 *******************************************************************/
Matrix* neighbor( Matrix* A)
{
    // create a matrix to hold the result
    Matrix* B = matrixCreate(A->rows, A->cols);

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
    NeighborStruct mStructs[T];
    
    // create an array of thread ids
    pthread_t tids[T];

    // initialize the thread parameters and create the threads
    for(unsigned i = 0; i < T; i++ )
    {
        mStructs[i].A = A;
        mStructs[i].B = B;
        mStructs[i].index = &index;
        mStructs[i].mutex = &mutex;
        mStructs[i].tid = i;
        //printf("Creating thread %u\n", i);
        pthread_create( &(tids[i]), NULL, neighborThreadStart, (void*)&(mStructs[i]));
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

    return B;
}
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
