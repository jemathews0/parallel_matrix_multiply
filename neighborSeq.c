#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 5
#define COLS 5


void print(int A[][COLS])
{
	int sum = 0;
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLS; ++j)
		{
			printf("%d\t", A[i][j]);
		}
		printf("\n");
	}
}


int main()
{
	int A[ROWS][COLS];
	int B[ROWS][COLS];
	int random = 0;
	srand(time(NULL));

	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLS; ++j)
		{
			A[i][j] = rand() % 20 + 1;
			printf("%d\t", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	for (int i = 1; i < ROWS-1; ++i)
	{
		for (int j = 1; j < COLS-1; ++j)
		{
			B[i][j] =  A[i][j] + A[i-1][j] + A[i][j-1] + A[i-1][j-1] + A[i+1][j] + A[i][j+1] + A[i+1][j+1] + A[i+1][j-1] + A[i-1][j+1];
			if (B[i][j] % 10 == 0)
				B[i][j] = 0;
			else if (B[i][j] < 50)
				B[i][j] = B[i][j] + 3;
			else if (B[i][j] > 50)
			{
				B[i][j] = B[i][j] - 3;
				if (B[i][j] < 0)
					B[i][j] = 0;
			}
			else
				B[i][j] = 1;
			printf("%d\t", B[i][j]);

		}
		printf("\n");
	}

	return 0;
}
