//
//  nnseq.c
//  
//
//  Created by Landon on 10/11/18.
//
//

//NOTE: Not finished, still in development by Landon Frederes

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int SIZE = 5;
int matrixA[5][5] = {0};
int matrixB[5][5] = {-1};

void populate();
void neighbor();


void populate()
{
    int i,j = 0;
    srand(time(NULL));
    //assign random values to the matrix
    for(i=0;i<SIZE;++i){
        for(j=0; j<SIZE; ++j){
            matrixA[i][j] = rand() % 51;
        }
    }
}

//may be broken up later, but for now just figuring out how not to break the math.
void neighbor()
{
    
    int i = 0;
    int j = 0;
    int k = 0;
    
    int temp;
    
    
    for(i=0;i<SIZE;++i){
        for(j=0; j<SIZE; ++j){
            //reset temp
            temp=0;
            
            //self
            temp = matrixA[i][j];
            //top
            if (i-1>=0) {
                temp = temp+matrixA[i-1][j];
            }
            //bottom
            if (i+1<=SIZE) {
                temp = temp+matrixA[i+1][j];
            }
            //left
            if (j-1>=0) {
                temp = temp+matrixA[i][j-1];
            }
            //right
            if (j+1<=SIZE) {
                temp = temp+matrixA[i][j+1];
            }
            //diagTopR
            if ((i-1>=0)&&(j+1<=SIZE)) {
                temp = temp+matrixA[i-1][j+1];
            }
            //diagTopL
            if ((i-1>=0)&&(j-1>=0)) {
                temp = temp+matrixA[i-1][j-1];
            }
            //diagBottomR
            if ((i+1<=SIZE)&&(j+1<=SIZE)) {
                temp = temp+matrixA[i+1][j+1];
            }
            //diagBottomL
            if ((i+1<=SIZE)&&(j-1>=0)) {
                temp = temp+matrixA[i+1][j-1];
            }
//debug print
//printf("%d\n", temp);
            
            int flag = -1;
            
            if ((flag==-1)&&(temp % 10==0)) {
                matrixB[i][j]=0;
                flag = 1;
            }
            if ((flag==-1)&&(temp<50)) {
                matrixB[i][j] = matrixA[i][j]+3;
                flag = 1;
            }
            if ((flag==-1)&&(temp>50)&&(temp<150)) {
                matrixB[i][j] = matrixA[i][j]-3;
                flag = 1;
            }
            if ((flag==-1)&&(temp>150)) {
                matrixB[i][j]=1;
                flag = 1;
            }
            if (matrixB[i][j]<0) {
                matrixB[i][j]=0;
            }
        }
    }
    
    
    
    //print matrixA
    printf("Matrix A\n");
    for(i=0;i<SIZE;++i){
        for(j=0; j<SIZE; ++j){
            printf("%d\t", matrixA[i][j]);
        }
        printf("\n");
    }
    
    printf("\n\n\n");
    
    //print matrixB
    printf("Matrix B\n");
    for(i=0;i<SIZE;++i){
        for(j=0; j<SIZE; ++j){
            printf("%d\t", matrixB[i][j]);
        }
        printf("\n");
    }
}




int main()
{
    //sequentially solve the neighbor problem.
    populate();
    neighbor();

    return 0;
}
