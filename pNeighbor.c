#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define NUMT 5
#define ROWS 200
#define COLS 200

pthread_mutex_t lock;
pthread_barrier_t barr;

int G = 0;
int A[ROWS][COLS];
int B[ROWS][COLS];

void *start (void* param)
{
	long myid = (long) param;

	while(G < ROWS)
	{
		if (myid % 5 == 0)
		{
			int i, j = 0;
			for (i = 0; i <= ROWS; i=i+5)
			{
				for (j = 0; j < COLS; ++j)
					A[i][j] = rand() % 20 + 1;
			}
			pthread_mutex_lock (&lock);
			++G;
			pthread_mutex_unlock (&lock);
		}
		else if (myid % 5 == 1)
		{
			int i, j = 0;
			for (i = 1; i <= ROWS; i=i+5)
			{
				for (j = 0; j < COLS; ++j)
					A[i][j] = rand() % 20 + 1;
			}
			pthread_mutex_lock (&lock);
			++G;
			pthread_mutex_unlock (&lock);
		}
		else if (myid % 5 == 2)
		{
			int i, j = 0;
			for (i = 2; i <= ROWS; i=i+5)
			{
				for (j = 0; j < COLS; ++j)
					A[i][j] = rand() % 20 + 1;
			}
			pthread_mutex_lock (&lock);
			++G;
			pthread_mutex_unlock (&lock);
		}
		else if (myid % 5 == 3)
		{
			int i, j = 0;
			for (i = 3; i <= ROWS; i=i+5)
			{
				for (j = 0; j < COLS; ++j)
				{
					A[i][j] = rand() % 20 + 1;
				}
			}
			pthread_mutex_lock (&lock);
			++G;
			pthread_mutex_unlock (&lock);
		}
		else
		{
			int i, j = 0;
			for (i = 4; i < ROWS; i=i+5)
			{
				for (j = 0; j < COLS; ++j)
				{
					A[i][j] = rand() % 20 + 1;
				}
			}
			pthread_mutex_lock (&lock);
			++G;
			pthread_mutex_unlock (&lock);
		}
		pthread_exit ((void*) myid);
		//pthread_barrier_wait (&barr);
	}
}

void print(int A[][COLS])
{
	int sum = 0;
	int i, j;
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
	srand(time(NULL));
	pthread_t tid[NUMT];
	pthread_mutex_init(&lock, NULL);
	pthread_barrier_init(&barr, NULL, 5);
	long i;

	for (i = 0; i < NUMT; ++i)
	{
		//printf("Creating %ld\n", i);
		pthread_create (&tid[i], NULL, start, (void *)i);
	}

	//print(A);

	//printf("\n");
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
			//printf("%d\t", B[i][j]);

		}
		//printf("\n");
	}

	return 0;
}
