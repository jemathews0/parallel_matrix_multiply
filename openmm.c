#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 200

multiply3 (int A[][N], int B[][N], int C[][N], int r1, int c1, int r2, int c2)
{
    // allow parallel sections to have nested parallel sections. If you
    // don't have this, then the for loop on k will only have 1 thread
    #pragma omp parallel
	#pragma omp for collapse(2)
	for (int i = 0; i < r1; ++i)
	{
        // placing any code here will break the 'omp for collapse(2)' call
		for (int j = 0; j < c2; ++j)
		{
            // initia
            int result = 0;
            // get the thread number for the outer parallel section
            int outer_ID = omp_get_thread_num();

            // loop over r2 elements with a single thread
			for (int k = 0; k < r2; ++k)
			{
                // get the thread number for the inner parallel section
                int inner_ID = omp_get_thread_num();
				result = result + A[i][k]*B[k][j];

                // output for debugging
                printf("Outer: %d Inner: %d i: %d j: %d k: %d\n", outer_ID, inner_ID, i, j, k);
			}

			C[i][j] = result;
			//result = 0;
		}
        // placing any code here will break the 'omp for collapse(2)' call
	}
}
multiply2 (int A[][N], int B[][N], int C[][N], int r1, int c1, int r2, int c2)
{
    // allow parallel sections to have nested parallel sections. If you
    // don't have this, then the for loop on k will only have 1 thread
    omp_set_nested(1);
	#pragma omp parallel for collapse(2)
	for (int i = 0; i < r1; ++i)
	{
        // placing any code here will break the 'omp for collapse(2)' call
		for (int j = 0; j < c2; ++j)
		{
            // initia
            int result = 0;
            // get the thread number for the outer parallel section
            int outer_ID = omp_get_thread_num();

            // create a nested parallel section to handle the summing
			#pragma omp parallel for reduction(+:result)
			for (int k = 0; k < r2; ++k)
			{
                // get the thread number for the inner parallel section
                int inner_ID = omp_get_thread_num();
				result = result + A[i][k]*B[k][j];

                // output for debugging
                printf("Outer: %d Inner: %d i: %d j: %d k: %d\n", outer_ID, inner_ID, i, j, k);
			}

			C[i][j] = result;
			//result = 0;
		}
        // placing any code here will break the 'omp for collapse(2)' call
	}
}
multiply (int A[][N], int B[][N], int C[][N], int r1, int c1, int r2, int c2)
{
    // allow parallel sections to have nested parallel sections. If you
    // don't have this, then the for loop on k will only have 1 thread
    omp_set_nested(1);
	int i, j, k;
	int result = 0;
	int sum = 0;
    // parallelize two nested for loops, creating r1*c2 threads in a team
    // For collapse to work, the loops must be perfectly nested with nothing
    // between them.
    // We also must declare result and k as private. Alternatively, we 
    // could just declare them inside of the second loop.
	#pragma omp parallel for collapse(2) private(result, k)
	for (i = 0; i < r1; ++i)
	{
        // placing any code here will break the 'omp for collapse(2)' call
		for (j = 0; j < c2; ++j)
		{
            // initia
            result = 0;
            // get the thread number for the outer parallel section
            int outer_ID = omp_get_thread_num();

            // create a nested parallel section to handle the summing
			#pragma omp parallel for reduction(+:result)
			for (k = 0; k < r2; ++k)
			{
                // get the thread number for the inner parallel section
                int inner_ID = omp_get_thread_num();
				result = result + A[i][k]*B[k][j];

                // output for debugging
                printf("Outer: %d Inner: %d i: %d j: %d k: %d\n", outer_ID, inner_ID, i, j, k);
			}

			C[i][j] = result;
			//result = 0;
		}
        // placing any code here will break the 'omp for collapse(2)' call
	}
}

void printMatrix (int C[][N], int r1, int c2)
{
	int i, j;
	printf("The product of the matrices is:\n");
	for (i = 0; i < r1; ++i)
	{
		for (j = 0; j < c2; ++j)
		{
			printf("%d   ", C[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	int A[N][N], B[N][N], C[N][N];
	int i, j, k, r1, c1, r2, c2;

	printf("\nEnter rows and columns (Ex.'5 5').\nThe column of matrix 1 must equal the row of matrix 2.\n\n");
	printf("Matrix 1:\n");
	scanf("%d%d", &r1, &c1);

	printf("Matrix 2:\n");
	scanf("%d%d", &r2, &c2);
	

	if (c1 != r2)
	{
		printf("Error!");
	}
	else if (c1 > N || c2 > N || r1 > N || r2 > N)
	{
		printf("Error!");
	}

	else
	{
		// Get elements of first matrix
		printf("Input matrix 1 elements: \n");
		for (i = 0; i < r1; ++i)
		{
			for (j = 0; j < c1; ++j)
			{
				A[i][j] = rand() % 10 + 1;
				printf("%d   ", A[i][j]);
			}
			printf("\n");
		}

		// Get elements of second matrix
		printf("Input matrix 2 elements: \n");
		for (i = 0; i < r2; ++i)
		{
			for (j = 0; j < c2; ++j)
			{
				B[i][j] = rand() % 10 + 1;
				printf("%d   ", B[i][j]);
			}
			printf("\n");
		}

		multiply3(A, B, C, r1, c1, r2, c2);
		printMatrix(C, r1, c2);
	}

	return 0;
}
