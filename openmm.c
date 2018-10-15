#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 200

multiply (int A[][N], int B[][N], int C[][N], int r1, int c1, int r2, int c2)
{
	//#pragma omp parallel 
	{
	int i, j, k;
	int result = 0;
	int sum = 0;
	#pragma omp parallel for collapse(2) private(result, k)
	for (i = 0; i < r1; ++i)
	{
        //#pragma omp for
		for (j = 0; j < c2; ++j)
		{
            result = 0;
			//#pragma omp parallel for reduction(+:result) schedule(dynamic)
			for (k = 0; k < r2; ++k)
			{
                int ID = omp_get_thread_num();
				result = result + A[i][k]*B[k][j];
                printf("Thread: %d i: %d j: %d k: %d\n", ID, i, j, k);
			}

			C[i][j] = result;
			result = 0;
		}
	}
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

		multiply(A, B, C, r1, c1, r2, c2);
		printMatrix(C, r1, c2);
	}

	return 0;
}
