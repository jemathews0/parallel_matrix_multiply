#ifndef _MATRIX_H
#define _MATRIX_H

/********************************************************************
 * A struct to hold a rectangular matrix of doubles. Must be 
 * initialized by calling matrixCreate( rows, cols);
 *******************************************************************/
typedef struct 
{
    unsigned int rows;
    unsigned int cols;
    double data[];
} Matrix;


Matrix * matrixCreate( unsigned rows, unsigned cols);
void matrixInit( Matrix * mat, double val);
void matrixRandomize( Matrix * mat, unsigned max);
void matrixRandomizeInt( Matrix * mat, unsigned max);
int matrixScale( Matrix * mat, double scalar);
void matrixFree( Matrix * mat );
void matrixPrint( Matrix* mat);

#endif
