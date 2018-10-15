/************************************************************************
 * A Sequential implementation of matrix multiplication
 ***********************************************************************/

// includes
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>


/********************************************************************
 * Global Constants
 *******************************************************************/


/********************************************************************
 * Global Variables
 *******************************************************************/
//int N= 200;     // Control size of matrix (N*N) is assumed
int MIN =1;     //minimum value for random number generator
int MAX = 101;  //maximum value for random number generator


/********************************************************************
 * Helper functions
 *******************************************************************/


/*
    fillMatrix: fills a 2D matrix with RGN values.
    Args:
        int **a: 2d array to fill with values.
        int n: length of array.
    Returns: N/A.
*/

void fillMatrix(int **a,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            a[i][j]= rand() % (MAX-MIN) + MIN;
        }
    }
}

/*

    displayMatrix: displays a 2D array to the screen.
    Args:
        int **a: 2D array to print.
        int n: length of array.
    returns: N/A.
*/
void displayMatrix(int **a, int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%2d\t",a[i][j]);
        }
        printf("\n");
    }
}



/*
    writeMatrix: write the values of the results matrix to a file.
        since writing to STDOUT is time consuming, this will speed up the process.
        mostly saving it to have a way to confirm values are working.

    Args:
        int **a: array to read from.
        char *file: name of file to save results to.
        FILE *fp: pointer to file.
        int n: length of array.

    returns: N/A.
*/

void writeMatrix(int **a,char *file, FILE *fp,int n)
{
    fp = fopen(file,"w");
    if (fp == NULL)
    {
        printf("error open file %s",file);
        return;
    }
    else
        printf("file %s opened successfully\n",file);

    fprintf(fp,"Results Matrix:\n\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            fprintf(fp,"%2d\t",a[i][j]);
        }
        fprintf(fp,"\n");
    }
    if ((fclose(fp))==0)
        printf("file closed\n");

}

/*
    multiplyMatrix: performs matrix multiplication on 2 matrices.
        expects matrices of size N*N for ease of use.
    Args:
        int **a: first of two matrices to be multiplied
        int **b: second of two matrices to be multiplied.
        int **c: Matrix where results will be saved.

    returns: N/A.
*/

void multiplyMatrix(int **a,int **b,int **result,int n)
{
    //long int sum =0,total=0;
    int i,j,k;
    //iterate through rows of X
    printf("********************************\n");
    printf("Multiplying array of size: %d",n);
    for(i=0;i<n;i++)
    {
        //sum=0;
        //iterate through columns of Y
        for(j=0;j<n;j++)
        {
            //total=0;
            //iterate through rows of Y
            for(k=0;k<n;k++)
            {
                //sum = a[i][k] * b[k][j];
                result[i][j] += a[i][k] * b[k][j];
                //printf("sum of %ld x %ld\t=%ld\n",a[i][k], b[k][j], sum);     //debugging
                //total+=sum;         //to make sure values are correct
            }
        }
        //printf("********************************\n"); //makes it look pretty
    }
}


/*
    fillMatrixZero: fills a N*N matrix with 0s.

    Args:
        int **a: array to fill.
    returns: N/A

*/
void fillMatrixZero(int **a,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            a[i][j]= 0;
        }
    }
}


/*
    Returns a ** pointer to a 2D array.
    Args:
        int col : size of array (expected N*N array).
    returns: ** pointer to an array.
*/

int ** makeArray(int size)
{
    //make rows
    int **arr = (int **)malloc(size * sizeof(int *));
    if(arr==NULL)
        printf("error creating array");

    //make cols
    for (int i=0; i<size; i++)
    {
         arr[i] = (int *)malloc(size * sizeof(int));
         if(arr[i]==NULL)
            printf("Error, out of memory likely\n");
    }
    return arr;
}



/*
    freeArray: frees dynamically allocated memory for a 2D array.
        //works alongside makeArray.
    Args:
        int **arr: the array to free.
        int col: size of columns to be freed.
    returns: N/A
*/
void freeArray(int **arr,int col)
{
    for (int i=0; i<col; i++)
        free(arr[i]);// = (int *)malloc(c * sizeof(int));
    free(arr);
}



 /********************************************************************
 * MAIN
 *******************************************************************/
int main(int argc, char *argv[])
{

    if(argc !=2)
    {
        printf("usage: %s NUM (size of matrix) \n",argv[0]);
        exit(1);
    }
    printf("Size of matrix: %d",atoi(argv[1]));
    int N  = atoi(argv[1]);
    FILE *fp = NULL;
    char *file = "results.txt";
    //writing to file is faster than stdout
    //save matrices results here.

    // create a matrix, A, mxn
    int **a = makeArray(N);
    if(a!=NULL)
        printf("created array\n");
    else
        printf("done creating array a\n");
    // create a matrix, B, nxp
    int **b = makeArray(N);
    if(b!=NULL)
        printf("created array\n");
    else
        printf("done creating array b\n");

    // create a matrix for the result, C, mxp
    int **c = makeArray(N);
    if(c!=NULL)
        printf("created array\n");
    else
        printf("done creating array c\n");

    //seed rand
    srand(time(NULL));

    //print matrices & result
    printf("matrix A: \n");
    fillMatrix(a,N);
    //displayMatrix(a,N);         //turn this on/off as you need

    printf("matrix B: \n");
    fillMatrix(b,N);
    //displayMatrix(b,N);         //turn this on/off as you need

    printf("matrix C: \n");
    fillMatrixZero(c,N);
    //displayMatrix(c,N);         //turn this on/off as you need

    printf("Multiplying matrices AXB = C: \n");
    //multiply matrix
    multiplyMatrix(a,b,c,N);

    printf("Displaying C:\n");
    printf("********************************\n");
    //displayMatrix(c,N);                             //turn this on/off as you need
    writeMatrix(c,file,fp,N);
    printf("********************************\n");

    printf("freeing up memory...\n");
    //clean up
    freeArray(a,N);
    freeArray(b,N);
    freeArray(c,N);

    printf("done");
    return 0;
}
