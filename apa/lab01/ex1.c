/**
	The following program computes the matrix product between 2 statically defined matrices
	whose dimensions and whose contents are read on stdin.
	
	Riccardo Cappuzzo
*/

#include <stdlib.h>
#include <stdio.h>

#define MAX_DIM 10


void readDim(int *, int *);
int checkDim(int, int, int, int);
void readMatrix(float [][MAX_DIM], int, int);
void computeProduct(float [][MAX_DIM], int, int,
                   float [][MAX_DIM], int, int,
                   float [][MAX_DIM], int *, int *);
void writeMatrix(float [][MAX_DIM], int, int,
                    float [][MAX_DIM], int, int,
                    float [][MAX_DIM], int, int);
   

int 
main (int argc, char *argv[])
{
	float m1 [MAX_DIM][MAX_DIM], m2 [MAX_DIM][MAX_DIM], m3 [MAX_DIM][MAX_DIM];
	int r1, c1, r2, c2, r3, c3;
	
	readDim(&r1, &c1);
	readDim(&r2, &c2);
	
	if (! checkDim (r1, c1, r2, c2) )
	{
		fprintf (stderr, "Dimensions are not correct. MAX_DIM = %d\n", MAX_DIM);
		exit(1);
	} else
	{
		r3 = r1;
		c3 = c2;
		printf("Dimensions are correct\n");
		printf("Reading data for matrix 1\n");
		readMatrix (m1, r1, c1);
		printf("Reading data for matrix 2\n");
		readMatrix (m2, r2, c2);
		//writeMatrix(m1, r1, c1, m2, r2, c2, m3, r3, c3);	
		computeProduct (m1, r1, c1, m2, r2, c3, m3, &r3, &c3);
		writeMatrix(m1, r1, c1, m2, r2, c2, m3, r3, c3);
	}
	
	return 0;
}

// read the dimension of the matrix
void readDim(int *r, int *c)
{
	printf("Insert the number of rows: ");
	scanf("%d", r);
	printf("Insert the number of columns: ");
	scanf("%d", c);
}

int checkDim(int r1, int c1, int r2, int c2)
{
	if ((r1 > MAX_DIM)||(r2 > MAX_DIM) || (c1 > MAX_DIM) || (c2 > MAX_DIM)) // check whether the matrix dimension is larger than the limits
	{
		printf ("A dimension is beyond the limit.\n");
		return 0;
	} else
	{
		if (c1 != r2) 
		{
			printf("The number of rows of m1 is different from the number of columns of m2\n");
			return 0;
		}
	}
	return 1;
}

// fill the matrix reading from stdin
void readMatrix(float m[][MAX_DIM], int r, int c) 
{
	int i, j;
	
	for (i = 0; i < r; i += 1)
	{
		for (j = 0; j < c; j += 1)
		{
			printf ("r = %d c = %d: ", i, j);
			scanf ("%f", &m[i][j]);
		}
	}
}

// compute the product between the two matrices
void computeProduct(float m1[][MAX_DIM], int r1, int c1,
                    float m2[][MAX_DIM], int r2, int c2,
                    float m3[][MAX_DIM], int *r3, int *c3)
{
	int i, j, k;
	float sum = 0;
	
	*r3 = r1;
	*c3 = c2;
	
	for (i = 0; i < r1; i += 1)
	{
		// change row
		for (j = 0; j < c1; j += 1)
		{
			// change column
			for (k = 0; k < r2; k += 1)
			{
				sum+=m1[i][k]*m2[k][j]; // compute the row*column sum
			}
			m3[i][j] = sum;
			sum = 0;
		}
	}
}    

// write the matrices on stdout              
void writeMatrix   (float m1[][MAX_DIM], int r1, int c1,
                    float m2[][MAX_DIM], int r2, int c2,
                    float m3[][MAX_DIM], int r3, int c3)
{
	int i, j;
	
	printf("Matrix 1:\n");
	for (i = 0; i < r1; i += 1)
	{
		for (j = 0; j < c1; j += 1)
		{
			printf ("%f\t", m1[i][j]);
		}
		printf("\n");
	}
	
	printf("Matrix 2:\n");
	for (i = 0; i < r2; i += 1)
	{
		for (j = 0; j < c3; j += 1)
		{
			printf ("%f\t", m2[i][j]);
		}
		printf("\n");
	}
	
	printf("Matrix 3:\n");
	for (i = 0; i < r3; i += 1)
	{
		for (j = 0; j < c3; j += 1)
		{
			printf ("%f\t", m3[i][j]);
		}
		printf("\n");
	}
}   


