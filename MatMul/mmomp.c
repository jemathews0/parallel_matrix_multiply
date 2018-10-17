#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 3

int A[N][N];
int B[N][N];
int C[N][N];

void multiply (int A[][N], int B[][N], int C[][N])
{
	omp_set_nested(1);
	
	int i, j, k;
	int result = 0;
	#pragma omp parallel for collapse(2) private(result, k)
	for (i = 0; i < N; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			result = 0;
			int outer_ID = omp_get_thread_num();
			#pragma omp parallel for reduction(+:result)
			for (k = 0; k < N; ++k)
			{
				int inner_ID = omp_get_thread_num();
				result = result + A[i][k]*B[k][j];
				printf("Outer: %d\nInner: %d\n i: %d j: %d k: %d\n", outer_ID, inner_ID, i, j, k);
			}

			C[i][j] = result;
		}
	}
}

void printMatrix (int C[][N])
{
	int i, j;
	printf("The product of the matrices is:\n");
	for (i = 0; i < N; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			printf("%d\t", C[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	int i, j;
	srand(time(NULL));
		printf("Input matrix 1 elements: \n");
		for (i = 0; i < N; ++i)
		{
			for (j = 0; j < N; ++j)
			{
				A[i][j] = rand() % 10 + 1;
				printf("%d   ", A[i][j]);
			}
			printf("\n");
		}

		// Get elements of second matrix
		printf("Input matrix 2 elements: \n");
		for (i = 0; i < N; ++i)
		{
			for (j = 0; j < N; ++j)
			{
				B[i][j] = rand() % 10 + 1;
				printf("%d   ", B[i][j]);
			}
			printf("\n");
		}

		multiply(A, B, C);
		printMatrix(C);

	return 0;
}
